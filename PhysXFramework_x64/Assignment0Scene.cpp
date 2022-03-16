#include "stdafx.h"
#include "Assignment0Scene.h"

#include "CubePosColorNorm.h"
#include "SpherePosColorNorm.h"

void Assignment0Scene::Initialize()
{
	PxRigidStatic* pGroundActor{ PxGetPhysics().createRigidStatic(PxTransform{PxQuat{PxPiDivTwo, PxVec3{0.f, 0.f, 1.f}}}) };
	const PxMaterial* pDefaultMaterial{ PxGetPhysics().createMaterial(1.f, 0.f, 1.f) };
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	GetPhysxScene()->addActor(*pGroundActor);

	float CubeSize{1};
	float padding{ CubeSize/2.f};
	
	PxMaterial* pCubeMaterial = PxGetPhysics().createMaterial(.5f, .5f, .5f);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			auto cube = new CubePosColorNorm(CubeSize, CubeSize, CubeSize);
			AddGameObject(cube);
			if (j>=0)
			{
				cube->Translate((float(j) * CubeSize) + padding * float(j), float(i) * CubeSize + padding * float(i), 0);
			}
			else
			{
				cube->Translate((float(j) * CubeSize) - padding*float(j), float(i) * CubeSize + padding * float(i), 0);
			}
			PxRigidDynamic* pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
			PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry{ CubeSize/2.f,CubeSize/2.f,CubeSize/2.f }, *pCubeMaterial);
			cube->AttachRigidActor(pCubeActor);
		}
	}

	m_pSphere = new SpherePosColorNorm{ CubeSize, 75, 75, XMFLOAT4(Colors::Beige) };
	AddGameObject(m_pSphere);

	m_pSphere->Translate(0, 0, -5);

	m_pSphereActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*m_pSphereActor, PxSphereGeometry(CubeSize), *pCubeMaterial);
	m_pSphere->AttachRigidActor(m_pSphereActor);
}

void Assignment0Scene::Update()
{
	const XMFLOAT3 forward{ GetSceneContext().GetCamera()->GetForward() };
	const XMFLOAT3 right{ GetSceneContext().GetCamera()->GetRight() };
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, 'A'))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ -right.x * 50, -right.y * 50, -right.z * 50 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, 'D'))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ right.x * 5000, right.y * 5000, right.z * 5000 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, 'W'))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ forward.x * 50, forward.y * 50, forward.z * 5000 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released,'S'))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ -forward.x * 5000, -forward.y * 5000, -forward.z * 5000 }, PxForceMode::eIMPULSE);
	}
	PxVec3 vec{ 2.f,2.f,2.f };
	PxRigidBodyExt::updateMassAndInertia(*m_pSphereActor, PxReal{ 10 }, &vec);
}

void Assignment0Scene::Draw() const
{
}

void Assignment0Scene::OnSceneActivated()
{
	GameScene::OnSceneActivated();
}

void Assignment0Scene::OnSceneDeactivated()
{
	GameScene::OnSceneDeactivated();
}
