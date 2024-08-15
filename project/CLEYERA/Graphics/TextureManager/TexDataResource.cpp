#include "TexDataResource.h"

TexDataResource::TexDataResource(string filePath, TexData texData)
{
	filePath_ = filePath;
	texData_ = texData;
}

TexDataResource::~TexDataResource()
{
	texData_.resource.Reset();
}
