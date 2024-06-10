﻿#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	//基準点として(ターゲット)からどれだけ離れえているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 6.f, -5.f);

	//どれだけ傾けているか
	m_Rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	CameraBase::Init();
}

void TrackingCamera::Update()
{
	//ターゲットの行列(有効な場合使用する)
	Math::Matrix targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = spTarget->GetMatrix();
	}

	m_mWorld = m_Rotation * m_LocalPos * targetMat;

	CameraBase::Update();
}
