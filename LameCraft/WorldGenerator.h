#ifndef WorldGenerator_H
#define WorldGenerator_H

#include <Aurora/Math/Frustum.h>
#include <math.h>
#include <psptypes.h>

#include <noisepp/Noise.h>
#include <noisepp/NoiseUtils.h>
#include <noisepp/NoiseBuilders.h>

#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#include "simplexnoise.h"
#include "Chest2.h"

class CraftWorld;
using namespace noisepp;

class WorldGenerator
{
	public:
		void initRandompMap(int worldSize, int worldHeight, int chunkSize, CraftWorld *world, bool makeTrees,bool makeWater,bool makeCaves,int seedII, int terrainBuilderI);
		void initTrees(int WORLD_SIZE,  CraftWorld *world, PerlinModule* perlin, int seed);
		void initGreatTrees(int WORLD_SIZE,  CraftWorld *world);
		void initPumpkins(int WORLD_SIZE,  CraftWorld *world);

		void initFlowers(int WORLD_SIZE, CraftWorld *world);
		void initGrass(int WORLD_SIZE, CraftWorld *world);
		void initOtherVegetation(int WORLD_SIZE, CraftWorld *world);

		void initLavaPools(int WORLD_SIZE, CraftWorld *world);
		void initBiome(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed);

		void initWaterAndCanes(int WORLD_SIZE, CraftWorld *world);
		void initBedrock(int WORLD_SIZE, CraftWorld *world);
        void initBeachSand(int WORLD_SIZE, CraftWorld *world);

        void initErosion(int WORLD_SIZE, CraftWorld *world);
        void initIron(int WORLD_SIZE, CraftWorld *world);
		void initCoal(int WORLD_SIZE, CraftWorld *world);
		void initGold(int WORLD_SIZE, CraftWorld *world);
		void initRedStone(int WORLD_SIZE, CraftWorld *world);
		void initDiamond(int WORLD_SIZE, CraftWorld *world);
		void initLapis(int WORLD_SIZE, CraftWorld *world);

		void initDungeons(int WORLD_SIZE, CraftWorld *world);

        void initClay(int WORLD_SIZE, CraftWorld *world);
		void initDirt(int WORLD_SIZE, CraftWorld *world);
		void initLava(int WORLD_SIZE, CraftWorld *world);

        int octaves;
        int frequency;
        int scale;
        int gain;
        int lacunarity;
        int exponent;
        int multiplier;
        int offset;
};

#endif
