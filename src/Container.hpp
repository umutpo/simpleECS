#pragma once

#include "Managers/EntityManager.hpp"
#include "Managers/ComponentManager.hpp"
#include "Managers/SystemManager.hpp"
#include "Data/Types.hpp"   

#include <memory>

class Container {
public:
    void initialize() {
        mEntityManager = std::unique_ptr<EntityManager>(new EntityManager());
        mComponentManager = std::unique_ptr<ComponentManager>(new ComponentManager());
        mSystemManager = std::unique_ptr<SystemManager>(new SystemManager());
    }

    Entity createEntity() {
        return mEntityManager->createEntity();
    }

    void destroyEntity(Entity entity) {
        mEntityManager->destroyEntity(entity);
        mComponentManager->onEntityDestroyed(entity);
        mSystemManager->onEntityDestroyed(entity);
    }

    template <typename T>
    void registerComponent() {
        mComponentManager->registerComponent<T>();
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        Signature entitySignature = mEntityManager->getEntitySignature(entity);
        ComponentType componentType = mComponentManager->getComponentType<T>();
        entitySignature.set(componentType, true);
        mEntityManager->setEntitySignature(entity, entitySignature);
        mSystemManager->onEntitySignatureChanged(entity, entitySignature);
        
        mComponentManager->addComponent(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity) {
        Signature entitySignature = mEntityManager->getEntitySignature(entity);
        ComponentType componentType = mComponentManager->getComponentType<T>();
        entitySignature.set(componentType, false);
        mEntityManager->setEntitySignature(entity, entitySignature);
        mSystemManager->onEntitySignatureChanged(entity, entitySignature);
        
        mComponentManager->removeComponent<T>(entity);
    }

    template <typename T>
    T& getComponent(Entity entity) {
        return mComponentManager->getComponent<T>(entity);
    }

    template <typename T>
    ComponentType getComponentType() {
        return mComponentManager->getComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> registerSystemWithComponents(std::vector<ComponentType> components) {
        auto newSystem = registerSystem<T>();

        Signature systemSignature;
        for (auto& component : components) {
            systemSignature.set(component);
        }
        setSystemSignature<T>(systemSignature);

        return newSystem;
    }

    template <typename T>
    void setSystemSignature(Signature signature) {
        mSystemManager->setSignature<T>(signature);
    }

private:
    template <typename T>
    std::shared_ptr<T> registerSystem() {
        return mSystemManager->registerSystem<T>();
    }

    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
};