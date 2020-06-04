#include "Engine/ApplicationContext.h"
#include "ECS/ECSManager.h"
#include <iostream>
#include "Test/A.h"
#include "Test/X.h"
#include "Test/B.h"


ECSManager manager;
int main() 
{
	ApplicationContext::Initialize();
	return ApplicationContext::Run();

	//manager.Init();

	//manager.RegisterComponent<AComponent>();
	//manager.RegisterComponent<XComponent>();
	//manager.RegisterComponent<BComponent>();

	//ASystem* system = manager.RegisterSystem<ASystem>();

	//Signature signature;
	//signature.set(manager.GetComponentType<AComponent>());
	//signature.set(manager.GetComponentType<XComponent>());

	//manager.SetSystemSignature<ASystem>(signature);


	//BSystem* bsystem = manager.RegisterSystem<BSystem>();
	//Signature bsignature;
	//bsignature.set(manager.GetComponentType<BComponent>());
	//bsignature.set(manager.GetComponentType<XComponent>());

	//manager.SetSystemSignature<BSystem>(bsignature);

	//Entity entity = manager.CreateEntity();
	//manager.AddComponent(entity, AComponent());
	//manager.AddComponent(entity, XComponent());

	//Entity entity2 = manager.CreateEntity();
	//manager.AddComponent(entity2, AComponent());
	//manager.AddComponent(entity2, XComponent());
	//manager.AddComponent(entity2, BComponent());

	//manager.GetComponent<AComponent>(entity2).id = 2;
	//manager.GetComponent<XComponent>(entity2).id = 3;
	//manager.GetComponent<BComponent>(entity2).id = 5;

	//Entity entity3 = manager.CreateEntity();
	//manager.AddComponent(entity3, XComponent());
	//manager.AddComponent(entity3, BComponent());
	//manager.GetComponent<XComponent>(entity3).id = 4;
	//manager.GetComponent<BComponent>(entity3).id = 6;

	//system->OnFrame(0);
	//bsystem->OnFrame(0);

	//manager.DestroyEntity(entity);
	//std::cout << "---------------------------" << std::endl;
	//system->OnFrame(0);



	return 0;
}