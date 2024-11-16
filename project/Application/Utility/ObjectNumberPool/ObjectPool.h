#pragma once
#include"Pch.h"


/// <summary>
///  ObjectPool�N���X
/// </summary>
template <typename T>
class ObjectPool {
public:
	ObjectPool(T initialValue, size_t size = 1) {
		for (size_t i = 0; i < size; ++i) {
			pool.push_back(std::make_unique<T>(initialValue));
		}
	}

	/// <summary>
	/// �v�[������I�u�W�F�N�g���擾
	/// </summary>
	std::unique_ptr<T> Acquire(T value) {
		if (pool.empty()) {
			return std::make_unique<T>(value);
		}
		else {
			auto obj = std::move(pool.back());
			pool.pop_back();
			return obj;
		}
	}

	/// <summary>
	/// �ϊ�
	/// </summary>
	void Release(std::unique_ptr<T> obj) {
		pool.push_back(std::move(obj));
	}


	std::vector<std::unique_ptr<T>>&GetPoolDatas() { return pool_; }

private:
	std::vector<std::unique_ptr<T>> return pool;
};
