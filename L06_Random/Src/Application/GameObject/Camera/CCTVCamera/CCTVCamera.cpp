#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	CameraBase::Init();

	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -10.0f);

	//一旦行列を確定させる
	m_mWorld = m_mLocalPos;
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

	//カメラの回転処理
	UpdateLookAtRotate(_targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	//元は長いコードになる

	//目の位置(カメラ),目的地(キャラ),上方向の行列		LH：左手座標系
	Math::Matrix shadowVP =
		DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);//対象Aから対象Bへの行列
	//		↑	キャラから見たカメラの位置

	m_mWorld = shadowVP.Invert();//Invert()：反転
}
