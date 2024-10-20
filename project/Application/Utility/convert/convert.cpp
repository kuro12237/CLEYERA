#include "convert.h"

std::string FormatNumberWithDots(int num)
{
	if (num == 0)
	{
		return "";
	}

	std::ostringstream oss;
	oss << "." << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}
