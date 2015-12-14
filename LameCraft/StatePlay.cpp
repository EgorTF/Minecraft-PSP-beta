#include "StatePlay.h"
#include "TextureHelper.h"

#include "WorldGenerator.h"

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define TEXTURE_CHUNKS 8
#define SKY_MOVE 0.003f

// font vars
#define default_size 0.347
#define default_big_size 0.687

StatePlay::StatePlay()
{
    mRender = NULL;
    mSystemMgr = NULL;
    fppCam = NULL;
    UseChest = NULL;
    UseFurnace = NULL;

    statisticsPage = 0;

    freeMemory = 30;
    freeMemoryTimer = 0.0f;

    ram1 = 0;
    ram2 = 0;
    dt = 0.0f;

    showCube = true;

    GRAVITY = -6.8f;
    JUMPVELOCITY = 4.6f;
    CLIMBVELOCITY = 2.5f;

    walkingOnGround = false;
    jumping = false;
    headInWater = false;
    footInWater = false;
    headInLava = false;
    footInLava = false;
    invEn = false;
    craft3xEn = false;
    upEn = false;
    chestEn = false;
    furnaceEn = false;
    armorEn = false;

    cycle = 0;
    dtt = 0.0f;
    furnaceTimes = 0.0f;

    shift_x = 0.0f;
    shift_y = 0.0f;

    musicTimeGo = 0;

    chunkId = 0;
    chunks = 0;

    angleFactor = 0.0f;

    startDt = false;
    dET = 0;
    dT = 0;
    dStd = -1;

    testPos1.x = -1;
    testPos1.y = -1;
    testPos1.z = -1;

    barPosition = 0;
    invXPosition = 0;
    invYPosition = 0;

    craftItemId = -1;
    craftItemAm = -1;
    craftItemSt = 0;

    craftItemId3 = -1;
    craftItemAm3 = -1;
    craftItemSt3 = 0;

    chestId = -1;
    furnaceId = -1;

    cameraSpeed = 2.0f / 60.0f;
    cameraMoveSpeed = 0.0f;

    menuState = 0;
    selectPos = 0;

    cloudsMove = 0;
    cloudsWay = 0;

    devMode = false;
    makeScreen = false;

	canHeadBob = true;
	invSteveAngle = 0.0f;
	bobCycle = 0.0f;
	changeY = 0.0f;

	anim[0] = 0;
	anim[1] = 0;
	anim[2] = 0;

	hpAnim = 0.0f;

	canFly = false;

	for(int i = 0; i <= 3; i += 1)
    {
        craftSlotId[i] = -1;
        craftSlotAm[i] = -1;
        craftSlotSt[i] = 0;
    }

    for(int i = 0; i <= 8; i += 1)
    {
        craftSlotId3[i] = -1;
        craftSlotAm3[i] = -1;
        craftSlotSt3[i] = 0;
    }

    tickHunger = 0.0f;
    tickHealth = 0.0f;
    tickCave = 0.0f;
    tickChunk = 0.0f;
    tickOS = 0.0f;

    hurt = false;
    hurt_time = 0;
    musicTime = 1000;

    dieFactor = true;

    animDest = 0.0f;
    animSpeed = 17.0f;
    animGo = false;
    cubeLight = 0.0f;
}

StatePlay::~StatePlay()
{

}

void StatePlay::InitCamera()
{
    fppCam = new Camera();
    fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
    mRender->SetActiveCamera(fppCam);

    mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
    mWorld->rebuildVisibleChunks();
    mWorld->rebuildVisibleTransperentChunks();
}

void StatePlay::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    WorldGenerator *mGen = new WorldGenerator();

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(176, 112, 16);
    delete mGen;
    //mWorld->initRandompMap(128,16);
    mWorld->setTextureSize(256,16,64,16,256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(6);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();

    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,mWorld->groundHeight(64,64)+1.65,64.0f);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    dt = mTimer.GetDeltaTime();

    bobCycle = 3.14/2;
    cubeLight = 0.0f;

    LoadTextures();
    mWorld->GetTexturesIds();
    mWorld->buildblocksVerts();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;
    loadReady = false;
}

void StatePlay::InitParametric(bool makeTrees,bool makeWater,bool makeCaves,int seed_1,int terrainBuilder, char gameMode)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(176, 112, 16);
    mWorld->gameModeWorld = gameMode;

    WorldGenerator *mGen = new WorldGenerator();
    mGen->initRandompMap(176, 112, 16, mWorld, makeTrees, makeWater, makeCaves, seed_1, terrainBuilder);
    delete mGen;
    //mWorld->initRandompMap(128,16,terrainType,makeFlat,makeTrees,makeWater,makeCaves);
    mWorld->setTextureSize(256,16,64,16,256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(6);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();

    playerPosition = newPlayerPos = oldPlayerPos = Vector3(87.0f,mWorld->groundHeight(87,87)+1.65,87.0f);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    dt = mTimer.GetDeltaTime();

    LoadTextures();
    mWorld->GetTexturesIds();
    mWorld->buildblocksVerts();
    mWorld->buildcloudsVerts();
    mWorld->buildmobVerts();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    cubeLight = 0.0f;
    bobCycle = 3.14/2;
    loadReady = true;
}

void StatePlay::SetWorldAndSaveName(std::string worldName,std::string fileName)
{
    if(mWorld != NULL)
    {
        sprintf(mWorld->worldName,"%s",worldName.c_str());
    }
    saveFileName = fileName;
}

void StatePlay::LoadMap(std::string fileName,bool compressed)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //save name
    saveFileName = fileName;
    //
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,64,64);

    //then create our perfect world
    mWorld = new CraftWorld();

    if(compressed)
    {
        mWorld->LoadCompressedWorld(saveFileName);
        //set player pos from map
        playerPosition = mWorld->GetPlayerPos();
        newPlayerPos  = mWorld->GetPlayerPos();
        oldPlayerPos = mWorld->GetPlayerPos();
        mWorld->SetWolrdTime(mWorld->worldDayTime);
    }
    else
    {
        mWorld->LoadWorld(saveFileName.c_str());
        mWorld->SetWolrdTime(6);
    }

    mWorld->setTextureSize(256,16,64,16,256,16);
    mWorld->initWorldBlocksLight();
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    //Rebuild nearby world
    mWorld->rebuildChunk(curchunkTarget);
    mWorld->rebuildTransparentChunk(curchunkTarget);
    mWorld->rebuildNearestChunks(curchunkTarget,playerPosition);

    dt = mTimer.GetDeltaTime();

    //block sets info
    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one

    LoadTextures();
    mWorld->GetTexturesIds();
    mWorld->buildblocksVerts();
    mWorld->buildcloudsVerts();
    mWorld->buildmobVerts();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    SetDayTimeAfterLoad();

    mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
    mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
    mRender-> fovv = mWorld->mainOptions.fov;
    RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);

    loadReady = true;
}

void StatePlay::LoadTextures()
{
    //terrain texure
    texture = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain1);
    waterAnimation = TextureHelper::Instance()->GetTexture(TextureHelper::WaterAnimation);

    invPlayerTex = TextureHelper::Instance()->GetTexture(TextureHelper::Steve);
    cloudsTex = TextureHelper::Instance()->GetTexture(TextureHelper::clouds1);
    zombieTex = TextureHelper::Instance()->GetTexture(TextureHelper::Zombie3);
    cowTex = TextureHelper::Instance()->GetTexture(TextureHelper::cowTexture);

    blue = TextureHelper::Instance()->GetTexture(TextureHelper::Blue);
    red = TextureHelper::Instance()->GetTexture(TextureHelper::Red);
    black = TextureHelper::Instance()->GetTexture(TextureHelper::Black);

    snowBall4 = TextureHelper::Instance()->GetTexture(TextureHelper::SnowBall3);

    suntex = TextureHelper::Instance()->GetTexture(TextureHelper::Sun);
    moontex = TextureHelper::Instance()->GetTexture(TextureHelper::Moon);

    barItems = TextureHelper::Instance()->GetTexture(TextureHelper::Items1);

    waterScreen = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Blue));
    waterScreen->SetPosition(240,136);
    waterScreen->Scale(30,17);

    int utilsSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::Utils));

    barSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,0*utilsSize/182,182*utilsSize/182,22*utilsSize/182);
    barSprite->SetPosition(240,250);
    barSprite->Scale(364/utilsSize,364/utilsSize);

    selectSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,22*utilsSize/182,24*utilsSize/182,24*utilsSize/182);
    selectSprite->SetPosition(80,250);
    selectSprite->Scale(364/utilsSize,364/utilsSize);

    crossSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24*utilsSize/182,22*utilsSize/182,9*utilsSize/182,9*utilsSize/182);
    crossSprite->SetPosition(240,136);
    crossSprite->Scale(364/utilsSize,364/utilsSize);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,190,24);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,190,24);
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,48,190,24);
	nbuttonSprite->SetPosition(240,150);

	moverSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,120,12,24);

    invSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv));//200
    invSprite->SetPosition(240,136);
    invSprite->Scale(2,2);

    crtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crt));//200
    crtSprite->SetPosition(240,136);
    crtSprite->Scale(2,2);

    chtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cht));//200
    chtSprite->SetPosition(240,136);
    chtSprite->Scale(2,2);

    furSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::fur));//200
    furSprite->SetPosition(240,136);
    furSprite->Scale(2,2);

    for(int j = 13; j >= 0; j--)
    {
        toolPointSprite[j] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),169,49+(13-j)*2,13,2,true);//200
        toolPointSprite[j]->SetPosition(240,136);
        toolPointSprite[j]->Scale(2,2);
    }

    for(int j = 0; j <= 10; j++)
    {
        furArrowSprite[j] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furArrow),0,0,2+j*2,16,true);//200
        furArrowSprite[j]->SetPosition(240,136);
        furArrowSprite[j]->Scale(2,2);
    }

    furFireSprite[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,0,14,14,true);//200
    furFireSprite[4]->SetPosition(240,136);
    furFireSprite[4]->Scale(2,2);

    furFireSprite[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,3,14,11,true);//200
    furFireSprite[3]->SetPosition(240,136);
    furFireSprite[3]->Scale(2,2);

    furFireSprite[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,6,14,8,true);//200
    furFireSprite[2]->SetPosition(240,136);
    furFireSprite[2]->Scale(2,2);

    furFireSprite[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,9,14,5,true);//200
    furFireSprite[1]->SetPosition(240,136);
    furFireSprite[1]->Scale(2,2);

    furFireSprite[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,12,14,2,true);//200
    furFireSprite[0]->SetPosition(240,136);
    furFireSprite[0]->Scale(2,2);

    selectInvSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cursor));//200
    selectInvSprite->SetPosition(96,138);

    hpCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpCellSprite->SetPosition(100,21);
    hpCellSprite->Scale(364/utilsSize,364/utilsSize);

    hpCellSpriteW = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),30*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpCellSpriteW->SetPosition(100,21);
    hpCellSpriteW->Scale(364/utilsSize,364/utilsSize);

    hpSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),10*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpSprite->SetPosition(100,22);
    hpSprite->Scale(364/utilsSize,364/utilsSize);

    hpHardSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),40*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpHardSprite->SetPosition(100,22);
    hpHardSprite->Scale(364/utilsSize,364/utilsSize);

    hpHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),20*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpHalfSprite->SetPosition(100,22);
    hpHalfSprite->Scale(364/utilsSize,364/utilsSize);

    hpHardHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),50*utilsSize/182,66*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hpHardHalfSprite->SetPosition(100,22);
    hpHardHalfSprite->Scale(364/utilsSize,364/utilsSize);

    hgCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,56*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hgCellSprite->SetPosition(100,24);
    hgCellSprite->Scale(364/utilsSize,364/utilsSize);

    hgSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),10*utilsSize/182,56*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hgSprite->SetPosition(100,26);
    hgSprite->Scale(364/utilsSize,364/utilsSize);

    hgHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),20*utilsSize/182,56*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    hgHalfSprite->SetPosition(100,26);
    hgHalfSprite->Scale(364/utilsSize,364/utilsSize);

    bubbleSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,46*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    bubbleSprite->SetPosition(100,27);
    bubbleSprite->Scale(364/utilsSize,364/utilsSize);

    arCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),10*utilsSize/182,46*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    arCellSprite->SetPosition(100,27);
    arCellSprite->Scale(364/utilsSize,364/utilsSize);

    arSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),20*utilsSize/182,46*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    arSprite->SetPosition(100,27);
    arSprite->Scale(364/utilsSize,364/utilsSize);

    arHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),30*utilsSize/182,46*utilsSize/182,10*utilsSize/182,10*utilsSize/182);
    arHalfSprite->SetPosition(100,27);
    arHalfSprite->Scale(364/utilsSize,364/utilsSize);


    skyLight = new SkyLight();
    skyMoonLight = new SkyLight();
    skyBox = new SkyBox();
    destroyer = new Destroyer();
    starsBox = new StarsBox();
    invPlayer = new InventoryPlayer();
}



void StatePlay::SetDayTimeAfterLoad()
{

}

void StatePlay::Enter()
{
    RenderManager::InstancePtr()->SetPerspective(55.0f, 480.0f / 272.0f, 0.18f, 1000.0f);//1000
}

void StatePlay::CleanUp()
{
    if(mSnowBalls.empty() == false)
    {
        for(unsigned int i = 0; i < mSnowBalls.size(); i++)
        {
            delete mSnowBalls[i];
        }
        mSnowBalls.clear();
    }

    delete mRender->mCam;
    mRender->mCam = NULL;

    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete moverSprite;
    delete barSprite;
    delete selectSprite;
    delete crossSprite;
    delete invSprite;
    delete crtSprite;
    delete chtSprite;
    delete selectInvSprite;

    delete skyLight;
    delete skyMoonLight;
    delete skyBox;
    delete destroyer;
    delete starsBox;
    delete invPlayer;

    delete furSprite;
    delete waterScreen;

    for(unsigned int i = 0; i <= 4; i++)
    {
        delete furFireSprite[i];
    }

    for(unsigned int i = 0; i <= 7; i++)
    {
        delete furArrowSprite[i];
    }

    for(unsigned int i = 0; i <= 10; i++)
    {
        delete toolPointSprite[i];
    }

    delete hpCellSprite;
    delete hpSprite;
    delete hpHardSprite;
    delete hpHalfSprite;
    delete hpHardHalfSprite;
    delete hpCellSpriteW;

    delete hgCellSprite;
    delete hgSprite;
    delete hgHalfSprite;

    delete arSprite;
    delete arHalfSprite;
    delete arCellSprite;

    delete bubbleSprite;

    delete mWorld;
}

void StatePlay::Pause()
{

}

void StatePlay::Resume()
{

}

int StatePlay::FindChestId(int x, int y, int z)
{
    int o;
    int address;
    o = -1;
    address = x + y * 176 + z * 176 * 112;

    for(unsigned int i = 0; i < mWorld->mChests.size(); i++)
    {
        Chest* NewChest = mWorld->mChests[i];
        if(NewChest->chestAddress == address)
        {
            o = i;
            break;
        }
    }

    return o;
}

int StatePlay::FindFurnaceId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mWorld->mFurnaces.size(); i++)
    {
        Furnace* NewFurnace = mWorld->mFurnaces[i];
        if(NewFurnace->furnaceX == x && NewFurnace->furnaceY == y && NewFurnace->furnaceZ == z)
        {
            o = i;
            break;
        }
    }

    return o;
}

void StatePlay::CheckForFurnFuel(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(Fur->fuelTime <= 0 && furnItem != -1)
    {
        if(Fur->furnaceSlotId[1] == -1)
            return;

        bool used = false;

        switch(Fur->furnaceSlotId[1])
        {
        case 8:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 31:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 34:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 296:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 276:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 277:
            Fur->fuelTime = 80;
            used = true;
        break;
        case 292:
            Fur->fuelTime = 1000;
            used = true;
        break;
        case 306:
            Fur->fuelTime = 30;
            used = true;
        break;
        case 59:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 100:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 105:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 125:
            Fur->fuelTime = 15;
            used = true;
        break;
        }

        if(used == true)
        {
            Fur->furnaceSlotAm[1] -= 1;
            if(Fur->furnaceSlotAm[1] == 0)
            {
                Fur->furnaceSlotAm[1] = -1;
                Fur->furnaceSlotId[1] = -1;
                Fur->furnaceSlotSt[1] = 0;
            }
        }
    }
}

void StatePlay::CheckForFurnWorking(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->fuelTime > 0)
        {
            if(Fur->furnaceSlotId[2] == furnItem || Fur->furnaceSlotId[2] == -1)
            {
                if(Fur->furnaceSlotAm[2] <= 63)
                {
                    Fur->working = true;
                }
            }
            if(Fur->furnaceSlotId[2] != furnItem && Fur->furnaceSlotId[2] != -1)
            {
                Fur->working = false;
                Fur->meltingTime = 0;
            }
        }
        else
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
        if(Fur->fuelTime == 0)
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
    }
    else
    {
        Fur->working = false;
        Fur->meltingTime = 0;
    }
}

void StatePlay::ReadyFurnSmelting(Furnace* Fur)
{
    int furnItem;

    if(Fur->furnaceSlotId[0] < 250)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->furnaceSlotId[2] == furnItem)
        {
           Fur->furnaceSlotAm[2] += 1;
        }
        if(Fur->furnaceSlotId[2] == -1)
        {
            Fur->furnaceSlotId[2] = furnItem;
            Fur->furnaceSlotSt[2] = true;
            Fur->furnaceSlotAm[2] = 1;
        }

        Fur->furnaceSlotAm[0] -= 1;
        if(Fur->furnaceSlotAm[0] <= 0)
        {
            Fur->furnaceSlotId[0] = -1;
            Fur->furnaceSlotAm[0] = -1;
            Fur->furnaceSlotSt[0] = 0;
        }
    }
}

void StatePlay::CraftItem2x2()
{
    craftItemId = -1;
    craftItemAm = -1;
    craftItemSt = 0;

    int result = 0;
    for(int i = 0; i <= 3; i ++)
    {
        if(craftSlotId[i] != -1)
        {
            result += craftSlotId[i];
        }
    }

    switch(result)
    {
    // wood to planks
    case 8:
        if(craftSlotId[0] == 8 || craftSlotId[1] == 8 || craftSlotId[2] == 8 || craftSlotId[3] == 8)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    // bone to bone meals
    case 321:
        if(craftSlotId[0] == 321 || craftSlotId[1] == 321 || craftSlotId[2] == 321 || craftSlotId[3] == 321)
        {
            craftItemId = 322;
            craftItemSt = 1;
            craftItemAm = 3;
        }
    break;

    // snowballs to snow block
    case 1196:
        if(craftSlotId[0] == 299 && craftSlotId[1] == 299 && craftSlotId[2] == 299 && craftSlotId[3] == 299)
        {
            craftItemId = 29;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // birch wood to planks
    case 31:
        if(craftSlotId[0] == 31 || craftSlotId[1] == 31 || craftSlotId[2] == 31 || craftSlotId[3] == 31)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    // dark wood to planks
    case 30:
        if(craftSlotId[0] == 30 || craftSlotId[1] == 30 || craftSlotId[2] == 30 || craftSlotId[3] == 30)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    // melon to seeds
    case 311:
        if(craftSlotId[0] == 311 || craftSlotId[1] == 311 || craftSlotId[2] == 311 || craftSlotId[3] == 311)
        {
            craftItemId = 312;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // melon to seeds
    case 293:
        if(craftSlotId[0] == 293 || craftSlotId[1] == 293 || craftSlotId[2] == 293 || craftSlotId[3] == 293)
        {
            craftItemId = 313;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // diamond block to diamonds
    case 64:
        if(craftSlotId[0] == 64 || craftSlotId[1] == 64 || craftSlotId[2] == 64 || craftSlotId[3] == 64)
        {
            craftItemId = 279;
            craftItemSt = 1;
            craftItemAm = 9;
        }
    break;

    // iron block to bars
    case 66:
        if(craftSlotId[0] == 66 || craftSlotId[1] == 66 || craftSlotId[2] == 66 || craftSlotId[3] == 66)
        {
            craftItemId = 278;
            craftItemSt = 1;
            craftItemAm = 9;
        }
    break;

    // golden block to bard
    case 65:
        if(craftSlotId[0] == 65 || craftSlotId[1] == 65 || craftSlotId[2] == 65 || craftSlotId[3] == 65)
        {
            craftItemId = 280;
            craftItemSt = 1;
            craftItemAm = 9;
        }
    break;


    // bricks to brick block
    case 1156:
        if(craftSlotId[0] == 289 && craftSlotId[1] == 289 && craftSlotId[2] == 289 && craftSlotId[3] == 289)
        {
            craftItemId = 27;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // clay pieces to clay block
    case 1132:
        if(craftSlotId[0] == 283 && craftSlotId[1] == 283 && craftSlotId[2] == 283 && craftSlotId[3] == 283)
        {
            craftItemId = 99;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // sand blocks to sandstone
    case 28:
        if(craftSlotId[0] == 7 && craftSlotId[1] == 7 && craftSlotId[2] == 7 && craftSlotId[3] == 7)
        {
            craftItemId = 26;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // stones to stone bricks
    case 12:
        if(craftSlotId[0] == 3 && craftSlotId[1] == 3 && craftSlotId[2] == 3 && craftSlotId[3] == 3)
        {
            craftItemId = 102;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;


    // half to carved stone brick
    case 216:
        if((craftSlotId[0] == 108 && craftSlotId[2] == 108) || (craftSlotId[1] == 108 && craftSlotId[3] == 108))
        {
            craftItemId = 104;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;


    // planks to crafting table
    case 136:
        if(craftSlotId[0] == 34)
        {
            craftItemId = 105;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    // planks to sticks
    case 68:
        if((craftSlotId[0] == 34 && craftSlotId[2] == 34)  || (craftSlotId[1] == 34 && craftSlotId[3] == 34))
        {
            craftItemId = 276;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    // torch
    case 553:
        if((craftSlotId[0] == 277 && craftSlotId[2] == 276) || (craftSlotId[1] == 277 && craftSlotId[3] == 276))
        {
            craftItemId = 308;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 556: //scissors
        if((craftSlotId[2] == 278 && craftSlotId[1] == 278))
        {
            craftItemId = 275;
            craftItemSt = 0;
            craftItemAm = 239;
        }
    break;

    default:
        craftItemId = -1;
        craftItemAm = -1;
        craftItemSt = 0;
    break;

    }
}

void StatePlay::CraftItem3x3()
{
    craftItemId3 = -1;
    craftItemAm3 = -1;
    craftItemSt3 = 0;

    int result = 0;

    for(int i = 0; i <= 8; i ++)
    {
        if(craftSlotId3[i] != -1)
        {
            result += craftSlotId3[i];
        }
    }

    switch(result)
    {
    case 321://bone to bone meals
        if(craftSlotId3[0] == 321 || craftSlotId3[1] == 321 || craftSlotId3[2] == 321 || craftSlotId3[3] == 321 || craftSlotId3[4] == 321 || craftSlotId3[5] == 321 || craftSlotId3[6] == 321 || craftSlotId3[7] == 321 || craftSlotId3[8] == 321)
        {
            craftItemId3 = 322;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 8: //wood to planks
        if(craftSlotId3[0] == 8 || craftSlotId3[1] == 8 || craftSlotId3[2] == 8 || craftSlotId3[3] == 8 || craftSlotId3[4] == 8 || craftSlotId3[5] == 8 || craftSlotId3[6] == 8 || craftSlotId3[7] == 8 || craftSlotId3[8] == 8)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 31://wood to planks
        if(craftSlotId3[0] == 31 || craftSlotId3[1] == 31 || craftSlotId3[2] == 31 || craftSlotId3[3] == 31 || craftSlotId3[4] == 31 || craftSlotId3[5] == 31 || craftSlotId3[6] == 31 || craftSlotId3[7] == 31 || craftSlotId3[8] == 31)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 30://wood to planks
        if(craftSlotId3[0] == 30 || craftSlotId3[1] == 30 || craftSlotId3[2] == 30 || craftSlotId3[3] == 30 || craftSlotId3[4] == 30 || craftSlotId3[5] == 30 || craftSlotId3[6] == 30 || craftSlotId3[7] == 30 || craftSlotId3[8] == 30)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 311://melon to seeds
        if(craftSlotId3[0] == 311 || craftSlotId3[1] == 311 || craftSlotId3[2] == 311 || craftSlotId3[3] == 311 || craftSlotId3[4] == 311 || craftSlotId3[5] == 311 || craftSlotId3[6] == 311 || craftSlotId3[7] == 311 || craftSlotId3[8] == 311)
        {
            craftItemId3 = 312;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 293://cane to sugar
        if(craftSlotId3[0] == 293 || craftSlotId3[1] == 293 || craftSlotId3[2] == 293 || craftSlotId3[3] == 293 || craftSlotId3[4] == 293 || craftSlotId3[5] == 293 || craftSlotId3[6] == 293 || craftSlotId3[7] == 293 || craftSlotId3[8] == 293)
        {
            craftItemId3 = 313;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 68://sticks
        if( (craftSlotId3[0] == 34 && craftSlotId3[3] == 34)  || (craftSlotId3[1] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[2] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[6] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[5] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 276;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 1656: //fence
        if((craftSlotId3[0] == 276 && craftSlotId3[1] == 276 && craftSlotId3[2] == 276 && craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276) || (craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276 && craftSlotId3[6] == 276 && craftSlotId3[7] == 276 && craftSlotId3[8] == 276))
        {
            craftItemId3 = 59;
            craftItemSt3 = 1;
            craftItemAm3 = 2;
        }
    break;

    case 204: //door
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 306;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
        //wooden stair
        if((craftSlotId3[0] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 125;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 216://stone stair
        if((craftSlotId3[0] == 36 && craftSlotId3[3] == 36 && craftSlotId3[4] == 36 && craftSlotId3[6] == 36 && craftSlotId3[7] == 36 && craftSlotId3[8] == 36))
        {
            craftItemId3 = 60;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
        if((craftSlotId3[0] == 108 && craftSlotId3[3] == 108) || (craftSlotId3[1] == 108 && craftSlotId3[4] == 108) || (craftSlotId3[2] == 108 && craftSlotId3[5] == 108) || (craftSlotId3[3] == 108 && craftSlotId3[6] == 108) || (craftSlotId3[4] == 108 && craftSlotId3[7] == 108) || (craftSlotId3[5] == 108 && craftSlotId3[8] == 108))
        {
            craftItemId3 = 104;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 162://brick stair
        if((craftSlotId3[0] == 27 && craftSlotId3[3] == 27 && craftSlotId3[4] == 27 && craftSlotId3[6] == 27 && craftSlotId3[7] == 27 && craftSlotId3[8] == 27))
        {
            craftItemId3 = 67;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 136://crafting
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 105;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1196://snow block
        if((craftSlotId3[0] == 299 && craftSlotId3[1] == 299 && craftSlotId3[3] == 299 && craftSlotId3[4] == 299) || (craftSlotId3[1] == 299 && craftSlotId3[2] == 299 && craftSlotId3[4] == 299 && craftSlotId3[5] == 299) || (craftSlotId3[3] == 299 && craftSlotId3[4] == 299 && craftSlotId3[6] == 299 && craftSlotId3[7] == 299) || (craftSlotId3[4] == 299 && craftSlotId3[5] == 299 && craftSlotId3[7] == 299 && craftSlotId3[8] == 299))
        {
            craftItemId3 = 29;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 28: //stonesand from sand
        if((craftSlotId3[0] == 28 && craftSlotId3[1] == 28 && craftSlotId3[3] == 28 && craftSlotId3[4] == 28) || (craftSlotId3[1] == 28 && craftSlotId3[2] == 28 && craftSlotId3[4] == 28 && craftSlotId3[5] == 28) || (craftSlotId3[3] == 28 && craftSlotId3[4] == 28 && craftSlotId3[6] == 28 && craftSlotId3[7] == 28) || (craftSlotId3[4] == 28 && craftSlotId3[5] == 28 && craftSlotId3[7] == 28 && craftSlotId3[8] == 28))
        {
            craftItemId3 = 26;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1156: //brick block
        if((craftSlotId3[0] == 289 && craftSlotId3[1] == 289 && craftSlotId3[3] == 289 && craftSlotId3[4] == 289) || (craftSlotId3[1] == 289 && craftSlotId3[2] == 289 && craftSlotId3[4] == 289 && craftSlotId3[5] == 289) || (craftSlotId3[3] == 289 && craftSlotId3[4] == 289 && craftSlotId3[6] == 289 && craftSlotId3[7] == 289) || (craftSlotId3[4] == 289 && craftSlotId3[5] == 289 && craftSlotId3[7] == 289 && craftSlotId3[8] == 289))
        {
            craftItemId3 = 27;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 12: //stonebricks
        if((craftSlotId3[0] == 3 && craftSlotId3[1] == 3 && craftSlotId3[3] == 3 && craftSlotId3[4] == 3) || (craftSlotId3[1] == 3 && craftSlotId3[2] == 3 && craftSlotId3[4] == 3 && craftSlotId3[5] == 3) || (craftSlotId3[3] == 3 && craftSlotId3[4] == 3 && craftSlotId3[6] == 3 && craftSlotId3[7] == 3) || (craftSlotId3[4] == 3 && craftSlotId3[5] == 3 && craftSlotId3[7] == 3 && craftSlotId3[8] == 3))
        {
            craftItemId3 = 102;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 553://torches
        if((craftSlotId3[0] == 277 && craftSlotId3[3] == 276) || (craftSlotId3[1] == 277 && craftSlotId3[4] == 276) || (craftSlotId3[2] == 277 && craftSlotId3[5] == 276) || (craftSlotId3[3] == 277 && craftSlotId3[6] == 276) || (craftSlotId3[4] == 277 && craftSlotId3[7] == 276) || (craftSlotId3[5] == 277 && craftSlotId3[8] == 276))
        {
            craftItemId3 = 308;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;


    case 556://scissors
        if((craftSlotId3[1] == 278 && craftSlotId3[3] == 278) || (craftSlotId3[2] == 278 && craftSlotId3[4] == 278) || (craftSlotId3[4] == 278 && craftSlotId3[6] == 278) || (craftSlotId3[5] == 278 && craftSlotId3[7] == 278))
        {
            craftItemId3 = 275;
            craftItemSt3 = 0;
            craftItemAm3 = 239;
        }
    break;

    case 1132://clay
        if((craftSlotId3[0] == 283 && craftSlotId3[1] == 283 && craftSlotId3[3] == 283 && craftSlotId3[4] == 283) || (craftSlotId3[1] == 283 && craftSlotId3[2] == 283 && craftSlotId3[4] == 283 && craftSlotId3[5] == 283) || (craftSlotId3[3] == 283 && craftSlotId3[4] == 283 && craftSlotId3[6] == 283 && craftSlotId3[7] == 283) || (craftSlotId3[4] == 283 && craftSlotId3[5] == 283 && craftSlotId3[7] == 283 && craftSlotId3[8] == 283))
        {
            craftItemId3 = 99;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    /// HALF BLOCKS
    case 108://cobblestone
        if((craftSlotId3[0] == 36 && craftSlotId3[1] == 36 && craftSlotId3[2] == 36) || (craftSlotId3[3] == 36 && craftSlotId3[4] == 36 && craftSlotId3[5] == 36) || (craftSlotId3[6] == 36 && craftSlotId3[7] == 36 && craftSlotId3[8] == 36))
        {
            craftItemId3 = 83;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 102://half planks
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[2] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 82;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
        //4 bowls
        if((craftSlotId3[0] == 34 && craftSlotId3[4] == 34 && craftSlotId3[2] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[7] == 34 && craftSlotId3[5] == 34))
        {
            craftItemId3 = 302;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 9://stone
        if((craftSlotId3[0] == 3 && craftSlotId3[1] == 3 && craftSlotId3[2] == 3) || (craftSlotId3[3] == 3 && craftSlotId3[4] == 3 && craftSlotId3[5] == 3) || (craftSlotId3[6] == 3 && craftSlotId3[7] == 3 && craftSlotId3[8] == 3))
        {
            craftItemId3 = 85;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 78://stonesand half block
        if((craftSlotId3[0] == 26 && craftSlotId3[1] == 26 && craftSlotId3[2] == 26) || (craftSlotId3[3] == 26 && craftSlotId3[4] == 26 && craftSlotId3[5] == 26) || (craftSlotId3[6] == 26 && craftSlotId3[7] == 26 && craftSlotId3[8] == 26))
        {
            craftItemId3 = 86;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 306: //stonesand half block
        if((craftSlotId3[0] == 102 && craftSlotId3[1] == 102 && craftSlotId3[2] == 102) || (craftSlotId3[3] == 102 && craftSlotId3[4] == 102 && craftSlotId3[5] == 102) || (craftSlotId3[6] == 102 && craftSlotId3[7] == 102 && craftSlotId3[8] == 102))
        {
            craftItemId3 = 108;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;


    // end
    case 903://mooshroom bowl
        if((craftSlotId3[1] == 300 && craftSlotId3[4] == 301 && craftSlotId3[7] == 302) || (craftSlotId3[1] == 301 && craftSlotId3[4] == 300 && craftSlotId3[7] == 302))
        {
            craftItemId3 = 303;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
    break;

    /// Tool crafts start
    //wooden tools
    case 654:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34 && craftSlotId3[2] == 34) // pick
        {
            craftItemId3 = 250;
            craftItemSt3 = 0;
            craftItemAm3 = 60;

        }
        if(craftSlotId3[0] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34) // axe
        {
            craftItemId3 = 265;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
    break;

    case 620:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34) // hoe
        {
            craftItemId3 = 270;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
    break;

    case 586:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276) // shovel
        {
            craftItemId3 = 260;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
    break;

    case 344:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 34 && craftSlotId3[7] == 276) // sword
        {
            craftItemId3 = 255;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
    break;

    //stone tools
    case 660:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36 && craftSlotId3[2] == 36)
        {
            craftItemId3 = 251;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        if(craftSlotId3[0] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 36 && craftSlotId3[3] == 36)
        {
            craftItemId3 = 266;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        break;

    case 624:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36)
        {
            craftItemId3 = 271;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
    break;

    case 588:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 261;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
    break;

    case 348:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 36 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 256;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
    break;

    //iron tools
    case 1386:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278 && craftSlotId3[2] == 278)
        {
            craftItemId3 = 252;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
        if(craftSlotId3[0] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 278 && craftSlotId3[3] == 278)
        {
            craftItemId3 = 267;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
    break;

    case 1108:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278)
        {
            craftItemId3 = 272;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
    break;

    case 830:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 262;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
    break;

    case 832:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 278 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 257;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
        if(craftSlotId3[1] == 280 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 264;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }
    break;

    //diamond tools
    case 1389:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279 && craftSlotId3[2] == 279)
        {
            craftItemId3 = 253;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        if(craftSlotId3[0] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 279 && craftSlotId3[3] == 279)
        {
            craftItemId3 = 268;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        break;

    case 1110:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279)
        {
            craftItemId3 = 273;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }
    break;

    case 831:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 263;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }
    break;

    case 834:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 279 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 258;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }

        if((craftSlotId3[0] == 278 && craftSlotId3[4] == 278 && craftSlotId3[2] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[7] == 278 && craftSlotId3[5] == 278))
        {
            craftItemId3 = 290;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
    break;

    //golden tools
    case 1392:
        if(craftSlotId3[1] == 280 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 280 && craftSlotId3[2] == 280)
        {
            craftItemId3 = 254;
            craftItemSt3 = 0;
            craftItemAm3 = 33;

        }
        if(craftSlotId3[0] == 280 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 280 && craftSlotId3[3] == 280)
        {
            craftItemId3 = 269;
            craftItemSt3 = 0;
            craftItemAm3 = 33;

        }
        break;

    case 1112:
        if(craftSlotId3[1] == 280 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 280)
        {
            craftItemId3 = 274;
            craftItemSt3 = 0;
            craftItemAm3 = 33;
        }

        if((craftSlotId3[0] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[5] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[8] == 278))
        {
            craftItemId3 = 339;
            craftItemAm3 = 195;
            craftItemSt3 = false;
        }
    break;

    case 836:
        if(craftSlotId3[1] == 280 && craftSlotId3[4] == 280 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 259;
            craftItemSt3 = 0;
            craftItemAm3 = 33;
        }
    break;
    /// Tool crafts end

    /// Armor crafts begin
    // leather

    // helmet
    case 1615:
        if((craftSlotId3[0] == 323 && craftSlotId3[1] == 323 && craftSlotId3[2] == 323 && craftSlotId3[3] == 323 && craftSlotId3[5] == 323) || (craftSlotId3[3] == 323 && craftSlotId3[4] == 323 && craftSlotId3[5] == 323 && craftSlotId3[6] == 323 && craftSlotId3[8] == 323))
        {
            craftItemId3 = 328;
            craftItemAm3 = 55;
            craftItemSt3 = false;
        }
    break;

    // chestplate
    case 2584:
        if(craftSlotId3[0] == 323 && craftSlotId3[2] == 323 && craftSlotId3[3] == 323 && craftSlotId3[4] == 323 && craftSlotId3[5] == 323 && craftSlotId3[6] == 323 && craftSlotId3[7] == 323 && craftSlotId3[8] == 323)
        {
            craftItemId3 = 329;
            craftItemAm3 = 80;
            craftItemSt3 = false;
        }
    break;

    // leggings
    case 2261:
        if(craftSlotId3[0] == 323 && craftSlotId3[1] == 323 && craftSlotId3[2] == 323 && craftSlotId3[3] == 323 && craftSlotId3[5] == 323 && craftSlotId3[6] == 323 && craftSlotId3[8] == 323)
        {
            craftItemId3 = 330;
            craftItemAm3 = 75;
            craftItemSt3 = false;
        }
    break;

    // boots
    case 1292:
        if((craftSlotId3[0] == 323 && craftSlotId3[2] == 323 && craftSlotId3[3] == 323 && craftSlotId3[5] == 323) || (craftSlotId3[3] == 323 && craftSlotId3[5] == 323 && craftSlotId3[6] == 323 && craftSlotId3[8] == 323))
        {
            craftItemId3 = 331;
            craftItemAm3 = 65;
            craftItemSt3 = false;
        }
    break;

    // end

    // iron

    // helmet
    case 1390:
        if((craftSlotId3[0] == 278 && craftSlotId3[1] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[5] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[4] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[8] == 278))
        {
            craftItemId3 = 336;
            craftItemAm3 = 165;
            craftItemSt3 = false;
        }
    break;

    // chestplate
    case 2224:
        if(craftSlotId3[0] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[4] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[7] == 278 && craftSlotId3[8] == 278)
        {
            craftItemId3 = 337;
            craftItemAm3 = 240;
            craftItemSt3 = false;
        }
    break;

    // leggings
    case 1946:
        if(craftSlotId3[0] == 278 && craftSlotId3[1] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[8] == 278)
        {
            craftItemId3 = 338;
            craftItemAm3 = 225;
            craftItemSt3 = false;
        }
    break;


    // end

    // diamond

    // helmet
    case 1395:
        if((craftSlotId3[0] == 279 && craftSlotId3[1] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[5] == 279) || (craftSlotId3[3] == 279 && craftSlotId3[4] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[8] == 279))
        {
            craftItemId3 = 340;
            craftItemAm3 = 363;
            craftItemSt3 = false;
        }
    break;

    // chestplate
    case 2232:
        if(craftSlotId3[0] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[4] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[7] == 279 && craftSlotId3[8] == 279)
        {
            craftItemId3 = 341;
            craftItemAm3 = 528;
            craftItemSt3 = false;
        }
    break;

    // leggings
    case 1953:
        if(craftSlotId3[0] == 279 && craftSlotId3[1] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[8] == 279)
        {
            craftItemId3 = 342;
            craftItemAm3 = 495;
            craftItemSt3 = false;
        }
    break;

    // boots
    case 1116:
        if((craftSlotId3[0] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[5] == 279) || (craftSlotId3[3] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[8] == 279))
        {
            craftItemId3 = 343;
            craftItemAm3 = 429;
            craftItemSt3 = false;
        }
    break;

    // end


    // golden

    // helmet
    case 1400:
        if((craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[5] == 280) || (craftSlotId3[3] == 280 && craftSlotId3[4] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[8] == 280))
        {
            craftItemId3 = 344;
            craftItemAm3 = 77;
            craftItemSt3 = false;
        }
    break;

    // chestplate
    case 2240:
        if(craftSlotId3[0] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 345;
            craftItemAm3 = 112;
            craftItemSt3 = false;
        }
    break;

    // leggings
    case 1960:
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 346;
            craftItemAm3 = 105;
            craftItemSt3 = false;
        }
    break;

    // boots
    case 1120:
        if((craftSlotId3[0] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[5] == 280) || (craftSlotId3[3] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[8] == 280))
        {
            craftItemId3 = 347;
            craftItemAm3 = 91;
            craftItemSt3 = false;
        }
    break;

    // end
    /// Armor crafts end

    case 2799: //melon block
        if(craftSlotId3[0] == 311 && craftSlotId3[1] == 311 && craftSlotId3[2] == 311 && craftSlotId3[3] == 311 && craftSlotId3[4] == 311 && craftSlotId3[5] == 311 && craftSlotId3[6] == 311 && craftSlotId3[7] == 311 && craftSlotId3[8] == 311)
        {
            craftItemId3 = 81;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;


    case 2862: //lapis block
        if(craftSlotId3[0] == 318 && craftSlotId3[1] == 318 && craftSlotId3[2] == 318 && craftSlotId3[3] == 318 && craftSlotId3[4] == 318 && craftSlotId3[5] == 318 && craftSlotId3[6] == 318 && craftSlotId3[7] == 318 && craftSlotId3[8] == 318)
        {
            craftItemId3 = 101;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;


    case 101: //lapis block to items
        if(craftSlotId3[0] == 101 || craftSlotId3[1] == 101 || craftSlotId3[2] == 101 && craftSlotId3[3] == 101 || craftSlotId3[4] == 101 || craftSlotId3[5] == 101 || craftSlotId3[6] == 101 && craftSlotId3[7] == 101 || craftSlotId3[8] == 101)
        {
            craftItemId3 = 318;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2502: //iron block
        if(craftSlotId3[0] == 278 && craftSlotId3[1] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[4] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[7] == 278 && craftSlotId3[8] == 278)
        {
            craftItemId3 = 66;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;


    case 66: //iron block to bars
        if(craftSlotId3[0] == 66 || craftSlotId3[1] == 66 || craftSlotId3[2] == 66 && craftSlotId3[3] == 66 || craftSlotId3[4] == 66 || craftSlotId3[5] == 66 || craftSlotId3[6] == 66 && craftSlotId3[7] == 66 || craftSlotId3[8] == 66)
        {
            craftItemId3 = 278;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2520: //gold block
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 65;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 65: //gold block to bars
        if(craftSlotId3[0] == 65 || craftSlotId3[1] == 65 || craftSlotId3[2] == 65 && craftSlotId3[3] == 65 || craftSlotId3[4] == 65 || craftSlotId3[5] == 65 || craftSlotId3[6] == 65 && craftSlotId3[7] == 65 || craftSlotId3[8] == 65)
        {
            craftItemId3 = 280;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2511: //diamond block
        if(craftSlotId3[0] == 279 && craftSlotId3[1] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[4] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[7] == 279 && craftSlotId3[8] == 279)
        {
            craftItemId3 = 64;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 64: //diamond block to diamonds
        if(craftSlotId3[0] == 64 || craftSlotId3[1] == 64 || craftSlotId3[2] == 64 && craftSlotId3[3] == 64 || craftSlotId3[4] == 64 || craftSlotId3[5] == 64 || craftSlotId3[6] == 64 && craftSlotId3[7] == 64 || craftSlotId3[8] == 64)
        {
            craftItemId3 = 279;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 1932: //ladder
        if(craftSlotId3[0] == 276 && craftSlotId3[2] == 276 && craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276 && craftSlotId3[6] == 276 && craftSlotId3[8] == 276)
        {
            craftItemId3 = 307;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 272: //chest
        if(craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[3] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[0] == 34 && craftSlotId3[6] == 34 && craftSlotId3[8] == 34)
        {
            craftItemId3 = 94;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 288: //furnace
        if(craftSlotId3[1] == 36 && craftSlotId3[2] == 36 && craftSlotId3[3] == 36 && craftSlotId3[5] == 36 && craftSlotId3[7] == 36 && craftSlotId3[0] == 36 && craftSlotId3[6] == 36 && craftSlotId3[8] == 36)
        {
            craftItemId3 = 106;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 861: //bread
        if((craftSlotId3[0] == 287 && craftSlotId3[1] == 287 && craftSlotId3[2] == 287) || (craftSlotId3[3] == 287 && craftSlotId3[4] == 287 && craftSlotId3[5] == 287) || (craftSlotId3[6] == 287 && craftSlotId3[7] == 287 && craftSlotId3[8] == 287))
        {
            craftItemId3 = 288;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 888: //cookies
        if((craftSlotId3[0] == 287 && craftSlotId3[1] == 314 && craftSlotId3[2] == 287) || (craftSlotId3[3] == 287 && craftSlotId3[4] == 314 && craftSlotId3[5] == 287) || (craftSlotId3[6] == 287 && craftSlotId3[7] == 314 && craftSlotId3[8] == 287))
        {
            craftItemId3 = 315;
            craftItemSt3 = 1;
            craftItemAm3 = 8;
        }
    break;

    case 2524: //golden apple
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 284 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 285;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 879: //paper
        if((craftSlotId3[0] == 293 && craftSlotId3[1] == 293 && craftSlotId3[2] == 293) || (craftSlotId3[3] == 293 && craftSlotId3[4] == 293 && craftSlotId3[5] == 293) || (craftSlotId3[6] == 293 && craftSlotId3[7] == 293 && craftSlotId3[8] == 293))
        {
            craftItemId3 = 297;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 891: //book
        if((craftSlotId3[0] == 297 && craftSlotId3[3] == 297 && craftSlotId3[6] == 297) || (craftSlotId3[1] == 297 && craftSlotId3[4] == 297 && craftSlotId3[7] == 297) || (craftSlotId3[2] == 297 && craftSlotId3[5] == 297 && craftSlotId3[8] == 297))
        {
            craftItemId3 = 298;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1098: //book shelf
        if(craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[3] == 298 && craftSlotId3[4] == 298 && craftSlotId3[5] == 298 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34)
        {
            craftItemId3 = 35;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 846: //watering can
        if(craftSlotId3[8] == 290 && craftSlotId3[4] == 278 && craftSlotId3[0] == 278)
        {
            craftItemId3 = 304;
            craftItemSt3 = 0;
            craftItemAm3 = 0;
        }
    break;

    default:
        craftItemId3 = -1;
        craftItemAm3 = -1;
        craftItemSt3 = 0;
    break;

    }
}

void StatePlay::HandleEvents(StateManager* sManager)
{
    //update delta time
    dt = mTimer.GetDeltaTime();

    cameraSpeed = 2.0f * dt;
    cameraMoveSpeed = 4.0f * dt;

    //free memory counter
    freeMemoryTimer += dt;
    if(menuState != 0)
    {
        if(freeMemoryTimer > 3.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }
    else
    {
        if(freeMemoryTimer > 15.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }

    //update input
    mSystemMgr->InputUpdate();

    if(mWorld->HP > 0)
    {
        if(menuState == 0)//game state
        {
            if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false)
            {
                if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
                {
                    if (mWorld->invId[27+barPosition] != -1)
                    {
                        changeY = -0.16f;
                        anim[0] = 1;
                    }
                    barPosition != 8 ? barPosition ++ : barPosition = 0;

                    selectSprite->SetPosition(80 + (barPosition * 40),250);
                    startDt = 0;
                    dT = 0;
                    dET = 0;
                    dStd = -1;
                    //mWorld->SpawnZombie(80.0f,80.0f,80.0f);
                }

                //switch right
                if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
                {
                    if (mWorld->invId[27+barPosition] != -1)
                    {
                        changeY = -0.16f;
                        anim[0] = 1;
                    }
                    barPosition != 0 ? barPosition -- : barPosition = 8;

                    selectSprite->SetPosition(80 + (barPosition * 40),250);
                    startDt = 0;
                    dT = 0;
                    dET = 0;
                    dStd = -1;
                }

                // drop 1 item
                if(keyPressed(InputHelper::Instance()->getButtonToAction(10)))
                {
                    if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
                    {
                        if(mWorld->invId[27+barPosition] > 0)
                        {
                            Vector3 dropVelocity = Vector3(0,0,0);


                            dropVelocity.x = (cosf((fppCam->horAngle/180.0f)*PI))*4.0f;
                            dropVelocity.y = 2.0f;
                            dropVelocity.z = (sinf((fppCam->horAngle/180.0f)*PI))*4.0f;

                            if(mWorld->invSt[27+barPosition] == true)
                            {
                                if(mWorld->invAm[27+barPosition] > 0)
                                {
                                    mWorld->invAm[27+barPosition] -= 1;
                                    mWorld->DropThisNoAlign(mWorld->invId[27+barPosition],1,mWorld->invSt[27+barPosition],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                    if(mWorld->invAm[27+barPosition] == 0)
                                    {
                                        mWorld->invAm[27+barPosition] = -1;
                                        mWorld->invSt[27+barPosition] = 0;
                                        mWorld->invId[27+barPosition] = -1;
                                    }
                                }
                            }
                            else
                            {
                                mWorld->DropThisNoAlign(mWorld->invId[27+barPosition],mWorld->invAm[27+barPosition],mWorld->invSt[27+barPosition],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                mWorld->invAm[27+barPosition] = -1;
                                mWorld->invSt[27+barPosition] = 0;
                                mWorld->invId[27+barPosition] = -1;
                            }
                        }
                        return;
                    }
                }

                //open menu
                if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
                {
                    menuState = 1;
                    menuOptions = false;
                    optionsMenuPos = 0;
                }

                //camera rotate up
                if(keyHold(InputHelper::Instance()->getButtonToAction(4)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->PitchView(cameraSpeed);

                    if (shift_y > -0.06)
                    {

                        shift_y -= 0.005;
                    }
                }
                else
                {
                    if (shift_y < 0)
                    {

                        shift_y += 0.005;
                    }

                }

                //camera rotate down
                if(keyHold(InputHelper::Instance()->getButtonToAction(5)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->PitchView(-cameraSpeed);

                    if (shift_y < 0.06)
                    {

                        shift_y += 0.005;
                    }
                }
                else
                {
                    if (shift_y > 0)
                    {

                        shift_y -= 0.005;
                    }
                }

                //camera rotate left
                if(keyHold(InputHelper::Instance()->getButtonToAction(6)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->RotateView(cameraSpeed,0,1,0);

                    if (shift_x < 0.06)
                    {

                        shift_x += 0.005;
                    }
                }
                else
                {
                    if (shift_x > 0)
                    {

                        shift_x -= 0.005;
                    }
                }

                //camera rotate right
                if(keyHold(InputHelper::Instance()->getButtonToAction(7)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->RotateView(-cameraSpeed,0,1,0);

                    if (shift_x > -0.06)
                    {

                        shift_x -= 0.005;
                    }
                }
                else
                {
                    if (shift_x < 0)
                    {

                        shift_x += 0.005;
                    }
                }

                //move right
                if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    if(headInWater == true || headInLava == true)
                    {
                        fppCam->StrafePhysic(cameraMoveSpeed*0.5);
                    }
                    if(headInWater == false && headInLava == false && (footInLava == true || footInWater == true))
                    {
                        fppCam->StrafePhysic(cameraMoveSpeed*0.7);
                    }
                    if(headInWater == false && headInLava == false && footInWater == false && footInLava == false)
                    {
                        fppCam->StrafePhysic(cameraMoveSpeed);
                    }

                    if(mWorld->HG > 0.00005)
                    {
                        mWorld->HG -= 0.00005;
                    }
                }


                //move left
                if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }

                    if(headInWater == true || headInLava == true)
                    {
                        fppCam->StrafePhysic(-cameraMoveSpeed*0.5);
                    }
                    if(headInWater == false && headInLava == false && (footInLava == true || footInWater == true))
                    {
                        fppCam->StrafePhysic(-cameraMoveSpeed*0.7);
                    }
                    if(headInWater == false && headInLava == false && footInWater == false && footInLava == false)
                    {
                        fppCam->StrafePhysic(-cameraMoveSpeed);
                    }

                    if(mWorld->HG > 0.00005)
                    {
                        mWorld->HG -= 0.00005;
                    }
                }

                //move back
                if(keyHold(InputHelper::Instance()->getButtonToAction(1)))
                {
                    if(mWorld->HG > 0.00005)
                    {
                        mWorld->HG -= 0.00005;
                    }

                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    if(canFly)
                    {
                        fppCam->MovePhysic(-cameraMoveSpeed);
                    }
                    else
                    {
                        if(headInWater == true || headInLava == true)
                        {
                            fppCam->MovePhysicNoY(-cameraMoveSpeed*0.5);
                        }
                        if(headInWater == false && headInLava == false && (footInLava == true || footInWater == true))
                        {
                            fppCam->MovePhysicNoY(-cameraMoveSpeed*0.7);
                        }
                        if(headInWater == false && headInLava == false && footInWater == false && footInLava == false)
                        {
                            fppCam->MovePhysicNoY(-cameraMoveSpeed);
                        }
                    }
                }

                //move forward
                if(keyHold(InputHelper::Instance()->getButtonToAction(0)))
                {
                    if(mWorld->HG > 0.0001)
                    {
                        mWorld->HG -= 0.0001;
                    }

                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }

                    if(canFly)
                    {
                        fppCam->MovePhysic(cameraMoveSpeed);
                    }
                    else
                    {
                        if(headInWater == true || headInLava == true)
                        {
                            fppCam->MovePhysicNoY(cameraMoveSpeed*0.5);
                        }
                        if(headInWater == false && headInLava == false && (footInLava == true || footInWater == true))
                        {
                            fppCam->MovePhysicNoY(cameraMoveSpeed*0.7);
                        }
                        if(headInWater == false && headInLava == false && footInWater == false && footInLava == false)
                        {
                            fppCam->MovePhysicNoY(cameraMoveSpeed);
                        }
                    }
                }

                // jump
                if(keyHold(InputHelper::Instance()->getButtonToAction(12)))
                {
                    dStd = -1;
                    if (headInWater || headInLava)
                    {
                        if(walkingOnGround == true)
                        {
                            jumping = true;
                        }
                        else
                        {
                            playerVelocity.y = 0.575 * JUMPVELOCITY;
                        }
                    }
                    if (headInWater == false && headInLava == false && walkingOnGround == false && (footInWater == true || footInLava == true))	//Your above he water, so Jump out
                    {
                        playerVelocity.y = 1.1 * JUMPVELOCITY;
                        walkingOnGround = false;
                    }
                    if(walkingOnGround == true)
                    {
                        if(headInWater == false && headInLava == false)
                        {
                            jumping = true;
                            mWorld->mainStatistics.jumps += 1;
                            if(mWorld->HG > 0.03)
                            {
                                mWorld->HG -= 0.03;
                            }
                        }
                    }
                }

            //add cube
            if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
            {
                if (startDt == true)
                {
                    startDt = false; //stop destroying
                }

                if(keyPressed(InputHelper::Instance()->getButtonToAction(13))) //open inventory
                {
                    if(craft3xEn == false && chestEn == false && furnaceEn == false)
                    {
                        invEn = true;
                        dT = 0;
                        dET = 0;
                        chestId = -1;
                        dStd = -1;
                        return;
                    }
                }

                /// EATING FOOD
                if (mWorld->invId[27+barPosition] == 288) ///BREAD
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 5;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }
                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 315) ///COOKIE
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 1;
                    mWorld->HP += 1;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }
                    if(mWorld->HP > 20)
                    {
                        mWorld->HP = 20;
                    }
                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == RottenFlesh::getID()) ///ROTTEN FLESH
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 1;

                    if(rand() % 100 < 45)
                    {
                        HurtPlayer(1);
                    }

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }

                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 311) ///MELON
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 2;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }

                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 317) ///STEAK
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 8;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }

                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 284) ///APPLE
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 4;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }
                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0)
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 303) ///MOOSHROOM BOWL
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG += 6;

                    if(mWorld->HG > 20)
                    {
                        mWorld->HG = 20;
                    }
                    mWorld->invId[27+barPosition] = 302; // turn it into simple stackable bowl
                    mWorld->invSt[27+barPosition] = 1;
                    return;
                }

                if (mWorld->invId[27+barPosition] == 285) ///GOLDEN APPLE
                {
                    mSoundMgr->PlayEatSound();
                    mWorld->mainStatistics.foodEaten += 1;
                    mWorld->HG = 20;
                    mWorld->HP = 20;
                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0)
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                if (mWorld->invId[27+barPosition] == 299) ///SNOWBALL THROWING
                {
                    mSoundMgr->PlayBowSound();

                    SnowBall2* NewSB = new SnowBall2(playerPosition.x,playerPosition.y,playerPosition.z);
                    NewSB->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180)*PI);
                    mSnowBalls.push_back(NewSB);

                    mWorld->invAm[27+barPosition] -= 1;
                    if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                    {
                        mWorld->invAm[27+barPosition] = -1;
                        mWorld->invId[27+barPosition] = -1;
                        mWorld->invSt[27+barPosition] = 0;
                    }
                    return;
                }

                //add cube
                Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
                rayDir.normalize();

                //get position and view vector
                Vector3 testPos;

                BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
                BoundingBox testBox = BoundingBox(testPos.x+collider.min.x, testPos.y+collider.min.y, testPos.z+collider.min.z, testPos.x+collider.max.x, testPos.y+collider.max.y, testPos.z+collider.max.z);

                //move to the target +=0.5
                for(float i = 0; i < 5.25f; i+=0.15f)
                {
                    testPos = fppCam->m_vPosition + (rayDir * i);

                    collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
                    testBox = BoundingBox(floorf(testPos.x)+0.5f+collider.min.x, floorf(testPos.y)+0.5f+collider.min.y, floorf(testPos.z)+0.5f+collider.min.z, floorf(testPos.x)+0.5f+collider.max.x, floorf(testPos.y)+0.5f+collider.max.y, floorf(testPos.z)+0.5f+collider.max.z);

                    if(mWorld->invId[27+barPosition] == 290) //busket
                    {
                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 4) //if it is WATER
                        {
                            if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4))
                            {
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 4;
                            }
                            else
                            {
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;
                            }

                            mWorld->invId[27+barPosition] = 291;

                            int	curchunkTarget = mWorld->getChunkId(testPos);
                            //Rebuild nearby world
                            mWorld->rebuildChunk(curchunkTarget);
                            mWorld->rebuildTransparentChunk(curchunkTarget);
                            fppCam->needUpdate = true;
                            return;
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 112) //if it is lava
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;

                            mWorld->invId[27+barPosition] = 292;

                            int	curchunkTarget = mWorld->getChunkId(testPos);

                            mWorld->RemoveLigtSourceAtPosition(testPos.x,testPos.y,testPos.z,112);
                            //Rebuild nearby world
                            mWorld->UpdateLightAreaIn(testPos);
                            mWorld->rebuildChunk(curchunkTarget);
                            mWorld->rebuildTransparentChunk(curchunkTarget);
                            fppCam->needUpdate = true;
                            return;
                        }
                    }

                    //check if we are touch something
                    if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z) && testBox.contains(testPos))
                    {
                        if(mWorld->invId[27+barPosition] >= 270 && mWorld->invId[27+barPosition] <= 274) //hoes
                        {
                            if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 1) //if it is grass
                            {
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 2;
                                if(rand() % 10 == 1)
                                {
                                    mWorld->DropThis(286,1,true,testPos); //put seed in inventory
                                }

                                mWorld->invAm[27+barPosition] -= 1; // bit crashing to our hoe
                                if(mWorld->invAm[27+barPosition] == 0) //destroy tool if it has 0 durability points
                                {
                                    mWorld->invAm[27+barPosition] = -1;
                                    mWorld->invId[27+barPosition] = -1;
                                    mWorld->invSt[27+barPosition] = 0;
                                }
                                int	curchunkTarget = mWorld->getChunkId(testPos);

                                fppCam->needUpdate = true;
                                //Rebuild nearby world
                                mWorld->rebuildChunk(curchunkTarget);
                                mWorld->rebuildTransparentChunk(curchunkTarget);
                                return;
                            }

                            if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 2) //if it is dirt
                            {
                                mWorld->mainStatistics.soilPlowed += 1;
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 79;

                                mWorld->invAm[27+barPosition] -= 1;
                                if(mWorld->invAm[27+barPosition] == 0) //destroy tool if it has 0 durability points
                                {
                                    mWorld->invAm[27+barPosition] = -1;
                                    mWorld->invId[27+barPosition] = -1;
                                    mWorld->invSt[27+barPosition] = 0;
                                }

                                int	curchunkTarget = mWorld->getChunkId(testPos);

                                fppCam->needUpdate = true;
                                //Rebuild nearby world
                                mWorld->rebuildChunk(curchunkTarget);
                                mWorld->rebuildTransparentChunk(curchunkTarget);
                                return;
                            }
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == CraftingTable::getID()) // open crafting table menu
                        {
                            craft3xEn = true;
                            return;
                        }

                        if(mWorld->invId[27+barPosition] == BoneMeal::getID())
                        {
                            bool used = false;

                            if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == GrassBlock::getID())
                            {
                                for(int xx = testPos.x-2; xx <= testPos.x+2; xx ++)
                                {
                                    for(int zz = testPos.z-2; zz <= testPos.z+2; zz ++)
                                    {
                                        for(int yy = testPos.y; yy > 0; yy--)
                                        {
                                            if(mWorld->GetBlock(xx,yy,zz) != 0)
                                            {
                                                if(mWorld->GetBlock(xx,yy,zz) == GrassBlock::getID())
                                                {
                                                    if(mWorld->GetBlock(xx,yy+1,zz) == 0)
                                                    {
                                                        if(rand()%100<55)
                                                        {
                                                            rand() % 2 == 0 ? mWorld->GetBlock(xx,yy+1,zz) = Flower1::getID() : mWorld->GetBlock(xx,yy+1,zz) = Flower2::getID();
                                                        }
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        break;
                                                    }
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                used = true;
                            }
                            if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= WheatBlock1::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= WheatBlock3::getID())
                            {
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = WheatBlock4::getID();
                                used = true;
                            }
                            if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= MelonPlant1::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= MelonPlant3::getID())
                            {
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = MelonPlant4::getID();
                                used = true;
                            }

                            if(used)
                            {
                                mWorld->invAm[27+barPosition] -= 1;
                                if(mWorld->invAm[27+barPosition] == 0)
                                {
                                    mWorld->invAm[27+barPosition] = -1;
                                    mWorld->invSt[27+barPosition] = 0;
                                    mWorld->invId[27+barPosition] = -1;
                                }
                                int	curchunkTarget = mWorld->getChunkId(testPos);
                                fppCam->needUpdate = true;
                                mWorld->rebuildTransparentChunk(curchunkTarget);
                                return;
                            }
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= 49 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= 52) //door
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) + 4;
                            mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 58;
                            mSoundMgr->PlayDoorSound(true);

                            int	curchunkTarget = mWorld->getChunkId(testPos);
                            fppCam->needUpdate = true;
                            mWorld->rebuildTransparentChunk(curchunkTarget);
                            return;
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= 53 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= 56) //door
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) - 4;
                            mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 57;
                            mSoundMgr->PlayDoorSound(false);

                            int	curchunkTarget = mWorld->getChunkId(testPos);
                            fppCam->needUpdate = true;
                            mWorld->rebuildTransparentChunk(curchunkTarget);
                            return;
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 57) //door
                        {
                            if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 49 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 52) //door
                            {
                                mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) + 4;
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 58;
                                mSoundMgr->PlayDoorSound(true);

                                int	curchunkTarget = mWorld->getChunkId(Vector3(testPos.x,testPos.y-1,testPos.z));
                                fppCam->needUpdate = true;
                                mWorld->rebuildTransparentChunk(curchunkTarget);
                                return;
                            }
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 58) //door
                        {
                            if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 53 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 56) //door
                            {
                                mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) - 4;
                                mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 57;
                                mSoundMgr->PlayDoorSound(false);

                                int	curchunkTarget = mWorld->getChunkId(Vector3(testPos.x,testPos.y-1,testPos.z));
                                fppCam->needUpdate = true;
                                mWorld->rebuildTransparentChunk(curchunkTarget);
                                return;
                            }
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == ChestBlock1::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == ChestBlock2::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == ChestBlock3::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == ChestBlock4::getID())
                        {
                            chestId = FindChestId(testPos.x,testPos.y,testPos.z);
                            if(chestId != -1)
                            {
                                craft3xEn = false;
                                chestEn = true;
                                UseChest = mWorld->mChests[chestId];
                                return;
                            }
                        }

                        if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == FurnaceOff::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == FurnaceOn::getID())
                        {
                            furnaceId = FindFurnaceId(testPos.x,testPos.y,testPos.z);
                            if(furnaceId != -1)
                            {
                                craft3xEn = false;
                                chestEn = false;
                                furnaceEn = true;
                                UseFurnace = mWorld->mFurnaces[furnaceId];
                                return;
                            }
                        }

                        BoundingBox testBox2 = BoundingBox(Vector3(cubePos.x - 0.5f,cubePos.y - 0.5f,cubePos.z - 0.5f),Vector3(cubePos.x + 0.5f,cubePos.y + 0.5f,cubePos.z + 0.5f));
                        Ray tesRay = Ray(fppCam->m_vPosition,rayDir);

                        float distance = -1.0f;
                        tesRay.hasIntersected(testBox2,distance);

                        if(distance != -1.0f)
                        {
                            Vector3 hitPos = fppCam->m_vPosition + (rayDir * distance);
                            Vector3 normal = (hitPos - cubePos);
                            normal.normalize();

                            Vector3 testPos2;

                            if(normal.x < -0.66f)
                                testPos2.x = -1.0f;
                            else if(normal.x > 0.66f)
                                testPos2.x = 1.0f;
                            else
                                testPos2.x = 0.0f;

                            if(normal.y < -0.66f)
                                testPos2.y = -1.0f;
                            else if(normal.y > 0.66f)
                                testPos2.y = 1.0f;
                            else
                                testPos2.y = 0.0f;

                            if(normal.z < -0.66f)
                                testPos2.z = -1.0f;
                            else if(normal.z > 0.66f)
                                testPos2.z = 1.0f;
                            else
                                testPos2.z = 0.0f;

                            testPos2 += testPos;

                            //check if this block is empty
                            if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID() || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 93)
                            {
                                //now check if player is not there ;) we don't want to place cubes where we stand
                                int boxX = (int)testPos2.x;
                                int boxY = (int)testPos2.y;
                                int boxZ = (int)testPos2.z;

                                BoundingBox blockBox = BoundingBox(Vector3(boxX,boxY,boxZ),Vector3(boxX + 1,boxY + 1,boxZ + 1));
                                BoundingBox playerBox = BoundingBox(Vector3(playerPosition.x - 0.15f,playerPosition.y - 1.3f,playerPosition.z - 0.15f),Vector3(playerPosition.x + 0.15f,playerPosition.y + 0.4f,playerPosition.z + 0.15f));

                                if(!blockBox.intersect(playerBox) || mWorld->invId[27+barPosition] == 48 || mWorld->invId[27+barPosition] == 307)
                                {
                                    //check if you want put light source or normal block
                                    if(mWorld->CanPutBlockHere(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]))
                                    {
                                        bool wasLight = false;

                                        if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
                                        {
                                            wasLight = true;
                                        }


                                        if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID())
                                        {
                                            mWorld->RemoveLigtSourceAtPosition(testPos2.x,testPos2.y,testPos2.z,112);
                                            mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
                                        }

                                        if (mWorld->invId[27+barPosition]<250) // if block in our hands
                                        {
                                            if(mWorld->invId[27+barPosition] == ChestBlock1::getID()) // if we are putting chest
                                            {
                                                Chest* NewChest =  new Chest(testPos2.x,testPos2.y,testPos2.z);
                                                mWorld->mChests.push_back(NewChest);
                                            }

                                            if(mWorld->invId[27+barPosition] == FurnaceOff::getID()) // if we are putting furnace
                                            {
                                                Furnace* NewFurnace =  new Furnace(testPos2.x,testPos2.y,testPos2.z);
                                                mWorld->mFurnaces.push_back(NewFurnace);
                                            }

                                            if(mWorld->invId[27+barPosition]!=-1) //multi-texturing blocks
                                            {

                                                    switch(mWorld->invId[27+barPosition])
                                                    {
                                                    case 73:
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 75;
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 76;
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 73;
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 73;
                                                    }
                                                    break;

                                                    case 94:
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 96; // 3
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 97; // 4
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 94; // 1
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 95; // 2
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 94;
                                                    }
                                                    break;

                                                    case 125:
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125; // 3
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 126; // 4
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 127; // 1
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 128; // 2
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125;
                                                    }
                                                    break;

                                                    case 60:
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 60; // 3
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 61; // 4
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 62; // 1
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 63; // 2
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 60;
                                                    }
                                                    break;

                                                    case 67:
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 67; // 3
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 68; // 4
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 69; // 1
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 70; // 2
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 67;
                                                    }
                                                    break;

                                                    default:
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = mWorld->invId[27+barPosition];
                                                    break;
                                                    }

                                                if(mWorld->invAm[27+barPosition]==1)
                                                {
                                                    mWorld->invAm[27+barPosition]= -1;
                                                    mWorld->invId[27+barPosition]= -1;
                                                    mWorld->invSt[27+barPosition]= 0;
                                                }
                                                else
                                                {
                                                    mWorld->invAm[27+barPosition]-= 1;
                                                }

                                                }
                                        }
                                        else //if it is item in our hand
                                        {
                                            if(mWorld->invId[27+barPosition] == TorchItem::getID()) // if it is torch
                                            {
                                                if(mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z) == true || mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z) == true || mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1) == true || mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1) == true || mWorld->BlockSolid(testPos2.x,testPos2.y-1,testPos2.z) == true)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 48;
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                       mWorld->invAm[27+barPosition] = -1;
                                                       mWorld->invSt[27+barPosition] = 0;
                                                       mWorld->invId[27+barPosition] = -1;
                                                    }
                                                    wasLight = true;
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] == WheatSeeds::getID()) // if it is seeds
                                            {
                                                if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 79 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 80) // planting seeds
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 134;
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                       mWorld->invAm[27+barPosition] = -1;
                                                       mWorld->invSt[27+barPosition] = 0;
                                                       mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] == MelonSeeds::getID()) // if it is melon seeds
                                            {
                                                if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == Soil::getID() || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == WateredSoil::getID()) // planting seeds
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = MelonPlant1::getID();
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                       mWorld->invAm[27+barPosition] = -1;
                                                       mWorld->invSt[27+barPosition] = 0;
                                                       mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] >= 300 && mWorld->invId[27+barPosition] <= 301) // if it is moshrooms
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 77 + (mWorld->invId[27+barPosition] - 300);
                                                fppCam->needUpdate = true;

                                                mWorld->invAm[27+barPosition] -= 1;
                                                if(mWorld->invAm[27+barPosition] == 0)
                                                {
                                                    mWorld->invAm[27+barPosition] = -1;
                                                    mWorld->invSt[27+barPosition] = 0;
                                                    mWorld->invId[27+barPosition] = -1;
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] >= 294 && mWorld->invId[27+barPosition] <= 296) // if it is flowers or saplings
                                            {
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 2) // if under is dirt or grass
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 119 + (mWorld->invId[27+barPosition] - 294); //very difficult expression >:
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                       mWorld->invAm[27+barPosition] = -1;
                                                       mWorld->invSt[27+barPosition] = 0;
                                                       mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] == 309 || mWorld->invId[27+barPosition] == 310) // if it is another sapling
                                            {
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 2 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 29) // if under is dirt or grass
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 122 + (mWorld->invId[27+barPosition] - 309); //very difficult expression >:
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                       mWorld->invAm[27+barPosition] = -1;
                                                       mWorld->invSt[27+barPosition] = 0;
                                                       mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] == 306) // if it is door item
                                            {
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) == 0)
                                                {
                                                    if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49; // 3
                                                        mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                                    }
                                                    if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 50; // 4
                                                        mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                                    }
                                                    if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 51; // 1
                                                        mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                                    }
                                                    if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 52; // 2
                                                        mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                                    }
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49;
                                                        mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                                    }

                                                    fppCam->needUpdate = true;
                                                    int chunkTarget = mWorld->getChunkId(testPos2);
                                                    //mWorld->rebuildTransparentChunk(chunkTarget);
                                                    //mWorld->rebuildNearestChunks(chunkTarget,testPos2);

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                        mWorld->invAm[27+barPosition] = -1;
                                                        mWorld->invSt[27+barPosition] = 0;
                                                        mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }


                                            if(mWorld->invId[27+barPosition] == 307) // if it is ladder item
                                            {
                                                bool placed = false;
                                                if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                {
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) != 0 && mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1) == true)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 90; // 3
                                                        placed = true;
                                                    }
                                                }
                                                if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                {
                                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) != 0 && mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1) == true)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 89;
                                                        placed = true;
                                                    }
                                                }
                                                if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                {
                                                    if(mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) != 0 && mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z) == true)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 88;
                                                        placed = true;
                                                    }
                                                }
                                                if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                {
                                                    if(mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) != 0 && mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z) == true)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 87;
                                                        placed = true;
                                                    }
                                                }

                                                if(placed == true)
                                                {
                                                    fppCam->needUpdate = true;
                                                    int chunkTarget = mWorld->getChunkId(testPos2);

                                                    mWorld->rebuildTransparentChunk(chunkTarget);
                                                    mWorld->rebuildNearestChunks(chunkTarget,testPos2);

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                        mWorld->invAm[27+barPosition] = -1;
                                                        mWorld->invSt[27+barPosition] = 0;
                                                        mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }


                                            if(mWorld->invId[27+barPosition] == 293) // if it is cane item
                                            {
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 7) //check if under is sand
                                                {
                                                    if(mWorld->GetBlock(testPos2.x-1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x+1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z+1) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z-1) == 4)
                                                    {
                                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 33;
                                                        fppCam->needUpdate = true;

                                                        mWorld->invAm[27+barPosition] -= 1;
                                                        if(mWorld->invAm[27+barPosition] == 0)
                                                        {
                                                            mWorld->invAm[27+barPosition] = -1;
                                                            mWorld->invSt[27+barPosition] = 0;
                                                            mWorld->invId[27+barPosition] = -1;
                                                        }
                                                    }
                                                }
                                            }

                                            if(mWorld->invId[27+barPosition] == 291) // if it is water busket
                                            {
                                                int chunkTarget = mWorld->getChunkId(testPos2);
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 4;
                                                mWorld->invId[27+barPosition] = 290;

                                                //mWorld->rebuildChunk(chunkTarget);
                                                //mWorld->rebuildTransparentChunk(chunkTarget);
                                                fppCam->needUpdate = true;
                                            }
                                            if(mWorld->invId[27+barPosition] == 292) // if it is lava busket
                                            {
                                                int chunkTarget = mWorld->getChunkId(testPos2);

                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 112;
                                                mWorld->invId[27+barPosition] = 290;

                                                wasLight = true;

                                                fppCam->needUpdate = true;
                                            }
                                        }

                                        animGo = true;
                                        animDest = 0.0f;
                                        mWorld->mainStatistics.blockPlaced += 1;

                                        int chunkTarget = mWorld->getChunkId(testPos2);

                                        if(mWorld->invId[27+barPosition] < 250)
                                        {
                                            mSoundMgr->PlayWalkSound(mWorld->blockTypes[mWorld->invId[27+barPosition]].soundType);
                                        }

                                        //rebuild
                                        if(wasLight == true)
                                        {
                                            mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
                                            mWorld->rebuildTransparentChunk(chunkTarget);
                                            mWorld->rebuildChunk(chunkTarget);

                                            mWorld->rebuildNearestChunksForLight(chunkTarget,testPos2);
                                        }
                                        else
                                        {
                                            //check if there are light sources nearby
                                            mWorld->initPutBlocksLight(testPos2.x,testPos2.z);

                                            if((mWorld->GetBlockSettings(testPos2.x,testPos2.y,testPos2.z) & mWorld->OpLighSource) != 0)
                                            {
                                                mWorld->UpdateLightAreaIn(testPos2);
                                            }

                                            mWorld->rebuildTransparentChunk(chunkTarget);
                                            mWorld->rebuildChunk(chunkTarget);
                                            mWorld->rebuildNearestChunks(chunkTarget,testPos2);
                                        }
                                    }
                                    fppCam->needUpdate = true;
                                }
                            }
                        }
                        break;
                    }
                }
            }


            if(keyPressed(InputHelper::Instance()->getButtonToAction(13)))
            {
                //remove cube
                Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
                rayDir.normalize();

                //we are takin our positiona and view vector
                Vector3 testPos2;
                testPos2 = Vector3(-1,-1,-1);

                BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
                BoundingBox testBox = BoundingBox(testPos2.x+collider.min.x, testPos2.y+collider.min.y, testPos2.z+collider.min.z, testPos2.x+collider.max.x, testPos2.y+collider.max.y, testPos2.z+collider.max.z);

                //we are moving slowly to the target +=0.5
                for(float i = 0; i < 5.25f; i+=0.15f)
                {
                    testPos2 = fppCam->m_vPosition + (rayDir * i);

                    collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
                    testBox = BoundingBox(floorf(testPos2.x)+0.5f+collider.min.x, floorf(testPos2.y)+0.5f+collider.min.y, floorf(testPos2.z)+0.5f+collider.min.z, floorf(testPos2.x)+0.5f+collider.max.x, floorf(testPos2.y)+0.5f+collider.max.y, floorf(testPos2.z)+0.5f+collider.max.z);

                    bool kick = false;
                    for(int f = 0; f < mWorld->mZombies.size(); f++)
                    {
                        Zombie *TestZombie = mWorld->mZombies[f];
                        if(TestZombie->DistanceToPlayer() < 2.25 && TestZombie->kicked == false && TestZombie->damaged == false)
                        {
                            if(TestZombie->bBox.contains(testPos2))
                            {
                                float damage = 2.0f;
                                bool weapon = false;

                                switch(mWorld->invId[27+barPosition])
                                {
                                    case 255 : damage = 4.0f; weapon = true; break;
                                    case 256 : damage = 5.0f; weapon = true; break;
                                    case 257 : damage = 6.0f; weapon = true; break;
                                    case 258 : damage = 7.0f; weapon = true; break;
                                    case 259 : damage = 4.0f; weapon = true; break;
                                }

                                if(weapon == true)
                                {
                                    mWorld->invAm[27+barPosition] -= 1+rand()%2;

                                    if(mWorld->invAm[27+barPosition] <= 0)
                                    {
                                        mWorld->invId[27+barPosition] = -1;
                                        mWorld->invAm[27+barPosition] = -1;
                                        mWorld->invSt[27+barPosition] = false;

                                        mSoundMgr->PlayBreakSound();
                                    }
                                }

                                TestZombie->TakeDamage(damage,0.7f,5.0f,dt);
                                kick = true;
                                animGo = true;
                                animDest = 0.0f;
                                return;
                            }
                        }
                    }
                    if(kick == true)
                    {
                        return;
                    }

                    for(int f = 0; f < mWorld->mCows.size(); f++)
                    {
                        Cow *TestCow = mWorld->mCows[f];
                        if(TestCow->DistanceToPlayer() < 2.25 && TestCow->kicked == false && TestCow->damaged == false)
                        {
                            if(TestCow->bBox.contains(testPos2))
                            {
                                float damage = 2.0f;
                                bool weapon = false;

                                switch(mWorld->invId[27+barPosition])
                                {
                                    case 255 : damage = 4.0f; weapon = true; break;
                                    case 256 : damage = 5.0f; weapon = true; break;
                                    case 257 : damage = 6.0f; weapon = true; break;
                                    case 258 : damage = 7.0f; weapon = true; break;
                                    case 259 : damage = 4.0f; weapon = true; break;
                                }

                                if(weapon == true)
                                {
                                    mWorld->invAm[27+barPosition] -= 1+rand()%2;

                                    if(mWorld->invAm[27+barPosition] <= 0)
                                    {
                                        mWorld->invId[27+barPosition] = -1;
                                        mWorld->invAm[27+barPosition] = -1;
                                        mWorld->invSt[27+barPosition] = false;

                                        mSoundMgr->PlayBreakSound();
                                    }
                                }

                                TestCow->TakeDamage(damage,0.7f,5.0f,dt);
                                kick = true;
                                animGo = true;
                                animDest = 0.0f;
                                return;
                            }
                        }
                    }

                    //check if we touch something
                    if(mWorld->BlockEditable(testPos2.x,testPos2.y,testPos2.z) && testBox.contains(testPos2))
                    {
                        if (startDt == false)
                        {
                            testPos1.x  = testPos2.x;
                            testPos1.y  = testPos2.y;
                            testPos1.z  = testPos2.z;
                            switch(mWorld->BlockMaterial(testPos2.x,testPos2.y,testPos2.z))
                            {
                                case 1: // материал - дерево
                                if(mWorld->invId[27+barPosition] == 265) // если в руке деревянный топор
                                {
                                    dET = 1.5f; // 1.5 секунды
                                }
                                else if(mWorld->invId[27+barPosition] == 266) // если в руке каменный топор
                                {
                                    dET = 0.75f;
                                }
                                else if(mWorld->invId[27+barPosition] == 267) // если в руке железный топор
                                {
                                    dET = 0.5f;
                                }
                                else if(mWorld->invId[27+barPosition] == 268) // если в руке алмазный топор
                                {
                                    dET = 0.4f;
                                }
                                else if(mWorld->invId[27+barPosition] == 269) // если в руке золотой топор
                                {
                                    dET = 0.25f;
                                }
                                else
                                {
                                    dET = 3.0f;
                                }
                                break;

                                case 2: // материал - камень
                                if(mWorld->invId[27+barPosition] == 250)
                                {
                                    dET = 1.5f;
                                }
                                else if(mWorld->invId[27+barPosition] == 251)
                                {
                                    dET = 0.75f;
                                }
                                else if(mWorld->invId[27+barPosition] == 252)
                                {
                                    dET = 0.5f;
                                }
                                else if(mWorld->invId[27+barPosition] == 253)
                                {
                                    dET = 0.4f;
                                }
                                else if(mWorld->invId[27+barPosition] == 254)
                                {
                                    dET = 0.25f;
                                }
                                else
                                {
                                    dET = 10.0f;
                                }
                                break;

                                case 3: // материал - земля
                                if(mWorld->invId[27+barPosition] == 260)
                                {
                                    dET = 0.45f;
                                }
                                else if(mWorld->invId[27+barPosition] == 261)
                                {
                                    dET = 0.25f;
                                }
                                else if(mWorld->invId[27+barPosition] == 262)
                                {
                                    dET = 0.15f;
                                }
                                else if(mWorld->invId[27+barPosition] == 263)
                                {
                                    dET = 0.15f;
                                }
                                else if(mWorld->invId[27+barPosition] == 264)
                                {
                                    dET = 0.1f;
                                }
                                else
                                {
                                    dET = 0.9f;
                                }
                                break;

                                case 4: // материал - листва
                                if(mWorld->invId[27+barPosition] == 275)
                                {
                                    dET = 0.1f;
                                }
                                else
                                {
                                    dET = 0.3f;
                                }
                                break;

                                case 5:
                                if(mWorld->invId[27+barPosition] == 253)
                                {
                                    dET = 10.0f;
                                }
                                else
                                {
                                    dET = 250.0f;
                                }
                                break;

                                case 6:
                                dET = 3600.0f;
                                break;

                                break;

                                default:
                                dET = 0.3f;
                                break;

                            }
                            dT = 0;
                            startDt = true;
                        }
                    }
                }
            }

            //remove cube
            if(keyHold(InputHelper::Instance()->getButtonToAction(13)))
            {
                if (startDt == true)
                {
                    if(animGo == false)
                    {
                        animGo = true;
                        animDest = 0.0f;
                    }

                    if(headInWater) // slow removing under water
                    {
                        dT < dET ? dT += dt*0.32 : dT = 0;
                    }
                    else
                    {
                        dT < dET ? dT += dt : dT = 0;
                    }

                    dStd = roundf(dT*(100/(float)dET))/10.0f;
                    //remove block
                    if (dT >= dET)
                    {
                        bool wasLight = false;
                        block_t oldBlock = 0;

                        if(mWorld->LightSourceBlock(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z)))//if it's light block
                        {
                            wasLight = true;
                        }
                        oldBlock = mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z);

                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) >= ChestBlock1::getID() && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) <= ChestBlock4::getID()) // if it is chest
                        {
                            chestId = FindChestId(testPos1.x,testPos1.y,testPos1.z);
                            if(chestId != -1)
                            {
                                // drop all items in chest
                                Chest* TestChest = mWorld->mChests[chestId];
                                for(int i = 0; i <= 27; i++)
                                {
                                    if(TestChest->chestSlotId[i] > 0)
                                    {
                                        Vector3 dropVelocity = Vector3(0,0,0);

                                        dropVelocity.x = (-15+rand()%30)*0.1f;
                                        dropVelocity.y = 3.0f;
                                        dropVelocity.z = (-15+rand()%30)*0.1f;

                                        if(TestChest->chestSlotAm[i] > 0)
                                        {
                                            mWorld->DropThisNoAlign(TestChest->chestSlotId[i],TestChest->chestSlotAm[i],TestChest->chestSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

                                            TestChest->chestSlotAm[i] = -1;
                                            TestChest->chestSlotSt[i] = 0;
                                            TestChest->chestSlotId[i] = -1;
                                        }
                                    }
                                }

                                delete mWorld->mChests[chestId];
                                mWorld->mChests.erase(mWorld->mChests.begin()+chestId);
                            }
                        }

                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == FurnaceOff::getID() || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == FurnaceOn::getID())
                        {
                            furnaceId = FindFurnaceId(testPos1.x,testPos1.y,testPos1.z);
                            if(furnaceId != -1)
                            {
                                // drop all items in furnace
                                Furnace* TestFurnace = mWorld->mFurnaces[furnaceId];
                                for(int i = 0; i <= 2; i++)
                                {
                                    if(TestFurnace->furnaceSlotId[i] > 0)
                                    {
                                        Vector3 dropVelocity = Vector3(0,0,0);

                                        dropVelocity.x = (-15+rand()%30)*0.1f;
                                        dropVelocity.y = 3.0f;
                                        dropVelocity.z = (-15+rand()%30)*0.1f;

                                        if(TestFurnace->furnaceSlotAm[i] > 0)
                                        {
                                            mWorld->DropThisNoAlign(TestFurnace->furnaceSlotId[i],TestFurnace->furnaceSlotAm[i],TestFurnace->furnaceSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

                                            TestFurnace->furnaceSlotAm[i] = -1;
                                            TestFurnace->furnaceSlotSt[i] = 0;
                                            TestFurnace->furnaceSlotId[i] = -1;
                                        }
                                    }
                                }
                                delete mWorld->mFurnaces[furnaceId];
                                mWorld->mFurnaces.erase(mWorld->mFurnaces.begin()+furnaceId);
                            }
                        }

                        if (mWorld->GetBlock(testPos1.x, testPos1.y, testPos1.z) == TNT::getID())//����
                        {
                            mSoundMgr->TNTSound();
                            int	curchunkTarget = mWorld->getChunkId(testPos1);
                            for(int x = -24; x <= 24; x++)
                            {
                                for(int y = -24; y <= 24; y++)
                                {
                                    for(int z = -24; z <= 24; z++)
                                    {
                                        if(mWorld->GetBlock(x+testPos1.x,y+testPos1.y,z+testPos1.z) != IronBlock::getID() || mWorld->GetBlock(x+testPos1.x,y+testPos1.y,z+testPos1.z) != WaterBlock::getID())
                                        {
                                            if(sqrt(pow(sqrt(pow(x,2)+pow(y,2)),2)+pow(z,2))<=24)
                                                mWorld->GetBlock(x+testPos1.x,y+testPos1.y,z+testPos1.z) = 0;
                                        }
                                    }
                                }
                            }
                        }

                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) >= 57 && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) <= 58) // если мы разрушаем дверь, разрушаем её нижний блок
                        {
                            mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                            mWorld->GetBlock(testPos1.x,testPos1.y-1,testPos1.z) = 0;
                        }

                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) >= 49 && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) <= 56) // если мы разрушаем дверь, разрушаем её верхний блок
                        {
                            mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                            mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z) = 0;
                        }

                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 32)
                        {
                            mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 4;
                        }
                        else
                        {
                            mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                        }

                        if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 275)
                        {
                            mWorld->invAm[27+barPosition] -= 1;
                            if(mWorld->invAm[27+barPosition] == 0)
                            {
                                mWorld->invId[27+barPosition] = -1;
                                mWorld->invAm[27+barPosition] = -1;
                                mWorld->invSt[27+barPosition] = 0;
                                mSoundMgr->PlayBreakSound();
                            }
                        }

                        switch(oldBlock)
                        {
                        case 9:
                            if(mWorld->invId[27+barPosition] != 275)
                            {
                                if (rand() % 50 == 1)
                                {
                                    mWorld->DropThis(284,testPos1);
                                }

                                if (rand() % 16 == 1)
                                {
                                    mWorld->DropThis(296,testPos1);
                                }
                            }
                            else
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 37:
                            if(mWorld->invId[27+barPosition] != 275)
                            {
                                if (rand() % 10 == 1)
                                {
                                    mWorld->DropThis(309,testPos1);
                                }
                            }
                            else
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 38:
                            if(mWorld->invId[27+barPosition] != 275)
                            {
                                if (rand() % 16 == 1)
                                {
                                    mWorld->DropThis(310,testPos1);
                                }
                            }
                            else
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 137:
                            mWorld->DropThis(287,testPos1);
                            mWorld->DropThis(286,testPos1);
                            if(rand() % 2 == 0)
                            {
                                mWorld->DropThis(286,testPos1);
                            }
                        break;

                        case 93:
                            if(mWorld->invId[27+barPosition] >= 260 && mWorld->invId[27+barPosition] <= 264)
                            {
                                mWorld->DropThis(299,4,testPos1);
                            }
                        break;

                        // ore digging with special tools
                        case 3:
                            if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 36:
                            if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 41:
                            if(mWorld->invId[27+barPosition] >= 251 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 42:
                            if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 43:
                            if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 44:
                            if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 45:
                            if(mWorld->invId[27+barPosition] >= 251 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),4+rand()%5,testPos1);
                            }
                        break;

                        case 5:
                            if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                            {
                                mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                            }
                        break;

                        case 99:
                            mWorld->DropThis(mWorld->LootBlock(oldBlock),4,testPos1);
                        break;

                        case 81:
                            mWorld->DropThis(mWorld->LootBlock(oldBlock),3+rand()%5,testPos1);
                        break;

                        case 116:
                        if (rand() % 10 == 1)
                        {
                            mWorld->DropThis(286,testPos1);
                        }
                        break;

                        default:
                            mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
                        break;
                        }

                        mWorld->mainStatistics.blockDestroyed += 1;
                        int chunkTarget = mWorld->getChunkId(testPos1);
                        //check if this block is a support for light block
                        mWorld->CheckForTorchSupport(testPos1.x,testPos1.y,testPos1.z,mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z));

                        if(wasLight == true)
                        {
                            mWorld->RemoveLigtSourceAtPosition(testPos1.x,testPos1.y,testPos1.z,oldBlock);
                        }

                        if(chunkTarget != -1)
                        {
                            if(wasLight == true)
                            {
                                mWorld->UpdateLightAreaIn(Vector3(testPos1.x,testPos1.y,testPos1.z));
                                mWorld->rebuildChunk(chunkTarget);
                                mWorld->rebuildTransparentChunk(chunkTarget);

                                mWorld->rebuildNearestChunksForLight(chunkTarget,testPos1);
                            }
                            else
                            {
                                mWorld->initPutBlocksLight(testPos1.x,testPos1.z);
                                mWorld->UpdateLightAreaIn(testPos1);

                                mWorld->rebuildChunk(chunkTarget);
                                mWorld->rebuildTransparentChunk(chunkTarget);
                                mWorld->rebuildNearestChunks(chunkTarget,testPos1);
                            }
                        }

                        if(mWorld->HG > 0.01)
                        {
                            mWorld->HG -= 0.01;
                        }
                        fppCam->needUpdate = true;
                        testPos1 = Vector3(-1,-1,-1);
                        startDt = false;
                        dT = 0;
                        dET = 0;
                        chestId = -1;
                        dStd = -1;

                    }
                }
            }
            else
            {
                if (startDt != false)
                {
                    dT = 0;
                    dStd = -1;
                    startDt = false;
                    chestId = -1;
                }

            }
            }

            /// INVENTORY

            if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
            {
                //Craft item
                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
                    if(invEn == true)
                    {
                        for(int i = 0; i <= 3; i++)
                        {
                            if(craftSlotId[i] > 0)
                            {
                                Vector3 dropVelocity = Vector3(0,0,0);

                                dropVelocity.x = (cosf((fppCam->horAngle/180.0f)*PI))*4.0f;
                                dropVelocity.y = 2.0f;
                                dropVelocity.z = (sinf((fppCam->horAngle/180.0f)*PI))*4.0f;

                                if(craftSlotAm[i] > 0)
                                {
                                    mWorld->DropThisNoAlign(craftSlotId[i],craftSlotAm[i],craftSlotSt[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                    craftSlotAm[i] = -1;
                                    craftSlotSt[i] = 0;
                                    craftSlotId[i] = -1;
                                }
                            }
                        }
                        craftItemId = -1;
                        craftItemAm = -1;
                        craftItemSt = false;
                    }

                    if(craft3xEn == true)
                    {
                        for(int i = 0; i <= 8; i++)
                        {
                            if(craftSlotId3[i] > 0)
                            {
                                Vector3 dropVelocity = Vector3(0,0,0);

                                dropVelocity.x = (cosf((fppCam->horAngle/180.0f)*PI))*4.0f;
                                dropVelocity.y = 2.0f;
                                dropVelocity.z = (sinf((fppCam->horAngle/180.0f)*PI))*4.0f;

                                if(craftSlotAm3[i] > 0)
                                {
                                    mWorld->DropThisNoAlign(craftSlotId3[i],craftSlotAm3[i],craftSlotSt3[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                    craftSlotAm3[i] = -1;
                                    craftSlotSt3[i] = 0;
                                    craftSlotId3[i] = -1;
                                }
                            }
                        }
                        craftItemId3 = -1;
                        craftItemAm3 = -1;
                        craftItemSt3 = false;
                    }

                    if(upEn == true)
                    {
                        invXPosition = 0;
                        invYPosition = 0;
                    }
                    selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));

                    invEn = false;
                    craft3xEn = false;
                    furnaceEn = false;
                    chestEn = false;
                    upEn = false;
                    furnaceEn = false;
                    chestId = -1;

                    UseChest = 0;
                    UseFurnace = 0;
                    return;
                }

                if(keyPressed(InputHelper::Instance()->getButtonToAction(14))) // if you press R
                {
                    if(invEn == true) // if 2x craft menu is open
                    {
                        if(craftItemId != -1) // if craft cell is not empty
                        {
                            if(mWorld->mId == craftItemId) // if item in craft cell = item in your mouse
                            {
                                if(craftItemSt == 1) // if item in craft cell is stackble
                                {
                                    if(mWorld->mAm+craftItemAm <= 64) //if sum of item in you mouse and items in craft cell is lower or equal than 64
                                    {
                                        for(int i = 0; i <= 3; i++) // check items in craft menu
                                        {
                                            craftSlotAm[i] -= 1;
                                            if(craftSlotAm[i] == 0) // delete if 0
                                            {
                                                craftSlotId[i] = -1;
                                                craftSlotAm[i] = -1;
                                                craftSlotSt[i] = 0;
                                            }
                                        }

                                        mWorld->mAm += craftItemAm; // item in mouse ++
                                        mWorld->mainStatistics.itemsCrafted += craftItemAm;

                                        CraftItem2x2(); // repeat function because in craft menu we can lost items
                                    }
                                }
                            }

                            if(mWorld->mId == -1) //if you haven't mouse item
                            {
                                for(int i = 0; i <= 3; i++)
                                {
                                    craftSlotAm[i] -= 1;
                                    if(craftSlotAm[i] == 0)
                                    {
                                        craftSlotId[i] = -1;
                                        craftSlotAm[i] = -1;
                                        craftSlotSt[i] = 0;
                                    }
                                }
                                mWorld->mId = craftItemId; // mouse item id = id of craft cell item
                                mWorld->mAm = craftItemAm;
                                mWorld->mSt = craftItemSt;
                                mWorld->mainStatistics.itemsCrafted += craftItemAm;

                                CraftItem2x2();

                            }
                        }
                    }


                    if(furnaceEn == true)
                    {
                        if(UseFurnace->furnaceSlotId[2] != -1)
                        {
                            if(mWorld->mId == UseFurnace->furnaceSlotId[2])
                            {
                                if(UseFurnace->furnaceSlotSt[2] == 1)
                                {
                                    if(mWorld->mAm+UseFurnace->furnaceSlotAm[2] <= 64)
                                    {
                                        mWorld->mAm += UseFurnace->furnaceSlotAm[2];

                                        UseFurnace->furnaceSlotAm[2] = -1;
                                        UseFurnace->furnaceSlotId[2] = -1;
                                        UseFurnace->furnaceSlotSt[2] = 0;
                                    }
                                }
                            }

                            if(mWorld->mId == -1) //if you haven't mouse item
                            {
                                mWorld->mId = UseFurnace->furnaceSlotId[2];
                                mWorld->mAm = UseFurnace->furnaceSlotAm[2];
                                mWorld->mSt = UseFurnace->furnaceSlotSt[2];

                                UseFurnace->furnaceSlotId[2] = -1;
                                UseFurnace->furnaceSlotAm[2] = -1;
                                UseFurnace->furnaceSlotSt[2] = 0;
                            }
                        }
                    }


                    if(craft3xEn == true)
                    {
                        if(craftItemId3 != -1)
                        {

                            if(mWorld->mId == craftItemId3)
                            {
                                if(craftItemSt3 == 1)
                                {
                                    if(mWorld->mAm+craftItemAm3 <= 64)
                                    {
                                        for(int i = 0; i <= 8; i++)
                                        {
                                            craftSlotAm3[i] -= 1;
                                            if(craftSlotAm3[i] == 0)
                                            {
                                                craftSlotId3[i] = -1;
                                                craftSlotAm3[i] = -1;
                                                craftSlotSt3[i] = 0;
                                            }
                                        }

                                        mWorld->mAm += craftItemAm3;
                                        mWorld->mainStatistics.itemsCrafted += craftItemAm3;

                                        CraftItem3x3();
                                    }
                                }
                            }

                            if(mWorld->mId == -1)
                            {
                                for(int i = 0; i <= 8; i++)
                                {
                                    craftSlotAm3[i] -= 1;
                                    if(craftSlotAm3[i] == 0)
                                    {
                                        craftSlotId3[i] = -1;
                                        craftSlotAm3[i] = -1;
                                        craftSlotSt3[i] = 0;
                                    }
                                }
                                mWorld->mId = craftItemId3;
                                mWorld->mAm = craftItemAm3;
                                mWorld->mSt = craftItemSt3;
                                mWorld->mainStatistics.itemsCrafted += craftItemAm3;

                                CraftItem3x3();
                            }
                        }
                    }
                }

                //switch right
                if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
                {
                    if (upEn == 0) // if your mouse in neither of craft menus
                    {
                        if(armorEn == true)
                        {
                            invXPosition != 1 ? invXPosition ++ : invXPosition = 1;
                            selectInvSprite->SetPosition(96+(invXPosition * 108),28+(invYPosition * 72));
                        }
                        else
                        {
                            invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
                            selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                        }
                    }
                    else
                    {
                        if(invEn == 1)
                        {
                            invXPosition != 1 ? invXPosition ++ : invXPosition = 1;
                            selectInvSprite->SetPosition(276 + (invXPosition * 36),46+(invYPosition * 36));
                        }
                        if(craft3xEn == 1)
                        {
                            invXPosition != 2 ? invXPosition ++ : invXPosition = 2;
                            selectInvSprite->SetPosition(204 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                        if(chestEn == 1) // if it is in chest
                        {
                            invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
                            selectInvSprite->SetPosition(96 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                    }
                }

                //switch left
                if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
                {
                    if (upEn == 0) // not only craft but chest too
                    {
                        invXPosition != 0 ? invXPosition -- : invXPosition = 0;

                        selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));

                        if(armorEn == true)
                        {
                            selectInvSprite->SetPosition(96+(invXPosition * 108),28+(invYPosition * 72));
                        }
                    }
                    else
                    {
                        invXPosition != 0 ? invXPosition -- : invXPosition = 0;
                        if(invEn == 1)
                        {
                            selectInvSprite->SetPosition(276 + (invXPosition * 36),46+(invYPosition * 36));
                        }
                        if(craft3xEn == 1)
                        {
                            selectInvSprite->SetPosition(204 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                        if(chestEn == 1)
                        {
                            selectInvSprite->SetPosition(96 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                    }
                }

                //switch down
                if(keyPressed(InputHelper::Instance()->getButtonToAction(11)))
                {
                    if (upEn == 0)
                    {
                        if(armorEn == true)
                        {
                            invYPosition ++;
                            selectInvSprite->SetPosition(96+(invXPosition * 108),28+(invYPosition * 72));

                            if(invYPosition == 2)
                            {
                                if(invXPosition == 1)
                                {
                                    invXPosition = 3;
                                }
                                invYPosition = 0;
                                armorEn = false;

                                selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                            }
                        }
                        else
                        {
                            invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
                            selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                        }
                    }
                    else
                    {
                        if (invEn == 1) //if mouse in the down of menu
                        {
                            if (invYPosition == 1)
                            {
                                upEn = 0; // we go to standart inv menu
                                invYPosition = 0;
                                invXPosition = 5 + invXPosition;
                                selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                            selectInvSprite->SetPosition(276 + (invXPosition * 36),46+(invYPosition * 36));
                        }

                        if (craft3xEn == 1)
                        {
                            if (invYPosition == 2)
                            {
                                upEn = 0;
                                invYPosition = 0;
                                invXPosition = 3 + invXPosition;
                                selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                                return;
                            }
                            invYPosition != 2 ? invYPosition ++ : invYPosition = 2;
                            selectInvSprite->SetPosition(204 + (invXPosition * 36),26+(invYPosition * 36));
                        }

                        if (chestEn == 1)
                        {
                            if (invYPosition == 2)
                            {
                                upEn = 0;
                                invYPosition = 0;
                                selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 2;
                            selectInvSprite->SetPosition(96 + (invXPosition * 36),26+(invYPosition * 36));
                        }

                        if (furnaceEn == 1)
                        {
                            if (invYPosition == 1)
                            {
                                upEn = 0;
                                invYPosition = 0;
                                invXPosition = 3;
                                selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                            selectInvSprite->SetPosition(204 ,28+(invYPosition * 72));
                        }
                    }
                }

                //switch up
                if(keyPressed(InputHelper::Instance()->getButtonToAction(10)))
                {
                    if (upEn == 0)
                    {
                        if (invYPosition == 0)
                        {
                            if(invEn == 1)
                            {
                                if((invXPosition == 5 || invXPosition == 6) && armorEn == false)
                                {
                                    invXPosition -= 5;
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(276 + (invXPosition * 36),46+(invYPosition * 36));
                                    upEn = true;
                                }
                                if((invXPosition == 0 || invXPosition == 3) && armorEn == false && upEn == false)
                                {
                                    if(invXPosition == 3)
                                    {
                                        invXPosition = 1;
                                    }
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(96 + (invXPosition * 108),28+(invYPosition * 72));
                                    armorEn = true;
                                }
                            }
                            if(craft3xEn == 1)
                            {
                                if(invXPosition >= 3 && invXPosition <= 5)
                                {
                                    invXPosition -= 3;
                                    invYPosition = 2;
                                    selectInvSprite->SetPosition(204 + (invXPosition * 36),26+(invYPosition * 36));
                                    upEn = 1;
                                }
                            }
                            if(chestEn == 1)
                            {
                                invYPosition = 2;
                                selectInvSprite->SetPosition(96 + (invXPosition * 36),26+(invYPosition * 36));
                                upEn = 1;
                            }
                            if(furnaceEn == 1)
                            {
                                if(invXPosition == 3)
                                {
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(204,28+(invYPosition * 72));
                                    upEn = 1;
                                }
                            }
                            return;
                        }
                        invYPosition != 0 ? invYPosition -- : invYPosition = 0;
                        selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));

                        if(armorEn == true)
                        {
                            selectInvSprite->SetPosition(96 + (invXPosition * 108),28+(invYPosition * 72));
                        }
                    }
                    else
                    {
                        invYPosition != 0 ? invYPosition -- : invYPosition = 0;

                        if(invEn == 1)
                        {
                            selectInvSprite->SetPosition(276 + (invXPosition * 36),46+(invYPosition * 36));
                        }
                        if(craft3xEn == 1)
                        {
                            selectInvSprite->SetPosition(204 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                        if(chestEn == 1)
                        {
                            selectInvSprite->SetPosition(96 + (invXPosition * 36),26+(invYPosition * 36));
                        }
                        if(furnaceEn == 1)
                        {
                            selectInvSprite->SetPosition(204,28+(invYPosition * 72));
                        }
                    }
                }


                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
                    if (upEn == 0)
                    {
                        if(armorEn == false)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (mWorld->invId[invYPosition*9 + invXPosition] != -1)
                                {
                                    mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
                                    mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
                                    mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
                                    mWorld->invId[invYPosition*9 + invXPosition] = -1;
                                    mWorld->invAm[invYPosition*9 + invXPosition] = -1;
                                    mWorld->invSt[invYPosition*9 + invXPosition] = 0;
                                }
                            }
                            else
                            {
                                if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
                                {
                                    mWorld->invId[invYPosition*9 + invXPosition]=mWorld->mId;
                                    mWorld->invAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                                    mWorld->invSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }

                                if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                                {
                                    if(mWorld->invSt[invYPosition*9 + invXPosition] == 1)
                                    {
                                        if (mWorld->invAm[invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                                        {
                                            mWorld->invAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (mWorld->invAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                                            mWorld->invAm[invYPosition*9 + invXPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (mWorld->mId == -1)
                            {
                                if (mWorld->armorId[invYPosition*2 + invXPosition] != 324+invYPosition*2+invXPosition) // 324+invYPosition*2+invXPosition is an id of sample armor item
                                {
                                    mWorld->mId = mWorld->armorId[invYPosition*2 + invXPosition];
                                    mWorld->mAm = mWorld->armorAm[invYPosition*2 + invXPosition];
                                    mWorld->mSt = mWorld->armorSt[invYPosition*2 + invXPosition];
                                    mWorld->armorId[invYPosition*2 + invXPosition] = 324+invYPosition*2+invXPosition;
                                    mWorld->armorAm[invYPosition*2 + invXPosition] = -1;
                                    mWorld->armorSt[invYPosition*2 + invXPosition] = false;
                                }
                            }
                            else
                            {
                                if (mWorld->armorId[invYPosition*2 + invXPosition] == 324+invYPosition*2+invXPosition)
                                {
                                    if(mWorld->mId == 324+invYPosition*2+invXPosition+4 || mWorld->mId == 324+invYPosition*2+invXPosition+8 || mWorld->mId == 324+invYPosition*2+invXPosition+12 || mWorld->mId == 324+invYPosition*2+invXPosition+16 || mWorld->mId == 324+invYPosition*2+invXPosition+20) // crazy code monkey skill
                                    {
                                        mWorld->armorId[invYPosition*2 + invXPosition]=mWorld->mId;
                                        mWorld->armorAm[invYPosition*2 + invXPosition]=mWorld->mAm;
                                        mWorld->armorSt[invYPosition*2 + invXPosition]=mWorld->mSt;
                                        mWorld->mId = -1;
                                        mWorld->mAm = -1;
                                        mWorld->mSt = false;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (invEn == 1)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (craftSlotId[invYPosition*2 + invXPosition] != -1)
                                {
                                    mWorld->mId = craftSlotId[invYPosition*2 + invXPosition];
                                    mWorld->mAm = craftSlotAm[invYPosition*2 + invXPosition];
                                    mWorld->mSt = craftSlotSt[invYPosition*2 + invXPosition];
                                    craftSlotId[invYPosition*2 + invXPosition] = -1;
                                    craftSlotAm[invYPosition*2 + invXPosition] = -1;
                                    craftSlotSt[invYPosition*2 + invXPosition] = 0;
                                }
                            }
                            else
                            {
                                if (craftSlotId[invYPosition*2 + invXPosition] == -1)
                                {
                                    craftSlotId[invYPosition*2 + invXPosition]=mWorld->mId;
                                    craftSlotAm[invYPosition*2 + invXPosition]=mWorld->mAm;
                                    craftSlotSt[invYPosition*2 + invXPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }

                                if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                                {
                                    if(craftSlotSt[invYPosition*2 + invXPosition] == 1)
                                    {
                                    if (craftSlotAm[invYPosition*2 + invXPosition]+mWorld->mAm < 64)
                                    {
                                        craftSlotAm[invYPosition*2 + invXPosition]+=mWorld->mAm;
                                        mWorld->mId = -1;
                                        mWorld->mAm = -1;
                                        mWorld->mSt = 0;
                                    }
                                    else
                                    {
                                        mWorld->mAm = (craftSlotAm[invYPosition*2 + invXPosition] + mWorld->mAm) - 64;
                                        craftSlotAm[invYPosition*2 + invXPosition]=64;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mAm = -1;
                                            mWorld->mId = -1;
                                            mWorld->mSt = 0;
                                        }
                                    }
                                    }
                                }
                            }
                            CraftItem2x2();
                        }

                        if (craft3xEn == 1)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (craftSlotId3[invYPosition*3 + invXPosition] != -1)
                                {
                                    mWorld->mId = craftSlotId3[invYPosition*3 + invXPosition];
                                    mWorld->mAm = craftSlotAm3[invYPosition*3 + invXPosition];
                                    mWorld->mSt = craftSlotSt3[invYPosition*3 + invXPosition];
                                    craftSlotId3[invYPosition*3 + invXPosition] = -1;
                                    craftSlotAm3[invYPosition*3 + invXPosition] = -1;
                                    craftSlotSt3[invYPosition*3 + invXPosition] = 0;
                                }
                            }
                            else
                            {
                                if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
                                {
                                    craftSlotId3[invYPosition*3 + invXPosition]=mWorld->mId;
                                    craftSlotAm3[invYPosition*3 + invXPosition]=mWorld->mAm;
                                    craftSlotSt3[invYPosition*3 + invXPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }

                                if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                                {
                                    if(craftSlotSt3[invYPosition*3 + invXPosition] == 1)
                                    {
                                        if (craftSlotAm3[invYPosition*3 + invXPosition]+mWorld->mAm < 64)
                                        {
                                            craftSlotAm3[invYPosition*3 + invXPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (craftSlotAm3[invYPosition*3 + invXPosition] + mWorld->mAm) - 64;
                                            craftSlotAm3[invYPosition*3 + invXPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            CraftItem3x3();
                        }
                        //Chest
                        if (chestEn == 1)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] != -1)
                                {
                                    mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
                                    mWorld->mAm = UseChest->chestSlotAm[invYPosition*9 + invXPosition];
                                    mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];
                                    UseChest->chestSlotId[invYPosition*9 + invXPosition] = -1;
                                    UseChest->chestSlotAm[invYPosition*9 + invXPosition] = -1;
                                    UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 0;
                                }
                            }
                            else
                            {
                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                                {
                                    UseChest->chestSlotId[invYPosition*9 + invXPosition]=mWorld->mId;
                                    UseChest->chestSlotAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                                    UseChest->chestSlotSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }

                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                                {
                                    if(UseChest->chestSlotSt[invYPosition*9 + invXPosition] == 1)
                                    {
                                        if (UseChest->chestSlotAm[+invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                                        {
                                            UseChest->chestSlotAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (UseChest->chestSlotAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                                            UseChest->chestSlotAm[invYPosition*9 + invXPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        //furnace
                        if(furnaceEn == true)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (UseFurnace->furnaceSlotId[invYPosition] != -1)
                                {
                                    mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
                                    mWorld->mAm = UseFurnace->furnaceSlotAm[invYPosition];
                                    mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];
                                    UseFurnace->furnaceSlotId[invYPosition] = -1;
                                    UseFurnace->furnaceSlotAm[invYPosition] = -1;
                                    UseFurnace->furnaceSlotSt[invYPosition] = 0;
                                }
                            }
                            else
                            {
                                if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                                {
                                    UseFurnace->furnaceSlotId[invYPosition]=mWorld->mId;
                                    UseFurnace->furnaceSlotAm[invYPosition]=mWorld->mAm;
                                    UseFurnace->furnaceSlotSt[invYPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }

                                if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                                {
                                    if(UseFurnace->furnaceSlotSt[invYPosition] == 1)
                                    {
                                        if (UseFurnace->furnaceSlotAm[invYPosition]+mWorld->mAm < 64)
                                        {
                                            UseFurnace->furnaceSlotAm[invYPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (UseFurnace->furnaceSlotAm[invYPosition] + mWorld->mAm) - 64;
                                            UseFurnace->furnaceSlotAm[invYPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            CheckForFurnFuel(UseFurnace);
                            CheckForFurnWorking(UseFurnace);
                        }
                    }
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_SQUARE))
                {
                    if(mWorld->mSt == 1)
                    {
                        if (upEn == 0)
                        {
                            if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                            {
                                if (mWorld->invAm[invYPosition*9 + invXPosition] != 64)
                                {
                                    mWorld->invAm[invYPosition*9 + invXPosition] += 1;

                                    mWorld->mAm -= 1;

                                    if(mWorld->mAm == 0)
                                    {
                                        mWorld->mId = -1;
                                        mWorld->mAm = -1;
                                    }
                                }

                            }

                            if (mWorld->mId != -1)
                            {
                               if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
                               {
                                    mWorld->invId[invYPosition*9 + invXPosition] = mWorld->mId;
                                    mWorld->invAm[invYPosition*9 + invXPosition] = 1;
                                    mWorld->invSt[invYPosition*9 + invXPosition] = 1;

                                    mWorld->mAm -= 1;

                                    if(mWorld->mAm == 0)
                                    {
                                        mWorld->mId = -1;
                                        mWorld->mAm = -1;
                                        mWorld->mSt = 0;
                                    }
                                }
                            }
                        }
                        else
                        {
                            ///2x CRAFT
                            if (invEn == 1)
                            {
                                if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                                {
                                    if (craftSlotAm[invYPosition*2 + invXPosition] != 64)
                                    {
                                        craftSlotAm[invYPosition*2 + invXPosition] += 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                    }
                                }

                                if (mWorld->mId != -1)
                                {
                                   if (craftSlotId[invYPosition*2 + invXPosition] == -1)
                                   {
                                       craftSlotId[invYPosition*2 + invXPosition] = mWorld->mId;
                                       craftSlotAm[invYPosition*2 + invXPosition] = 1;
                                       craftSlotSt[invYPosition*2 + invXPosition] = 1;

                                       mWorld->mAm -= 1;

                                       if(mWorld->mAm == 0)
                                       {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                    }
                                }
                                CraftItem2x2();
                            }

                            ///CRAFT TABLE
                            if (craft3xEn == 1)
                            {
                                if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                                {
                                    if (craftSlotAm3[invYPosition*3 + invXPosition] != 64)
                                    {
                                        craftSlotAm3[invYPosition*3 + invXPosition] += 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                    }
                                }

                                if (mWorld->mId != -1)
                                {
                                   if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
                                   {
                                       craftSlotId3[invYPosition*3 + invXPosition] = mWorld->mId;
                                       craftSlotAm3[invYPosition*3 + invXPosition] = 1;
                                       craftSlotSt3[invYPosition*3 + invXPosition] = 1;

                                       mWorld->mAm -= 1;

                                       if(mWorld->mAm == 0)
                                       {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                       }
                                   }
                               }
                               CraftItem3x3();
                            }

                            ///CHEST
                            if (chestEn == 1)
                            {
                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                                {
                                    if (UseChest->chestSlotAm[invYPosition*9 + invXPosition] != 64)
                                    {
                                        UseChest->chestSlotAm[invYPosition*9 + invXPosition] += 1;

                                        mWorld->mAm -= 1;
                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                    }
                                }

                                if (mWorld->mId != -1)
                                {
                                    if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                                    {
                                        UseChest->chestSlotId[invYPosition*9 + invXPosition] = mWorld->mId;
                                        UseChest->chestSlotAm[invYPosition*9 + invXPosition] = 1;
                                        UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                    }
                                }
                            }
                            ///FURNACE
                            if (furnaceEn == 1)
                            {
                                if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                                {
                                    if (UseFurnace->furnaceSlotAm[invYPosition] != 64)
                                    {
                                        UseFurnace->furnaceSlotAm[invYPosition] += 1;

                                        mWorld->mAm -= 1;
                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                    }
                                }

                                if (mWorld->mId != -1)
                                {
                                    if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                                    {
                                        UseFurnace->furnaceSlotId[invYPosition] = mWorld->mId;
                                        UseFurnace->furnaceSlotAm[invYPosition] = 1;
                                        UseFurnace->furnaceSlotSt[invYPosition] = 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                    }
                                }
                                CheckForFurnFuel(UseFurnace);
                                CheckForFurnWorking(UseFurnace);
                            }
                        }
                    }
                }
            }
        }
        else if(menuState == 1) //menu state
        {
            //turn off menu with the same key
            if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
            {
                menuState = 0;
                menuOptions = false;
                optionsMenuPos = 0;
                selectPos = 0;
            }

            //menu keys
            if(menuOptions)
            {
                //up, down
                if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
                {
                    if(optionsMenuPos == 8 || optionsMenuPos == 0)
                    {
                        return;
                    }
                    optionsMenuPos--;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
                {
                    if(optionsMenuPos == 7 || optionsMenuPos == 15)
                    {
                        return;
                    }
                    optionsMenuPos++;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
                {
                    if(optionsMenuPos + 8 > 15)
                    {
                        return;
                    }
                    optionsMenuPos += 8;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
                {
                    if(optionsMenuPos - 8 < 0)
                    {
                        return;
                    }
                    optionsMenuPos -= 8;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
                {
                    if(optionsMenuPos == 0)
                    {
                        if (mWorld->mainOptions.fov <= 95)
                        {
                            mWorld->mainOptions.fov += 5;
                            mSoundMgr->PlayMenuSound();
                            mRender->fovv = mWorld->mainOptions.fov;
                            RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
                            skyLight->UpdateLightSource(mWorld->skyTime);
                            skyMoonLight->UpdateLightSource(mWorld->skyTime);
                        }
                    }
                    if(optionsMenuPos == 1)
                    {
                        if (mWorld->mainOptions.horizontalViewDistance != 4)
                        {
                            mWorld->mainOptions.horizontalViewDistance += 1;
                            mSoundMgr->PlayMenuSound();
                            mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                            fppCam->needUpdate = true;
                        }
                    }
                    if(optionsMenuPos == 8)
                    {
                        if (mWorld->mainOptions.verticalViewDistance != 2)
                        {
                            mWorld->mainOptions.verticalViewDistance += 1;
                            mSoundMgr->PlayMenuSound();
                            mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                            fppCam->needUpdate = true;
                        }
                    }
                    if(optionsMenuPos == 9)
                    {
                        mWorld->mainOptions.difficult += 1;
                        mSoundMgr->PlayMenuSound();

                        if(mWorld->mainOptions.difficult > 3)
                        {
                            mWorld->mainOptions.difficult = 0;
                        }
                    }
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
                {
                    if(optionsMenuPos == 0)
                    {
                        if (mWorld->mainOptions.fov >= 45)
                        {
                            mWorld->mainOptions.fov -= 5;
                            mSoundMgr->PlayMenuSound();
                            mRender->fovv = mWorld->mainOptions.fov;
                            RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
                            skyLight->UpdateLightSource(mWorld->skyTime);
                            skyMoonLight->UpdateLightSource(mWorld->skyTime);
                        }
                    }
                    if(optionsMenuPos == 1)
                    {
                        if (mWorld->mainOptions.horizontalViewDistance != 1)
                        {
                            mWorld->mainOptions.horizontalViewDistance -= 1;
                            mSoundMgr->PlayMenuSound();
                            mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                            fppCam->needUpdate = true;
                        }
                    }
                    if(optionsMenuPos == 8)
                    {
                        if (mWorld->mainOptions.verticalViewDistance != 1)
                        {
                            mWorld->mainOptions.verticalViewDistance -= 1;
                            mSoundMgr->PlayMenuSound();
                            mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                            fppCam->needUpdate = true;
                        }
                    }
                    if(optionsMenuPos == 9)
                    {
                        mWorld->mainOptions.difficult -= 1;
                        mSoundMgr->PlayMenuSound();

                        if(mWorld->mainOptions.difficult < 0)
                        {
                            mWorld->mainOptions.difficult = 3;
                        }
                    }
                }

                //back
                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
                    selectPos = 0;
                    menuOptions = false;
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
                    //fog rendering
                    if(optionsMenuPos == 2)
                    {
                         mWorld->mainOptions.fogRendering = !mWorld->mainOptions.fogRendering;
                         mSoundMgr->PlayMenuSound();
                    }

                    //clouds rendering
                    if(optionsMenuPos == 3)
                    {
                         mWorld->mainOptions.cloudsRender = !mWorld->mainOptions.cloudsRender;
                         mSoundMgr->PlayMenuSound();
                    }

                    //fast rendering
                    if(optionsMenuPos == 4)
                    {
                         mWorld->mainOptions.fastRendering = !mWorld->mainOptions.fastRendering;
                         mSoundMgr->PlayMenuSound();

                         mWorld->rebuildVisibleChunks();
                         mWorld->rebuildVisibleTransperentChunks();
                    }

                    if(optionsMenuPos == 7)
                    {
                         mWorld->mainOptions.fakeShadowsRendering = !mWorld->mainOptions.fakeShadowsRendering;
                         mSoundMgr->PlayMenuSound();

                         mWorld->rebuildVisibleChunks();
                         mWorld->rebuildVisibleTransperentChunks();
                    }

                    //block animation
                    if(optionsMenuPos == 5)
                    {
                         mWorld->mainOptions.worldBlockAnimation = !mWorld->mainOptions.worldBlockAnimation;
                         mSoundMgr->PlayMenuSound();
                    }

                    //head bob
                    if(optionsMenuPos == 6)
                    {
                         mWorld->mainOptions.headBob = !mWorld->mainOptions.headBob;
                         bobCycle = 0.0f;
                         mSoundMgr->PlayMenuSound();
                    }

                    if(optionsMenuPos == 10)
                    {
                         mWorld->mainOptions.sunMoodRendering = !mWorld->mainOptions.sunMoodRendering;
                         mSoundMgr->PlayMenuSound();
                    }

                    if(optionsMenuPos == 11)
                    {
                         mWorld->mainOptions.guiDrawing = !mWorld->mainOptions.guiDrawing;
                         mSoundMgr->PlayMenuSound();
                    }

                    if(optionsMenuPos == 12)
                    {
                         mWorld->mainOptions.sounds = !mWorld->mainOptions.sounds;
                         mSoundMgr->PlayMenuSound();
                         mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
                    }

                    //take screenshot
                    if(optionsMenuPos == 13)
                        makeScreen = true;

                    //rename
                    if(optionsMenuPos == 14)
                    {
                        unsigned short test[128];
                        unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                        if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                        {
                            std::string newWorldName = "";
                            for(int j = 0; test[j]; j++)
                            {
                                unsigned c = test[j];

                                if(32 <= c && c <= 127) // print ascii only
                                    newWorldName += c;
                            }

                            sprintf(mWorld->worldName,"%s",newWorldName.c_str());
                        }
                    }

                    if(optionsMenuPos == 15)
                    {
                        devMode = !devMode;
                    }
                }
            }
            else
            {
                //up, down
                if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
                {
                    selectPos--;
                    if(selectPos < 0)
                        selectPos = 5;

                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
                {
                    selectPos++;
                    if(selectPos > 5)
                        selectPos = 0;

                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
                    menuState = 0;
                    selectPos = 0;
                    optionsMenuPos = 0;
                    menuOptions = false;
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
                    if(selectPos == 0)//resume
                    {
                        menuState = 0;
                    }
                    if(selectPos == 1)//options
                    {
                        optionsMenuPos = 0;
                        menuOptions = true;
                    }
                    if(selectPos == 2)//options
                    {
                        menuState = 3;
                        selectPos = 0;
                    }
                    if(selectPos == 3)//save
                    {
                        //mWorld->sunTime = sunTime;
                        mWorld->SaveCompressedWorld(saveFileName.c_str());
                        menuState = 0;
                    }
                    if(selectPos == 4)//save end exit
                    {
                        //save
                        //mWorld->sunTime = sunTime;
                        mWorld->SaveCompressedWorld(saveFileName.c_str());
                        sManager->PopState();
                    }
                    if(selectPos == 5)//exit
                    {
                        //exit
                        sManager->PopState();
                    }
                }
            }
        }
        if (menuState == 3)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 0;
                menuState = 1;
            }
            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                statisticsPage += 1;
                if(statisticsPage == 2)
                {
                    statisticsPage = 0;
                }
            }
            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                statisticsPage -= 1;
                if(statisticsPage == -1)
                {
                    statisticsPage = 1;
                }
            }
        }
    }
    if(mWorld->HP <= 0)
    {
        if(dieFactor == 1)
        {
            for(int i = 0; i < 36; i++)
            {
                if(i <= 3) // drop armor items
                {
                    if(mWorld->armorId[i] != 324 + i)
                    {
                        Vector3 dropVelocity = Vector3(0,0,0);

                        dropVelocity.x = (-15+rand()%30)*0.1f;
                        dropVelocity.y = 3.0f;
                        dropVelocity.z = (-15+rand()%30)*0.1f;

                        mWorld->DropThisNoAlign(mWorld->armorId[i],mWorld->armorAm[i],mWorld->armorSt[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                        mWorld->armorAm[i] = -1;
                        mWorld->armorSt[i] = 0;
                        mWorld->armorId[i] = -1;
                    }
                }
                if(mWorld->invId[i] > 0)
                {
                    Vector3 dropVelocity = Vector3(0,0,0);

                    dropVelocity.x = (-15+rand()%30)*0.1f;
                    dropVelocity.y = 3.0f;
                    dropVelocity.z = (-15+rand()%30)*0.1f;

                    if(mWorld->invAm[i] > 0)
                    {
                        mWorld->DropThisNoAlign(mWorld->invId[i],mWorld->invAm[i],mWorld->invSt[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                        mWorld->invAm[i] = -1;
                        mWorld->invSt[i] = 0;
                        mWorld->invId[i] = -1;
                    }
                }
            }

            mWorld->mainStatistics.dies += 1;
            dieFactor = 0;
        }
        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(mWorld->gameModeWorld == 2)
            {
                mWorld->gameLocked = true;
                mWorld->SaveCompressedWorld(saveFileName.c_str());

                std::string fileName = saveFileName;
                remove(fileName.c_str());
                fileName = fileName + "c";
                remove(fileName.c_str());

                sManager->PopState();
            }
            else
            {
                playerPosition.x = newPlayerPos.x;
                playerPosition.y = newPlayerPos.y;
                playerPosition.z = newPlayerPos.z;

                mWorld->UpdatePlayerZoneBB(playerPosition);	//Move player back to original spawn point
                fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
                //fppCam->RotateView(0,0,90,0);
                fppCam->upDownAngle = 0;
                fppCam->horAngle = 0;
                mWorld->HP = 20;
                mWorld->HG = 20;
                dieFactor = 1;
            }
        }
    }
}


void StatePlay::Update(StateManager* sManager)
{
    if(mWorld->armorAm[0] <= 0)
    {
        mWorld->armorId[0] = 324;
        mWorld->armorAm[0] = -1;
        mWorld->armorSt[0] = false;
    }
    if(mWorld->armorAm[1] <= 0)
    {
        mWorld->armorId[1] = 325;
        mWorld->armorAm[1] = -1;
        mWorld->armorSt[1] = false;
    }
    if(mWorld->armorAm[2] <= 0)
    {
        mWorld->armorId[2] = 326;
        mWorld->armorAm[2] = -1;
        mWorld->armorSt[2] = false;
    }
    if(mWorld->armorAm[3] <= 0)
    {
        mWorld->armorId[3] = 327;
        mWorld->armorAm[3] = -1;
        mWorld->armorSt[3] = false;
    }

    mWorld->AP = 0.0f;
    switch(mWorld->armorId[0])
    {
       case 328 : mWorld->AP += 1.0f; break;
       case 332 : mWorld->AP += 2.0f; break;
       case 336 : mWorld->AP += 2.0f; break;
       case 340 : mWorld->AP += 3.0f; break;
       case 344 : mWorld->AP += 2.0f; break;
    }
    switch(mWorld->armorId[1])
    {
       case 329 : mWorld->AP += 3.0f; break;
       case 333 : mWorld->AP += 5.0f; break;
       case 337 : mWorld->AP += 6.0f; break;
       case 341 : mWorld->AP += 8.0f; break;
       case 345 : mWorld->AP += 5.0f; break;
    }
    switch(mWorld->armorId[2])
    {
       case 330 : mWorld->AP += 2.0f; break;
       case 334 : mWorld->AP += 4.0f; break;
       case 338 : mWorld->AP += 5.0f; break;
       case 342 : mWorld->AP += 6.0f; break;
       case 346 : mWorld->AP += 3.0f; break;
    }
    switch(mWorld->armorId[3])
    {
       case 331 : mWorld->AP += 1.0f; break;
       case 335 : mWorld->AP += 1.0f; break;
       case 339 : mWorld->AP += 2.0f; break;
       case 343 : mWorld->AP += 3.0f; break;
       case 347 : mWorld->AP += 1.0f; break;
    }

    if(menuState == 0)//game state
    {
        cubeLight = mWorld->BlockFinalLight(playerPosition.x,playerPosition.y-1,playerPosition.z) * 1.2f;
        if(cubeLight > 1.0f)
        {
            cubeLight = 1.0f;
        }

        furnaceTimes += dt;
        if(furnaceTimes >= 1.0f)
        {
            if(mWorld->mFurnaces.size() > 0)
            {
                for(unsigned int i = 0; i < mWorld->mFurnaces.size(); i ++)
                {
                    Furnace* WorkingFurance = mWorld->mFurnaces[i];

                    if(WorkingFurance->fuelTime > 0)
                    {
                        WorkingFurance->fuelTime -= 1;
                        if(mWorld->GetBlock(WorkingFurance->furnaceX, WorkingFurance->furnaceY, WorkingFurance->furnaceZ) == 106)
                        {
                            Vector3 testPos5 = Vector3(-1,-1,-1);
                            int chunkTarget2 = -1;

                            testPos5.x = WorkingFurance->furnaceX;
                            testPos5.y = WorkingFurance->furnaceY;
                            testPos5.z = WorkingFurance->furnaceZ;
                            chunkTarget2 = mWorld->getChunkId(testPos5);

                            mWorld->GetBlock(WorkingFurance->furnaceX, WorkingFurance->furnaceY, WorkingFurance->furnaceZ) = 107;

                            mWorld->SetLigtSourcePosition(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ,107);
                            mWorld->UpdateLightAreaIn(testPos5);

                            mWorld->rebuildChunk(chunkTarget2);
                            mWorld->rebuildTransparentChunk(chunkTarget2);
                            mWorld->rebuildNearestChunksForLight(chunkTarget2,testPos5);

                            fppCam->needUpdate = true;
                        }
                    }

                    if(WorkingFurance->fuelTime <= 0)
                    {
                        WorkingFurance->fuelTime = 0.0f;
                        CheckForFurnFuel(WorkingFurance);
                    }

                    if(WorkingFurance->fuelTime <= 0)
                    {
                        if(mWorld->GetBlock(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ) == 107)
                        {
                            Vector3 testPos5 = Vector3(-1,-1,-1);
                            int chunkTarget2 = -1;

                            testPos5.x = WorkingFurance->furnaceX;
                            testPos5.y = WorkingFurance->furnaceY;
                            testPos5.z = WorkingFurance->furnaceZ;
                            chunkTarget2 = mWorld->getChunkId(testPos5);

                            mWorld->GetBlock(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ) = 106;

                            mWorld->RemoveLigtSourceAtPosition(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ,107);

                            mWorld->UpdateLightAreaIn(testPos5);

                            mWorld->rebuildChunk(chunkTarget2);
                            mWorld->rebuildTransparentChunk(chunkTarget2);
                            mWorld->rebuildNearestChunksForLight(chunkTarget2,testPos5);

                            fppCam->needUpdate = true;
                        }
                    }

                    if(WorkingFurance->fuelTime > 0 && WorkingFurance->working == 1)
                    {
                        WorkingFurance->meltingTime += 1;
                        if(WorkingFurance->meltingTime >= 10)
                        {
                            WorkingFurance->meltingTime = 0;
                            WorkingFurance->working = 0;

                            ReadyFurnSmelting(WorkingFurance);
                            CheckForFurnWorking(WorkingFurance);
                        }
                    }
                }
            }
            furnaceTimes = 0.0f;
        }

        cloudsWay == 0 ? cloudsMove += 0.01 : cloudsMove -= 0.01;
        if(cloudsWay == 0)
        {
            if(cloudsMove > 150)
            {
                cloudsWay = 1;
            }
        }
        else
        {
            if(cloudsMove < -150)
            {
                cloudsWay = 0;
            }
        }

        if (mWorld->skyTime >= 101 && mWorld->skyTime < 200)
        {
            if (mWorld->brightFactor < 1)
            {
                mWorld->brightFactor += 0.0001f;
            }
        }

        if (mWorld->skyTime >= 255)
        {
            if (mWorld->brightFactor > 0.001f)
            {
                mWorld->brightFactor -= 0.0001f;
            }
        }

        if (mWorld->skyTime >= 101 && mWorld->skyTime <= 116)
        {
            mWorld->dawnSunsetFactor = (mWorld->skyTime - 101)/18.0f;
        }
        if (mWorld->skyTime >= 119 && mWorld->skyTime <= 134)
        {
            mWorld->dawnSunsetFactor = (134 - mWorld->skyTime)/18.0f;
        }
        if (mWorld->skyTime > 134 && mWorld->skyTime < 240 )
        {
            mWorld->dawnSunsetFactor = 0.0f;
        }

        if (mWorld->skyTime >= 278 && mWorld->skyTime <= 293)
        {
            mWorld->dawnSunsetFactor = (mWorld->skyTime - 278)/18.0f;
        }
        if (mWorld->skyTime >= 297 && mWorld->skyTime <= 316)
        {
            mWorld->dawnSunsetFactor = (316 - mWorld->skyTime)/18.0f;
        }
        if (mWorld->skyTime > 316)
        {
            mWorld->dawnSunsetFactor = 0.0f;
        }

        if (anim[0] == 1)
        {
            if (changeY >= 0.0f)
            {
                anim[0] = 0;
                changeY = 0.0f;
            }
            if (changeY < 0.2f)
            {
                changeY += 0.02f;
            }
        }

        {
            tickChunk < 15 ? tickChunk += dt : tickChunk = 0;

            if (tickChunk > 14)
            {
                chunkId = mWorld->getChunkId(playerPosition);
                mWorld->UpdateChunkBlocks(chunkId);
                mWorld->rebuildChunk(chunkId);
                mWorld->rebuildTransparentChunk(chunkId);
                tickChunk = 0;
            }
        }

        {
            tickHunger += dt;
            if(tickHunger >= 79)
            {
                HungerTime();
                tickHunger = 0;
            }

            tickHealth += dt;
            if(tickHealth >= 5)
            {
                HealthTime();
                tickHealth = 0;
            }


            if (hurt_time > 0)
            {
                hurt_time -= dt;
            }
            if (hurt_time <= 0)
            {
                hurt = false;
            }

            if(tickOS >= 1 && headInWater == 1)
            {
                OxygenTime();
                tickOS = 0;
            }

            if (headInWater == 0)
            {
                if (mWorld->OS != 10)
                {
                    mWorld->OS = 10;
                }
                tickOS = 0;
            }
            else
            {
                tickOS += dt;
            }
        }

        if(animGo == true)
        {
            if(animDest < PI)
            {
                animDest += PI/animSpeed;
            }
            if(animDest >= PI)
            {
                animGo = false;
                animDest = 0;
            }
        }

        if(fppCam->needUpdate)
        {
            showCube = false;

            //show pick cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we take position and view vector
            Vector3 testPos ;

            // collider
            BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
            BoundingBox testBox = BoundingBox(testPos.x+collider.min.x, testPos.y+collider.min.y, testPos.z+collider.min.z, testPos.x+collider.max.x, testPos.y+collider.max.y, testPos.z+collider.max.z);

            //moving slowly to the target
            for(float i = 0; i < 5.25f; i+=0.15f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);

                collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
                testBox = BoundingBox(floorf(testPos.x)+0.5f+collider.min.x, floorf(testPos.y)+0.5f+collider.min.y, floorf(testPos.z)+0.5f+collider.min.z, floorf(testPos.x)+0.5f+collider.max.x, floorf(testPos.y)+0.5f+collider.max.y, floorf(testPos.z)+0.5f+collider.max.z);

                //check if we touching something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z) && testBox.contains(testPos) == true)
                {
                    //if yes then show pick cube
                    cubePos.x = (int)testPos.x + 0.5f;
                    cubePos.y = (int)testPos.y + 0.5f;
                    cubePos.z = (int)testPos.z + 0.5f;

                    showCube = true;
                    break;
                }
            }
        }

        int soundBlockType = -1;

        //RenderManager::InstancePtr()

        //update player position
        if(dt < 0.1f)
        {

            Vector3 delta = fppCam->m_vView - fppCam->m_vPosition;
            playerPosition = fppCam->m_vPosition;

            //gravity
            Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
            Vector3 legsPosition = playerPosition + Vector3(0.0f, -1.0f, 0.0f);
            Vector3 headPosition = playerPosition + Vector3(0.0f, 0.1f, 0.0f);

            //foot in water
            if(mWorld->PlayerInWater(legsPosition))
                footInWater = true;
            else
                footInWater = false;

            //check if head is is in the water
            //check if head is is in the water
            if(mWorld->PlayerInWater(headPosition))
            {
                //change gravity
                if (playerVelocity.y > -1.75)
                {
                    playerVelocity.y += (GRAVITY/3.0f) * dt;
                }
                else
                {
                    playerVelocity.y = -1.75;
                }
                if(playerVelocity.y > 2.0f)
                {
                    playerVelocity.y -= 0.1f;
                    if(playerVelocity.y < 2.15f)
                    {
                        playerVelocity.y = 2.0f;
                    }
                }

                headInWater = true;
            }
            else
            {
                headInWater = false;
                playerVelocity.y += (GRAVITY*1.3 * dt) * 1.6f;
            }

            if(mWorld->PlayerInLava(legsPosition))
            {
                footInLava = true;
                mWorld->HP -= 0.5f;


            }
            else
            {
                footInLava = false;
            }

            //check if head is is in the Lava
            if(mWorld->PlayerInLava(headPosition))
            {
                //change gravity
                playerVelocity.y += (GRAVITY/3.0f) * dt;
                headInLava = true;
                mWorld->HP -= 1;
            }
            else
            {
                headInLava = false;
                playerVelocity.y += GRAVITY * dt;
            }

            //check if we are standing on ground
            if(mWorld->SolidAtPointForPlayer(footPosition) || mWorld->SolidAtPointForPlayer(headPosition))
            {
                walkingOnGround = true;
                soundBlockType = mWorld->BlockSoundAtPos(footPosition);

                // If the player has their head stuck in a block, push them down.
                if (mWorld->SolidAtPointForPlayer(headPosition))
                {
                    int blockIn = (int)(headPosition.y);
                    playerPosition.y = (float)(blockIn - 0.105f); //0.15
                }

                // If the player is stuck in the ground, bring them out.
                // This happens because we're standing on a block at -1.5, but stuck in it at -1.4, so -1.45 is the sweet spot.
                if (mWorld->SolidAtPointForPlayer(footPosition))
                {
                    int blockOn = (int)(footPosition.y);
                    playerPosition.y = (float)(blockOn + 1 + 1.6f);
                }

                if(playerVelocity.y != 0.0f) /// FALL DAMAGE
                {
                    if (!mWorld->PlayerInWater(footPosition) && mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) != 87 && mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) != 88 && mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) != 89 && mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) != 90)
                    {
                        if(playerVelocity.y < -12 && playerVelocity.y > -19)
                        {
                            mSoundMgr->PlayFallSound(playerVelocity.y);
                            HurtPlayer((playerVelocity.y*-1 - 11) / 1.4);

                            if(mWorld->HG > 0.2)
                            {
                                mWorld->HG -= 0.2;
                            }
                            mWorld->mainStatistics.badlyFalls += 1;

                            if(mWorld->armorId[3] != 327) // if we have boots
                            {
                                mWorld->armorAm[3] -= 2;
                            }
                        }
                        if(playerVelocity.y < -19)
                        {
                            mSoundMgr->PlayFallSound(playerVelocity.y);
                            HurtPlayer((playerVelocity.y*-1 - 11) * 1.3f);

                            if(mWorld->HG > 0.3)
                            {
                                mWorld->HG -= 0.3;
                            }
                            mWorld->mainStatistics.badlyFalls += 1;

                            if(mWorld->armorId[3] != 327) // if we have boots
                            {
                                mWorld->armorAm[3] -= 6;
                            }
                        }
                    }
                }
                playerVelocity.y = 0.0f;

                //dodatkowa logika podczas stania na klocku
                //jump
                if(jumping)
                {
                    playerVelocity.y = 1.45f * JUMPVELOCITY;
                    jumping = false;
                    walkingOnGround = false;
                }

                if(mWorld->kickedStart) // if you damaged by zombie
                {
                    mWorld->kickedStart = false;
                    walkingOnGround = false;
                    playerVelocity.y = 0.9f * JUMPVELOCITY;
                    mWorld->kickedTimer = 0.5f;

                    switch(mWorld->mainOptions.difficult)
                    {
                    case 0: // peaceful
                        HurtPlayer(0);
                    break;
                    case 1: // easy
                        HurtPlayer(2);

                        if(mWorld->armorId[0] != 324)
                        {
                            mWorld->armorAm[0] -= 1+rand()%3;
                        }
                        if(mWorld->armorId[1] != 325)
                        {
                            mWorld->armorAm[1] -= 1+rand()%3;
                        }
                        if(mWorld->armorId[2] != 326)
                        {
                            mWorld->armorAm[2] -= 1+rand()%2;
                        }
                        if(mWorld->armorId[3] != 327)
                        {
                            mWorld->armorAm[3] -= rand()%3;
                        }
                    break;
                    case 2: // normal
                        HurtPlayer(3);

                        if(mWorld->armorId[0] != 324)
                        {
                            mWorld->armorAm[0] -= 1+rand()%3;
                        }
                        if(mWorld->armorId[1] != 325)
                        {
                            mWorld->armorAm[1] -= 1+rand()%4;
                        }
                        if(mWorld->armorId[2] != 326)
                        {
                            mWorld->armorAm[2] -= 1+rand()%3;
                        }
                        if(mWorld->armorId[3] != 327)
                        {
                            mWorld->armorAm[3] -= rand()%3;
                        }
                    break;
                    case 3: // hard
                        HurtPlayer(4);

                        if(mWorld->armorId[0] != 324)
                        {
                            mWorld->armorAm[0] -= 1+rand()%4;
                        }
                        if(mWorld->armorId[1] != 325)
                        {
                            mWorld->armorAm[1] -= 1+rand()%5;
                        }
                        if(mWorld->armorId[2] != 326)
                        {
                            mWorld->armorAm[2] -= 1+rand()%4;
                        }
                        if(mWorld->armorId[3] != 327)
                        {
                            mWorld->armorAm[3] -= rand()%4;
                        }
                    break;
                    }
                }
            }
            else
            {
                walkingOnGround = false;
            }

            //update position
            if(!canFly)
                playerPosition += playerVelocity * dt;
            else
                playerVelocity.y = 0.0f;


            //collision with walls
            isWalking = false;
            Vector3 moveVector = fppCam->m_vVelocity;

            jumping = false;
            if(moveVector.x != 0.0f || moveVector.z != 0.0f)
            {
                if(TryToMove(moveVector,dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(0,0,moveVector.z),dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(moveVector.x,0,0),dt))
                {
                    isWalking = true;
                }
            }

            if(mWorld->kickedTimer > 0.0f)
            {
                mWorld->kickedTimer -= dt;
                TryToMove(Vector3(sinf(mWorld->kickedAngle)*0.1,0,cosf(mWorld->kickedAngle))*0.1,dt);
            }
            else
            {
                mWorld->kickedTimer = 0.0f;
                mWorld->kickedAngle = 0.0f;
            }


            //update camera
            fppCam->m_vPosition = playerPosition;
            fppCam->m_vView = fppCam->m_vPosition + delta;
            fppCam->m_vVelocity = Vector3(0,0,0);
            fppCam->needUpdate = true;
        }

        if(fppCam->needUpdate)
        {
            mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
        }

        //walking sound
       if(isWalking && walkingOnGround && (!footInWater || !footInLava))
		{
			if(walkSoundAccu > 0.5f || walkSoundAccu == 0.0f)
			{
				mSoundMgr->PlayWalkSound(soundBlockType);
				walkSoundAccu = 0.0f;
			}
			walkSoundAccu += dt;

			if(mWorld->mainOptions.headBob == 1)
			{
			    if(bobType == 0)
                {
                    if (bobCycle < 3.14)
                    {
                        bobCycle += 3.14/20;
                    }
                    else
                    {
                        bobType = 1;
                    }
                }
                else
                {
                    if (bobCycle > 0)
                    {
                        bobCycle -= 3.14/20;
                    }
                    else
                    {
                        bobType = 0;
                    }
                }

                float bobSine = sinf(bobCycle - (3.14/2) + 3.14)/3;
                float bobCose = cosf(bobCycle - (3.14/2) + 3.14)/3;

                //fppCam->m_vOffset = Vector3(0.02f*bobSine,0.02f*bobCose,0.0f);
			}

		}
		else
		{
			walkSoundAccu = 0.0f;
			fppCam->m_vOffset = Vector3(0.0f,0.0f,0.0f);
            if(bobCycle > 3.14/2)
            {
                bobCycle -= (bobCycle-(3.14/2))/3;
            }
            else
            {
                bobCycle += ((3.14/2) - bobCycle) / 3;
            }
		}
        mWorld->UpdateWorldTime(dt);
        skyLight->UpdateLightSource(mWorld->skyTime);
    }
}


void StatePlay::Draw(StateManager* sManager)
{
    mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0x00000200);

    if (mWorld->skyTime < 180)
    {
        if(fppCam->horAngle <= 359 && fppCam->horAngle >= 239)
        {
            angleFactor = (fppCam->horAngle - 239)/120.0f;
        }
        if(fppCam->horAngle >= 0 && fppCam->horAngle <= 120)
        {
            angleFactor = (120 - fppCam->horAngle)/120.0f;
        }
    }
    else
    {
        if(fppCam->horAngle <= 180 && fppCam->horAngle >= 60)
        {
            angleFactor = (fppCam->horAngle - 60)/120.0f;
        }
        if(fppCam->horAngle > 180 && fppCam->horAngle <= 300)
        {
            angleFactor = (300 - fppCam->horAngle)/120.0f;
        }
    }
    if(angleFactor < 0.0f)
    {
        angleFactor = 0.0f;
    }
    if(angleFactor > 1.0f)
    {
        angleFactor = 1.0f;
    }
	//start rendering*mWorld->bright
	bool needUpdate = fppCam->needUpdate;
	mRender->StartFrame(0.5,0.662,1);

    /// Skybox rendering
	{
	    MatrixColor(0xFFFFFFFF);

        MatrixPush();
        MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

        if(playerPosition.y <= 70)
        {
            skyBox->Update(((mWorld->startSkyColor*mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f), mWorld->endSkyColor*mWorld->brightFactor*(playerPosition.y/70.0f));
        }
        else
        {
            skyBox->Update((mWorld->startSkyColor*mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor), mWorld->endSkyColor*mWorld->brightFactor);
        }

        skyBox->Render();
		MatrixPop();
	}

    /* /// Stars renderingsceGuDisable(GU_DEPTH_TEST);
    if(mWorld->brightFactor < 0.6f)
	{
	    MatrixColor(0xFFFFFFFF);

        MatrixPush();
		MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

		TextureManager::Instance()->SetTextureModeulate(stars);

        starsBox->Update(1.0f-(mWorld->brightFactor*2));
		starsBox->Render();
		MatrixPop();
	}*/

    /// Sun/moon rendering
    if(mWorld->mainOptions.sunMoodRendering == 1)
    {
        MatrixColor(0xFFFFFFFF);

        // sun
		MatrixPush();
        MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

        TextureManager::Instance()->SetTextureModeulate(suntex);

        skyLight->Render();
		MatrixPop();

		// moon
		MatrixPush();
		MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

        TextureManager::Instance()->SetTextureModeulate(moontex);

        skyMoonLight->UpdateLightSource(mWorld->skyTime+180.0f);
        skyMoonLight->Render();
		MatrixPop();
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        if(headInWater == true)
        {
            sceGuFog(0.0f, 15.0f, GU_COLOR(74.0f/255.0f*mWorld->brightFactor*0.6,130.0f/255.0f*mWorld->brightFactor*0.6,158.0f/255.0f*mWorld->brightFactor*0.6, 1.0f));
        }
        else
        {
            if(playerPosition.y <= 70)
            {
                sceGuFog(20.0f, mWorld->mainOptions.horizontalViewDistance * 20 + 80.0f, GU_COLOR((( (mWorld->startSkyColor.x+mWorld->endSkyColor.x)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.x*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),(( (mWorld->startSkyColor.y+mWorld->endSkyColor.y)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.y*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),(( (mWorld->startSkyColor.z+mWorld->endSkyColor.z)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.z*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),1.0f));	// Fog parameters 100.75
            }
            else
            {
                sceGuFog(20.0f, mWorld->mainOptions.horizontalViewDistance * 20 + 80.0f, GU_COLOR(( (mWorld->startSkyColor.x+mWorld->endSkyColor.x)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.x*mWorld->dawnSunsetFactor*angleFactor),( (mWorld->startSkyColor.y+mWorld->endSkyColor.y)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.y*mWorld->dawnSunsetFactor*angleFactor),( (mWorld->startSkyColor.z+mWorld->endSkyColor.z)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.z*mWorld->dawnSunsetFactor*angleFactor),1.0f));	// Fog parameters 100.75
            }
        }
        sceGuEnable(GU_FOG);
    }

    /// Clouds rendering
    if(mWorld->mainOptions.cloudsRender == 1)
    {
        MatrixPush();

        MatrixColor(GU_COLOR(mWorld->brightFactor,mWorld->brightFactor,mWorld->brightFactor,1));
		MatrixTranslation(Vector3(-180+cloudsMove,112,-180));

		TextureManager::Instance()->SetTextureModeulate(cloudsTex);

		mWorld->drawClouds();

		MatrixPop();
        MatrixColor(0xFFFFFFFF);
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuDisable(GU_FOG);
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        if(headInWater == true)
        {
            sceGuFog(0.0f, 15.0f, GU_COLOR(74.0f/255.0f*mWorld->brightFactor*0.6,130.0f/255.0f*mWorld->brightFactor*0.6,158.0f/255.0f*mWorld->brightFactor*0.6, 1.0f));
        }
        else
        {
            if(playerPosition.y <= 70)
            {
                sceGuFog(0, mWorld->mainOptions.horizontalViewDistance * 15 + 65.0f, GU_COLOR((( (mWorld->startSkyColor.x+mWorld->endSkyColor.x)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.x*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),(( (mWorld->startSkyColor.y+mWorld->endSkyColor.y)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.y*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),(( (mWorld->startSkyColor.z+mWorld->endSkyColor.z)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.z*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/70.0f),1.0f));
            }
            else
            {
                sceGuFog(0, mWorld->mainOptions.horizontalViewDistance * 15 + 65.0f, GU_COLOR(( (mWorld->startSkyColor.x+mWorld->endSkyColor.x)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.x*mWorld->dawnSunsetFactor*angleFactor),( (mWorld->startSkyColor.y+mWorld->endSkyColor.y)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.y*mWorld->dawnSunsetFactor*angleFactor),( (mWorld->startSkyColor.z+mWorld->endSkyColor.z)/2.0f *mWorld->brightFactor)*((1.0f-mWorld->dawnSunsetFactor))+(mWorld->dawnSunsetSkyColor.z*mWorld->dawnSunsetFactor*angleFactor),1.0f));
            }
        }
        sceGuEnable(GU_FOG );	// Enable fog
    }

    /// Draw world
    {
        sceGuEnable(GU_TEXTURE_2D);
        TextureManager::Instance()->SetTextureModeulate(texture);
        sceGumPushMatrix();
        mWorld->drawWorld(fppCam->mFrustum,needUpdate);
        sceGumPopMatrix();
        sceGuDisable(GU_TEXTURE_2D);
    }

    /// DROP
    if(mWorld->mDrops.empty() == false)
    {
        for(int d = 0; d < mWorld->mDrops.size(); d++)
        {
            if(d < mWorld->mDrops.size())
            {
                Drop* TestDrop = mWorld->mDrops[d];

                if(menuState == 0)//game state
                {
                    TestDrop->Update(dt);
                }

                if(TestDrop->GetId() < 250)
                {
                    TextureManager::Instance()->SetTextureModeulate(texture);
                }
                else
                {
                    TextureManager::Instance()->SetTextureModeulate(barItems);
                }

                TestDrop->Render(playerPosition, fppCam->horAngle/180.0f*PI);

                if(TestDrop->toDestroy == true)
                {
                    mWorld->DestroyDrop(d);
                    d -= 1;
                    continue;
                }

                if(TestDrop->getMe == true)
                {
                    mWorld->PutInInventory(TestDrop->GetId(),TestDrop->GetAmount(),TestDrop->GetStackable());
                    mSoundMgr->PlayPlopSound();
                    mWorld->DestroyDrop(d);
                    d -= 1;
                    continue;
                }
            }
        }
    }

    { /// ZOMBIE
        if(mWorld->mZombies.empty() == false)
        {
            for(int d = 0; d < mWorld->mZombies.size(); d++)
            {
                if(d < mWorld->mZombies.size())
                {
                    TextureManager::Instance()->SetTextureModeulate(zombieTex);
                    Zombie* TestZombie = mWorld->mZombies[d];

                    if(menuState == 0)//game state
                    {
                        TestZombie->Update(mWorld, playerPosition, dt);
                    }
                    TestZombie->Render(fppCam->mFrustum);

                    if(TestZombie->playHurtSound)
                    {
                        mSoundMgr->PlayZombieHurtSound(TestZombie->DistanceToPlayer());
                        TestZombie->playHurtSound = false;
                    }

                    if(TestZombie->toDestroy == true || TestZombie->killed == true)
                    {
                        if(TestZombie->playDieSound)
                        {
                            mSoundMgr->PlayZombieDieSound(TestZombie->DistanceToPlayer());
                            TestZombie->playDieSound = false;
                        }

                        if(TestZombie->killed == true)
                        {
                            if(rand()%4>=1)
                            {
                                mWorld->DropThis(Bone::getID(),1+rand()%2,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(rand()%4>=1)
                            {
                                mWorld->DropThis(RottenFlesh::getID(),1+rand()%2,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }

                            if(TestZombie->helmetId != -1)
                            {
                                mWorld->DropThis(TestZombie->helmetId,50+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->chestplateId != -1)
                            {
                                mWorld->DropThis(TestZombie->chestplateId,50+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->leggingsId != -1)
                            {
                                mWorld->DropThis(TestZombie->leggingsId,50+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->bootsId != -1)
                            {
                                mWorld->DropThis(TestZombie->bootsId,50+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                        }

                        mWorld->DestroyZombie(d);
                    }
                }
            }
        }
    }

        /// COWS
        if(mWorld->mCows.empty() == false)
        {
            for(int d = 0; d < mWorld->mCows.size(); d++)
            {
                if(d < mWorld->mCows.size())
                {
                    TextureManager::Instance()->SetTextureModeulate(cowTex);
                    Cow* TestCow = mWorld->mCows[d];

                    if(menuState == 0)//game state
                    {
                        TestCow->Update(mWorld, playerPosition, dt);
                    }
                    TestCow->Render(fppCam->mFrustum);

                    if(TestCow->playHurtSound)
                    {
                        mSoundMgr->PlayCowHurtSound(TestCow->DistanceToPlayer());
                        TestCow->playHurtSound = false;
                    }

                    if(TestCow->toDestroy == true || TestCow->killed == true)
                    {
                        if(TestCow->killed == true)
                        {
                            if(rand() % 100 < 65)
                            {
                                mWorld->DropThis(RawBeef::getID(),1+rand()%2,true,Vector3(TestCow->position.x,TestCow->position.y+0.3f,TestCow->position.z));
                            }
                            if(rand() % 100 < 55)
                            {
                                mWorld->DropThis(Leather::getID(),1+rand()%2,true,Vector3(TestCow->position.x,TestCow->position.y+0.3f,TestCow->position.z));
                            }
                        }

                        mWorld->DestroyCow(d);
                    }
                }
            }
        }


    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuDisable(GU_FOG); // disable fog
    }

    /// render snowballs
    if (mSnowBalls.empty() == false)
    {
        MatrixPush();
        MatrixTranslation(Vector3(0,0,0));

        for(unsigned int i = 0; i < mSnowBalls.size(); i++)
        {
            DrawSetDepthTest(true);
            DrawSetAlphaTest(true);

            TextureManager::Instance()->SetTextureModeulate(snowBall4);

            SnowBall2* UseSnowBall = mSnowBalls[i];
            UseSnowBall->Render();
            UseSnowBall->Update(mWorld, dt);
            if(UseSnowBall->CheckCollision(mWorld) == true)
            {
                delete mSnowBalls[i];
                mSnowBalls.erase(mSnowBalls.begin()+i);
            }

            DrawSetAlphaTest(false);
            DrawSetDepthTest(false);
        }

        MatrixPop();
    }

    /// render destroy model
    if (((startDt == 1 && dStd >= 0 && dStd <= 9) || showCube == true) && makeScreen == false)
	{
		MatrixPush();

        DrawSetDepthTest(true);
        DrawSetAlphaTest(true);
		DrawSetBlend(true);

		sceGuDepthMask(1);

		MatrixTranslation(Vector3(cubePos.x,cubePos.y,cubePos.z));
		MatrixColor(0xFFFFFFFF);

        TextureManager::Instance()->SetTextureModeulate(texture);

		destroyer->Update(dStd, mWorld, mWorld->GetBlock(cubePos.x,cubePos.y,cubePos.z));
		destroyer->Render();

		sceGuDepthMask(0);

		DrawSetBlend(false);
        DrawSetAlphaTest(false);
        DrawSetDepthTest(false);

		MatrixPop();
	}

	if(mWorld->mainOptions.guiDrawing == 1)
	{
        float cubeBob = sinf(bobCycle - (3.14/2) + 3.14)/16;
        float cubeBob2 = cosf(bobCycle - (3.14/2) + 3.14)/18;

        sceGuColor(GU_COLOR(cubeLight,cubeLight,cubeLight,1));

        if(mWorld->invId[27+barPosition] == -1)
        {
            TextureManager::Instance()->SetTextureModeulate(invPlayerTex);
            sceGumPushMatrix();

            //set view matrix to identity
            sceGumMatrixMode(GU_VIEW);
            sceGumLoadIdentity();
            //translate
            ScePspFVector3 move = {0.686f+cubeBob+shift_x+(mWorld->mainOptions.fov-70)/200.0f+sinf(animDest)*-0.15,-0.45f+shift_y+cubeBob2+changeY,-0.6f+(mWorld->mainOptions.fov-70)/130.0f}; //446
            sceGumTranslate(&move);
            //rotate
            sceGumRotateX(-0.65+sinf(animDest)*-1.5);//0.1
            sceGumRotateY(0.334+sinf(animDest)*-0.3); //0.9
            //scale
            ScePspFVector3 scale = {0.47f,0.47f,0.47f};
            sceGumScale(&scale);
            //draw cube
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDepthMask(1);
            mWorld->drawHand();
            sceGuEnable(GU_DEPTH_TEST);
            sceGuDepthMask(0);

            sceGumMatrixMode(GU_MODEL);
            sceGumPopMatrix();
        }

        if(mWorld->invId[27+barPosition] < 250 && mWorld->invId[27+barPosition] != -1)
        {
            TextureManager::Instance()->SetTextureModeulate(texture);
            sceGumPushMatrix();

            //set view matrix to identity
            sceGumMatrixMode(GU_VIEW);
            sceGumLoadIdentity();
            //translate
            ScePspFVector3 move = {0.596f+cubeBob+shift_x+(mWorld->mainOptions.fov-70)/200.0f+sinf(animDest)*-0.15,-0.35f+shift_y+cubeBob2+changeY,-0.7f+(mWorld->mainOptions.fov-70)/130.0f}; //446
            sceGumTranslate(&move);
            //rotate
            sceGumRotateX(0.169+sinf(animDest)*-1.5);
            sceGumRotateY(0.934+sinf(animDest)*-0.3); //3
            //scale
            ScePspFVector3 scale = {0.3f,0.3f,0.3f};
            sceGumScale(&scale);
            //draw cube
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDepthMask(1);
            mWorld->drawCubes(mWorld->invId[27+barPosition],cubeLight);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuDepthMask(0);

            sceGumMatrixMode(GU_MODEL);
            sceGumPopMatrix();
        }

        if(mWorld->invId[27+barPosition] >= 250)
        {
            TextureManager::Instance()->SetTextureModeulate(barItems);
            sceGumPushMatrix();

            //set view matrix to identity
            sceGumMatrixMode(GU_VIEW);
            sceGumLoadIdentity();

            //translate
            ScePspFVector3 move = {0.72f+cubeBob+shift_x+(mWorld->mainOptions.fov-70)/250.0f+sinf(animDest)*-0.15,-0.24f+cubeBob2+shift_y+changeY,-0.6f+(mWorld->mainOptions.fov-70)/180.0f};//-0.17
            sceGumTranslate(&move); //-0.22
            //rotate
            sceGumRotateX(-0.33f);
            sceGumRotateY(-1.47+sinf(animDest)*-0.3); //-1.47
            sceGumRotateZ(-3.13+sinf(animDest)*1.4); //-3.8
            //scale
            ScePspFVector3 scale = {0.42f,0.42f,0.42f};
            sceGumScale(&scale);

            //draw cube
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDepthMask(1);
            mWorld->drawHandItems(mWorld->invId[27+barPosition],cubeLight);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuDepthMask(0);

            sceGumMatrixMode(GU_MODEL);
            sceGumPopMatrix();
        }
        MatrixColor(0xFFFFFFFF);
	}
	MatrixColor(0xFFFFFFFF);

	/// GUI
	mRender->SetOrtho(0,0,0,0,0,0);

    if(mWorld->HP <= 0)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

		MatrixColor(GU_COLOR(1,1,1,0.5f));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}

    if(hurt == true)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,hurt_time));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}

	if(headInLava == 1 || footInLava == 1)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.7));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}
    if((invEn == 1 || craft3xEn == 1 || chestEn == 1 || menuState != 0 || furnaceEn == 1) && makeScreen == false)
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.7));

        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }

	if(headInWater)
	{
        if (GRAVITY != -4.0f)
        {
            GRAVITY = -4.0f;
        }

        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.8));

		waterScreen->Draw();

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}
	else
    {
        if (GRAVITY != -6.8f)
        {
            GRAVITY = -6.8f;
        }
    }

	/// GUI
	DrawSetDepthTest(false);
	DrawSetDepthMask(true);

	DrawSetBlend(true);
	MatrixColor(GU_COLOR(1,1,1,1.0f));

	if ((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || makeScreen == true)
    {
        hpAnim += dt * 5.9 * PI;
        if(hpAnim >= 10 * PI)
        {
            hpAnim = 0.0f;
        }
        barSprite->Draw();
        if (menuState != 1 || makeScreen == true)
        {
            /// HP and HG RENDERING
            for(int i = 1; i <= 10; i++)
            {
                hpCellSpriteW->SetPosition(60+i*16,220);
                hpCellSprite->SetPosition(60+i*16,220);

                hpSprite->SetPosition(60+i*16,220);
                hpHalfSprite->SetPosition(60+i*16,220);

                hpHardSprite->SetPosition(60+i*16,220);
                hpHardHalfSprite->SetPosition(60+i*16,220);

                if(hurt == true && sinf(hpAnim) > 0)
                {
                    hpCellSpriteW->Draw();
                }
                if(hurt == false || sinf(hpAnim) <= 0)
                {
                    hpCellSprite->Draw();
                }

                if(i * 2 <= roundf(mWorld->HP) && mWorld->HP >= 0)
                {
                    if(mWorld->gameModeWorld == 2) // hardcore mode
                    {
                        hpHardSprite->Draw();
                    }
                    else
                    {
                        hpSprite->Draw();
                    }
                }
                if(i * 2 - roundf(mWorld->HP) == 1 && mWorld->HP >= 0)
                {
                    if(mWorld->gameModeWorld == 2) // hardcore mode
                    {
                        hpHardHalfSprite->Draw();
                    }
                    else
                    {
                        hpHalfSprite->Draw();
                    }
                }

                hgCellSprite->SetPosition(247+i*16,220);

                hgSprite->SetPosition(247+i*16,220);
                hgHalfSprite->SetPosition(247+i*16,220);

                hgCellSprite->Draw();
                if(i * 2 <= roundf(mWorld->HG))
                {
                    hgSprite->Draw();
                }
                if(i * 2 - roundf(mWorld->HG) == 1)
                {
                    hgHalfSprite->Draw();
                }

                arCellSprite->SetPosition(60+i*16,200);
                arSprite->SetPosition(60+i*16,200);
                arHalfSprite->SetPosition(60+i*16,200);

                if(mWorld->AP > 0)
                {
                    arCellSprite->Draw();
                    if(i * 2 <= roundf(mWorld->AP))
                    {
                        arSprite->Draw();
                    }
                    if(i * 2 - roundf(mWorld->AP) == 1)
                    {
                        arHalfSprite->Draw();
                    }
                }

                if(headInWater)
                {
                    bubbleSprite->SetPosition(247+i*16,200);
                    if(i <= mWorld->OS)
                    {
                        bubbleSprite->Draw();
                    }
                }
            }

            if(mWorld->HP > 0)
            {
                DrawSetInverseColors();
                crossSprite->Draw();
                DrawSetDefaultColors();
            }

            selectSprite->Draw();
        }
    }
    else
    {
        if (invEn == true)
        {
            invSprite->Draw();
        }
        if (craft3xEn == true)
        {
            crtSprite->Draw();
        }
        if (chestEn == true)
        {
            chtSprite->Draw();
        }
        if (furnaceEn == true)
        {
            furSprite->Draw();

            int furFireStage = 0;

            if(UseFurnace->fuelTime >= 10.0f)
            {
                furFireStage = 4;
            }
            if(UseFurnace->fuelTime < 10.0f)
            {
                furFireStage = ((int)(UseFurnace->fuelTime/2.0f))-1;
            }

            if(furFireStage >= 0)
            {
                furFireSprite[furFireStage]->SetPosition(190,50-((furFireStage-4)*6));
                furFireSprite[furFireStage]->Draw();
            }

            int furArrowStage = 0;

            furArrowStage = (ceilf(UseFurnace->meltingTime/0.91f))-1;

            if(furArrowStage >= 0)
            {
                furArrowSprite[furArrowStage]->SetPosition(236,46);
                furArrowSprite[furArrowStage]->Draw();
            }
        }
    }
	DrawSetBlend(false);

    /// 3D BLOCKS AND ITEMS ON 2D PANEL
    if ((invEn == false && craft3xEn == false && chestEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1 && furnaceEn == false) || makeScreen == true)
    {
        for(int k = 0; k <= 8; k++)
        {
            if(mWorld->invId[27+k] != -1)
            {
                MatrixPush();

                if(mWorld->invId[27+k] < 250)
                {
                    MatrixTranslation(Vector3(80+k*40,250,0));
                    MatrixScale(Vector3(18,18,18));
                    MatrixAngle(Vector3(143,52,0));

                    TextureManager::Instance()->SetTextureModeulate(texture);

                    DrawSetCulling(true);
                    mWorld->drawCubes(mWorld->invId[27+k],1.0f);
                    DrawSetCulling(false);
                }

                if(mWorld->invId[27+k] >= 250)
                {
                    MatrixTranslation(Vector3(80+k*40,250,0));
                    MatrixScale(Vector3(32,32,32));
                    MatrixAngle(Vector3(0,0,0));

                    TextureManager::Instance()->SetTextureModeulate(barItems);

                    DrawSetCulling(true);
                    mWorld->drawItems(mWorld->invId[27+k]);
                    DrawSetCulling(false);
                }
                MatrixPop();
            }
        }
    }

    /// INVENTORY CRAFT MENU
    if(invEn == true)
    {
        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(craftSlotId[i*2+j] != -1)
                {
                    MatrixPush();

                    MatrixTranslation(Vector3(276+j*36,46+i*36,0.0f));

                    if(craftSlotId[i*2+j] < 250)
                    {
                        MatrixScale(Vector3(18,18,18));
                        MatrixAngle(Vector3(143,52,0));

                        TextureManager::Instance()->SetTextureModeulate(texture);

                        DrawSetCulling(true);
                        mWorld->drawCubes(craftSlotId[i*2+j],1.0f);
                        DrawSetCulling(false);
                    }

                    if(craftSlotId[i*2+j] >= 250)
                    {
                        MatrixScale(Vector3(32,32,32));
                        MatrixAngle(Vector3(0,0,0));

                        TextureManager::Instance()->SetTextureModeulate(barItems);

                        DrawSetCulling(true);
                        mWorld->drawItems(craftSlotId[i*2+j]);
                        DrawSetCulling(false);
                    }
                    MatrixPop();
                }
            }
        }

        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(mWorld->armorId[i*2+j] != -1)
                {
                    MatrixPush();

                    MatrixTranslation(Vector3(96+j*108,26+i*72,0.0f));

                    if(mWorld->armorId[i*2+j] < 250)
                    {
                        MatrixScale(Vector3(18,18,18));
                        MatrixAngle(Vector3(143,52,0));

                        TextureManager::Instance()->SetTextureModeulate(texture);

                        DrawSetCulling(true);
                        mWorld->drawCubes(mWorld->armorId[i*2+j],1.0f);
                        DrawSetCulling(false);
                    }

                    if(mWorld->armorId[i*2+j] >= 250)
                    {
                        MatrixScale(Vector3(32,32,32));
                        MatrixAngle(Vector3(0,0,0));

                        TextureManager::Instance()->SetTextureModeulate(barItems);

                        DrawSetCulling(true);
                        mWorld->drawItems(mWorld->armorId[i*2+j]);
                        DrawSetCulling(false);
                    }
                    MatrixPop();
                }
            }
        }

        //End

        //Item which we are crafting
        if (craftItemId != -1)
        {
            MatrixPush();

            MatrixTranslation(Vector3(384,66,0.0f));

            if(craftItemId < 250)
            {
                MatrixScale(Vector3(18,18,18));
                MatrixAngle(Vector3(143,52,0));

                TextureManager::Instance()->SetTextureModeulate(texture);

                DrawSetCulling(true);
                mWorld->drawCubes(craftItemId,1.0f);
                DrawSetCulling(false);
            }

            if(craftItemId >= 250)
            {
                MatrixScale(Vector3(32,32,32));
                MatrixAngle(Vector3(0,0,0));

                TextureManager::Instance()->SetTextureModeulate(barItems);

                DrawSetCulling(true);
                mWorld->drawItems(craftItemId);
                DrawSetCulling(false);
            }
            MatrixPop();
        }

        if(upEn == false)
        {
            if(invSteveAngle < invXPosition/8.0f*48)
            {
                invSteveAngle += (invXPosition/8.0f*48-invSteveAngle)*0.05;
            }
            if(invSteveAngle > invXPosition/8.0f*48)
            {
                invSteveAngle -= (invSteveAngle-invXPosition/8.0f*48)*0.05;
            }
        }

        MatrixPush();

        MatrixTranslation(Vector3(151,56,0));
        MatrixScale(Vector3(46,46,46));
        MatrixAngle(Vector3(-14,invSteveAngle,180));// 24

        TextureManager::Instance()->SetTextureModeulate(invPlayerTex);

        invPlayer->mainAngle = 0.45f;

        DrawSetDepthMask(false);
        DrawSetCulling(true);
        invPlayer->Render(mWorld, dt, invSteveAngle, invPlayerTex);
        DrawSetCulling(false);
        DrawSetDepthMask(true);

        MatrixPop();
    }


    ///CRAFTING TABLE
    if(craft3xEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 2; j++)
            {
                if(craftSlotId3[i*3+j] != -1)
                {
                    MatrixPush();

                    MatrixTranslation(Vector3(204+j*36,26+i*36,0.0f));

                    if(craftSlotId3[i*3+j] < 250)
                    {
                        MatrixScale(Vector3(18,18,18));
                        MatrixAngle(Vector3(143,52,0));

                        TextureManager::Instance()->SetTextureModeulate(texture);

                        DrawSetCulling(true);
                        mWorld->drawCubes(craftSlotId3[i*3+j],1.0f);
                        DrawSetCulling(false);
                    }

                    if(craftSlotId3[i*3+j] >= 250)
                    {
                        MatrixScale(Vector3(32,32,32));
                        MatrixAngle(Vector3(0,0,0));

                        TextureManager::Instance()->SetTextureModeulate(barItems);

                        DrawSetCulling(true);
                        mWorld->drawItems(craftSlotId3[i*3+j]);
                        DrawSetCulling(false);
                    }
                    MatrixPop();
                }
            }
        }
        //End

        //Item which we are crafting 3x
        if (craftItemId3 != -1)
        {
            MatrixPush();

            MatrixTranslation(Vector3(348,62,0.0f));

            if(craftItemId3 < 250)
            {
                MatrixScale(Vector3(18,18,18));
                MatrixAngle(Vector3(143,52,0));

                TextureManager::Instance()->SetTextureModeulate(texture);

                DrawSetCulling(true);
                mWorld->drawCubes(craftItemId3,1.0f);
                DrawSetCulling(false);
            }

            if(craftItemId3 >= 250)
            {
                MatrixScale(Vector3(32,32,32));
                MatrixAngle(Vector3(0,0,0));

                TextureManager::Instance()->SetTextureModeulate(barItems);

                DrawSetCulling(true);
                mWorld->drawItems(craftItemId3);
                DrawSetCulling(false);
            }
            MatrixPop();
        }
    }

    ///CHEST
    if(chestEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] != -1)
                {
                    MatrixPush();

                    MatrixTranslation(Vector3(96+j*36,26+i*36,0.0f));

                    if(UseChest->chestSlotId[i*9+j] < 250)
                    {
                        MatrixScale(Vector3(18,18,18));
                        MatrixAngle(Vector3(143,52,0));

                        TextureManager::Instance()->SetTextureModeulate(texture);

                        DrawSetCulling(true);
                        mWorld->drawCubes(UseChest->chestSlotId[i*9+j],1.0f);
                        DrawSetCulling(false);
                    }

                    if(UseChest->chestSlotId[i*9+j] >= 250)
                    {
                        MatrixScale(Vector3(32,32,32));
                        MatrixAngle(Vector3(0,0,0));

                        TextureManager::Instance()->SetTextureModeulate(barItems);

                        DrawSetCulling(true);
                        mWorld->drawItems(UseChest->chestSlotId[i*9+j]);
                        DrawSetCulling(false);
                    }
                    MatrixPop();
                }
            }
        }
    }

    ///FURNACE
    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {204,26,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[0] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
                ScePspFVector3 sca = {18,18,18.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(UseFurnace->furnaceSlotId[0],1.0f);
                sceGuFrontFace(GU_CCW);
            }

            if(UseFurnace->furnaceSlotId[0] >= 250)
            {
                TextureManager::Instance()->SetTextureModeulate(barItems);
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGuFrontFace(GU_CW);
                mWorld->drawItems(UseFurnace->furnaceSlotId[0]);
                sceGuFrontFace(GU_CCW);
            }
            sceGumPopMatrix();
        }

        if(UseFurnace->furnaceSlotId[1] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {204,98,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[1] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
                ScePspFVector3 sca = {18,18,18.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(UseFurnace->furnaceSlotId[1],1.0f);
                sceGuFrontFace(GU_CCW);
            }

            if(UseFurnace->furnaceSlotId[1] >= 250)
            {
                TextureManager::Instance()->SetTextureModeulate(barItems);
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGuFrontFace(GU_CW);
                mWorld->drawItems(UseFurnace->furnaceSlotId[1]);
                sceGuFrontFace(GU_CCW);
            }
            sceGumPopMatrix();
        }

        if(UseFurnace->furnaceSlotId[2] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {312,62,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[2] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
                ScePspFVector3 sca = {18,18,18.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(UseFurnace->furnaceSlotId[2],1.0f);
                sceGuFrontFace(GU_CCW);
            }

            if(UseFurnace->furnaceSlotId[2] >= 250)
            {
                TextureManager::Instance()->SetTextureModeulate(barItems);
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);
                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGuFrontFace(GU_CW);
                mWorld->drawItems(UseFurnace->furnaceSlotId[2]);
                sceGuFrontFace(GU_CCW);
            }
            sceGumPopMatrix();
        }
    }

    if (invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
    {
        for(int i = 0; i <= 3; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(mWorld->invId[i*9+j] != -1)
                {
                    MatrixPush();
                    MatrixTranslation(Vector3(96+j*36,138+i*36,0.0f));

                    if(mWorld->invId[i*9+j] < 250)
                    {
                        TextureManager::Instance()->SetTextureModeulate(texture);
                        ScePspFVector3 sca = {18,18,18.0f};
                        sceGumScale(&sca);

                        sceGumRotateX(2.5f);
                        sceGumRotateY(0.9f);

                        sceGuFrontFace(GU_CW);
                        mWorld->drawCubes(mWorld->invId[i*9+j],1.0f);
                        sceGuFrontFace(GU_CCW);
                    }

                    if(mWorld->invId[i*9+j] >= 250)
                    {
                        TextureManager::Instance()->SetTextureModeulate(barItems);
                        ScePspFVector3 sca = {32,32,32.0f};
                        sceGumScale(&sca);

                        sceGumRotateX(0.0f);
                        sceGumRotateY(0.0f);

                        sceGuFrontFace(GU_CW);
                        mWorld->drawItems(mWorld->invId[i*9+j]);
                        sceGuFrontFace(GU_CCW);
                    }
                    MatrixPop();
                }
            }
        }



        if (mWorld->mId != -1) //MOUSE ITEM
        {
            MatrixPush();
            if (upEn == 1)
            {
                if (invEn == 1)
                {
                    MatrixTranslation(Vector3(276+invXPosition*36,38+invYPosition*36,0.0f));
                }
                if (craft3xEn == 1)
                {
                    MatrixTranslation(Vector3(204+invXPosition*36,18+invYPosition*36,0.0f));
                }
                if (chestEn == 1)
                {
                    MatrixTranslation(Vector3(96+invXPosition*36,18+invYPosition*36,0.0f));
                }
                if (furnaceEn == 1)
                {
                    MatrixTranslation(Vector3(204,18+(invYPosition * 72),0.0f));
                }
            }
            else
            {
                if(armorEn == false)
                {
                    MatrixTranslation(Vector3(96 + (invXPosition * 36),130+(invYPosition * 36),0.0f)); // 8 upper
                }
                else
                {
                    MatrixTranslation(Vector3(96 + (invXPosition * 108),18+(invYPosition * 72),0.0f)); // 8 upper
                }
            }

            if (mWorld->mId < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
                ScePspFVector3 sca = {18,18,18.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);
                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(mWorld->mId,1.0f);
                sceGuFrontFace(GU_CCW);
            }

            if (mWorld->mId >= 250)
            {
                TextureManager::Instance()->SetTextureModeulate(barItems);
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGuFrontFace(GU_CW);
                mWorld->drawItems(mWorld->mId);
                sceGuFrontFace(GU_CCW);
            }
            MatrixPop();
        }
    }

	DrawSetDepthTest(false);
	DrawSetDepthMask(true);
	DrawSetBlend(true);
	MatrixColor(GU_COLOR(1,1,1,1.0f));
    // durability strip drawing
    if ((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || makeScreen == true)
    {
        for(int k = 0; k <= 8; k++)
        {
            if(mWorld->invId[27+k] >= 250)
            {
                if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) != -1) // if it is tool
                {
                    if(mWorld->invAm[27+k] != mWorld->DurabilityPointsItem(mWorld->invId[27+k])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(mWorld->invAm[27+k]) / (float)(mWorld->DurabilityPointsItem(mWorld->invId[27+k])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(68+k*40,260);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }

    if(invEn == true)
    {
        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(craftSlotId[i*2+j] >= 250 && mWorld->DurabilityPointsItem(craftSlotId[i*2+j]) != -1)
                {
                    if(craftSlotAm[i*2+j] != mWorld->DurabilityPointsItem(craftSlotId[i*2+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(craftSlotAm[i*2+j]) / (float)(mWorld->DurabilityPointsItem(craftSlotId[i*2+j])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(264+j*36,56+i*36);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }

        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(mWorld->armorId[i*2+j] >= 250 && mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j]) != -1)
                {
                    if(mWorld->armorAm[i*2+j] != mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(mWorld->armorAm[i*2+j]) / (float)(mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(84+j*108,36+i*72);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }

    if(craft3xEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 2; j++)
            {
                if(craftSlotId3[i*3+j] >= 250 && mWorld->DurabilityPointsItem(craftSlotId3[i*3+j]) != -1)
                {
                    if(craftSlotAm3[i*3+j] != mWorld->DurabilityPointsItem(craftSlotId3[i*3+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(craftSlotAm3[i*3+j]) / (float)(mWorld->DurabilityPointsItem(craftSlotId3[i*3+j])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(192+j*36,36+i*36);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }

    if(chestEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] >= 250 && mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j]) != -1)
                {
                    if(UseChest->chestSlotAm[i*9+j] != mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(UseChest->chestSlotAm[i*9+j]) / (float)(mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(84+j*36,36+i*36);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }

    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] >= 250 && mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) != -1) // it is item and it have durability points
        {
            if(UseFurnace->furnaceSlotAm[0] != mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) != -1)
            {
                unsigned int toolPointStd = roundf((float)(UseFurnace->furnaceSlotAm[0]) / (float)(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0])) * 13);

                toolPointSprite[toolPointStd]->SetPosition(192,36);
                toolPointSprite[toolPointStd]->Draw();
            }
        }

        if(UseFurnace->furnaceSlotId[1] >= 250 && mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) != -1) // it is item and it have durability points
        {
            if(UseFurnace->furnaceSlotAm[1] != mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) != -1)
            {
                unsigned int toolPointStd = roundf((float)(UseFurnace->furnaceSlotAm[1]) / (float)(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1])) * 13);

                toolPointSprite[toolPointStd]->SetPosition(192,108);
                toolPointSprite[toolPointStd]->Draw();
            }
        }
    }

    if (invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
    {
        for(int i = 0; i <= 3; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(mWorld->invId[i*9+j] >= 250)
                {
                    if(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j]) != -1) // if it is tool
                    {
                        if(mWorld->invAm[i*9+j] != mWorld->DurabilityPointsItem(mWorld->invId[i*9+j])) // checking durability
                        {
                            unsigned int toolPointStd = roundf((float)(mWorld->invAm[i*9+j]) / (float)(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j])) * 13);

                            toolPointSprite[toolPointStd]->SetPosition(84+j*36,148+i*36);
                            toolPointSprite[toolPointStd]->Draw();
                        }
                    }
                }
            }
        }

        if (mWorld->mId >= 250 && mWorld->DurabilityPointsItem(mWorld->mId) != -1)
        {
            if(mWorld->mAm != mWorld->DurabilityPointsItem(mWorld->mId))
            {
                unsigned int toolPointStd = roundf((float)(mWorld->mAm) / (float)(mWorld->DurabilityPointsItem(mWorld->mId)) * 13);
                if (upEn == 1)
                {
                    if (invEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(264+invXPosition*36,48+invYPosition*36);
                    }
                    if (craft3xEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(192+invXPosition*36,28+invYPosition*36);
                    }
                    if (chestEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(84+invXPosition*36,28+invYPosition*36);

                    }
                    if (furnaceEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(192,28+invYPosition*72);
                    }
                }
                else
                {
                    if(armorEn == false)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(84+invXPosition*36,140+invYPosition*36);
                    }
                    else
                    {
                        toolPointSprite[toolPointStd]->SetPosition(84+invXPosition*108,28+invYPosition*72);
                    }
                }
                toolPointSprite[toolPointStd]->Draw();
            }
        }
    }

    DrawSetBlend(false);


	sceGuEnable(GU_DEPTH_TEST);
	sceGuDepthMask(0);

    //text
    if(mWorld->HP <= 0)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
        if(mWorld->gameModeWorld == 2)
        {
            mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);

            mRender->DebugPrint(242,52,"Game over!");
            mRender->DebugPrint(242,152,"Press X to delete your world!");

            mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);

            mRender->DebugPrint(240,50,"Game over!");
            mRender->DebugPrint(240,150,"Press X to delete your world!");
        }
        else
        {
            mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);

            mRender->DebugPrint(242,52,"You died!");
            mRender->DebugPrint(242,152,"Press X to respawn!");

            mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);

            mRender->DebugPrint(240,50,"You died!");
            mRender->DebugPrint(240,150,"Press X to respawn!");
        }
    }

    mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);

    if((freeMemory/1024)/1024 <= 3 && mWorld->mainStatistics.minutesPlayed > 2)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
        mRender->SetFontStyle(default_size,GU_COLOR(1,0,0,1),0,0x00000000);
        //mRender->DebugPrint(5,15,"You have few free ram! Please, reduce the settings or restart the game!");
        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);
    }

    mRender->SetFontStyle(default_size,0xFFFFFFFF,0xFF000000,0x00000200);

    if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        selectInvSprite->Draw();

        for(int i = 0; i <= 3; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(mWorld->invId[i*9+j] != -1 && mWorld->invAm[i*9+j] > 1)
                {
                    if(mWorld->invId[i*9+j] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j]) == -1)
                        {
                            DrawAmount(106+j*36,164+i*36,mWorld->invAm[i*9+j]);
                        }
                    }
                    else
                    {
                        DrawAmount(106+j*36,164+i*36,mWorld->invAm[i*9+j]);
                    }
                }
            }
        }

        if (mWorld->mId != -1)
        {
            bool canDraw = false;

            if(mWorld->mId >= 250)
            {
                if(mWorld->DurabilityPointsItem(mWorld->mId) == -1)
                {
                    canDraw = true;
                }
            }
            else
            {
                canDraw = true;
            }

            if(canDraw == true)
            {
                if (upEn == 0)
                {
                    if(armorEn == false)
                    {
                        DrawAmount(106+(invXPosition * 36),156+(invYPosition * 36),mWorld->mAm);
                    }
                    else
                    {
                        DrawAmount(106+(invXPosition * 108),44+(invYPosition * 72),mWorld->mAm);
                    }
                }
                else
                {
                    if(invEn == 1)
                    {
                        DrawAmount(286+(invXPosition * 36),64+(invYPosition * 36),mWorld->mAm);
                    }
                    if(craft3xEn == 1)
                    {
                        DrawAmount(214+(invXPosition * 36),44+(invYPosition * 36),mWorld->mAm);
                    }
                    if(chestEn == 1)
                    {
                        DrawAmount(106+(invXPosition * 36),44+(invYPosition * 36),mWorld->mAm);
                    }
                    if(furnaceEn == 1)
                    {
                        DrawAmount(214,44+(invYPosition * 72),mWorld->mAm);
                    }
                }
            }
        }
    }

    if((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || makeScreen == true)
    {
        for(int k = 0; k <= 8; k++)
        {
            if (mWorld->invAm[27+k] > 1)
            {
                if(mWorld->invId[27+k] >= 250) // if it is item but not a tool
                {
                    if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) == -1)
                    {
                        DrawAmount(90+k*40,276,mWorld->invAm[27+k]);
                    }
                }
                else
                {
                    DrawAmount(90+k*40,276,mWorld->invAm[27+k]);
                }
            }
        }
    }

    if(invEn == true)
    {
        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(craftSlotId[i*2+j] != -1 && craftSlotAm[i*2+j] > 1)
                {
                    if(craftSlotId[i*2+j] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(craftSlotId[i*2+j]) == -1)
                        {
                            DrawAmount(286+j*36,72+i*36,craftSlotAm[i*2+j]);
                        }
                    }
                    else
                    {
                        DrawAmount(286+j*36,72+i*36,craftSlotAm[i*2+j]);
                    }
                }
            }
        }

        if(craftItemId != -1)
        {
            if(craftItemId >= 250)
            {
                if(mWorld->DurabilityPointsItem(craftItemId) == -1)
                {
                    DrawAmount(394,92,craftItemAm);
                }
            }
            else
            {
                DrawAmount(394,92,craftItemAm);
            }
        }
    }

    if(craft3xEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 2; j++)
            {
                if(craftSlotId3[i*3+j] != -1 && craftSlotAm3[i*3+j] > 1)
                {
                    if(craftSlotId3[i*3+j] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(craftSlotId3[i*3+j]) == -1)
                        {
                            DrawAmount(214+j*36,52+i*36,craftSlotAm3[i*3+j]);
                        }
                    }
                    else
                    {
                        DrawAmount(214+j*36,52+i*36,craftSlotAm3[i*3+j]);
                    }
                }
            }
        }

        if(craftItemId3 != -1)
        {
            if(craftItemId3 >= 250)
            {
                if(mWorld->DurabilityPointsItem(craftItemId3) == -1)
                {
                    DrawAmount(358,88,craftItemAm3);
                }
            }
            else
            {
                DrawAmount(358,88,craftItemAm3);
            }
        }
    }

    if(chestEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] != -1 && UseChest->chestSlotAm[i*9+j] > 1)
                {
                    if(UseChest->chestSlotId[i*9+j] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j]) == -1)
                        {
                            DrawAmount(106+j*36,52+i*36,UseChest->chestSlotAm[i*9+j]);
                        }
                    }
                    else
                    {
                        DrawAmount(106+j*36,52+i*36,UseChest->chestSlotAm[i*9+j]);
                    }
                }
            }
        }
    }

    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] != -1 && UseFurnace->furnaceSlotAm[0] > 1)
        {
            if(UseFurnace->furnaceSlotId[0] >= 250)
            {
                if(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) == -1)
                {
                    DrawAmount(214,52,UseFurnace->furnaceSlotAm[0]);
                }
            }
            else
            {
                 DrawAmount(214,52,UseFurnace->furnaceSlotAm[0]);
            }
        }
        if(UseFurnace->furnaceSlotId[1] != -1 && UseFurnace->furnaceSlotAm[1] > 1)
        {
            if(UseFurnace->furnaceSlotId[1] >= 250)
            {
                if(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) == -1)
                {
                    DrawAmount(214,124,UseFurnace->furnaceSlotAm[1]);
                }
            }
            else
            {
                DrawAmount(214,124,UseFurnace->furnaceSlotAm[1]);
            }
        }
        if(UseFurnace->furnaceSlotId[2] != -1 && UseFurnace->furnaceSlotAm[2] > 1)
        {
            DrawAmount(322,88,UseFurnace->furnaceSlotAm[2]);
        }
    }
    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    if(makeScreen)
	{
		//end frame now to update frame buffer
		mRender->EndFrame();
		//make screenshot
		mRender->TakeNextScreenshot();
		makeScreen = false;
	}


    mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0x00000200);

    //menu buttons
    if(menuState == 1)
    {
        if(menuOptions)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            nbuttonSprite->SetPosition(110,40);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(370,40);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(110,70);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(370,70);
            nbuttonSprite->Draw();

            buttonSprite->SetPosition(110,100);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,100);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,130);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,130);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,160);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,160);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,190);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,190);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,220);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,220);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,250);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,250);
            buttonSprite->Draw();

            if (optionsMenuPos < 8)
            {
                sbuttonSprite->SetPosition(110,(optionsMenuPos * 30) + 40);
            }
            if(optionsMenuPos >= 8)
            {
                sbuttonSprite->SetPosition(370,((optionsMenuPos-8) * 30) + 40);
            }
            sbuttonSprite->Draw();


            if(mWorld->mainOptions.fov == 40)
            {
                moverSprite->SetPosition(21,40);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.fov - 40)*3.0f+19,40);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.horizontalViewDistance == 1)
            {
                moverSprite->SetPosition(21,70);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.horizontalViewDistance - 1)*63.3+9,70);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.verticalViewDistance == 1)
            {
                moverSprite->SetPosition(281,40);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.verticalViewDistance - 1)*190.0f+269,40);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.difficult == 0)
            {
                moverSprite->SetPosition(281,70);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.difficult - 1)*63.3+269,70);
            }
            moverSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            //draw subtitles on buttons
            if(mWorld->mainOptions.fov == 70)
            {
                optionsMenuPos == 0 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(110,49,"FOV: Normal");
            }
            else
            {
                optionsMenuPos == 0 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(110,49,"FOV: %f",mWorld->mainOptions.fov);
            }

            if(mWorld->mainOptions.horizontalViewDistance == 1)
            {
                optionsMenuPos == 1 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(110,79,"H View Distance: %i chunk",mWorld->mainOptions.horizontalViewDistance);
            }
            else
            {
                optionsMenuPos == 1 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(110,79,"H View Distance: %i chunks",mWorld->mainOptions.horizontalViewDistance);
            }

            if(mWorld->mainOptions.verticalViewDistance == 1)
            {
                optionsMenuPos == 8 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,49,"V View Distance: %i chunk",mWorld->mainOptions.verticalViewDistance);
            }
            else
            {
                optionsMenuPos == 8 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,49,"V View Distance: %i chunks",mWorld->mainOptions.verticalViewDistance);
            }


            switch(mWorld->mainOptions.difficult)
            {
            case 0:
                optionsMenuPos == 9 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,79,"Difficult: Peaceful");
            break;
            case 1:
                optionsMenuPos == 9 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,79,"Difficult: Easy");
            break;
            case 2:
                optionsMenuPos == 9 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,79,"Difficult: Normal");
            break;
            case 3:
                optionsMenuPos == 9 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
                mRender->DebugPrint(370,79,"Difficult: Hard");
            break;
            }


            optionsMenuPos == 2 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.fogRendering == true ? mRender->DebugPrint(110,109,"Fog Rendering: ON"): mRender->DebugPrint(110,109,"Fog Rendering: OFF");

            optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.cloudsRender == true ? mRender->DebugPrint(110,139,"Clouds Rendering: ON"): mRender->DebugPrint(110,139,"Clouds Rendering: OFF");

            optionsMenuPos == 4 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.fastRendering == true ? mRender->DebugPrint(110,169,"Graphics: Fast"): mRender->DebugPrint(110,169,"Graphics: Fancy");

            optionsMenuPos == 5 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.worldBlockAnimation == true ? mRender->DebugPrint(110,199,"Block Animation: ON"): mRender->DebugPrint(110,199,"Block Animation: OFF");

            optionsMenuPos == 6 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.headBob == true ? mRender->DebugPrint(110,229,"Head Bob: ON"): mRender->DebugPrint(110,229,"Head Bob: OFF");

            optionsMenuPos == 7 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.fakeShadowsRendering == true ? mRender->DebugPrint(110,259,"Fake Shadows: ON"): mRender->DebugPrint(110,259,"Fake Shadows: OFF");

            optionsMenuPos == 10 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.sunMoodRendering == true ? mRender->DebugPrint(370,109,"Sun&Moon Rendering: ON"): mRender->DebugPrint(370,109,"Sun&Moon Rendering: OFF");

            optionsMenuPos == 11 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.guiDrawing == true ? mRender->DebugPrint(370,139,"GUI Rendering: ON"): mRender->DebugPrint(370,139,"GUI Rendering: OFF");

            optionsMenuPos == 12 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mWorld->mainOptions.sounds == true ? mRender->DebugPrint(370,169,"Sounds: ON"): mRender->DebugPrint(370,169,"Sounds: OFF");

            optionsMenuPos == 13 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mRender->DebugPrint(370,199,"Take Screenshot");

            optionsMenuPos == 14 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            mRender->DebugPrint(370,229,"Rename Map");

            optionsMenuPos == 15 ? RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
            devMode == true ? mRender->DebugPrint(370,259,"Dev Mode: ON") : mRender->DebugPrint(370,259,"Dev Mode: OFF");

            DrawText(240,24,GU_COLOR(1,1,1,1),default_size,"Options");

            DrawText(110,24,GU_COLOR(1,1,1,1),default_size,"L");
            DrawText(370,24,GU_COLOR(1,1,1,1),default_size,"R");
        }
        else
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,50);
            buttonSprite->Draw();

            //resume
            buttonSprite->SetPosition(240,80);
            buttonSprite->Draw();

            //options
            buttonSprite->SetPosition(240,110);
            buttonSprite->Draw();

            //save
            buttonSprite->SetPosition(240,160);
            buttonSprite->Draw();

            //quit
            buttonSprite->SetPosition(240,190);
            buttonSprite->Draw();

            //quit and save
            buttonSprite->SetPosition(240,220);
            buttonSprite->Draw();

            //selected button
            if(selectPos <= 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 50);
            }
            if(selectPos > 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 70);
            }
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000000|0x00004000);
            mRender->DebugPrint(2,15,"World seed is: %i",mWorld->worldSeed);

            selectPos == 0 ? DrawText(240,59,GU_COLOR(1,1,0,1),default_size,"Back to game") : DrawText(240,59,GU_COLOR(1,1,1,1),default_size,"Back to game");
            selectPos == 1 ? DrawText(240,89,GU_COLOR(1,1,0,1),default_size,"Options...") : DrawText(240,89,GU_COLOR(1,1,1,1),default_size,"Options...");
            selectPos == 2 ? DrawText(240,119,GU_COLOR(1,1,0,1),default_size,"Statistics") : DrawText(240,119,GU_COLOR(1,1,1,1),default_size,"Statistics");
            selectPos == 3 ? DrawText(240,169,GU_COLOR(1,1,0,1),default_size,"Save") : DrawText(240,169,GU_COLOR(1,1,1,1),default_size,"Save");
            selectPos == 4 ? DrawText(240,199,GU_COLOR(1,1,0,1),default_size,"Save and exit") : DrawText(240,199,GU_COLOR(1,1,1,1),default_size,"Save and exit");
            selectPos == 5 ? DrawText(240,229,GU_COLOR(1,1,0,1),default_size,"Exit") : DrawText(240,229,GU_COLOR(1,1,1,1),default_size,"Exit");

            DrawText(240,29,GU_COLOR(1,1,1,1),default_size,"Game menu");
        }
    }
    if (menuState == 3)
    {
        if(statisticsPage == 0)
        {
            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,54,"Blocks Placed: %i",mWorld->mainStatistics.blockPlaced);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,74,"Blocks Destroyed: %i",mWorld->mainStatistics.blockDestroyed);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,94,"Age Of The World: %i d",mWorld->mainStatistics.daysInGame);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,114,"Minutes Played: %i m",mWorld->mainStatistics.minutesPlayed);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,134,"Items Crafted: %i",mWorld->mainStatistics.itemsCrafted);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,154,"Items Smelted: %i",mWorld->mainStatistics.itemsSmelted);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,174,"Soil Plowed: %i",mWorld->mainStatistics.soilPlowed);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,194,"Crops Grown: %i",mWorld->mainStatistics.cropsGrowned);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,214,"Trees Grown: %i",mWorld->mainStatistics.treesGrowned);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,234,"Damage Dealt: %i",mWorld->mainStatistics.damageRecieved);
        }
        else
        {
            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,54,"Badly falls: %i",mWorld->mainStatistics.badlyFalls);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,74,"Food eaten: %i",mWorld->mainStatistics.foodEaten);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,94,"Jumps: %i",mWorld->mainStatistics.jumps);

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.8,0.8,0.8,1),0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,114,"Dies: %i",mWorld->mainStatistics.dies);
        }

        DrawText(240,24,GU_COLOR(1,1,1,1),default_size,"Statistics");

        RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
        RenderManager::InstancePtr()->DebugPrint(240,254,"Page: %i / 2",statisticsPage+1);
    }

    //debug info
    if(devMode)
    {
        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000000);

        if(dt > 0.0f)
            mRender->DebugPrint(20,24,"fps: %4.2f",(1.0f/dt));
        mRender->DebugPrint(20,34,"cpu: %d%%",mRender->GetCpuUsage());
        mRender->DebugPrint(20,44,"gpu: %d%%",mRender->GetGpuUsage());
        mRender->DebugPrint(20,54,"free memory: %d kb (%d mb)",freeMemory/1024,(freeMemory/1024)/1024);
        mRender->DebugPrint(20,64,"polygons: %d",(mWorld->GetDrawntTrianglesCount() / 3));
        mRender->DebugPrint(20,74,"vertices: %d",mWorld->GetDrawntTrianglesCount());
        mRender->DebugPrint(20,84,"world time: %f",mWorld->worldDayTime);
        mRender->DebugPrint(20,94,"camera angle: %f",fppCam->horAngle);

        mRender->DebugPrint(20,104,"player.x: %f",playerPosition.x);
        mRender->DebugPrint(20,114,"player.y: %f",playerPosition.y);
        mRender->DebugPrint(20,124,"player.z: %f",playerPosition.z);

        mRender->DebugPrint(20,134,"walkingonground: %d",walkingOnGround);
        mRender->DebugPrint(20,144,"veloc.y: %f",playerVelocity.y);

        mRender->DebugPrint(20,154,"Chunks in process : %d",mWorld->toUpdate.size());

        if(mWorld->mZombies.size() > 0)
        {
            mRender->DebugPrint(20,184,"size of vector zombies : %d",mWorld->mZombies.size());
        }
        if(mWorld->mCows.size() > 0)
        {
            mRender->DebugPrint(20,194,"size of vector cows : %d",mWorld->mCows.size());
        }

        if(mWorld->mDrops.size() > 0)
        {
            mRender->DebugPrint(20,204," size of vector Drops : %i", mWorld->mDrops.size());
        }
        if(mWorld->updatingChunks.size() > 0)
        {
            mRender->DebugPrint(20,214," size of vector updatingChunks : %i", mWorld->updatingChunks.size());
        }
        if(mSnowBalls.size() > 0)
        {
            mRender->DebugPrint(20,224," size of vector SnowBalls : %i", mSnowBalls.size());
        }

        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);
    }

    //end frame
    mRender->EndFrame();
}

//additional functions
void StatePlay::advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice)
{
    int start, end;

    // blit maximizing the use of the texture-cache

    for (start = sx, end = sx+sw; start < end; start += slice, dx += slice)
    {
        TexturesPSPVertex16* vertices = (TexturesPSPVertex16*)sceGuGetMemory(2 * sizeof(TexturesPSPVertex16));
        int width = (start + slice) < end ? slice : end-start;

        vertices[0].u = start;
        vertices[0].v = sy;
        vertices[0].x = dx;
        vertices[0].y = dy;
        vertices[0].z = 0;

        vertices[1].u = start + width;
        vertices[1].v = sy + sh;
        vertices[1].x = dx + width;
        vertices[1].y = dy + sh;
        vertices[1].z = 0;

        sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
    }
}

bool StatePlay::TryToMove(Vector3 moveVector,float dt)
{
    // Build a "test vector" that is a little longer than the move vector.
    float moveLength = moveVector.magnitude();
    Vector3 testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.2f);

    // Apply this test vector.
    Vector3 movePosition = playerPosition + testVector;
    Vector3 midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    Vector3 lowerBodyPoint = movePosition + Vector3(0, -1.55f, 0);

    if (!mWorld->SolidAtPointForPlayer(movePosition) && !mWorld->SolidAtPointForPlayer(lowerBodyPoint) && !mWorld->SolidAtPointForPlayer(midBodyPoint))
    {
        playerPosition = playerPosition + moveVector;
        return true;
    }

    //teraz mo¿na robiæ ciekawe rzeczy

    testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.35f);
    movePosition = playerPosition + testVector;
    midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    lowerBodyPoint = movePosition + Vector3(0, -1.55f, 0);

    unsigned char lowerBlock = mWorld->BlockAtPoint(lowerBodyPoint);
    unsigned char midBlock = mWorld->BlockAtPoint(midBodyPoint);
    unsigned char upperBlock = mWorld->BlockAtPoint(movePosition);

    if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder1::getID())
    {
        if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
        {
            if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
            {
                playerVelocity.y = CLIMBVELOCITY;
                Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
                if (mWorld->SolidAtPointForPlayer(footPosition))
                    playerPosition.y += 0.1f;
                return true;
            }
        }
    }

    if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder2::getID())
    {
        if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
        {
            if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
            {
                playerVelocity.y = CLIMBVELOCITY;
                Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
                if (mWorld->SolidAtPointForPlayer(footPosition))
                    playerPosition.y += 0.1f;
                return true;
            }
        }
    }

    if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder3::getID())
    {
        if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
        {
            if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
            {
                playerVelocity.y = CLIMBVELOCITY;
                Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
                if (mWorld->SolidAtPointForPlayer(footPosition))
                    playerPosition.y += 0.1f;
                return true;
            }
        }
    }

    if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder4::getID())
    {
        if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
        {
            if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
            {
                playerVelocity.y = CLIMBVELOCITY;
                Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
                if (mWorld->SolidAtPointForPlayer(footPosition))
                    playerPosition.y += 0.1f;
                return true;
            }
        }
    }

    if (upperBlock == 6 || lowerBlock == 6 || midBlock == 6)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 82 || lowerBlock == 82 || midBlock == 82)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 83 || lowerBlock == 83 || midBlock == 83)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 84 || lowerBlock == 84 || midBlock == 84)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 85 || lowerBlock == 85 || midBlock == 85)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 86 || lowerBlock == 86 || midBlock == 86)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 87 || lowerBlock == 87 || midBlock == 87)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 88 || lowerBlock == 88 || midBlock == 88)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 89 || lowerBlock == 89 || midBlock == 89)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 90 || lowerBlock == 90 || midBlock == 90)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }



    return false;
}

bool StatePlay::keyPressed(int currentKey)
{
    //analog reset
    if(analogUp)
    {
        if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYup)
            analogUp = false;
    }
    if(analogDown)
    {
        if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYdown)
            analogDown = false;
    }
    if(analogLeft)
    {
        if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXleft)
            analogLeft = false;
    }
    if(analogRight)
    {
        if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXright)
            analogRight = false;
    }

    //keys
    if(currentKey == 0)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
    {
        if(!analogUp)
        {
            if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup)
            {
                analogUp = true;
                return true;//analog up
            }
        }
    }
    if(currentKey == 11)//cross
    {
        if(!analogDown)
        {
            if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown)
            {
                analogDown = true;
                return true;//analog down
            }
        }
    }
    if(currentKey == 13)//cross
    {
        if(!analogLeft)
        {
            if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft)
            {
                analogLeft = true;
                return true;//analog left
            }
        }
    }
    if(currentKey == 14)//cross
    {
        if(!analogRight)
        {
            if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright)
            {
                analogRight = true;
                return true;//analog right
            }
        }
    }

    return false;
}

bool StatePlay::keyHold(int currentKey)
{
    if(currentKey == 0)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
        return (mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup);//analog up
    if(currentKey == 11)//cross
        return (mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown);//analog down
    if(currentKey == 13)//cross
        return (mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft);//analog left
    if(currentKey == 14)//cross
        return (mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright);//analog right

    return false;
}


void StatePlay::HungerTime()
{
    if(mWorld->HG >= 15)
    {
        if (rand() % 3 == 1)
        {
            mWorld->HG -= 1;
        }
    }
    else
    {
        mWorld->HG -= 1;
    }
    if(mWorld->HG < 0)
    {
        mWorld->HG = 0;
    }
}

void StatePlay::HealthTime()
{
    if(mWorld->HG < 1 && mWorld->HP > 0)
    {
        HurtPlayer(2);
    }

    if(mWorld->HG >= 18)
    {
        if(mWorld->HP > 0)
        {
            mWorld->HP += 1;
        }
    }

    if(mWorld->HP > 20)
    {
        mWorld->HP = 20;
    }
}

void StatePlay::OxygenTime()
{
    if(mWorld->OS <= 0)
    {
        HurtPlayer(2);
    }
    if(mWorld->OS > 0)
    {
        mWorld->OS -= 1;
    }
}

void StatePlay::HurtPlayer(float damage)
{
    mSoundMgr->PlayHitSound();
    mWorld->HP -= damage*(1-(mWorld->AP-damage/2.0f)/30.0f);
    mWorld->mainStatistics.damageRecieved += damage*(1-(mWorld->AP-damage/2.0f)/30.0f);

    if(mWorld->HP > 0)
    {
        hurt = true;
        hurt_time = 1.0f;
        hpAnim = 0.0f;
    }
}

void StatePlay::PutInInventory(int id, int num, bool st)
{
    bool ok;
    ok = false;
    for(int j = 27; j <= 35; j++)
    {
        if (mWorld->invSt[j]==1)
        {
            if (mWorld->invId[j]== id)
            {
                if(mWorld->invAm[j] + num <= 64)
                {
                    mWorld->invAm[j] += num;
                    chestId = -1;
                    ok = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (mWorld->invId[j]== -1)
        {
            mWorld->invSt[j] = st;
            mWorld->invId[j] = id;
            mWorld->invAm[j] = num;
            ok = true;
            break;
        }
    }

    if(ok == false)
    {
        for(int j = 0; j <= 26; j++)
        {
            if (mWorld->invSt[j]==1)
            {
                if (mWorld->invId[j]== id)
                {
                    if(mWorld->invAm[j] + num <= 64)
                    {
                        mWorld->invAm[j] += num;
                        chestId = -1;
                        break;
                        return;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            if (mWorld->invId[j]== -1)
            {
                mWorld->invSt[j] = st;
                mWorld->invId[j] = id;
                mWorld->invAm[j] = num;
                break;
                return;
            }
        }
    }
}

void StatePlay::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0x00000200|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

void StatePlay::DrawText2(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0x00004000|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

void StatePlay::DrawAmount(int x,int y, int amount)
{
    int dozens, units;

    dozens = floorf(amount / 10.0f);
    units = amount % 10;

    if(dozens != 0)
    {
        RenderManager::InstancePtr()->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1.0f),0,0x00000400|0x00004000);
        RenderManager::InstancePtr()->DebugPrint(x+2,y+2,"%i",dozens);
        RenderManager::InstancePtr()->SetFontStyle(default_big_size,GU_COLOR(1.0f,1.0f,1.0f,1.0f),0,0x00000400|0x00004000);
        RenderManager::InstancePtr()->DebugPrint(x,y,"%i",dozens);
    }

    RenderManager::InstancePtr()->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1.0f),0,0x00000400|0x00004000);
    RenderManager::InstancePtr()->DebugPrint(x+14,y+2,"%i",units);
    RenderManager::InstancePtr()->SetFontStyle(default_big_size,GU_COLOR(1.0f,1.0f,1.0f,1.0f),0,0x00000400|0x00004000);
    RenderManager::InstancePtr()->DebugPrint(x+12,y,"%i",units);
}

