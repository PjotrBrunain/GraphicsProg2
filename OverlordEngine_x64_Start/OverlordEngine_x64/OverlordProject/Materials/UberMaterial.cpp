#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial()
	:Material<UberMaterial>(L"Effects/UberShader.fx")
{}

void UberMaterial::InitializeEffectVariables()
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(L"Textures/Skulls_Diffusemap.tga");
	SetVariable_Texture(L"gTextureDiffuse", m_pDiffuseTexture);

	SetVariable_Scalar(L"gUseTextureDiffuse", true);

	m_pNormalTexture = ContentManager::Load<TextureData>(L"Textures/Skulls_Normalmap.tga");
	SetVariable_Texture(L"gTextureNormal", m_pNormalTexture);

	SetVariable_Scalar(L"gUseTextureNormal", true);
}
