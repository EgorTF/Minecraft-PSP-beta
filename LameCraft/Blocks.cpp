#include "Blocks.h"



GrassBlock::GrassBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    solid = true;
    editable = true;
	transparent = false;
	allowLight = false;

	soundType = 0;
	loot = 2;
	material = 3;
	update = 1;

	name = "Grass";
}

block_t GrassBlock::getID(){ return 1;}

DirtBlock::DirtBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 2;
    leftPlane_y = 0;

    rightPlane_x = 2;
    rightPlane_y = 0;

    botPlane_x = 2;
    botPlane_y = 0;

    forPlane_x = 2;
    forPlane_y = 0;

    solid = true;
	editable = true;
	transparent = false;
	allowLight = false;

	soundType = 1;
	loot = 2;
	material = 3;
	update = 1;

	name = "Dirt";
}

block_t DirtBlock::getID(){ return 2;}


RockBlock::RockBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 0;

    downPlane_x = 1;
    downPlane_y = 0;

    leftPlane_x = 1;
    leftPlane_y = 0;

    rightPlane_x = 1;
    rightPlane_y = 0;

    botPlane_x = 1;
    botPlane_y = 0;

    forPlane_x = 1;
    forPlane_y = 0;

    solid = true;
	editable = true;
	transparent = false;
	allowLight = false;

	soundType = 2;
	loot = 36;
	material = 2;
	update = 0;
	refraction = 3;

	name = "Stone";
}

block_t RockBlock::getID(){ return 3;}


WaterBlock::WaterBlock():BaseBlock()
{
    upPlane_x = 14;
    upPlane_y = 15;

    downPlane_x = 14;
    downPlane_y = 15;

    leftPlane_x = 14;
    leftPlane_y = 15;

    rightPlane_x = 14;
    rightPlane_y = 15;

    botPlane_x = 14;
    botPlane_y = 15;

    forPlane_x = 14;
    forPlane_y = 15;

	editable = false;
	transparent = true;
    solid = false;

    soundType = -1;
    blockModel = 5;
    allowLight = true;
    refraction = 1;

    name = "Water Block";
}

block_t WaterBlock::getID(){ return 4;}

GoldBlock::GoldBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 2;

    downPlane_x = 0;
    downPlane_y = 2;

    leftPlane_x = 0;
    leftPlane_y = 2;

    rightPlane_x = 0;
    rightPlane_y = 2;

    botPlane_x = 0;
    botPlane_y = 2;

    forPlane_x = 0;
    forPlane_y = 2;

	editable = true;
	transparent = false;
    solid = true;

	loot = 5;
	material = 2;
    soundType = 2;
	furnItem = 280;

	name = "Gold Block";
}

block_t GoldBlock::getID(){ return 5;}

LadderBlock::LadderBlock():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 5;

    downPlane_x = 3;
    downPlane_y = 5;

    leftPlane_x = 3;
    leftPlane_y = 5;

    rightPlane_x = 3;
    rightPlane_y = 5;

    botPlane_x = 3;
    botPlane_y = 5;

    forPlane_x = 3;
    forPlane_y = 5;
	editable = true;
	transparent = true;
	soundType = 3;

	loot = 6;
	material = 1;
	solid = true;
	allowLight = true;

	name = "Ladder Block";
}
block_t LadderBlock::getID(){ return 6;}


SandBlock::SandBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 1;

    downPlane_x = 2;
    downPlane_y = 1;

    leftPlane_x = 2;
    leftPlane_y = 1;

    rightPlane_x = 2;
    rightPlane_y = 1;

    botPlane_x = 2;
    botPlane_y = 1;

    forPlane_x = 2;
    forPlane_y = 1;

	editable = true;
	transparent = false;
	soundType = 5;

	loot = 7;
	material = 3;
	update = 1;
	solid = true;

	furnItem = 40;

	name = "Sand";
}
block_t SandBlock::getID(){ return 7;}


WoodBlock::WoodBlock():BaseBlock()
{
    upPlane_x = 5;
    upPlane_y = 1;

    downPlane_x = 5;
    downPlane_y = 1;

    leftPlane_x = 4;
    leftPlane_y = 1;

    rightPlane_x = 4;
    rightPlane_y = 1;

    botPlane_x = 4;
    botPlane_y = 1;

    forPlane_x = 4;
    forPlane_y = 1;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 8;
	material = 1;
	solid = true;

	furnItem = 277;

	name = "Wood";
}
block_t WoodBlock::getID(){ return 8;}

LeavesBlock::LeavesBlock():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 3;

    downPlane_x = 4;
    downPlane_y = 3;

    leftPlane_x = 4;
    leftPlane_y = 3;

    rightPlane_x = 4;
    rightPlane_y = 3;

    botPlane_x = 4;
    botPlane_y = 3;

    forPlane_x = 4;
    forPlane_y = 3;

	editable = true;
	allowLight = true;
	transparent = 1;
	soundType = 0;
	blockModel = 5;

	loot = 9;
	material = 4;
	solid = true;
	refraction = 1;

	name = "Leaves";
}
block_t LeavesBlock::getID(){ return 9;}


BlackWoolBlock::BlackWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 7;

    downPlane_x = 1;
    downPlane_y = 7;

    leftPlane_x = 1;
    leftPlane_y = 7;

    rightPlane_x = 1;
    rightPlane_y = 7;

    botPlane_x = 1;
    botPlane_y = 7;

    forPlane_x = 1;
    forPlane_y = 7;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 10;
	material = 4;
	solid = true;

	name = "Black Wool";
}
block_t BlackWoolBlock::getID(){ return 10;}


GrayWoolBlock::GrayWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 7;

    downPlane_x = 2;
    downPlane_y = 7;

    leftPlane_x = 2;
    leftPlane_y = 7;

    rightPlane_x = 2;
    rightPlane_y = 7;

    botPlane_x = 2;
    botPlane_y = 7;

    forPlane_x = 2;
    forPlane_y = 7;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 11;
	solid = true;

	name = "Gray Wool";
}
block_t GrayWoolBlock::getID(){ return 11;}


RedWoolBlock::RedWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 8;

    downPlane_x = 1;
    downPlane_y = 8;

    leftPlane_x = 1;
    leftPlane_y = 8;

    rightPlane_x = 1;
    rightPlane_y = 8;

    botPlane_x = 1;
    botPlane_y = 8;

    forPlane_x = 1;
    forPlane_y = 8;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 12;
	solid = true;

	name = "Red Wool";
}
block_t RedWoolBlock::getID(){ return 12;}


PinkWoolBlock::PinkWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 8;

    downPlane_x = 2;
    downPlane_y = 8;

    leftPlane_x = 2;
    leftPlane_y = 8;

    rightPlane_x = 2;
    rightPlane_y = 8;

    botPlane_x = 2;
    botPlane_y = 8;

    forPlane_x = 2;
    forPlane_y = 8;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 13;
	solid = true;

	name = "Pink Wool";
}
block_t PinkWoolBlock::getID(){ return 13;}


DarkGreenWoolBlock::DarkGreenWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 9;

    downPlane_x = 1;
    downPlane_y = 9;

    leftPlane_x = 1;
    leftPlane_y = 9;

    rightPlane_x = 1;
    rightPlane_y = 9;

    botPlane_x = 1;
    botPlane_y = 9;

    forPlane_x = 1;
    forPlane_y = 9;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 14;
	solid = true;

	name = "Dark Green Wool";
}
block_t DarkGreenWoolBlock::getID(){ return 14;}


GreenWoolBlock::GreenWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 9;

    downPlane_x = 2;
    downPlane_y = 9;

    leftPlane_x = 2;
    leftPlane_y = 9;

    rightPlane_x = 2;
    rightPlane_y = 9;

    botPlane_x = 2;
    botPlane_y = 9;

    forPlane_x = 2;
    forPlane_y = 9;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 15;
	solid = true;

	name = "Green Wool";
}
block_t GreenWoolBlock::getID(){ return 15;}



BrownWoolBlock::BrownWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 10;

    downPlane_x = 1;
    downPlane_y = 10;

    leftPlane_x = 1;
    leftPlane_y = 10;

    rightPlane_x = 1;
    rightPlane_y = 10;

    botPlane_x = 1;
    botPlane_y = 10;

    forPlane_x = 1;
    forPlane_y = 10;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 16;
	solid = true;

	name = "Brown Wool";
}
block_t BrownWoolBlock::getID(){ return 16;}


YellowWoolBlock::YellowWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 10;

    downPlane_x = 2;
    downPlane_y = 10;

    leftPlane_x = 2;
    leftPlane_y = 10;

    rightPlane_x = 2;
    rightPlane_y = 10;

    botPlane_x = 2;
    botPlane_y = 10;

    forPlane_x = 2;
    forPlane_y = 10;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 17;
	solid = true;

	name = "Yellow Wool";
}
block_t YellowWoolBlock::getID(){ return 17;}

BlueWoolBlock::BlueWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 11;

    downPlane_x = 1;
    downPlane_y = 11;

    leftPlane_x = 1;
    leftPlane_y = 11;

    rightPlane_x = 1;
    rightPlane_y = 11;

    botPlane_x = 1;
    botPlane_y = 11;

    forPlane_x = 1;
    forPlane_y = 11;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 18;
	solid = true;

	name = "Blue Wool";
}
block_t BlueWoolBlock::getID(){ return 18;}

LightBlueWoolBlock::LightBlueWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 11;

    downPlane_x = 2;
    downPlane_y = 11;

    leftPlane_x = 2;
    leftPlane_y = 11;

    rightPlane_x = 2;
    rightPlane_y = 11;

    botPlane_x = 2;
    botPlane_y = 11;

    forPlane_x = 2;
    forPlane_y = 11;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 19;
	solid = true;

	name = "LightBlue Wool";
}
block_t LightBlueWoolBlock::getID(){ return 19;}

VioletWoolBlock::VioletWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 12;

    downPlane_x = 1;
    downPlane_y = 12;

    leftPlane_x = 1;
    leftPlane_y = 12;

    rightPlane_x = 1;
    rightPlane_y = 12;

    botPlane_x = 1;
    botPlane_y = 12;

    forPlane_x = 1;
    forPlane_y = 12;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 20;
	solid = true;

	name = "Violet Wool";
}
block_t VioletWoolBlock::getID(){ return 20;}

PastelWoolBlock::PastelWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 12;

    downPlane_x = 2;
    downPlane_y = 12;

    leftPlane_x = 2;
    leftPlane_y = 12;

    rightPlane_x = 2;
    rightPlane_y = 12;

    botPlane_x = 2;
    botPlane_y = 12;

    forPlane_x = 2;
    forPlane_y = 12;

	editable = true;
	transparent = false;
	soundType = 3;
	loot = 21;
	solid = true;

	name = "Pastel Wool";
}
block_t PastelWoolBlock::getID(){ return 21;}

OrangeWoolBlock::OrangeWoolBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 13;

    downPlane_x = 2;
    downPlane_y = 13;

    leftPlane_x = 2;
    leftPlane_y = 13;

    rightPlane_x = 2;
    rightPlane_y = 13;

    botPlane_x = 2;
    botPlane_y = 13;

    forPlane_x = 2;
    forPlane_y = 13;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 22;
	solid = true;

	name = "Orange Wool";
}
block_t OrangeWoolBlock::getID(){ return 22;}

LightGrayWoolBlock::LightGrayWoolBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 14;

    downPlane_x = 1;
    downPlane_y = 14;

    leftPlane_x = 1;
    leftPlane_y = 14;

    rightPlane_x = 1;
    rightPlane_y = 14;

    botPlane_x = 1;
    botPlane_y = 14;

    forPlane_x = 1;
    forPlane_y = 14;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 23;
	solid = true;

	name = "LightGray Wool";
}
block_t LightGrayWoolBlock::getID(){ return 23;}

WhiteWoolBlock::WhiteWoolBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 4;

    downPlane_x = 0;
    downPlane_y = 4;

    leftPlane_x = 0;
    leftPlane_y = 4;

    rightPlane_x = 0;
    rightPlane_y = 4;

    botPlane_x = 0;
    botPlane_y = 4;

    forPlane_x = 0;
    forPlane_y = 4;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 24;
	solid = true;

	name = "White Wool";
}
block_t WhiteWoolBlock::getID(){ return 24;}

CactusBlock::CactusBlock():BaseBlock()
{
    upPlane_x = 5;
    upPlane_y = 4;

    downPlane_x = 7;
    downPlane_y = 4;

    leftPlane_x = 6;
    leftPlane_y = 4;

    rightPlane_x = 6;
    rightPlane_y = 4;

    botPlane_x = 6;
    botPlane_y = 4;

    forPlane_x = 6;
    forPlane_y = 4;

	editable = true;
	transparent = true;
    blockModel = 5;
	soundType = 3;

	loot = 25;
	material = 1;
	update = 1;
	solid = true;
	refraction = 1;
    allowLight = true;

    name = "Cactus";

    collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.5,0.4375f));
}
block_t CactusBlock::getID(){ return 25;}

SandStone::SandStone():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 11;

    downPlane_x = 0;
    downPlane_y = 13;

    leftPlane_x = 0;
    leftPlane_y = 12;

    rightPlane_x = 0;
    rightPlane_y = 12;

    botPlane_x = 0;
    botPlane_y = 12;

    forPlane_x = 0;
    forPlane_y = 12;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 26;
	solid = true;
	material = 2;

	name = "SandStone";
}
block_t SandStone::getID(){ return 26;}

BrickBlock::BrickBlock():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 27;
	material = 2;
	solid = true;

	name = "Bricks";
}
block_t BrickBlock::getID(){ return 27;}

CageBlock::CageBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 4;

    downPlane_x = 1;
    downPlane_y = 4;

    leftPlane_x = 1;
    leftPlane_y = 4;

    rightPlane_x = 1;
    rightPlane_y = 4;

    botPlane_x = 1;
    botPlane_y = 4;

    forPlane_x = 1;
    forPlane_y = 4;

	editable = true;
	transparent = true;
	soundType = 2;

	loot = 28;
	material = 2;
	solid = true;
	refraction = 1;
    allowLight = true;

    name = "Cage";
}
block_t CageBlock::getID(){ return 28;}

SnowBlock::SnowBlock():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 4;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 4;

    rightPlane_x = 4;
    rightPlane_y = 4;

    botPlane_x = 4;
    botPlane_y = 4;

    forPlane_x = 4;
    forPlane_y = 4;

	editable = true;
	transparent = false;
	soundType = 6;

	loot = 2;
	material = 3;
	solid = true;

	name = "Snow Block";
}
block_t SnowBlock::getID(){ return 29;}

DarkWoodBlock::DarkWoodBlock():BaseBlock()
{
    upPlane_x = 5;
    upPlane_y = 1;

    downPlane_x = 5;
    downPlane_y = 1;

    leftPlane_x = 4;
    leftPlane_y = 7;

    rightPlane_x = 4;
    rightPlane_y = 7;

    botPlane_x = 4;
    botPlane_y = 7;

    forPlane_x = 4;
    forPlane_y = 7;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 30;
	material = 1;
	solid = true;

	name = "Dark Wood";
}
block_t DarkWoodBlock::getID(){ return 30;}

WhiteWoodBlock::WhiteWoodBlock():BaseBlock()
{
    upPlane_x = 5;
    upPlane_y = 1;

    downPlane_x = 5;
    downPlane_y = 1;

    leftPlane_x = 5;
    leftPlane_y = 7;

    rightPlane_x = 5;
    rightPlane_y = 7;

    botPlane_x = 5;
    botPlane_y = 7;

    forPlane_x = 5;
    forPlane_y = 7;

	editable = true;
	transparent = false;
	soundType = 3;

	loot = 31;
	material = 1;
	solid = true;

	furnItem = 277;

	name = "White Wood";
}
block_t WhiteWoodBlock::getID(){ return 31;}

IceBlock::IceBlock():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 4;

    downPlane_x = 3;
    downPlane_y = 4;

    leftPlane_x = 3;
    leftPlane_y = 4;

    rightPlane_x = 3;
    rightPlane_y = 4;

    botPlane_x = 3;
    botPlane_y = 4;

    forPlane_x = 3;
    forPlane_y = 4;

	editable = true;
	transparent = false;
	soundType = 2;
    material = 3;

	loot = -1;
	solid = true;
	refraction = 1;

	name = "Ice";
}
block_t IceBlock::getID(){ return 32;}

CaneBlock::CaneBlock():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 4;

    downPlane_x = 9;
    downPlane_y = 4;

    leftPlane_x = 9;
    leftPlane_y = 4;

    rightPlane_x = 9;
    rightPlane_y = 4;

    botPlane_x = 9;
    botPlane_y = 4;

    forPlane_x = 9;
    forPlane_y = 4;

	editable = true;
	transparent = true;
    blockModel = 3;
    allowLight = true;

    loot = 293;
    update = 1;
    solid = false;
    refraction = 0;

    name = "Cane";

    collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.5,0.4375f));
}
block_t CaneBlock::getID(){ return 33;}

Planks::Planks():BaseBlock() // planks
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

	editable = true;
	transparent = false;
	soundType = 3;

    loot = 34;
    material = 1;
    solid = true;

    name = "Planks";
}
block_t Planks::getID(){ return 34;}

ShelfBlock::ShelfBlock():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 2;

    rightPlane_x = 3;
    rightPlane_y = 2;

    botPlane_x = 3;
    botPlane_y = 2;

    forPlane_x = 3;
    forPlane_y = 2;

	editable = true;
	transparent = false;
	soundType = 3;

    loot = 35;
    solid = true;

    name = "Shelf";
}
block_t ShelfBlock::getID(){ return 35;}

CobbleStone::CobbleStone():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

	editable = true;
	transparent = false;
	soundType = 2;

    loot = 36;
    material = 2;
    solid = true;

    furnItem = 3;

    name = "Cobblestone";
}
block_t CobbleStone::getID(){ return 36;}

SpruceLeaves::SpruceLeaves():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 8;

    downPlane_x = 4;
    downPlane_y = 8;

    leftPlane_x = 4;
    leftPlane_y = 8;

    rightPlane_x = 4;
    rightPlane_y = 8;

    botPlane_x = 4;
    botPlane_y = 8;

    forPlane_x = 4;
    forPlane_y = 8;

	editable = true;
	allowLight = true;
	transparent = 1;
	soundType = 0;
	blockModel = 5;

	loot = 37;
	material = 4;
	solid = true;
	refraction = 1;

    name = "Spruce Leaves";
}
block_t SpruceLeaves::getID(){ return 37;}

BirchLeaves::BirchLeaves():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 6;

    downPlane_x = 4;
    downPlane_y = 6;

    leftPlane_x = 4;
    leftPlane_y = 6;

    rightPlane_x = 4;
    rightPlane_y = 6;

    botPlane_x = 4;
    botPlane_y = 6;

    forPlane_x = 4;
    forPlane_y = 6;

	editable = true;
	allowLight = true;
	transparent = 1;
	soundType = 0;
	blockModel = 5;

	loot = 38;
	material = 4;
	solid = true;
	refraction = 1;

    name = "Birch Leaves";
}
block_t BirchLeaves::getID(){ return 38;}

Sponge::Sponge():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 3;

    downPlane_x = 0;
    downPlane_y = 3;

    leftPlane_x = 0;
    leftPlane_y = 3;

    rightPlane_x = 0;
    rightPlane_y = 3;

    botPlane_x = 0;
    botPlane_y = 3;

    forPlane_x = 0;
    forPlane_y = 3;

	editable = true;
	transparent = false;
	soundType = 1;

    loot = 38;
    solid = true;

    name = "Sponge";
}
block_t Sponge::getID(){ return 39;}

GlassBlock::GlassBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 3;

    downPlane_x = 1;
    downPlane_y = 3;

    leftPlane_x = 1;
    leftPlane_y = 3;

    rightPlane_x = 1;
    rightPlane_y = 3;

    botPlane_x = 1;
    botPlane_y = 3;

    forPlane_x = 1;
    forPlane_y = 3;

	editable = true;
	transparent = true;
	soundType = 2;

    loot = -1;
    solid = true;
    allowLight = true;

    name = "Glass";
}
block_t GlassBlock::getID(){ return 40;}

IronOre::IronOre():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 2;

    downPlane_x = 1;
    downPlane_y = 2;

    leftPlane_x = 1;
    leftPlane_y = 2;

    rightPlane_x = 1;
    rightPlane_y = 2;

    botPlane_x = 1;
    botPlane_y = 2;

    forPlane_x = 1;
    forPlane_y = 2;

	editable = true;
	transparent = false;
	soundType = 2;

    loot = 41;
    material = 2;
    solid = true;

    furnItem = 278;

    name = "Iron Ore";
}
block_t IronOre::getID(){ return 41;}

CoalOre::CoalOre():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 2;

    downPlane_x = 2;
    downPlane_y = 2;

    leftPlane_x = 2;
    leftPlane_y = 2;

    rightPlane_x = 2;
    rightPlane_y = 2;

    botPlane_x = 2;
    botPlane_y = 2;

    forPlane_x = 2;
    forPlane_y = 2;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 277;
	material = 2;
	solid = true;

	furnItem = 277;

	name = "Coal Ore";
}
block_t CoalOre::getID(){ return 42;}

DiamondOre::DiamondOre():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 3;

    downPlane_x = 2;
    downPlane_y = 3;

    leftPlane_x = 2;
    leftPlane_y = 3;

    rightPlane_x = 2;
    rightPlane_y = 3;

    botPlane_x = 2;
    botPlane_y = 3;

    forPlane_x = 2;
    forPlane_y = 3;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 279;
	material = 2;
	solid = true;

	furnItem = 279;

	name = "Diamond Ore";
}
block_t DiamondOre::getID(){ return 43;}

RedstoneOre::RedstoneOre():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 3;

    downPlane_x = 3;
    downPlane_y = 3;

    leftPlane_x = 3;
    leftPlane_y = 3;

    rightPlane_x = 3;
    rightPlane_y = 3;

    botPlane_x = 3;
    botPlane_y = 3;

    forPlane_x = 3;
    forPlane_y = 3;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 44;
	material = 2;
	solid = true;

	furnItem = 44;
}
block_t RedstoneOre::getID(){ return 44;}

LapisOre::LapisOre():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 10;

    downPlane_x = 0;
    downPlane_y = 10;

    leftPlane_x = 0;
    leftPlane_y = 10;

    rightPlane_x = 0;
    rightPlane_y = 10;

    botPlane_x = 0;
    botPlane_y = 10;

    forPlane_x = 0;
    forPlane_y = 10;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 318;
	material = 2;
	solid = true;
}
block_t LapisOre::getID(){ return 45;}

Obsidian::Obsidian():BaseBlock()
{
    upPlane_x = 5;
    upPlane_y = 2;

    downPlane_x = 5;
    downPlane_y = 2;

    leftPlane_x = 5;
    leftPlane_y = 2;

    rightPlane_x = 5;
    rightPlane_y = 2;

    botPlane_x = 5;
    botPlane_y = 2;

    forPlane_x = 5;
    forPlane_y = 2;

	editable = true;
	transparent = false;
	soundType = 2;

	loot = 46;
	material = 5;
	solid = true;

	name = "Obsidian";
}
block_t Obsidian::getID(){ return 46;}

JackOLantern::JackOLantern():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 6;

    downPlane_x = 6;
    downPlane_y = 7;

    leftPlane_x = 6;
    leftPlane_y = 7;

    rightPlane_x = 6;
    rightPlane_y = 7;

    botPlane_x = 6;
    botPlane_y = 7;

    forPlane_x = 8;
    forPlane_y = 7;

	editable = true;
	transparent = false;
	soundType = 3;
	lightSource = true;
	solid = true;
	allowLight = true;

    name = "JackOLantern";
}
block_t JackOLantern::getID(){ return 47;}

Torch::Torch():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 5;

    downPlane_x = 0;
    downPlane_y = 5;

    leftPlane_x = 0;
    leftPlane_y = 5;

    rightPlane_x = 0;
    rightPlane_y = 5;

    botPlane_x = 0;
    botPlane_y = 5;

    forPlane_x = 0;
    forPlane_y = 5;

	editable = true;
	transparent = false;
	soundType = 2;
	lightSource = true;
    blockModel = 5;
    allowLight = true;

    loot = 308;
    solid = false;

    name = "Torch";

    collideBox = BoundingBox(Vector3(-0.25f,-0.25f,-0.25f),Vector3(0.25f,0.25f,0.25f));
}
block_t Torch::getID(){ return 48;}

Door1::Door1():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = true;
    material = 1;
    allowLight = true;

    name = "Door Block";
}
block_t Door1::getID(){ return 49;}

Door2::Door2():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = true;
    material = 1;
    allowLight = true;
}
block_t Door2::getID(){ return 50;}

Door3::Door3():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = true;
    material = 1;
    allowLight = true;

}
block_t Door3::getID(){ return 51;}

Door4::Door4():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = true;
    material = 1;
    allowLight = true;
}
block_t Door4::getID(){ return 52;}

Door5::Door5():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = false;
    material = 1;
    allowLight = true;
}
block_t Door5::getID(){ return 53;}

Door6::Door6():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = false;
    material = 1;
    allowLight = true;
}
block_t Door6::getID(){ return 54;}

Door7::Door7():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = false;
    material = 1;
    allowLight = true;
}
block_t Door7::getID(){ return 55;}

Door8::Door8():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = false;
    material = 1;
    allowLight = true;
}
block_t Door8::getID(){ return 56;}

Door9::Door9():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = true;
    material = 1;
    allowLight = true;
    refraction = 0;
}
block_t Door9::getID(){ return 57;}

Door10::Door10():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 6;

    downPlane_x = 1;
    downPlane_y = 6;

    leftPlane_x = 1;
    leftPlane_y = 6;

    rightPlane_x = 1;
    rightPlane_y = 6;

    botPlane_x = 1;
    botPlane_y = 6;

    forPlane_x = 1;
    forPlane_y = 6;

	editable = true;
	transparent = true;
	soundType = 2;
    blockModel = 5;

    loot = 306;
    solid = false;
    material = 1;
    allowLight = true;
    refraction = 0;
}
block_t Door10::getID(){ return 58;}

WoodenFence::WoodenFence():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

	editable = true;
	transparent = false;
    allowLight = true;
	solid = true;

    blockModel = 2;
	loot = 59;
	material = 1;
	refraction = 2;

	name = "Wooden Fence";

	collideBox = BoundingBox(Vector3(-0.125f,-0.5f,-0.125f),Vector3(0.125f,0.5,0.125f));
}
block_t WoodenFence::getID(){ return 59;}

CobbleStair1::CobbleStair1():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    solid = true;

    blockModel = 5;
    loot = 60;
    material = 1;
}
block_t CobbleStair1::getID(){ return 60;}

CobbleStair2::CobbleStair2():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    solid = true;

    blockModel = 5;
    loot = 60;
    material = 1;
}
block_t CobbleStair2::getID(){ return 61;}

CobbleStair3::CobbleStair3():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    solid = true;

    blockModel = 5;
    loot = 60;
    material = 1;
}
block_t CobbleStair3::getID(){ return 62;}

CobbleStair4::CobbleStair4():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    solid = true;

    blockModel = 5;
    loot = 60;
    material = 1;
}
block_t CobbleStair4::getID(){ return 63;}

Diamond::Diamond():BaseBlock()
{
    upPlane_x = 8;
    upPlane_y = 1;

    downPlane_x = 8;
    downPlane_y = 1;

    leftPlane_x = 8;
    leftPlane_y = 1;

    rightPlane_x = 8;
    rightPlane_y = 1;

    botPlane_x = 8;
    botPlane_y = 1;

    forPlane_x = 8;
    forPlane_y = 1;

	editable = true;
	transparent = false;

    loot = 64;
    material = 2;
    solid = true;
}
block_t Diamond::getID(){ return 64;}

Gold::Gold():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 1;

    downPlane_x = 7;
    downPlane_y = 1;

    leftPlane_x = 7;
    leftPlane_y = 1;

    rightPlane_x = 7;
    rightPlane_y = 1;

    botPlane_x = 7;
    botPlane_y = 1;

    forPlane_x = 7;
    forPlane_y = 1;

	editable = true;
	transparent = false;

    loot = 65;
    material = 2;
    solid = true;
}
block_t Gold::getID(){ return 65;}


Iron::Iron():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 1;

    downPlane_x = 6;
    downPlane_y = 1;

    leftPlane_x = 6;
    leftPlane_y = 1;

    rightPlane_x = 6;
    rightPlane_y = 1;

    botPlane_x = 6;
    botPlane_y = 1;

    forPlane_x = 6;
    forPlane_y = 1;

	editable = true;
	transparent = false;
	soundType = 2;

    loot = 66;
    material = 2;
    solid = true;
}
block_t Iron::getID(){ return 66;}

BrickStair1::BrickStair1():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 67;
    material = 1;
    solid = true;
}
block_t BrickStair1::getID(){ return 67;}

BrickStair2::BrickStair2():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 67;
    material = 1;
    solid = true;
}
block_t BrickStair2::getID(){ return 68;}

BrickStair3::BrickStair3():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 67;
    material = 1;
    solid = true;
}
block_t BrickStair3::getID(){ return 69;}

BrickStair4::BrickStair4():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 67;
    material = 1;
    solid = true;
}
block_t BrickStair4::getID(){ return 70;}

NoteBlock::NoteBlock():BaseBlock()
{
    upPlane_x = 15;
    upPlane_y = 6;

    downPlane_x = 14;
    downPlane_y = 6;

    leftPlane_x = 14;
    leftPlane_y = 6;

    rightPlane_x = 14;
    rightPlane_y = 6;

    botPlane_x = 14;
    botPlane_y = 6;

    forPlane_x = 14;
    forPlane_y = 6;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 71;
    solid = true;
}
block_t NoteBlock::getID(){ return 71;}

JukeBox::JukeBox():BaseBlock()
{
    upPlane_x = 11;
    upPlane_y = 4;

    downPlane_x = 10;
    downPlane_y = 4;

    leftPlane_x = 10;
    leftPlane_y = 4;

    rightPlane_x = 10;
    rightPlane_y = 4;

    botPlane_x = 10;
    botPlane_y = 4;

    forPlane_x = 10;
    forPlane_y = 4;

    editable = true;
    transparent = false;
    solid = true;
}
block_t JukeBox::getID(){ return 72;}


Pumpkin1::Pumpkin1():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 6;

    downPlane_x = 6;
    downPlane_y = 7;

    leftPlane_x = 7;
    leftPlane_y = 7;

    rightPlane_x = 6;
    rightPlane_y = 7;

    botPlane_x = 6;
    botPlane_y = 7;

    forPlane_x = 6;
    forPlane_y = 7;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 73;
    material = 1;
    solid = true;
}
block_t Pumpkin1::getID(){ return 73;}

Pumpkin2::Pumpkin2():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 6;

    downPlane_x = 6;
    downPlane_y = 7;

    leftPlane_x = 6;
    leftPlane_y = 7;

    rightPlane_x = 7;
    rightPlane_y = 7;

    botPlane_x = 6;
    botPlane_y = 7;

    forPlane_x = 6;
    forPlane_y = 7;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 73;
    material = 1;
    solid = true;
}
block_t Pumpkin2::getID(){ return 74;}

Pumpkin3::Pumpkin3():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 6;

    downPlane_x = 6;
    downPlane_y = 7;

    leftPlane_x = 6;
    leftPlane_y = 7;

    rightPlane_x = 6;
    rightPlane_y = 7;

    botPlane_x = 7;
    botPlane_y = 7;

    forPlane_x = 6;
    forPlane_y = 7;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 73;
    material = 1;
    solid = true;
}
block_t Pumpkin3::getID(){ return 75;}

Pumpkin4::Pumpkin4():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 6;

    downPlane_x = 6;
    downPlane_y = 7;

    leftPlane_x = 6;
    leftPlane_y = 7;

    rightPlane_x = 6;
    rightPlane_y = 7;

    botPlane_x = 6;
    botPlane_y = 7;

    forPlane_x = 7;
    forPlane_y = 7;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 73;
    material = 1;
    solid = true;
}
block_t Pumpkin4::getID(){ return 76;}

Mooshroom1::Mooshroom1():BaseBlock()
{
    upPlane_x = 12;
    upPlane_y = 1;

    downPlane_x = 12;
    downPlane_y = 1;

    leftPlane_x = 12;
    leftPlane_y = 1;

    rightPlane_x = 12;
    rightPlane_y = 1;

    botPlane_x = 12;
    botPlane_y = 1;

    forPlane_x = 12;
    forPlane_y = 1;

	editable = true;
	transparent = true;
    blockModel = 3;

    loot = 300;
    solid = false;
    update = 1;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t Mooshroom1::getID(){ return 77;}

Mooshroom2::Mooshroom2():BaseBlock()
{
    upPlane_x = 13;
    upPlane_y = 1;

    downPlane_x = 13;
    downPlane_y = 1;

    leftPlane_x = 13;
    leftPlane_y = 1;

    rightPlane_x = 13;
    rightPlane_y = 1;

    botPlane_x = 13;
    botPlane_y = 1;

    forPlane_x = 13;
    forPlane_y = 1;

	editable = true;
	transparent = true;
    blockModel = 3;

    loot = 301;
    solid = false;
    update = 1;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t Mooshroom2::getID(){ return 78;}

Soil::Soil():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 5;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 2;
    leftPlane_y = 0;

    rightPlane_x = 2;
    rightPlane_y = 0;

    botPlane_x = 2;
    botPlane_y = 0;

    forPlane_x = 2;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    soundType = 1;

    loot = 2;
    material = 3;
    update = 1;
    solid = true;
}
block_t Soil::getID(){ return 79;}

WateredSoil::WateredSoil():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 5;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 2;
    leftPlane_y = 0;

    rightPlane_x = 2;
    rightPlane_y = 0;

    botPlane_x = 2;
    botPlane_y = 0;

    forPlane_x = 2;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    soundType = 1;

    loot = 2;
    material = 3;
    update = 1;
    solid = true;
}
block_t WateredSoil::getID(){ return 80;}

MelonBlock::MelonBlock():BaseBlock()
{
    upPlane_x = 15;
    upPlane_y = 6;

    downPlane_x = 14;
    downPlane_y = 6;

    leftPlane_x = 14;
    leftPlane_y = 6;

    rightPlane_x = 14;
    rightPlane_y = 6;

    botPlane_x = 14;
    botPlane_y = 6;

    forPlane_x = 14;
    forPlane_y = 6;

    editable = true;
    transparent = false;
    soundType = 3;

    loot = 311;
    solid = true;
    material = 1;
}
block_t MelonBlock::getID(){ return 81;}

WoodenHalfBlock::WoodenHalfBlock():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 1;

    loot = 82;
    material = 1;

    solid = true;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,0,0.5f));
}
block_t WoodenHalfBlock::getID(){ return 82;}

CobbleHalfBlock::CobbleHalfBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 1;

    downPlane_x = 0;
    downPlane_y = 1;

    leftPlane_x = 0;
    leftPlane_y = 1;

    rightPlane_x = 0;
    rightPlane_y = 1;

    botPlane_x = 0;
    botPlane_y = 1;

    forPlane_x = 0;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    blockModel = 1;

    solid = true;
    loot = 83;
    material = 1;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,0,0.5f));
}
block_t CobbleHalfBlock::getID(){ return 83;}

BrickHalfBlock::BrickHalfBlock():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 0;

    downPlane_x = 7;
    downPlane_y = 0;

    leftPlane_x = 7;
    leftPlane_y = 0;

    rightPlane_x = 7;
    rightPlane_y = 0;

    botPlane_x = 7;
    botPlane_y = 0;

    forPlane_x = 7;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 1;;
    lightSource = false;
    allowLight = true;

    loot = 84;
    material = 1;
    solid = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,0,0.5f));
}
block_t BrickHalfBlock::getID(){ return 84;}

Slab::Slab():BaseBlock()
{
    upPlane_x = 6;
    upPlane_y = 0;

    downPlane_x = 6;
    downPlane_y = 0;

    leftPlane_x = 5;
    leftPlane_y = 0;

    rightPlane_x = 5;
    rightPlane_y = 0;

    botPlane_x = 5;
    botPlane_y = 0;

    forPlane_x = 5;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 1;
    lightSource = false;
    allowLight = true;

    loot = 85;
    material = 1;
    solid = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,0,0.5f));
}
block_t Slab::getID(){ return 85;}

StoneSandHalfBlock::StoneSandHalfBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 11;

    downPlane_x = 0;
    downPlane_y = 13;

    leftPlane_x = 0;
    leftPlane_y = 12;

    rightPlane_x = 0;
    rightPlane_y = 12;

    botPlane_x = 0;
    botPlane_y = 12;

    forPlane_x = 0;
    forPlane_y = 12;

    editable = true;
    transparent = false;
    blockModel = 1;
    lightSource = false;
    allowLight = true;

    loot = 86;
    material = 1;
    solid = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,0,0.5f));
}
block_t StoneSandHalfBlock::getID(){ return 86;}

Ladder1::Ladder1():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 5;

    downPlane_x = 3;
    downPlane_y = 5;

    leftPlane_x = 3;
    leftPlane_y = 5;

    rightPlane_x = 3;
    rightPlane_y = 5;

    botPlane_x = 3;
    botPlane_y = 5;

    forPlane_x = 3;
    forPlane_y = 5;

    blockModel = 5;

    refraction = 0;
    loot = 307;

    lightSource = false;
    solid = false;
    allowLight = true;
    editable = true;
    transparent = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5,-0.5f),Vector3(-0.375f,0.5f,0.5f));
}
block_t Ladder1::getID(){ return 87;}

Ladder2::Ladder2():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 5;

    downPlane_x = 3;
    downPlane_y = 5;

    leftPlane_x = 3;
    leftPlane_y = 5;

    rightPlane_x = 3;
    rightPlane_y = 5;

    botPlane_x = 3;
    botPlane_y = 5;

    forPlane_x = 3;
    forPlane_y = 5;

    blockModel = 5;

    refraction = 0;
    loot = 307;

    lightSource = false;
    solid = false;
    allowLight = true;
    editable = true;
    transparent = true;

    collideBox = BoundingBox(Vector3(0.375f,-0.5,-0.5f),Vector3(0.5f,0.5f,0.5f));
}
block_t Ladder2::getID(){ return 88;}

Ladder3::Ladder3():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 5;

    downPlane_x = 3;
    downPlane_y = 5;

    leftPlane_x = 3;
    leftPlane_y = 5;

    rightPlane_x = 3;
    rightPlane_y = 5;

    botPlane_x = 3;
    botPlane_y = 5;

    forPlane_x = 3;
    forPlane_y = 5;

    blockModel = 5;

    refraction = 0;
    loot = 307;

    lightSource = false;
    solid = false;
    allowLight = true;
    editable = true;
    transparent = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5,-0.5f),Vector3(0.5f,0.5f,-0.375f));
}
block_t Ladder3::getID(){ return 89;}

Ladder4::Ladder4():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 5;

    downPlane_x = 3;
    downPlane_y = 5;

    leftPlane_x = 3;
    leftPlane_y = 5;

    rightPlane_x = 3;
    rightPlane_y = 5;

    botPlane_x = 3;
    botPlane_y = 5;

    forPlane_x = 3;
    forPlane_y = 5;

    blockModel = 5;

    refraction = 0;
    loot = 307;

    lightSource = false;
    solid = false;
    allowLight = true;
    editable = true;
    transparent = true;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5,0.375f),Vector3(0.5f,0.5f,0.5f));
}
block_t Ladder4::getID(){ return 90;}

Cake::Cake():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;
    lightSource = false;

    solid = true;
    allowLight = true;
}
block_t Cake::getID(){ return 91;}

MossyCobblestone::MossyCobblestone():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 2;

    downPlane_x = 4;
    downPlane_y = 2;

    leftPlane_x = 4;
    leftPlane_y = 2;

    rightPlane_x = 4;
    rightPlane_y = 2;

    botPlane_x = 4;
    botPlane_y = 2;

    forPlane_x = 4;
    forPlane_y = 2;

	editable = true;
	transparent = false;
	soundType = 2;

    loot = 36;
    material = 2;
    solid = true;
}
block_t MossyCobblestone::getID(){ return 92;}

Snow2::Snow2():BaseBlock()
{
    upPlane_x = 2;
    upPlane_y = 4;

    downPlane_x = 2;
    downPlane_y = 4;

    leftPlane_x = 2;
    leftPlane_y = 4;

    rightPlane_x = 2;
    rightPlane_y = 4;

    botPlane_x = 2;
    botPlane_y = 4;

    forPlane_x = 2;
    forPlane_y = 4;

    editable = true;
    transparent = false;
    blockModel = 5;
    lightSource = false;
    allowLight = true;

    loot = 1;
    solid = false;
    refraction = 2;

    collideBox = BoundingBox(Vector3(-0.5f,-0.5,-0.5f),Vector3(0.5f,-0.375f,0.5f));
}
block_t Snow2::getID(){ return 93;}

ChestBlock1::ChestBlock1():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 1;

    downPlane_x = 9;
    downPlane_y = 1;

    leftPlane_x = 11;
    leftPlane_y = 1;

    rightPlane_x = 10;
    rightPlane_y = 1;

    botPlane_x = 10;
    botPlane_y = 1;

    forPlane_x = 10;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    blockModel = 5;
    lightSource = false;
    allowLight = true;

    solid = true;

    loot = 94;
    material = 1;
	refraction = 2;

	collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.375f,0.4375f));
}
block_t ChestBlock1::getID(){ return 94;}

ChestBlock2::ChestBlock2():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 1;

    downPlane_x = 9;
    downPlane_y = 1;

    leftPlane_x = 10;
    leftPlane_y = 1;

    rightPlane_x = 11;
    rightPlane_y = 1;

    botPlane_x = 10;
    botPlane_y = 1;

    forPlane_x = 10;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    lightSource = false;
    blockModel = 5;
    solid = true;
    allowLight = true;

    loot = 94;
    material = 1;
    refraction = 2;

    collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.375f,0.4375f));
}
block_t ChestBlock2::getID(){ return 95;}

ChestBlock3::ChestBlock3():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 1;

    downPlane_x = 9;
    downPlane_y = 1;

    leftPlane_x = 10;
    leftPlane_y = 1;

    rightPlane_x = 10;
    rightPlane_y = 1;

    botPlane_x = 11;
    botPlane_y = 1;

    forPlane_x = 10;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    lightSource = false;
    blockModel = 5;
    solid = true;
    allowLight = true;

    loot = 94;
    material = 1;
    refraction = 2;

    collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.375f,0.4375f));
}
block_t ChestBlock3::getID(){ return 96;}

ChestBlock4::ChestBlock4():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 1;

    downPlane_x = 9;
    downPlane_y = 1;

    leftPlane_x = 10;
    leftPlane_y = 1;

    rightPlane_x = 10;
    rightPlane_y = 1;

    botPlane_x = 10;
    botPlane_y = 1;

    forPlane_x = 11;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    lightSource = false;
    blockModel = 5;
    solid = true;
    allowLight = true;

    loot = 94;
    material = 1;
    refraction = 2;

    collideBox = BoundingBox(Vector3(-0.4375f,-0.5f,-0.4375f),Vector3(0.4375f,0.375f,0.4375f));
}
block_t ChestBlock4::getID(){ return 97;}

ChestLock::ChestLock():BaseBlock()
{
    upPlane_x = 8;
    upPlane_y = 2;

    downPlane_x = 8;
    downPlane_y = 2;

    leftPlane_x = 8;
    leftPlane_y = 2;

    rightPlane_x = 8;
    rightPlane_y = 2;

    botPlane_x = 8;
    botPlane_y = 2;

    forPlane_x = 8;
    forPlane_y = 2;
}
block_t ChestLock::getID(){ return 98;}

ClayBlock::ClayBlock():BaseBlock()
{
    upPlane_x = 8;
    upPlane_y = 4;

    downPlane_x = 8;
    downPlane_y = 4;

    leftPlane_x = 8;
    leftPlane_y = 4;

    rightPlane_x = 8;
    rightPlane_y = 4;

    botPlane_x = 8;
    botPlane_y = 4;

    forPlane_x = 8;
    forPlane_y = 4;

    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 1;

    loot = 283;
    material = 3;
    solid = true;
}
block_t ClayBlock::getID(){ return 99;}

Chest5::Chest5():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    solid = true;

    loot = 100;
    material = 1;
}
block_t Chest5::getID(){ return 100;}

LapisBlock::LapisBlock():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 9;

    downPlane_x = 0;
    downPlane_y = 9;

    leftPlane_x = 0;
    leftPlane_y = 9;

    rightPlane_x = 0;
    rightPlane_y = 9;

    botPlane_x = 0;
    botPlane_y = 9;

    forPlane_x = 0;
    forPlane_y = 9;


    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 101;
    material = 2;
}
block_t LapisBlock::getID(){ return 101;}

StoneBrick::StoneBrick():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 2;

    downPlane_x = 9;
    downPlane_y = 2;

    leftPlane_x = 9;
    leftPlane_y = 2;

    rightPlane_x = 9;
    rightPlane_y = 2;

    botPlane_x = 9;
    botPlane_y = 2;

    forPlane_x = 9;
    forPlane_y = 2;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 102;
    material = 2;
    furnItem = 103;
}
block_t StoneBrick::getID(){ return 102;}

CrackedStoneBrick::CrackedStoneBrick():BaseBlock()
{
    upPlane_x = 10;
    upPlane_y = 2;

    downPlane_x = 10;
    downPlane_y = 2;

    leftPlane_x = 10;
    leftPlane_y = 2;

    rightPlane_x = 10;
    rightPlane_y = 2;

    botPlane_x = 10;
    botPlane_y = 2;

    forPlane_x = 10;
    forPlane_y = 2;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 103;
    material = 2;

}
block_t CrackedStoneBrick::getID(){ return 103;}

CarvedStoneBrick::CarvedStoneBrick():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 3;

    downPlane_x = 9;
    downPlane_y = 3;

    leftPlane_x = 9;
    leftPlane_y = 3;

    rightPlane_x = 9;
    rightPlane_y = 3;

    botPlane_x = 9;
    botPlane_y = 3;

    forPlane_x = 9;
    forPlane_y = 3;

    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 2;

    loot = 104;
    material = 2;
    solid = true;
}
block_t CarvedStoneBrick::getID(){ return 104;}

CraftingTable::CraftingTable():BaseBlock()
{
    upPlane_x = 11;
    upPlane_y = 2;

    downPlane_x = 11;
    downPlane_y = 2;

    leftPlane_x = 12;
    leftPlane_y = 3;

    rightPlane_x = 11;
    rightPlane_y = 3;

    botPlane_x = 12;
    botPlane_y = 3;

    forPlane_x = 12;
    forPlane_y = 3;

    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 3;

    loot = 105;
    material = 1;
    solid = true;
}
block_t CraftingTable::getID(){ return 105;}

FurnaceOff::FurnaceOff():BaseBlock()
{
    upPlane_x = 14;
    upPlane_y = 3;

    downPlane_x = 14;
    downPlane_y = 3;

    leftPlane_x = 12;
    leftPlane_y = 2;

    rightPlane_x = 12;
    rightPlane_y = 2;

    botPlane_x = 12;
    botPlane_y = 2;

    forPlane_x = 12;
    forPlane_y = 2;

    editable = true;
    transparent = false;
    lightSource = false;

    loot = 106;
    material = 2;
    solid = true;
}
block_t FurnaceOff::getID(){ return 106;}

FurnaceOn::FurnaceOn():BaseBlock()
{
    upPlane_x = 14;
    upPlane_y = 3;

    downPlane_x = 14;
    downPlane_y = 3;

    leftPlane_x = 13;
    leftPlane_y = 3;

    rightPlane_x = 13;
    rightPlane_y = 3;

    botPlane_x = 13;
    botPlane_y = 3;

    forPlane_x = 13;
    forPlane_y = 3;

    editable = true;
    transparent = false;
    lightSource = false;

    loot = 106;
    material = 2;
    solid = true;
    lightSource = true;
}
block_t FurnaceOn::getID(){ return 107;}

HalfStoneBrick::HalfStoneBrick():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 2;

    downPlane_x = 9;
    downPlane_y = 2;

    leftPlane_x = 9;
    leftPlane_y = 2;

    rightPlane_x = 9;
    rightPlane_y = 2;

    botPlane_x = 9;
    botPlane_y = 2;

    forPlane_x = 9;
    forPlane_y = 2;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 106;
    material = 2;
    blockModel = 1;
}
block_t HalfStoneBrick::getID(){ return 108;}

Furnace6::Furnace6():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 106;
    material = 2;
}
block_t Furnace6::getID(){ return 109;}

TNT::TNT():BaseBlock()
{
    upPlane_x = 9;
    upPlane_y = 0;

    downPlane_x = 10;
    downPlane_y = 0;

    leftPlane_x = 8;
    leftPlane_y = 0;

    rightPlane_x = 8;
    rightPlane_y = 0;

    botPlane_x = 8;
    botPlane_y = 0;

    forPlane_x = 8;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t TNT::getID(){ return 110;}

Nuclear::Nuclear():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t Nuclear::getID(){ return 111;}

Lava::Lava():BaseBlock()
{
    upPlane_x = 15;
    upPlane_y = 15;

    downPlane_x = 15;
    downPlane_y = 15;

    leftPlane_x = 15;
    leftPlane_y = 15;

    rightPlane_x = 15;
    rightPlane_y = 15;

    botPlane_x = 15;
    botPlane_y = 15;

    forPlane_x = 15;
    forPlane_y = 15;

    editable = false;
	transparent = false;
	lightSource = true;
    allowLight = true;
    solid = false;
    animated = true;

	update = 1;
    blockModel = 5;
	soundType = 2;
}
block_t Lava::getID(){ return 112;}

Gravel::Gravel():BaseBlock()
{
    upPlane_x = 3;
    upPlane_y = 1;

    downPlane_x = 3;
    downPlane_y = 1;

    leftPlane_x = 3;
    leftPlane_y = 1;

    rightPlane_x = 3;
    rightPlane_y = 1;

    botPlane_x = 3;
    botPlane_y = 1;

    forPlane_x = 3;
    forPlane_y = 1;

    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 1;

    update = 1;
    solid = true;
    loot = 113;
}
block_t Gravel::getID(){ return 113;}

LavaStone::LavaStone():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t LavaStone::getID(){ return 114;}

LavaObsidian::LavaObsidian():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t LavaObsidian::getID(){ return 115;}

TallGrass::TallGrass():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

	editable = true;
	transparent = true;
    blockModel = 3;

    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t TallGrass::getID(){ return 116;}

Fern::Fern():BaseBlock()
{
    upPlane_x = 8;
    upPlane_y = 3;

    downPlane_x = 8;
    downPlane_y = 3;

    leftPlane_x = 8;
    leftPlane_y = 3;

    rightPlane_x = 8;
    rightPlane_y = 3;

    botPlane_x = 8;
    botPlane_y = 3;

    forPlane_x = 8;
    forPlane_y = 3;

	editable = true;
	transparent = true;
    blockModel = 3;

    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t Fern::getID(){ return 117;}

DrySapling::DrySapling():BaseBlock()
{
    upPlane_x = 7;
    upPlane_y = 3;

    downPlane_x = 7;
    downPlane_y = 3;

    leftPlane_x = 7;
    leftPlane_y = 3;

    rightPlane_x = 7;
    rightPlane_y = 3;

    botPlane_x = 7;
    botPlane_y = 3;

    forPlane_x = 7;
    forPlane_y = 3;

	editable = true;
	transparent = true;
    blockModel = 3;

    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t DrySapling::getID(){ return 118;}

Flower1::Flower1():BaseBlock()
{
    upPlane_x = 12;
    upPlane_y = 0;

    downPlane_x = 12;
    downPlane_y = 0;

    leftPlane_x = 12;
    leftPlane_y = 0;

    rightPlane_x = 12;
    rightPlane_y = 0;

    botPlane_x = 12;
    botPlane_y = 0;

    forPlane_x = 12;
    forPlane_y = 0;

	editable = true;
	transparent = true;
    blockModel = 3;

    loot = 294;
    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t Flower1::getID(){ return 119;}

Flower2::Flower2():BaseBlock()
{
    upPlane_x = 13;
    upPlane_y = 0;

    downPlane_x = 13;
    downPlane_y = 0;

    leftPlane_x = 13;
    leftPlane_y = 0;

    rightPlane_x = 13;
    rightPlane_y = 0;

    botPlane_x = 13;
    botPlane_y = 0;

    forPlane_x = 13;
    forPlane_y = 0;

	editable = true;
	transparent = true;
    blockModel = 3;

    loot = 295;
    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t Flower2::getID(){ return 120;}


OakSapling::OakSapling():BaseBlock()
{
    upPlane_x = 15;
    upPlane_y = 0;

    downPlane_x = 15;
    downPlane_y = 0;

    leftPlane_x = 15;
    leftPlane_y = 0;

    rightPlane_x = 15;
    rightPlane_y = 0;

    botPlane_x = 15;
    botPlane_y = 0;

    forPlane_x = 15;
    forPlane_y = 0;

    editable = true;
    transparent = true;
    blockModel = 3;

    loot = 296;
    update = true;
    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t OakSapling::getID(){ return 121;}

SpruceSapling::SpruceSapling():BaseBlock()
{
    upPlane_x = 14;
    upPlane_y = 0;

    downPlane_x = 14;
    downPlane_y = 0;

    leftPlane_x = 14;
    leftPlane_y = 0;

    rightPlane_x = 14;
    rightPlane_y = 0;

    botPlane_x = 14;
    botPlane_y = 0;

    forPlane_x = 14;
    forPlane_y = 0;

    editable = true;
    transparent = true;
    blockModel = 3;

    loot = 309;
    update = true;
    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t SpruceSapling::getID(){ return 122;}

BirchSapling::BirchSapling():BaseBlock()
{
    upPlane_x = 14;
    upPlane_y = 1;

    downPlane_x = 14;
    downPlane_y = 1;

    leftPlane_x = 14;
    leftPlane_y = 1;

    rightPlane_x = 14;
    rightPlane_y = 1;

    botPlane_x = 14;
    botPlane_y = 1;

    forPlane_x = 14;
    forPlane_y = 1;

    editable = true;
    transparent = true;
    blockModel = 3;

    loot = 310;
    update = true;
    solid = false;
    allowLight = true;
    refraction = 0;

    collideBox = BoundingBox(Vector3(-0.2f,-0.5f,-0.2f),Vector3(0.2f,0.35,0.2f));
}
block_t BirchSapling::getID(){ return 123;}

FreeBlock5::FreeBlock5():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    soundType = 3;

    material = 1;
    loot = 74;
    solid = true;

}
block_t FreeBlock5::getID(){ return 124;}

WoodenStair1::WoodenStair1():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 125;
    material = 1;
    solid = true;
}
block_t WoodenStair1::getID(){ return 125;}

WoodenStair2::WoodenStair2():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 125;
    material = 1;
    solid = true;
}
block_t WoodenStair2::getID(){ return 126;}

WoodenStair3::WoodenStair3():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 125;
    material = 1;
    solid = true;
}
block_t WoodenStair3::getID(){ return 127;}

WoodenStair4::WoodenStair4():BaseBlock()
{
    upPlane_x = 4;
    upPlane_y = 0;

    downPlane_x = 4;
    downPlane_y = 0;

    leftPlane_x = 4;
    leftPlane_y = 0;

    rightPlane_x = 4;
    rightPlane_y = 0;

    botPlane_x = 4;
    botPlane_y = 0;

    forPlane_x = 4;
    forPlane_y = 0;

    editable = true;
    transparent = false;
    blockModel = 5;

    loot = 125;
    material = 1;
    solid = true;
}
block_t WoodenStair4::getID(){ return 128;}

Marble::Marble():BaseBlock()
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    editable = true;
    transparent = false;

    loot = 128;
    material = 2;
    solid = true;
}
block_t Marble::getID(){ return 129;}

MelonPlant1::MelonPlant1():BaseBlock()
{
    upPlane_x = 10;
    upPlane_y = 6;

    downPlane_x = 10;
    downPlane_y = 6;

    leftPlane_x = 10;
    leftPlane_y = 6;

    rightPlane_x = 10;
    rightPlane_y = 6;

    botPlane_x = 10;
    botPlane_y = 6;

    forPlane_x = 10;
    forPlane_y = 6;

    editable = true;
    transparent = true;
    blockModel = 5;
    solid = false;

    update = 1;
}
block_t MelonPlant1::getID(){ return 130;}

MelonPlant2::MelonPlant2():BaseBlock()
{
    upPlane_x = 11;
    upPlane_y = 6;

    downPlane_x = 11;
    downPlane_y = 6;

    leftPlane_x = 11;
    leftPlane_y = 6;

    rightPlane_x = 11;
    rightPlane_y = 6;

    botPlane_x = 11;
    botPlane_y = 6;

    forPlane_x = 11;
    forPlane_y = 6;

    editable = true;
    transparent = true;
    blockModel = 5;
    solid = false;

    update = 1;
}
block_t MelonPlant2::getID(){ return 131;}

MelonPlant3::MelonPlant3():BaseBlock()
{
    upPlane_x = 12;
    upPlane_y = 6;

    downPlane_x = 12;
    downPlane_y = 6;

    leftPlane_x = 12;
    leftPlane_y = 6;

    rightPlane_x = 12;
    rightPlane_y = 6;

    botPlane_x = 12;
    botPlane_y = 6;

    forPlane_x = 12;
    forPlane_y = 6;

    editable = true;
    transparent = true;
    blockModel = 5;
    solid = false;

    update = 1;
}
block_t MelonPlant3::getID(){ return 132;}

MelonPlant4::MelonPlant4():BaseBlock()
{
    upPlane_x = 13;
    upPlane_y = 6;

    downPlane_x = 13;
    downPlane_y = 6;

    leftPlane_x = 13;
    leftPlane_y = 6;

    rightPlane_x = 13;
    rightPlane_y = 6;

    botPlane_x = 13;
    botPlane_y = 6;

    forPlane_x = 13;
    forPlane_y = 6;

    editable = true;
    transparent = true;
    blockModel = 5;
    solid = false;

    update = 1;
}
block_t MelonPlant4::getID(){ return 133;}


WheatBlock1::WheatBlock1():BaseBlock()
{
    upPlane_x = 8;
    upPlane_y = 5;

    downPlane_x = 8;
    downPlane_y = 5;

    leftPlane_x = 8;
    leftPlane_y = 5;

    rightPlane_x = 8;
    rightPlane_y = 5;

    botPlane_x = 8;
    botPlane_y = 5;

    forPlane_x = 8;
    forPlane_y = 5;

	editable = true;
	transparent = true;
    blockModel = 4;

    loot = 286;
    update = 1;
    solid = false;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.45f,-0.5f,-0.45f),Vector3(0.45f,0.5,0.45f));
}
block_t WheatBlock1::getID(){ return 134;}

WheatBlock2::WheatBlock2():BaseBlock()
{
    upPlane_x = 10;
    upPlane_y = 5;

    downPlane_x = 10;
    downPlane_y = 5;

    leftPlane_x = 10;
    leftPlane_y = 5;

    rightPlane_x = 10;
    rightPlane_y = 5;

    botPlane_x = 10;
    botPlane_y = 5;

    forPlane_x = 10;
    forPlane_y = 5;

	editable = true;
	transparent = true;
    blockModel = 4;

    loot = 286;
    update = 1;
    solid = false;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.45f,-0.5f,-0.45f),Vector3(0.45f,0.5,0.45f));
}
block_t WheatBlock2::getID(){ return 135;}

WheatBlock3::WheatBlock3():BaseBlock()
{
    upPlane_x = 13;
    upPlane_y = 5;

    downPlane_x = 13;
    downPlane_y = 5;

    leftPlane_x = 13;
    leftPlane_y = 5;

    rightPlane_x = 13;
    rightPlane_y = 5;

    botPlane_x = 13;
    botPlane_y = 5;

    forPlane_x = 13;
    forPlane_y = 5;

	editable = true;
	transparent = true;
    blockModel = 4;

    loot = 286;
    update = 1;
    solid = false;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.45f,-0.5f,-0.45f),Vector3(0.45f,0.5,0.45f));
}
block_t WheatBlock3::getID(){ return 136;}

WheatBlock4::WheatBlock4():BaseBlock()
{
    upPlane_x = 15;
    upPlane_y = 5;

    downPlane_x = 15;
    downPlane_y = 5;

    leftPlane_x = 15;
    leftPlane_y = 5;

    rightPlane_x = 15;
    rightPlane_y = 5;

    botPlane_x = 15;
    botPlane_y = 5;

    forPlane_x = 15;
    forPlane_y = 5;

	editable = true;
	transparent = true;
    blockModel = 4;

    loot = 287;
    update = 1;
    solid = false;
    allowLight = true;

    collideBox = BoundingBox(Vector3(-0.45f,-0.5f,-0.45f),Vector3(0.45f,0.5,0.45f));
}
block_t WheatBlock4::getID(){ return 137;}

FreeBlock3::FreeBlock3():BaseBlock()//низ постели
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    solid = true;
    editable = true;
	transparent = false;
	allowLight = false;


	blockModel = 1;

	soundType = 0;
	loot = 2;
	material = 3;
	update = 1;
}
block_t FreeBlock3::getID(){ return 138;}

FreeBlock4::FreeBlock4():BaseBlock()//Верх постели
{
    upPlane_x = 0;
    upPlane_y = 0;

    downPlane_x = 2;
    downPlane_y = 0;

    leftPlane_x = 3;
    leftPlane_y = 0;

    rightPlane_x = 3;
    rightPlane_y = 0;

    botPlane_x = 3;
    botPlane_y = 0;

    forPlane_x = 3;
    forPlane_y = 0;

    solid = true;
    editable = true;
	transparent = false;
	allowLight = false;

	blockModel = 1;

	soundType = 0;
	loot = 2;
	material = 3;
	update = 1;
}
block_t FreeBlock4::getID(){ return 139;}

WorldSky::WorldSky():BaseBlock()
{
    transparent = false;
    blockModel = 5;

}
block_t WorldSky::getID(){ return 140;}

Cloud::Cloud():BaseBlock()
{

    transparent = true;
    blockModel = 5;

}
block_t Cloud::getID(){ return 141;}

IronBlock::IronBlock():BaseBlock()
{
    upPlane_x = 1;
    upPlane_y = 1;

    downPlane_x = 1;
    downPlane_y = 1;

    leftPlane_x = 1;
    leftPlane_y = 1;

    rightPlane_x = 1;
    rightPlane_y = 1;

    botPlane_x = 1;
    botPlane_y = 1;

    forPlane_x = 1;
    forPlane_y = 1;

	editable = true;;
	transparent = false;
	soundType = 2;
	solid = true;
	material = 6;
}
block_t IronBlock::getID(){ return 142;}
