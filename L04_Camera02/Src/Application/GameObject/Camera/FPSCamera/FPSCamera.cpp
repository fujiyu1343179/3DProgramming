#include "FPSCamera.h"

void FPSCamera::Init()
{
	//基準点として(ターゲット)からどれだけ離れえているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.f);

	//マウスカーソルを画面中央に固定
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void FPSCamera::Update()
{
	//ターゲットの行列(有効な場合使用する)
	Math::Matrix targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}

	//カメラの回転
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_Rotation * m_LocalPos * targetMat;

	CameraBase::Update();
}

void FPSCamera::UpdateRotateByMouse()
{
	//マウスでカメラの回転させる処理
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//実際にカメラを回転させる処理
	m_DegAng.x += mouseMove.y * 0.15f;//縦
	m_DegAng.y += mouseMove.x * 0.15f;//横

	//回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}
