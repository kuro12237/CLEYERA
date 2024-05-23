#pragma once

class SkyBox
{
public:

	void Initialize();

	void Update();

	void Draw();

private:
	//Singleton
	SkyBox() = default;
	~SkyBox() = default;
	SkyBox(const 	SkyBox&) = delete;
	const 	SkyBox& operator=(const 	SkyBox&) = delete;
};
