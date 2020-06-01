#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include <vector>
#include <unordered_map>
#include "ECSDefinitions.h"

class AKANEENGINE_API IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class AKANEENGINE_API ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		size_t newIndex = size;
		entityToIndexMap[entity] = newIndex;
		indexToEntityMap[newIndex] = entity;
		components[newIndex] = component;
		++size;

	}

	void RemoveData(Entity entity)
	{
		size_t removedIndex = entityToIndexMap[entity];
		size_t lastElementIndex = size - 1;
		components[removedIndex] = components[lastElementIndex];

		Entity lastEntity = indexToEntityMap[lastElementIndex];
		entityToIndexMap[lastEntity] = removedIndex;
		indexToEntityMap[removedIndex] = lastElementIndex;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(lastElementIndex);

		--size;
	}

	T& GetData(Entity entity)
	{
		return components[entityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity)
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			RemoveData(entity);
	}

private:
	size_t size;
	std::vector<T> components = std::vector<T>(MAX_ENTITIES);

	std::unordered_map<Entity, size_t> entityToIndexMap;
	std::unordered_map<size_t, Entity> indexToEntityMap;

};
