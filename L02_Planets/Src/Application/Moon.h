#pragma once

class Moon :public KdGameObject
{
public:
	Moon();
	~Moon();

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdModelData>m_spModel = nullptr;
};