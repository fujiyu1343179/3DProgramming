#include "TPSCamera.h"

void TPSCamera::Init()
{
	//基準点として(ターゲット)からどれだけ離れえているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);

	//マウスカーソルを画面中央に固定
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
{
	//ターゲットの行列(有効な場合使用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラの回転
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_LocalPos * m_Rotation * _targetMat;

	//===めり込み防止のための座標補正計算===

	//①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo _rayInfo;

	//レイの発射位置を設定
	_rayInfo.m_pos = GetPos();

	//レイの当たり判定を取りたいオブジェクトタイプを設定
	_rayInfo.m_type = KdCollider::TypeGround;

	//レイの発射方向を設定
	_rayInfo.m_dir = Math::Vector3::Down;

	//レイの長さを設定
	_rayInfo.m_range = 1000.f;
	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1f;
		_rayInfo.m_dir = _targetPos - GetPos();
		_rayInfo.m_range = _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}

	//②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> _spObj = wpObj.lock();
		if (_spObj)
		{
			std::list<KdCollider::CollisionResult> _result;
			_spObj->Intersects(_rayInfo, &_result);

			//③結果を使って座標を補正する
			//レイに当たったリストから一番近いオブジェクトを検出
			float _maxOverLap = 0;
			Math::Vector3 _hitPos = Math::Vector3::Zero;
			bool _hit = false;

			for (auto& ret : _result)
			{
				//レイを遮断し、オーバーした長さが一番長いものを探す
				if (_maxOverLap < ret.m_overlapDistance)
				{
					_maxOverLap = ret.m_overlapDistance;
					_hitPos = ret.m_hitPos;
					_hit = true;
				}
			}
			//何かしらの障害物に当たっている
			if (_hit)
			{
				//座標を補正
				Math::Vector3 _HoseiPos = _hitPos;
				_HoseiPos += _rayInfo.m_dir * 0.4f;
				SetPos(_HoseiPos);
			}
		}
	}

	CameraBase::Update();
}

void TPSCamera::UpdateRotateByMouse()
{
	//マウスでカメラの回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//実際にカメラを回転させる処理
	m_DegAng.x += _mouseMove.y * 0.15f;//縦
	m_DegAng.y += _mouseMove.x * 0.15f;//横

	//回転制御
	//m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}
