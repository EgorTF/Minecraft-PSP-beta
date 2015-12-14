#ifndef BASEITEM_H
#define BASEITEM_H

#include <Aurora/Graphics/Vertex.h>
#include <stdlib.h>
#include <string>

using namespace Aurora::Graphics;

typedef unsigned short item_t;

class BaseItem
{
public:
	char textureRow;
	char plane;

	short furnItem;
    short durabilityPoints;

	short points;
	short addPoints;

	char itemType; // "D" - default, "T" - tool, "F" - food, "H" - helmet, "C" - chestplate, "L" - leggings, "B" - boots

	TexturesPSPVertex *vertices;
	TexturesPSPVertex *addVertices;
	TexturesPSPVertex *dropVertices;

	BaseItem();
	virtual ~BaseItem();

	static item_t getBaseID();
    std::string name;
};

#endif
