#pragma once

#include "../Data/Types.hpp"
#include "../Data/ComponentArray.hpp"

#include <unordered_map>
#include <memory>
#include <assert.h>

class ComponentManager {
public:
    void onEntityDestroyed(Entity entity) {
        for (auto& pair : mComponentArrays) {
            auto& component = pair.second;
            component->onEntityDestroyed(entity);
        }
    }

    template <typename T>
    void registerComponent() {
        const char* typeName = typeid(T).name;

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component is already registered!");

        mComponentTypes[typeName] = mNextComponentType;
        mComponentArrays[mNextComponentType] = std::make_shared(ComponentArray<T>());
        mNextComponentType++;
    }

    template <typename T>
    void getComponentType() {
        const char* typeName = typeid(T).name;

        assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Component does NOT exist!");

        return mComponentTypes[typeName];
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        return getComponentArray<T>()->addComponent(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity) {
        return getComponentArray<T>()->removeComponent(entity);
    }

    template <typename T>
    T& getComponent(Entity entity) {
        return getComponentArray<T>()->getComponent(entity);
    }
private:
    std::unordered_map<const char*, ComponentType> mComponentTypes{};

    std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> mComponentArrays{};

    ComponentType mNextComponentType{};
};