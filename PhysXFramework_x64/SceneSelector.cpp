#include "stdafx.h"
#include "SceneSelector.h"

#include "Assignment0Scene.h"
#include "Assignment1Scene.h"
#include "SceneManager.h"

//Change this define to activate/deactive the corresponding scenes
// W01 - W02  (#define ...)

#define W01
//#define W02

#ifdef W01
#include "TestScene.h"

#endif

#ifdef W02

#endif

namespace dae
{
	void AddScenes(SceneManager * pSceneManager)
	{

#ifdef W01
		pSceneManager->AddGameScene(new TestScene());
		pSceneManager->AddGameScene(new Assignment0Scene());
		pSceneManager->AddGameScene(new Assignment1Scene());
#endif

#ifdef W02

#endif

	}
}

