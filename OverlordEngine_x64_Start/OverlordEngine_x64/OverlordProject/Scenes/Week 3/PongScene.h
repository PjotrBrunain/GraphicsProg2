#pragma once
class PongScene : public GameScene
{
public:
	PongScene();
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;
protected:
	void Initialize() override;
	void Update() override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

	GameObject* m_pPaddle1{};
	GameObject* m_pPaddle2{};
	GameObject* m_pPingPongBall{};

	GameObject* m_pRightTrigger{};
	GameObject* m_pLeftTrigger{};

	bool Start{ false };
};

