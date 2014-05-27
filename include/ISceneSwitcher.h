#include "ISceneSeamlessLoader.h"

using namespace irr;
using namespace scene;

namespace irr
{
namespace scene
{
	typedef struct {
		NScene* nextScene;
		core::vector3df switchPosition;
		core::vector3df newPosition;
	} SScene;

	class IRRLICHT_API ISceneSwitcher
	{
	private:
		ISceneManager* smgr;
		std::vector<SScene>* switches;
		bool switchScene();

	public:
		ISceneSwitcher(ISceneManager* smgr);
		~ISceneSwitcher();
		int addSwitch(NScene* nextScene, 
			core::vector3df switchPosition, 
			core::vector3df newPosition);
		bool dropSwitch(int index);
		void update();
	};
}
}