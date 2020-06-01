#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include "ECSDefinitions.h"
#include "System.h"
#include <unordered_map>

class AKANEENGINE_API SystemManager
{
public:
	template<typename T>
	T* RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		T* system = new T();
		systems.insert({typeName, system });
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
			System* system = pair.second;
			system->entities.erase(entity);
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
				system->entities.insert(entity);
			}
			else
			{
				system->entities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> signatures;
	std::unordered_map<const char*, System*> systems;
};
