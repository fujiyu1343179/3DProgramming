#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	void SetCamera(const std::shared_ptr<KdCamera> camera)
	{
		m_wpCamera = camera;
	}
	void SetTerrain(const std::shared_ptr<KdGameObject> terrain)
	{
		m_wpTerrain = terrain;
	}

private:
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	std::weak_ptr<KdCamera> m_wpCamera;
	std::weak_ptr<KdGameObject> m_wpTerrain;
	Math::Vector3 m_TargetPos = Math::Vector3::Zero;
	KdTexture m_hamu;
};