#include "ITexture.h"
#include <utility>

using namespace irr;
using namespace video;

// Check http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#pragma warning( disable: 4251 )


namespace irr
{
namespace video
{

enum E_QUALITY_TEXTURE {
	TEXTURE_HQ,
	TEXTURE_MQ,
	TEXTURE_LQ,
	TEXTURE_COUNT // Tricky, don't touch
};

class IRRLICHT_API IQualityTexture
{
private:
	std::pair<video::E_QUALITY_TEXTURE, ITexture*> textures[video::TEXTURE_COUNT];
	E_QUALITY_TEXTURE tdefault;

public:
	IQualityTexture();
	~IQualityTexture();
	void addQuality(E_QUALITY_TEXTURE quality, ITexture* texture);
	void removeQuality(E_QUALITY_TEXTURE quality);
	void setDefaultQuality(E_QUALITY_TEXTURE quality);
	E_QUALITY_TEXTURE getDefaultQuality();
	E_QUALITY_TEXTURE increaseQuality();
	E_QUALITY_TEXTURE decreaseQuality();
	ITexture* getTexture(E_QUALITY_TEXTURE quality);
};
}
}