#include "stdafx.h"
#include "UberMaterialScene.h"

#include "Materials/UberMaterial.h"

UberMaterialScene::UberMaterialScene()
	:GameScene(L"UberMaterialScene")
{
}

void UberMaterialScene::Initialize()
{
	m_pUberMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();

	m_pSphere = new GameObject{};
	auto model = new ModelComponent{ L"Meshes/Sphere.ovm" };
	m_pSphere->AddComponent(model);
	model->SetMaterial(m_pUberMaterial);
	AddChild(m_pSphere);
	m_pSphere->GetTransform()->Scale(10.f, 10.f, 10.f);

	GetSceneSettings().drawGrid = false;
	GetSceneSettings().enableOnGUI = true;
}

void UberMaterialScene::Draw()
{
	GameScene::Draw();
}

void UberMaterialScene::OnGUI()
{
	GameScene::OnGUI();
	m_pUberMaterial->DrawImGui();
}
