#pragma once

class SpikyMaterial;

class SpikyScene : public GameScene
{
public:
	SpikyScene();
	~SpikyScene() override = default;

	SpikyScene(const SpikyScene& other) = delete;
	SpikyScene(SpikyScene&& other) noexcept = delete;
	SpikyScene& operator=(const SpikyScene& other) = delete;
	SpikyScene& operator=(SpikyScene&& other) noexcept = delete;
protected:
	void Initialize() override;
	void OnGUI() override;
	void Update() override;
private:
	SpikyMaterial* m_pSpikyMaterial{};
	GameObject* m_pSphere{};
	float turnRate{ 20.f };
};
