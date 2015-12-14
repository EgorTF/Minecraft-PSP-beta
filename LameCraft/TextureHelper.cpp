#include "TextureHelper.h"
#include <Aurora/Graphics/RenderManager.h>

TextureHelper::TextureHelper()
{
	defaulPatch = "Assets/Textures/";
	defaultFolder = "Default [16x]/";
	texturePatch = "Assets/Textures/Default [16x]/";
}

TextureHelper::~TextureHelper()
{

}

void TextureHelper::Init()
{
    FastLoadTexture("title/genesis.png");
    FastLoadTexture("environment/moon.png");
    FastLoadTexture("hud/utils.png");
    FastLoadTexture("title/dirt.png");
    FastLoadTexture("terrain.png");
    FastLoadTexture("water_still.png");
    FastLoadTexture("lava_still.png");
    FastLoadTexture("items.png");
    FastLoadTexture("hud/blue.png");
    FastLoadTexture("environment/sun.png");
    FastLoadTexture("environment/moon.png");
    FastLoadTexture("entity/snowball.png");
    FastLoadTexture("entity/zombie.png");
    FastLoadTexture("entity/steve.png");
    FastLoadTexture("title/logo.png");
    FastLoadTexture("title/menu_elements.png");
    FastLoadTexture("title/load.png");
    FastLoadTexture("title/subload.png");
    FastLoadTexture("hud/red.png");
    FastLoadTexture("hud/black.png");
    FastLoadTexture("environment/clouds.png");
    FastLoadTexture("gui/inventory1.png");
    FastLoadTexture("gui/inventory_creative.png");
    FastLoadTexture("gui/crafting_table.png");
    FastLoadTexture("gui/chest.png");
    FastLoadTexture("gui/furnace.png");
    FastLoadTexture("gui/cursor.png");
    FastLoadTexture("gui/fire.png");
	FastLoadTexture("gui/arrow.png");
	FastLoadTexture("armor/cloth_1.png");
	FastLoadTexture("armor/cloth_2.png");
	FastLoadTexture("armor/chain_1.png");
	FastLoadTexture("armor/chain_2.png");
	FastLoadTexture("armor/iron_1.png");
	FastLoadTexture("armor/iron_2.png");
	FastLoadTexture("armor/diamond_1.png");
	FastLoadTexture("armor/diamond_2.png");
	FastLoadTexture("armor/gold_1.png");
	FastLoadTexture("armor/gold_2.png");
	FastLoadTexture("entity/cow.png");
}

int TextureHelper::GetTexture(Textures texture)
{
	switch(texture)
	{
		case Genesis:
		{
			fileName = texturePatch + "title/genesis.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Logo:
		{
			fileName = texturePatch + "environment/moon.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Utils:
		{
			fileName = texturePatch + "hud/utils.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Dirt:
		{
			fileName = texturePatch + "title/dirt.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Terrain1:
		{
			fileName = texturePatch + "terrain.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case WaterAnimation:
		{
			fileName = texturePatch + "water_still.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case LavaAnimation:
		{
			fileName = texturePatch + "lava_still.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Items1:
		{
			fileName = texturePatch + "items.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Blue:
		{
			fileName = texturePatch + "hud/blue.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Sun:
		{
			fileName = texturePatch + "environment/sun.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Moon:
		{
			fileName = texturePatch + "environment/moon.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case SnowBall3:
		{
			fileName = texturePatch + "entity/snowball.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Zombie3:
		{
			fileName = texturePatch + "entity/zombie.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Steve:
		{
			fileName = texturePatch + "entity/steve.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case lameCraft:
		{
			fileName = texturePatch + "title/logo.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Buttons:
		{
			fileName = texturePatch + "title/menu_elements.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Load:
		{
			fileName = texturePatch + "title/load.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case SubLoad:
		{
			fileName = texturePatch + "title/subload.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Red:
		{
			fileName = texturePatch + "hud/red.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Black:
		{
			fileName = texturePatch + "hud/black.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case clouds1:
		{
			fileName = texturePatch + "environment/clouds.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case inv:
		{
			fileName = texturePatch + "gui/inventory1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case invCreative:
		{
			fileName = texturePatch + "gui/inventory_creative.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case crt:
		{
			fileName = texturePatch + "gui/crafting_table.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case cht:
		{
			fileName = texturePatch + "gui/chest.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case fur:
		{
			fileName = texturePatch + "gui/furnace.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case cursor:
		{
			fileName = texturePatch + "gui/cursor.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case furFire:
		{
			fileName = texturePatch + "gui/fire.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case furArrow:
		{
			fileName = texturePatch + "gui/arrow.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case leatherArmor1:
		{
			fileName = texturePatch + "armor/cloth_1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case leatherArmor2:
		{
			fileName = texturePatch + "armor/cloth_2.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case chainmailArmor1:
		{
			fileName = texturePatch + "armor/chain_1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case chainmailArmor2:
		{
			fileName = texturePatch + "armor/chain_2.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case ironArmor1:
		{
			fileName = texturePatch + "armor/iron_1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case ironArmor2:
		{
			fileName = texturePatch + "armor/iron_2.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case diamondArmor1:
		{
			fileName = texturePatch + "armor/diamond_1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case diamondArmor2:
		{
			fileName = texturePatch + "armor/diamond_2.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case goldenArmor1:
		{
			fileName = texturePatch + "armor/gold_1.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case goldenArmor2:
		{
			fileName = texturePatch + "armor/gold_2.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case cowTexture:
		{
			fileName = texturePatch + "entity/cow.png";
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
	}

	return 0;
}

void TextureHelper::SetTexturePack(std::string name)
{
    TextureManager::Instance()->RemoveTexture2();

	SetTextureFolderName(name+"/");

    FastLoadTexture("environment/moon.png");
    FastLoadTexture("hud/utils.png");
    FastLoadTexture("title/dirt.png");
    FastLoadTexture("terrain.png");
    FastLoadTexture("water_still.png");
    FastLoadTexture("lava_still.png");
    FastLoadTexture("items.png");
    FastLoadTexture("hud/blue.png");
    FastLoadTexture("environment/sun.png");
    FastLoadTexture("environment/moon.png");
    FastLoadTexture("entity/snowball.png");
    FastLoadTexture("entity/zombie.png");
    FastLoadTexture("entity/steve.png");
    FastLoadTexture("title/logo.png");
    FastLoadTexture("title/menu_elements.png");
    FastLoadTexture("title/load.png");
    FastLoadTexture("title/subload.png");
    FastLoadTexture("hud/red.png");
    FastLoadTexture("hud/black.png");
    FastLoadTexture("environment/clouds.png");
    FastLoadTexture("gui/inventory1.png");
    FastLoadTexture("gui/inventory_creative.png");
    FastLoadTexture("gui/crafting_table.png");
    FastLoadTexture("gui/chest.png");
    FastLoadTexture("gui/furnace.png");
    FastLoadTexture("gui/cursor.png");
    FastLoadTexture("gui/fire.png");
	FastLoadTexture("gui/arrow.png");
	FastLoadTexture("armor/cloth_1.png");
	FastLoadTexture("armor/cloth_2.png");
	FastLoadTexture("armor/chain_1.png");
	FastLoadTexture("armor/chain_2.png");
	FastLoadTexture("armor/iron_1.png");
	FastLoadTexture("armor/iron_2.png");
	FastLoadTexture("armor/diamond_1.png");
	FastLoadTexture("armor/diamond_2.png");
	FastLoadTexture("armor/gold_1.png");
	FastLoadTexture("armor/gold_2.png");
	FastLoadTexture("entity/cow.png");
}

void TextureHelper::FastRemoveTexture(std::string name)
{

}

void TextureHelper::FastLoadTexture(std::string name)
{
    std::string endName = texturePatch+name;
    TextureManager::Instance()->LoadTexture(endName);
}

void TextureHelper::SetTextureFolderName(std::string name)
{
	defaultFolder = name;
	texturePatch = defaulPatch + defaultFolder;
}

TextureHelper TextureHelper::m_TextureHelper;

TextureHelper* TextureHelper::Instance()
{
	return &m_TextureHelper;
}
