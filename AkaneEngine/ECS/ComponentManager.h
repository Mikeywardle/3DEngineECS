#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include "ECSDefinitions.h"
#include "ComponentArray.h"
#include <unordered_map>
#include <typeinfo>

class AKANEENGINE_API ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		componentTypes.insert({ typeName, nextComponentType });
		componentArrays.insert({typeName, new ComponentArray<T>()});
		++nextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();
		return componentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}


	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : componentArrays)
		{
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> componentTypes;
	std::unordered_map<const char*, IComponentArray*> componentArrays;

	ComponentType nextComponentType;

	template<typename T>
	ComponentArray<T>* GetComponentArray()
	{
		const char* typeName = typeid(T).name();
		return (ComponentArray<T>*)(componentArrays[typeName]);
	}
};
