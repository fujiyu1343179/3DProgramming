#include"Hamu.h"

Hamu::Hamu()
{
}

Hamu::~Hamu()
{
}

void Hamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");

	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	/*
	//ハムスターを前後に動かす処理
	m_hamuPos = { 0,0,5 };
	m_bFlg = true;
	*/
}

void Hamu::Update()
{
	/*
		//ダイレクトに書くと斜め移動が倍になってしまう
		if (GetAsyncKeyState('D')) { m_mHamuWorld._41 += 0.1f; }
		if (GetAsyncKeyState('A')) { m_mHamuWorld._41 -= 0.1f; }
		if (GetAsyncKeyState('S')) { m_mHamuWorld._43 -= 0.1f; }
		if (GetAsyncKeyState('W')) { m_mHamuWorld._43 += 0.1f; }
		*/

		//キャラクターの移動速度(マネしちゃダメ)
	float			moveSpd = 0.1f;
	Math::Vector3	nowPos = m_mWorld.Translation();

	//移動する方向ベクトル(矢印(大きさ、方向))
	Math::Vector3 moveVec = Math::Vector3::Zero;

	//float len = moveVec.Length();	長さ確認用

	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	//正規化(方向ベクトルは必ず長さが1.0で無ければダメ)
	moveVec.Normalize();	//強制的に1.0にする(伸ばしたり、短くする)

	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Hamu::DrawLit()
{
	//Math::Matrix _mat = Math::Matrix::CreateTranslation(0, 0, 0);
	//Math::Matrix _mat = Math::Matrix::Identity;
	//_mat._43 = 5;

	/*
		//ハムスターを前後に動かす処理
		if (m_bFlg)
		{
			m_hamuPos.z += 0.1f;
			if (m_hamuPos.z > 10)m_bFlg = false;
		}
		if (!m_bFlg)
		{
			m_hamuPos.z -= 0.1f;
			if (m_hamuPos.z < 3)m_bFlg = true;
		}
	*/

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
