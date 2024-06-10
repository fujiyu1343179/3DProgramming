#include"Earth.h"

Earth::Earth()
{
	Init();
}

Earth::~Earth()
{
}

void Earth::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");
	m_pos = { 4.0f,0.0f,0.0f };
}

void Earth::Update()
{
	static float ang = 0;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(ang));
	ang += 0.5f;
	m_mWorld = rotMatY * transMat * rotMatY;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
