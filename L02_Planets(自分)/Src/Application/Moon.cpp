#include"Moon.h"

#include"Earth.h"

Moon::Moon()
{
	Init();
}

Moon::~Moon()
{
}

void Moon::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
	m_pos = { 1.5f,0.0f,0.0f };

	m_earth = std::make_shared<Earth>();
	m_earth->Init();
}

void Moon::Update()
{
	m_earth->Update();

	static float ang = 0;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(ang));
	ang += 0.3f;
	m_mWorld = rotMatY * transMat * rotMatY * m_earth->GetMatrix();
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
