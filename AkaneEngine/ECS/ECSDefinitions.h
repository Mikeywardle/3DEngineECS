#pragma once
#include <bitset>

using Entity = unsigned int;
using ComponentType = unsigned short;

const Entity MAX_ENTITIES = 100000;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
