#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//===================================================================
	// 乱数の実験場
	//===================================================================

	int randRes[10] = {};

	//如何にrand()が偏るか
	/*
	srand((unsigned)time(NULL));
	for (int i = 0; 1 < 100000000; i++)
	{
		//0～32767 % 10000(0～9999)
		int tmp = rand() % 10000;
		int idx = tmp / 1000;

		randRes[idx]++;
	}
	OutputDebugStringA("---------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数：\t" << randRes[i] << "\n";
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}	
	OutputDebugStringA("---------------------------------------------------------------\n");
	

	//==== メルセンヌツイスタ ====
	for (int i = 0; 1 < 100000000; i++)
	{
		int tmp = KdGetInt(0, 9999);
		int idx = tmp / 1000;

		randRes[idx]++;
	}
	OutputDebugStringA("---------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数：\t" << randRes[i] << "\n";
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("---------------------------------------------------------------\n");
	*/

	//レッスンその１：CカードとRカードをそれぞれ50％の確率で起動時に表示
	//レッスンその２：CカードとRカードをそれぞれ99.5％0.5％の確率で起動時に表示
	//レッスンその３：CカードとRカードとSRカードをそれぞれ 34% 33% 33% の確率で起動時に表示
	//レッスンその４：CカードとRカードとSRカードをそれぞれ 50% 49.5% 0.5% の確率で起動時に表示
	
	OutputDebugStringA("---------------------------------------------------------------\n");
	
	int bunbo = 1000;	//確率分母
	int randNum[3] = { 500,495,5 };//抽選値
	int ThusenNum = 10000000;
	int TosenNum[3] = { 0,0,0 };

	for (int i = 0; i < ThusenNum; i++)
	{
		int rnd = KdGetInt(0, bunbo - 1);

		for (int j = 0; j < std::size(randNum); j++)
		{
			rnd -= randNum[j];
			if (rnd < 0)
			{
				TosenNum[j]++;
				break;
			}
		}
	}

	float prob = 0;
	for (int i = 0; i < std::size(randNum); i++)
	{
		std::stringstream ss;
		prob = ((float)TosenNum[i] / (float)ThusenNum) * 100;
		round_n(prob, 3);

		switch (i)
		{
		case 0:
			ss << "Cカード当選回数" << TosenNum[0] << " " << "当選確率 = " << prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード当選回数" << TosenNum[1] << " " << "当選確率 = " << prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード当選回数" << TosenNum[1] << " " << "当選確率 = " << prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}

	/* レッスンその１
	if (rnd == 0)
	{
		ss << "CカードGET""\n";
	}
	else
	{
		ss << "RカードGET""\n";
	}
	std::string str = ss.str();
	OutputDebugStringA(str.c_str());
	*/

	OutputDebugStringA("---------------------------------------------------------------\n");

}

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}