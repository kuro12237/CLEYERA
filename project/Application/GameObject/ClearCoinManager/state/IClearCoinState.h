#pragma once

class ClearCoin;
class IClearCoinState
{
public:
	IClearCoinState() = default;
	virtual ~IClearCoinState() {};

	virtual void Initialize() = 0;

	virtual void Update(ClearCoin* state) = 0;

private:

};