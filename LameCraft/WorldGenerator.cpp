#include "WorldGenerator.h"
#include "CraftWorld2.h"
#include "LoadingScreen.h"


#define PI 3.1415926535897f
using namespace noisepp;

void WorldGenerator::initRandompMap(int worldSize, int worldHeight, int chunkSize, CraftWorld *world, bool makeTrees,bool makeWater,bool makeCaves,int seedII, int terrainBuilderI)
{
    LoadingScreen* loading = new LoadingScreen();
    loading->state = 1;
    loading->state2 = 1;

    octaves = 1;
    frequency = 1;
    scale = 1;
    gain = 1;
    exponent = 1;
    lacunarity = 1;
    multiplier = 1;
    offset = 1;
    //inicjuj mape
    int WORLD_SIZE = worldSize;
    int CHUNK_SIZE = chunkSize;

    if (seedII == 0)
    {
        seedII = rand() % 100000000;
    }

    int seed = seedII;

    srand(seedII);
    world->worldSeed = seedII;


    //terrain settings for default terrain
    unsigned char grass = 1;
    unsigned char rock = 3;
    unsigned char dirt = 2;

    float x3 = 1 + (rand() % 28)*0.1f;
    float x4 = 0 + (rand() % 35)*0.1f;

    while (x3 == x4)
    {
        x3 = 0 + rand() % 3;
    }
    int Height = 64;

    PerlinModule* perlin = new PerlinModule();
    perlin->setSeed(seed);
    perlin->setQuality(noisepp::NOISE_QUALITY_FAST_HIGH);

    if(terrainBuilderI != 0)
    {
        loading->state2 = 2;
        loading->state = 2;

        float *data = new float[worldSize * worldSize];
        float *data2 = new float[worldSize * worldSize];

        noisepp::utils::PlaneBuilder2D builder;
        noisepp::utils::PlaneBuilder2D builder2;

        perlin->setOctaveCount(6);
        perlin->setPersistence(0.5f);
        perlin->setFrequency(1.2f);
        perlin->setScale(2);
        perlin->setLacunarity(2.0f);

        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);
        builder.setBounds(0, 0, 2+(rand()%10)/10.0f, 2+(rand()%10)/10.0f);

        builder.setDestination(data);
        builder.build();

        perlin->setSeed(seed+2300);

        builder2.setModule(perlin);
        builder2.setSize(worldSize, worldSize);
        builder2.setBounds(0, 0, 2, 2);

        builder.setDestination(data2);
        builder.build();

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE] * 132/12 + 132/2;

                if(data2[x + z*WORLD_SIZE] * 132/12 + 132/2 > 72)
                {
                    Height += 1 + (data2[x + z*WORLD_SIZE] * 132/12 + 132/2 - 74)*0.3f;
                }

                for (int y = 0; y < Height; ++y)
                {
                    if(y == Height-1)
                        world->GetBlock(x, y, z) = grass;//grass
                    else if(y < Height-3)
                        world->GetBlock(x, y, z) = rock;
                    else
                        world->GetBlock(x, y, z) = dirt;
                }

            }
        }

        delete []data;
        delete []data2;


        loading->state = 3;
    }
    else
    {
        float *data = new float[worldSize * worldSize];
        noisepp::PerlinModule perlin;
        perlin.setSeed(seed);
        perlin.setQuality(noisepp::NOISE_QUALITY_FAST_STD);

        noisepp::utils::PlaneBuilder2D builder;
        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);

        builder.setBounds(0.0, 0.0, 0.0, 0.0);
        builder.setDestination(data);
        builder.build ();

        int Height = 50;

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE]* 128/12 + 128/2;
                //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

                for (int y = 0; y < Height; ++y)
                {
                        if(y == Height-1)
                            world->GetBlock(x, y, z) = grass;//grass
                        else if(y < Height-3)
                            world->GetBlock(x, y, z) = rock;
                        else
                            world->GetBlock(x, y, z) = dirt;
                }
            }
        }
        delete []data;
    }

    loading->state2 = 3;
	initBedrock(WORLD_SIZE, world);

	loading->state2 = 4;
	initBeachSand(WORLD_SIZE, world);
	initErosion(WORLD_SIZE, world);

    if(terrainBuilderI != 0)
    {
        loading->state2 = 5;
        initWaterAndCanes(WORLD_SIZE, world);
    }

    loading->state = 4;

    for (int z = 0; z < WORLD_SIZE; z++)
    {
        for (int x = 0; x < WORLD_SIZE; x++)
        {
            for (int y = 90; y >= 1; y--)
            {
                if(world->GetBlock(x,y,z) == 2 || world->GetBlock(x,y,z) == 1)
                {
                    if(world->GetBlock(x,y+1,z) == 0)
                    {
                        world->GetBlock(x,y,z) = 1;
                    }
                    else if(world->GetBlock(x,y+1,z) != 0 && (world->GetBlock(x,y+2,z) == 0 || world->GetBlock(x,y+3,z) == 0))
                    {
                        world->GetBlock(x,y,z) = 2;
                    }
                    else
                    {
                        world->GetBlock(x,y,z) = 3;
                    }
                }
            }
        }
    }

    loading->state = 5;

    loading->state2 = 6;

    if(makeCaves)
	{
	    int numWorms = 10 + rand() % 10;
	    for(int i = 0; i < numWorms; i++)
        {
            int steps = 32 + rand() % 48;
            float direction = rand() % 360;
            int radius = 2 + rand() % 2;

            int x = 10 + rand() % (WORLD_SIZE-10);
            int z = 10 + rand() % (WORLD_SIZE-10);
            int y = 32 - rand() % 24;

            for(int j = 0; j < steps; j++)
            {
                world->BuildBlockSphere(radius,0,x,y,z,2);

                x += sinf(direction/180*PI)*radius*1.33f;
                z += cosf(direction/180*PI)*radius*1.33f;
                y += -2 + rand() % 3;

                if(rand() % 100 < 15)
                {
                    direction += -70 + rand() % 140;
                }
                else
                {
                    direction += -30 + rand() % 60;
                }
            }
        }
	}

    loading->state = 6;

    loading->state2 = 7;
    initBiome(WORLD_SIZE, world, perlin, seed);

    loading->state2 = 8;
    initPumpkins(WORLD_SIZE, world);

    loading->state = 7;

    loading->state2 = 9;
    if(makeTrees)
    {
        initGreatTrees(WORLD_SIZE, world);
        initTrees(WORLD_SIZE, world, perlin, seed);
    }

    loading->state = 8;

    loading->state2 = 10;
    initIron(WORLD_SIZE, world);
    initCoal(WORLD_SIZE, world);
    initGold(WORLD_SIZE, world);
    initLapis(WORLD_SIZE, world);
    initDiamond(WORLD_SIZE, world);
    initClay(WORLD_SIZE, world);

    loading->state = 9;

    loading->state2 = 11;
    initFlowers(WORLD_SIZE, world);
    //initGrass(WORLD_SIZE, world);
    //initOtherVegetation(WORLD_SIZE, world);

    loading->state = 9;

    loading->state2 = 12;
    initLava(WORLD_SIZE, world);
    initDirt(WORLD_SIZE, world);
    initDungeons(WORLD_SIZE, world);

    loading->KillLoadingScreen();
        //caves?
    delete loading;
    delete perlin;
}

void WorldGenerator::initErosion(int WORLD_SIZE, CraftWorld *world)
{
    int num = 13 + rand() % 8;

    for(int i = 0; i < num; i++)
    {
        int x = 6 + rand() % WORLD_SIZE-9;
        int z = 6 + rand() % WORLD_SIZE-9;
        int y = world->groundHeight(x,z);
        world->BuildBlockSphere(2+rand()%3,0,x,y+rand()%2,z);

        int xx, yy, zz;
        xx = x;
        yy = y+1;
        zz = z;
        for(int j = 0; j <= 10; j++)
        {
            world->GetBlock(xx,yy,zz) = 0;
            world->GetBlock(xx,yy-2,zz) = 0;
            world->GetBlock(xx,yy-1,zz) = 0;
            world->GetBlock(xx,yy+1,zz) = 0;

            world->GetBlock(xx+1,yy,zz) = 0;
            world->GetBlock(xx+1,yy-2,zz) = 0;
            world->GetBlock(xx+1,yy-1,zz) = 0;
            world->GetBlock(xx+1,yy+1,zz) = 0;

            world->GetBlock(xx-1,yy,zz) = 0;
            world->GetBlock(xx-1,yy-2,zz) = 0;
            world->GetBlock(xx-1,yy-1,zz) = 0;
            world->GetBlock(xx-1,yy+1,zz) = 0;

            world->GetBlock(xx,yy,zz+1) = 0;
            world->GetBlock(xx,yy-2,zz+1) = 0;
            world->GetBlock(xx,yy-1,zz+1) = 0;
            world->GetBlock(xx,yy+1,zz+1) = 0;

            world->GetBlock(xx,yy,zz-1) = 0;
            world->GetBlock(xx,yy-2,zz-1) = 0;
            world->GetBlock(xx,yy-1,zz-1) = 0;
            world->GetBlock(xx,yy+1,zz-1) = 0;



            switch(rand()%2)
            {
                case 0: xx += -1+rand()%3; break;
                case 1: zz += -1+rand()%3; break;
            }
        }
    }
}

void WorldGenerator::initLavaPools(int WORLD_SIZE, CraftWorld *world)
{
    int num = 2 + rand() % 2;

    for(int i = 0; i < num; i++)
    {
        int x = 9 + rand() % WORLD_SIZE-12;
        int z = 9 + rand() % WORLD_SIZE-12;
        int y = 0;

        while(world->groundHeight(x,z) < 70)
        {
            x = 9 + rand() % WORLD_SIZE-12;
            z = 9 + rand() % WORLD_SIZE-12;
        }
        y = world->groundHeight(x,z);

        if(rand() % 100 > 40)
        {
            world->BuildBlockSphere(3,0,x,y+2,z);
            world->BuildBlockSphere(3,112,x,y,z,1);
            world->BuildBlockSphere(3,112,x,y,z,2);
            world->BuildBlockSphere(3,112,x,y,z,3);
            world->BuildBlockSphere(3,112,x,y,z,7);
        }
        else
        {
            world->BuildBlockSphere(5,0,x,y+4,z);
            world->BuildBlockSphere(5,112,x,y,z,1);
            world->BuildBlockSphere(5,112,x,y,z,2);
            world->BuildBlockSphere(5,112,x,y,z,3);
            world->BuildBlockSphere(5,112,x,y,z,7);
        }
    }
}

void WorldGenerator::initLava(int WORLD_SIZE, CraftWorld *world)
{
    char Num = 15 + rand() % 8;

    for(int i = 0; i <= Num; i++)
    {
        int x = 16 + rand() % WORLD_SIZE-20;
        int z = 16 + rand() % WORLD_SIZE-20;
        int y = 32 - rand() % WORLD_SIZE-20;

        int w;


        w = 1 + rand() % 2;

        for(int X = x - w; X < x + w; X++)
        {
            for(int Z = z - w; Z < z + w; Z++)
            {

                if(X > 0 && X < WORLD_SIZE-1 && Z > 0 && Z < WORLD_SIZE-1 && y > 0 && y < world->WORLD_HEIGHT-1)
                    world->GetBlock(X,y,Z) = 112;

            }
        }
        for(int X = x - w-1; X < x + w+1; X++)
        {
            for(int Z = z - w-1; Z < z + w+1; Z++)
            {
                if(X > 0 && X < WORLD_SIZE-1 && Z > 0 && Z < WORLD_SIZE-1 && y+1 > 0 && y+1 < world->WORLD_HEIGHT-1)
                     world->GetBlock(X,y+1,Z) = 0;
            }
        }
        for(int X = x - w; X < x + w; X++)
        {
            for(int Z = z - w; Z < z + w; Z++)
            {
                if(X > 0 && X < WORLD_SIZE-1 && Z > 0 && Z < WORLD_SIZE-1 && y+2 > 0 && y+2 < world->WORLD_HEIGHT-1)
                     world->GetBlock(X,y+2,Z) = 0;
            }
        }
    }
}


void WorldGenerator::initGreatTrees(int WORLD_SIZE, CraftWorld *world)
{
    int NumTrees = 12 + rand() % 8;
    bool flag = 1;

    for(int i = 0; i <= NumTrees; i++)
    {
        flag = 1;

        int x = 10 + rand() % WORLD_SIZE-11;
        int z = 10 + rand() % WORLD_SIZE-11;
        int y = world->groundHeight(x,z) + 1;

        int treeHeight = 8;

        for(int X = x-1; X <= x+1; X++)
        {
            for(int Z = z-1; Z <= z+1; Z++)
            {
                for(int Y = y; Y < y + treeHeight; Y++)
                {
                    if(world->GetBlock(X,Y,Z) != 0)
                    {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        if(world->GetBlock(x,y-1,z) != 1)
        {
            flag = 0;
        }

        if(flag == 1)
        {
            for(int X = x-1; X <= x+1; X++)
            {
                for(int Z = z-1; Z <= z+1; Z++)
                {
                    switch(rand()%7)
                    {
                    case 1:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 77;
                    }
                    break;
                    case 2:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 77;
                    }
                    break;
                    case 3:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 78;
                    }
                    break;
                    }
                }
            }
            for(int y1 = y; y1 < y + treeHeight; y1 ++)
            {
                world->GetBlock(x,y1,z) = 8;
                if(y1 - y > treeHeight/3)
                {
                    if(rand() % 3 == 2)
                    {
                        switch(rand() % 4)
                        {
                        case 0:
                        for(int X = x; X <= x + 3; X++)
                        {
                            world->GetBlock(X,y1,z) = 8;
                            if(X == x+3)
                            {
                                world->BuildBlockSphere(2,9,X,y1,z,0);
                            }
                        }
                        break;
                        case 1:
                        for(int X = x-3; X <= x; X++)
                        {
                            world->GetBlock(X,y1,z) = 8;
                            if(X == x-3)
                            {
                                world->BuildBlockSphere(2,9,X,y1,z,0);
                            }
                        }
                        break;
                        case 2:
                        for(int Z = z; Z <= z + 3; Z++)
                        {
                            world->GetBlock(x,y1,Z) = 8;
                            if(Z == z+3)
                            {
                                world->BuildBlockSphere(2,9,x,y1,Z,0);
                            }
                        }
                        break;
                        case 3:
                        for(int Z = z-3; Z <= z; Z++)
                        {
                            world->GetBlock(x,y1,Z) = 8;
                            if(Z == z-3)
                            {
                                world->BuildBlockSphere(2,9,x,y1,Z,0);
                            }
                        }
                        break;
                        }
                    }
                }
                if(y1 - y == treeHeight - 2)
                {
                    world->BuildBlockSphere(3,9,x,y1,z,0);
                }
            }
        }
    }
}

void WorldGenerator::initBiome(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed)
{
    int ran = 100;
    for (int z = 0; z < 88; ++z)
    {
        for (int x = 0; x < 88; ++x)
        {
            ran = 100;
            if(x == 85 || z == 85)
            {
                ran = 75;
            }
            if(x == 86 || z == 86)
            {
                ran = 50;
            }
            if(x == 87 || z == 87)
            {
                ran = 25;
            }

            if(rand() % 100 < ran)
            {
                if(world->GetBlock(x, world->groundHeight(x, z), z) == 0) continue;
                if(world->GetBlock(x, world->groundHeightExcept(x, z, 9), z) == 1)
                {
                    world->GetBlock(x, world->groundHeightExcept(x, z, 9), z) = 29; // snow
                }
                else if(world->GetBlock(x, world->groundHeightWater(x, z), z) == 4)
                {
                    world->GetBlock(x, world->groundHeightWater(x, z), z) = 32; // ice
                    continue;
                }

                if(world->GetBlock(x, world->groundHeight(x, z), z) != 93 && world->GetBlock(x, world->groundHeight(x, z), z) != 32)
                {
                    if(world->GetBlock(x, world->groundHeight(x, z)+1, z) == 0)
                    {
                        world->GetBlock(x, world->groundHeight(x, z)+1, z) = 93;
                    }
                }
            }
        }
    }

    ran = 100;
    for (int z = 0; z < 88; ++z)
    {
        for (int x = 0; x < 88; ++x)
        {
            ran = 100;
            if(x == 2 || z == 2)
            {
                ran = 75;
            }
            if(x == 1 || z == 1)
            {
                ran = 50;
            }
            if(x == 0 || z == 0)
            {
                ran = 25;
            }

            if(rand() % 100 < ran)
            {
                if(world->GetBlock(88+x, world->groundHeight(88+x, 88+z), 88+z) == 0) continue;

                if(world->GetBlock(88+x, world->groundHeight(88+x, 88+z), 88+z) == 1 || (world->GetBlock(88+x, world->groundHeight(88+x, 88+z), 88+z) == 2 && world->GetBlock(88+x, world->groundHeight(88+x, 88+z)+1, 88+z) != 4 ))
                {
                    for(int Y = world->groundHeight(88+x, 88+z); Y >= world->groundHeight(88+x, 88+z) - 4; Y--)
                    {
                        if(world->GetBlock(88+x, Y, 88+z) == 3)
                        {
                            world->GetBlock(88+x, Y, 88+z) = 26;
                        }
                        if(world->GetBlock(88+x, Y, 88+z) == 1 || world->GetBlock(88+x, Y, 88+z) == 2)
                        {
                            world->GetBlock(88+x, Y, 88+z) = 7;
                            if(world->GetBlock(88+x, Y+1, 88+z) == 0)
                            {
                                if(rand() % 250 == 1)
                                {
                                    for(int YY = Y+1; YY <= Y+3; YY ++)
                                    {
                                        world->GetBlock(88+x, YY, 88+z) = 25;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void WorldGenerator::initWaterAndCanes(int WORLD_SIZE, CraftWorld *world)
{

        for (int z = 0; z < WORLD_SIZE; z++)
        {
            for (int x = 0; x < WORLD_SIZE; x++)
            {
                if (world->GetBlock(x,62,z) == 0)
                {
                    world->GetBlock(x,62,z) = 4;
                    if (world->GetBlock(x+1,62,z) == 7) //placing canes
                    {
                        if(rand()% 45 == 1)
                        {
                            char height = rand() % 3;
                            for(int k = 1; k < 2+height; k++)
                            {
                                world->GetBlock(x+1,62+k,z) = 33;
                            }
                        }
                    }
                    if (world->GetBlock(x-1,62,z) == 7) //placing canes
                    {
                        if(rand()% 45 == 1)
                        {
                            char height = 1+ rand() % 2;
                            for(int k = 1; k < 2+height; k++)
                            {
                                world->GetBlock(x-1,62+k,z) = 33;
                            }
                        }
                    }
                    if (world->GetBlock(x,61,z) == 1)
                    {
                        world->GetBlock(x,61,z) = 2;
                        continue;
                    }
                    for(int y = 61; y >= 30; y--)
                    {
                        if (world->GetBlock(x,y,z) != 0)
                            break;


                        if (world->GetBlock(x,y+1,z) == 4)
                        {
                            world->GetBlock(x,y,z) = 4;
                        }
                        if (world->GetBlock(x,y-1,z) != 2 && world->GetBlock(x,y-1,z) != 4 && world->GetBlock(x,y-1,z) != 0)
                        {
                            world->GetBlock(x,y-1,z) = 2;
                        }
                    }
                }
            }
        }

}

void WorldGenerator::initBedrock(int WORLD_SIZE, CraftWorld *world)
{
        for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            world->GetBlock(x, 0, z) = IronBlock::getID();//last one in set
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 2;
            if (r == 1)
            {
            world->GetBlock(x, 1, z) = IronBlock::getID();//last one in set
            }
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 3;
            if (r == 1)
            {
            world->GetBlock(x, 2, z) = IronBlock::getID();//last one in set
            }
        }
    }
}

void WorldGenerator::initBeachSand(int WORLD_SIZE, CraftWorld *world)
{
    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            if (world->GetBlock(x,62,z) != 0 && world->GetBlock(x,63,z) == 0)
            {
                world->GetBlock(x,62,z) = 7;
                world->GetBlock(x,61,z) = 7;
            }
        }
    }
}

void WorldGenerator::initTrees(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed)
{
    float *dataTrees = new float[WORLD_SIZE * WORLD_SIZE];
    perlin->setSeed(seed+10);
    perlin->setOctaveCount(2+rand()%2);
    perlin->setPersistence(0.5f + (rand() % 10 *0.1f));
    noisepp::utils::PlaneBuilder2D builderTrees;
    builderTrees.setModule(perlin);
    builderTrees.setSize(WORLD_SIZE, WORLD_SIZE);
    builderTrees.setBounds(1 + rand() % 5, 1, 6, 1 + rand() % 5);
    builderTrees.setDestination(dataTrees);
    builderTrees.build ();

    char perlinHeight;
    char woodBlock;
    char leavesBlock;
    bool snowTree;

    int frequency2 = 30 + rand() % 25;

    for (int Z = 0; Z < WORLD_SIZE; Z += 4 +rand()%5)
    {
        for (int x = 0; x < WORLD_SIZE; x += 4 +rand()%5)
        {
            int z = Z + (-2 + rand() % 3);
            if(x < 0 || x > WORLD_SIZE-1 || z < 0 || z > WORLD_SIZE-1)
            {
                continue;
            }
            perlinHeight = dataTrees[x + z*WORLD_SIZE]* 128/12 + 128/2;
            if(perlinHeight >  65 && rand() % 100 <= frequency2)
            {
                if(world->GetBlock(x,world->groundHeightExcept(x,z,93),z) == 29)
                {
                    snowTree = true;
                }
                else
                {
                    snowTree = false;
                }

                if(snowTree == false)
                {
                    char y = world->groundHeightExcept(x,z,93);
                    char TrunkHeight = 5;//rand() % 5 + 4;


                    //check if there is an water on there or another tree
                    bool flag = 0;

                    if(world->GetBlock(x, y, z) == 1)
                    {
                        flag = 1;
                    }

                    for (int y1 = y+1; y1 < y + 1 + TrunkHeight && y1 < world->WORLD_HEIGHT; ++y1)
                    {
                        if(world->GetBlock(x, y1, z) != 0 && world->GetBlock(x, y1, z) != 93)
                        {
                            flag = 0;
                            break;
                        }
                    }

                    if(flag == 0)continue;

                    if(rand() % 8 == 1)
                    {
                        woodBlock = 31;
                        leavesBlock = 38;
                        TrunkHeight = 4 + rand() % 2;
                    }
                    else
                    {
                        woodBlock = 8;
                        leavesBlock = 9;
                        TrunkHeight = 3 + rand() % 2;
                    }
                    //Create the tree trunk
                    for (int y1 = y+1; y1 < y + 1 + TrunkHeight && y1 < world->WORLD_HEIGHT; ++y1)
                    {
                        block_t& Block = world->GetBlock(x, y1, z);
                        Block = woodBlock;
                    }

                    //create my leaves
                    for(int yy = 0; yy < 2; yy++)
                    {
                        for(int xx = 0; xx < 5; xx++)
                        {
                            for(int zz = 0; zz < 3; zz++)
                            {
                                int x1 = xx + x - 2;// :D - what a shitty code
                                int y1 = yy + y + TrunkHeight - 1;
                                int z1 = zz + z - 1;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = leavesBlock;
                            }
                        }
                    }


                    for(int yy = 0; yy < 2; yy++)
                    {
                        for(int xx = 0; xx < 3; xx++)
                        {

                                int x1 = xx + x - 1;// :D - what a shitty code
                                int y1 = yy + y + TrunkHeight +1;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = leavesBlock;
                        }
                    }


                    for(int xx = 0; xx < 3; xx++)
                    {
                        for(int zz = 0; zz < 3; zz++)
                        {

                            int x1 = xx + x - 1;// :D - what a shitty code
                            int y1 = y + TrunkHeight + 1;
                            int z1 = zz + z - 1;
                            int rand1 = rand() % 8;

                            if (rand1 > 6)
                            {
                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = leavesBlock;
                            }
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        for(int zz = 0; zz < 3; zz++)
                        {

                                int x1 = x;// :D - what a shitty code
                                int y1 = yy + y + TrunkHeight + 1;
                                int z1 = zz + z - 1;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = leavesBlock;
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        for(int xx = 0; xx < 3; xx++)
                        {
                            for(int zz = 0; zz < 5; zz++)
                            {
                                int x1 = xx + x - 1;// :D - what a shitty code
                                int y1 = yy + y + TrunkHeight - 1;
                                int z1 = zz + z - 2;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = leavesBlock;
                            }
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        int x1 = x - 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = z - 2;
                        int rand1 = rand() % 3;

                        if (rand1 != 1)
                        {
                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = leavesBlock;
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        int x1 = x + 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = z - 2;
                        int rand1 = rand() % 3;

                        if (rand1 != 1)
                        {
                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = leavesBlock;
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        int x1 = x - 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = z + 2;
                        int rand1 = rand() % 3;

                        if (rand1 != 1)
                        {
                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = leavesBlock;
                        }
                    }

                    for(int yy = 0; yy < 2; yy++)
                    {
                        int x1 = x + 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = z + 2;
                        int rand1 = rand() % 3;

                        if (rand1 != 1)
                        {
                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = leavesBlock;
                        }
                    }
                }
                if(snowTree == true)
                {
                    char y = world->groundHeight(x,z);
                    char TrunkHeight = 6;//rand() % 5 + 4;
                    char type;

                    //check if there is an water on there or another tree
                    bool flag = 1;

                    for (int y1 = y+1; y1 <= y + TrunkHeight ; y1++)
                    {
                        if(world->GetBlock(x, y1, z) != 0)
                        {
                            flag = 0;
                            break;
                        }
                    }

                    if(flag == 0)continue;

                    woodBlock = 30;

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
                        block_t& Block = world->GetBlock(x, y1, z);
                        Block = woodBlock;
                    }

                    if(type == 0)
                    {
                        for(int xx = -1; xx <= 1; xx++)
                        {
                            for(int zz = -2; zz <= 2; zz++)
                            {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 1;
                                int z1 = zz + z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                            }
                        }

                        for(int xx = -2; xx <= 2; xx++)
                        {
                            for(int zz = -1; zz <= 1; zz++)
                            {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 1;
                                int z1 = zz + z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                            }
                        }

                        for(int xx = -1; xx <= 1; xx++)
                        {
                            for(int zz = -2; zz <= 2; zz++)
                            {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 3;
                                int z1 = zz + z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                            }
                        }

                        for(int xx = -2; xx <= 2; xx++)
                        {
                            for(int zz = -1; zz <= 1; zz++)
                            {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 3;
                                int z1 = zz + z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                            }
                        }

                        for(int xx = -1; xx <= 1; xx++)
                        {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 2;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                        }


                        for(int zz = -1; zz <= 1; zz++)
                        {
                            int x1 = x;// :D - what a shitty code
                            int y1 = y + 2;
                            int z1 = zz + z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 37;
                        }

                        for(int xx = -1; xx <= 1; xx++)
                        {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 4;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                        }


                        for(int zz = -1; zz <= 1; zz++)
                        {
                            int x1 = x;// :D - what a shitty code
                            int y1 = y + 4;
                            int z1 = zz + z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 37;
                        }

                        for(int xx = -1; xx <= 1; xx++)
                        {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + 6;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                        }

                        for(int zz = -1; zz <= 1; zz++)
                        {
                            int x1 = x;// :D - what a shitty code
                            int y1 = y + 6;
                            int z1 = zz + z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 37;
                        }

                        block_t& Block = world->GetBlock(x, y+7, z);
                        if (Block == 0) Block = 37;
                    }
                    else // type == 1
                    {
                        block_t& Block = world->GetBlock(x, y+TrunkHeight+1, z);
                        if (Block == 0) Block = 37;

                        for(int xx = -1; xx <= 1; xx++)
                        {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + TrunkHeight;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                        }

                        for(int zz = -1; zz <= 1; zz++)
                        {
                            int x1 = x;// :D - what a shitty code
                            int y1 = y + TrunkHeight;
                            int z1 = zz + z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 37;
                        }

                        for(int xx = -1; xx <= 1; xx++)
                        {
                                int x1 = xx + x;// :D - what a shitty code
                                int y1 = y + TrunkHeight-1;
                                int z1 = z;

                                if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                                if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                                block_t& Block = world->GetBlock(x1, y1, z1);
                                if (Block == 0) Block = 37;
                        }

                        for(int zz = -1; zz <= 1; zz++)
                        {
                            int x1 = x;// :D - what a shitty code
                            int y1 = y + TrunkHeight-1;
                            int z1 = zz + z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= world->WORLD_HEIGHT || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 37;
                        }
                    }
                }
            }
        }
    }

    delete[] dataTrees;
}

void WorldGenerator::initPumpkins(int WORLD_SIZE, CraftWorld *world)
{
    char NumPumpkinsSpawns = 8 + rand() % 4;
    char Frequency = 4; // 1 - 100

    for (int i = 0; i < NumPumpkinsSpawns; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        //check if there is an water on there or another tree
        unsigned short rad = 0;

        for(int x2 = x-3; x2 < x+3; ++x2)
        {
            for(int z2 = z-3; z2 < z+3; ++z2)
            {
                if (x2 > 0 && x2 < WORLD_SIZE && z2 > 0 && z2 < WORLD_SIZE)
                {

                    rad = rand() % 100;

                    if (rad > Frequency)
                        continue;

                    if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 2 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 29)
                    {
                        if(world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) == 0)
                        {
                            short rad2 = rand() % 4;

                            world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2) = 73+rad2;
                        }
                    }
                }
            }
        }
    }
}

void WorldGenerator::initFlowers(int WORLD_SIZE, CraftWorld *world) //generate flowers
{
    int num = 10 + rand() % 10;

    for (int i = 0; i < num; ++i)
    {
        int centerX = 10 + rand() % (WORLD_SIZE-10);
        int centerZ = 10 + rand() % (WORLD_SIZE-10);

        int size = 2 + rand() % 2;
        int typeProcent = 25 + rand() % 50;

        for(int x = centerX-size; x <= centerX+size; x++)
        {
            for(int z = centerZ-size; z <= centerZ+size; z++)
            {
                int y = world->groundHeight(x, z);
                if(world->GetBlock(x,y,z) == 1)
                {
                    if(x == centerX-size || x == centerX+size || z == centerZ-size || z == centerZ+size) // check for corner flower
                    {
                        if(rand() % 7 == 1) // 1/6
                        {
                            if(rand() % 100 > typeProcent)
                            {
                                world->GetBlock(x,y+1,z) = Flower1::getID();
                            }
                            else
                            {
                                world->GetBlock(x,y+1,z) = Flower2::getID();
                            }
                        }
                    }
                    else
                    {
                        if(rand() % 100 < 60) // 3/5
                        {
                            if(rand() % 100 > typeProcent)
                            {
                                world->GetBlock(x,y+1,z) = Flower1::getID();
                            }
                            else
                            {
                                world->GetBlock(x,y+1,z) = Flower2::getID();
                            }
                        }
                    }
                }
            }
        }
    }
}

void WorldGenerator::initGrass(int WORLD_SIZE, CraftWorld *world)
{

    int NumTypes = 700 + rand() % 150;

    for (int i = 0; i < NumTypes; ++i)
    {
        //Choose the tpumpkin position
        int x2 = rand() % WORLD_SIZE;
        int z2 = rand() % WORLD_SIZE;


        if(world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) == 0 && world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1)
        {
            world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) = 116;
        }
    }
}

void WorldGenerator::initOtherVegetation(int WORLD_SIZE, CraftWorld *world)
{

    int NumTypes = 100 + rand() % 100;

    for (int i = 0; i < NumTypes; ++i)
    {
        //Choose the tpumpkin position
        int x2 = rand() % WORLD_SIZE;
        int z2 = rand() % WORLD_SIZE;


        if(world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) == 0)
        {
            if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1)
            {
                world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) = 117;
            }
            if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 7)
            {
                world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) = 118;
            }
        }
    }
}

void WorldGenerator::initIron(int WORLD_SIZE, CraftWorld *world)
{
    int ore = IronOre::getID();
    int oreMinAmount = 3;
    int oreMaxAmount = 8;
    int highestLayer = 61;
    int lowestLayer = 3;

    float concentration = 0.43; // in percents - 0.5%

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);
        y = lowestLayer + rand() % (highestLayer-lowestLayer+1);

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}

void WorldGenerator::initCoal(int WORLD_SIZE, CraftWorld *world)
{
    int ore = CoalOre::getID();
    int oreMinAmount = 4;
    int oreMaxAmount = 9;
    int highestLayer = 70;
    int lowestLayer = 3;

    float concentration = 0.7; // in percents

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);
        y = lowestLayer + rand() % (highestLayer-lowestLayer+1);

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}

void WorldGenerator::initGold(int WORLD_SIZE, CraftWorld *world)
{
    int ore = GoldBlock::getID();
    int oreMinAmount = 2;
    int oreMaxAmount = 9;
    int highestLayer = 32;
    int lowestLayer = 2;

    float concentration = 0.1437; // in percents

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);
        y = lowestLayer + rand() % (highestLayer-lowestLayer+1);

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}

void WorldGenerator::initRedStone(int WORLD_SIZE, CraftWorld *world)//44
{
    int ore = RedstoneOre::getID();
    int oreMinAmount = 1;
    int oreMaxAmount = 10;
    int highestLayer = 15;
    int lowestLayer = 1;

    float concentration = 1.015; // in percents

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);
        y = lowestLayer + rand() % (highestLayer-lowestLayer+1);

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}

void WorldGenerator::initLapis(int WORLD_SIZE, CraftWorld *world)//44
{
    int ore = LapisOre::getID();
    int oreMinAmount = 8;
    int oreMaxAmount = 12;
    int highestLayer = 28;
    int lowestLayer = 1;

    float concentration = 0.2; // in percents

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);

        int rand1 = rand() % 100;
        if(rand1 > 20)
        {
            y = lowestLayer + rand() % (highestLayer-lowestLayer+1);
        }
        else if(rand1 <= 20 && rand1 > 5)
        {
            y = 15 + rand() % 5;
        }
        else
        {
            y = 30 + rand() % 3;
        }

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}

void WorldGenerator::initDiamond(int WORLD_SIZE, CraftWorld *world)
{
    int ore = DiamondOre::getID();
    int oreMinAmount = 3;
    int oreMaxAmount = 4;
    int highestLayer = 18;
    int lowestLayer = 2;

    float concentration = 0.08; // in percents

    int depositsAmount = (WORLD_SIZE*WORLD_SIZE*(highestLayer - lowestLayer))*(0.01*concentration)/((oreMinAmount+oreMaxAmount)/2.0f); // simple formula

    for(int i = 0; i < depositsAmount; ++i)
    {
        int x, y, z;

        x = 1 + rand() % (WORLD_SIZE-2);
        z = 1 + rand() % (WORLD_SIZE-2);
        y = lowestLayer + rand() % (highestLayer-lowestLayer+1);

        int oreAmount = oreMinAmount + rand() % (oreMaxAmount-oreMinAmount+1);

        for(int j = 0; j < oreAmount; j++)
        {
            if(world->GetBlock(x,y,z) == RockBlock::getID())
            {
                world->GetBlock(x,y,z) = ore;
            }

            bool go_further = false;
            int iterAmount = 0;

            while(go_further == false)
            {
                switch(rand() % 6)
                {
                    case 0:
                    if(world->GetBlock(x+1,y,z) == RockBlock::getID())
                    {
                        x += 1;
                        go_further = true;
                    }
                    break;

                    case 1:
                    if(world->GetBlock(x-1,y,z) == RockBlock::getID())
                    {
                        x -= 1;
                        go_further = true;
                    }
                    break;

                    case 2:
                    if(world->GetBlock(x,y+1,z) == RockBlock::getID())
                    {
                        y += 1;
                        go_further = true;
                    }
                    break;

                    case 3:
                    if(world->GetBlock(x,y-1,z) == RockBlock::getID())
                    {
                        y -= 1;
                        go_further = true;
                    }
                    break;

                    case 4:
                    if(world->GetBlock(x,y,z+1) == RockBlock::getID())
                    {
                        z += 1;
                        go_further = true;
                    }
                    break;

                    case 5:
                    if(world->GetBlock(x,y,z-1) == RockBlock::getID())
                    {
                        z -= 1;
                        go_further = true;
                    }
                    break;
                }

                iterAmount++;
                if(iterAmount > 7)
                {
                    go_further = true;
                }
            }
        }
    }
}


void WorldGenerator::initClay(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 200 + rand() % 100;

    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 12 + rand() % 8;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 76 - rand() % 24;

        for(int j = 0; j <= NumOreBlocks; j++)
        {
            if(x > 0 && x < WORLD_SIZE-1 && z > 0 && z < WORLD_SIZE-1 && y > 0 && y < world->WORLD_HEIGHT - 1)
            {
                if(world->GetBlock(x,y,z) == 7 || world->GetBlock(x,y,z) == 2)
                    world->GetBlock(x,y,z) = 99;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}



void WorldGenerator::initDirt(int WORLD_SIZE, CraftWorld *world)
{
    int NumBlocks = 1000;
    char radius = 2 + rand() % 3;

    short PlaceBlock = 2;

    for (int i = 0; i < NumBlocks; ++i)
    {
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 80 - rand() % 78;

        world->BuildBlockSphere(radius, PlaceBlock, x, y, z, RockBlock::getID());

    }
}


void WorldGenerator::initDungeons(int WORLD_SIZE, CraftWorld *world)
{
    int xSize, ySize, zSize;
    int x, y, z;

    ySize = 5;

    for(int t = 0; t <= 2; t++)
    {
        xSize = 5+rand()%3;
        zSize = 5+rand()%3;

        x = 1 + rand() % WORLD_SIZE-8;
        z = 1 + rand() % WORLD_SIZE-8;
        y = 40-(t*15) + rand() % 15;

        for(int xx = x; xx <= x+xSize; xx++)
        {
            for(int yy = y; yy <= y+ySize; yy++)
            {
                for(int zz = z; zz <= z+zSize; zz++)
                {
                    if(rand() % 100 > 80)
                    {
                        world->GetBlock(xx,yy,zz) = CobbleStone::getID();
                    }
                    else
                    {
                        world->GetBlock(xx,yy,zz) = MossyCobblestone::getID();
                    }
                }
            }
        }

        for(int xx = x+1; xx <= x+xSize-1; xx++)
        {
            for(int yy = y+1; yy <= y+ySize-1; yy++)
            {
                for(int zz = z+1; zz <= z+zSize-1; zz++)
                {
                    world->GetBlock(xx,yy,zz) = 0;
                }
            }
        }

        for(int j = 0; j <= 1; j++)
        {
            world->GetBlock(x+2+j,y+1,z+2+j) = 94 + rand() % 4;
            Chest *NewChest = new Chest(x+2+j,y+1,z+2+j);
            for(int i = 0; i <= 7; i++)
            {
                int slot = rand() % 27;
                int item = -1;
                int am = 0;
                bool st = true;

                int rand1 = rand() % 100;

                if(rand1 < 80)
                {
                    switch(rand() % 6)
                    {
                    case 0:
                        item = 284;
                        am = 1 + rand() % 2;
                    break;
                    case 1:
                        item = 286;
                        am = 2 + rand() % 3;
                    break;
                    case 2:
                        item = 288;
                        am = 2;
                    break;
                    case 3:
                        item = 322;
                        am = 5+rand()%5;
                    break;
                    case 4:
                        item = 311;
                        am = 1+rand()%4;
                    break;
                    case 5:
                        item = 314;
                        am = 6+rand()%8;
                    break;
                    }
                }
                else if(rand1 >= 80 && rand1 < 95)
                {
                    switch(rand() % 4)
                    {
                    case 0:
                        item = 315;
                        am = 8;
                    break;
                    case 1:
                        item = 291;
                        am = 1;
                        st = false;
                    break;
                    case 2:
                        item = 278;
                        am = 2+rand()%4;
                    break;
                    case 3:
                        item = 280;
                        am = 2+rand()%4;
                    break;
                    }
                }
                else
                {
                    switch(rand() % 2)
                    {
                    case 0:
                        item = 285;
                        am = 1;
                    break;
                    case 1:
                        item = 279;
                        am = 1+rand()%2;
                    break;
                    }
                }

                NewChest->chestSlotId[slot] = item;
                NewChest->chestSlotAm[slot] = am;
                NewChest->chestSlotSt[slot] = st;
            }
            NewChest->chestSlotId[26] = 312;
            NewChest->chestSlotAm[26] = 3;
            NewChest->chestSlotSt[26] = true;
            world->mChests.push_back(NewChest);
        }
    }
}


