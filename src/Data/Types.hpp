#pragma once

#include <bitset>

const unsigned int ENTITY_LIMIT = 32;
const unsigned int COMPONENT_LIMIT = 16;

using Entity = unsigned int;
using Signature = std::bitset<COMPONENT_LIMIT>;
using ComponentType = std::uint8_t;

class Vec3 {
public:
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    float x;
    float y;
    float z;
};