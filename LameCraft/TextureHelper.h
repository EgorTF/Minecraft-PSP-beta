#ifndef TEXTUREHELPER_H_
#define TEXTUREHELPER_H_

#include <string>

class TextureHelper
{
private:

	std::string defaulPatch;
	std::string defaultFolder;
	std::string fileName;

public:

	enum Textures
	{
         Genesis,
		 Logo,
		 Utils,
		 Dirt,
		 Terrain1,
		 WaterAnimation,
		 LavaAnimation,
         Items1,
		 Blue,
		 Sun,
         Moon,
         SnowBall3,
         Zombie3,
         Steve,
		 lameCraft,
		 Buttons,
		 Load,
		 SubLoad,
		 Red,
		 Black,
         clouds1,
         inv,
         invCreative,
         crt,
         cht,
         fur,
         cursor,
         furFire,
         furArrow,
         leatherArmor1,
         leatherArmor2,
         chainmailArmor1,
         chainmailArmor2,
         ironArmor1,
         ironArmor2,
         diamondArmor1,
         diamondArmor2,
         goldenArmor1,
         goldenArmor2,
         cowTexture,
	};
    std::string texturePatch;

	static TextureHelper m_TextureHelper;
	static TextureHelper* Instance();


	TextureHelper();
	~TextureHelper();

	int GetTexture(Textures texture);
    void Init();
    void FastRemoveTexture(std::string name);
    void FastLoadTexture(std::string name);
	void SetTextureFolderName(std::string name);
	void SetTexturePack(std::string name);
};

#endif
