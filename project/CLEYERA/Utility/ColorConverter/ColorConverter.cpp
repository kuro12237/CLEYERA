#include "ColorConverter.h"

Math::Vector::Vector4 ColorConverter::ColorConversion(uint32_t rgbaValue)
{
	Math::Vector::Vector4 result = {};
	result.x = ((rgbaValue >> 24) & 0xFF) / 255.0f; // Red
	result.y = ((rgbaValue >> 16) & 0xFF) / 255.0f; // Green
	result.z = ((rgbaValue >> 8) & 0xFF) / 255.0f;  // Blue
	result.w = (rgbaValue & 0xFF) / 255.0f;         // Alpha
	return result;
}
