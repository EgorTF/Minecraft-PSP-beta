#include "StateMenu.h"
#include "StateOptions.h"
#include "StatePlay.h"
#include "StatePlayCreative.h"
#include "LoadingScreen.h"
#include "InputHelper.h"
#include "TextureHelper.h"

#include <Aurora/System/NetworkManager.h>
#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

// font vars
#define default_size 0.347
#define default_big_size 0.687


StateMenu::StateMenu()
{

}

StateMenu::~StateMenu()
{

}

void StateMenu::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo),0,0,256,64);
    logoSprite->Scale(1.5f,1.5f);
    logoSprite->SetPosition(240,50);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,190,24);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,190,24);
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,48,190,24);
    nbuttonSprite->SetPosition(240,150);

    snbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,72,190,24);
    snbuttonSprite->SetPosition(240,150);

    mbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,72,190,24);
    mbuttonSprite->SetPosition(240,150);

    smbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,96,190,24);
    smbuttonSprite->SetPosition(240,150);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,32,32);
    backSprite->Scale(2,2);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,320,90);
    lamecraftSprite->SetPosition(240,50);
    lamecraftSprite->Scale(1,1);

    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");
    ScanTexturePacks("Assets/Textures/");

    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    aboutPos = 0;
    newWorldName = "LameWorld";
    newWorldSeed = "";

    size_f = 0.347f;

    //for map generation
    makeTrees = true;
    makeWater = true;
    makeCaves = true;

    terrainBuilder = 0;

    seed_1 = 0;
    gameMode = 0;

    SplashNumber = rand() % 5;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    generateSelectPose = 0;

    newWorldNamestr = newWorldName.c_str();
    currentVersion = 120;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

	animationscreen = 1;
	fontcoloroption = 0;
	fontcolor = 0;
	srand(time(0));

    tpCurrent = 0;
	tpMax = 0;
	tpEnd = 0;
	tpStart = 0;
	tpPos = 0;
	tpSelectPos = 0;
}

void StateMenu::Enter()
{
    mRender->SetOrtho(0,0,0,0,0,0);
    selectPos = 0;
}

void StateMenu::CleanUp()
{
    delete logoSprite;
    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete snbuttonSprite;
    delete mbuttonSprite;
    delete smbuttonSprite;
    delete backSprite;
    delete lamecraftSprite;
}

void StateMenu::Pause()
{

}

void StateMenu::Resume()
{
    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    mRender->SetOrtho(0,0,0,0,0,0);
}

void StateMenu::HandleEvents(StateManager* sManager)
{
    //update input
    mSystemMgr->InputUpdate();

    /*if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
    {
        size_f += 0.0001f;
    }
    if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
    {
        size_f -= 0.0001f;
    }

    if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
    {
        size_f -= 0.001f;
    }
    if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
    {
        size_f += 0.001f;
    }

    if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
    {
        size_f -= 0.01f;
    }
    if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
    {
        size_f += 0.01f;
    }*/

    switch(menuState)
    {
    case 0://main menu
    {
        //if triangle button pressed the exit
        if(mSystemMgr->KeyPressed(PSP_CTRL_START))
        {
            //running = false;
            sManager->Quit();
        }

        //up, down
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            selectPos--;
            if(selectPos < 0)
                selectPos = 3;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            selectPos++;
            if(selectPos > 3)
                selectPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            SplashNumber = rand() % 5;
            if(selectPos == 0)//play state
            {
            generateSelectPose = 0;
            menuState = 7;
            }

            if(selectPos == 1)
            {
                //w teori opcje
                StateOptions *stateOptions = new StateOptions();
                stateOptions->Init();
                sManager->PushState(stateOptions);
            }
            if(selectPos == 2)
            {
                //about
                menuState = 3;
                aboutPos = 1;
            }
            if(selectPos == 3)
            {
                //about
                menuState = 11;
                tpSelectPos = 0;
                tpEnd = texturePackList.size();
                tpMax = 4;
                ScanTexturePacks("Assets/Textures/");
            }
        }
    }
    break;
    case 11://tp
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            tpSelectPos --;
            if(tpSelectPos < 0)
            {
                tpSelectPos = 1;
            }
            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            tpSelectPos ++;
            if(tpSelectPos > 1)
            {
                tpSelectPos = 0;
            }
            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
        {
            tpPos--;
            if(tpEnd > 4)
            {
                tpStart--;
                tpMax--;

                if(tpMax < 4)
                {
                    tpStart = 0;
                    tpMax = 4;
                }
            }

            if(tpPos < 0)
            {
                tpPos = texturePackList.size() - 1;
                tpMax = tpEnd;
                tpStart = tpEnd - 4;
                if(tpStart < 0)
                    tpStart = 0;
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
        {
            tpPos++;
            if(tpPos == tpMax)
            {
                tpStart++;
                tpMax++;
                if(tpStart > tpEnd)
                {
                    tpStart = tpEnd - 4;
                    if(tpStart < 0)
                        tpStart = 0;
                    tpMax = tpEnd;
                }
            }
            if(tpPos >= texturePackList.size())
            {
                tpPos = 0;
                tpStart = 0;
                tpMax = 4;
                if(tpMax > tpEnd)
                    tpMax = tpEnd;
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(tpSelectPos == 0)//play state
            {
                if(texturePackList.empty() == false)
                {
                    TextureHelper::Instance()->SetTexturePack(texturePackList[tpPos].name);
                    tpCurrent = tpPos;
                }
            }
            if(tpSelectPos == 1)//delete save
            {
                menuState = 0;
            }
        }
    }
    break;
    case 10:
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            saveSubMenuSelect == 0 ? saveSubMenuSelect = 1 : saveSubMenuSelect = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            saveSubMenuSelect == 1 ? saveSubMenuSelect = 0 : saveSubMenuSelect = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            char worldNameTemp[50];
            for(char i = 0; i <= 49; i++)
            {
                worldNameTemp[i] = saveFilesList[loadSavePos].worldName[i];
            }

            int saveVersionTemp = 3;
            char worldGameModeTemp = saveSubMenuSelect;
            bool locked = saveFilesList[loadSavePos].locked;

            FILE * pFile;
            pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(),"wb");

            if(pFile != NULL)
            {
                //version
                fwrite(&saveVersionTemp, sizeof(int),1,pFile);

                fwrite(&worldGameModeTemp, sizeof(char),1,pFile);

                fwrite(&locked, sizeof(bool),1,pFile);
                //name
                fwrite(worldNameTemp ,sizeof(char),50,pFile);

                fclose(pFile);
            }

            ScanSaveFiles("Save/");

            if(saveFilesList[loadSavePos].locked == true)
            {
                loadSelectPos = 1;
            }

            menuState = 1;
        }
    }
    break;
    case 1://load
    {
        if(saveSubmenu)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                saveSubMenuSelect--;
                if(saveSubMenuSelect < 1)
                    saveSubMenuSelect = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                saveSubMenuSelect++;
                if(saveSubMenuSelect > 2)
                    saveSubMenuSelect = 1;

                mSoundMgr->PlayMenuSound();
            }



            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(saveSubMenuSelect == 1)//remove file
                {
                    //remove file
                    if(saveFilesList.size() > 0)
                    {
                        if(saveFilesList[loadSavePos].compression)
                        {
                            //remove normal file
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                            //remove compressed one
                            saveFilesList[loadSavePos].fileName += "c";
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                        }
                        else
                        {
                            remove(saveFilesList[loadSavePos].fileName.c_str());
                        }

                        ScanSaveFiles("Save/");

                        loadSelectPos = 0;
                        loadSavePos = 0;
                        loadSaveStart = 0;
                        loadSaveEnd = saveFilesList.size();
                        loadSaveMax = 4;
                        if(loadSaveMax > loadSaveEnd)
                            loadSaveMax = loadSaveEnd;

                        saveSubmenu = false;
                        saveSubMenuSelect = 2;
                        if(saveFilesList[loadSavePos].locked == true)
                        {
                            loadSelectPos = 1;
                        }
                    }
                }
                if(saveSubMenuSelect == 2)//return
                {
                    saveSubMenuSelect = 2;
                    saveSubmenu = false;
                }
            }


        }
        else
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                if(saveFilesList[loadSavePos].locked == false)
                {
                    if(saveFilesList[loadSavePos].worldGameMode != 2)
                    {
                        loadSelectPos--;
                        if(loadSelectPos < 0)
                            loadSelectPos = 2;

                        mSoundMgr->PlayMenuSound();
                    }
                    else
                    {
                        loadSelectPos--;
                        if(loadSelectPos < 0)
                            loadSelectPos = 1;

                        mSoundMgr->PlayMenuSound();
                    }
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                if(saveFilesList[loadSavePos].locked == false)
                {
                    if(saveFilesList[loadSavePos].worldGameMode != 2)
                    {
                        loadSelectPos++;
                        if(loadSelectPos > 2)
                            loadSelectPos = 0;

                        mSoundMgr->PlayMenuSound();
                    }
                    else
                    {
                        loadSelectPos++;
                        if(loadSelectPos > 1)
                            loadSelectPos = 0;

                        mSoundMgr->PlayMenuSound();
                    }
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                loadSavePos--;
                if(loadSaveEnd > 4)
                {
                    loadSaveStart--;
                    loadSaveMax--;

                    if(loadSaveMax < 4)
                    {
                        loadSaveStart = 0;
                        loadSaveMax = 4;
                    }
                }

                if(loadSavePos < 0)
                {
                    loadSavePos = saveFilesList.size() - 1;
                    loadSaveMax = loadSaveEnd;
                    loadSaveStart = loadSaveEnd - 4;
                    if(loadSaveStart < 0)
                        loadSaveStart = 0;
                }
                if(saveFilesList[loadSavePos].locked == true)
                {
                    loadSelectPos = 1;
                }
                if(saveFilesList[loadSavePos].worldGameMode == 2)
                {
                    if(loadSelectPos == 2)
                    {
                        loadSelectPos = 1;
                    }
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                loadSavePos++;
                if(loadSavePos == loadSaveMax)
                {
                    loadSaveStart++;
                    loadSaveMax++;
                    if(loadSaveMax > loadSaveEnd)
                    {
                        loadSaveStart = loadSaveEnd - 4;
                        if(loadSaveStart < 0)
                            loadSaveStart = 0;
                        loadSaveMax = loadSaveEnd;
                    }
                }
                if(loadSavePos >= saveFilesList.size())
                {
                    loadSavePos = 0;
                    loadSaveStart = 0;
                    loadSaveMax = 4;
                    if(loadSaveMax > loadSaveEnd)
                        loadSaveMax = loadSaveEnd;
                }
                if(saveFilesList[loadSavePos].locked == true)
                {
                    loadSelectPos = 1;
                }
                if(saveFilesList[loadSavePos].worldGameMode == 2)
                {
                    if(loadSelectPos == 2)
                    {
                        loadSelectPos = 1;
                    }
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 7;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(loadSelectPos == 0)//play state
                {
						//load map
                    if(saveFilesList.size() > 0)
                    {
                        if(saveFilesList[loadSavePos].locked == false)
                        {
                            if(saveFilesList[loadSavePos].worldGameMode == 0 || saveFilesList[loadSavePos].worldGameMode == 2)
                            {
                                StatePlay *statePlay = new StatePlay();
                                LoadingScreen *loading = new LoadingScreen();
                                statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                                statePlay->InitCamera();
                                loading->KillLoadingScreen();
                                delete loading;
                                sManager->PushState(statePlay);
                            }
                            else
                            {
                                StatePlayCreative *statePlay = new StatePlayCreative();
                                LoadingScreen *loading = new LoadingScreen();
                                statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                                statePlay->InitCamera();
                                loading->KillLoadingScreen();
                                delete loading;
                                sManager->PushState(statePlay);
                            }
                        }
                    }

                }
                if(loadSelectPos == 1)//delete save
                {
                    if(saveFilesList.size() > 0)
                    {
                        saveSubmenu = true;
                        saveSubMenuSelect = 2;
                    }
                }
                if(loadSelectPos == 2)
                {
                    if(saveFilesList.size() > 0)
                    {
                        menuState = 10;
                        saveSubMenuSelect = 0;
                    }
                }
            }
        }
    }
    break;
    case 3://about
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            aboutPos--;
            if(aboutPos < 0)
                aboutPos = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            aboutPos++;
            if(aboutPos > 1)
                aboutPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(aboutPos == 1)
            {
                menuState = 0;
            }
            if(aboutPos == 0)
            {
                //checking for new update
                NetworkManager::Instance()->Init();
                //initialize connection
                if(NetworkManager::Instance()->InitializeConnection())
                {
                    //show network dialog and connect to ap
                    if(SystemManager::Instance()->ShowNetworkDialog())
                    {
                         //download update info
                        if(NetworkManager::Instance()->GetFile("http://net2ftp.ru/node0/kuznetsoffvyacheslav@gmail.com/version.txt","version.txt"))
                        {
                            //check what version is inside
                            int fileVersion = 0;
                            FILE * pFile;
                            pFile = fopen("version.txt","r");
                            if (pFile!=NULL)
                            {
                                char buffer[3];
                                fread(buffer,1,3,pFile);
                                fileVersion = atoi(buffer);
                                fclose (pFile);

                                if(fileVersion > currentVersion)
                                {
                                    SystemManager::Instance()->ShowMessage("There is new version available");

                                    //ask question if user want to download updater
                                    if(SystemManager::Instance()->ShowMessageYesNo("Do you want to download Minecraft PSP update?") == 1)
                                    {
                                        //download updater there
                                        NetworkManager::Instance()->GetFile("http://net2ftp.ru/node0/kuznetsoffvyacheslav@gmail.com/Minecraft-PSP.zip","ms0:/PSP/GAME/Minecraft-PSP.zip");
										theZip = pgeZipOpen("ms0:/PSP/GAME/Minecraft-PSP.zip");
                                        chdir("ms0:/PSP/GAME");
                                        pgeZipExtract(theZip, NULL);
                                        pgeZipClose(theZip);

                                        SystemManager::Instance()->ShowMessage("Update was installed. You can find it in your game directory");
                                        theZip = NULL;
                                    }
                                }
                                else
                                {
                                    SystemManager::Instance()->ShowMessage("You have latest version.");
                                }
                            }
                            else
                            {
                                SystemManager::Instance()->ShowMessage("Can't open version.txt .");
                            }
                        }
                        else
                        {
                            SystemManager::Instance()->ShowMessage("Can't download update information.");
                        }
                    }
                    else
                    {
                        SystemManager::Instance()->ShowMessage("You must connect to an access point.");
                    }
                }
                else
                {
                    SystemManager::Instance()->ShowMessage("Can't initialize network.");
                }

                //turn off connection
                NetworkManager::Instance()->ShutDownConnection();
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            menuState = 0;
        }
    }
    break;
    case 5://parametric terrain
    {

        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            mSoundMgr->PlayMenuSound();

            if (generateSelectPose == 0)
            {
                generateSelectPose = 4;
                return;
            }

            generateSelectPose--;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            mSoundMgr->PlayMenuSound();
            if (generateSelectPose == 4)
            {
                generateSelectPose = 0;
                return;
            }
            generateSelectPose++;

        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 7;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0)
            {

                newWorldName = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];

                        if(32 <= c && c <= 127) // print ascii only
                            newWorldName += c;
                    }


                }
                newWorldNamestr = newWorldName.c_str();
            }

            if(generateSelectPose == 1)
            {
                seed_1 = 0;
                newWorldSeed = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','s','e','e','d'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];

                        if(48 <= c && c <= 57)
                        {
                            newWorldSeed += c;
                        }
                    }
                    seed_1 = std::atoi(newWorldSeed.c_str());
                }
            }

            if(generateSelectPose == 3)
            {

            }

            if(generateSelectPose == 2)
            {
                gameMode += 1;
                if (gameMode == 3)
                {
                    gameMode = 0;
                }
            }

            if(generateSelectPose == 4)
            {
                //terrainBuilder = 2;
                if(gameMode == 0 || gameMode == 2)
                {
                    StatePlay *statePlay = new StatePlay();
                    statePlay->InitParametric(makeTrees,makeWater,makeCaves,seed_1,1,gameMode);
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);
                }
                else
                {
                    StatePlayCreative *statePlay = new StatePlayCreative();
                    statePlay->InitParametric(makeTrees,makeWater,makeCaves,seed_1,1,gameMode);
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);
                }
                seed_1 = 0;
            }
    }


    }
    break;
    case 6://check new version menu
    {

    }
    break;
    case 7://load or new map
    {
         if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 1)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0) //new game
            {
                generateSelectPose = 0;
                menuState = 5;

                makeTrees = true;
                makeWater = true;
                makeCaves = true;
                terrainBuilder = 0;

            }

            if(generateSelectPose == 1) //load game
            {
                ScanSaveFiles("Save/");

                menuState = 1;
                loadSelectPos = 0;
                loadSavePos = 0;
                loadSaveStart = 0;
                loadSaveEnd = saveFilesList.size();
                loadSaveMax = 4;
                if(loadSaveMax > loadSaveEnd)
                loadSaveMax = loadSaveEnd;

                if(saveFilesList[loadSavePos].locked == true)
                {
                    loadSelectPos = 1;
                }
            }
        }
    }
    break;

    }

}

void StateMenu::Update(StateManager* sManager)
{




}

void StateMenu::Draw(StateManager* sManager)
{
    //start rendering
    mRender->StartFrame(1,1,1);

    switch(menuState)
    {
    case 0://main menu
    {
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
        //logo
        lamecraftSprite->Draw();

        //singlePlayer
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //options
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //about
        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        //texture pack
        buttonSprite->SetPosition(240,240);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons
        selectPos == 0 ? DrawText(240,129,GU_COLOR(1,1,0.25,1) ,default_size,"Play Game") : DrawText(240,129,GU_COLOR(1,1,1,1) ,default_size,"Play Game");
        selectPos == 1 ? DrawText(240,169,GU_COLOR(1,1,0.25,1) ,default_size,"Options") : DrawText(240,169,GU_COLOR(1,1,1,1) ,default_size,"Options");
        selectPos == 2 ? DrawText(240,209,GU_COLOR(1,1,0.25,1) ,default_size,"About") : DrawText(240,209,GU_COLOR(1,1,1,1) ,default_size,"About");
        selectPos == 3 ? DrawText(240,249,GU_COLOR(1,1,0.25,1) ,default_size,"Texture Pack") : DrawText(240,249,GU_COLOR(1,1,1,1) ,default_size,"Texture Pack");
       // mRender->DebugPrint(50,150,"%f",size_f);

		}
		break;
    case 1://load menu
    {
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

        //select sprite
        if(saveFilesList.size() > 0)
        {
            //save files
            for(int i = loadSaveStart; i <loadSaveMax; i++)
            {
                if(loadSavePos == i)
                {

                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,0,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].worldName);

                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                    mRender->DebugPrint(30,66 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].fileName.c_str());
                    switch(saveFilesList[i].worldGameMode)
                    {
                    case 0:
                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                    mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Survival mode");
                    break;
                    case 1:
                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                    mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Creative mode");
                    break;
                    case 2:
                    if(saveFilesList[i].locked == true)
                    {
                        mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                        mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Hardcore mode (LOCKED)");
                    }
                    else
                    {
                        mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                        mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Hardcore mode");
                    }
                    break;
                    }
                }
                else
                {
                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,1,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].worldName);

                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                    mRender->DebugPrint(30,66 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].fileName.c_str());
                    switch(saveFilesList[i].worldGameMode)
                    {
                    case 0:
                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                    mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Survival mode");
                    break;
                    case 1:
                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                    mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Creative mode");
                    break;
                    case 2:
                    if(saveFilesList[i].locked == true)
                    {
                        mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                        mRender->DebugPrint(30,78  + (i * 41) - (loadSaveStart * 41),"Hardcore mode (LOCKED)");
                    }
                    else
                    {
                        mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                        mRender->DebugPrint(30,78  + (i * 41) - (loadSaveStart * 41),"Hardcore mode");
                    }
                    break;
                    }
                }
            }

        }

        if(!saveSubmenu)
        {
            if(saveFilesList[loadSavePos].locked == false)
            {
                //play
                buttonSprite->SetPosition(240,210);
                buttonSprite->Draw();

                if(saveFilesList[loadSavePos].worldGameMode != 2)
                {
                    buttonSprite->SetPosition(240,260);
                    buttonSprite->Draw();
                }
            }

            //delete
            buttonSprite->SetPosition(240,235);
            buttonSprite->Draw();
        }
        else
        {
            buttonSprite->SetPosition(240,235);
            buttonSprite->Draw();

            buttonSprite->SetPosition(240,260);
            buttonSprite->Draw();
        }


        if(saveSubmenu)
        {
            sbuttonSprite->SetPosition(240,(saveSubMenuSelect * 25) + 210);
        }
        else
        {
            sbuttonSprite->SetPosition(240,(loadSelectPos * 25) + 210);
        }
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(saveSubmenu)
        {
            saveSubMenuSelect == 0 ? DrawText(240,219,GU_COLOR(1,1,0.25,1) ,default_size,"Are you sure?") : DrawText(240,219,GU_COLOR(1,1,1,1) ,default_size,"Are you sure?");
            saveSubMenuSelect == 1 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Yes") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Yes");
            saveSubMenuSelect == 2 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"No") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"No");
        }
        else
        {
            if(saveFilesList[loadSavePos].locked == false)
            {
                loadSelectPos == 0 ? DrawText(240,219,GU_COLOR(1,1,0.25,1),default_size,"Play") : DrawText(240,219,GU_COLOR(1,1,1,1),default_size,"Play");
                if(saveFilesList[loadSavePos].worldGameMode != 2)
                {
                    loadSelectPos == 2 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"Game Mode");
                }
            }
            loadSelectPos == 1 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Delete") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Delete");
        }
        DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,"Load world");
    }
    break;
    case 11://tp
    {
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

        //select sprite
        if(texturePackList.size() > 0)
        {

        }

        for(int i = tpStart; i < tpMax; i++)
        {
            if(i < texturePackList.size())
            {
                if(i == tpPos)
                {
                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,0,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (tpStart * 41),"%s",texturePackList[i].name.c_str());
                }
                else
                {
                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,1,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (tpStart * 41),"%s",texturePackList[i].name.c_str());
                }
                if(i == tpCurrent)
                {
                    if(tpPos == tpCurrent)
                    {
                        mRender->SetFontStyle(0.8f,GU_COLOR(1,0.5,0,1),0,0x00000000);
                        mRender->DebugPrint(30,54 + (i * 41) - (tpStart * 41),"%s",texturePackList[i].name.c_str());
                    }
                    else
                    {
                        mRender->SetFontStyle(0.8f,GU_COLOR(1,0,0,1),0,0x00000000);
                        mRender->DebugPrint(30,54 + (i * 41) - (tpStart * 41),"%s",texturePackList[i].name.c_str());
                    }

                }
            }

        }


        buttonSprite->SetPosition(240,210);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();


        sbuttonSprite->SetPosition(240,(tpSelectPos * 25) + 210);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        tpSelectPos == 0 ? DrawText(240,219,GU_COLOR(1,1,0.25,1),default_size,"Select") : DrawText(240,219,GU_COLOR(1,1,1,1),default_size,"Select");
        tpSelectPos == 1 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Back") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Back");
        DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,"Texture Pack");
    }
    break;
    case 3://about
    {


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

        //check for update
        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,260);
        buttonSprite->Draw();

        //back
        sbuttonSprite->SetPosition(240,(aboutPos * 25) + 235);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        DrawText(242,106,GU_COLOR(0.25f,0.25f,0.25f,1.0f),default_big_size,"Original Code: Drakon");
        DrawText(240,104,GU_COLOR(1,1,1,1) ,default_big_size,"Original Code: Drakon");

        DrawText(242,128,GU_COLOR(0.25f,0.25f,0.25f,1.0f),default_big_size,"Mod by: Woolio");
        DrawText(240,126,GU_COLOR(1,1,1,1) ,default_big_size,"Mod by: Woolio");

        DrawText(242,150,GU_COLOR(0.25f,0.25f,0.25f,1.0f),default_big_size,"Version: 1.3.1 beta");
        DrawText(240,148,GU_COLOR(1,1,1,1) ,default_big_size,"Version: 1.3.1 beta");

        aboutPos == 0 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Check for update") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Check for update");
        aboutPos == 1 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"Back") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"Back");
        DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"About");

    }
    break;
    case 5://paramateric view
    {


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


        //name
        mbuttonSprite->SetPosition(240,70);
        mbuttonSprite->Draw();
        //seed
        mbuttonSprite->SetPosition(240,110);
        mbuttonSprite->Draw();

        buttonSprite->SetPosition(240,150);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,190);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,230);
        buttonSprite->Draw();

        if(generateSelectPose > 1)
        {
            sbuttonSprite->SetPosition(240,150+(generateSelectPose-2)*40);
            sbuttonSprite->Draw();
        }
        if(generateSelectPose <= 1)
        {
            smbuttonSprite->SetPosition(240,70+generateSelectPose*40);
            smbuttonSprite->Draw();
        }

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);


        DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"New World");
        DrawText(240,58,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Name");
        DrawText(240,98,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Seed");

        //draw subtitles on buttons
        if(gameMode == 0)
        {
            generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Survival") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Survival");
        }
        if(gameMode == 1)
        {
            generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Creative") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Creative");
        }
        if(gameMode == 2)
        {
            generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Hardcore") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Hardcore");
        }
        generateSelectPose == 3 ? DrawText(240,199,GU_COLOR(1,1,0.25,1) ,default_size,"Nothing Here") : DrawText(240,199,GU_COLOR(1,1,1,1) ,default_size,"Nothing Here");
        generateSelectPose == 4 ? DrawText(240,239,GU_COLOR(1,1,0.25,1) ,default_size,"Create New World") : DrawText(240,239,GU_COLOR(1,1,1,1) ,default_size,"Create New World");

        mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000000|0x00004000);
        mRender->DebugPrint(150,79,"%s",newWorldName.c_str());
        mRender->DebugPrint(150,119,"%s",newWorldSeed.c_str());
    }
    break;
    case 10://New or load map
    {
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

        buttonSprite->SetPosition(240,100);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,140);
        buttonSprite->Draw();

        sbuttonSprite->SetPosition(240,100+saveSubMenuSelect*40);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        DrawText(240,64,GU_COLOR(1,1,1,1) ,default_size,"Choose Game Mode");

        saveSubMenuSelect == 0 ? DrawText(240,109,GU_COLOR(1,1,0.25,1) ,default_size,"Survival") : DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"Survival");
        saveSubMenuSelect == 1 ? DrawText(240,149,GU_COLOR(1,1,0.25,1) ,default_size,"Creative") : DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Creative");

    }
    break;
    case 7://New or load map
    {


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

        //Randomly
        buttonSprite->SetPosition(240,100);
        buttonSprite->Draw();

        //Parametric
        buttonSprite->SetPosition(240,140);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(generateSelectPose * 40) + 100);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        generateSelectPose == 0 ? DrawText(240,109,GU_COLOR(1,1,0.25,1) ,default_size,"New world") : DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"New world");
        generateSelectPose == 1 ? DrawText(240,149,GU_COLOR(1,1,0.25,1) ,default_size,"Load world") : DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Load world");
        DrawText(240,25,GU_COLOR(1,1,1,1) ,default_size,"SinglePlayer");
    }
    break;
    }

    //mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),0,0x00000000);
    //mRender->DebugPrint(30,50,"%f",size_f);

    //draw debug text at the end
    /*mRender->DebugPrint(40,30,"cpu: %d%%",mRender->GetCpuUsage());
    mRender->DebugPrint(40,40,"gpu: %d%%",mRender->GetGpuUsage());
    mRender->DebugPrint(40,50,"saves: %d",saveFilesList.size());*/

    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000400);
    //mRender->DebugPrint(475,15,"CraftSite.pl Edition");
    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);

    //end frame
    mRender->EndFrame();
}

//additional functions
void StateMenu::ScanSaveFiles(const char* dirName)
{
    //clear list with save files
    saveFilesList.clear();

    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(dirName);

    while((DirEntry = readdir(Dir)) != NULL)
    {
        if ( DirEntry->d_stat.st_attr & FIO_SO_IFREG) // найден файлик, епта
        {
            SaveFile newSaveFile;
            std::string plik = dirName;
            plik += DirEntry->d_name;
            //dont load lmsc files
            size_t found = plik.find(".lmsc");
            size_t found2 = plik.find(".LMSc");
            if(found==std::string::npos && found2==std::string::npos)//не найдено
            {
                newSaveFile.fileName = plik;
                saveFilesList.push_back(newSaveFile);
            }
        }
    }

    closedir(Dir);


    //now update all info in save files
    for(unsigned int i = 0; i < saveFilesList.size(); i++)
    {
        FILE * pFile;
        pFile = fopen(saveFilesList[i].fileName.c_str(),"rb");

        if(pFile != NULL)
        {
            //version
            fread(&saveFilesList[i].saveVersion,sizeof(int),1,pFile);

            fread(&saveFilesList[i].worldGameMode,sizeof(char),1,pFile);

            fread(&saveFilesList[i].locked,sizeof(bool),1,pFile);
            //name
            fread(saveFilesList[i].worldName,sizeof(char),50,pFile);

            if(saveFilesList[i].saveVersion >= 2)
                saveFilesList[i].compression = true;
            else
                saveFilesList[i].compression = false;

            fclose(pFile);
        }
    }

    //set next save name and numer
    nextSaveFileNumber = saveFilesList.size() + 1;
    {
        //ride thru all saves and check if i can use new name
        char liczba[3];
        sprintf(liczba,"%d",nextSaveFileNumber);
        nextSaveFileName = "Save/world";
        nextSaveFileName += liczba;
        nextSaveFileName += ".lms";

        for(unsigned int i = 0; i < saveFilesList.size(); i++)
        {
            if(nextSaveFileName.compare(saveFilesList[i].fileName) == 0)
            {
                nextSaveFileNumber+=1;
                char liczba[3];
                sprintf(liczba,"%d",nextSaveFileNumber);
                nextSaveFileName = "Save/world";
                nextSaveFileName += liczba;
                nextSaveFileName += ".lms";
            }
        }
    }
}

void StateMenu::ScanTexturePacks(const char* dirName)
{
    texturePackList.clear();
    DIR *dir = opendir(dirName);

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL)
    {
        if (FIO_SO_ISDIR(entry->d_stat.st_attr))
        {
            TP newTP;
            std::string plik = "";
            plik += entry->d_name;

            size_t found = plik.find(".");
            size_t found2 = plik.find("..");
            size_t found3 = plik.find(".svn");
            if(found==std::string::npos && found2==std::string::npos && found3==std::string::npos)//не найдено
            {
                newTP.name = plik;
                texturePackList.push_back(newTP);
            }
        }
    }

    closedir(dir);
}
/*
    texturePackList.clear();

	FILE *infile;
	char textLine[80];
	char textPack[80];

	infile = fopen("Assets/texturePacks.txt","rt");

	 while(fgets(textLine, 80, infile) != NULL)
	 {
		 sscanf(textLine,"%s",textPack);
		 std::string texturePack = textPack;

		 size_t found = texturePack.find(".tp");
		 size_t found2 = texturePack.find(".TP");
		 if(found != std::string::npos || found2 != std::string::npos)// found
		 {
		 	texturePackList.push_back(texturePack);
		 }
	 }
	 fclose(infile);

*/

void StateMenu::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,color,0,0x00000200|0x00000000);
    mRender->DebugPrint(x,y,message);
}
