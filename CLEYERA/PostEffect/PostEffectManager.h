#pragma once
#include"PostEffectData.h"

class PostEffectManager
{
public:

	static PostEffectManager* GetInstance();

	bool CheckData(const string& name);

	SPostEffectData GetData(const string& name);

	void SetData(const string& name, SPostEffectData data);

private:

	map<string, unique_ptr<PostEffectData >>data_;

	PostEffectManager()=default;
	~PostEffectManager()=default;

	PostEffectManager(const PostEffectManager&) = delete;
	const  PostEffectManager& operator=(const PostEffectManager&) = delete;

};

