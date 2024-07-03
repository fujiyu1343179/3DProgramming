#pragma once

class CameraBase;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetCamera(std::shared_ptr<CameraBase> camera)
	{
		m_wpCamera = camera;
	}

private:

	void UpdateRotate(const Math::Vector3& srcMoveVec);

	std::shared_ptr<KdSquarePolygon>	m_spPoly	= nullptr;
	
	std::weak_ptr<CameraBase>	m_wpCamera;

	Math::Vector3 m_worldRot;
};
//前方宣言：ポインタは中身を知らなくていいのでできる
//			実体のあるものは作られた時点で中身を持っていなければいけないため
// 〇 CameraBase　*m_wpCamera;
// × CameraBase　m_wpCamera;