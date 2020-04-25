#include "Engine/ApplicationContext.h"
#include "TestLevel.h"

int main() 
{
	ApplicationContext::Initialize();
	return ApplicationContext::Run();
}