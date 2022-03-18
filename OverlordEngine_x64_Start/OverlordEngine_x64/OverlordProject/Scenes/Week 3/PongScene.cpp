#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

PongScene::PongScene()
	:GameScene(L"PongScene")
{}

void PongScene::Initialize()
{
	GameObject* pCameraObject = new GameObject{};
	CameraComponent* pCameraComponent = new CameraComponent{};
	pCameraObject->GetTransform()->Translate(0.f, 100.f, 0.f);
	pCameraObject->GetTransform()->Rotate(90.f, 0.f, 0.f);
	pCameraObject->AddComponent(pCameraComponent);
	AddChild(pCameraObject);
	SetActiveCamera(pCameraComponent);

	PxMaterial* pPaddleMaterial{ PxGetPhysics().createMaterial(0.f,0.f,1.1f) };
	//Paddles
	{
		const float paddleWidth{2.f};
		const float paddleHeight{1.f};
		const float paddleDepth{8.f};
		m_pPaddle1 = new CubePrefab{ paddleWidth,paddleHeight,paddleDepth,XMFLOAT4(Colors::White) };

		m_pPaddle1->GetTransform()->Translate(70.f, 0.f, 0.f);
		AddChild(m_pPaddle1);

		//m_pPaddle1Actor = PxCreateKinematic(PxGetPhysics(), PxTransform(PxIdentity), PxBoxGeometry{ paddleWidth / 2.f,paddleHeight / 2.f,paddleDepth / 2.f }, *pPaddleMaterial, 1000.f);
		RigidBodyComponent* pRigidBodyComponent{new RigidBodyComponent(true)};
		pRigidBodyComponent->AddCollider(PxBoxGeometry{ paddleWidth / 2.f,paddleHeight / 2.f,paddleDepth / 2.f }, *pPaddleMaterial);
		m_pPaddle1->AddComponent(pRigidBodyComponent);

		m_pPaddle2 = new CubePrefab{ paddleWidth, paddleHeight, paddleDepth, XMFLOAT4(Colors::White) };

		m_pPaddle2->GetTransform()->Translate(-70.f, 0.f, 0.f);
		AddChild(m_pPaddle2);

		pRigidBodyComponent = new RigidBodyComponent(true);
		pRigidBodyComponent->AddCollider(PxBoxGeometry{ paddleWidth / 2.f,paddleHeight / 2.f,paddleDepth / 2.f }, *pPaddleMaterial);
		m_pPaddle2->AddComponent(pRigidBodyComponent);
	}

	//PingPongBall
	{
		const float pingpongRadius{ 1.f };
		PxMaterial* pPingPongMaterial{ PxGetPhysics().createMaterial(0.f,0.f,1.f) };
		m_pPingPongBall = new SpherePrefab{pingpongRadius};
		RigidBodyComponent* pRigidBodyComponent{ new RigidBodyComponent{} };
		pRigidBodyComponent->SetConstraint(RigidBodyConstraint::TransY, false);
		pRigidBodyComponent->AddCollider(PxSphereGeometry{ pingpongRadius }, *pPingPongMaterial);
		m_pPingPongBall->AddComponent(pRigidBodyComponent);
		AddChild(m_pPingPongBall);

	}

	//Borders
	{
		GameObject* pTopBorder = new GameObject{};
		RigidBodyComponent* pTopBorderRigid{ new RigidBodyComponent(true) };
		pTopBorder->GetTransform()->Translate(0.f, 0.f, 42.f);
		pTopBorderRigid->AddCollider(PxBoxGeometry{ 200.f,2.f,1.f },*pPaddleMaterial);
		pTopBorder->AddComponent(pTopBorderRigid);
		AddChild(pTopBorder);

		GameObject* pBottomBorder = new GameObject{};
		RigidBodyComponent* pBottomBorderRigid{ new RigidBodyComponent(true) };
		pBottomBorder->GetTransform()->Translate(0.f, 0.f, -42.f);
		pBottomBorderRigid->AddCollider(PxBoxGeometry{ 200.f,2.f,1.f }, *pPaddleMaterial);
		pBottomBorder->AddComponent(pBottomBorderRigid);
		AddChild(pBottomBorder);
	}

	//EndTriggers
	{
		m_pLeftTrigger = new GameObject{};
		m_pLeftTrigger->GetTransform()->Translate(-86.f, 0.f, 0.f);

		RigidBodyComponent* pRigidBodyComponent{ new RigidBodyComponent(true) };
		auto colliderId = pRigidBodyComponent->AddCollider(PxBoxGeometry{ 1.f,20.f,100.f }, *pPaddleMaterial, true);
		m_pLeftTrigger->AddComponent(pRigidBodyComponent);
		AddChild(m_pLeftTrigger);
		auto collider = pRigidBodyComponent->GetCollider(colliderId);
		collider.SetTrigger(true);

		m_pLeftTrigger->SetOnTriggerCallBack([this](GameObject* pTrigger, GameObject* pOther, PxTriggerAction action)
			{
				if (action == PxTriggerAction::ENTER && pOther == m_pPingPongBall && pTrigger == m_pLeftTrigger)
				{
					m_pPingPongBall->GetTransform()->Translate(0, 0, 0);
					Start = true;
				}
			});

		m_pRightTrigger = new GameObject{};
		m_pRightTrigger->GetTransform()->Translate(86.f, 0.f, 0.f);

		pRigidBodyComponent = new RigidBodyComponent(true);
		colliderId = pRigidBodyComponent->AddCollider(PxBoxGeometry{ 1.f,20.f,100.f }, *pPaddleMaterial, true);
		m_pRightTrigger->AddComponent(pRigidBodyComponent);
		AddChild(m_pRightTrigger);
		collider = pRigidBodyComponent->GetCollider(colliderId);
		collider.SetTrigger(true);

		m_pRightTrigger->SetOnTriggerCallBack([this](GameObject* pTrigger, GameObject* pOther, PxTriggerAction action)
			{
				if (action == PxTriggerAction::ENTER && pOther == m_pPingPongBall && pTrigger == m_pRightTrigger)
				{
					m_pPingPongBall->GetTransform()->Translate(0, 0, 0);
					Start = true;
				}
			});
	}
}

void PongScene::Update()
{
	if (Start)
	{
		m_pPingPongBall->GetComponent<RigidBodyComponent>()->AddForce({ -2000.f,0.f,-2000.f });
		Start = false;
	}
	GameScene::Update();
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_UP))
	{
		auto location = m_pPaddle1->GetTransform()->GetPosition();
		m_pPaddle1->GetTransform()->Translate(XMFLOAT3{ location.x, location.y, location.z + 1.f });
	}
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_DOWN))
	{
		auto location = m_pPaddle1->GetTransform()->GetPosition();
		m_pPaddle1->GetTransform()->Translate(XMFLOAT3{ location.x, location.y , location.z - 1.f });
	}
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, 'W'))
	{
		auto location = m_pPaddle2->GetTransform()->GetPosition();
		m_pPaddle2->GetTransform()->Translate(XMFLOAT3{ location.x, location.y , location.z + 1.f });
	}
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, 'S'))
	{
		auto location = m_pPaddle2->GetTransform()->GetPosition();
		m_pPaddle2->GetTransform()->Translate(XMFLOAT3{ location.x, location.y , location.z - 1.f });
	}
}

void PongScene::OnSceneActivated()
{
	GameScene::OnSceneActivated();
	m_pPingPongBall->GetComponent<RigidBodyComponent>()->AddForce({ -200000.f,0.f,-200000.f });
}

void PongScene::OnSceneDeactivated()
{
	GameScene::OnSceneDeactivated();
}
