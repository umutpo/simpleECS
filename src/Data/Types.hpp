#pragma once

#include <bitset>

const unsigned int ENTITY_LIMIT = 32;
const unsigned int COMPONENT_LIMIT = 16;

using Entity = unsigned int;
using Signature = std::bitset<COMPONENT_LIMIT>;
using ComponentType = std::bitset<COMPONENT_LIMIT>;