﻿#include "CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)//二重初期化を防ぐ
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::Update()
{
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera)return;

	m_spCamera->SetToShader();
}
