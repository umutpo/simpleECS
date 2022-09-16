#pragma once

#include <Managers/EntityManager.hpp>
#include <Managers/ComponentManager.hpp>
#include <Managers/SystemManager.hpp>
#include <memory>

class Container {
public:
    void initialize() {
        mEntityManager = std::make_unique<EntityManager>();
        mComponentManager = std::make_unique<ComponentManager>();
        mSystemManager = std::make_unique<SystemManager>();
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
        Signature entitySignature = mEntityManager.getEntitySignature(entity);
        ComponentType componentType = mComponentManager->getComponentType<T>();
        entitySignature.set(componentType, true);
        mEntityManager->setEntitySignature(entity, entitySignature);
        mSystemManager->onEntitySignatureChanged(entity, entitySignature);
        
        mComponentManager->addComponent(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity) {
        Signature entitySignature = mEntityManager.getEntitySignature(entity);
        ComponentType componentType = mComponentManager->getComponentType<T>();
        entitySignature.set(componentType, false);
        mEntityManager->setEntitySignature(entity, entitySignature);
        mSystemManager->onEntitySignatureChanged(entity, entitySignature);
        
        mComponentManager->removeComponent(entity);
    }

    template <typename T>
    const char* getComponentType() {
        return mComponentManager->getComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> registerSystem() {
        return mSystemManager->registerSystem<T>();
    }

    template <typename T>
    void setSystemSignature(Signature signature) {
        mSystemManager->setSignature<T>(signature);
    }

private:
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
};