#include <iostream>

#include "src/Container.hpp"
#include "src/Data/Components/TransformComponent.hpp"
#include "src/Data/Systems/PhysicsSystem.hpp"

#include <memory>
#include <vector>
#include <chrono>

Container globalContainer;

void initializeEntities(std::vector<Entity>& entities) {
    for (auto& entity : entities)
	{
		entity = globalContainer.createEntity();

		globalContainer.addComponent(
			entity,
			TransformComponent{Vec3(0.0f, 1.0f, 0.0f)});
	}
}

int main() {
    std::cout << "Simple ECS program started!" << std::endl;

    std::vector<Entity> entities(ENTITY_LIMIT);

    // Initialize the global container
    globalContainer.initialize();

    // Register Components
    globalContainer.registerComponent<TransformComponent>();

    // Register PhysicsSystem
    std::vector<ComponentType> physicsSystemComponents;
    physicsSystemComponents.push_back(globalContainer.getComponentType<TransformComponent>());
    auto physicsSystem = globalContainer.registerSystemWithComponents<PhysicsSystem>(physicsSystemComponents);

    // Initialize entities
    initializeEntities(entities);

    // Game Loop / Tick
    float deltaTime = 0.0f;
    while(true) {
        auto startTime = std::chrono::high_resolution_clock::now();

		physicsSystem->Update(deltaTime);

		auto stopTime = std::chrono::high_resolution_clock::now();

        std::cout << "First entity's x reached: " << globalContainer.getComponent<TransformComponent>(entities[0]).position.x << std::endl;
    }

    return 0;
}