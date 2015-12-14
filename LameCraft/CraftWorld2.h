#ifndef CraftWorld_H
#define CraftWorld_H

#include <string>
#include <math.h>
#include <psptypes.h>

#include <Aurora/Math/Frustum.h>
#include <Aurora/Math/Vector4.h>
#include <Aurora/Graphics/Effects/Drop.h>

#include "Blocks.h"
#include "Items.h"
#include "SimpleMeshChunk2.h"
#include "Furnace2.h"
#include "Chest2.h"
#include "DirectionBlock.h"

#include "LameFunctions.h"

class Cow;
class Zombie;
class Drop;

class CraftWorld
{
public:

	int WORLD_HEIGHT;

	enum BlockSettings
	{
		 OpLighSource = 0x10, //16
		 OpSideRender = 0x20,
		 OpActAsLadder = 0x40,
		 OpLightTraveled = 0x80
	};

	CraftWorld();
	~CraftWorld();

    typedef struct Statistics
    {
        unsigned short blockPlaced;
        unsigned short blockDestroyed;
        unsigned short daysInGame;
        unsigned short minutesPlayed;
        unsigned short itemsCrafted;
        unsigned short itemsSmelted;
        unsigned short jumps;
        unsigned short dies;
        unsigned short foodEaten;
        unsigned short badlyFalls;
        unsigned short blocksWalked;
        unsigned short treesGrowned;
        unsigned short cropsGrowned;
        unsigned short soilPlowed;
        unsigned short timeInWater;
        unsigned short timeInAir;
        unsigned short damageRecieved;
    } st;

    typedef struct Options
    {
        bool cloudsRender;
        bool fastRendering;
        bool sunMoodRendering;
        bool sounds;
        bool music;
        bool headBob;
        bool worldBlockAnimation;
        bool fogRendering;
        bool fakeShadowsRendering;
        bool particles;
        bool guiDrawing;

        float fov;
        char horizontalViewDistance;
        char verticalViewDistance;
        int difficult;
    } opt;

    st mainStatistics;
    opt mainOptions;

    char gameModeWorld;
    bool gameLocked;

	block_t& GetBlock (const int x, const int y, const int z) ;
	block_t& GetBlockLight (const int x, const int y, const int z);
	block_t& GetBlockSettings (const int x, const int y, const int z);
	block_t BlockAtPoint(Vector3 pos);

	inline void BuildWorldBlockPlane(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4);
	inline void BuildWorldBlockPlane(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, bool alwaysBuild, bool constantColor);
	inline void BuildWorldBlockPlaneNoCheck(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4);
    inline void BuildGUIBlockPlane(BaseBlock* blockType, char side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4);


	//inline void BuildWorldBlockPlane(BaseBlock *blockType, int x,int y, int z, int &iVertex, SimpleMeshChunk* MeshChunk, block_t Block, bool transparent, std::string side, Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4);

	//map creation
	void initWorld(int worldSize, int worldHeight, int chunkSize);
	void initWorldBlocksLight();
	void initPutBlocksLight(const int x, const int z);

	void GetSpecialBlockVerts(int i,BaseBlock *blockType);
	void GetNormalBlockVerts(int i,BaseBlock *blockType);
	void GetItemVerts(int i,BaseItem *itemType);
	void GetCloudsVerts(BaseBlock *blockType);

	void buildblocksVerts();
	void buildcloudsVerts();
	void buildskyVerts();
	void buildmobVerts();
    void setTextureSize(int texture,int chunk,int animTexture, int animChunk, int itemTexture, int itemChunk);

    void PutInInventory(int id, int num, bool st);
    bool InventoryIsFull(int id, int num, bool st);

	//chunks handling
	void createChunks(const int StartX, const int StartY, const int StartZ);
	void createTransparentChunks(const int StartX, const int StartY, const int StartZ);
	void rebuildChunk(int id);
	void rebuildTransparentChunk(int id);
	void rebuildNearestChunks(int id,Vector3 pos);
	void rebuildNearestChunksForLight(int id,Vector3 pos);
	void createWorldChunkss();
	void SetAllChunksToUpdate();

    void rebuildVisibleTransperentChunks();
	void rebuildVisibleChunks();

	void GetSpecialBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent);
	void GetNormalBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent);

	//load/save options
	void SaveCompressedWorld(std::string filename);
	void LoadWorld(const char *filename);
	void LoadCompressedWorld(std::string filename);

	//lightening
	void InitLightValues();
	void SetWolrdTime(float time);
	void LightTravel(int x,int y,int z,int steps,int lightLevel);

	void buildMap();
	void destroyMap();

	//rendering
	void drawWorld(Frustum &camFrustum,bool camUpdate);
	void drawCubes(int i, float light);
	void drawHand();
	void drawClouds();
	void drawDropItems(int i);
	void drawItems(int i);
	void drawHandItems(int i, float light);
	void drawArmor(int i, float light);
	void drawShoulder(int chestplateId, float light);

	//pickin,collision etc
	int groundHeight (const int x, const int z);
	int groundHeightWater (const int x, const int z);
	int groundHeightExcept (const int x, const int z, int bl);
	int getChunkId(Vector3 pos);
	int BlockSoundAtPos(Vector3 pos);

	bool SolidAtPointForPlayer(Vector3 pos);
	bool SolidAtPointForEntity(Vector3 pos, Vector3 collider1);
	bool SolidAtPoint(Vector3 pos);
	bool PlayerInWater(Vector3 pos);
	bool PlayerInLava(Vector3 pos);
	bool PlayerInBlock(Vector3 pos);

	bool BlockTransparentOrSpecial(const int x, const int y, const int z);
	bool BlockTransparentOrLightSource(const int x, const int y, const int z);
	bool BlockTransparent(const int x, const int y, const int z);
	bool BlockAnimated(const int x, const int y, const int z);
	char BlockSpecial(const int x, const int y, const int z);
	bool BlockEditable(const int x, const int y, const int z);
	bool BlockAllowLight(const int x, const int y, const int z);
	float BlockFinalLight(int x, int y, int z);
	char BlockRefraction(const int x, const int y, const int z);
	short BlockLoot(const int x, const int y, const int z);
	short BlockMaterial(const int x, const int y, const int z);
	bool BlockUpdate2(const int x, const int y, const int z);
	bool BlockSolid(const int x, const int y, const int z);

    int LootBlock(int id);
	bool LightSourceBlock(int id);
	int DurabilityPointsItem(int id);

	bool CanPutBlockHere(const int x, const int y, const int z,int blockID);
	void SetLigtSourcePosition(const int x, const int y, const int z,int blockID);
	void CheckForTorchSupport(const int x, const int y, const int z,int blockID);
	void CheckForLadderSupport(const int x, const int y, const int z);
	void RemoveLigtSourceAtPosition(const int x, const int y, const int z,int blockID);
	void AddChunkToUpdate(const int x, const int y, const int z);
	void UpdateLightAreaIn(Vector3 pos);

	void SpawnZombie(float xx, float yy, float zz);
	void DestroyZombie(int id);
    void SpawnCow(float xx, float yy, float zz);
	void DestroyCow(int id);
    void CollisionWithOtherZombies(Zombie *Zombie1);

    void DropThis(int id, Vector3 position);
    void DropThis(int id, int am, Vector3 position);
    void DropThis(int id, int am, bool st, Vector3 position);

    void DropThisNoAlign(int id, int am, bool st, Vector3 position, Vector3 velocity);
    void DestroyDrop(int id);


	int GetDrawntTrianglesCount() { return drawnTriangles; }

	Vector3 GetPlayerPos();
	void UpdatePlayerZoneBB(Vector3 playerPosition);
	void UpdateWorldTime(float dt);
	void UpdateWorldAnimation(float dt);
	int GetBlockTypesCount();
	int GetItemTypesCount();
	void UpdateChunkBlocks(int id);
	void UpdateChunkGrowingBlocks(int id);

	int FindDirId(int x, int y, int z);

	void GetTexturesIds();

    short armorId[4];
    short armorAm[4];
    bool armorSt[4];
    short invId[36];  // id вещей в €чейках в инвентаре
    short invAm[36];  // количество вещей в €чейках в инвентаре
    bool invSt[36]; // стакаетс€ ли предмет в €чейке?
    short mId;        // id вещи в курсоре
    short mAm;        // количество вещи в курсоре
    bool mSt;       // стакаетс€?

    std::vector<BaseBlock> blockTypes;
	std::vector<BaseItem> itemTypes;

    float brightFactor;         // освещение неба
    float dawnSunsetFactor;     // закат и рассвет
    Vector3	fogColor;           // цвет тумана
	Vector3 startSkyColor;      // начальный цвет неба (градиент)
	Vector3 endSkyColor;        // конечный цвет неба (градиент)
	Vector3 dawnSunsetSkyColor; // цвет заката и рассвета

    int worldSeed;  // сид мира
    float HP;       // здоровье
    float HG;       // сытость
    float AP;       // брон€
    char OS;        // количесвто кислорода

    bool kickedStart;
    float kickedAngle;
    float kickedTimer;

    float animationTimer;
    float animationTimerEnd;
    char animationWaterFrame;
    char animationLavaFrame;
    bool animationLavaStep;

    float spawnMobsTimer;

    int textureWaterAnimationId;
    int textureLavaAnimationId;
    int textureItemsId;
    int textureTerrainId;
    int textureLeatherArmor1Id;
    int textureLeatherArmor2Id;
    int textureChainArmor1Id;
    int textureChainArmor2Id;
    int textureIronArmor1Id;
    int textureIronArmor2Id;
    int textureDiamondArmor1Id;
    int textureDiamondArmor2Id;
    int textureGoldenArmor1Id;
    int textureGoldenArmor2Id;

	char worldName[50];
	int createdChunksCount;

	float worldDayTime;
	float worldTime;

	float sunTime;
	int worldVersion;
	float lightAngle;

	Vector3 playerZoneSize;

    std::vector<Chest*> mChests;
    std::vector<Furnace*> mFurnaces;
    std::vector<DirectionBlock*> mDirects;
    std::vector<Zombie*> mZombies;
    std::vector<Cow*> mCows;
    std::vector<Drop*> mDrops;

    /// Gui block properties
    std::vector<Vector3*> mPositionLeftRight;
    std::vector<Vector2*> mtexturesLeftRight;
    std::vector<Vector3*> mTriangleLeftRight;

    std::vector<Vector3*> mPositionBackFront;
    std::vector<Vector2*> mtexturesBackFront;
    std::vector<Vector3*> mTriangleBackFront;

    std::vector<Vector3*> mPositionBottomTop;
    std::vector<Vector2*> mtexturesBottomTop;
    std::vector<Vector3*> mTriangleBottomTop;

    int iVertexLeftRight;
    int pointsLeftRight;

    int iVertexBackFront;
    int pointsBackFront;

    int iVertexBottomTop;
    int pointsBottomTop;

    int mChestsize;
    int mFurnacesize;
    int mDirectsize;
    int mZombiesize;
    int mCowsize;

    int zombieNum;
    int dropNum;

    Vector3 lightColor;
    Vector3	ambientColor;

    float skyTime;

    void BuildBlockSphere(int radius, block_t block, int X, int Y, int Z);
    void BuildBlockSphere(int radius, block_t block, int X, int Y, int Z, block_t blockToChange);

    std::vector<SimpleMeshChunk*> mChunks;
    std::vector<int> toUpdate;

    float updatingChunksTimer;
    float updatingChunksTimerMax;
    unsigned int updatingChunksPosition;
    std::vector<int> updatingChunks;

    // for humanoids
    TexturesPSPVertex *bodyVertices;
    TexturesPSPVertex *headVertices;
    TexturesPSPVertex *legVertices;
    TexturesPSPVertex *handVertices;

    // for cows
    TexturesPSPVertex *cowBodyVertices;
    TexturesPSPVertex *cowHeadVertices;
    TexturesPSPVertex *cowLegVertices;

    // for armor
    TexturesPSPVertex *helmetVertices;
    TexturesPSPVertex *shoulderVertices;
    TexturesPSPVertex *chestplateVertices;
   // TexturesPSPVertex *bellyVertices;
    TexturesPSPVertex *leggingVertices;
    TexturesPSPVertex *bootVertices;

    Vector3 playerPos;

private:

	int WORLD_SIZE;
	int CHUNK_SIZE;

	int texutreSize;
	int textureChunk;
	float percent;
	float percent2;
	float percent3;

	std::vector<SimpleMeshChunk*> mTransparentChunks;

	block_t* m_BlockLight;
	block_t* m_BlockSettings;
    block_t* m_Blocks;

	//player zone aabb
	BoundingBox playerZoneBB;

	int chunksCreatedInFrameCount;
	int transparentchunksCreatedInFrameCount;
	int animatedchunksCreatedInFrameCount;

	float updateChunkTimer;
	bool updateChunksSwitch;

	//world time

	float worldHour;//1 game hour = 50 real seconds = 24 game hours = 20 real minutes

	//information
	int drawnTriangles;

	//transparent order rendering
	float lightShadowFactor;
	Vector3 lightFactor;

	float timee;
};


#endif
