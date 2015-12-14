#include "CraftWorld2.h"
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include "TextureHelper.h"

#include <string.h>
#include <zlib.h>
#define PI 3.1415926535897f
#include "Zombie2.h"
#include "Cow2.h"

CraftWorld::CraftWorld()
{
    //srand(time(NULL));
    WORLD_SIZE = 0;
    CHUNK_SIZE = 0;
    WORLD_HEIGHT = 0;

    // Инициализируем переменные статистики
    mainStatistics.blockPlaced = 0;
    mainStatistics.blockDestroyed = 0;
    mainStatistics.daysInGame = 0;
    mainStatistics.minutesPlayed = 0;
    mainStatistics.itemsCrafted = 0;
    mainStatistics.itemsSmelted = 0;
    mainStatistics.jumps = 0;
    mainStatistics.dies = 0;
    mainStatistics.foodEaten = 0;
    mainStatistics.badlyFalls = 0;
    mainStatistics.blocksWalked = 0;
    mainStatistics.treesGrowned = 0;
    mainStatistics.cropsGrowned = 0;
    mainStatistics.soilPlowed = 0;
    mainStatistics.timeInAir = 0;
    mainStatistics.timeInWater = 0;
    mainStatistics.damageRecieved = 0;
    // end

    // Инициализируем переменные опций
    mainOptions.cloudsRender = 1;
    mainOptions.fakeShadowsRendering = 1;
    mainOptions.sounds = 1;
    mainOptions.music = 1;
    mainOptions.fogRendering = 1;
    mainOptions.fastRendering = 0;
    mainOptions.headBob = 1;
    mainOptions.fov = 70;
    mainOptions.sunMoodRendering = 1;
    mainOptions.worldBlockAnimation = 1;
    mainOptions.particles = 0;
    mainOptions.difficult = 2; // normal
    mainOptions.horizontalViewDistance = 3;
    mainOptions.verticalViewDistance = 1;
    mainOptions.guiDrawing = 1;
    // end

    worldTime = 0.0f;
    skyTime = 112.0f;

    playerZoneSize = Vector3(48,16,48); // Зона прорисовки чанков (каждый параметр должен быть кратен 16)

    updateChunksSwitch = false;
    updateChunkTimer = 0.0f;

    chunksCreatedInFrameCount = 0;
    transparentchunksCreatedInFrameCount = 0;
    animatedchunksCreatedInFrameCount = 0;

    mId = -1;
    mAm = -1;
    mSt = 0;

    worldSeed = 0;

    HP = 20;
    HG = 20;
    OS = 10;
    AP = 0;

    worldTime = 0.0f;
    worldDayTime = 12.0f;
    worldHour = 0.0f;

    worldVersion = 3;

    mChestsize = 0;
    mFurnacesize = 0;
    mZombiesize = 0;
    mDirectsize = 0;
    mCowsize = 0;

    zombieNum = 0;
    dropNum = 0;
    spawnMobsTimer = 0.0f;

    updatingChunksTimer = 0.0f;
    updatingChunksTimerMax = 1.0f;
    updatingChunksPosition = 0;

    gameModeWorld = 0;
    gameLocked = false;
    //Воздух
    blockTypes.push_back(BaseBlock());
    //Нормальные блоки
    blockTypes.push_back(GrassBlock());
    blockTypes.push_back(DirtBlock());
    blockTypes.push_back(RockBlock());
    blockTypes.push_back(WaterBlock());
    blockTypes.push_back(GoldBlock());
    blockTypes.push_back(LadderBlock());
    blockTypes.push_back(SandBlock());
    blockTypes.push_back(WoodBlock());
    blockTypes.push_back(LeavesBlock());

    blockTypes.push_back(BlackWoolBlock());
    blockTypes.push_back(GrayWoolBlock());
    blockTypes.push_back(RedWoolBlock());
    blockTypes.push_back(PinkWoolBlock());
    blockTypes.push_back(DarkGreenWoolBlock());
    blockTypes.push_back(GreenWoolBlock());
    blockTypes.push_back(BrownWoolBlock());
    blockTypes.push_back(YellowWoolBlock());
    blockTypes.push_back(BlueWoolBlock());

    blockTypes.push_back(LightBlueWoolBlock());
    blockTypes.push_back(VioletWoolBlock());
    blockTypes.push_back(PastelWoolBlock());
    blockTypes.push_back(OrangeWoolBlock());
    blockTypes.push_back(LightGrayWoolBlock());
    blockTypes.push_back(WhiteWoolBlock());
    blockTypes.push_back(CactusBlock());
    blockTypes.push_back(SandStone());
    blockTypes.push_back(BrickBlock());

    blockTypes.push_back(CageBlock());
    blockTypes.push_back(SnowBlock());
    blockTypes.push_back(DarkWoodBlock());
    blockTypes.push_back(WhiteWoodBlock());
    blockTypes.push_back(IceBlock());
    blockTypes.push_back(CaneBlock());
    blockTypes.push_back(Planks());
    blockTypes.push_back(ShelfBlock());
    blockTypes.push_back(CobbleStone());

    blockTypes.push_back(SpruceLeaves());
    blockTypes.push_back(BirchLeaves());
    blockTypes.push_back(Sponge());
    blockTypes.push_back(GlassBlock());
    blockTypes.push_back(IronOre());
    blockTypes.push_back(CoalOre());
    blockTypes.push_back(DiamondOre());
    blockTypes.push_back(RedstoneOre());
    blockTypes.push_back(LapisOre());

    blockTypes.push_back(Obsidian());
    blockTypes.push_back(JackOLantern());
    blockTypes.push_back(Torch());
    blockTypes.push_back(Door1());
    blockTypes.push_back(Door2());
    blockTypes.push_back(Door3());
    blockTypes.push_back(Door4());
    blockTypes.push_back(Door5());
    blockTypes.push_back(Door6());

    blockTypes.push_back(Door7());
    blockTypes.push_back(Door8());
    blockTypes.push_back(Door9());
    blockTypes.push_back(Door10());
    blockTypes.push_back(WoodenFence());
    blockTypes.push_back(CobbleStair1());
    blockTypes.push_back(CobbleStair2());
    blockTypes.push_back(CobbleStair3());
    blockTypes.push_back(CobbleStair4());

    blockTypes.push_back(Diamond());
    blockTypes.push_back(Gold());
    blockTypes.push_back(Iron());
    blockTypes.push_back(BrickStair1());
    blockTypes.push_back(BrickStair2());
    blockTypes.push_back(BrickStair3());
    blockTypes.push_back(BrickStair4());
    blockTypes.push_back(NoteBlock());
    blockTypes.push_back(JukeBox());

    blockTypes.push_back(Pumpkin1());
    blockTypes.push_back(Pumpkin2());
    blockTypes.push_back(Pumpkin3());
    blockTypes.push_back(Pumpkin4());
    blockTypes.push_back(Mooshroom1());
    blockTypes.push_back(Mooshroom2());
    blockTypes.push_back(Soil());
    blockTypes.push_back(WateredSoil());
    blockTypes.push_back(MelonBlock());

    blockTypes.push_back(WoodenHalfBlock());
    blockTypes.push_back(CobbleHalfBlock());
    blockTypes.push_back(BrickHalfBlock());
    blockTypes.push_back(Slab());
    blockTypes.push_back(StoneSandHalfBlock());
    blockTypes.push_back(Ladder1());
    blockTypes.push_back(Ladder2());
    blockTypes.push_back(Ladder3());
    blockTypes.push_back(Ladder4());

    blockTypes.push_back(Cake());
    blockTypes.push_back(MossyCobblestone());
    blockTypes.push_back(Snow2());
    blockTypes.push_back(ChestBlock1());
    blockTypes.push_back(ChestBlock2());
    blockTypes.push_back(ChestBlock3());
    blockTypes.push_back(ChestBlock4());
    blockTypes.push_back(ChestLock());
    blockTypes.push_back(ClayBlock());

    blockTypes.push_back(Chest5());
    blockTypes.push_back(LapisBlock());
    blockTypes.push_back(StoneBrick());
    blockTypes.push_back(CrackedStoneBrick());
    blockTypes.push_back(CarvedStoneBrick());
    blockTypes.push_back(CraftingTable());
    blockTypes.push_back(FurnaceOff());
    blockTypes.push_back(FurnaceOn());
    blockTypes.push_back(HalfStoneBrick());

    blockTypes.push_back(Furnace6());
    blockTypes.push_back(TNT());
    blockTypes.push_back(Nuclear());
    blockTypes.push_back(Lava());
    blockTypes.push_back(Gravel());
    blockTypes.push_back(LavaStone());
    blockTypes.push_back(LavaObsidian());
    blockTypes.push_back(TallGrass());
    blockTypes.push_back(Fern());

    blockTypes.push_back(DrySapling());
    blockTypes.push_back(Flower1());
    blockTypes.push_back(Flower2());
    blockTypes.push_back(OakSapling());
    blockTypes.push_back(SpruceSapling());
    blockTypes.push_back(BirchSapling());
    blockTypes.push_back(FreeBlock5());
    blockTypes.push_back(WoodenStair1());
    blockTypes.push_back(WoodenStair2());

    blockTypes.push_back(WoodenStair3());
    blockTypes.push_back(WoodenStair4());
    blockTypes.push_back(Marble());
    blockTypes.push_back(MelonPlant1());
    blockTypes.push_back(MelonPlant2());
    blockTypes.push_back(MelonPlant3());
    blockTypes.push_back(MelonPlant4());

    blockTypes.push_back(WheatBlock1());
    blockTypes.push_back(WheatBlock2());
    blockTypes.push_back(WheatBlock3());
    blockTypes.push_back(WheatBlock4());

    blockTypes.push_back(FreeBlock3());
    blockTypes.push_back(FreeBlock4());
    blockTypes.push_back(WorldSky());
    blockTypes.push_back(Cloud());
    blockTypes.push_back(IronBlock());

    //Предметы
    itemTypes.push_back(WoodenPickaxe());
    itemTypes.push_back(StonePickaxe());
    itemTypes.push_back(IronPickaxe());
    itemTypes.push_back(DiamondPickaxe());
    itemTypes.push_back(GoldenPickaxe());

    itemTypes.push_back(WoodenSword());
    itemTypes.push_back(StoneSword());
    itemTypes.push_back(IronSword());
    itemTypes.push_back(DiamondSword());
    itemTypes.push_back(GoldenSword());

    itemTypes.push_back(WoodenShovel());
    itemTypes.push_back(StoneShovel());
    itemTypes.push_back(IronShovel());
    itemTypes.push_back(DiamondShovel());
    itemTypes.push_back(GoldenShovel());

    itemTypes.push_back(WoodenAxe());
    itemTypes.push_back(StoneAxe());
    itemTypes.push_back(IronAxe());
    itemTypes.push_back(DiamondAxe());
    itemTypes.push_back(GoldenAxe());

    itemTypes.push_back(WoodenHoe());
    itemTypes.push_back(StoneHoe());
    itemTypes.push_back(IronHoe());
    itemTypes.push_back(DiamondHoe());
    itemTypes.push_back(GoldenHoe());

    itemTypes.push_back(Scissors());
    itemTypes.push_back(Stick());
    itemTypes.push_back(Coal());
    itemTypes.push_back(IronBar());
    itemTypes.push_back(DiamondItem());

    itemTypes.push_back(GoldenBar());
    itemTypes.push_back(FireItem());
    itemTypes.push_back(LigniteCoal());
    itemTypes.push_back(Clay());
    itemTypes.push_back(Apple());
    itemTypes.push_back(GoldenApple());

    itemTypes.push_back(WheatSeeds());
    itemTypes.push_back(Wheat());
    itemTypes.push_back(WhiteBread());
    itemTypes.push_back(Brick());
    itemTypes.push_back(Busket());
    itemTypes.push_back(WaterBusket());
    itemTypes.push_back(LavaBusket());

    itemTypes.push_back(CaneItem());
    itemTypes.push_back(Flower1Item());
    itemTypes.push_back(Flower2Item());
    itemTypes.push_back(OakSaplingItem());
    itemTypes.push_back(Paper());
    itemTypes.push_back(Book());
    itemTypes.push_back(SnowBallItem());

    itemTypes.push_back(MooshroomItem1());
    itemTypes.push_back(MooshroomItem2());
    itemTypes.push_back(Bowl());
    itemTypes.push_back(MooshroomBowl());

    itemTypes.push_back(IronWateringCan());
    itemTypes.push_back(DiamondWateringCan());
    itemTypes.push_back(DoorItem());
    itemTypes.push_back(LadderItem());
    itemTypes.push_back(TorchItem());
    itemTypes.push_back(SpruceSaplingItem());
    itemTypes.push_back(BirchSaplingItem());

    itemTypes.push_back(MelonItem());
    itemTypes.push_back(MelonSeeds());
    itemTypes.push_back(Sugar());
    itemTypes.push_back(CocoaBeans());
    itemTypes.push_back(Cookie());
    itemTypes.push_back(RawBeef());
    itemTypes.push_back(Steak());
    itemTypes.push_back(LapisLazuli());
    itemTypes.push_back(MilkBusket());
    itemTypes.push_back(CakeItem());
    itemTypes.push_back(Bone());
    itemTypes.push_back(BoneMeal());
    itemTypes.push_back(Leather());

    itemTypes.push_back(SampleHelmet());
    itemTypes.push_back(SampleChestplate());
    itemTypes.push_back(SampleLeggings());
    itemTypes.push_back(SampleBoots());

    itemTypes.push_back(LeatherHelmet());
    itemTypes.push_back(LeatherChestplate());
    itemTypes.push_back(LeatherLeggings());
    itemTypes.push_back(LeatherBoots());

    itemTypes.push_back(ChainmailHelmet());
    itemTypes.push_back(ChainmailChestplate());
    itemTypes.push_back(ChainmailLeggings());
    itemTypes.push_back(ChainmailBoots());

    itemTypes.push_back(IronHelmet());
    itemTypes.push_back(IronChestplate());
    itemTypes.push_back(IronLeggings());
    itemTypes.push_back(IronBoots());

    itemTypes.push_back(DiamondHelmet());
    itemTypes.push_back(DiamondChestplate());
    itemTypes.push_back(DiamondLeggings());
    itemTypes.push_back(DiamondBoots());

    itemTypes.push_back(GoldenHelmet());
    itemTypes.push_back(GoldenChestplate());
    itemTypes.push_back(GoldenLeggings());
    itemTypes.push_back(GoldenBoots());

    itemTypes.push_back(RottenFlesh());

    for(int o = 0; o <= 35; o += 1) // Инициализация инвентаря
    {
        invAm[o] = -1; // Количество вещей в ячейки = -1 (0)
        invId[o] = -1; // Id вещей в ячейке = -1 (ячейка пуста)
        invSt[o] = false; // Вещь в ячейке не стакается (по умолчанию)
    }

    for(int o = 0; o <= 3; o += 1)
    {
        armorId[o] = 324+o;
        armorAm[o] = -1;
        armorSt[o] = false;
    }


    timee = 0.0f;
    lightShadowFactor = 0.31f;
    lightFactor = Vector3(1.0f,1.0f,1.0f);

    startSkyColor = Vector3(166,207,229);
	endSkyColor = Vector3(76,136,210);
	dawnSunsetSkyColor = Vector3(219,136,46);

	startSkyColor *= 1.0f/255.0f;
	endSkyColor *= 1.0f/255.0f;
	dawnSunsetSkyColor *= 1.0f/255.0f;

    brightFactor = 0;
    dawnSunsetFactor = 0.0f;

    bodyVertices = NULL;
    headVertices = NULL;
    legVertices = NULL;
    handVertices = NULL;

    cowBodyVertices = NULL;
    cowHeadVertices = NULL;
    cowLegVertices = NULL;

    helmetVertices = NULL;
    shoulderVertices = NULL;
    chestplateVertices = NULL;
    leggingVertices = NULL;
    bootVertices = NULL;

    kickedStart = false;
    kickedAngle = 0.0f;
    kickedTimer = 0.0f;

    iVertexLeftRight = 0;
    pointsLeftRight = 0;
    iVertexBackFront = 0;
    pointsBackFront = 0;
    iVertexBottomTop = 0;
    pointsBottomTop = 0;

    textureTerrainId = 0;
    textureItemsId = 0;
    textureWaterAnimationId = 0;
    textureLavaAnimationId = 0;
    textureLeatherArmor1Id = 0;
    textureLeatherArmor2Id = 0;
    textureChainArmor1Id = 0;
    textureChainArmor2Id = 0;
    textureIronArmor1Id = 0;
    textureIronArmor2Id = 0;
    textureDiamondArmor1Id = 0;
    textureDiamondArmor2Id = 0;
    textureGoldenArmor1Id = 0;
    textureGoldenArmor2Id = 0;

    animationTimer = 0.0f;
    animationTimerEnd = 0.085f;
    animationWaterFrame = 0;
    animationLavaFrame = 0;

    animationLavaStep = true;
}

CraftWorld::~CraftWorld()
{
    free(m_Blocks);
    free(m_BlockLight);
    free(m_BlockSettings);

    //delete chests
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        delete mChunks[i];
    }
    mChunks.clear();

    //water chunks
    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        delete mTransparentChunks[i];
    }
    mTransparentChunks.clear();

    for(unsigned int i = 0; i < mChests.size(); i++)
    {
        delete mChests[i];
    }
    mChests.clear();

    //delete furnace
    for(unsigned int i = 0; i < mFurnaces.size(); i++)
    {
        delete mFurnaces[i];
    }
    mFurnaces.clear();

    //delete all direction mind blocks
    for(unsigned int i = 0; i < mDirects.size(); i++)
    {
        delete mDirects[i];
    }
    mDirects.clear();

    //delete all zombies
    for(unsigned int i = 0; i < mZombies.size(); i++)
    {
        delete mZombies[i];
    }
    mZombies.clear();

    //delete all cows
    for(unsigned int i = 0; i < mCows.size(); i++)
    {
        delete mCows[i];
    }
    mCows.clear();

    if(mDrops.empty() == false)
    {
        for(unsigned int i = 0; i < mDrops.size(); i++)
        {
            delete mDrops[i];
        }
        mDrops.clear();
    }

    blockTypes.clear();
    itemTypes.clear();
    toUpdate.clear();
    updatingChunks.clear();

    free(bodyVertices);
    free(headVertices);
    free(legVertices);
    free(handVertices);

    free(cowBodyVertices);
    free(cowHeadVertices);
    free(cowLegVertices);

    free(helmetVertices);
    free(shoulderVertices);
    free(chestplateVertices);
   // free(bellyVertices);
    free(leggingVertices);
    free(bootVertices);
}

void CraftWorld::SaveCompressedWorld(std::string  filename) // Сохранение мира
{
    //first save version and name on normal file
    FILE * pFile;
    pFile = fopen(filename.c_str(),"wb");

    if(pFile == NULL)
        return;

    //version
    fwrite(&worldVersion,sizeof(int),1,pFile);

    //game mode
    fwrite(&gameModeWorld,sizeof(char),1,pFile);

    //game mode
    fwrite(&gameLocked,sizeof(bool),1,pFile);

    //name
    fwrite(worldName,sizeof(char),50,pFile);

    //close file
    fclose(pFile);

    //now save compressed map info
    filename = filename + "c";

    //open file
    gzFile saveFile;
    saveFile = gzopen(filename.c_str(),"wb");
    if(saveFile == 0)
        return;

    //player pos
    gzwrite(saveFile, &playerPos.x,sizeof(float));
    gzwrite(saveFile, &playerPos.y,sizeof(float));
    gzwrite(saveFile, &playerPos.z,sizeof(float));

    //size
    gzwrite(saveFile, &WORLD_SIZE,sizeof(int));

    //size
    gzwrite(saveFile, &WORLD_HEIGHT,sizeof(int));

    //chunksize
    gzwrite(saveFile, &CHUNK_SIZE,sizeof(int));

    //cubes
    gzwrite(saveFile, m_Blocks,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

    //light
    gzwrite(saveFile, m_BlockLight,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

    //settings
    gzwrite(saveFile, m_BlockSettings,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

    //world time
    gzwrite(saveFile, &worldDayTime,sizeof(float));
    //sun time
    //gzwrite(saveFile, &sunTime,sizeof(float));

    gzwrite(saveFile, &mainStatistics,sizeof(st));

    gzwrite(saveFile, &mainOptions,sizeof(opt));

    gzwrite(saveFile, &invId,sizeof(short)*(36));

    gzwrite(saveFile, &invAm,sizeof(short)*(36));

    gzwrite(saveFile, &invSt,sizeof(bool)*(36));

    gzwrite(saveFile, &armorId,sizeof(short)*(4));

    gzwrite(saveFile, &armorAm,sizeof(short)*(4));

    gzwrite(saveFile, &armorSt,sizeof(bool)*(4));

    gzwrite(saveFile, &HP,sizeof(unsigned int));

    gzwrite(saveFile, &HG,sizeof(unsigned int));

    gzwrite(saveFile, &OS,sizeof(unsigned int));

    gzwrite(saveFile, &brightFactor,sizeof(float));

    gzwrite(saveFile, &worldSeed,sizeof(int));

    gzwrite(saveFile, &skyTime,sizeof(float));

    mChestsize = mChests.size();
    gzwrite(saveFile, &mChestsize,sizeof(int));

    if(mChestsize != 0)
    {
        int* data1 = new int[27*mChestsize];
        int* data2 = new int[27*mChestsize];
        bool* data3 = new bool[27*mChestsize];

        int* data4 = new int[mChestsize];

        for(int k = 0; k < mChestsize; k++)
        {
            Chest* SaveChest = mChests[k];
            for(int l = 0; l <= 26; l++)
            {
                data1[k*27+l] = SaveChest->chestSlotId[l];
                data2[k*27+l] = SaveChest->chestSlotAm[l];
                data3[k*27+l] = SaveChest->chestSlotSt[l];
            }

            data4[k] = SaveChest->chestAddress;
        }

        gzwrite(saveFile, data1,sizeof(int) * (mChestsize*27));
        gzwrite(saveFile, data2,sizeof(int) * (mChestsize*27));
        gzwrite(saveFile, data3,sizeof(bool) * (mChestsize*27));

        gzwrite(saveFile, data4,sizeof(int)*(mChestsize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
    }

    mFurnacesize = mFurnaces.size();
    gzwrite(saveFile, &mFurnacesize,sizeof(int));

    if(mFurnacesize != 0)
    {
        int* data1 = new int[3*mFurnacesize];
        int* data2 = new int[3*mFurnacesize];
        bool* data3 = new bool[3*mFurnacesize];

        int* data4 = new int[mFurnacesize];
        int* data5 = new int[mFurnacesize];
        int* data6 = new int[mFurnacesize];

        float* data7 = new float[mFurnacesize];
        float* data8 = new float[mFurnacesize];
        int* data10 = new int[mFurnacesize];

        for(int k = 0; k < mFurnacesize; k++)
        {
            Furnace* SaveFurnace = mFurnaces[k];
            for(int l = 0; l <= 2; l++)
            {
                data1[k*3+l] = SaveFurnace->furnaceSlotId[l];
                data2[k*3+l] = SaveFurnace->furnaceSlotAm[l];
                data3[k*3+l] = SaveFurnace->furnaceSlotSt[l];
            }
            data4[k] = SaveFurnace->furnaceX;
            data5[k] = SaveFurnace->furnaceY;
            data6[k] = SaveFurnace->furnaceZ;

            data7[k] = SaveFurnace->fuelTime;
            data8[k] = SaveFurnace->meltingTime;
            data10[k] = SaveFurnace->smeltItemTemp;
        }

        gzwrite(saveFile, data1,sizeof(int) * (mFurnacesize*3));
        gzwrite(saveFile, data2,sizeof(int) * (mFurnacesize*3));
        gzwrite(saveFile, data3,sizeof(bool) *(mFurnacesize*3));

        gzwrite(saveFile, data4,sizeof(int)*(mFurnacesize));
        gzwrite(saveFile, data5,sizeof(int)*(mFurnacesize));
        gzwrite(saveFile, data6,sizeof(int)*(mFurnacesize));

        gzwrite(saveFile, data7,sizeof(float)*(mFurnacesize));
        gzwrite(saveFile, data8,sizeof(float)*(mFurnacesize));
        gzwrite(saveFile, data10,sizeof(int)*(mFurnacesize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
        delete[] data7;
        delete[] data8;
        delete[] data10;
    }

    mZombiesize = mZombies.size();
    gzwrite(saveFile, &mZombiesize,sizeof(int));

    if(mZombiesize != 0)
    {
        float* data1 = new float[mZombiesize]; // x
        float* data2 = new float[mZombiesize]; // y
        float* data3 = new float[mZombiesize]; // z

        float* data4 = new float[mZombiesize]; // mainAngle
        float* data5 = new float[mZombiesize]; // health
        int* data6 = new int[mZombiesize]; // id

        int* data7 = new int[mZombiesize]; // helmet id
        int* data8 = new int[mZombiesize]; // chestplate id
        int* data9 = new int[mZombiesize]; // leggings id
        int* data10 = new int[mZombiesize]; // boots id

        for(int k = 0; k < mZombiesize; k++)
        {
            Zombie* SaveZombie = mZombies[k];

            data1[k] = SaveZombie->position.x;
            data2[k] = SaveZombie->position.y;
            data3[k] = SaveZombie->position.z;

            data4[k] = SaveZombie->mainAngle;
            data5[k] = SaveZombie->HP;
            data6[k] = SaveZombie->number;

            data7[k] = SaveZombie->helmetId;
            data8[k] = SaveZombie->chestplateId;
            data9[k] = SaveZombie->leggingsId;
            data10[k] = SaveZombie->bootsId;
        }

        gzwrite(saveFile, data1,sizeof(float) * (mZombiesize));
        gzwrite(saveFile, data2,sizeof(float) * (mZombiesize));
        gzwrite(saveFile, data3,sizeof(float) *(mZombiesize));

        gzwrite(saveFile, data4,sizeof(float)*(mZombiesize));
        gzwrite(saveFile, data5,sizeof(float)*(mZombiesize));
        gzwrite(saveFile, data6,sizeof(int)*(mZombiesize));

        gzwrite(saveFile, data7,sizeof(int)*(mZombiesize));
        gzwrite(saveFile, data8,sizeof(int)*(mZombiesize));
        gzwrite(saveFile, data9,sizeof(int)*(mZombiesize));
        gzwrite(saveFile, data10,sizeof(int)*(mZombiesize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
        delete[] data7;
        delete[] data8;
        delete[] data9;
        delete[] data10;
    }


    mCowsize = mCows.size();
    gzwrite(saveFile, &mCowsize,sizeof(int));

    if(mCowsize != 0)
    {
        float* data1 = new float[mCowsize]; // x
        float* data2 = new float[mCowsize]; // y
        float* data3 = new float[mCowsize]; // z

        float* data4 = new float[mCowsize]; // mainAngle
        float* data5 = new float[mCowsize]; // health
        int* data6 = new int[mCowsize]; // id

        for(int k = 0; k < mCowsize; k++)
        {
            Cow* SaveCow = mCows[k];

            data1[k] = SaveCow->position.x;
            data2[k] = SaveCow->position.y;
            data3[k] = SaveCow->position.z;

            data4[k] = SaveCow->mainAngle;
            data5[k] = SaveCow->HP;
            data6[k] = SaveCow->number;
        }

        gzwrite(saveFile, data1,sizeof(float) * (mCowsize));
        gzwrite(saveFile, data2,sizeof(float) * (mCowsize));
        gzwrite(saveFile, data3,sizeof(float) *(mCowsize));

        gzwrite(saveFile, data4,sizeof(float)*(mCowsize));
        gzwrite(saveFile, data5,sizeof(float)*(mCowsize));
        gzwrite(saveFile, data6,sizeof(int)*(mCowsize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
    }

    gzwrite(saveFile, &zombieNum,sizeof(int));


    /*mDirectsize = mDirects.size();
    gzwrite(saveFile, &mDirectsize,sizeof(int));

    if(mDirectsize != 0)
    {
        int* data1 = new int[mDirectsize];
        int* data2 = new int[mDirectsize];
        int* data3 = new int[mDirectsize];

        char* data4 = new char[mDirectsize];

        for(int k = 0; k < mDirectsize; k++)
        {
            DirectionBlock* SaveDirectionBlock = mDirects[k];

            data1[k] = SaveDirectionBlock->X;
            data2[k] = SaveDirectionBlock->Y;
            data3[k] = SaveDirectionBlock->Z;
            data4[k] = SaveDirectionBlock->direction;
        }

        gzwrite(saveFile, data1,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data2,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data3,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data4,sizeof(char)* (mDirectsize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
    }*/
    //close file
    gzclose(saveFile);
    saveFile=0;
}

void CraftWorld::LoadWorld(const char *filename)
{
    FILE * pFile;
    pFile = fopen(filename,"rb");

    if(pFile == NULL)
        return;

    //version
    fread(&worldVersion,sizeof(int),1,pFile);

    //name
    fread(worldName,sizeof(char),50,pFile);

    //size
    fread(&WORLD_SIZE,sizeof(int),1,pFile);

    //chunksize
    fread(&CHUNK_SIZE,sizeof(int),1,pFile);

    //cubes
    m_Blocks = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    fread(m_Blocks,sizeof(unsigned char),(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE),pFile);

    //light
    m_BlockLight = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    fread(m_BlockLight,sizeof(unsigned char),(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE),pFile);

    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE);

    //close file
    fclose(pFile);
}

void CraftWorld::LoadCompressedWorld(std::string  filename) // Загрузка мира
{
    //load normal save info
    FILE * pFile;
    pFile = fopen(filename.c_str(),"rb");

    if(pFile == NULL)
        return;

    //version
    fread(&worldVersion,sizeof(int),1,pFile);

    fread(&gameModeWorld,sizeof(char),1,pFile);

    fread(&gameLocked,sizeof(bool),1,pFile);
    //name
    fread(worldName,sizeof(char),50,pFile);
    //close file
    fclose(pFile);

    //load compressed map data
    filename = filename + "c";

    //open file
    gzFile saveFile;
    saveFile = gzopen(filename.c_str(),"rb");
    if(saveFile == 0)
        return;

    //player pos
    gzread(saveFile, &playerPos.x,sizeof(float));
    gzread(saveFile, &playerPos.y,sizeof(float));
    gzread(saveFile, &playerPos.z,sizeof(float));

    //size
    gzread(saveFile, &WORLD_SIZE,sizeof(int));

    //size
    gzread(saveFile, &WORLD_HEIGHT,sizeof(int));

    //chunksize
    gzread(saveFile, &CHUNK_SIZE,sizeof(int));

    //cubes
    m_Blocks = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    gzread(saveFile, m_Blocks,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

    //light
    m_BlockLight = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    gzread(saveFile, m_BlockLight,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

    //settings
    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    if(worldVersion >= 3)
    {
        //settings
        gzread(saveFile, m_BlockSettings,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

        //world time
        gzread(saveFile, &worldDayTime,sizeof(float));

        //sun time
        //gzread(saveFile, &sunTime,sizeof(float));

        gzread(saveFile, &mainStatistics,sizeof(st));

        gzread(saveFile, &mainOptions,sizeof(opt));

        gzread(saveFile, &invId,sizeof(short)*(36));

        gzread(saveFile, &invAm,sizeof(short)*(36));

        gzread(saveFile, &invSt,sizeof(bool)*(36));

        gzread(saveFile, &armorId,sizeof(short)*(4));

        gzread(saveFile, &armorAm,sizeof(short)*(4));

        gzread(saveFile, &armorSt,sizeof(bool)*(4));

        gzread(saveFile, &HP,sizeof(unsigned int));

        gzread(saveFile, &HG,sizeof(unsigned int));

        gzread(saveFile, &OS,sizeof(unsigned int));

        gzread(saveFile, &brightFactor,sizeof(float));

        gzread(saveFile, &worldSeed,sizeof(int));

        gzread(saveFile, &skyTime,sizeof(float));

        gzread(saveFile, &mChestsize,sizeof(int));


        mChests.clear();

        if(mChestsize != 0)
        {
            int* data1 = new int[27*mChestsize];
            int* data2 = new int[27*mChestsize];
            bool* data3 = new bool[27*mChestsize];
            int* data4 = new int[mChestsize];


            gzread(saveFile, data1,sizeof(int)*(mChestsize*27));
            gzread(saveFile, data2,sizeof(int)*(mChestsize*27));
            gzread(saveFile, data3,sizeof(bool)*(mChestsize*27));

            gzread(saveFile, data4,sizeof(int)*(mChestsize));

            for(int k = 0; k < mChestsize; k++)
            {
                Chest* SaveChest = new Chest(-1,-1,-1);

                for(int l = 0; l <= 26; l++)
                {
                    SaveChest->chestSlotId[l] = data1[k * 27 + l];
                    SaveChest->chestSlotAm[l] = data2[k * 27 + l];
                    SaveChest->chestSlotSt[l] = data3[k * 27 + l];
                }
                SaveChest->chestAddress = data4[k];
                mChests.push_back(SaveChest);

                //delete SaveChest;
            }
            delete[] data1;
            delete[] data2;
            delete[] data3;
            delete[] data4;
        }


        gzread(saveFile, &mFurnacesize,sizeof(int));
        mFurnaces.clear();

        if(mFurnacesize != 0)
        {
            int* data1 = new int[3*mFurnacesize];
            int* data2 = new int[3*mFurnacesize];
            bool* data3 = new bool[3*mFurnacesize];

            int* data4 = new int[mFurnacesize];
            int* data5 = new int[mFurnacesize];
            int* data6 = new int[mFurnacesize];

            float* data7 = new float[mFurnacesize];
            float* data8 = new float[mFurnacesize];
            int* data10 = new int[mFurnacesize];

            gzread(saveFile, data1,sizeof(int)*(mFurnacesize*3));
            gzread(saveFile, data2,sizeof(int)*(mFurnacesize*3));
            gzread(saveFile, data3,sizeof(bool)*(mFurnacesize*3));

            gzread(saveFile, data4,sizeof(int)*(mFurnacesize));
            gzread(saveFile, data5,sizeof(int)*(mFurnacesize));
            gzread(saveFile, data6,sizeof(int)*(mFurnacesize));

            gzread(saveFile, data7,sizeof(float)*(mFurnacesize));
            gzread(saveFile, data8,sizeof(float)*(mFurnacesize));
            gzread(saveFile, data10,sizeof(int)*(mFurnacesize));

            for(int k = 0; k < mFurnacesize; k++)
            {
                Furnace* SaveFurnace = new Furnace(-1,-1,-1);

                for(int l = 0; l <= 2; l++)
                {
                    SaveFurnace->furnaceSlotId[l] = data1[k * 3 + l];
                    SaveFurnace->furnaceSlotAm[l] = data2[k * 3 + l];
                    SaveFurnace->furnaceSlotSt[l] = data3[k * 3 + l];
                }
                SaveFurnace->furnaceX = data4[k];
                SaveFurnace->furnaceY = data5[k];
                SaveFurnace->furnaceZ = data6[k];
                SaveFurnace->fuelTime = data7[k];
                SaveFurnace->meltingTime = data8[k];
                SaveFurnace->smeltItemTemp = data10[k];
                mFurnaces.push_back(SaveFurnace);
                //delete SaveChest;
            }
            delete[] data1;
            delete[] data2;
            delete[] data3;
            delete[] data4;
            delete[] data5;
            delete[] data6;
            delete[] data7;
            delete[] data8;
            delete[] data10;
        }

        mZombiesize = 0;
        gzread(saveFile, &mZombiesize,sizeof(int));

        mZombies.clear();

        if(mZombiesize != 0)
        {
            float* data1 = new float[mZombiesize];
            float* data2 = new float[mZombiesize];
            float* data3 = new float[mZombiesize];

            float* data4 = new float[mZombiesize];
            float* data5 = new float[mZombiesize];
            int* data6 = new int[mZombiesize];

            int* data7 = new int[mZombiesize];
            int* data8 = new int[mZombiesize];
            int* data9 = new int[mZombiesize];
            int* data10 = new int[mZombiesize];

            gzread(saveFile, data1,sizeof(float)*(mZombiesize));
            gzread(saveFile, data2,sizeof(float)*(mZombiesize));
            gzread(saveFile, data3,sizeof(float)*(mZombiesize));

            gzread(saveFile, data4,sizeof(float)*(mZombiesize));
            gzread(saveFile, data5,sizeof(float)*(mZombiesize));
            gzread(saveFile, data6,sizeof(int)*(mZombiesize));

            gzread(saveFile, data7,sizeof(int)*(mZombiesize));
            gzread(saveFile, data8,sizeof(int)*(mZombiesize));
            gzread(saveFile, data9,sizeof(int)*(mZombiesize));
            gzread(saveFile, data10,sizeof(int)*(mZombiesize));

            for(int g = 0; g < mZombiesize; g++)
            {
                Zombie* SaveZombie = new Zombie(Vector3(data1[g],data2[g],data3[g]), data6[g]);

                SaveZombie->mainAngle = data4[g];
                SaveZombie->HP = data5[g];
                SaveZombie->helmetId = data7[g];
                SaveZombie->chestplateId = data8[g];
                SaveZombie->leggingsId = data9[g];
                SaveZombie->bootsId = data10[g];

                mZombies.push_back(SaveZombie);
            }
            delete[] data1;
            delete[] data2;
            delete[] data3;
            delete[] data4;
            delete[] data5;
            delete[] data6;
            delete[] data7;
            delete[] data8;
            delete[] data9;
            delete[] data10;
        }

        mCowsize = 0;
        gzread(saveFile, &mCowsize,sizeof(int));

        mCows.clear();

        if(mCowsize != 0)
        {
            float* data1 = new float[mCowsize];
            float* data2 = new float[mCowsize];
            float* data3 = new float[mCowsize];

            float* data4 = new float[mCowsize];
            float* data5 = new float[mCowsize];
            int* data6 = new int[mCowsize];


            gzread(saveFile, data1,sizeof(float)*(mCowsize));
            gzread(saveFile, data2,sizeof(float)*(mCowsize));
            gzread(saveFile, data3,sizeof(float)*(mCowsize));

            gzread(saveFile, data4,sizeof(float)*(mCowsize));
            gzread(saveFile, data5,sizeof(float)*(mCowsize));
            gzread(saveFile, data6,sizeof(int)*(mCowsize));


            for(int g = 0; g < mCowsize; g++)
            {
                Cow* SaveCow = new Cow(Vector3(data1[g],data2[g],data3[g]), data6[g]);

                SaveCow->mainAngle = data4[g];
                SaveCow->HP = data5[g];

                mCows.push_back(SaveCow);
            }
            delete[] data1;
            delete[] data2;
            delete[] data3;
            delete[] data4;
            delete[] data5;
            delete[] data6;
        }

        gzread(saveFile, &zombieNum,sizeof(int));




        /*gzread(saveFile, &mDirectsize,sizeof(int));
        mDirects.clear();

        if(mDirectsize != 0)
        {
        int* data1 = new int[mDirectsize];
        int* data2 = new int[mDirectsize];
        int* data3 = new int[mDirectsize];
        char* data4 = new char[mDirectsize];

        gzread(saveFile, data1,sizeof(int)*(mDirectsize));
        gzread(saveFile, data2,sizeof(int)*(mDirectsize));
        gzread(saveFile, data3,sizeof(int)*(mDirectsize));
        gzread(saveFile, data4,sizeof(char)*(mDirectsize));

        for(int k = 0; k < mDirectsize; k++)
        {
            DirectionBlock* SaveDirectionBlock = new DirectionBlock(-1,-1,-1,-1);

            SaveDirectionBlock->X = data1[k];
            SaveDirectionBlock->Y = data2[k];
            SaveDirectionBlock->Z = data3[k];
            SaveDirectionBlock->direction = data4[k];
            mDirects.push_back(SaveDirectionBlock);

            //delete SaveChest;
        }
        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        }*/


    }
    else
    {
        memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE);
    }

    //close file
    gzclose(saveFile);
    saveFile=0;
}

void CraftWorld::initWorld(int worldSize, int worldHeight, int chunkSize)
{
    //inicjuj mape
    WORLD_SIZE = worldSize;
    CHUNK_SIZE = chunkSize;
    WORLD_HEIGHT = worldHeight;

    m_Blocks = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    memset(m_Blocks, 0, sizeof(block_t) * WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE);

    m_BlockLight = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    memset(m_BlockLight, 255, sizeof(block_t) * WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE);

    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE];
    memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE);
}

void CraftWorld::initWorldBlocksLight() // Тень под блоками
{
    int x, y, z;
    block_t Light;
    block_t RefractionLevel = 0;

    for (z = 0; z < WORLD_SIZE; ++z)
    {
        for (x = 0; x < WORLD_SIZE; ++x)
        {
            Light = 255;
            RefractionLevel = 0;
            for (y = WORLD_HEIGHT - 1; y >= 0; --y)
            {
                if(GetBlock(x,y,z) != 0 && BlockRefraction(x,y,z) != 0 && BlockRefraction(x,y,z) != 2)
                {
                    if (Light > 24)
                    {
                        if(GetBlock(x,y,z) == WaterBlock::getID())
                        {
                            if(Light - 48 < 0)
                            {
                                Light = 24;
                            }
                            else
                            {
                                Light -= 48;
                            }

                            if(Light < 24)
                            {
                                Light = 24;
                            }
                        }
                        else
                        {
                            if(Light - 24 < 0)
                            {
                                Light = 24;
                            }
                            else
                            {
                                Light -= 24;
                            }

                            if(Light < 24)
                            {
                                Light = 24;
                            }
                        }
                    }

                    if(y >= 64)
                    {
                        if(Light < 128)
                        {
                            Light = 128;
                        }
                    }
                }
                GetBlockLight(x, y, z) = Light;
            }
        }
    }
}

void CraftWorld::initPutBlocksLight(const int x, const int z) // Тень под блоками
{
    int y;
    block_t Light;
    block_t RefractionLevel = 0;

    Light = 255;
    for (y = WORLD_HEIGHT - 1; y >= 0; --y)
    {
        if(GetBlock(x,y,z) != 0 && BlockRefraction(x,y,z) != 0 && BlockRefraction(x,y,z) != 2)
        {
            if(GetBlock(x,y,z) == WaterBlock::getID())
            {
                if(Light - 48 < 0)
                {
                    Light = 24;
                }
                else
                {
                    Light -= 48;
                }

                if(Light < 24)
                {
                    Light = 24;
                }
            }
            else
            {
                if(Light - 24 < 0)
                {
                    Light = 24;
                }
                else
                {
                    Light -= 24;
                }

                if(Light < 24)
                {
                    Light = 24;
                }
            }

            if(y >= 64)
            {
                if(Light < 128)
                {
                    Light = 128;
                }
            }
        }
        GetBlockLight(x, y, z) = Light;
    }
}

void CraftWorld::InitLightValues()
{
    lightColor = Vector3(1, 1, 1);
    fogColor = lightColor * 0.8f;

    //light face factors
    //buildcloudsVerts();
}


void CraftWorld::GetTexturesIds()
{
    textureTerrainId = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain1);
    textureItemsId = TextureHelper::Instance()->GetTexture(TextureHelper::Items1);
    textureWaterAnimationId = TextureHelper::Instance()->GetTexture(TextureHelper::WaterAnimation);
    textureLavaAnimationId = TextureHelper::Instance()->GetTexture(TextureHelper::LavaAnimation);
    textureLeatherArmor1Id = TextureHelper::Instance()->GetTexture(TextureHelper::leatherArmor1);
    textureLeatherArmor2Id = TextureHelper::Instance()->GetTexture(TextureHelper::leatherArmor2);
    textureChainArmor1Id = TextureHelper::Instance()->GetTexture(TextureHelper::chainmailArmor1);
    textureChainArmor2Id = TextureHelper::Instance()->GetTexture(TextureHelper::chainmailArmor2);
    textureIronArmor1Id = TextureHelper::Instance()->GetTexture(TextureHelper::ironArmor1);
    textureIronArmor2Id = TextureHelper::Instance()->GetTexture(TextureHelper::ironArmor2);
    textureDiamondArmor1Id = TextureHelper::Instance()->GetTexture(TextureHelper::diamondArmor1);
    textureDiamondArmor2Id = TextureHelper::Instance()->GetTexture(TextureHelper::diamondArmor2);
    textureGoldenArmor1Id = TextureHelper::Instance()->GetTexture(TextureHelper::goldenArmor1);
    textureGoldenArmor2Id = TextureHelper::Instance()->GetTexture(TextureHelper::goldenArmor2);
}

void CraftWorld::SetWolrdTime(float time)
{
    if(time >= 22)
    {
        skyTime = 280+22.5*(time-22);
    }
    if(time < 6)
    {
        skyTime = 325+22.5*time;
    }
    if(time < 22 && time >= 6)
    {
        skyTime = 100+11.25f*(time-6);
    }
    worldDayTime = time;//std::fmod(time, 24);

    lightAngle = worldDayTime / 24.0f * 360.0f - 90.0f;
    if (lightAngle < 0)lightAngle += 360.0f;

    if (worldDayTime <= 4 || worldDayTime >= 22)
    {
        lightColor = Vector3(0.12f, 0.12f, 0.12f);
    }
    else if (worldDayTime == 5)
    {
        lightColor = Vector3(0.12, 0.12, 0.12);
    }
    else if (worldDayTime == 6)
    {
        lightColor = Vector3(0.19, 0.19, 0.19);
    }
    else if (worldDayTime == 7)
    {
        lightColor = Vector3(0.35, 0.35, 0.35);
    }
    else if (worldDayTime == 8)
    {
        lightColor = Vector3(0.5, 0.5, 0.5);
    }
    else if (worldDayTime == 9)
    {
        lightColor = Vector3(0.7, 0.7, 0.7);
    }
    else if (worldDayTime == 10)
    {
        lightColor = Vector3(0.9, 0.9, 0.9);
    }
    else if (worldDayTime >= 11 && worldDayTime <= 18)
    {
        lightColor = Vector3(1.0, 1.0, 1.0);
    }
    else if (worldDayTime == 19)
    {
        lightColor = Vector3(0.7, 0.7, 0.7);
    }
    else if (worldDayTime == 20)
    {
        lightColor = Vector3(0.4, 0.4, 0.4);
    }
    else if (worldDayTime == 21)
    {
        lightColor = Vector3(0.2, 0.2, 0.2);
    }
    else if (worldDayTime == 22)
    {
        lightColor = Vector3(0.15, 0.15, 0.15);
    }
    else if (worldDayTime == 23)
    {
        lightColor = Vector3(0.12, 0.12, 0.12);
    }
    else	//Shouldn't get here
    {
        lightColor = Vector3(1, 1, 1);
    }

    //ambientColor = lightColor / 3.0f;
    ambientColor = Vector3(0,0,0);
    //light face factors
}

void CraftWorld::DropThis(int id, Vector3 position)
{
    if(id != -1)
    {
        dropNum ++;
        Drop *NewDrop = new Drop(this, Vector3((int)position.x+0.5f,(int)position.y+0.51f,(int)position.z+0.5f), id, 1, true);
        mDrops.push_back(NewDrop);
    }
}

void CraftWorld::DropThis(int id, int am, Vector3 position)
{
    if(id != -1)
    {
        dropNum ++;
        Drop *NewDrop = new Drop(this, Vector3((int)position.x+0.5f,(int)position.y+0.51f,(int)position.z+0.5f), id, am, true);
        mDrops.push_back(NewDrop);
    }
}

void CraftWorld::DropThis(int id, int am, bool st, Vector3 position)
{
    if(id != -1)
    {
        dropNum ++;
        Drop *NewDrop = new Drop(this, Vector3((int)position.x+0.5f,(int)position.y+0.51f,(int)position.z+0.5f), id, am, st);
        mDrops.push_back(NewDrop);
    }
}

void CraftWorld::DropThisNoAlign(int id, int am, bool st, Vector3 position, Vector3 velocity)
{
    if(id != -1)
    {
        dropNum ++;
        Drop *NewDrop = new Drop(this, Vector3(position.x,position.y,position.z), id, am, st);
        NewDrop->SetVelociy(velocity);
        mDrops.push_back(NewDrop);
    }
}


void CraftWorld::DestroyDrop(int id)
{
    if(id < mDrops.size())
    {
        delete mDrops[id];
        mDrops.erase(mDrops.begin()+id);
    }
}


void CraftWorld::SpawnZombie(float xx, float yy, float zz)
{
    zombieNum += 1;

    Zombie *NewZombie = new Zombie(Vector3(xx,yy,zz), zombieNum);
   // NewZombie->Update(this,Vector3(0,0,0),0.0f);
    mZombies.push_back(NewZombie);
}

void CraftWorld::DestroyZombie(int id)
{
    if(id < mZombies.size())
    {
        delete mZombies[id];
        mZombies.erase(mZombies.begin()+id);
    }
}

void CraftWorld::SpawnCow(float xx, float yy, float zz)
{
    zombieNum += 1;

    Cow *NewCow = new Cow(Vector3(xx,yy,zz), zombieNum);
   // NewZombie->Update(this,Vector3(0,0,0),0.0f);
    mCows.push_back(NewCow);
}

void CraftWorld::DestroyCow(int id)
{
    if(id < mCows.size())
    {
        delete mCows[id];
        mCows.erase(mCows.begin()+id);
    }
}

void CraftWorld::CollisionWithOtherZombies(Zombie *Zombie1)
{

}

void CraftWorld::buildMap()
{
    createWorldChunkss();
}

void CraftWorld::destroyMap()
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i]->reset();
    }

    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        mTransparentChunks[i]->reset();
    }
}

void CraftWorld::setTextureSize(int texture,int chunk,int animTexture, int animChunk, int itemTexture, int itemChunk)
{
    texutreSize = texture;
    textureChunk = chunk;

    percent = (float)textureChunk / (float)texutreSize;
    percent2 = (float)animChunk / (float)animTexture;
    percent3 = (float)itemChunk / (float)itemTexture;

   // TextureManager::Instance()->setColour(36, 4, 255, 0, 0, 255, textureTerrainId);
}

block_t& CraftWorld::GetBlock (const int x, const int y, const int z) // id блока в данной координате
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT];
    }
    return m_Blocks[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_HEIGHT];
}

block_t& CraftWorld::GetBlockLight (const int x, const int y, const int z) // освещение блока в данной координате
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return m_BlockLight[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT];
    }
    return m_BlockLight[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_HEIGHT];
}

block_t& CraftWorld::GetBlockSettings(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return m_BlockSettings[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT];
    }
    return m_BlockSettings[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_HEIGHT];
}

void CraftWorld::CheckForTorchSupport(const int x, const int y, const int z,int blockID) // проверка : можно ли поставить факел (есть ли соседняя опора для него)
{
    for(int zz = z-1; zz < z+2; zz++)
    {
        for(int xx = x-1; xx < x+2; xx++)
        {
            for(int yy = y-1; yy < y+2; yy++)
            {
                if(GetBlock(xx,yy,zz) == Torch::getID())
                {
                    if(!CanPutBlockHere(xx,yy,zz,Torch::getID()))
                    {
                        GetBlock(xx,yy,zz) = 0;
                        RemoveLigtSourceAtPosition(xx,yy,zz,Torch::getID());
                    }
                }
            }
        }
    }
}

void CraftWorld::CheckForLadderSupport(const int x, const int y, const int z) // проверка : можно ли поставить факел (есть ли соседняя опора для него)
{
    for(int zz = z-1; zz < z+2; zz++)
    {
        for(int xx = x-1; xx < x+2; xx++)
        {
            for(int yy = y-1; yy < y+2; yy++)
            {
                if(GetBlock(xx,yy,zz) == Ladder1::getID() && GetBlock(xx-1,yy,zz) == 0)
                {
                    GetBlock(xx,yy,zz) = 0;
                }
                if(GetBlock(xx,yy,zz) == Ladder2::getID() && GetBlock(xx+1,yy,zz) == 0)
                {
                    GetBlock(xx,yy,zz) = 0;
                }
                if(GetBlock(xx,yy,zz) == Ladder3::getID() && GetBlock(xx,yy,zz-1) == 0)
                {
                    GetBlock(xx,yy,zz) = 0;
                }
                if(GetBlock(xx,yy,zz) == Ladder4::getID() && GetBlock(xx,yy,zz+1) == 0)
                {
                    GetBlock(xx,yy,zz) = 0;
                }
            }
        }
    }
}


void CraftWorld::SetLigtSourcePosition(const int x, const int y, const int z,int blockID) // Установить источник света
{
    LightTravel(x,y,z,10,11);
}

void CraftWorld::RemoveLigtSourceAtPosition(const int x, const int y, const int z,int blockID) // Выпилить источник света
{
    int current = 0;

    for(int zz = z-10; zz < z+10; zz++)
    {
        for(int xx = x-10; xx < x+10; xx++)
        {
            for(int yy = y-10; yy < y+10; yy++)
            {
                if (xx >= 0 || yy >= 0 || zz >= 0  || xx < WORLD_SIZE || yy < WORLD_HEIGHT || zz < WORLD_SIZE)
                {
                    if((GetBlockSettings(xx,yy,zz) & OpLighSource) != 0)
                    {
                        current = GetBlockSettings(xx,yy,zz) & 0xF;
                        GetBlockSettings(xx,yy,zz) ^= current & 0xF;
                        GetBlockSettings(xx,yy,zz) ^= 0 & 0xF;
                        //turn off light here
                        GetBlockSettings(xx,yy,zz) ^= OpLighSource;
                    }
                }
            }
        }
    }
}

void CraftWorld::LightTravel(int x,int y,int z,int steps,int lightLevel) // Алгоритм распространения света
{
    if (x >= 0 && y >= 0 && z >= 0  && x < WORLD_SIZE && y < WORLD_HEIGHT && z < WORLD_SIZE && steps > 0 && lightLevel >= 0)
    {
        bool canGofuther = false;
        //check if it's lightened
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//lightened
        {
            //get current value
            int current = GetBlockSettings(x,y,z) & 0xF;
            //set new only if it's brighter
            if(current < lightLevel)
            {
                //clear this value
                GetBlockSettings(x,y,z) ^= current & 0xF;
                //set new value
                GetBlockSettings(x,y,z) ^= lightLevel & 0xF;

                canGofuther = true;
            }
        }
        else
        {
            int current = GetBlockSettings(x,y,z) & 0xF;
            //clear thisBlockSolid(x,y,z) == 1 value
            GetBlockSettings(x,y,z) ^= current & 0xF;
            //set new value
            GetBlockSettings(x,y,z) ^= lightLevel & 0xF;
            //mark as lightened
            GetBlockSettings(x,y,z) ^= OpLighSource;

            canGofuther = true;
        }


        //go futher
        if(canGofuther == true)
        {
            if(GetBlock(x+1,y,z) == 0 || BlockAllowLight(x+1,y,z) == true)
            {
                LightTravel(x+1,y,z,steps-1,lightLevel-1);
            }
            if(GetBlock(x-1,y,z) == 0 || BlockAllowLight(x-1,y,z) == true)
            {
                LightTravel(x-1,y,z,steps-1,lightLevel-1);
            }
            if(GetBlock(x,y+1,z) == 0 || BlockAllowLight(x,y+1,z) == true)
            {
                LightTravel(x,y+1,z,steps-1,lightLevel-1);
            }
            if(GetBlock(x,y-1,z) == 0 || BlockAllowLight(x,y-1,z) == true)
            {
                LightTravel(x,y-1,z,steps-1,lightLevel-1);
            }
            if(GetBlock(x,y,z+1) == 0 || BlockAllowLight(x,y,z+1) == true)
            {
                LightTravel(x,y,z+1,steps-1,lightLevel-1);
            }
            if(GetBlock(x,y,z-1) == 0 || BlockAllowLight(x,y,z-1) == true)
            {
                LightTravel(x,y,z-1,steps-1,lightLevel-1);
            }
        }
    }
}

bool CraftWorld::CanPutBlockHere(const int x, const int y, const int z,int blockID)
{
    return true;
}

bool CraftWorld::BlockTransparentOrSpecial(const int x, const int y, const int z)
{
    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE || y >= WORLD_HEIGHT || z >= WORLD_SIZE) return true;

    if(blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].transparent || blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].blockModel > 0)
        return true;

    return false;
}

bool CraftWorld::BlockTransparentOrLightSource(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        if(blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].transparent || blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].lightSource || blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].refraction == 2)
            return true;

        return false;
    }
}

bool CraftWorld::BlockTransparent(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].transparent;
    }
}

bool CraftWorld::BlockAnimated(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].animated;
    }
}

char CraftWorld::BlockSpecial(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].blockModel;
    }
}

bool CraftWorld::BlockUpdate2(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].update;
    }
}

bool CraftWorld::BlockSolid(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].solid;
    }
}

short CraftWorld::BlockLoot(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].loot;
    }
}

short CraftWorld::BlockMaterial(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].material;
    }
}

bool CraftWorld::BlockEditable(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].editable;
    }
    return 0;
}


bool CraftWorld::BlockAllowLight(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].allowLight;
    }
    return 0;
}

char CraftWorld::BlockRefraction(const int x, const int y, const int z)
{
    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT]].refraction;
    }
    return 0;
}

float CraftWorld::BlockFinalLight(int x, int y, int z)
{
    float Light = 0.0f;

    if (x >= 0 && x < WORLD_SIZE && z >= 0 && z < WORLD_SIZE && y >= 0 && y < WORLD_HEIGHT)
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            float normal = lightColor.x * (GetBlockLight(x, y, z) / 255.0f);
            float lightened = (GetBlockSettings(x, y, z) & 0xF) / 15.0f;

            if(lightened > normal)
            {
                Light = lightened; // 255.0f;
            }
            else
            {
                Light  = (GetBlockLight(x, y, z) / 255.0f) * lightColor.x;
            }
        }
        else
        {
            Light  = (GetBlockLight(x, y, z) / 255.0f) * lightColor.x;
        }

        return Light;
    }
    return 0.1;
}


bool CraftWorld::LightSourceBlock(int id)
{
    if(id < blockTypes.size())
    {
        return blockTypes[id].lightSource;
    }
    else
    {
        return false;
    }
}


int CraftWorld::LootBlock(int id)
{
    if(id < blockTypes.size())
    {
        return blockTypes[id].loot;
    }
    else
    {
        return false;
    }
}

int CraftWorld::DurabilityPointsItem(int id)
{
    id -= 250; // it is item
    if(id < itemTypes.size())
    {
        return itemTypes[id].durabilityPoints;
    }
}


void CraftWorld::GetSpecialBlockVerts(int i,BaseBlock* blockType) // Строим меш инвентарных блоков, имеющих особую модель
{
    iVertexLeftRight = 0;
    pointsLeftRight = 0;
    iVertexBackFront = 0;
    pointsBackFront = 0;
    iVertexBottomTop = 0;
    pointsBottomTop = 0;

    if(blockType->blockModel == 5) //not common model
    {
        if(i == 6 || i == 134 || i == 135 || i == 136 || (i >= 87 && i <= 90))
        {
            BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));
            BuildGUIBlockPlane(blockType,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
        }

        if(i == Cake::getID())
        {
            BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0));
            BuildGUIBlockPlane(blockType,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
        }

        if(i == Snow2::getID())
        {
            BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,2,16),Vector3(0,2,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,2,0),Vector3(16,2,16),Vector3(16,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,2,16),Vector3(16,2,16),Vector3(16,2,0),Vector3(0,2,0));
            BuildGUIBlockPlane(blockType,5,Vector3(0,2,0),Vector3(16,2,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,2,16),Vector3(0,2,16));
        }

        if(i == Torch::getID())
        {
            BuildGUIBlockPlane(blockType,1,Vector3(7,0,9),Vector3(7,10,9),Vector3(7,10,7),Vector3(7,0,7));
            BuildGUIBlockPlane(blockType,2,Vector3(10,0,7),Vector3(9,10,7),Vector3(9,10,9),Vector3(9,0,9));
            BuildGUIBlockPlane(blockType,3,Vector3(7,0,7),Vector3(9,0,7),Vector3(9,0,9),Vector3(7,0,10));
            BuildGUIBlockPlane(blockType,4,Vector3(7,10,9),Vector3(9,10,9),Vector3(9,10,7),Vector3(7,10,7));
            BuildGUIBlockPlane(blockType,5,Vector3(7,10,7),Vector3(9,10,7),Vector3(9,0,7),Vector3(7,0,7));
            BuildGUIBlockPlane(blockType,6,Vector3(7,0,9),Vector3(9,0,9),Vector3(9,10,9),Vector3(7,10,9));
        }

        if(i == 112 || i == 9 || i == 4 || i == 37 || i == 38)
        {
            BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));
            BuildGUIBlockPlane(blockType,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
        }


        if(i == 125 || i == 60 || i == 67)
        {
            BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,8,8),Vector3(16,8,8),Vector3(16,8,0),Vector3(0,8,0));
            BuildGUIBlockPlane(blockType,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));

            BuildGUIBlockPlane(blockType,1,Vector3(0,8,16),Vector3(0,16,16),Vector3(0,16,8),Vector3(0,8,8));
            BuildGUIBlockPlane(blockType,2,Vector3(16,8,8),Vector3(16,16,8),Vector3(16,16,16),Vector3(16,8,16));
            BuildGUIBlockPlane(blockType,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,8),Vector3(0,16,8));
            BuildGUIBlockPlane(blockType,5,Vector3(0,16,8),Vector3(16,16,8),Vector3(16,8,8),Vector3(0,8,8));
            BuildGUIBlockPlane(blockType,6,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,16,16),Vector3(0,16,16));
        }

        if(i == 25)
        {
            BuildGUIBlockPlane(blockType,1,Vector3(1,0,16),Vector3(1,16,16),Vector3(1,16,0),Vector3(1,0,0));
            BuildGUIBlockPlane(blockType,2,Vector3(15,0,0),Vector3(15,16,0),Vector3(15,16,16),Vector3(15,0,16));
            BuildGUIBlockPlane(blockType,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15));
            BuildGUIBlockPlane(blockType,4,Vector3(0,16,15),Vector3(15,16,15),Vector3(15,16,1),Vector3(1,16,1));
            BuildGUIBlockPlane(blockType,5,Vector3(0,16,1),Vector3(16,16,1),Vector3(16,0,1),Vector3(0,0,1));
            BuildGUIBlockPlane(blockType,6,Vector3(0,0,15),Vector3(16,0,15),Vector3(16,16,15),Vector3(0,16,15));
        }

        if(i == 94)
        {
            BuildGUIBlockPlane(blockType,1,Vector3(1,0,15),Vector3(1,14,15),Vector3(1,14,1),Vector3(1,0,1));
            BuildGUIBlockPlane(blockType,2,Vector3(15,0,1),Vector3(15,14,1),Vector3(15,14,15),Vector3(15,0,15));
            BuildGUIBlockPlane(blockType,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15));
            BuildGUIBlockPlane(blockType,4,Vector3(1,14,15),Vector3(15,14,15),Vector3(15,14,1),Vector3(1,14,1));
            BuildGUIBlockPlane(blockType,5,Vector3(1,14,1),Vector3(15,14,1),Vector3(15,0,1),Vector3(1,0,1));
            BuildGUIBlockPlane(blockType,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,14,15),Vector3(1,14,15));

            blockType = &blockTypes[98];

            BuildGUIBlockPlane(blockType,1,Vector3(0,7,9),Vector3(0,11,9),Vector3(0,11,7),Vector3(0,7,7));
            BuildGUIBlockPlane(blockType,3,Vector3(0,7,7),Vector3(1,7,7),Vector3(1,7,9),Vector3(0,7,9));
            BuildGUIBlockPlane(blockType,4,Vector3(0,11,9),Vector3(1,11,9),Vector3(1,11,7),Vector3(0,11,7));
            BuildGUIBlockPlane(blockType,5,Vector3(0,11,7),Vector3(1,11,7),Vector3(1,7,7),Vector3(0,7,7));
            BuildGUIBlockPlane(blockType,6,Vector3(0,7,9),Vector3(1,7,9),Vector3(1,11,9),Vector3(0,11,9));
        }
    }

    if(blockType->blockModel == 2)
    {
        BuildGUIBlockPlane(blockType,1,Vector3(6,0,10),Vector3(6,16,10),Vector3(6,16,6),Vector3(6,0,6));
        BuildGUIBlockPlane(blockType,2,Vector3(10,0,6),Vector3(10,16,6),Vector3(10,16,10),Vector3(10,0,10));
        BuildGUIBlockPlane(blockType,3,Vector3(6,0,6),Vector3(10,0,6),Vector3(10,0,10),Vector3(6,0,10));
        BuildGUIBlockPlane(blockType,4,Vector3(6,16,10),Vector3(10,16,10),Vector3(10,16,6),Vector3(6,16,6));
        BuildGUIBlockPlane(blockType,5,Vector3(6,16,6),Vector3(10,16,6),Vector3(10,0,6),Vector3(6,0,6));
        BuildGUIBlockPlane(blockType,6,Vector3(6,0,10),Vector3(10,0,10),Vector3(10,16,10),Vector3(6,16,10));
    }

    if(blockType->blockModel == 1)
    {
        BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
        BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
        BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
        BuildGUIBlockPlane(blockType,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0));
        BuildGUIBlockPlane(blockType,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
        BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
    }

    blockTypes[i].verticesLeftRight = (TexturesPSPVertex*)memalign(16,( mTriangleLeftRight.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsLeftRight = pointsLeftRight;
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangleLeftRight.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->x]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->x]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->x]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->x]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->x]->z;
        vert++;

        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->y]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->y]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->y]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->y]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->y]->z;
        vert++;

        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->z]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->z]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->z]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->z]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesLeftRight,(mTriangleLeftRight.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionLeftRight.size(); aa++)
    {
        delete mPositionLeftRight[aa];
        delete mtexturesLeftRight[aa];
    }
    mPositionLeftRight.clear();
    mtexturesLeftRight.clear();

    for(unsigned int aa = 0; aa < mTriangleLeftRight.size(); aa++)
    {
        delete mTriangleLeftRight[aa];
    }
    mTriangleLeftRight.clear();



    blockTypes[i].verticesBackFront = (TexturesPSPVertex*)memalign(16,(mTriangleBackFront.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsBackFront = pointsBackFront;
    //build verts
    //vertices
    vert = 0;
    size =  mTriangleBackFront.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->x]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->x]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->x]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->x]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->x]->z;
        vert++;

        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->y]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->y]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->y]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->y]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->y]->z;
        vert++;

        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->z]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->z]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->z]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->z]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesBackFront,(mTriangleBackFront.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionBackFront.size(); aa++)
    {
        delete mPositionBackFront[aa];
        delete mtexturesBackFront[aa];
    }
    mPositionBackFront.clear();
    mtexturesBackFront.clear();

    for(unsigned int aa = 0; aa < mTriangleBackFront.size(); aa++)
    {
        delete mTriangleBackFront[aa];
    }
    mTriangleBackFront.clear();



    blockTypes[i].verticesBottomTop = (TexturesPSPVertex*)memalign(16,(mTriangleBottomTop.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsBottomTop = pointsBottomTop;
    //build verts
    //vertices
    vert = 0;
    size =  mTriangleBottomTop.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->x]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->x]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->x]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->x]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->x]->z;
        vert++;

        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->y]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->y]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->y]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->y]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->y]->z;
        vert++;

        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->z]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->z]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->z]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->z]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesBottomTop,(mTriangleBottomTop.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionBottomTop.size(); aa++)
    {
        delete mPositionBottomTop[aa];
        delete mtexturesBottomTop[aa];
    }
    mPositionBottomTop.clear();
    mtexturesBottomTop.clear();

    for(unsigned int aa = 0; aa < mTriangleBottomTop.size(); aa++)
    {
        delete mTriangleBottomTop[aa];
    }
    mTriangleBottomTop.clear();
}

void CraftWorld::GetCloudsVerts(BaseBlock *blockType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;
    int points = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;

    iVertex = 0;
    points = 0;

    for(float l = 1; l <= 10; l += 1)
    {
        for(float j = 1; j <= 10; j += 1)//0-|-
        {
            mPosition.push_back(new Vector3(x+((l-1)*48),   y, z+((j-1)*48)));
            mtextures.push_back(new Vector2(0+(l-1)/16, 0+(j-1)/16));
            mPosition.push_back(new Vector3(x+(l*48), y, z+((j-1)*48)));
            mtextures.push_back(new Vector2(l/16, 0+(j-1)/16));
            mPosition.push_back(new Vector3(x+(l*48), y, z+(j*48)));
            mtextures.push_back(new Vector2(l/16, j/16));
            mPosition.push_back(new Vector3(x+((l-1)*48),   y, z+(j*48)));
            mtextures.push_back(new Vector2(0+(l-1)/16, j/16));

            mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
            mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

            iVertex += 4;
            points += 6;
        }
    }

    blockTypes[141].verticesBottomTop = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[141].pointsBottomTop = points;
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[141].verticesBottomTop[vert].u = mtextures[mTriangle[j]->x]->x;
        blockTypes[141].verticesBottomTop[vert].v = mtextures[mTriangle[j]->x]->y;
        blockTypes[141].verticesBottomTop[vert].x = mPosition[mTriangle[j]->x]->x;
        blockTypes[141].verticesBottomTop[vert].y = mPosition[mTriangle[j]->x]->y;
        blockTypes[141].verticesBottomTop[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        blockTypes[141].verticesBottomTop[vert].u = mtextures[mTriangle[j]->y]->x;
        blockTypes[141].verticesBottomTop[vert].v = mtextures[mTriangle[j]->y]->y;
        blockTypes[141].verticesBottomTop[vert].x = mPosition[mTriangle[j]->y]->x;
        blockTypes[141].verticesBottomTop[vert].y = mPosition[mTriangle[j]->y]->y;
        blockTypes[141].verticesBottomTop[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        blockTypes[141].verticesBottomTop[vert].u = mtextures[mTriangle[j]->z]->x;
        blockTypes[141].verticesBottomTop[vert].v = mtextures[mTriangle[j]->z]->y;
        blockTypes[141].verticesBottomTop[vert].x = mPosition[mTriangle[j]->z]->x;
        blockTypes[141].verticesBottomTop[vert].y = mPosition[mTriangle[j]->z]->y;
        blockTypes[141].verticesBottomTop[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[141].verticesBottomTop,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
        mPosition.clear();
        mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();
}


void CraftWorld::GetNormalBlockVerts(int i,BaseBlock *blockType)
{
    iVertexLeftRight = 0;
    pointsLeftRight = 0;
    iVertexBackFront = 0;
    pointsBackFront = 0;
    iVertexBottomTop = 0;
    pointsBottomTop = 0;

    BuildGUIBlockPlane(blockType,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
    BuildGUIBlockPlane(blockType,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));
    BuildGUIBlockPlane(blockType,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
    BuildGUIBlockPlane(blockType,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));
    BuildGUIBlockPlane(blockType,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
    BuildGUIBlockPlane(blockType,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));

    blockTypes[i].verticesLeftRight = (TexturesPSPVertex*)memalign(16,( mTriangleLeftRight.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsLeftRight = pointsLeftRight;
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangleLeftRight.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->x]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->x]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->x]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->x]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->x]->z;
        vert++;

        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->y]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->y]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->y]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->y]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->y]->z;
        vert++;

        blockTypes[i].verticesLeftRight[vert].u = mtexturesLeftRight[mTriangleLeftRight[j]->z]->x;
        blockTypes[i].verticesLeftRight[vert].v = mtexturesLeftRight[mTriangleLeftRight[j]->z]->y;
        blockTypes[i].verticesLeftRight[vert].x = mPositionLeftRight[mTriangleLeftRight[j]->z]->x;
        blockTypes[i].verticesLeftRight[vert].y = mPositionLeftRight[mTriangleLeftRight[j]->z]->y;
        blockTypes[i].verticesLeftRight[vert].z = mPositionLeftRight[mTriangleLeftRight[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesLeftRight,(mTriangleLeftRight.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionLeftRight.size(); aa++)
    {
        delete mPositionLeftRight[aa];
        delete mtexturesLeftRight[aa];
    }
    mPositionLeftRight.clear();
    mtexturesLeftRight.clear();

    for(unsigned int aa = 0; aa < mTriangleLeftRight.size(); aa++)
    {
        delete mTriangleLeftRight[aa];
    }
    mTriangleLeftRight.clear();



    blockTypes[i].verticesBackFront = (TexturesPSPVertex*)memalign(16,(mTriangleBackFront.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsBackFront = pointsBackFront;
    //build verts
    //vertices
    vert = 0;
    size =  mTriangleBackFront.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->x]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->x]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->x]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->x]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->x]->z;
        vert++;

        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->y]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->y]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->y]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->y]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->y]->z;
        vert++;

        blockTypes[i].verticesBackFront[vert].u = mtexturesBackFront[mTriangleBackFront[j]->z]->x;
        blockTypes[i].verticesBackFront[vert].v = mtexturesBackFront[mTriangleBackFront[j]->z]->y;
        blockTypes[i].verticesBackFront[vert].x = mPositionBackFront[mTriangleBackFront[j]->z]->x;
        blockTypes[i].verticesBackFront[vert].y = mPositionBackFront[mTriangleBackFront[j]->z]->y;
        blockTypes[i].verticesBackFront[vert].z = mPositionBackFront[mTriangleBackFront[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesBackFront,(mTriangleBackFront.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionBackFront.size(); aa++)
    {
        delete mPositionBackFront[aa];
        delete mtexturesBackFront[aa];
    }
    mPositionBackFront.clear();
    mtexturesBackFront.clear();

    for(unsigned int aa = 0; aa < mTriangleBackFront.size(); aa++)
    {
        delete mTriangleBackFront[aa];
    }
    mTriangleBackFront.clear();



    blockTypes[i].verticesBottomTop = (TexturesPSPVertex*)memalign(16,(mTriangleBottomTop.size() * 3) * sizeof(TexturesPSPVertex));
    blockTypes[i].pointsBottomTop = pointsBottomTop;
    //build verts
    //vertices
    vert = 0;
    size =  mTriangleBottomTop.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->x]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->x]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->x]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->x]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->x]->z;
        vert++;

        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->y]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->y]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->y]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->y]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->y]->z;
        vert++;

        blockTypes[i].verticesBottomTop[vert].u = mtexturesBottomTop[mTriangleBottomTop[j]->z]->x;
        blockTypes[i].verticesBottomTop[vert].v = mtexturesBottomTop[mTriangleBottomTop[j]->z]->y;
        blockTypes[i].verticesBottomTop[vert].x = mPositionBottomTop[mTriangleBottomTop[j]->z]->x;
        blockTypes[i].verticesBottomTop[vert].y = mPositionBottomTop[mTriangleBottomTop[j]->z]->y;
        blockTypes[i].verticesBottomTop[vert].z = mPositionBottomTop[mTriangleBottomTop[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].verticesBottomTop,(mTriangleBottomTop.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPositionBottomTop.size(); aa++)
    {
        delete mPositionBottomTop[aa];
        delete mtexturesBottomTop[aa];
    }
    mPositionBottomTop.clear();
    mtexturesBottomTop.clear();

    for(unsigned int aa = 0; aa < mTriangleBottomTop.size(); aa++)
    {
        delete mTriangleBottomTop[aa];
    }
    mTriangleBottomTop.clear();
}

void CraftWorld::GetItemVerts(int i,BaseItem *itemType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;
    int points = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;

    float pixel = 1 / 16.0f;
    float texturepixel = percent3 / 16.0f;

    float down = 1.0f - percent3 * (itemType->textureRow + 1);
    float up = down + percent3;

    float left = percent3 * itemType->plane;
    float right = left + percent3;

    int startPixelsX = itemType->plane*16;
    int startPixelsY = 256 - ((itemType->textureRow + 1)*16);

    iVertex = 0;
    //light
    float BlockLight  = 1.0f;  //For the two x faces

    mPosition.push_back(new Vector3(x,   y,   z+1));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+1, y,   z+1));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+1, y+1, z+1));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+1, z+1));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    itemTypes[i].vertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    itemTypes[i].points = points;
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(itemTypes[i].vertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete mTriangle[aa];
    }
    mTriangle.clear();

    // drop vertices
    float size2 = 0.25f;
    iVertex = 0;

    mPosition.push_back(new Vector3(0,   -size2,   size2));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(0, size2,   size2));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(0, size2, -size2));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(0,   -size2, -size2));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    itemTypes[i].dropVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    vert = 0;
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        itemTypes[i].dropVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        itemTypes[i].dropVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        itemTypes[i].dropVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        itemTypes[i].dropVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        itemTypes[i].dropVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        itemTypes[i].dropVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        itemTypes[i].dropVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        itemTypes[i].dropVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        itemTypes[i].dropVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        itemTypes[i].dropVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        itemTypes[i].dropVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        itemTypes[i].dropVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        itemTypes[i].dropVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        itemTypes[i].dropVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        itemTypes[i].dropVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(itemTypes[i].dropVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete mTriangle[aa];
    }
    mTriangle.clear();

    // add vertices
    points = 0;
    iVertex = 0;

    if(TextureManager::Instance()->Images[textureItemsId]->Width == 256)
    {
        for(int i = 15; i >= 0; i--)
        {
            for(int j = 15; j >= 0; j--)
            {
                int xx = startPixelsX+i;
                int yy = startPixelsY+j;
                if(TextureManager::Instance()->getAlpha(xx,yy,textureItemsId) == 255)
                {
                    if( (i == 0) || (i != 0 && TextureManager::Instance()->getAlpha(xx-1,yy,textureItemsId) == 0))
                    {
                        mPosition.push_back(new Vector3(x+i*pixel,y+j*pixel,   z+pixel*16));
                        mtextures.push_back(new Vector2(left+texturepixel*(i+1), down+texturepixel*(j+1)));

                        mPosition.push_back(new Vector3(x+i*pixel, y+(j+1)*pixel,   z+pixel*16));
                        mtextures.push_back(new Vector2(left+texturepixel*(i+1), down+texturepixel*j));

                        mPosition.push_back(new Vector3(x+i*pixel, y+(j+1)*pixel, z+pixel*15));
                        mtextures.push_back(new Vector2(left+texturepixel*i, down+texturepixel*j));

                        mPosition.push_back(new Vector3(x+i*pixel, y+j*pixel, z+pixel*15));
                        mtextures.push_back(new Vector2(left+texturepixel*i, down+texturepixel*(j+1)));

                        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
                        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

                        iVertex += 4;
                        points += 6;

                    }

                    if( (j == 0) || (j != 0 && TextureManager::Instance()->getAlpha(xx,yy+1,textureItemsId) == 0) )
                    {
                        mPosition.push_back(new Vector3(x+i*pixel,y+(j+1)*pixel,   z+pixel*16));
                        mtextures.push_back(new Vector2(left+texturepixel*i, down+texturepixel*j));

                        mPosition.push_back(new Vector3(x+(i+1)*pixel, y+(j+1)*pixel,   z+pixel*16));
                        mtextures.push_back(new Vector2(left+texturepixel*(i+1), down+texturepixel*j));

                        mPosition.push_back(new Vector3(x+(i+1)*pixel, y+(j+1)*pixel, z+pixel*15));
                        mtextures.push_back(new Vector2(left+texturepixel*(i+1), down+texturepixel*(j+1)));

                        mPosition.push_back(new Vector3(x+i*pixel, y+(j+1)*pixel, z+pixel*15));
                        mtextures.push_back(new Vector2(left+texturepixel*i, down+texturepixel*(j+1)));

                        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
                        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

                        iVertex += 4;
                        points += 6;
                    }
                }
            }
        }
    }

    itemTypes[i].addVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    itemTypes[i].addPoints = points;
    //build verts
    //vertices
    vert = 0;
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        itemTypes[i].addVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        itemTypes[i].addVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        itemTypes[i].addVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        itemTypes[i].addVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        itemTypes[i].addVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        itemTypes[i].addVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        itemTypes[i].addVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        itemTypes[i].addVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        itemTypes[i].addVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        itemTypes[i].addVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        itemTypes[i].addVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        itemTypes[i].addVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        itemTypes[i].addVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        itemTypes[i].addVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        itemTypes[i].addVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(itemTypes[i].addVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete mTriangle[aa];
    }
    mTriangle.clear();
}

void CraftWorld::buildblocksVerts()
{
    for(unsigned int i = 0; i < itemTypes.size(); i++)
    {
        BaseItem *itemType = &itemTypes[i];
        GetItemVerts(i,itemType);
    }
    //create vertices for each block type
    for(unsigned int i = 1; i < blockTypes.size(); i++)
    {
        BaseBlock *blockType = &blockTypes[i];
        if(blockType->blockModel > 0)
            GetSpecialBlockVerts(i,blockType);
        else
            GetNormalBlockVerts(i,blockType);
    }

}

void CraftWorld::buildcloudsVerts()
{
    BaseBlock *blockType = &blockTypes[141];
    GetCloudsVerts(blockType);
}

void CraftWorld::buildmobVerts()
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;
    int points = 0;
    unsigned int size = 0;

    float pixel = 1 / 16.0f;

    float x = pixel * -2;
    float y = pixel * -6;
    float z = pixel * -4;

    float down = 0.0f;
    float up = 0.0f;

    float left = 0.0f;
    float right = 0.0f;

    int vert = 0;

    /// * --- BODY --- *

    left = 0.5f;
    right = left + 0.125f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.3125f;
    right = left + 0.125f;

    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.4375f;
    right = left + 0.125f;

    down = 0.5f;
    up = down + 0.125f;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y, z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.3125f;
    right = left + 0.125f;

    down = 0.5f;
    up = down + 0.125f;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.25f;
    right = left + 0.0625f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.4375f;
    right = left + 0.0625f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    bodyVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices

    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        bodyVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        bodyVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        bodyVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        bodyVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        bodyVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        bodyVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        bodyVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        bodyVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        bodyVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        bodyVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        bodyVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        bodyVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        bodyVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        bodyVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        bodyVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(bodyVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();

    /// * --- HEAD --- *

    x = pixel * -4;
    y = pixel * -4;
    z = pixel * -4;

    vert = 0;
    iVertex = 0;
    points = 0;
    size = 0;

    left = 0.375f;
    right = left + 0.125f;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*8, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.125f;
    right = left + 0.125f;

    mPosition.push_back(new Vector3(x+pixel*8, y,   z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*8, y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.25f;
    right = left + 0.125f;

    down = 0;
    up = down + 0.25f;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*8, y, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*8, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y, z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.125f;
    right = left + 0.125f;

    down = 0;
    up = down + 0.25f;

    mPosition.push_back(new Vector3(x,   y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*8, z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.125;
    right = 0;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x,   y+pixel*8, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*8, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.375;
    right = 0.25;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*8, y,   z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*8, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    headVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        headVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        headVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        headVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        headVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        headVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        headVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        headVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        headVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        headVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        headVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        headVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        headVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        headVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        headVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        headVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(headVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();



    /// * --- HAND --- *

    x = pixel * -2;
    y = pixel * -2;
    z = pixel * -2;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y, z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    handVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        handVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        handVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        handVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        handVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        handVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        handVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        handVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        handVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        handVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        handVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        handVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        handVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        handVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        handVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        handVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(handVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();




    /// * --- LEG --- *

    x = pixel * -2;
    y = pixel * -2;
    z = pixel * -2;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875 - 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f - 0.625;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y, z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.625f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    legVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        legVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        legVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        legVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        legVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        legVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        legVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        legVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        legVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        legVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        legVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        legVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        legVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        legVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        legVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        legVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(legVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();



    /// * --- cowBodyVertices --- *

    x = pixel * -9;
    y = pixel * -5;
    z = pixel * -6;

    vert = 0;
    iVertex = 0;
    points = 0;
    size = 0;

    left = 40.0f/64.0f;
    right = left + 12.0f/64.0f;

    down = 4.0f/32.0f;
    up = down + 10.0f/32.0f;

    mPosition.push_back(new Vector3(x, y, z+pixel*12));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*10, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    //face
    left = 28.0f/64.0f;
    right = left + 12.0f/64.0f;

    down = 4.0f/32.0f;
    up = down + 10.0f/32.0f;

    mPosition.push_back(new Vector3(x+pixel*18, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*18, y,   z+pixel*12));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    // bottom
    left = 28.0f/64.0f;
    right = left + 12.0f/64.0f;

    down = 14.0f/32.0f;
    up = down + 18.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*18, y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*18, y, z+pixel*12));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y, z+pixel*12));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    // top
    left = 50.0f/64.0f;
    right = left + 12.0f/64.0f;

    down = 14.0f/32.0f;
    up = down + 18.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y+pixel*10, z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    // left
    left = 18.0f/64.0f;
    right = left + 10.0f/64.0f;

    down = 14.0f/32.0f;
    up = down + 18.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y+pixel*10, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*18, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    // right
    left = 40.0f/64.0f;
    right = left + 10.0f/64.0f;

    down = 14.0f/32.0f;
    up = down + 18.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*12));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*18, y,   z+pixel*12));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*18, y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*10, z+pixel*12));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    cowBodyVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices

    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        cowBodyVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        cowBodyVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        cowBodyVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        cowBodyVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        cowBodyVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        cowBodyVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        cowBodyVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        cowBodyVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        cowBodyVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        cowBodyVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        cowBodyVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        cowBodyVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        cowBodyVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        cowBodyVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        cowBodyVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(cowBodyVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();



    /// * --- cowHeadVertices --- *

    x = pixel * -3;
    y = pixel * -4;
    z = pixel * -4;

    vert = 0;
    iVertex = 0;
    points = 0;
    size = 0;

    left = 20.0f/64.0f;
    right = left + 8.0f/64.0f;

    down = 6.0f/32.0f;
    up = down + 8.0f/32.0f;

    mPosition.push_back(new Vector3(x, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*8, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    //face
    left = 6.0f/64.0f;
    right = left + 8.0f/64.0f;

    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 14.0f/64.0f;
    right = left + 8.0f/64.0f;

    down = 0;
    up = down + 6.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y, z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y, z+pixel*8));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 6.0f/64.0f;
    right = left + 8.0f/64.0f;

    down = 0;
    up = down + 6.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*8, z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    left = 6.0f/64.0f;
    right = 0;

    down = 6.0f/32.0f;
    up = down + 8.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y+pixel*8, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    left = 14.0f/64.0f;
    right = 20.0f/64.0f;

    down = 6.0f/32.0f;
    up = down + 8.0f/32.0f;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*8));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*8));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*8, z+pixel*8));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    cowHeadVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        cowHeadVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        cowHeadVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        cowHeadVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        cowHeadVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        cowHeadVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        cowHeadVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        cowHeadVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        cowHeadVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        cowHeadVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        cowHeadVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        cowHeadVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        cowHeadVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        cowHeadVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        cowHeadVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        cowHeadVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(cowHeadVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();



    /// * --- cowLegVertices --- *


    x = pixel * -2;
    y = pixel * -2;
    z = pixel * -2;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875 - 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f - 0.625;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y, z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y, z+pixel*4));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.625f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*12, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*4));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*4, y,   z+pixel*4));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*4, y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*12, z+pixel*4));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    cowLegVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        cowLegVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        cowLegVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        cowLegVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        cowLegVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        cowLegVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        cowLegVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        cowLegVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        cowLegVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        cowLegVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        cowLegVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        cowLegVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        cowLegVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        cowLegVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        cowLegVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        cowLegVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(cowLegVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();



    /// * --- helmetVertices --- *

    x = pixel * -5;
    y = pixel * -5;
    z = pixel * -5;

    vert = 0;
    iVertex = 0;
    points = 0;
    size = 0;

    left = 0.375f;
    right = left + 0.125f;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x, y, z+pixel*10));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*10, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.125f;
    right = left + 0.125f;

    mPosition.push_back(new Vector3(x+pixel*10, y,   z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*10));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.125f;
    right = left + 0.125f;

    down = 0;
    up = down + 0.25f;

    mPosition.push_back(new Vector3(x,   y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*10, z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.125;
    right = 0;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x,   y+pixel*10, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*10, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.375;
    right = 0.25;

    down = 0.25;
    up = down + 0.25;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*10));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*10));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*10, y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*10, z+pixel*10));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    helmetVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        helmetVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        helmetVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        helmetVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        helmetVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        helmetVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        helmetVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        helmetVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        helmetVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        helmetVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        helmetVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        helmetVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        helmetVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        helmetVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        helmetVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        helmetVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(helmetVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();





    /// * --- shoulderVertices --- *

    x = pixel * -3;
    y = pixel * -3;
    z = pixel * -3;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*6));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875f;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y, z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y, z+pixel*6));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    left = 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*14, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*6));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    shoulderVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        shoulderVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        shoulderVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        shoulderVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        shoulderVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        shoulderVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        shoulderVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        shoulderVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        shoulderVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        shoulderVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        shoulderVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        shoulderVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        shoulderVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        shoulderVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        shoulderVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        shoulderVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(shoulderVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();






    /// * --- chestplateVertices --- *

    x = pixel * -3;
    y = pixel * -7;
    z = pixel * -5;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.5f;
    right = left + 0.125f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x, y, z+pixel*10));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*14, z+pixel*10));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.3125f;
    right = left + 0.125f;

    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*10));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*10));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    left = 0.25f;
    right = left + 0.0625f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x,   y+pixel*14, z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.4375f;
    right = left + 0.0625f;

    down = 0.625f;
    up = down + 0.375f;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*10));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*10));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*10));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y+pixel*14, z+pixel*10));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    chestplateVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices

    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        chestplateVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        chestplateVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        chestplateVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        chestplateVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        chestplateVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        chestplateVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        chestplateVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        chestplateVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        chestplateVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        chestplateVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        chestplateVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        chestplateVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        chestplateVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        chestplateVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        chestplateVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(chestplateVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();






    /// * --- leggingVertices --- *

    x = pixel * -2.5f;
    y = pixel * -2.5f;
    z = pixel * -2.5f;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*5));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*13, z+pixel*5));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*13, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.6875 - 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*5, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*5, y+pixel*13, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*5, y+pixel*13, z+pixel*5));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*5, y,   z+pixel*5));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    left = 0.625f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*13, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*5, y+pixel*13, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*5, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*5));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*5, y,   z+pixel*5));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*5, y+pixel*13, z+pixel*5));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*13, z+pixel*5));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    leggingVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        leggingVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        leggingVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        leggingVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        leggingVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        leggingVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        leggingVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        leggingVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        leggingVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        leggingVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        leggingVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        leggingVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        leggingVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        leggingVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        leggingVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        leggingVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(leggingVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();




    /// * --- bootVertices --- *

    x = pixel * -3;
    y = pixel * -3;
    z = pixel * -3;

    iVertex = 0;
    points = 0;
    vert = 0;
    size = 0;

    left = 0.8125f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x, y, z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.6875 - 0.625f;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*6));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.6875f - 0.625;
    right = left + 0.0625f;

    down = 0.5;
    up = down + 0.125;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y, z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x,   y, z+pixel*6));
    mtextures.push_back(new Vector2(left, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;



    left = 0.625f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y+pixel*14, z));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z));
    mtextures.push_back(new Vector2(left, up));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;

    left = 0.75f - 0.625;
    right = left + 0.0625f;

    down = 0.625;
    up = down + 0.375;

    mPosition.push_back(new Vector3(x,   y,   z+pixel*6));
    mtextures.push_back(new Vector2(left, down));
    mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*6));
    mtextures.push_back(new Vector2(right, down));
    mPosition.push_back(new Vector3(x+pixel*6, y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(right, up));
    mPosition.push_back(new Vector3(x,   y+pixel*14, z+pixel*6));
    mtextures.push_back(new Vector2(left, up));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;
    points += 6;


    bootVertices = (TexturesPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //build verts
    //vertices
    size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        bootVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        bootVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        bootVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        bootVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        bootVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        bootVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        bootVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        bootVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        bootVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        bootVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        bootVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        bootVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        bootVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        bootVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        bootVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(bootVertices,( mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
    {
        delete 	mTriangle[aa];
    }
    mTriangle.clear();
}

void CraftWorld::createChunks(const int StartX, const int StartY, const int StartZ)
{
    SimpleMeshChunk* MeshChunk = new SimpleMeshChunk();

    int iVertex = 0;
    block_t Block;

    /* Only create visible faces of each chunk */
    MeshChunk->chunkStartZ = StartZ;
    MeshChunk->chunkStartY = StartY;
    MeshChunk->chunkStartX = StartX;

    MeshChunk->bBox = BoundingBox(Vector3(StartX,StartY,StartZ),Vector3(StartX + CHUNK_SIZE,StartY + CHUNK_SIZE,StartZ + CHUNK_SIZE));

    //if we are in player zone on the start then build map
    if(playerZoneBB.intersect(MeshChunk->bBox))
    {
        createdChunksCount++;
        //light
        for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
        {
            for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
            {
                for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
                {
                    Block = GetBlock(x,y,z);
                    if(BlockTransparent(x,y,z) == true)continue;//if block is transparent don't continue

                    if(BlockSpecial(x,y,z) == 0)
                        GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,false);
                    else
                        GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }
            }
        }

        MeshChunk->end();
    }
    else
    {
        MeshChunk->end();
        MeshChunk->created = false;
    }

    MeshChunk->id = mChunks.size();
    mChunks.push_back(MeshChunk);
}


void CraftWorld::createTransparentChunks(const int StartX, const int StartY, const int StartZ)
{
    SimpleMeshChunk* MeshChunk = new SimpleMeshChunk();

    int iVertex = 0;
    block_t Block;

    MeshChunk->chunkStartZ = StartZ;
    MeshChunk->chunkStartY = StartY;
    MeshChunk->chunkStartX = StartX;

    MeshChunk->bBox = BoundingBox(Vector3(StartX,StartY,StartZ),Vector3(StartX + CHUNK_SIZE,StartY + CHUNK_SIZE,StartZ + CHUNK_SIZE));

    //if we are in player zone on the start then build map
    if(playerZoneBB.intersect(MeshChunk->bBox))
    {
        for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
        {
            for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
            {
                for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
                {
                    Block = GetBlock(x,y,z);
                    if (BlockTransparent(x,y,z) == false || Block == 0) continue;

                    if(BlockSpecial(x,y,z) == 0)
                        GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,true);
                    else
                        GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,true);
                }
            }
        }
        MeshChunk->end();
    }
    else
    {
        MeshChunk->end();
        MeshChunk->created = false;
    }

    //MeshChunk->end();
    MeshChunk->id = mChunks.size();
    mTransparentChunks.push_back(MeshChunk);
}

void CraftWorld::rebuildChunk(int id)
{
    SimpleMeshChunk* MeshChunk = mChunks[id];

    int iVertex = 0;
    block_t Block;

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    MeshChunk->reset();

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                Block = GetBlock(x,y,z);
                if(MeshChunk->periodicallyUpadted == false)
                {
                    if((Block >= MelonPlant1::getID() && Block <= MelonPlant4::getID()) || (Block >= WheatBlock1::getID() && Block <= WheatBlock4::getID()) || (Block >= OakSapling::getID() && Block <= BirchSapling::getID()))
                    {
                        updatingChunks.push_back(id);
                        MeshChunk->periodicallyUpadted = true;
                    }
                }

                if(BlockTransparent(x,y,z) == true)continue;//if block is transparent don't continue

                if(BlockSpecial(x,y,z) == 0)
                {
                    GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }
                else
                {
                    GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }

            }
        }
    }

    MeshChunk->end();
}

void CraftWorld::rebuildTransparentChunk(int id)
{
    SimpleMeshChunk* MeshChunk = mTransparentChunks[id];

    int iVertex = 0;
    block_t Block;

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    MeshChunk->reset();

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                Block = GetBlock(x,y,z);
                if (BlockTransparent(x,y,z) == false || Block == 0) continue;

                if(BlockSpecial(x,y,z) == 0)
                    GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,true);
                else
                    GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,true);
            }
        }
    }

    MeshChunk->end();
}

void CraftWorld::GetSpecialBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent)
{
    BaseBlock *blockType = &blockTypes[Block];
    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    bool canCreate = false;
    bool DefaultBlock = false;
    bool transparentBlock = false;

    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;

    char Block1;

    Vector3 light1, light2, light3, light4;
    Vector3 BlockColorx1, BlockColorx2, BlockColory1, BlockColory2, BlockColorz1, BlockColorz2;

    ///left     right
    // x y z    x y z
    // 0 0 1    1 0 0
    // 0 1 1    1 1 0
    // 0 1 0    1 1 1
    // 0 0 0    1 0 1

    ///down     top
    // x y z    x y z
    // 0 0 0    0 1 1
    // 1 0 0    1 1 1
    // 1 0 1    1 1 0
    // 0 0 1    0 1 0

    ///back     forward
    // x y z    x y z
    // 0 1 0    0 0 1
    // 1 1 0    1 0 1
    // 1 0 0    1 1 1
    // 0 0 0    0 1 1

    if(blockTypes[Block].blockModel == 5)
    {
        if(Block == Cake::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,15),Vector3(1,8,15),Vector3(1,8,1),Vector3(1,0,1));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,1),Vector3(15,8,1),Vector3(15,8,15),Vector3(15,0,15));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,8,15),Vector3(15,8,15),Vector3(15,8,1),Vector3(1,8,1));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(1,8,1),Vector3(15,8,1),Vector3(15,0,1),Vector3(1,0,1));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,8,15),Vector3(1,8,15));
        }


        if(Block == Ladder1::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(1,0,0),Vector3(1,16,0),Vector3(1,16,16),Vector3(1,0,16),1,1);
        }

        if(Block == Ladder2::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(15,0,16),Vector3(15,16,16),Vector3(15,16,0),Vector3(15,0,0),1,1);
        }

        if(Block == Ladder3::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,1),Vector3(16,0,1),Vector3(16,16,1),Vector3(0,16,1),1,1);
        }

        if(Block == Ladder4::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,15),Vector3(16,16,15),Vector3(16,0,15),Vector3(0,0,15),1,1);
        }


        if(Block == 4)
        {
            if(GetBlock(x,y+1,z) == 4)
            {
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
            }
            else
            {
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,14,16),Vector3(0,14,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,14,0),Vector3(16,14,16),Vector3(16,0,16));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,14,16),Vector3(16,14,16),Vector3(16,14,0),Vector3(0,14,0));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,14,0),Vector3(16,14,0),Vector3(16,0,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,14,16),Vector3(0,14,16));
            }
        }

        if(Block == 112)
        {
            if(GetBlock(x,y+1,z) == 112)
            {
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
            }
            else
            {
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,14,16),Vector3(0,14,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,14,0),Vector3(16,14,16),Vector3(16,0,16));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,14,16),Vector3(16,14,16),Vector3(16,14,0),Vector3(0,14,0));

                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,14,0),Vector3(16,14,0),Vector3(16,0,0),Vector3(0,0,0));
                BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,14,16),Vector3(0,14,16));
            }
        }

        if(Block == Snow2::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,2,16),Vector3(0,2,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,2,0),Vector3(16,2,16),Vector3(16,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,2,16),Vector3(16,2,16),Vector3(16,2,0),Vector3(0,2,0),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,2,0),Vector3(16,2,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,2,16),Vector3(0,2,16));
        }

        /// MELON PLANTS
        if(Block >= MelonPlant1::getID() && Block <= MelonPlant4::getID())
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(8,0,16),Vector3(8,16,16),Vector3(8,16,0),Vector3(8,0,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(8,0,0),Vector3(8,16,0),Vector3(8,16,16),Vector3(8,0,16),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,8),Vector3(16,16,8),Vector3(16,0,8),Vector3(0,0,8),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,8),Vector3(16,0,8),Vector3(16,16,8),Vector3(0,16,8),1,0);
        }

        /// DOOR 1 Z--
        if  (
            Block == 49 ||
            (Block == 56 && GetBlock(x,y,z-1) != 52 && GetBlock(x,y,z-1) != 56 && (GetBlock(x,y,z+1) == 56 || GetBlock(x,y,z+1) == 52)) ||
            (Block == 56 && GetBlock(x,y,z-1) != 52 && GetBlock(x,y,z-1) != 56 && GetBlock(x,y,z+1) != 52 && GetBlock(x,y,z+1) != 56) ||
            (Block == 55 && GetBlock(x,y,z-1) != 51 && GetBlock(x,y,z-1) != 55 && (GetBlock(x,y,z+1) == 55 || GetBlock(x,y,z+1) == 51))
            )
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,3),Vector3(0,32,3),Vector3(0,32,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,32,0),Vector3(16,32,3),Vector3(16,0,3));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,3),Vector3(0,0,3));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,32,3),Vector3(16,32,3),Vector3(16,32,0),Vector3(0,32,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,32,0),Vector3(16,32,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,3),Vector3(16,0,3),Vector3(16,32,3),Vector3(0,32,3),1,0);
        }

        /// DOOR Z++
        if  (
            Block == 50 ||
            (Block == 56 && GetBlock(x,y,z+1) != 52 && GetBlock(x,y,z+1) != 56 && (GetBlock(x,y,z-1) == 56 || GetBlock(x,y,z-1) == 52)) ||
            (Block == 55 && GetBlock(x,y,z+1) != 51 && GetBlock(x,y,z+1) != 55 && (GetBlock(x,y,z-1) == 55 || GetBlock(x,y,z-1) == 51)) ||
            (Block == 55 && GetBlock(x,y,z+1) != 51 && GetBlock(x,y,z+1) != 55 && GetBlock(x,y,z-1) != 51 && GetBlock(x,y,z-1) != 55)
            )
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,32,16),Vector3(0,32,13),Vector3(0,0,13));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,13),Vector3(16,32,13),Vector3(16,32,16),Vector3(16,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,13),Vector3(16,0,13),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,32,16),Vector3(16,32,16),Vector3(16,32,13),Vector3(0,32,13));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,32,13),Vector3(16,32,13),Vector3(16,0,13),Vector3(0,0,13),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,32,16),Vector3(0,32,16));
        }

        /// DOOR X--
        if  (
            Block == 51 ||
            (Block == 53 && GetBlock(x-1,y,z) != 49 && GetBlock(x-1,y,z) != 53 && (GetBlock(x+1,y,z) == 53 || GetBlock(x+1,y,z) == 49)) ||
            (Block == 53 && GetBlock(x-1,y,z) != 49 && GetBlock(x-1,y,z) != 53 && GetBlock(x+1,y,z) != 49 && GetBlock(x+1,y,z) != 53) ||
            (Block == 54 && GetBlock(x-1,y,z) != 50 && GetBlock(x-1,y,z) != 54 && (GetBlock(x+1,y,z) == 54 || GetBlock(x+1,y,z) == 50))
            )
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,32,16),Vector3(0,32,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(3,0,0),Vector3(3,32,0),Vector3(3,32,16),Vector3(3,0,16),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(3,0,0),Vector3(3,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,32,16),Vector3(3,32,16),Vector3(3,32,0),Vector3(0,32,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,32,0),Vector3(3,32,0),Vector3(3,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(3,0,16),Vector3(3,32,16),Vector3(0,32,16));
        }

        /// DOOR X++
        if  (
            Block == 52 ||
            (Block == 53 && GetBlock(x+1,y,z) != 49 && GetBlock(x+1,y,z) != 53 && (GetBlock(x-1,y,z) == 53 || GetBlock(x-1,y,z) == 49)) ||
            (Block == 54 && GetBlock(x+1,y,z) != 50 && GetBlock(x+1,y,z) != 54 && (GetBlock(x-1,y,z) == 54 || GetBlock(x-1,y,z) == 50)) ||
            (Block == 54 && GetBlock(x+1,y,z) != 50 && GetBlock(x+1,y,z) != 54 && GetBlock(x-1,y,z) != 50 && GetBlock(x-1,y,z) != 54)
            )
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(13,0,16),Vector3(13,32,16),Vector3(13,32,0),Vector3(13,0,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,32,0),Vector3(16,32,16),Vector3(16,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(13,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(13,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(13,32,16),Vector3(16,32,16),Vector3(16,32,0),Vector3(13,32,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(13,32,0),Vector3(16,32,0),Vector3(16,0,0),Vector3(13,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(13,0,16),Vector3(16,0,16),Vector3(16,32,16),Vector3(13,32,16));
        }

        /// STAIRS
        if(Block == 125 || Block == 60 || Block == 67)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,8,16),Vector3(0,16,16),Vector3(0,16,8),Vector3(0,8,8));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,8,8),Vector3(16,16,8),Vector3(16,16,16),Vector3(16,8,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,8),Vector3(0,16,8));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,8),Vector3(16,16,8),Vector3(16,8,8),Vector3(0,8,8),1,0);

            if(BlockTransparentOrSpecial(x,y,z+1) == true)
                BuildWorldBlockPlaneNoCheck(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
        }

        if(Block == 126 || Block == 61 || Block == 68)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,8,8),Vector3(0,16,8),Vector3(0,16,0),Vector3(0,8,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,8,0),Vector3(16,16,0),Vector3(16,16,8),Vector3(16,8,8));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,8),Vector3(16,16,8),Vector3(16,16,0),Vector3(0,16,0));

            if(BlockTransparentOrSpecial(x,y,z-1) == true)
                BuildWorldBlockPlaneNoCheck(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,8,8),Vector3(16,8,8),Vector3(16,16,8),Vector3(0,16,8),1,0);
        }


        if(Block == 127 || Block == 62 || Block == 69)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(8,8,16),Vector3(8,16,16),Vector3(8,16,0),Vector3(8,8,0),1,0);

            if(BlockTransparentOrSpecial(x+1,y,z) == true)
                BuildWorldBlockPlaneNoCheck(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(8,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(8,16,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(8,16,0),Vector3(16,16,0),Vector3(16,8,0),Vector3(8,8,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(8,8,16),Vector3(16,8,16),Vector3(16,16,16),Vector3(8,16,16));
        }

        if(Block == 128 || Block == 63 || Block == 70)
        {
            if(BlockTransparentOrSpecial(x-1,y,z) == true)
                BuildWorldBlockPlaneNoCheck(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(8,8,0),Vector3(8,16,0),Vector3(8,16,16),Vector3(8,8,16),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(8,16,16),Vector3(8,16,0),Vector3(0,16,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(8,16,0),Vector3(8,8,0),Vector3(0,8,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,8,16),Vector3(8,8,16),Vector3(8,16,16),Vector3(0,16,16));
        }

        /// CACTI
        if(Block == 25)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,16),Vector3(1,16,16),Vector3(1,16,0),Vector3(1,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,0),Vector3(15,16,0),Vector3(15,16,16),Vector3(15,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,16,15),Vector3(15,16,15),Vector3(15,16,1),Vector3(1,16,1));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,1),Vector3(16,16,1),Vector3(16,0,1),Vector3(0,0,1));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,15),Vector3(16,0,15),Vector3(16,16,15),Vector3(0,16,15));
        }

        /// LEAVES
        if(Block == 9 || Block == 37 || Block == 38)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));
        }

        /// CHEST
        if(Block == 94)
        {
            // chest
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,15),Vector3(1,14,15),Vector3(1,14,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,1),Vector3(15,14,1),Vector3(15,14,15),Vector3(15,0,15),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,14,15),Vector3(15,14,15),Vector3(15,14,1),Vector3(1,14,1),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(1,14,1),Vector3(15,14,1),Vector3(15,0,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,14,15),Vector3(1,14,15),1,0);

            // chest lock
            blockType = &blockTypes[98];
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,1,Vector3(0,7,9),Vector3(0,11,9),Vector3(0,11,7),Vector3(0,7,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,3,Vector3(0,7,7),Vector3(1,7,7),Vector3(1,7,9),Vector3(0,7,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,4,Vector3(0,11,9),Vector3(1,11,9),Vector3(1,11,7),Vector3(0,11,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,5,Vector3(0,11,7),Vector3(1,11,7),Vector3(1,7,7),Vector3(0,7,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,6,Vector3(0,7,9),Vector3(1,7,9),Vector3(1,11,9),Vector3(0,11,9),1,0);
        }

        if(Block == 95)
        {
            // chest
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,15),Vector3(1,14,15),Vector3(1,14,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,1),Vector3(15,14,1),Vector3(15,14,15),Vector3(15,0,15),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,14,15),Vector3(15,14,15),Vector3(15,14,1),Vector3(1,14,1),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(1,14,1),Vector3(15,14,1),Vector3(15,0,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,14,15),Vector3(1,14,15),1,0);

            // chest lock
            blockType = &blockTypes[98];
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,2,Vector3(16,7,7),Vector3(16,11,7),Vector3(16,11,9),Vector3(16,7,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,3,Vector3(15,7,7),Vector3(16,7,7),Vector3(16,7,9),Vector3(15,7,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,4,Vector3(15,11,9),Vector3(16,11,9),Vector3(16,11,7),Vector3(15,11,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,5,Vector3(15,11,7),Vector3(16,11,7),Vector3(16,7,7),Vector3(15,7,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,6,Vector3(15,7,9),Vector3(16,7,9),Vector3(16,11,9),Vector3(15,11,9),1,0);
        }

        if(Block == 96)
        {
            // chest
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,15),Vector3(1,14,15),Vector3(1,14,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,1),Vector3(15,14,1),Vector3(15,14,15),Vector3(15,0,15),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,14,15),Vector3(15,14,15),Vector3(15,14,1),Vector3(1,14,1),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(1,14,1),Vector3(15,14,1),Vector3(15,0,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,14,15),Vector3(1,14,15),1,0);

            // chest lock
            blockType = &blockTypes[98];
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,1,Vector3(7,7,1),Vector3(7,11,1),Vector3(7,11,0),Vector3(7,7,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,2,Vector3(9,7,0),Vector3(9,11,0),Vector3(9,11,1),Vector3(9,7,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,3,Vector3(7,7,0),Vector3(9,7,0),Vector3(9,7,1),Vector3(7,7,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,4,Vector3(7,11,1),Vector3(9,11,1),Vector3(9,11,0),Vector3(7,11,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,5,Vector3(7,11,0),Vector3(9,11,0),Vector3(9,7,0),Vector3(7,7,0),1,0);
        }

        if(Block == 97)
        {
            // chest
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(1,0,15),Vector3(1,14,15),Vector3(1,14,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(15,0,1),Vector3(15,14,1),Vector3(15,14,15),Vector3(15,0,15),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(1,0,1),Vector3(15,0,1),Vector3(15,0,15),Vector3(1,0,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(1,14,15),Vector3(15,14,15),Vector3(15,14,1),Vector3(1,14,1),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(1,14,1),Vector3(15,14,1),Vector3(15,0,1),Vector3(1,0,1),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(1,0,15),Vector3(15,0,15),Vector3(15,14,15),Vector3(1,14,15),1,0);

            // chest lock
            blockType = &blockTypes[98];
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,1,Vector3(7,7,16),Vector3(7,11,16),Vector3(7,11,15),Vector3(7,7,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,2,Vector3(9,7,15),Vector3(9,11,15),Vector3(9,11,16),Vector3(9,7,16),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,3,Vector3(7,7,15),Vector3(9,7,15),Vector3(9,7,16),Vector3(7,7,16),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,4,Vector3(7,11,16),Vector3(9,11,16),Vector3(9,11,15),Vector3(7,11,15),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,66,transparent,6,Vector3(7,7,16),Vector3(9,7,16),Vector3(9,11,16),Vector3(7,11,16),1,0);
        }

        /// TORCH
        if(Block == Torch::getID())
        {
            //texture stuff
            BaseBlock *blockType = &blockTypes[Block];
            float up = percent*blockType->leftPlane_y + texturePixel*6;
            float down = percent*blockType->leftPlane_y + percent;

            float left = percent * blockType->leftPlane_x + texturePixel*7;
            float right = left + texturePixel*2;

            //standing torch
            block_t Block1 = GetBlock(x,y-1,z);

            if(BlockSolid(x,y-1,z)) /////
            {
                //x-1
                MeshChunk->info(x + 0.4375f,y			,z + 0.4375f + 0.0625*2	,right	, down,1,1,1);
                MeshChunk->info(x + 0.4375f,y + 0.0625*10,z + 0.4375f + 0.0625*2	,right	, up	,1,1,1);
                MeshChunk->info(x + 0.4375f,y + 0.0625*10,z + 0.4375f			,left	, up	,1,1,1);
                MeshChunk->info(x + 0.4375f,y			,z + 0.4375f			,left	, down	,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;

                //x+1
                MeshChunk->info(x + 0.4375f + pixel*2,y		        ,z + 0.4375f            ,right, down,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2,y + pixel*10  ,z + 0.4375f            ,right, up,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2,y + pixel*10  ,z + 0.4375f + pixel*2  ,left, up,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2,y		        ,z + 0.4375f + pixel*2  ,left, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;

                //z-1
                MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f,right, up,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f,left, up,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2   ,y			    ,z + 0.4375f,left, down,1,1,1);
                MeshChunk->info(x + 0.4375f		        ,y			    ,z + 0.4375f,right, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;

                //z+1
                MeshChunk->info(x + 0.4375f		        ,y			    ,z + 0.4375f + pixel*2,left, down,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2   ,y			    ,z + 0.4375f + pixel*2,right, down,1,1,1);
                MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10	,z + 0.4375f + pixel*2,right, up,1,1,1);
                MeshChunk->info(x + 0.4375f		        ,y + pixel*10	,z + 0.4375f + pixel*2,left, up,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;

                //y+1
                {
                    up = percent*blockType->leftPlane_y + texturePixel*6;
                    down = up + texturePixel*2;

                    left = percent * blockType->leftPlane_x + texturePixel*7;
                    right = left + texturePixel*2;

                    MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f + pixel*2  ,left, up,1,1,1);
                    MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f + pixel*2  ,right, up,1,1,1);
                    MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f            ,right, down,1,1,1);
                    MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f            ,left, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;
                }
            }
            else
            {

                bool canPlaseTorch = true;
                if(BlockSolid(x-1,y,z) && canPlaseTorch)
                {

                    //x-1
                    MeshChunk->info(x - pixel   ,y + pixel*3    ,z + 0.4375f + pixel*2	,right	, down	,1,1,1);
                    MeshChunk->info(x + pixel*4 ,y + pixel*13   ,z + 0.4375f + pixel*2	,right	, up	,1,1,1);
                    MeshChunk->info(x + pixel*4 ,y + pixel*13   ,z + 0.4375f			,left	, up	,1,1,1);
                    MeshChunk->info(x - pixel   ,y + pixel*3    ,z + 0.4375f			,left	, down	,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //x+1
                    MeshChunk->info(x + pixel    ,y	+ pixel*3	,z + 0.4375f            ,right, down,1,1,1);
                    MeshChunk->info(x + pixel*6  ,y + pixel*13  ,z + 0.4375f            ,right, up  ,1,1,1);
                    MeshChunk->info(x + pixel*6  ,y + pixel*13  ,z + 0.4375f + pixel*2  ,left, up   ,1,1,1);
                    MeshChunk->info(x + pixel    ,y + pixel*3   ,z + 0.4375f + pixel*2  ,left, down ,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z-1
                    MeshChunk->info(x + pixel*4		,y + pixel*13   ,z + pixel*7,right, up  ,1,1,1);
                    MeshChunk->info(x + pixel*6     ,y + pixel*13   ,z + pixel*7,left, up   ,1,1,1);
                    MeshChunk->info(x + pixel       ,y + pixel*3	,z + pixel*7,left, down ,1,1,1);
                    MeshChunk->info(x - pixel	    ,y + pixel*3	,z + pixel*7,right, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z+1
                    MeshChunk->info(x - pixel	        ,y + pixel*3    ,z + pixel*9,left, down,1,1,1);
                    MeshChunk->info(x + pixel           ,y + pixel*3	,z + pixel*9,right, down,1,1,1);
                    MeshChunk->info(x + pixel*6         ,y + pixel*13	,z + pixel*9,right, up,1,1,1);
                    MeshChunk->info(x + pixel*4		    ,y + pixel*13	,z + pixel*9,left, up,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;


                    //y+1
                    {
                        up = percent*blockType->leftPlane_y + texturePixel*6;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*4		        ,y + pixel*13   ,z + pixel*7 + pixel*2  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*4 + pixel*2   ,y + pixel*13   ,z + pixel*7 + pixel*2  ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*4 + pixel*2   ,y + pixel*13   ,z + pixel*7            ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*4		        ,y + pixel*13   ,z + pixel*7            ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }

                    {
                        up = percent*blockType->leftPlane_y + texturePixel*14;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x - pixel   ,y + pixel*3   ,z + pixel*7            ,left, up,1,1,1);
                        MeshChunk->info(x + pixel   ,y + pixel*3   ,z + pixel*7            ,right, up,1,1,1);
                        MeshChunk->info(x + pixel   ,y + pixel*3   ,z + pixel*7 + pixel*2  ,right, down,1,1,1);
                        MeshChunk->info(x - pixel	,y + pixel*3   ,z + pixel*7 + pixel*2  ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }
                    canPlaseTorch = false;
                }

                if(BlockSolid(x+1,y,z) && canPlaseTorch)
                {
                    //x-1
                    MeshChunk->info(x + pixel*15   ,y + pixel*3    ,z + 0.4375f + pixel*2	,right	, down	,1,1,1);
                    MeshChunk->info(x + pixel*10 ,y + pixel*13   ,z + 0.4375f + pixel*2	,right	, up	,1,1,1);
                    MeshChunk->info(x + pixel*10 ,y + pixel*13   ,z + 0.4375f			,left	, up	,1,1,1);
                    MeshChunk->info(x + pixel*15  ,y + pixel*3    ,z + 0.4375f			,left	, down	,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //x+1
                    MeshChunk->info(x + pixel*17    ,y	+ pixel*3	,z + 0.4375f            ,right, down,1,1,1);
                    MeshChunk->info(x + pixel*12  ,y + pixel*13  ,z + 0.4375f            ,right, up  ,1,1,1);
                    MeshChunk->info(x + pixel*12  ,y + pixel*13  ,z + 0.4375f + pixel*2  ,left, up   ,1,1,1);
                    MeshChunk->info(x + pixel*17    ,y + pixel*3   ,z + 0.4375f + pixel*2  ,left, down ,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z-1
                    MeshChunk->info(x + pixel*12		,y + pixel*13   ,z + pixel*9,right, up  ,1,1,1);
                    MeshChunk->info(x + pixel*10     ,y + pixel*13   ,z + pixel*9,left, up   ,1,1,1);
                    MeshChunk->info(x + pixel*15       ,y + pixel*3	,z + pixel*9,left, down ,1,1,1);
                    MeshChunk->info(x + pixel*17	    ,y + pixel*3	,z + pixel*9,right, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z+1
                    MeshChunk->info(x + pixel*17	        ,y + pixel*3    ,z + pixel*7,left, down,1,1,1);
                    MeshChunk->info(x + pixel*15           ,y + pixel*3	,z + pixel*7,right, down,1,1,1);
                    MeshChunk->info(x + pixel*10         ,y + pixel*13	,z + pixel*7,right, up,1,1,1);
                    MeshChunk->info(x + pixel*12		    ,y + pixel*13	,z + pixel*7,left, up,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    {
                        up = percent*blockType->leftPlane_y + texturePixel*6;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*10		        ,y + pixel*13   ,z + pixel*7 + pixel*2  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*12                ,y + pixel*13   ,z + pixel*7 + pixel*2  ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*12                ,y + pixel*13   ,z + pixel*7            ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*10		        ,y + pixel*13   ,z + pixel*7            ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }

                    {
                        up = percent*blockType->leftPlane_y + texturePixel*14;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel * 15  ,y + pixel*3   ,z + pixel*7            ,left, up,1,1,1);
                        MeshChunk->info(x + pixel * 17  ,y + pixel*3   ,z + pixel*7            ,right, up,1,1,1);
                        MeshChunk->info(x + pixel * 17  ,y + pixel*3   ,z + pixel*7 + pixel*2  ,right, down,1,1,1);
                        MeshChunk->info(x + pixel * 15 	,y + pixel*3   ,z + pixel*7 + pixel*2  ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }
                    canPlaseTorch = false;
                }

                if(BlockSolid(x,y,z-1) && canPlaseTorch)
                {
                    //x-1
                    MeshChunk->info(x + pixel*9,y + pixel*3		,z - pixel	    ,right	, down	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*4	,right	, up	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*6	,left	, up	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel	    ,left	, down	,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //x+1
                    MeshChunk->info(x + pixel*7,y + pixel*3     ,z + pixel          ,right, down,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*6           ,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*4  ,left, up,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*3	    ,z - pixel ,left, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z-1
                    MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*4,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*4,left, up,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3    ,z - pixel,left, down,1,1,1);
                    MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z - pixel,right, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z+1
                    MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel,left, down,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3	,z + pixel,right, down,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13	,z + pixel*6,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7		        ,y + pixel*13	,z + pixel*6,left, up,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //y+1
                    {
                        up = percent*blockType->leftPlane_y + texturePixel*6;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*6  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*6  ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*4            ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*4          ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }

                    //y-1
                    {
                        up = percent*blockType->leftPlane_y + texturePixel*14;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*7		        ,y + pixel*3   ,z + pixel  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*7             ,y + pixel*3   ,z - pixel  ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*9             ,y + pixel*3   ,z - pixel  ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*9		        ,y + pixel*3   ,z + pixel  ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }
                    canPlaseTorch = false;
                }

                if(BlockSolid(x,y,z+1) && canPlaseTorch)
                {

                    //x-1
                    MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel*15	    ,right	, down	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*10	,right	, up	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*12	,left	, up	,1,1,1);
                    MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel*17	    ,left	, down	,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //x+1
                    MeshChunk->info(x + pixel*7,y + pixel*3     ,z + pixel*17         ,right, down,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*12           ,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*10  ,left, up,1,1,1);
                    MeshChunk->info(x + pixel*7,y + pixel*3	    ,z + pixel*15 ,left, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z-1
                    MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*10,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*10,left, up,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3    ,z + pixel*15,left, down,1,1,1);
                    MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel*15,right, down,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //z+1
                    MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel*17,left, down,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3	,z + pixel*17,right, down,1,1,1);
                    MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13	,z + pixel*12,right, up,1,1,1);
                    MeshChunk->info(x + pixel*7		        ,y + pixel*13	,z + pixel*12,left, up,1,1,1);

                    MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                    MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                    iVertex += 4;

                    //y+1
                    {
                        up = percent*blockType->leftPlane_y + texturePixel*6;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*12  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*12  ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*10            ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*10          ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }

                            //y+1
                    {
                        up = percent*blockType->leftPlane_y + texturePixel*14;
                        down = up + texturePixel*2;

                        left = percent * blockType->leftPlane_x + texturePixel*7;
                        right = left + texturePixel*2;

                        MeshChunk->info(x + pixel*7		        ,y + pixel*3   ,z + pixel *17  ,left, up,1,1,1);
                        MeshChunk->info(x + pixel*7             ,y + pixel*3   ,z + pixel *15 ,right, up,1,1,1);
                        MeshChunk->info(x + pixel*9             ,y + pixel*3   ,z + pixel *15 ,right, down,1,1,1);
                        MeshChunk->info(x + pixel*9		        ,y + pixel*3   ,z + pixel *17 ,left, down,1,1,1);

                        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                        iVertex += 4;
                    }
                }
            }
        }
    }

    /// HALF BLOCKS
    if(blockTypes[Block].blockModel == 1)
    {
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,8,16),Vector3(0,8,0),Vector3(0,0,0));
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,8,0),Vector3(16,8,16),Vector3(16,0,16));

        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,8,16),Vector3(16,8,16),Vector3(16,8,0),Vector3(0,8,0),1,0);

        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,8,0),Vector3(16,8,0),Vector3(16,0,0),Vector3(0,0,0));
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,8,16),Vector3(0,8,16));
    }


    /// FENCE
    if(blockTypes[Block].blockModel == 2)
    {
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(6,0,10),Vector3(6,16,10),Vector3(6,16,6),Vector3(6,0,6),1,0);
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(10,0,6),Vector3(10,16,6),Vector3(10,16,10),Vector3(10,0,10),1,0);

        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(6,0,6),Vector3(10,0,6),Vector3(10,0,10),Vector3(6,0,10));
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(6,16,10),Vector3(10,16,10),Vector3(10,16,6),Vector3(6,16,6));

        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(6,16,6),Vector3(10,16,6),Vector3(10,0,6),Vector3(6,0,6),1,0);
        BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(6,0,10),Vector3(10,0,10),Vector3(10,16,10),Vector3(6,16,10),1,0);

        if(BlockSolid(x,y,z-1) == true)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(7,12,8),Vector3(7,15,8),Vector3(7,15,0),Vector3(7,12,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(7,6,8),Vector3(7,9,8),Vector3(7,9,0),Vector3(7,6,0),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(9,12,0),Vector3(9,15,0),Vector3(9,15,8),Vector3(9,12,8),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(9,6,0),Vector3(9,9,0),Vector3(9,9,8),Vector3(9,6,8),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(7,12,0),Vector3(9,12,0),Vector3(9,12,8),Vector3(7,12,8),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(7,6,0),Vector3(9,6,0),Vector3(9,6,8),Vector3(7,6,8),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(7,15,8),Vector3(9,15,8),Vector3(9,15,0),Vector3(7,15,0),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(7,9,8),Vector3(9,9,8),Vector3(9,9,0),Vector3(7,9,0),1,0);
        }

        if(BlockSolid(x,y,z+1) == true)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(7,12,16),Vector3(7,15,16),Vector3(7,15,8),Vector3(7,12,8),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(7,6,16),Vector3(7,9,16),Vector3(7,9,8),Vector3(7,6,8),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(9,12,8),Vector3(9,15,8),Vector3(9,15,16),Vector3(9,12,16),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(9,6,8),Vector3(9,9,8),Vector3(9,9,16),Vector3(9,6,16),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(7,12,8),Vector3(9,12,8),Vector3(9,12,16),Vector3(7,12,16),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(7,6,8),Vector3(9,6,8),Vector3(9,6,16),Vector3(7,6,16),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(7,15,16),Vector3(9,15,16),Vector3(9,15,8),Vector3(7,15,8),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(7,9,16),Vector3(9,9,16),Vector3(9,9,8),Vector3(7,9,8),1,0);
        }

        if(BlockSolid(x-1,y,z) == true)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,15,7),Vector3(8,15,7),Vector3(8,12,7),Vector3(0,12,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,9,7),Vector3(8,9,7),Vector3(8,6,7),Vector3(0,6,7),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,12,9),Vector3(8,12,9),Vector3(8,15,9),Vector3(0,15,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,6,9),Vector3(8,6,9),Vector3(8,9,9),Vector3(0,9,9),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,12,7),Vector3(8,12,7),Vector3(8,12,9),Vector3(0,12,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,6,7),Vector3(8,6,7),Vector3(8,6,9),Vector3(0,6,9),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,15,9),Vector3(8,15,9),Vector3(8,15,7),Vector3(0,15,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,9,9),Vector3(8,9,9),Vector3(8,9,7),Vector3(0,9,7),1,0);
        }

        if(BlockSolid(x+1,y,z) == true)
        {
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(8,15,7),Vector3(16,15,7),Vector3(16,12,7),Vector3(8,12,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(8,9,7),Vector3(16,9,7),Vector3(16,6,7),Vector3(8,6,7),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(8,12,9),Vector3(16,12,9),Vector3(16,15,9),Vector3(8,15,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(8,6,9),Vector3(16,6,9),Vector3(16,9,9),Vector3(8,9,9),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(8,12,7),Vector3(16,12,7),Vector3(16,12,9),Vector3(8,12,9),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(8,6,7),Vector3(16,6,7),Vector3(16,6,9),Vector3(8,6,9),1,0);

            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(8,15,9),Vector3(16,15,9),Vector3(16,15,7),Vector3(8,15,7),1,0);
            BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(8,9,9),Vector3(16,9,9),Vector3(16,9,7),Vector3(8,9,7),1,0);
        }
    }

    /// FLOWERS & CANES & MOOSHROOMS
    if(blockTypes[Block].blockModel == 3)
    {
        BlockColorx1 = Vector3(BlockFinalLight(x,y,z),BlockFinalLight(x,y,z),BlockFinalLight(x,y,z));
        BlockColorx2 = BlockColorx1*0.9f;

        up = blockType->leftPlane_y*percent;
        down = up+percent;

        left = blockType->leftPlane_x*percent;
        right = left+percent;

        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx1;

            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+1 );
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y+1, z );
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx1;

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// WHEAT
    if(blockTypes[Block].blockModel == 4)
    {
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = true;

        BlockColorx2 = Vector3(BlockFinalLight(x,y,z),BlockFinalLight(x,y,z),BlockFinalLight(x,y,z));
        BlockColorz2 = BlockColorx2*0.9f;

        up = blockType->leftPlane_y*percent;
        down = up+percent;

        left = blockType->leftPlane_x*percent;
        right = left+percent;

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x+pixel*4, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*4, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*4, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*4, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x+pixel*4, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*4, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*4, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*4, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x+pixel*12, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*12, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*12, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*12, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorx2;

            MeshChunk->position(x+pixel*12, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*12, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*12, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*12, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorz2;

            MeshChunk->position(x,   y+1, z+pixel*4);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+pixel*4);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+pixel*4);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+pixel*4);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate == true)
        {
            light1 = light2 = light3 = light4 = BlockColorz2;

            MeshChunk->position(x,   y,   z+pixel*4);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*4);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+pixel*4);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+pixel*4);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate == true)
        {
            light1 = light2 = light3 = light4 = BlockColorz2;

            MeshChunk->position(x,   y,   z+pixel*12);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*12);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+pixel*12);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+pixel*12);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            light1 = light2 = light3 = light4 = BlockColorz2;

            MeshChunk->position(x,   y+1, z+pixel*12);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+pixel*12);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+pixel*12);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+pixel*12);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }
}

void CraftWorld::GetNormalBlock(int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent)
{
    ///left     right
    // x y z    x y z
    // 0 0 1    1 0 0
    // 0 1 1    1 1 0
    // 0 1 0    1 1 1
    // 0 0 0    1 0 1

    ///down     top
    // x y z    x y z
    // 0 0 0    0 1 1
    // 1 0 0    1 1 1
    // 1 0 1    1 1 0
    // 0 0 1    0 1 0

    ///back     forward
    // x y z    x y z
    // 0 1 0    0 0 1
    // 1 1 0    1 0 1
    // 1 0 0    1 1 1
    // 0 0 0    0 1 1

    BaseBlock *blockType = &blockTypes[Block];

    //BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,1,Vector3(0,0,16),Vector3(0,16,16),Vector3(0,16,0),Vector3(0,0,0));
 //   BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,2,Vector3(16,0,0),Vector3(16,16,0),Vector3(16,16,16),Vector3(16,0,16));

  //  BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,3,Vector3(0,0,0),Vector3(16,0,0),Vector3(16,0,16),Vector3(0,0,16));
//BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,4,Vector3(0,16,16),Vector3(16,16,16),Vector3(16,16,0),Vector3(0,16,0));

  //  BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,5,Vector3(0,16,0),Vector3(16,16,0),Vector3(16,0,0),Vector3(0,0,0));
  //  BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,6,Vector3(0,0,16),Vector3(16,0,16),Vector3(16,16,16),Vector3(0,16,16));

    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    bool canCreate = false;
    bool DefaultBlock = false;
    bool transparentBlock = false;

    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;

    char Block1 = 0;

    Vector3 light1, light2, light3, light4;
    Block = GetBlock(x,y,z);


    Vector3 BlockColorx1;
    Block1 = GetBlock(x-1,y,z);

    if(transparent == true)
    {
        if (x > 0)
        {
            transparentBlock = BlockTransparent(x-1,y,z);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x-1,y,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x-1,y,z) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (x > 0)
        {
            if (BlockSpecial(x-1,y,z) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x-1,y,z) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }


    if(canCreate == true)
    {
        BlockColorx1 = Vector3(BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z)) * 0.95f;
        light1 = light2 = light3 = light4 = BlockColorx1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        left = percent*blockType->leftPlane_x;
        right = percent*blockType->leftPlane_x+percent;

        up = percent*blockType->leftPlane_y;
        down = percent*blockType->leftPlane_y+percent;

        MeshChunk->position(x+0*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+0*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+0*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+0*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    Vector3 BlockColorx2;
    canCreate = false;
    Block1 = GetBlock(x+1,y,z);

    if(transparent == true)
    {
        if (x < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x+1,y,z);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x+1,y,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x+1,y,z) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (x < WORLD_SIZE - 1)
        {
            if (BlockSpecial(x+1,y,z) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x+1,y,z) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }

    if (canCreate)
    {
        BlockColorx2 = Vector3(BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z)) * 0.95f;
        light1 = light2 = light3 = light4 = BlockColorx2;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx2 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        left = percent*blockType->rightPlane_x;
        right = percent*blockType->rightPlane_x+percent;

        up = percent*blockType->rightPlane_y;
        down = percent*blockType->rightPlane_y+percent;

        MeshChunk->position(x+16*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+16*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }



    canCreate = false;
    Vector3 BlockColory2;
    Block1 = GetBlock(x,y-1,z);

    if(transparent == true)
    {
        if (y > 0)
        {
            transparentBlock = BlockTransparent(x,y-1,z);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y-1,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x,y-1,z) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (y > 0)
        {
            if (BlockSpecial(x,y-1,z) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x,y-1,z) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }

    if (canCreate)
    {
        BlockColory2 = Vector3(BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z)) * 0.6f;
        light1 = light2 = light3 = light4 = BlockColory2;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory2 * lightShadowFactor;

            //simple shadows
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
            {
                light4-=lightFactor;
            }
        }

        left = percent*blockType->downPlane_x;
        right = percent*blockType->downPlane_x+percent;

        up = percent*blockType->downPlane_y;
        down = percent*blockType->downPlane_y+percent;

        MeshChunk->position(x+0*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+16*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+16*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+0*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }



    canCreate = false;
    Vector3 BlockColory1;
    Block1 = GetBlock(x,y+1,z);

    if(transparent == true)
    {
        if (y < WORLD_HEIGHT - 1)
        {
            transparentBlock = BlockTransparent(x,y+1,z);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y+1,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 ))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x,y+1,z) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (y < WORLD_HEIGHT - 1)
        {
            if (BlockSpecial(x,y+1,z) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x,y+1,z) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }

    if(Block1 == 93)
    {
        canCreate = false;
    }

    if(canCreate)
    {

        BlockColory1 = Vector3(BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z));
        light1 = light2 = light3 = light4 = BlockColory1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory1 * lightShadowFactor;
            //simple shadows
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light4-=lightFactor;
            }
        }

        left = percent*blockType->upPlane_x;
        right = percent*blockType->upPlane_x+percent;

        up = percent*blockType->upPlane_y;
        down = percent*blockType->upPlane_y+percent;

        MeshChunk->position(x+0*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+0*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);


        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    Vector3 BlockColorz1;
    canCreate = false;
    Block1 = GetBlock(x,y,z-1);

    if(transparent == true)
    {
        if (z > 0)
        {
            transparentBlock = BlockTransparent(x,y,z-1);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z-1) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x,y,z-1) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (z > 0)
        {
            if (BlockSpecial(x,y,z-1) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x,y,z-1) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }

    if (canCreate)
    {
        BlockColorz1 = Vector3(BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1)) * 0.75f;
        light1 = light2 = light3 = light4 = BlockColorz1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        left = percent*blockType->botPlane_x;
        right = percent*blockType->botPlane_x+percent;

        up = percent*blockType->botPlane_y;
        down = percent*blockType->botPlane_y+percent;

        MeshChunk->position(x+0*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+16*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+0*pixel, y+0*pixel, z+0*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    Vector3 BlockColorz2;
    canCreate = false;
    Block1 = GetBlock(x,y,z+1);

    if(transparent == true)
    {
        if (z < WORLD_SIZE-1)
        {
            transparentBlock = BlockTransparent(x,y,z+1);

            if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z+1) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
            {
                canCreate = true;
            }
            if (transparentBlock == false && BlockSpecial(x,y,z+1) == 0)
            {
                canCreate = false;
            }
        }
    }
    else
    {
        if (z < WORLD_SIZE-1)
        {
            if (BlockSpecial(x,y,z+1) > 0 && Block1 != Block)
            {
                canCreate = true;
            }
            if (BlockTransparent(x,y,z+1) == true || Block1 == 0)
            {
                canCreate = true;
            }
        }
    }

    if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
    {
        canCreate = false;
    }


    if (canCreate == true)
    {
        BlockColorz2 = Vector3(BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1)) * 0.75f;
        light1 = light2 = light3 = light4 = BlockColorz2;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz2 * lightShadowFactor;

            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light3-=lightFactor;
            }
        }

        left = percent*blockType->forPlane_x;
        right = percent*blockType->forPlane_x+percent;

        up = percent*blockType->forPlane_y;
        down = percent*blockType->forPlane_y+percent;

        MeshChunk->position(x+0*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+16*pixel, y+0*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+16*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+0*pixel, y+16*pixel, z+16*pixel);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }
}

void CraftWorld::UpdateLightAreaIn(Vector3 pos)
{
    std::vector<Vector4> lights;
    Vector3 pos2 = pos;


	for (int x2 = pos2.x-20; x2 < pos2.x+20; ++x2)
	{
		for (int y2 = pos2.y-20; y2 < pos2.y+20; ++y2)
		{
			for (int z2 = pos2.z-20; z2 < pos2.z+20; ++z2)
			{
			    block_t Block2 = GetBlock(x2,y2,z2);
				if(LightSourceBlock(Block2) == true)
				{
				    lights.push_back(Vector4(x2,y2,z2,sqrt(pow(x2-pos2.x,2)+pow(y2-pos2.y,2)+pow(z2-pos2.z,2))));
				}
			}
		}
	}

    if(lights.empty() == false)
    {
        for(int j = 0; j < lights.size(); j++)
        {
            for(int i = 0; i < lights.size()-j; i++)
            {
                Vector4 temp = Vector4(0,0,0,0);
                if(i != lights.size()-1)
                {
                    if(lights[i].w > lights[i+1].w)
                    {
                        temp = lights[i+1];
                        lights[i+1] = lights[i];
                        lights[i] = temp;
                    }
                }
            }
        }

        for(int j = 0; j < lights.size(); j++)
        {
            if(lights[j].w <= 10.0f)
            {
                RemoveLigtSourceAtPosition(lights[j].x,lights[j].y,lights[j].z,0);
            }
        }
        for(int j = 0; j < lights.size(); j++)
        {
            if(lights[j].w <= 20.0f)
            {
                SetLigtSourcePosition(lights[j].x,lights[j].y,lights[j].z,0);
            }
        }
        lights.clear();
    }
}

/*void CraftWorld::AddChunkToUpdate(const int x, const int y, const int z)
{
    int chunkTarget = getChunkId(Vector3(x,y,z));
    if(chunkTarget != -1)
        mChunks[chunkTarget]->needUpdate = true;
        SetAllChunksToUpdate
}*/

void CraftWorld::rebuildNearestChunksForLight(int id,Vector3 pos)
{
    Vector3 test = mChunks[id]->bBox.onBorder(pos);
    Vector3 temp = pos;

    int chunkNumber = -1;

    if(temp.x - mChunks[id]->chunkStartX >= 10)
    {
        chunkNumber = getChunkId(Vector3(temp.x + 8,temp.y,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y+8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y+16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y-16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y-8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ < 10 && temp.z - mChunks[id]->chunkStartZ > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+8,temp.y,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }



    if(temp.x - mChunks[id]->chunkStartX < 10 && temp.x - mChunks[id]->chunkStartX > 6)
    {
        chunkNumber = getChunkId(Vector3(temp.x+16,temp.y,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        chunkNumber = getChunkId(Vector3(temp.x-16,temp.y,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y+8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y+8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y+16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y-16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y+16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y-16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y-8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y-8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z -mChunks[id]-> chunkStartZ >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ < 10 && temp.z - mChunks[id]->chunkStartZ > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x+16,temp.y,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x-16,temp.y,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }



    if(temp.x - mChunks[id]->chunkStartX <= 6)
    {
        chunkNumber = getChunkId(Vector3(temp.x-8,temp.y,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y+8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y+16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y-16,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y-8,temp.z));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ < 10 && temp.z - mChunks[id]->chunkStartZ > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.z - mChunks[id]->chunkStartZ <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x-8,temp.y,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }



    if(temp.z - mChunks[id]->chunkStartZ >= 10)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y,temp.z+8));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+8,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+16,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-16,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 2)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-8,temp.z+8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }



    if(temp.z - mChunks[id]->chunkStartZ < 10 && temp.z - mChunks[id]->chunkStartZ > 6)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y,temp.z+16));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }
        chunkNumber = getChunkId(Vector3(temp.x,temp.y,temp.z-16));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+8,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+8,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+16,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+16,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }

            chunkNumber = getChunkId(Vector3(temp.x,temp.y-16,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-16,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-8,temp.z+16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-8,temp.z-16));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }



    if(temp.z - mChunks[id]->chunkStartZ <= 6)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y,temp.z-8));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }

        if(temp.y - mChunks[id]->chunkStartY >= 10)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+8,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y+16,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-16,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }

        if(temp.y - mChunks[id]->chunkStartY <= 2)
        {
            chunkNumber = getChunkId(Vector3(temp.x,temp.y-8,temp.z-8));
            if(chunkNumber != -1)
            {
                toUpdate.push_back(chunkNumber);
            }
        }
    }

    if(temp.y - mChunks[id]->chunkStartY >= 10)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y+8,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }
    }

    if(temp.y - mChunks[id]->chunkStartY < 10 && temp.y - mChunks[id]->chunkStartY > 6)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y+16,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }
        chunkNumber = getChunkId(Vector3(temp.x,temp.y-16,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }
    }

    if(temp.y - mChunks[id]->chunkStartY <= 2)
    {
        chunkNumber = getChunkId(Vector3(temp.x,temp.y-8,temp.z));
        if(chunkNumber != -1)
        {
            toUpdate.push_back(chunkNumber);
        }
    }
}

void CraftWorld::rebuildNearestChunks(int id,Vector3 pos)
{
    Vector3 test = mChunks[id]->bBox.onBorder(pos);
    Vector3 temp = pos;
    int chunkNumber = -1;

    if(test.x != 0)
    {
        temp.x +=test.x;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }


        //now check for other with this... //needed by shadows
        if(test.y != 0)
        {
            temp.y +=test.y;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }

        if(test.z != 0)
        {
            temp.z +=test.z;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }


    if(test.y != 0)
    {
        temp = pos;
        temp.y +=test.y;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }

        if(test.z != 0)
        {
            temp.z +=test.z;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }

    if(test.z != 0)
    {
        temp = pos;
        temp.z +=test.z;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }

        if(test.x != 0)
        {
            temp.x +=test.x;

            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }
}

void CraftWorld::createWorldChunkss()
{
    createdChunksCount = 0;

    for (int z = 0; z < WORLD_SIZE; z += CHUNK_SIZE)
    {
        for (int y = 0; y < WORLD_HEIGHT; y += CHUNK_SIZE)
        {
            for (int x = 0; x < WORLD_SIZE; x += CHUNK_SIZE)
            {
                createChunks(x,y,z);
                createTransparentChunks(x,y,z);
            }
        }
    }
}

void CraftWorld::UpdateChunkBlocks(int id)
{
    SimpleMeshChunk* MeshChunk = mChunks[id];

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                if (BlockUpdate2(x,y,z) == 0)
                {
                    continue;
                }
                if(GetBlock(x,y,z) == 0)
                {
                    continue;
                }
                if(x > 0 && x < WORLD_SIZE && y > 0 && y < WORLD_SIZE && z > 0 && z < WORLD_SIZE)
                {
                    if(GetBlock(x,y,z) == 2 && (GetBlock(x,y+1,z) == 0 || GetBlock(x,y+1,z) == 48 || GetBlock(x,y+1,z) == 119 || GetBlock(x,y+1,z) == 120 || GetBlock(x,y+1,z) == 77 || GetBlock(x,y+1,z) == 78 || GetBlock(x,y+1,z) == 59) && GetBlockLight(x,y,z) > 128)
                    {
                        GetBlock(x,y,z) = 1;
                        continue;
                    }
                    if(GetBlock(x,y,z) == 1 && GetBlock(x,y+1,z) != 0 && GetBlock(x,y+1,z) != 119 && GetBlock(x,y+1,z) != 120 && GetBlock(x,y+1,z) != 48 && GetBlock(x,y+1,z) != 77 && GetBlock(x,y+1,z) != 78 && GetBlock(x,y+1,z) != 59)
                    {
                        GetBlock(x,y,z) = 2;
                        continue;

                    }

                    if(GetBlock(x,y,z) == 79)
                    {
                        if(GetBlock(x-1,y,z) == 4 || GetBlock(x+1,y,z) == 4 || GetBlock(x,y,z-1) == 4 || GetBlock(x,y,z+1) == 4 || GetBlock(x,y-1,z) == 4)
                        {
                            if(rand() % 100 < 67)
                            {
                                GetBlock(x,y,z) = 80;
                            }
                        }
                    }
                    if(GetBlock(x,y,z) == 80)
                    {
                        if(GetBlock(x-1,y,z) == 4 && GetBlock(x+1,y,z) == 4 && GetBlock(x,y,z-1) == 4 && GetBlock(x,y,z+1) == 4 && GetBlock(x,y-1,z) == 4)
                        {
                            if(rand() % 100 < 67)
                            {
                                GetBlock(x,y,z) = 79;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 79 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 8 == 1)
                        {
                            GetBlock(x,y,z) = 2;
                            continue;
                        }
                    }
                    if(GetBlock(x,y,z) == 80 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 12 == 1)
                        {
                            GetBlock(x,y,z) = 79;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 77)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 77;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 78)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 78;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 33 && GetBlock(x,y+1,z) == 0 && GetBlock(x,y-3,z) != 33 && GetBlock(x,y-3,z) != 0)
                    {
                        if(rand() % 4 == 1)
                        {
                            GetBlock(x,y+1,z) = 33;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y+2,z) == 4 && GetBlock(x,y+1,z) == 0)
                    {
                        GetBlock(x,y+1,z) = 36; //make coblestone
                        continue;
                    }


                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y-2,z) == 4 && GetBlock(x,y-1,z) == 0)
                    {
                        GetBlock(x,y-1,z) = 46; //make obsidian
                        continue;
                    }

                    /// oak tree growing
                    if(GetBlock(x,y,z) == 121 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2))
                    {
                        if((rand() % 14 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 32 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 1 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 9;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 9;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 9;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 8;
                            }
                        }
                    }


                    /// birch tree growing
                    if(GetBlock(x,y,z) == 123 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2))
                    {
                        if((rand() % 13 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 40 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 2 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 38;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 38;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 38;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 31;
                            }
                        }
                    }


                    /// spruce tree growing
                    if(GetBlock(x,y,z) == 122 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2 || GetBlock(x,y-1,z) == 29))
                    {
                        if((rand() % 22 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 14 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;

                            y = groundHeight(x,z);
                            char TrunkHeight = 6;
                            char type;

                            //check if there is an water on there or another tree
                            bool flag = 1;

                            for (int y1 = y+1; y1 <= y + TrunkHeight ; y1++)
                            {
                                if(GetBlock(x, y1, z) != 0)
                                {
                                    flag = 0;
                                    break;
                                }
                            }

                            if(flag == 0)continue;

                            if(rand() % 7 == 1)
                            {
                                type = 1;
                                TrunkHeight = 6 + rand() % 3;
                            }
                            else
                            {
                                type = 0;
                            }

                            //Create the tree trunk
                            for (int y1 = y; y1 <= y + TrunkHeight ; y1++)
                            {
                                block_t& Block = GetBlock(x, y1, z);
                                Block = 30;
                            }

                            if(type == 0)
                            {
                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    for(int zz = -2; zz <= 2; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 1;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -2; xx <= 2; xx++)
                                {
                                    for(int zz = -1; zz <= 1; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 1;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    for(int zz = -2; zz <= 2; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 3;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -2; xx <= 2; xx++)
                                {
                                    for(int zz = -1; zz <= 1; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 3;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;
                                        int y1 = y + 2;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }


                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;
                                    int y1 = y + 2;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;
                                        int y1 = y + 4;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }


                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + 4;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    int x1 = xx + x;// :D - what a shitty code
                                    int y1 = y + 6;
                                    int z1 = z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + 6;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                block_t& Block = GetBlock(x, y+7, z);
                                if (Block == 0) Block = 37;
                            }
                            else // type == 1
                            {
                                block_t& Block = GetBlock(x, y+TrunkHeight+1, z);
                                if (Block == 0) Block = 37;

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;// :D - what a shitty code
                                        int y1 = y + TrunkHeight;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;
                                    int y1 = y + TrunkHeight;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;// :D - what a shitty code
                                        int y1 = y + TrunkHeight-1;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + TrunkHeight-1;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void CraftWorld::UpdateChunkGrowingBlocks(int id)
{
    SimpleMeshChunk* MeshChunk = mChunks[id];

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                if (BlockUpdate2(x,y,z) == 0)
                {
                    continue;
                }
                if(GetBlock(x,y,z) == 0)
                {
                    continue;
                }
                if(x > 0 && x < WORLD_SIZE && y > 0 && y < WORLD_SIZE && z > 0 && z < WORLD_SIZE)
                {
                    if(GetBlock(x,y,z) == 79)
                    {
                        if(GetBlock(x-1,y,z) == 4 || GetBlock(x+1,y,z) == 4 || GetBlock(x,y,z-1) == 4 || GetBlock(x,y,z+1) == 4 || GetBlock(x,y-1,z) == 4)
                        {
                            if(rand() % 100 < 67)
                            {
                                GetBlock(x,y,z) = 80;
                            }
                        }
                    }
                    if(GetBlock(x,y,z) == 80)
                    {
                        if(GetBlock(x-1,y,z) == 4 && GetBlock(x+1,y,z) == 4 && GetBlock(x,y,z-1) == 4 && GetBlock(x,y,z+1) == 4 && GetBlock(x,y-1,z) == 4)
                        {
                            if(rand() % 100 < 67)
                            {
                                GetBlock(x,y,z) = 79;
                            }
                        }
                    }

                    // melon plants
                    if(GetBlock(x,y,z) == 130)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 131;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 131;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 131)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 132;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 132;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 132)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 133;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 133;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 133)
                    {
                        if(rand() % 100 < 10)
                        {
                            switch(rand() % 4)
                            {
                            case 0:
                                if(GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = MelonBlock::getID();
                                }
                            break;
                            case 1:
                                if(GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = MelonBlock::getID();
                                }
                            break;
                            case 2:
                                if(GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = MelonBlock::getID();
                                }
                            break;
                            case 3:
                                if(GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = MelonBlock::getID();
                                }
                            break;
                            }
                        }
                    }

                    // wheat
                    if(GetBlock(x,y,z) == 134)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 135 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 136 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                GetBlock(x,y-1,z) = 79;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 77)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 77;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 78)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 78;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 79 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 8 == 1)
                        {
                            GetBlock(x,y,z) = 2;
                            continue;
                        }
                    }
                    if(GetBlock(x,y,z) == 80 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 12 == 1)
                        {
                            GetBlock(x,y,z) = 79;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 33 && GetBlock(x,y+1,z) == 0 && GetBlock(x,y-3,z) != 33 && GetBlock(x,y-3,z) != 0)
                    {
                        if(rand() % 4 == 1)
                        {
                            GetBlock(x,y+1,z) = 33;
                            continue;
                        }
                    }

                    /// oak tree growing
                    if(GetBlock(x,y,z) == 121 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2))
                    {
                        if((rand() % 14 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 32 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 1 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 9;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 9;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 9;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 8;
                            }
                        }
                    }


                    /// birch tree growing
                    if(GetBlock(x,y,z) == 123 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2))
                    {
                        if((rand() % 13 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 40 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 2 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 38;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 38;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 38;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 31;
                            }
                        }
                    }


                    /// spruce tree growing
                    if(GetBlock(x,y,z) == 122 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2 || GetBlock(x,y-1,z) == 29))
                    {
                        if((rand() % 22 < 2 && (GetBlock(x,y-1,z) == 1 || GetBlock(x,y-1,z) == 2)) || (rand() % 14 < 2 && GetBlock(x,y-1,z) == 29))
                        {
                            mainStatistics.treesGrowned += 1;

                            y = groundHeight(x,z);
                            char TrunkHeight = 6;
                            char type;

                            //check if there is an water on there or another tree
                            bool flag = 1;

                            for (int y1 = y+1; y1 <= y + TrunkHeight ; y1++)
                            {
                                if(GetBlock(x, y1, z) != 0)
                                {
                                    flag = 0;
                                    break;
                                }
                            }

                            if(flag == 0)continue;

                            if(rand() % 7 == 1)
                            {
                                type = 1;
                                TrunkHeight = 6 + rand() % 3;
                            }
                            else
                            {
                                type = 0;
                            }

                            //Create the tree trunk
                            for (int y1 = y; y1 <= y + TrunkHeight ; y1++)
                            {
                                block_t& Block = GetBlock(x, y1, z);
                                Block = 30;
                            }

                            if(type == 0)
                            {
                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    for(int zz = -2; zz <= 2; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 1;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -2; xx <= 2; xx++)
                                {
                                    for(int zz = -1; zz <= 1; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 1;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    for(int zz = -2; zz <= 2; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 3;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -2; xx <= 2; xx++)
                                {
                                    for(int zz = -1; zz <= 1; zz++)
                                    {
                                        int x1 = xx + x;
                                        int y1 = y + 3;
                                        int z1 = zz + z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                    }
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;
                                        int y1 = y + 2;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }


                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;
                                    int y1 = y + 2;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;
                                        int y1 = y + 4;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }


                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + 4;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                    int x1 = xx + x;// :D - what a shitty code
                                    int y1 = y + 6;
                                    int z1 = z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + 6;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                block_t& Block = GetBlock(x, y+7, z);
                                if (Block == 0) Block = 37;
                            }
                            else // type == 1
                            {
                                block_t& Block = GetBlock(x, y+TrunkHeight+1, z);
                                if (Block == 0) Block = 37;

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;// :D - what a shitty code
                                        int y1 = y + TrunkHeight;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;
                                    int y1 = y + TrunkHeight;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }

                                for(int xx = -1; xx <= 1; xx++)
                                {
                                        int x1 = xx + x;// :D - what a shitty code
                                        int y1 = y + TrunkHeight-1;
                                        int z1 = z;

                                        block_t& Block = GetBlock(x1, y1, z1);
                                        if (Block == 0) Block = 37;
                                }

                                for(int zz = -1; zz <= 1; zz++)
                                {
                                    int x1 = x;// :D - what a shitty code
                                    int y1 = y + TrunkHeight-1;
                                    int z1 = zz + z;

                                    block_t& Block = GetBlock(x1, y1, z1);
                                    if (Block == 0) Block = 37;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CraftWorld::SetAllChunksToUpdate()
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i]->needUpdate = true;
    }

    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        mTransparentChunks[i]->needUpdate = true;
    }
}

void CraftWorld::drawCubes(int i, float light)
{
    DrawPlaceTexture(true);
    if(blockTypes[i].transparent)
    {
        DrawSetBlend(true);
    }

    sceGuColor(GU_COLOR(light*0.56,light*0.56,light*0.56,1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, blockTypes[i].pointsLeftRight, 0, blockTypes[i].verticesLeftRight);

    sceGuColor(GU_COLOR(light*0.76,light*0.76,light*0.76,1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, blockTypes[i].pointsBackFront, 0, blockTypes[i].verticesBackFront);

    sceGuColor(GU_COLOR(light,light,light,1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, blockTypes[i].pointsBottomTop, 0, blockTypes[i].verticesBottomTop);

    if(blockTypes[i].transparent)
    {
        DrawSetBlend(false);
    }
    DrawPlaceTexture(false);
}


void CraftWorld::drawHand()
{
    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 36, 0, handVertices);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}



void CraftWorld::drawClouds()
{
    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 600, 0, blockTypes[141].verticesBottomTop);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}

void CraftWorld::drawHandItems(int i, float light)
{
    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGuColor(GU_COLOR(light*0.8,light*0.8,light*0.8,1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, itemTypes[i-250].addPoints, 0, itemTypes[i-250].addVertices);
    sceGuColor(GU_COLOR(light,light,light,1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, itemTypes[i-250].points, 0, itemTypes[i-250].vertices);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}

void CraftWorld::drawItems(int i)
{
    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, itemTypes[i-250].points, 0, itemTypes[i-250].vertices);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}

void CraftWorld::drawDropItems(int i)
{
    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, itemTypes[i-250].points, 0, itemTypes[i-250].dropVertices);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}

void CraftWorld::drawArmor(int i, float light)
{
    if(i >= 328 && i <= 331) // leather
    {
        TextureManager::Instance()->SetTextureModeulate(textureLeatherArmor1Id);
        if(i == 330)
        {
            TextureManager::Instance()->SetTextureModeulate(textureLeatherArmor2Id);
        }
    }

    if(i >= 332 && i <= 335) // chain
    {
        TextureManager::Instance()->SetTextureModeulate(textureChainArmor1Id);
        if(i == 334)
        {
            TextureManager::Instance()->SetTextureModeulate(textureChainArmor2Id);
        }
    }

    if(i >= 336 && i <= 339) // iron
    {
        TextureManager::Instance()->SetTextureModeulate(textureIronArmor1Id);
        if(i == 338)
        {
            TextureManager::Instance()->SetTextureModeulate(textureIronArmor2Id);
        }
    }

    if(i >= 340 && i <= 343) // diamond
    {
        TextureManager::Instance()->SetTextureModeulate(textureDiamondArmor1Id);
        if(i == 342)
        {
            TextureManager::Instance()->SetTextureModeulate(textureDiamondArmor2Id);
        }
    }

    if(i >= 344 && i <= 347) // diamond
    {
        TextureManager::Instance()->SetTextureModeulate(textureGoldenArmor1Id);
        if(i == 346)
        {
            TextureManager::Instance()->SetTextureModeulate(textureGoldenArmor2Id);
        }
    }

    float points = 0;

    DrawSetBlend(true);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuEnable(GU_ALPHA_TEST);

    sceGuColor(GU_COLOR(light,light,light,1));
    switch(itemTypes[i-250].itemType)
    {
    case 'H':
        points = 30;
        sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, points, 0, helmetVertices);
    break;
    case 'C':
        points = 24;
        sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, points, 0, chestplateVertices);
    break;
    case 'L':
        points = 24;
        sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, points, 0, leggingVertices);
    break;
    case 'B':
        points = 30;
        sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, points, 0, bootVertices);
    break;
    }

    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_DEPTH_TEST);
    DrawSetBlend(false);
}


void CraftWorld::drawShoulder(int chestplateId, float light)
{
    if(chestplateId >= 328 && chestplateId <= 331) // leather
    {
        TextureManager::Instance()->SetTextureModeulate(textureLeatherArmor1Id);
    }

    if(chestplateId >= 332 && chestplateId <= 335) // chain
    {
        TextureManager::Instance()->SetTextureModeulate(textureChainArmor1Id);
    }

    if(chestplateId >= 336 && chestplateId <= 339) // iron
    {
        TextureManager::Instance()->SetTextureModeulate(textureIronArmor1Id);
    }

    if(chestplateId >= 340 && chestplateId <= 343) // diamond
    {
        TextureManager::Instance()->SetTextureModeulate(textureDiamondArmor1Id);
    }

    if(chestplateId >= 344 && chestplateId <= 347) // diamond
    {
        TextureManager::Instance()->SetTextureModeulate(textureGoldenArmor1Id);
    }

    float points = 0;

    DrawSetBlend(true);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuEnable(GU_ALPHA_TEST);

    sceGuColor(GU_COLOR(light,light,light,1));
    switch(itemTypes[chestplateId-250].itemType)
    {
    case 'C':
        points = 30;
        sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, points, 0, shoulderVertices);
    break;
    }

    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_DEPTH_TEST);
    DrawSetBlend(false);
}

void CraftWorld::drawWorld(Frustum &camFrustum,bool camUpdate)
{
  //  DrawSetCulling(true);
    drawnTriangles = 0;
    //normal not transparent chunks
    sceGuColor(0xFFFFFFFF);
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        if(mChunks[i]->trienglesCount > 0 || !mChunks[i]->created)
        {
            if(playerZoneBB.intersect(mChunks[i]->bBox))
            {
                if((!mChunks[i]->created || mChunks[i]->needUpdate) && chunksCreatedInFrameCount == 0)
                {
                    rebuildChunk(i);
                    chunksCreatedInFrameCount++;
                }
                if(camFrustum.BoxInFrustum(mChunks[i]->bBox) == Frustum::Intersects)
                {
                    //check if wee need to build vertices of this chunk

                    mChunks[i]->drawChunk();
                    drawnTriangles += mChunks[i]->trienglesCount;
                }
            }
            else if(mChunks[i]->created)
            {
                mChunks[i]->reset();
            }
        }
    }

    //transparent chunks
    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        if(mTransparentChunks[i]->trienglesCount > 0 || !mTransparentChunks[i]->created)
        {
            if(playerZoneBB.intersect(mTransparentChunks[i]->bBox))
            {
                //check if wee need to build vertices of this chunk
                if((!mTransparentChunks[i]->created || mTransparentChunks[i]->needUpdate) && transparentchunksCreatedInFrameCount == 0)
                {
                    rebuildTransparentChunk(i);
                    transparentchunksCreatedInFrameCount++;
                }
                if(camFrustum.BoxInFrustum(mTransparentChunks[i]->bBox) == Frustum::Intersects)
                {
                    sceGuEnable(GU_DEPTH_TEST);
                    sceGuEnable(GU_ALPHA_TEST);
                    sceGuEnable(GU_BLEND);

                    mTransparentChunks[i]->drawChunk();
                    drawnTriangles += mTransparentChunks[i]->trienglesCount;

                    sceGuDisable(GU_BLEND);
                    sceGuDisable(GU_ALPHA_TEST);
                    sceGuDisable(GU_DEPTH_TEST);
                }
            }
            else if(mTransparentChunks[i]->created)
            {
                mTransparentChunks[i]->reset();
            }
        }
    }
}

void CraftWorld::UpdatePlayerZoneBB(Vector3 playerPosition)
{
    playerPos = playerPosition;
    playerZoneBB = BoundingBox(Vector3(playerPosition.x - playerZoneSize.x,playerPosition.y - playerZoneSize.y,playerPosition.z - playerZoneSize.z),Vector3(playerPosition.x + playerZoneSize.x,playerPosition.y + playerZoneSize.y,playerPosition.z + playerZoneSize.z));
}

Vector3 CraftWorld::GetPlayerPos()
{
    return playerPos;
}

void CraftWorld::UpdateWorldAnimation(float dt)
{
    if(mainOptions.worldBlockAnimation == true)
    {
        animationTimer += dt;

        if(animationTimer >= animationTimerEnd) // every 0.075 secs
        {
            int waterFrameSize = TextureManager::Instance()->getWidth(textureWaterAnimationId);

            animationTimer = 0.0f; // zeroize timer

            animationWaterFrame += 1; // go to the next water frame
            if(animationWaterFrame >= TextureManager::Instance()->getHeight(textureWaterAnimationId)/TextureManager::Instance()->getWidth(textureWaterAnimationId)) // if all frames passed
            {
                animationWaterFrame = 0; // zeroize frames
            }

            for(int i = 0; i < waterFrameSize; i++)
            {
                for(int j = 0; j < waterFrameSize; j++)
                {
                    // copy each water pixel from water_still.png to terrain.png
                    TextureManager::Instance()->setColour(waterFrameSize*14+i,
                                                          waterFrameSize*15+j,
                                                          TextureManager::Instance()->getRed(i,animationWaterFrame*waterFrameSize+j,textureWaterAnimationId),
                                                          TextureManager::Instance()->getGreen(i,animationWaterFrame*waterFrameSize+j,textureWaterAnimationId),
                                                          TextureManager::Instance()->getBlue(i,animationWaterFrame*waterFrameSize+j,textureWaterAnimationId),
                                                          180,
                                                          textureTerrainId);
                }
            }

            int lavaFrameSize = TextureManager::Instance()->getWidth(textureLavaAnimationId);

            if(animationLavaFrame >= TextureManager::Instance()->getHeight(textureLavaAnimationId)/TextureManager::Instance()->getWidth(textureLavaAnimationId)-1)
            {
                animationLavaStep = false;
            }
            if(animationLavaFrame == 0)
            {
                animationLavaStep = true;
            }

            if(animationLavaStep == true)
            {
                animationLavaFrame += 1;
            }
            else
            {
                animationLavaFrame -= 1;
            }

            for(int i = 0; i < lavaFrameSize; i++)
            {
                for(int j = 0; j < lavaFrameSize; j++)
                {
                    TextureManager::Instance()->setColour(lavaFrameSize*15+i,
                                                          lavaFrameSize*15+j,
                                                          TextureManager::Instance()->getRed(i,animationLavaFrame*lavaFrameSize+j,textureLavaAnimationId),
                                                          TextureManager::Instance()->getGreen(i,animationLavaFrame*lavaFrameSize+j,textureLavaAnimationId),
                                                          TextureManager::Instance()->getBlue(i,animationLavaFrame*lavaFrameSize+j,textureLavaAnimationId),
                                                          180,
                                                          textureTerrainId);
                }
            }
        }
    }
}

void CraftWorld::UpdateWorldTime(float dt)
{
    UpdateWorldAnimation(dt);
    //stuff that goes on tick
    //1 tick = 1 second

    timee += dt;
    if(timee > 60.0f)
    {
        mainStatistics.minutesPlayed += 1;
        timee = 0;
    }

    spawnMobsTimer += dt;
    if(spawnMobsTimer > 15.0f)
    {
        if(worldDayTime > 21 || worldDayTime < 6)
        {
            if(mZombies.empty() == false)
            {
                if(rand() % 2 == 1 && mZombies.size() < 10)
                {
                    float spawnX = 0;
                    float spawnY = 0;
                    float spawnZ = 0;

                    rand() % 2 == 0 ? spawnX = playerPos.x-5-rand() % 20 : spawnX = playerPos.x+5+rand() % 20;
                    rand() % 2 == 0 ? spawnZ = playerPos.z-5-rand() % 20 : spawnZ = playerPos.z+5+rand() % 20;

                    spawnY = groundHeightWater(spawnX,spawnZ);

                    if(BlockFinalLight(spawnX,spawnY,spawnZ) < 0.25f) // spawn only at black areas
                    {
                        if(spawnY != -1 && spawnY < WORLD_HEIGHT && spawnX < WORLD_SIZE && spawnZ < WORLD_SIZE && spawnY > 0 && spawnX > 0 && spawnZ > 0)
                        {
                            SpawnZombie(spawnX,spawnY+1.8f,spawnZ);
                            SpawnZombie(spawnX+2.0f,groundHeightWater(spawnX+2.0f,spawnZ+2.0f)+1.8f,spawnZ+2.0f);
                        }
                    }
                }
            }
            else
            {
                float spawnX = 0;
                float spawnY = 0;
                float spawnZ = 0;

                rand() % 2 == 0 ? spawnX = playerPos.x-5-rand() % 20 : spawnX = playerPos.x+5+rand() % 20;
                rand() % 2 == 0 ? spawnZ = playerPos.z-5-rand() % 20 : spawnZ = playerPos.z+5+rand() % 20;

                spawnY = groundHeightWater(spawnX,spawnZ);

                if(BlockFinalLight(spawnX,spawnY,spawnZ) < 0.25f) // spawn only at black areas
                {
                    if(spawnY != -1 && spawnY < WORLD_HEIGHT && spawnX < WORLD_SIZE && spawnZ < WORLD_SIZE && spawnY > 0 && spawnX > 0 && spawnZ > 0)
                    {
                        SpawnZombie(spawnX,spawnY+1.8f,spawnZ);
                        SpawnZombie(spawnX+2.0f,groundHeightWater(spawnX+2.0f,spawnZ+2.0f)+1.8f,spawnZ+2.0f);
                    }
                }
            }
        }
        if(worldDayTime > 6 && worldDayTime < 21)
        {
            if(mCows.empty() == false)
            {
                if(rand() % 5 == 1 && mCows.size() < 8)
                {
                    float spawnX = 0;
                    float spawnY = 0;
                    float spawnZ = 0;

                    spawnX = 10 + rand() % 150;
                    spawnZ = 10 + rand() % 150;
                    spawnY = groundHeightWater(spawnX,spawnZ);

                    if(spawnY != -1 && spawnY < WORLD_HEIGHT && spawnX < WORLD_SIZE && spawnZ < WORLD_SIZE && spawnY > 0 && spawnX > 0 && spawnZ > 0)
                    {
                        SpawnCow(spawnX,spawnY+2.0f,spawnZ);
                        SpawnCow(spawnX+2.0f,groundHeightWater(spawnX+2.0f,spawnZ+2.0f)+2.0f,spawnZ+2.0f);
                    }
                }
            }
            else
            {
                float spawnX = 0;
                float spawnY = 0;
                float spawnZ = 0;

                spawnX = 10 + rand() % 150;
                spawnZ = 10 + rand() % 150;
                spawnY = groundHeightWater(spawnX,spawnZ);

                if(spawnY != -1 && spawnY < WORLD_HEIGHT && spawnX < WORLD_SIZE && spawnZ < WORLD_SIZE && spawnY > 0 && spawnX > 0 && spawnZ > 0)
                {
                    SpawnCow(spawnX,spawnY+2.0f,spawnZ);
                    SpawnCow(spawnX+2,groundHeightWater(spawnX+2,spawnZ+2)+2.0f,spawnZ+2);
                }
            }
        }
        spawnMobsTimer = 0.0f;
    }

    if(updatingChunks.empty() == false)
    {
        updatingChunksTimer += dt;
        updatingChunksTimerMax = 30.0f/updatingChunks.size();
        if(updatingChunksTimer > updatingChunksTimerMax)
        {
            UpdateChunkGrowingBlocks(updatingChunks[updatingChunksPosition]);
            rebuildChunk(updatingChunks[updatingChunksPosition]);

            updatingChunksPosition += 1;
            if(updatingChunksPosition >= updatingChunks.size())
            {
                updatingChunksPosition = 0;
            }
            updatingChunksTimer = 0.0f;
        }
    }

    worldTime += dt;
    updateChunkTimer += dt;
    if(updateChunkTimer > 0.2f)//update time 1/5 second
    {
        chunksCreatedInFrameCount = 0;
        transparentchunksCreatedInFrameCount = 0;
        animatedchunksCreatedInFrameCount = 0;
        updateChunkTimer = 0.0f;

        if(toUpdate.empty() == false)
        {
            rebuildChunk(toUpdate[0]);
            rebuildTransparentChunk(toUpdate[0]);

            toUpdate.erase(toUpdate.begin()+0);
        }
    }

    if(worldTime >= 0.1f)
    {
        if(worldDayTime >= 22 || worldDayTime < 6)
        {
            skyTime += 180.0f/8.0f/50.0f/10.0f;
        }
        if(worldDayTime >= 6 && worldDayTime < 22)
        {
            skyTime += 180.0f/16.0f/50.0f/10.0f;
        }
        worldTime = 0.0f;
    }

    //world day/night time
    worldHour += dt;

    if(worldHour >= 50.0f)//one game hour = 50 sec
    {
        worldHour = 0.0f;
        worldDayTime += 1.0f;
        if(worldDayTime > 23.0f)
        {
            worldDayTime = 0.0f;
            mainStatistics.daysInGame += 1;
        }
        SetWolrdTime(worldDayTime);
        SetAllChunksToUpdate();
    }
}

int CraftWorld::GetBlockTypesCount()
{
    return blockTypes.size();
}

int CraftWorld::GetItemTypesCount()
{
    return itemTypes.size();
}

int CraftWorld::groundHeight(const int x, const int z)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;

    for (int y = WORLD_HEIGHT - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if (Block != 0 && Block != 4)
        {
            return y;
        }
    }

    return -1;
}

int CraftWorld::groundHeightExcept(const int x, const int z, int bl)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;


    for (int y = WORLD_HEIGHT - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if(Block == bl)
        {
            continue;
        }
        if (Block != 0) return (y);
    }

    return -1;
}

int CraftWorld::groundHeightWater(const int x, const int z)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;

    for (int y = WORLD_HEIGHT - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if (Block != 0)
        {
            return y;
        }
    }

    return -1;
}

int CraftWorld::getChunkId(Vector3 pos)
{
    int id = floorf(pos.x/16) + floorf(pos.y/16) * (WORLD_SIZE/16) + floorf(pos.z/16) * (WORLD_SIZE/16) * (WORLD_HEIGHT/16);
    return id;
}

bool CraftWorld::SolidAtPoint(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return true;

    //don't collide with water and air
    if(BlockSolid(x,y,z) == 0)
    {
        //
        return false;
    }

    //collision
    return true;
}

int CraftWorld::BlockSoundAtPos(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return -1;

    return blockTypes[GetBlock(x,y,z)].soundType;
}

bool CraftWorld::SolidAtPointForPlayer(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return true;

    //don't collide with water and air
    if(BlockSolid(x,y,z) == 0)
    {
        //4 corners
        if(SolidAtPoint(Vector3(pos.x-0.15f,pos.y,pos.z-0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x+0.15f,pos.y,pos.z+0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x+0.15f,pos.y,pos.z-0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x-0.15f,pos.y,pos.z+0.15f))) return true;
        //
        return false;
    }

    //collision
    return true;
}

bool CraftWorld::SolidAtPointForEntity(Vector3 pos, Vector3 collider1)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    float xSize = collider1.x;
    float zSize = collider1.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return true;

    //don't collide with water and air
    if(BlockSolid(x,y,z) == 0)
    {
        //4 corners
        if(SolidAtPoint(Vector3(pos.x-xSize,pos.y,pos.z-zSize))) return true;
        if(SolidAtPoint(Vector3(pos.x+xSize,pos.y,pos.z+zSize))) return true;
        if(SolidAtPoint(Vector3(pos.x+xSize,pos.y,pos.z-zSize))) return true;
        if(SolidAtPoint(Vector3(pos.x-xSize,pos.y,pos.z+zSize))) return true;
        //
        return false;
    }

    //collision
    return true;
}

bool CraftWorld::PlayerInWater(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) == 4 || GetBlock(x,y,z) == 32)
        return true;

    return false;
}

bool CraftWorld::PlayerInLava(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) == Lava::getID())
        return true;

    return false;
}

bool CraftWorld::PlayerInBlock(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_HEIGHT-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) != Lava::getID() || GetBlock(x,y,z) != 4 || GetBlock(x,y,z) != 0)
        return true;

    return false;
}

block_t CraftWorld::BlockAtPoint(Vector3 pos)
{


    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE || y >= WORLD_HEIGHT || z >= WORLD_SIZE) return -1;

    return GetBlock(x,y,z);

}


void CraftWorld::BuildBlockSphere(int radius, block_t block, int X, int Y, int Z)
{
    float reference = 125 / 20.0f;

    int latitudes = (int)(radius * reference);
    int longitudes = (int)(latitudes/2);

    float latitude_increment = PI*2 / latitudes;
    float longitude_increment = PI / longitudes;

    for (float u = 0; u < PI*2; u += latitude_increment)
    {
        for (float t = 0; t < PI; t += longitude_increment)
        {

            float rad = radius;

            int x = X + (rad * sinf(t) * sinf(u));
            int y = Y + (rad * cosf(t));
            int z = Z + (rad * sinf(t) * cosf(u));

            if(x > X)
            {
                for(int x2 = x; x2 >= X - (x2-X); x2 --)
                {
                    GetBlock(x2,y,z) = block;
                }
            }

            if(x < X)
            {
                for(int x2 = x; x2 <= X + (X-x2); x2 ++)
                {
                    GetBlock(x2,y,z) = block;
                }
            }
        }
    }
}

void CraftWorld::BuildBlockSphere(int radius, block_t block, int X, int Y, int Z, block_t blockToChange)
{
    float reference = 125 / 20.0f;

    int latitudes = (int)(radius * reference);
    int longitudes = (int)(latitudes/2);

    float latitude_increment = PI*2 / latitudes;
    float longitude_increment = PI / longitudes;

    for (float u = 0; u < PI*2; u += latitude_increment)
    {
        for (float t = 0; t < PI; t += longitude_increment)
        {

            float rad = radius;

            int x = X + (rad * sinf(t) * sinf(u));
            int y = Y + (rad * cosf(t));
            int z = Z + (rad * sinf(t) * cosf(u));

            if(x > X)
            {
                for(int x2 = x; x2 >= X - (x2-X); x2 --)
                {
                    if (GetBlock(x2,y,z) == blockToChange)
                    {
                        GetBlock(x2,y,z) = block;
                    }
                }
            }

            if(x < X)
            {
                for(int x2 = x; x2 <= X + (X-x2); x2 ++)
                {
                    if (GetBlock(x2,y,z) == blockToChange)
                    {
                        GetBlock(x2,y,z) = block;
                    }
                }
            }
        }
    }
}


void CraftWorld::PutInInventory(int id, int num, bool st)
{
    bool ok;
    ok = false;
    for(int j = 27; j <= 35; j++)
    {
        if (invSt[j]==1)
        {
            if (invId[j]== id)
            {
                if(invAm[j] + num <= 64)
                {
                    invAm[j] += num;
                    ok = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (invId[j]== -1)
        {
            invSt[j] = st;
            invId[j] = id;
            invAm[j] = num;
            ok = true;
            break;
        }
    }

    if(ok == false)
    {
        for(int j = 0; j <= 26; j++)
        {
            if (invSt[j]==1)
            {
                if (invId[j]== id)
                {
                    if(invAm[j] + num <= 64)
                    {
                        invAm[j] += num;
                        break;
                        return;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            if (invId[j]== -1)
            {
                invSt[j] = st;
                invId[j] = id;
                invAm[j] = num;
                break;
                return;
            }
        }
    }
}

bool CraftWorld::InventoryIsFull(int id, int num, bool st)
{
    bool ok;
    ok = false;
    for(int j = 27; j <= 35; j++)
    {
        if (invSt[j]==1)
        {
            if (invId[j]== id)
            {
                if(invAm[j] + num <= 64)
                {
                    ok = true;
                    return false;
                }
                else
                {
                    continue;
                }
            }
        }

        if (invId[j]== -1)
        {
            ok = true;
            return false;
            break;

        }
    }

    if(ok == false)
    {
        for(int j = 0; j <= 26; j++)
        {
            if (invSt[j]==1)
            {
                if (invId[j]== id)
                {
                    if(invAm[j] + num <= 64)
                    {
                        return false;
                        break;

                    }
                    else
                    {
                        continue;
                    }
                }
            }

            if (invId[j]== -1)
            {
                return false;
                break;
            }
        }
    }
    return true;
}

int CraftWorld::FindDirId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mDirects.size(); i++)
    {
        DirectionBlock* NewDirectionBlock = mDirects[i];
        if(NewDirectionBlock->X == x && NewDirectionBlock->Y == y && NewDirectionBlock->Z == z)
        {
            o = i;
            break;
        }
    }

    return o;
}

void CraftWorld::rebuildVisibleTransperentChunks()
{
    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        if(playerZoneBB.intersect(mTransparentChunks[i]->bBox))
        {
            rebuildTransparentChunk(i);
        }
    }
}

void CraftWorld::rebuildVisibleChunks()
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        if(playerZoneBB.intersect(mChunks[i]->bBox))
        {
            rebuildChunk(i);
        }
    }
}

inline void CraftWorld::BuildWorldBlockPlaneNoCheck(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4)
{
    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    bool canCreate = false;
    bool DefaultBlock = false;
    bool transparentBlock = false;

    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;

    char Block1 = 0;

    Vector3 light1, light2, light3, light4;
    Block = GetBlock(x,y,z);

    if(side == 1)
    {
        // x y z
        // 0 0 1
        // 0 1 1
        // 0 1 0
        // 0 0 0
        Vector3 BlockColorx1;
        Block1 = GetBlock(x-1,y,z);
        canCreate = true;

        if(canCreate == true)
        {
            BlockColorx1 = Vector3(BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z)) * 0.95f;
            light1 = light2 = light3 = light4 = BlockColorx1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->leftPlane_x + point4.z*texturePixel;
            right = percent*blockType->leftPlane_x+percent - (16-point2.z)*texturePixel;

            up = percent*blockType->leftPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->leftPlane_y + (16-point4.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 2)
    {
        // x y z
        // 1 0 0
        // 1 1 0
        // 1 1 1
        // 1 0 1

        Vector3 BlockColorx2;
        Block1 = GetBlock(x+1,y,z);
        canCreate = true;

        if (canCreate)
        {
            BlockColorx2 = Vector3(BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z)) * 0.95f;
            light1 = light2 = light3 = light4 = BlockColorx2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx2 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->rightPlane_x + point1.z*texturePixel;
            right = percent*blockType->rightPlane_x+percent - (16-point3.z)*texturePixel;

            up = percent*blockType->rightPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->rightPlane_y + (16-point1.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 3)
    {
        // x z y
        // 0 0 0
        // 1 0 0
        // 1 1 0
        // 0 1 0

        Vector3 BlockColory2;
        Block1 = GetBlock(x,y-1,z);
        canCreate = true;

        if (canCreate)
        {
            BlockColory2 = Vector3(BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z)) * 0.6f;
            light1 = light2 = light3 = light4 = BlockColory2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory2 * lightShadowFactor;

                //simple shadows
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
                {
                    light4-=lightFactor;
                }
            }

            left = percent*blockType->downPlane_x + point1.x*texturePixel;
            right = percent*blockType->downPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->downPlane_y + (16-point1.z)*texturePixel;
            down = percent*blockType->downPlane_y + (16-point3.z)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 4)
    {
        // x z y
        // 0 1 1
        // 1 1 1
        // 1 0 1
        // 0 0 1

        Vector3 BlockColory1;
        Block1 = GetBlock(x,y+1,z);
        canCreate = true;

        if(canCreate)
        {

            BlockColory1 = Vector3(BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z));
            light1 = light2 = light3 = light4 = BlockColory1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory1 * lightShadowFactor;
                //simple shadows
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light4-=lightFactor;
                }
            }

            left = percent*blockType->upPlane_x + point4.x*texturePixel;
            right = percent*blockType->upPlane_x+percent - (16-point2.x)*texturePixel;

            up = percent*blockType->upPlane_y + (16-point2.z)*texturePixel;
            down = percent*blockType->upPlane_y + (16-point4.z)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);


            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 5)
    {
        // x y z
        // 0 1 0
        // 1 1 0
        // 1 0 0
        // 0 0 0

        Vector3 BlockColorz1;
        Block1 = GetBlock(x,y,z-1);
        canCreate = true;

        if (canCreate)
        {
            BlockColorz1 = Vector3(BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1)) * 0.75f;
            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->botPlane_x + point4.x*texturePixel;
            right = percent*blockType->botPlane_x+percent - (16-point2.x)*texturePixel;

            up = percent*blockType->botPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->botPlane_y + (16-point4.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 6)
    {
        // x y z
        // 0 0 1
        // 1 0 1
        // 1 1 1
        // 0 1 1

        Vector3 BlockColorz2;
        Block1 = GetBlock(x,y,z+1);
        canCreate = true;


        if (canCreate == true)
        {
            BlockColorz2 = Vector3(BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1)) * 0.75f;
            light1 = light2 = light3 = light4 = BlockColorz2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz2 * lightShadowFactor;

                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->forPlane_x + point1.x*texturePixel;
            right = percent*blockType->forPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->forPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->forPlane_y + (16-point1.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }
}


inline void CraftWorld::BuildWorldBlockPlane(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4)
{
    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    bool canCreate = false;
    bool DefaultBlock = false;
    bool transparentBlock = false;

    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;

    char Block1 = 0;

    Vector3 light1, light2, light3, light4;
    Block = GetBlock(x,y,z);

    if(side == 1)
    {
        // x y z
        // 0 0 1
        // 0 1 1
        // 0 1 0
        // 0 0 0
        Vector3 BlockColorx1;

        Block1 = GetBlock(x-1,y,z);

        if(transparent == true)
        {
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x-1,y,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x-1,y,z) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (x > 0)
            {
                if (BlockSpecial(x-1,y,z) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x-1,y,z) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }


        if(canCreate == true)
        {
            BlockColorx1 = Vector3(BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z)) * 0.95f;
            light1 = light2 = light3 = light4 = BlockColorx1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->leftPlane_x + point4.z*texturePixel;
            right = percent*blockType->leftPlane_x+percent - (16-point2.z)*texturePixel;

            up = percent*blockType->leftPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->leftPlane_y + (16-point4.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 2)
    {
        // x y z
        // 1 0 0
        // 1 1 0
        // 1 1 1
        // 1 0 1

        Vector3 BlockColorx2;

        Block1 = GetBlock(x+1,y,z);

        if(transparent == true)
        {
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x+1,y,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x+1,y,z) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (x < WORLD_SIZE - 1)
            {
                if (BlockSpecial(x+1,y,z) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x+1,y,z) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (canCreate)
        {
            BlockColorx2 = Vector3(BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z)) * 0.95f;
            light1 = light2 = light3 = light4 = BlockColorx2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx2 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->rightPlane_x + point1.z*texturePixel;
            right = percent*blockType->rightPlane_x+percent - (16-point3.z)*texturePixel;

            up = percent*blockType->rightPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->rightPlane_y + (16-point1.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 3)
    {
        // x z y
        // 0 0 0
        // 1 0 0
        // 1 1 0
        // 0 1 0

        Vector3 BlockColory2;

        Block1 = GetBlock(x,y-1,z);

        if(transparent == true)
        {
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-1,z);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y-1,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x,y-1,z) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (y > 0)
            {
                if (BlockSpecial(x,y-1,z) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x,y-1,z) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if(Block == 25 && Block1 == 25)
        {
            canCreate = false;
        }

        if (canCreate)
        {
            BlockColory2 = Vector3(BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z)) * 0.6f;
            light1 = light2 = light3 = light4 = BlockColory2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory2 * lightShadowFactor;

                //simple shadows
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
                {
                    light4-=lightFactor;
                }
            }

            left = percent*blockType->downPlane_x + point1.x*texturePixel;
            right = percent*blockType->downPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->downPlane_y + (16-point1.z)*texturePixel;
            down = percent*blockType->downPlane_y + (16-point3.z)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 4)
    {
        // x z y
        // 0 1 1
        // 1 1 1
        // 1 0 1
        // 0 0 1

        Vector3 BlockColory1;

        Block1 = GetBlock(x,y+1,z);

        if(transparent == true)
        {
            if (y < WORLD_HEIGHT - 1)
            {
                transparentBlock = BlockTransparent(x,y+1,z);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y+1,z) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x,y+1,z) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (y < WORLD_HEIGHT - 1)
            {
                if (BlockSpecial(x,y+1,z) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x,y+1,z) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if(Block1 == 93)
        {
            canCreate = false;
        }

        if(Block == 25 && Block1 == 25)
        {
            canCreate = false;
        }

        if(canCreate)
        {

            BlockColory1 = Vector3(BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z));
            light1 = light2 = light3 = light4 = BlockColory1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory1 * lightShadowFactor;
                //simple shadows
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light4-=lightFactor;
                }
            }

            left = percent*blockType->upPlane_x + point4.x*texturePixel;
            right = percent*blockType->upPlane_x+percent - (16-point2.x)*texturePixel;

            up = percent*blockType->upPlane_y + (16-point2.z)*texturePixel;
            down = percent*blockType->upPlane_y + (16-point4.z)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);


            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 5)
    {
        // x y z
        // 0 1 0
        // 1 1 0
        // 1 0 0
        // 0 0 0

        Vector3 BlockColorz1;

        Block1 = GetBlock(x,y,z-1);

        if(transparent == true)
        {
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z-1) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x,y,z-1) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (z > 0)
            {
                if (BlockSpecial(x,y,z-1) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x,y,z-1) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (canCreate)
        {
            BlockColorz1 = Vector3(BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1)) * 0.75f;
            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->botPlane_x + point4.x*texturePixel;
            right = percent*blockType->botPlane_x+percent - (16-point2.x)*texturePixel;

            up = percent*blockType->botPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->botPlane_y + (16-point4.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 6)
    {
        // x y z
        // 0 0 1
        // 1 0 1
        // 1 1 1
        // 0 1 1

        Vector3 BlockColorz2;

        Block1 = GetBlock(x,y,z+1);

        if(transparent == true)
        {
            if (z < WORLD_SIZE-1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);

                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z+1) > 0 && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38 && Block1 != 37))
                {
                    canCreate = true;
                }
                if (transparentBlock == false && BlockSpecial(x,y,z+1) == 0)
                {
                    canCreate = false;
                }
            }
        }
        else
        {
            if (z < WORLD_SIZE-1)
            {
                if (BlockSpecial(x,y,z+1) > 0 && Block1 != Block)
                {
                    canCreate = true;
                }
                if (BlockTransparent(x,y,z+1) == true || Block1 == 0)
                {
                    canCreate = true;
                }
            }
        }

        if((Block1 == 9 || Block1 == 37 || Block1 == 38) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }


        if (canCreate == true)
        {
            BlockColorz2 = Vector3(BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1)) * 0.75f;
            light1 = light2 = light3 = light4 = BlockColorz2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz2 * lightShadowFactor;

                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->forPlane_x + point1.x*texturePixel;
            right = percent*blockType->forPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->forPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->forPlane_y + (16-point1.y)*texturePixel;

            if((Block == 9 || Block == 37 || Block == 38) && mainOptions.fastRendering == true)
            {
                left += percent;
                right += percent;
            }

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }
}


inline void CraftWorld::BuildWorldBlockPlane(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, bool alwaysBuild, bool constantColor)
{
    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    bool canCreate = false;
    bool DefaultBlock = false;
    bool transparentBlock = false;

    float up = 0.0f;
    float down = 0.0f;
    float left = 0.0f;
    float right = 0.0f;

    char Block1;

    Vector3 light1, light2, light3, light4;

    if(side == 1)
    {
        // x y z
        // 0 0 1
        // 0 1 1
        // 0 1 0
        // 0 0 0
        Block1 = GetBlock(x-1,y,z);

        Vector3 BlockColorx1;

        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x-1,y,z) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                    canCreate = true;
            }
        }
        else
        {
            if (x > 0)
            {
                Block1 = GetBlock(x-1,y,z);
                transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
                if (transparentBlock == true)
                    canCreate = true;
            }
        }

        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if (canCreate)
        {
            if(constantColor == true)
            {
                BlockColorx1 = Vector3(BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z));
            }
            else
            {
                BlockColorx1 = Vector3(BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z),BlockFinalLight(x-1,y,z)) * 0.95f;
            }
            light1 = light2 = light3 = light4 = BlockColorx1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->leftPlane_x + point4.z*texturePixel;
            right = percent*blockType->leftPlane_x+percent - (16-point2.z)*texturePixel;

            up = percent*blockType->leftPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->leftPlane_y + (16-point4.y)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 2)
    {
        // x y z
        // 1 0 0
        // 1 1 0
        // 1 1 1
        // 1 0 1

        Vector3 BlockColorx2;

        Block1 = GetBlock(x+1,y,z);

        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x+1,y,z) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                    canCreate = true;
            }
        }
        else
        {
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
                if (transparentBlock == true)
                    canCreate = true;
            }
        }
        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if (canCreate)
        {
            if(constantColor == true)
            {
                BlockColorx2 = Vector3(BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z));
            }
            else
            {
                BlockColorx2 = Vector3(BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z),BlockFinalLight(x+1,y,z)) * 0.95f;
            }
            light1 = light2 = light3 = light4 = BlockColorx2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx2 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->rightPlane_x + point1.z*texturePixel;
            right = percent*blockType->rightPlane_x+percent - (16-point3.z)*texturePixel;

            up = percent*blockType->rightPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->rightPlane_y + (16-point1.y)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 3)
    {
        // x z y
        // 0 0 0
        // 1 0 0
        // 1 1 0
        // 0 1 0

        Vector3 BlockColory2;

        Block1 = GetBlock(x,y-1,z);

        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-1,z);
                Block1 = GetBlock(x,y-1,z);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y-1,z) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                    canCreate = true;
            }
        }
        else
        {
            if (y > 0)
            {
                Block1 = GetBlock(x,y-1,z);
                transparentBlock = BlockTransparentOrSpecial(x,y-1,z);
                if (transparentBlock == true)
                    canCreate = true;
            }
            else
            {
                canCreate = false;
            }
        }
        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if (canCreate)
        {
            if(constantColor == true)
            {
                BlockColory2 = Vector3(BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z));
            }
            else
            {
                BlockColory2 = Vector3(BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z),BlockFinalLight(x,y-1,z)) * 0.6f;
            }
            light1 = light2 = light3 = light4 = BlockColory2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory2 * lightShadowFactor;

                //simple shadows
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
                {
                    light4-=lightFactor;
                }
            }

            left = percent*blockType->downPlane_x + point1.x*texturePixel;
            right = percent*blockType->downPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->downPlane_y + (16-point1.z)*texturePixel;
            down = percent*blockType->downPlane_y + (16-point3.z)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 4)
    {
        // x z y
        // 0 1 1
        // 1 1 1
        // 1 0 1
        // 0 0 1

        Vector3 BlockColory1;

        Block1 = GetBlock(x,y+1,z);

        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_HEIGHT - 1)
            {
                transparentBlock = BlockTransparent(x,y+1,z);
                Block1 = GetBlock(x,y+1,z);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y+1,z) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                {
                    canCreate = true;
                }
            }
        }
        else
        {
            if (y < WORLD_HEIGHT - 1)
            {
                Block1 = GetBlock(x,y+1,z);
                if (BlockTransparentOrSpecial(x,y+1,z) == true && GetBlock(x,y+1,z) != 93)
                {
                    canCreate = true;
                }
            }
        }
        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if(canCreate)
        {
            BlockColory1 = Vector3(BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z),BlockFinalLight(x,y+1,z));
            light1 = light2 = light3 = light4 = BlockColory1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory1 * lightShadowFactor;
                //simple shadows
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light4-=lightFactor;
                }
            }
            //BuildWorldBlockPlane(blockType,x,y,z,iVertex,MeshChunk,Block,transparent,"top",Vector3(6,16,10),Vector3(10,16,10),Vector3(10,16,6),Vector3(6,16,6));
            left = percent*blockType->upPlane_x + point4.x*texturePixel;
            right = percent*blockType->upPlane_x + percent - ((16-point2.x)*texturePixel);

            up = percent*blockType->upPlane_y + (16-point2.z)*texturePixel;
            down = percent*blockType->upPlane_y + (16-point4.z)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);


            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 5)
    {
        // x y z
        // 0 1 0
        // 1 1 0
        // 1 0 0
        // 0 0 0

        Vector3 BlockColorz1;

        Block1 = GetBlock(x,y,z-1);

        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z-1) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                    canCreate = true;
            }
        }
        else
        {
            if (z > 0)
            {
                Block1 = GetBlock(x,y,z-1);
                transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
                if (transparentBlock == true)
                    canCreate = true;
            }
        }
        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if (canCreate)
        {
            if(constantColor == true)
            {
                BlockColorz1 = Vector3(BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1));
            }
            else
            {
                BlockColorz1 = Vector3(BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1),BlockFinalLight(x,y,z-1)) * 0.75f;
            }
            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->botPlane_x + point4.x*texturePixel;
            right = percent*blockType->botPlane_x+percent - (16-point2.x)*texturePixel;

            up = percent*blockType->botPlane_y + (16-point2.y)*texturePixel;
            down = percent*blockType->botPlane_y + (16-point4.y)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(side == 6)
    {
        // x y z
        // 0 0 1
        // 1 0 1
        // 1 1 1
        // 0 1 1

        Vector3 BlockColorz2;

        Block1 = GetBlock(x,y,z+1);

        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
                if ((transparentBlock == true && Block1 != Block) || Block1 == 0 || (BlockSpecial(x,y,z+1) && Block1 != 9 && Block1 != 4 && Block1 != 112 && Block1 != 38))
                    canCreate = true;
            }
        }
        else
        {
            if (z < WORLD_SIZE - 1)
            {
                Block1 = GetBlock(x,y,z+1);
                transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
                if (transparentBlock == true)
                    canCreate = true;
            }
            else
            {
                canCreate = false;
            }
        }
        if((Block1 == 38 || Block1 == 9) && mainOptions.fastRendering == 1)
        {
            canCreate = false;
        }

        if (alwaysBuild == true)
        {
            canCreate = true;
        }

        if (canCreate == true)
        {
            if(constantColor == true)
            {
                BlockColorz2 = Vector3(BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1));
            }
            else
            {
                BlockColorz2 = Vector3(BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1),BlockFinalLight(x,y,z+1)) * 0.75f;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz2 * lightShadowFactor;

                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light3-=lightFactor;
                }
            }

            left = percent*blockType->forPlane_x + point1.x*texturePixel;
            right = percent*blockType->forPlane_x+percent - (16-point3.x)*texturePixel;

            up = percent*blockType->forPlane_y + (16-point3.y)*texturePixel;
            down = percent*blockType->forPlane_y + (16-point1.y)*texturePixel;

            MeshChunk->position(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }
}


inline void CraftWorld::BuildGUIBlockPlane(BaseBlock* blockType, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4)
{
    float pixel, texturePixel;

    pixel = (float)1/16.0f;
    texturePixel = (float)1/256.0f;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;

    float down = 0.0f;
    float up = 0.0f;

    float left = 0.0f;
    float right = 0.0f;

    if(side == 1)
    {
        /// x  y  z
        //  0  0  1
        //  0  1  1
        //  0  1  0
        //  0  0  0

        left = blockType->leftPlane_x * percent + point4.z*texturePixel;
        right = blockType->leftPlane_x * percent + percent - (16-point2.z)*texturePixel;

        up = percent*blockType->leftPlane_y + (16-point2.y)*texturePixel;
        down = percent*blockType->leftPlane_y + (16-point4.y)*texturePixel;

        mPositionLeftRight.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(right, down));
        mPositionLeftRight.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(right, up));
        mPositionLeftRight.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(left, up));
        mPositionLeftRight.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(left, down));

        mTriangleLeftRight.push_back(new Vector3(iVertexLeftRight, iVertexLeftRight+1, iVertexLeftRight+2));
        mTriangleLeftRight.push_back(new Vector3(iVertexLeftRight+2, iVertexLeftRight+3, iVertexLeftRight));

        iVertexLeftRight += 4;
        pointsLeftRight += 6;
    }

    if(side == 2)
    {
        /// x  y  z
        //  1  0  0
        //  1  1  0
        //  1  1  1
        //  1  0  1

        left = blockType->rightPlane_x*percent + point1.z*texturePixel;
        right = blockType->rightPlane_x*percent + percent - (16-point3.z)*texturePixel;

        up = percent*blockType->rightPlane_y + (16-point3.y)*texturePixel;
        down = percent*blockType->rightPlane_y + (16-point1.y)*texturePixel;

        mPositionLeftRight.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(right, down));
        mPositionLeftRight.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(right, up));
        mPositionLeftRight.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(left, up));
        mPositionLeftRight.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesLeftRight.push_back(new Vector2(left, down));

        mTriangleLeftRight.push_back(new Vector3(iVertexLeftRight, iVertexLeftRight+1, iVertexLeftRight+2));
        mTriangleLeftRight.push_back(new Vector3(iVertexLeftRight+2, iVertexLeftRight+3, iVertexLeftRight));

        iVertexLeftRight += 4;
        pointsLeftRight += 6;
    }

    if(side == 3)
    {
        /// x  y  z
        //  0  0  0
        //  1  0  0
        //  1  0  1
        //  0  0  1

        left = blockType->downPlane_x*percent + point1.x*texturePixel;
        right = blockType->downPlane_x*percent + percent - (16-point3.x)*texturePixel;

        up = percent*blockType->downPlane_y + (16-point1.z)*texturePixel;
        down = percent*blockType->downPlane_y + (16-point3.z)*texturePixel;

        mPositionBottomTop.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(left, up));
        mPositionBottomTop.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(right, up));
        mPositionBottomTop.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(right, down));
        mPositionBottomTop.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(left, down));

        mTriangleBottomTop.push_back(new Vector3(iVertexBottomTop, iVertexBottomTop+1, iVertexBottomTop+2));
        mTriangleBottomTop.push_back(new Vector3(iVertexBottomTop+2, iVertexBottomTop+3, iVertexBottomTop));

        iVertexBottomTop += 4;
        pointsBottomTop += 6;
    }

    if(side == 4)
    {
        /// x  y  z
        //  0  1  1
        //  1  1  1
        //  1  1  0
        //  0  1  0

        left = blockType->upPlane_x*percent + point4.x*texturePixel;
        right = blockType->upPlane_x*percent + percent - (16-point2.x)*texturePixel;

        up = percent*blockType->upPlane_y + (16-point2.z)*texturePixel;
        down = percent*blockType->upPlane_y + (16-point4.z)*texturePixel;

        mPositionBottomTop.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(left, up));
        mPositionBottomTop.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(right, up));
        mPositionBottomTop.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(right, down));
        mPositionBottomTop.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesBottomTop.push_back(new Vector2(left, down));

        mTriangleBottomTop.push_back(new Vector3(iVertexBottomTop, iVertexBottomTop+1, iVertexBottomTop+2));
        mTriangleBottomTop.push_back(new Vector3(iVertexBottomTop+2, iVertexBottomTop+3, iVertexBottomTop));

        iVertexBottomTop += 4;
        pointsBottomTop += 6;
    }

    if(side == 5)
    {
        /// x  y  z
        //  0  1  0
        //  1  1  0
        //  1  0  0
        //  0  0  0

        left = blockType->botPlane_x*percent + point4.x*texturePixel;
        right = blockType->botPlane_x*percent + percent - (16-point2.x)*texturePixel;

        up = percent*blockType->botPlane_y + (16-point2.y)*texturePixel;
        down = percent*blockType->botPlane_y + (16-point4.y)*texturePixel;

        mPositionBackFront.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesBackFront.push_back(new Vector2(right, up));
        mPositionBackFront.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesBackFront.push_back(new Vector2(left, up));
        mPositionBackFront.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesBackFront.push_back(new Vector2(left, down));
        mPositionBackFront.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesBackFront.push_back(new Vector2(right, down));

        mTriangleBackFront.push_back(new Vector3(iVertexBackFront, iVertexBackFront+1, iVertexBackFront+2));
        mTriangleBackFront.push_back(new Vector3(iVertexBackFront+2, iVertexBackFront+3, iVertexBackFront));

        iVertexBackFront += 4;
        pointsBackFront += 6;
    }

    if(side == 6)
    {
        /// x  y  z
        //  0  0  1
        //  1  0  1
        //  1  1  1
        //  0  1  1

        left = blockType->forPlane_x*percent + point1.x*texturePixel;
        right = blockType->forPlane_x*percent + percent - (16-point3.x)*texturePixel;

        up = percent*blockType->forPlane_y + (16-point3.y)*texturePixel;
        down = percent*blockType->forPlane_y + (16-point1.y)*texturePixel;

        mPositionBackFront.push_back(new Vector3(x+point1.x*pixel, y+point1.y*pixel, z+point1.z*pixel));
        mtexturesBackFront.push_back(new Vector2(left, down));
        mPositionBackFront.push_back(new Vector3(x+point2.x*pixel, y+point2.y*pixel, z+point2.z*pixel));
        mtexturesBackFront.push_back(new Vector2(right, down));
        mPositionBackFront.push_back(new Vector3(x+point3.x*pixel, y+point3.y*pixel, z+point3.z*pixel));
        mtexturesBackFront.push_back(new Vector2(right, up));
        mPositionBackFront.push_back(new Vector3(x+point4.x*pixel, y+point4.y*pixel, z+point4.z*pixel));
        mtexturesBackFront.push_back(new Vector2(left, up));

        mTriangleBackFront.push_back(new Vector3(iVertexBackFront, iVertexBackFront+1, iVertexBackFront+2));
        mTriangleBackFront.push_back(new Vector3(iVertexBackFront+2, iVertexBackFront+3, iVertexBackFront));

        iVertexBackFront += 4;
        pointsBackFront += 6;
    }
}


