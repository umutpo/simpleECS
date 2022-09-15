#pragma once

#include "Types.hpp"

#include <array>
#include <queue>
#include <memory>
#include <assert.h>

class EntityManager {
public:
    EntityManager() {
        for (Entity entity = 0; entity < ENTITY_LIMIT; entity++) {
            mUnusedEntities.push(entity);
        }
    }

    Entity createEntity() {
        assert(!mUnusedEntities.empty() && "Limit for Entities is reached!");

        Entity newEntity = mUnusedEntities.front();
        mUnusedEntities.pop();

        return newEntity;
    }

    void destroyEntity(Entity entity) {
        mEntitySignatures[entity].reset();
        mUnusedEntities.push(entity);
    }

    void setEntitySignature(Entity entity, Signature newSignature) {
        mEntitySignatures[entity] = newSignature;
    }

    Signature getEntitySignature(Entity entity) {
        return mEntitySignatures[entity];
    }

private:
    std::queue<Entity> mUnusedEntities;
    std::array<Signature, ENTITY_LIMIT> mEntitySignatures;
};