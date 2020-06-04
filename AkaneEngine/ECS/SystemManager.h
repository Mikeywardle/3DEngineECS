#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include "ECSDefinitions.h"
#include "System.h"
#include <unordered_map>
#include <algorithm>
#include <vector>

class AKANEENGINE_API SystemManager
{
public:
	template<typename T>
	T* RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		T* system = new T();
		systems.insert({typeName, system });
		system->OnRegister();
		return system;

	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();
		signatures.insert({ typeName, signature });
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : systems)
		{
			std::vector<Entity>* entities = &pair.second->entities;
			entities->erase(std::remove(entities->begin(), entities->end(),entity), entities->end());
		}
	}
	
	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : systems)
		{
			const char* type = pair.first;
			System* system = pair.second;
			Signature systemSignature = signatures[type];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.push_back(entity);
			}
			else
			{
				std::vector<Entity>* entities = &system->entities;
				entities->erase(std::remove(entities->begin(), entities->end(), entity), entities->end());
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> signatures;
	std::unordered_map<const char*, System*> systems;
};
