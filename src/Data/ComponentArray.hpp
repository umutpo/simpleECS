#pragma once

#include "Types.hpp"

#include <array>
#include <unordered_map>
#include <assert.h>

class IComponentArray {
public:
    virtual void onEntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
public:
    void onEntityDestroyed(Entity entity) override {
        assert(entity < ENTITY_LIMIT && "Invalid Entity ID!");

        removeComponent(entity);
    }

    void addComponent(Entity entity, T component) {
        assert(mIdToIndex.find(entity) == mIdToIndex.end() && "Component exists!");

        mComponentArray[mNextIndex] = component;
        mIdToIndex[entity] = mNextIndex;
        mIndexToId[mNextIndex] = entity;

        mNextIndex++;
    }

    void removeComponent(Entity entity) {
        assert(mIdToIndex.find(entity) != mIdToIndex.end() && "Component does NOT exist!");

        unsigned int replacedComponentIndex = mIdToIndex[entity];
        unsigned int lastComponentIndex = mNextIndex - 1;
        Entity lastComponentEntity = mIndexToId[lastComponentIndex];

        mIdToIndex[lastComponentEntity] = replacedComponentIndex;
        mIndexToId[replacedComponentIndex] = lastComponentEntity;
        mComponentArray[replacedComponentIndex] = mComponentArray[lastComponentIndex];
        
        mIdToIndex.erase(entity);
        mIndexToId.erase(lastComponentIndex);
        
        mNextIndex--;
    }

    T& getComponent(Entity entity) {
        assert(mIdToIndex.find(entity) != mIdToIndex.end() && "Component does NOT exist!");

        return mComponentArray[mIdToIndex[entity]];
    }
private:
    std::array<T, ENTITY_LIMIT> mComponentArray;

    std::unordered_map<Entity, unsigned int> mIdToIndex{};
    std::unordered_map<unsigned int, Entity> mIndexToId{};

    int mNextIndex = 0;
};