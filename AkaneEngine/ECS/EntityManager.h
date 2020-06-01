#pragma once

#define AKANEENGINE_API __declspec(dllexport)
#include <queue>
#include <vector>

#include "ECSDefinitions.h"


class AKANEENGINE_API EntityManager
{
public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
		{
			availableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		Entity id = availableEntities.front();
		availableEntities.pop();
		++livingEntityCount;

		return id;
	}

	void DestroyEntity(Entity toDestroy)
	{
		signatures.erase(signatures.begin() + toDestroy);
		availableEntities.push(toDestroy);
		--livingEntityCount;
	}


	void SetSignature(Entity entity, Signature signature)
	{
		signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		return signatures[entity];
	}

private:

	std::queue<Entity> availableEntities;
	std::vector<Signature> signatures = std::vector<Signature>(MAX_ENTITIES);
	unsigned int livingEntityCount = 0;

};

