#pragma once

#include "Types.hpp"

#include <set>

class System {
public:
    virtual void Update(float deltaTime) = 0;
    std::set<Entity> mEntities{};
};