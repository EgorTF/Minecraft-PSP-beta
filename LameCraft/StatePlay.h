
#ifndef STATEPLAY_H_
#define STATEPLAY_H_

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <Aurora/Graphics/Effects/InventoryPlayer.h>
#include <Aurora/Graphics/Effects/SkyLight.h>
#include <Aurora/Graphics/Effects/SnowBall2.h>
#include <Aurora/Graphics/Effects/SkyBox.h>
#include <Aurora/Graphics/Effects/Destroyer.h>
#include <Aurora/Graphics/Effects/StarsBox.h>
#include <Aurora/Graphics/Effects/Drop.h>

#include "Zombie2.h"
#include "Cow2.h"
#include "LameMob.h"
#include "CraftWorld2.h"
#include "InputHelper.h"
#include "SoundManager.h"
#include "Chest2.h"
#include "Furnace2.h"

#include "LameFunctions.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


class StatePlay : public CGameState
{
public:
	StatePlay();
	virtual ~StatePlay();

	void Init();
	void InitParametric(bool makeTrees,bool makeWater,bool makeCaves,int seedIII, int terBuilderType, char gameMode);
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();
	void LoadTextures();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

	void LoadMap(std::string fileName,bool compressed);
	void SetWorldAndSaveName(std::string worldName,std::string fileName);
	void InitCamera();

	//keys helpers
	bool keyPressed(int currentKey);
	bool keyHold(int currentKey);
	void PutInInventory(int id, int num, bool st);

private:

	void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice);
	bool TryToMove(Vector3 moveVector,float dt);
	void SetDayTimeAfterLoad();
	void CraftItem2x2();
	void CraftItem3x3();

	void CheckForFurnFuel(Furnace* Fur);
	void CheckForFurnWorking(Furnace* Fur);
	void ReadyFurnSmelting(Furnace* Fur);

    int FindFurnaceId(int x, int y, int z);
	int FindChestId(int x, int y, int z);

	void HungerTime();
	void HealthTime();
	void OxygenTime();
	void HurtPlayer(float damage);

private:

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	InputHelper *mIhelper;
	Camera *fppCam;

	std::string saveFileName;
	int freeMemory;
	float freeMemoryTimer;

    float cloudsMove;
    bool cloudsWay;

	CraftWorld *mWorld;

    SkyLight *skyLight;
    SkyLight *skyMoonLight;
    SkyBox *skyBox;
    Destroyer *destroyer;
    StarsBox *starsBox;
    InventoryPlayer* invPlayer;

    bool cycle;
    bool loadReady;
	bool startDt;
    float dT;
    float dET;          // ����� �������
    char dStd;          // ������ �������� ���������� �����

    bool hurt;
    float hurt_time;
    float dtt;

    float furnaceTimes;

    Vector3 testPos1;
	Vector3 cubePos;

	bool showCube;

    short craftSlotId[4];
    short craftSlotAm[4];
    bool craftSlotSt[4];

    short craftSlotId3[9];
    short craftSlotAm3[9];
    bool craftSlotSt3[9];

    short craftItemId;
    short craftItemAm;
    bool craftItemSt;

    short craftItemId3;
    short craftItemAm3;
    bool craftItemSt3;

    float musicTimeGo;
    float musicTime;

    char chestId;
    char furnaceId;

    Chest* UseChest;
    Furnace* UseFurnace;
	//zmienne do poruszania
	float GRAVITY;
	float JUMPVELOCITY;
	float CLIMBVELOCITY;

	Vector3 playerVelocity;
	Vector3 playerPosition;
	Vector3 newPlayerPos;
	Vector3 oldPlayerPos;

	bool walkingOnGround;
	bool jumping;
	bool headInWater;
	bool footInWater;
	bool headInLava;
	bool footInLava;

	bool invEn;
	bool upEn;
	bool armorEn;
	bool craft3xEn;
	bool chestEn;
	bool furnaceEn;

    char barPosition;
    char invXPosition;
    char invYPosition;
    float invSteveAngle;

	int ram1;
	int ram2;

    float tickCave; //cave sounds timer
	float tickHunger;
	float tickHealth;
	float tickChunk;
	float tickOS;
	short chunks; // 0 - 7;

    int chunkId;

	Timer mTimer;
	float dt;

	//int texture[16];
	int barItems;
	int texture;
	int waterAnimation;

	char blue;
	char red;
	char black;
	char stars;

    int invPlayerTex;
    int zombieTex;
    int cowTex;
    int snowBall4;
	int cloudsTex;
	int suntex;
	int moontex;

	unsigned char currentTexture;
	unsigned char timeTexture;

	Sprite *waterScreen;

	Sprite *invSprite;
    Sprite *crtSprite;
    Sprite *chtSprite;
    Sprite *selectInvSprite;
	Sprite *barSprite;
	Sprite *crossSprite;
	Sprite *selectSprite;

	Sprite *furArrowSprite[11];
	Sprite *furFireSprite[5];
    Sprite *furSprite;

	Sprite *hpCellSprite;
	Sprite *hpCellSpriteW;
	Sprite *hpSprite;
	Sprite *hpHardSprite;
	Sprite *hpHalfSprite;
	Sprite *hpHardHalfSprite;

	Sprite *hgCellSprite;
	Sprite *hgSprite;
	Sprite *hgHalfSprite;
	Sprite *bubbleSprite;

    Sprite *arCellSprite;
	Sprite *arSprite;
	Sprite *arHalfSprite;

	Sprite *toolPointSprite[14];

	float hpAnim;

	float cameraSpeed;
	float cameraMoveSpeed;

	//menu sprites
	Sprite *buttonSprite;
	Sprite *sbuttonSprite;
	Sprite *nbuttonSprite;
	Sprite *moverSprite;

	bool menuOptions;
	char menuState;//0 game,1 menu
	char optionsMenuPos;
	char selectPos;

    char statisticsPage;

	//some settings
	bool canFly;
	bool devMode;
	bool analogLeft,analogRight,analogUp,analogDown;

	//for sound of walkinng
	float walkSoundAccu;
	bool  isWalking;

	//Headbob
	bool canHeadBob;
	float bobCycle;
	bool bobType;
	float cubeLight;

    float shift_x;
    float shift_y;
    float changeY;

    float animDest;
    float animSpeed;
    bool animGo;

    bool anim[3];
	bool makeScreen;
	bool dieFactor;

	float angleFactor;

    void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
    void DrawText2(int x,int y, unsigned int color, float size, const char *message, ...);

    void DrawAmount(int x,int y, int amount);

	std::vector<SnowBall2*> mSnowBalls;
};

#endif
