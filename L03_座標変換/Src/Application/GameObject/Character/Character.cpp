#include "Character.h"

#include"../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	m_hamu.Load("Asset/Textures/Hamu.png");
}

void Character::Update()
{
	//右クリックしたら
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		//➀マウス位置の取得
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);//マウス座標補正	大事!!

		std::shared_ptr<KdCamera> camera = m_wpCamera.lock();
		if (camera)
		{
			//②レイの発射方向を求める(rayDir)
			Math::Vector3 camPos = camera->GetCameraMatrix().Translation();
			Math::Vector3 rayDir = Math::Vector3::Zero;
			float rayRange = 1000.f;
			camera->GenerateRayInfoFromClientPos(mousePos, camPos, rayDir, rayRange);
		
			//③レイの衝突位置を求める
			const std::shared_ptr<KdGameObject> spTerrain = m_wpTerrain.lock();
			if (spTerrain)
			{
				Math::Vector3 endRayPos = camPos + (rayDir * rayRange);
				KdCollider::RayInfo rayInfo(KdCollider::TypeGround, camPos, endRayPos);

				//実際の当たり判定処理
				std::list<KdCollider::CollisionResult> results;
				spTerrain->Intersects(rayInfo, &results);

				//結果が1つでも帰って来ていたら
				if (results.size())
				{
					for (KdCollider::CollisionResult result : results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
	}
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;//←移動しすぎる
	Math::Vector3 nowPos = GetPos();
	
	Math::Vector3 moveVec = m_TargetPos - nowPos;
	if (moveVec.Length() < moveSpd)
	{
		moveSpd = moveVec.Length();//キャラが震えるのを抑える
		//moveVec.LengthSquared()
		//↑平方根なし(Len>0)ゼロなのかをみたい時など
	}
	moveVec.Normalize();

	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	//座標変換( 3D -> 2D )
	Math::Vector3 resultPos = {};
	std::shared_ptr<KdCamera> camera = m_wpCamera.lock();
	if (camera)
	{
		camera->ConvertWorldToScreenDetail(GetPos(), resultPos);
		KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y, 10, &kRedColor);
		
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_hamu, resultPos.x, resultPos.y + 100);
	}

	//座標変換( 2D -> 3D )
	
}