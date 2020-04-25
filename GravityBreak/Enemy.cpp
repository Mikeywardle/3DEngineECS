#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	recieveFrameEvent = true;
}

Enemy::~Enemy()
{
}

void Enemy::OnStartPlay()
{
	Actor::OnStartPlay();
	//cout << "Hello " << name << "\n";
}

void Enemy::OnFrame(float deltaTime)
{
	//cout << name << "\n";
}
