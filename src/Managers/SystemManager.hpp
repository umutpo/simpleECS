#pragma once

#include "../Data/Types.hpp"
#include "../Data/System.hpp"

#include <unordered_map>
#include <memory>
#include <assert.h>

class SystemManager {
public:
    void onEntityDestroyed(Entity entity) {
        for (auto& pair : mSystems) {
            auto& system = pair.second;

            system->mEntities.erase(entity);
        }
    }

    template <typename T>
    std::shared_ptr<T> registerSystem() {
        const char* typeName = typeid(T).name();

        assert(mSystemSignatures.find(typeName) == mSystemSignatures.end() && "System already exists!");

        auto newSystem = std::make_shared<T>();
        mSystems[typeName] = newSystem;
        return newSystem;
    }

    template <typename T>
    void setSignature(Signature signature) {
        const char* typeName = typeid(T).name();
        mSystemSignatures[typeName] = signature;
    }

    void onEntitySignatureChanged(Entity entity, Signature newSignature) {
        for (auto& pair : mSystems) {
            const char* systemType = pair.first;
            auto& system = pair.second;

            Signature oldSignature = mSystemSignatures[systemType];
            if ((oldSignature & newSignature) == oldSignature) {
                system->mEntities.insert(entity);
            } else {
                system->mEntities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> mSystemSignatures;

    std::unordered_map<const char*, std::shared_ptr<System>> mSystems;
};