#pragma once

#include "../System.hpp"
#include "../../Container.hpp"
#include "../Components/TransformComponent.hpp"

extern Container globalContainer;

class PhysicsSystem : public System {
public:
    void Update(float deltaTime) {
        for (auto& entity : mEntities) {
            TransformComponent& transformComponent = globalContainer.getComponent<TransformComponent>(entity);

            transformComponent.position.x += deltaTime;
            transformComponent.position.y += deltaTime;
            transformComponent.position.z += deltaTime;
        }
    }
};