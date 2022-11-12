cmake_minimum_required(VERSION 3.10)

project(simpleECS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(simpleECS simpleECS.cpp 
    src/Data/ComponentArray.hpp
    src/Data/System.hpp
    src/Data/Types.hpp
    src/Managers/ComponentManager.hpp
    src/Managers/EntityManager.hpp
    src/Managers/SystemManager.hpp
    src/Data/Components/TransformComponent.hpp
    src/Data/Systems/PhysicsSystem.hpp
    src/Container.hpp)
