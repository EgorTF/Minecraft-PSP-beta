#include "LoadingScreen.h"
#include "TextureHelper.h"
#include <pspthreadman.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Graphics/Sprite.h>

// font vars
#define default_size 0.347
#define default_big_size 0.687

using namespace Aurora::Graphics;

Sprite* backSprite;
Sprite* loadSprite;
Sprite* subLoadSprite;

int LoadingScreen::state = 0;
int LoadingScreen::state2 = 0;

LoadingScreen::LoadingScreen()
{
	// the loadingscreen is loaded as a thread
	thid_ = sceKernelCreateThread("LoadingThread", RunLoadingScreen, 0x18, 0x10000, THREAD_ATTR_VFPU|THREAD_ATTR_USER, NULL);
	// start the thread
	sceKernelStartThread(thid_, 0, 0);
}


void LoadingScreen::KillLoadingScreen()
{
	// shut down the loading screen again.
	sceKernelTerminateDeleteThread(thid_);
	// free the mem space of the images
	delete backSprite;
	delete loadSprite;
	delete subLoadSprite;
}


int LoadingScreen::RunLoadingScreen(SceSize args, void *argp)
{
	// load up the images
	backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,32,32);
	backSprite->Scale(2,2);

    loadSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Load),0,0,16,8);
	loadSprite->Scale(1,1);

    subLoadSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::SubLoad),0,0,16,8);
	subLoadSprite->Scale(1,1);


    int tip = rand() % 7;
	float loadingProcess = 0.0f;

	// start the render loop
	while(1)
	{
		RenderManager::InstancePtr()->StartFrame(1,1,1);

		sceGuDisable(GU_DEPTH_TEST);
		sceGuEnable(GU_BLEND);
		sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        if(state == 0)
        {
            if(loadingProcess < 160)
            {
                loadingProcess += 0.5f;
            }
        }
        else
        {
            switch(state)
            {
            case 2:
            loadingProcess < 18 ? loadingProcess += 0.75f : loadingProcess = 18;
            break;
            case 3:
            loadingProcess < 64 ? loadingProcess += 0.75f : loadingProcess = 64;
            break;
            case 4:
            loadingProcess < 80 ? loadingProcess += 0.75f : loadingProcess = 80;
            break;
            case 5:
            loadingProcess < 96 ? loadingProcess += 0.75f : loadingProcess = 96;
            break;
            case 6:
            loadingProcess < 112 ? loadingProcess += 0.75f : loadingProcess = 112;
            break;
            case 7:
            loadingProcess < 128 ? loadingProcess += 0.75f : loadingProcess = 128;
            break;
            case 8:
            loadingProcess < 144 ? loadingProcess += 0.5 : loadingProcess = 144;
            break;
            case 9:
            loadingProcess < 160 ? loadingProcess += 0.5f : loadingProcess = 160;
            break;
            }
        }

        subLoadSprite->NewScale(160);
        subLoadSprite->SetPosition(160,150);

        loadSprite->NewScale(loadingProcess);
        loadSprite->SetPosition(160,150);

        if(loadingProcess < 159)
        {
            subLoadSprite->Draw();
            loadSprite->Draw();
        }

		sceGuDisable(GU_BLEND);
		sceGuEnable(GU_DEPTH_TEST);

		//draw subtitles on buttons
        RenderManager::InstancePtr()->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200|0x00000000);
        if(state2 == 0)
        {
            RenderManager::InstancePtr()->DebugPrint(240,112,"Loading level");
        }
        else
        {
            RenderManager::InstancePtr()->DebugPrint(240,112,"Generating level");
            switch(state2)
            {
            case 2:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Building terrain");
            break;
            case 3:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Placing bedrock");
            break;
            case 4:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Making beaches");
            break;
            case 5:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Pouring water");
            break;
            case 6:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Digging caves");
            break;
            case 7:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Placing pumpkins");
            break;
            case 8:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Drawing biomes");
            break;
            case 9:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Growing trees");
            break;
            case 10:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Placing ores");
            break;
            case 11:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Last chips");
            break;
            case 12:
            RenderManager::InstancePtr()->DebugPrint(240,136,"Saving chunks");
            break;
            }
        }

        RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.45f,0.45f,0.45f,1.0f),0,0x00000200|0x00000000);
        switch(tip)
        {
        case 0:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : press R+L to open inventory menu");
        break;
        case 1:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : place items, according to recipe and");
        RenderManager::InstancePtr()->DebugPrint(240,255,"press R to craft recipe item");
        break;
        case 2:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : press up button + R trigger to drop item");
        break;
        case 3:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : aim at crafting table and");
        RenderManager::InstancePtr()->DebugPrint(240,255,"press R to open crafting table menu");
        break;
        case 4:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : take food item in your hand and");
        RenderManager::InstancePtr()->DebugPrint(240,255,"press R trigger to eat it");
        break;
        case 5:
        RenderManager::InstancePtr()->DebugPrint(240,240,"Tip : build a small shelter before the night");
        RenderManager::InstancePtr()->DebugPrint(240,255,"or zombies will eat you");
        break;
        }
        RenderManager::InstancePtr()->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200|0x00000000);

		RenderManager::InstancePtr()->EndFrame();
	}
	return 0;
}

