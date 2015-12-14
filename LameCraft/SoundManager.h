#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

extern "C"
{
    #include "sound_utils/pgeWav.h"
}

#include <stdlib.h>
#include <time.h>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static SoundManager m_SoundManager;
	static SoundManager* Instance();

	void Init();

    void PlayBreakSound();
    void PlayHitSound();
    void PlayEatSound();

    void PlayZombieHurtSound(float distanceToPlayer);
    void PlayZombieDieSound(float distanceToPlayer);

    void PlayCowHurtSound(float distanceToPlayer);
    void PlayCowSaySound(float distanceToPlayer);

    void PlayBowSound();
	void PlayMenuSound();
	void PlayPlopSound();
	void PlayWalkSound(int type);
	void TNTSound();
	void PlayDoorSound(bool open);
	void PlayFallSound(float i);

	bool playerSounds;
	bool ambientSoundsEnabled;

	int currentAmbientSound;

private:

	int currentWalkSound;
	int lastWalkSound;

	//sounds
	pgeWav *buttonSound;
	//plop sound
	pgeWav *plopSound;
	//grass sounds
	pgeWav *grassSounds[4];
	pgeWav *grawelSounds[4];
	pgeWav *stoneSounds[4];
	pgeWav *woodSounds[4];
	pgeWav *clothSounds[4];
	pgeWav *sandSounds[4];
	pgeWav *snowSounds[4];

	pgeWav *eatSounds[3];

	pgeWav *hitSounds[3];
    pgeWav *fallSounds[2];

    pgeWav *zombieHurtSounds[2];
    pgeWav *zombieDieSound;

    pgeWav *cowHurtSounds[2];
    pgeWav *cowSaySound;

	pgeWav *doorOpen;
	pgeWav *doorClose;
	pgeWav *tnt;
	pgeWav *bow;
	pgeWav *breakSound;

};

#endif

