#pragma once

class Earth :public KdGameObject
{
public:
	Earth();
	~Earth();

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdModelData>m_spModel = nullptr;
};