#include "ITexture.h"
#include <utility>

using namespace irr;
using namespace video;

//! Check http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#pragma warning( disable: 4251 )


namespace irr
{
namespace video
{

    /**
     * This class allows to load and store a texture with different qualities at
     * the same time to easily change between them. This will avoid to manually
     * handle the same texture with various qualities.
     *
     * Keep in mind that even if you change the quality of the texture, you need
     * to apply it again calling the setMaterialTexture function for the node.
     */

    /**
     * Enum with the different qualities.
     */
enum E_QUALITY_TEXTURE {
	TEXTURE_HQ,
	TEXTURE_MQ,
	TEXTURE_LQ,
	TEXTURE_COUNT // Tricky, don't touch. We get the size of the enum.
};

class IRRLICHT_API IQualityTexture
{
private:
    //! Array with pairs of qualities and textures.
	std::pair<video::E_QUALITY_TEXTURE, ITexture*> textures[video::TEXTURE_COUNT];
    //! Default quality.
	E_QUALITY_TEXTURE tdefault;

public:
    /**
     * Constructor.
     */
	IQualityTexture();
    /**
     * Destructor.
     */
	~IQualityTexture();
    /**
     * Adds a new quality to the current wrapper.
     * \param quality The quality of the texture.
     * \param texture Pointer to the texture.
     */
	void addQuality(E_QUALITY_TEXTURE quality, ITexture* texture);
    /**
     * Removes a existent quality of the current wrapper. If there is no texture
     * assigned to this quality, nothing happens.
     * \param quality The quality of the texture.
     */
	void removeQuality(E_QUALITY_TEXTURE quality);
    /**
     * Changes the default quality of the wrapper. Medium by default.
     * \param quality The new quality.
     */
	void setDefaultQuality(E_QUALITY_TEXTURE quality);
    /**
     * Returns the actual default quality of the wrapper.
     */
	E_QUALITY_TEXTURE getDefaultQuality();
    /**
     * Increases by one the quality of the texture. Does nothing if it is
     * actually the highest.
     */
	E_QUALITY_TEXTURE increaseQuality();
    /**
     * Decreases by one the quality of the texture. Does nothing if it is
     * actually the lowest.
     */
	E_QUALITY_TEXTURE decreaseQuality();
    /**
     * Gets a concrete texture quality.
     */
	ITexture* getTexture(E_QUALITY_TEXTURE quality);
};
} //! end namespace video.
} //! end namespace irr.
