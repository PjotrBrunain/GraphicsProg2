#include "stdafx.h"
#include "ModelTestScene.h"

#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

ModelTestScene::ModelTestScene()
	:GameScene(L"ModelTestScene")
{
}

void ModelTestScene::Initialize()
{
	m_pChair = new GameObject{};
	auto diffuseMat =	MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	diffuseMat->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	ModelComponent* modelComp =  new ModelComponent{ L"Meshes/Chair.ovm" };
	m_pChair->AddComponent(modelComp);
	modelComp->SetMaterial(diffuseMat);
	AddChild(m_pChair);
	m_pChair->GetTransform()->Translate(0, 2, 0);

	auto rigidBody = new RigidBodyComponent{};

	PxConvexMesh* convexMesh{ ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc") };
	PxConvexMeshGeometry* convexMeshGeo{ new PxConvexMeshGeometry{convexMesh} };

	PxMaterial* pDefaultMat = PxGetPhysics().createMaterial(1.f, 1.f, 1.f);

	rigidBody->AddCollider(*convexMeshGeo, *pDefaultMat);
	m_pChair->AddComponent(rigidBody);

	GameSceneExt::CreatePhysXGroundPlane(*this);
}

void ModelTestScene::Update()
{
	GameScene::Update();
}
