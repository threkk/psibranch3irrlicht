#include "IQualityTexture.h"

IQualityTexture::IQualityTexture()
{
	for(unsigned i = 0; i < video::TEXTURE_COUNT; i++)
	{
		textures[i].first = (video::E_QUALITY_TEXTURE)i;
		textures[i].second = 0;
	}
	tdefault = video::TEXTURE_MQ;
}

IQualityTexture::~IQualityTexture()
{
	delete[] textures;
}

void IQualityTexture::addQuality(E_QUALITY_TEXTURE quality, ITexture* texture)
{
	textures[quality].second = texture;
}

void IQualityTexture::removeQuality(E_QUALITY_TEXTURE quality)
{
	textures[quality].second = 0;
}

void IQualityTexture::setDefaultQuality(E_QUALITY_TEXTURE quality)
{
	tdefault = quality;
}

E_QUALITY_TEXTURE IQualityTexture::getDefaultQuality()
{
	return tdefault;
}

E_QUALITY_TEXTURE IQualityTexture::increaseQuality()
{
	if(tdefault < video::TEXTURE_COUNT)
	{
		int quality = (int)tdefault + 1;
		tdefault = (E_QUALITY_TEXTURE)quality;
	}
	return tdefault;
}

E_QUALITY_TEXTURE IQualityTexture::decreaseQuality()
{
	if(tdefault > 0)
	{
		int quality = (int)tdefault - 1;
		tdefault = (E_QUALITY_TEXTURE)quality;
	}
	return tdefault;
}

ITexture* IQualityTexture::getTexture(E_QUALITY_TEXTURE quality)
{
	return textures[quality].second;
}