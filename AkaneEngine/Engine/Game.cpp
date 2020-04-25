#include "Game.h"
#include "Actor.h"

Event<float>* Game::GetFrameEvent()
{
	return &Frame;
}

Event<float>* Game::GetEndFrameEvent()
{
	return &EndFrame;
}

void Game::DoFrame(float deltaTime)
{
	Frame.Invoke(deltaTime);
}

void Game::DoEndFrame(float deltaTime)
{
	EndFrame.Invoke(deltaTime);
}

void Game::LoadLevel(string levelName)
{}

void Game::UnloadLevel(string levelName)
{}

Actor* Game::CreateObject()
{
	return nullptr;
}

void Game::DestroyObject(Actor* toDestroy)
{}

void Game::DrawFrame()
{
	renderingSystem.OnFrame();
}
