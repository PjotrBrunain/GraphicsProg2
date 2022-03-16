#pragma once
#include "GameScene.h"
class Assignment0Scene : public GameScene
{
public:
	Assignment0Scene():GameScene(L"Assignment0Scene"){}
	~Assignment0Scene() override = default;
	Assignment0Scene(const Assignment0Scene&) = delete;
	Assignment0Scene(Assignment0Scene&&) noexcept = delete;
	Assignment0Scene& operator=(const Assignment0Scene&) = delete;
	Assignment0Scene& operator=(Assignment0Scene&&) noexcept = delete;
protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

	std::vector<GameObject*> m_pCubes{};
	GameObject* m_pSphere{};
	PxRigidDynamic* m_pSphereActor{};
};

