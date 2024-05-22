#include"Sun.h"

Sun::Sun()
{
	Init();
}

Sun::~Sun()
{
}

void Sun::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
}

void Sun::Update()
{
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}
