#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	CameraBase::Init();

	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.0f);
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	m_mWorld = m_mLocalPos;
}
