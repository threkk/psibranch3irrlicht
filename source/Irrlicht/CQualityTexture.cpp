#include "IQualityTexture.h"
#include <stdexcept>

//! Constructor
IQualityTexture::IQualityTexture(ITexture* texture)
{
	//! Initialize the array to avoid null pointers.
	for(unsigned i = 0; i < video::TEXTURE_COUNT; i++)
	{
		textures[i].first = (video::E_QUALITY_TEXTURE)i;
		textures[i].second = 0;
	}
	//! Medium quality by default.
	tdefault = video::TEXTURE_MQ;
	textures[video::TEXTURE_MQ].second = texture;
}

//! Destructor
IQualityTexture::~IQualityTexture()
{
	delete[] textures;
}

//! Add a new quality. The texture must be created in advance.
void IQualityTexture::addQuality(E_QUALITY_TEXTURE quality, ITexture* texture)
{
	textures[quality].second = texture;
}

//! Remove an existing quality. If it already doesn't exists, does nothing.
void IQualityTexture::removeQuality(E_QUALITY_TEXTURE quality)
{
	textures[quality].second = 0;
}

//! Set the chosen quality to default.
void IQualityTexture::setDefaultQuality(E_QUALITY_TEXTURE quality)
{
	if (textures[quality].second == 0)
	{
		throw std::invalid_argument("The quality chosen doesn't have a texture.");
	} else {
		tdefault = quality;
	}
}

//! Returns the actual quality.
E_QUALITY_TEXTURE IQualityTexture::getDefaultQuality()
{
	return tdefault;
}

//! Increases the quality. Nothing if no texture associated.
E_QUALITY_TEXTURE IQualityTexture::increaseQuality()
{
	if(tdefault < video::TEXTURE_COUNT)
	{
		int quality = (int)tdefault + 1;
		if(textures[quality].second != 0) 
		{
			tdefault = (E_QUALITY_TEXTURE)quality;
		}
	}
	return tdefault;
}

//! Decreases the quality. Nothing if no texture associated.
E_QUALITY_TEXTURE IQualityTexture::decreaseQuality()
{
	if(tdefault > 0)
	{
		int quality = (int)tdefault - 1;
		if(textures[quality].second != 0) 
		{
			tdefault = (E_QUALITY_TEXTURE)quality;
		}
	}
	return tdefault;
}

//! Gets the selected quality. Throws exception if there is no texture associated.
ITexture* IQualityTexture::getTexture(E_QUALITY_TEXTURE quality)
{
	ITexture* texture = textures[quality].second;
	if(texture == 0) 
	{
		throw std::invalid_argument("The quality chosen doesn't have a texture.");
	} else {
		return texture;
	}
}