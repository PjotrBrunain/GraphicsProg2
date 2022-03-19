#include "stdafx.h"
#include "SpikyScene.h"

#include "Materials/SpikyMaterial.h"

SpikyScene::SpikyScene()
	:GameScene(L"SpikyScene")
{
}

void SpikyScene::Initialize()
{
	m_pSphere = new GameObject{};
	auto modelComp = new ModelComponent{ L"Meshes/OctaSphere.ovm" };
	m_pSphere->AddComponent(modelComp);
	m_pSphere->GetTransform()->Scale(15.f, 15.f, 15.f);
	m_pSpikyMaterial = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();
	modelComp->SetMaterial(m_pSpikyMaterial);
	AddChild(m_pSphere);

	GetSceneSettings().drawGrid = false;
	GetSceneSettings().enableOnGUI = true;
}

void SpikyScene::OnGUI()
{
	GameScene::OnGUI();
	m_pSpikyMaterial->DrawImGui();
}

void SpikyScene::Update()
{
	GameScene::Update();
	auto rotation = m_pSphere->GetTransform()->GetWorldRotation();
	m_pSphere->GetTransform()->Rotate(rotation.x, rotation.y + turnRate * GetSceneContext().pGameTime->GetElapsed(), rotation.z);
}
