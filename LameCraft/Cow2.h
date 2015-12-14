#ifndef COW_H_
#define COW_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <psptypes.h>
#include <Aurora/Math/Frustum.h>

#include <Aurora/Math/BoundingBox.h>
#include <Aurora/Math/Frustum.h>

class CraftWorld;

class Cow
{
public:

    Cow(Vector3 position1, int number1);
    ~Cow();

    float DistanceToPlayer();
    float DistanceToHauntingPos();
    void TryToJump();
    void TryToMove(Vector3 movePosition1, float speed1);
    void TryToMoveWithoutJump(Vector3 movePosition1, float speed1);
    void SetPosition(Vector3 position1);
    void SetCollideBox(Vector3 collider1, Vector3 collider2);
    void UpdateBBox();
    void BoxCollision();
    void Update(CraftWorld *myWorld, Vector3 playerPos, float dt);
    void Render(Frustum &camFrustum);
    void TakeDamage(float damage, float power, float criticalPercent, float dt);

    float mainAngle;

    Vector3 position;
    Vector3 relPlayerPos;

    bool walkingOnGround;
    bool moving;
    bool angred;
    bool toDestroy;
    bool killed;
    bool kicked;
    bool nearToPlayer;
    bool damaged;
    bool rotate1;

    CraftWorld *world;

    float HP;
    float SPD;

    float damagedTimer;
    float kickTimer;

    BoundingBox bBox;

    int number;
    int helmetId, chestplateId, leggingsId, bootsId;

    bool playHurtSound;
    bool playDieSound;

private:

    Vector3 velocity;
    Vector3 colliderD;
    Vector3 colliderU;

    Vector3 legs, foot, body, head;


    float rLegAngle;
    float lLegAngle;

    float animLegAngle;
    float animLegAngleT;

    Vector3 hauntingPos;

    bool jumping;
    bool freezed;
    bool footInWater;
    bool footInLava;
    bool headInWater;
    bool headInLava;
    bool jumpReady;
    bool haunting;

    float jumpTimer;
    float freezedTimer;
    float hauntingTimer;
    float hauntingTimerMax;
    float checkCollisionTimer;

    float hauntingAngle;
};

#endif

