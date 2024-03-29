#ifndef STATEMENU_H_
#define STATEMENU_H_

#include <stdlib.h>

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/Utils/pgeZip.h>
#include <Aurora/Utils/pgeDir.h>
#include <Aurora/Utils/pge.h>

#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __PSP__
	#include <sys/stat.h>
#endif


#include "SoundManager.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class SaveFile
{
public:

	int saveVersion;
	bool compression;
	char worldGameMode;
	char worldName[50];
	bool locked;
	std::string fileName;
};

class TP
{
public:

	std::string name;
};

class StateMenu : public CGameState
{
public:
	StateMenu();
	virtual ~StateMenu();

	void Init();
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

private:

	void ScanSaveFiles(const char* dirName);
	void ScanTexturePacks(const char* dirName);
	void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);

private:

	Sprite *buttonSprite;
	Sprite *sbuttonSprite;

	Sprite *nbuttonSprite;
	Sprite *snbuttonSprite;

	Sprite *mbuttonSprite;
	Sprite *smbuttonSprite;

	Sprite *backSprite;
	Sprite *logoSprite;
	Sprite *lamecraftSprite;
	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;

    int SplashNumber;
    int seed_1;
	int selectPos;
	int loadSelectPos;
	int loadSavePos;
	int aboutPos;
	char worldName[32];

    float size_f;

	float fontcolor;
	bool fontcoloroption;

	bool saveSubmenu;
	int saveSubMenuSelect;

    pgeZip* theZip;

	int loadSaveStart;
	int loadSaveEnd;
	int loadSaveMax;

	short animationscreen;
	short menuState;//0 main,1 load,2 options

	int nextSaveFileNumber;
	std::string nextSaveFileName;

	std::vector<SaveFile> saveFilesList;
	std::vector<TP> texturePackList;
	std::string newWorldName;
	std::string newWorldSeed;
	std::string newWorldNamestr;
	//options for parametric map generation
	bool makeTrees;
	bool makeWater;
	bool makeCaves;
    int terrainBuilder;
	short gameMode;

    short generateSelectPose;

	//game version
	short currentVersion;

	int tpCurrent;
	int tpMax;
	int tpEnd;
	int tpStart;
	int tpPos;
	int tpSelectPos;
};

#endif
