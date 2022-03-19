#include "stdafx.h"
#include "Assignment1Scene.h"

#include "ContentManager.h"
#include "CubePosColorNorm.h"
#include "MeshObject.h"
#include "SoundManager.h"
#include "SpherePosColorNorm.h"

void Assignment1Scene::Initialize()
{
	const PxMaterial* pDefaultMaterial{ PxGetPhysics().createMaterial(1.f, 0.f, 1.f) };
	//ground
	{
		PxRigidStatic* pGroundActor{ PxGetPhysics().createRigidStatic(PxTransform{PxQuat{PxPiDivTwo, PxVec3{0.f, 0.f, 1.f}}}) };
		PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
		GetPhysxScene()->addActor(*pGroundActor);
	}
	//Level
	{
		MeshObject* levelMesh{ new MeshObject{L"Resources/Meshes/Level.ovm"} };
		levelMesh->Initialize();
		m_pLevelMesh = levelMesh;
		AddGameObject(m_pLevelMesh);

		PxRigidStatic* pLevelActor{ PxGetPhysics().createRigidStatic(PxTransform(PxIdentity)) };
		PxTriangleMesh* triangleMesh{ ContentManager::GetInstance()->Load<PxTriangleMesh>(L"Resources/Meshes/Level.ovpt") };
		PxTriangleMeshGeometry* triangleMeshGeo{ new PxTriangleMeshGeometry{triangleMesh} };
		PxRigidActorExt::createExclusiveShape(*pLevelActor, *triangleMeshGeo, *pDefaultMaterial);
		m_pLevelMesh->AttachRigidActor(pLevelActor);
	}
	PxMaterial* pSphereMaterial{ PxGetPhysics().createMaterial(1.f, 0.f, 0.f) };
	//Spheres
	{
		const float SphereSize{ 1.f };


		m_pSphere1 = new SpherePosColorNorm{ SphereSize, 75, 75, XMFLOAT4(Colors::Beige) };
		AddGameObject(m_pSphere1);

		m_pSphere1->Translate(0, 5, 0);

		m_pSphere1Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
		PxRigidActorExt::createExclusiveShape(*m_pSphere1Actor, PxSphereGeometry(SphereSize), *pSphereMaterial);
		m_pSphere1->AttachRigidActor(m_pSphere1Actor);
		m_pSphere1Actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);

		m_pSphere2 = new SpherePosColorNorm{ SphereSize, 75, 75, XMFLOAT4(Colors::Beige) };
		AddGameObject(m_pSphere2);

		m_pSphere2->Translate(-5, 23, 0);

		PxRigidDynamic* pSphereActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
		PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry(SphereSize), *pSphereMaterial);
		m_pSphere2->AttachRigidActor(pSphereActor);

		m_pSphere3 = new SpherePosColorNorm{ SphereSize, 75, 75, XMFLOAT4(Colors::Beige) };
		AddGameObject(m_pSphere3);

		m_pSphere3->Translate(5, 23, 0);

		pSphereActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
		PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry(SphereSize), *pSphereMaterial);
		m_pSphere3->AttachRigidActor(pSphereActor);
	}
	//Boxes
	constexpr float CubeSize{ 2.f };
	{
		m_pBox1 = new CubePosColorNorm(CubeSize, CubeSize, CubeSize);
		AddGameObject(m_pBox1);

		m_pBox1->Translate(4, 5, 0);

		PxRigidDynamic* pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
		PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry{ CubeSize / 2.f,CubeSize / 2.f,CubeSize / 2.f }, *pSphereMaterial);
		m_pBox1->AttachRigidActor(pCubeActor);
		pCubeActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);

		m_pBox2 = new CubePosColorNorm(CubeSize, CubeSize, CubeSize);
		AddGameObject(m_pBox2);

		m_pBox2->Translate(-4, 5, 0);

		pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
		PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry{ CubeSize / 2.f,CubeSize / 2.f,CubeSize / 2.f }, *pSphereMaterial);
		m_pBox2->AttachRigidActor(pCubeActor);
		pCubeActor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
	}

	//Triggers
	{
		m_pBoxTrigger1 = new CubePosColorNorm(CubeSize, CubeSize, CubeSize);
		AddGameObject(m_pBoxTrigger1);

		m_pBoxTrigger1->Translate(-7, 2, 0);

		PxRigidStatic* pTriggerActor = PxGetPhysics().createRigidStatic(PxTransform(PxIdentity));
		PxShape* pTriggerShape = PxRigidActorExt::createExclusiveShape(*pTriggerActor, PxBoxGeometry{ CubeSize / 2.f,CubeSize / 2.f,CubeSize / 2.f }, *pSphereMaterial);
		m_pBoxTrigger1->AttachRigidActor(pTriggerActor);
		pTriggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		pTriggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

		m_pBoxTrigger2 = new CubePosColorNorm(CubeSize, CubeSize, CubeSize);
		AddGameObject(m_pBoxTrigger2);

		m_pBoxTrigger2->Translate(7, 2, 0);

		pTriggerActor = PxGetPhysics().createRigidStatic(PxTransform(PxIdentity));
		pTriggerShape = PxRigidActorExt::createExclusiveShape(*pTriggerActor, PxBoxGeometry{ CubeSize / 2.f,CubeSize / 2.f,CubeSize / 2.f }, *pSphereMaterial);
		pTriggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		pTriggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		m_pBoxTrigger2->AttachRigidActor(pTriggerActor);
	}

	//Hatches
	{
		m_pHatch1 = new CubePosColorNorm{ 2.f,0.5f,2.f };
		AddGameObject(m_pHatch1);

		m_pHatch1->Translate(-9.f, 17.f, 0.f);

		m_pHatch1Actor = PxCreateKinematic(PxGetPhysics(), PxTransform(PxIdentity), PxBoxGeometry{ 1.f,0.25f,1.f }, *pSphereMaterial, PxReal{ 10.f });
		m_pHatch1->AttachRigidActor(m_pHatch1Actor);

		m_pHatch2 = new CubePosColorNorm{ 2.f,0.5f,2.f };
		AddGameObject(m_pHatch2);

		m_pHatch2->Translate(9.f, 17.f, 0.f);

		m_pHatch2Actor = PxCreateKinematic(PxGetPhysics(), PxTransform(PxIdentity), PxBoxGeometry{ 1.f,0.25f,1.f }, *pSphereMaterial, PxReal{ 10.f });
		m_pHatch2->AttachRigidActor(m_pHatch2Actor);
	}
}

void Assignment1Scene::Update()
{
	const XMFLOAT3 forward{ GetSceneContext().GetCamera()->GetForward() };
	const XMFLOAT3 right{ GetSceneContext().GetCamera()->GetRight() };
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, VK_LEFT))
	{
		m_pSphere1->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ -right.x * 10, -right.y * 50, -right.z * 50 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, VK_RIGHT))
	{
		m_pSphere1->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ right.x * 10, right.y * 5000, right.z * 5000 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, VK_UP))
	{
		m_pSphere1->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ forward.x * 10, forward.y * 50, forward.z * 5000 }, PxForceMode::eIMPULSE);
	}
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::released, VK_DOWN))
	{
		m_pSphere1->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3{ -forward.x * 10, -forward.y * 5000, -forward.z * 5000 }, PxForceMode::eIMPULSE);
	}
	PxVec3 vec{ 1.f,1.f,1.f };
	PxRigidBodyExt::updateMassAndInertia(*m_pSphere1Actor, PxReal{ 1 }, &vec);


	if (m_Trigger1 && m_Trigger1DoOnce)
	{
		auto location = m_pHatch1->GetPosition();
		m_pHatch1Actor->setKinematicTarget(PxTransform{ location.x - 3.f, location.y, location.z });
		m_Trigger1DoOnce = false;
	}
	if (m_Trigger2 && m_Trigger2DoOnce)
	{
		auto location = m_pHatch2->GetPosition();
		m_pHatch2Actor->setKinematicTarget(PxTransform{ location.x + 3.f, location.y, location.z });
		m_Trigger2DoOnce = false;
	}
}

void Assignment1Scene::Draw() const
{
}

void Assignment1Scene::OnSceneActivated()
{
	GameScene::OnSceneActivated();
	SoundManager::GetInstance()->GetSystem()->createSound("Resources/Sounds/bell.mp3", FMOD_DEFAULT, nullptr, &m_pBellSound);
}

void Assignment1Scene::OnSceneDeactivated()
{
	GameScene::OnSceneDeactivated();
	m_pBellSound->release();
}

void Assignment1Scene::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	GameScene::onTrigger(pairs, count);

	if (pairs->triggerActor == m_pBoxTrigger1->GetRigidActor())
	{
		if (pairs->otherActor == m_pBox2->GetRigidActor())
		{
			FMOD::ChannelGroup* pChannelGroup{};
			SoundManager::GetInstance()->GetSystem()->getMasterChannelGroup(&pChannelGroup);
			FMOD::Channel* pChannel{};
			SoundManager::GetInstance()->GetSystem()->playSound(m_pBellSound, pChannelGroup, false, &pChannel);

			//PxRigidDynamic* pDynamicActor = dynamic_cast<PxRigidDynamic*>(m_pHatch1->GetRigidActor());
			//if (pDynamicActor)
			//{
			//	pDynamicActor->setKinematicTarget(PxTransform{ m_pHatch1->GetPosition().x - 3.f, m_pHatch1->GetPosition().y, m_pHatch1->GetPosition().z });
			//}
			m_Trigger1 = true;
			}
		std::cout << "trigger1\n";
	}
	if (pairs->triggerActor == m_pBoxTrigger2->GetRigidActor())
	{
		if (pairs->otherActor == m_pBox1->GetRigidActor())
		{
			FMOD::ChannelGroup* pChannelGroup{};
			SoundManager::GetInstance()->GetSystem()->getMasterChannelGroup(&pChannelGroup);
			FMOD::Channel* pChannel{};
			SoundManager::GetInstance()->GetSystem()->playSound(m_pBellSound, pChannelGroup, false, &pChannel);
			m_Trigger2 = true;
		}
		std::cout << "trigger2\n";
	}
}
