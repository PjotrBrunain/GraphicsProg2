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

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

	void onTrigger(PxTriggerPair* pairs, PxU32 count) override;

	GameObject* m_pLevelMesh{};
	GameObject* m_pSphere1{};
	PxRigidDynamic* m_pSphere1Actor{};
	GameObject* m_pSphere2{};
	GameObject* m_pSphere3{};
	GameObject* m_pBox1{};
	GameObject* m_pBox2{};
	GameObject* m_pBoxTrigger1{};
	bool m_Trigger1{};
	bool m_Trigger1DoOnce{true};
	bool m_Trigger2{};
	bool m_Trigger2DoOnce{ true };
	GameObject* m_pBoxTrigger2{};
	FMOD::Sound* m_pBellSound{};

	GameObject* m_pHatch1{};
	PxRigidDynamic* m_pHatch1Actor{};
	GameObject* m_pHatch2{};
	PxRigidDynamic* m_pHatch2Actor{};
};

