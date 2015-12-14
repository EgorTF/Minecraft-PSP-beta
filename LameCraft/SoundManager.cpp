#include "SoundManager.h"

SoundManager SoundManager::m_SoundManager;

SoundManager* SoundManager::Instance()
{
	return &m_SoundManager;
}

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
    pgeWavStopAll();

    pgeWavUnload(buttonSound);
    pgeWavUnload(tnt);
    pgeWavUnload(doorOpen);
    pgeWavUnload(doorClose);
    pgeWavUnload(breakSound);
    pgeWavUnload(bow);
    pgeWavUnload(plopSound);
    pgeWavUnload(zombieDieSound);
    pgeWavUnload(cowSaySound);

    for(int i = 0; i <= 3; i++)
    {
        pgeWavUnload(grassSounds[i]);
        pgeWavUnload(grawelSounds[i]);
        pgeWavUnload(stoneSounds[i]);
        pgeWavUnload(woodSounds[i]);
        pgeWavUnload(clothSounds[i]);
        pgeWavUnload(sandSounds[i]);
        pgeWavUnload(snowSounds[i]);
    }
    for(int i = 0; i <= 2; i++)
    {
        pgeWavUnload(eatSounds[i]);
        pgeWavUnload(hitSounds[i]);
    }
    for(int i = 0; i <= 1; i++)
    {
        pgeWavUnload(fallSounds[i]);
        pgeWavUnload(cowHurtSounds[i]);
        pgeWavUnload(zombieHurtSounds[i]);
    }
}

void SoundManager::Init()
{
	//first of all init audio engine
	pgeWavInit();

	//button sound
	buttonSound = pgeWavLoad("Assets/Sounds/other/button1.wav");

	//TNT
	tnt = pgeWavLoad("Assets/Sounds/other/tnt.wav");

	doorOpen = pgeWavLoad("Assets/Sounds/other/door_open.wav");
	doorClose = pgeWavLoad("Assets/Sounds/other/door_close.wav");

	breakSound = pgeWavLoad("Assets/Sounds/other/break.wav");

	bow = pgeWavLoad("Assets/Sounds/other/bow.wav");

	//plop sound
	plopSound = pgeWavLoad("Assets/Sounds/other/plop.wav");
	pgeWavVolume(plopSound,50,50);

    //fall sounds
    fallSounds[0] = pgeWavLoad("Assets/Sounds/Damage/fallbig.wav");
    fallSounds[1] = pgeWavLoad("Assets/Sounds/Damage/fallsmall.wav");

    //zombie sounds
    zombieHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt1.wav");
    zombieHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt2.wav");
    zombieDieSound = pgeWavLoad("Assets/Sounds/mobs/zombie/death.wav");

    //cow sounds
    cowHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt1.wav");
    cowHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt2.wav");
    cowSaySound = pgeWavLoad("Assets/Sounds/mobs/cow/say1.wav");

	//grass sounds
	grassSounds[0] = pgeWavLoad("Assets/Sounds/walking/grass/grass1.wav");
	grassSounds[1] = pgeWavLoad("Assets/Sounds/walking/grass/grass2.wav");
	grassSounds[2] = pgeWavLoad("Assets/Sounds/walking/grass/grass3.wav");
	grassSounds[3] = pgeWavLoad("Assets/Sounds/walking/grass/grass4.wav");

	//gravel
	grawelSounds[0] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel1.wav");
	grawelSounds[1] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel2.wav");
	grawelSounds[2] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel3.wav");
	grawelSounds[3] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel4.wav");

	//stone
	stoneSounds[0] = pgeWavLoad("Assets/Sounds/walking/stone/stone1.wav");
	stoneSounds[1] = pgeWavLoad("Assets/Sounds/walking/stone/stone2.wav");
	stoneSounds[2] = pgeWavLoad("Assets/Sounds/walking/stone/stone3.wav");
	stoneSounds[3] = pgeWavLoad("Assets/Sounds/walking/stone/stone4.wav");

	//wood
	woodSounds[0] = pgeWavLoad("Assets/Sounds/walking/wood/wood1.wav");
	woodSounds[1] = pgeWavLoad("Assets/Sounds/walking/wood/wood2.wav");
	woodSounds[2] = pgeWavLoad("Assets/Sounds/walking/wood/wood3.wav");
	woodSounds[3] = pgeWavLoad("Assets/Sounds/walking/wood/wood4.wav");

    //cloth
    clothSounds[0] = pgeWavLoad("Assets/Sounds/walking/cloth/cloth1.wav");
	clothSounds[1] = pgeWavLoad("Assets/Sounds/walking/cloth/cloth2.wav");
	clothSounds[2] = pgeWavLoad("Assets/Sounds/walking/cloth/cloth3.wav");
	clothSounds[3] = pgeWavLoad("Assets/Sounds/walking/cloth/cloth4.wav");

    //sand
    sandSounds[0] = pgeWavLoad("Assets/Sounds/walking/sand/sand1.wav");
	sandSounds[1] = pgeWavLoad("Assets/Sounds/walking/sand/sand2.wav");
	sandSounds[2] = pgeWavLoad("Assets/Sounds/walking/sand/sand3.wav");
	sandSounds[3] = pgeWavLoad("Assets/Sounds/walking/sand/sand4.wav");

    //snow
    snowSounds[0] = pgeWavLoad("Assets/Sounds/walking/snow/snow1.wav");
	snowSounds[1] = pgeWavLoad("Assets/Sounds/walking/snow/snow2.wav");
	snowSounds[2] = pgeWavLoad("Assets/Sounds/walking/snow/snow3.wav");
	snowSounds[3] = pgeWavLoad("Assets/Sounds/walking/snow/snow4.wav");

    // Eat sounds
	eatSounds[0] = pgeWavLoad("Assets/Sounds/eat/eat1.wav");
	eatSounds[1] = pgeWavLoad("Assets/Sounds/eat/eat2.wav");
	eatSounds[2] = pgeWavLoad("Assets/Sounds/eat/eat3.wav");

    // Hit sounds
    hitSounds[0] = pgeWavLoad("Assets/Sounds/Damage/hit1.wav");
    hitSounds[1] = pgeWavLoad("Assets/Sounds/Damage/hit2.wav");
    hitSounds[2] = pgeWavLoad("Assets/Sounds/Damage/hit3.wav");

	//set default values
	currentWalkSound = 0;
	lastWalkSound = 0;

	playerSounds = true;
}

void SoundManager::PlayMenuSound()
{
	pgeWavPlay(buttonSound);
}

void SoundManager::PlayPlopSound()
{
	if(playerSounds)
		pgeWavPlay(plopSound);
}

void SoundManager::TNTSound()
{
	if(playerSounds)
		pgeWavPlay(tnt);
}

void SoundManager::PlayDoorSound(bool open)
{
	if(playerSounds)
    {
        open == true ? pgeWavPlay(doorOpen) : pgeWavPlay(doorClose);
    }
}

void SoundManager::PlayBreakSound()
{
	if(playerSounds)
		pgeWavPlay(breakSound);
}

void SoundManager::PlayBowSound()
{
	if(playerSounds)
		pgeWavPlay(bow);
}

void SoundManager::PlayZombieHurtSound(float distanceToPlayer)
{
	if(playerSounds)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(zombieHurtSounds[i],volume,volume);
            pgeWavPlay(zombieHurtSounds[i]);
        }
    }
}

void SoundManager::PlayZombieDieSound(float distanceToPlayer)
{
	if(playerSounds)
    {
        if(distanceToPlayer < 15.0f)
        {
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(zombieDieSound,volume,volume);
            pgeWavPlay(zombieDieSound);
        }
    }
}

void SoundManager::PlayCowHurtSound(float distanceToPlayer)
{
	if(playerSounds)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(cowHurtSounds[i],volume,volume);
            pgeWavPlay(cowHurtSounds[i]);
        }
    }
}

void SoundManager::PlayCowSaySound(float distanceToPlayer)
{
	if(playerSounds)
    {
        if(distanceToPlayer < 15.0f)
        {
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(zombieDieSound,volume,volume);
            pgeWavPlay(zombieDieSound);
        }
    }
}

void SoundManager::PlayHitSound()
{
	if(playerSounds)
    {
		pgeWavPlay(hitSounds[rand() % 3]);
    }
}

void SoundManager::PlayEatSound()
{
	if(playerSounds)
    {
		pgeWavPlay(eatSounds[rand() % 3]);
    }
}


void SoundManager::PlayFallSound(float i)
{
	if(playerSounds)
    {
        if (i < -9 && i > -21)
        {
            pgeWavPlay(fallSounds[1]);
        }
        if (i < -21)
        {
            pgeWavPlay(fallSounds[0]);
        }
    }
}

void SoundManager::PlayWalkSound(int type)
{
	if(playerSounds)
	{
		switch(type)
		{
			case 0://grass
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grassSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(grassSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 1://gravel
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grawelSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(grawelSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 2://stone
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(stoneSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(stoneSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 3://wood
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(woodSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(woodSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 4://cloth
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(clothSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(clothSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 5://sand
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(sandSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(sandSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 6://snow
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(snowSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(snowSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
		}
	}
}
