#pragma once

class Earth :public KdGameObject
{
public:
	Earth();
	~Earth();

	void Init()override;
	void Update()override;
	void DrawLit()override;

	//Math::Matrix& GetMatrix() const { return m_mWorld; }

private:

	std::shared_ptr<KdModelData>m_spModel = nullptr;

	Math::Vector3 m_pos;
};