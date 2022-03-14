#pragma once
#include "GameScene.h"
class Assignment1Scene : public GameScene
{
public:
	Assignment1Scene():GameScene(L"Assignment1Scene"){}
	~Assignment1Scene() override = default;
	Assignment1Scene(const Assignment1Scene& other) = delete;
	Assignment1Scene(Assignment1Scene&& other) noexcept = delete;
	Assignment1Scene& operator=(const Assignment1Scene& other) = delete;
	Assignment1Scene& operator=(Assignment1Scene&& other) noexcept = delete;
};

