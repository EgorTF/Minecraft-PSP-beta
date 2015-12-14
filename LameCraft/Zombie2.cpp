#include "Zombie2.h"
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define PIXEL 1.0f / 16.0f
#define GRAVITY -6.8f
#define JUMPVELOCITY 4.6f
#include "CraftWorld2.h"

/// SIMPLE TRIGONOMETRY

/// Degree range = 0 - 360
/// Radian range = 0 - 2*PI

/// PI * 0.5 = 90 deg
/// PI * 1.0 = 180 deg
/// PI * 1.5 = 270 deg
/// PI * 2.0 = 360 deg (full circle)

/// Degree to radian = deg/180*PI
/// Radian to degree = rad/PI*180

/// atan2f(x-other.x,z-other.z) - function to find the angle between two points

/// sinf and cosf working only with radians
/// x = sinf(rad) * length; y = cosf(rad) * length

/// END

Zombie::Zombie(Vector3 position1, int number1)
{
    world = NULL;

    position = position1;
    number = number1;

    SetCollideBox(Vector3(PIXEL*4,PIXEL*18,PIXEL*4),Vector3(PIXEL*4,PIXEL*12,PIXEL*4));
    bBox = BoundingBox(Vector3(0,0,0),Vector3(0,0,0));

    legs = Vector3(0,PIXEL*-6,0);
    body = Vector3(0,0,0);

    relPlayerPos = Vector3(0,0,0);
    velocity = Vector3(0,0,0);

    rHandAngle = PI / 2 + PI;
    lHandAngle = PI / 2 + PI;

    animHandAngle = 0.0f;
    animHandAngleT = 0.0f;

    animLegAngle = 0.0f;
    animLegAngleT = 0.0f;

    rLegAngle = PI;
    lLegAngle = PI;

    mainAngle = 0.0f;

    SPD = 1.0f;
    HP = 20.0f;

    toDestroy = false;
    freezed = false;
    angred = false;
    moving = false;
    jumping = false;
    jumpReady = true;
    footInWater = false;
    footInLava = false;
    headInWater = false;
    headInLava = false;
    walkingOnGround = true;
    kicked = false;
    damaged = false;
    nearToPlayer = false;
    killed = false;
    haunting = false;

    playDieSound = false;
    playHurtSound = false;


    kickTimer = 0.0f;
    damagedTimer = 0.0f;
    freezedTimer = 0.0f;
    jumpTimer = 0.0f;
    sunTimer = (rand() % 14)/10.0f;
    checkCollisionTimer = 0.0f;

    hauntingTimer = 0.0f;
    hauntingTimerMax = 0.0f;
    hauntingAngle = 0.0f;
    hauntingPos = Vector3(0,0,0);

    UpdateBBox();

    helmetId = -1;
    chestplateId = -1;
    leggingsId = -1;
    bootsId = -1;

    if(rand() % 125 < 3)
    {
        if(rand() % 2 == 0)
        {
            helmetId = 332;
        }
        else
        {
            helmetId = 344;
        }
    }

    if(rand() % 125 < 2)
    {
        if(rand() % 2 == 0)
        {
            chestplateId = 333;
        }
        else
        {
            chestplateId = 345;
        }
    }

    if(rand() % 125 < 2)
    {
        if(rand() % 2 == 0)
        {
            leggingsId = 334;
        }
        else
        {
            leggingsId = 346;
        }
    }

    if(rand() % 125 < 3)
    {
        if(rand() % 2 == 0)
        {
            bootsId = 334;
        }
        else
        {
            bootsId = 347;
        }
    }
}


Zombie::~Zombie()
{

}


float Zombie::DistanceToPlayer() /// TAXICAB DISTANCE
{
    return abs(relPlayerPos.x-position.x) + abs(relPlayerPos.z-position.z) + abs(relPlayerPos.y-position.y);
}


float Zombie::DistanceToHauntingPos() /// TAXICAB DISTANCE
{
    return abs(hauntingPos.x-position.x) + abs(hauntingPos.z-position.z);
}


void Zombie::TryToJump()
{
    if (headInWater || headInLava)
    {
        if (walkingOnGround)
        {
            jumping = true;
        }
        else
        {
            velocity.y = 0.2 * JUMPVELOCITY;
            walkingOnGround = false;
        }
    }
    if ((!headInWater || !headInLava) && !walkingOnGround && (footInWater || footInLava))
    {
        velocity.y = 1.25 * JUMPVELOCITY;
        walkingOnGround = false;
    }
    if(walkingOnGround)
    {
        jumping = true;
    }
    else
    {
        jumping = false;
    }
}


void Zombie::TryToMove(Vector3 movePosition1, float speed)
{
    Vector3 movePosition = position + Vector3(movePosition1.x*(speed+0.2),0.0f,movePosition1.z*(speed+0.2));
    Vector3 movePositionHead = movePosition + head;
    Vector3 movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        Vector3 collisionPosition = position + Vector3(sinf(mainAngle)*(speed+0.25),0.0f,cosf(mainAngle)*(speed+0.25));
        position += Vector3(movePosition1.x*speed,0.0f,movePosition1.z*speed);

        moving = true;
    }
    else
    {
        if(jumpReady == true)
        {
            TryToJump();
            jumpReady = false;
        }
        moving = false;
    }

    movePosition = position + Vector3(movePosition1.x*(speed+0.2),0.0f,0.0f);
    movePositionHead = movePosition + head;
    movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        position += Vector3(movePosition1.x*speed,0.0f,0);
    }
    else
    {
        if(jumpReady == true)
        {
            TryToJump();
            jumpReady = false;
        }
    }

    movePosition = position + Vector3(0.0f,0.0f,movePosition1.z*(speed+0.2));
    movePositionHead = movePosition + head;
    movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        position += Vector3(0.0f,0.0f,movePosition1.z*speed);
    }
    else
    {
        if(jumpReady == true)
        {
            TryToJump();
            jumpReady = false;
        }
    }
}


void Zombie::TryToMoveWithoutJump(Vector3 movePosition1, float speed)
{
    Vector3 movePosition = position + Vector3(movePosition1.x*(speed+0.2),0.0f,movePosition1.z*(speed+0.2));
    Vector3 movePositionHead = movePosition + head;
    Vector3 movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        Vector3 collisionPosition = position + Vector3(sinf(mainAngle)*(speed+0.25),0.0f,cosf(mainAngle)*(speed+0.25));
        position += Vector3(movePosition1.x*speed,0.0f,movePosition1.z*speed);

        moving = true;
    }
    else
    {
        moving = false;
    }

    movePosition = position + Vector3(movePosition1.x*(speed+0.2),0.0f,0.0f);
    movePositionHead = movePosition + head;
    movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        position += Vector3(movePosition1.x*speed,0.0f,0);
    }


    movePosition = position + Vector3(0.0f,0.0f,movePosition1.z*(speed+0.2));
    movePositionHead = movePosition + head;
    movePositionFoot = movePosition + Vector3(foot.x,foot.y+0.1,foot.z);

    if (!world->SolidAtPointForEntity(movePosition,colliderD) && !world->SolidAtPointForEntity(movePositionHead,colliderU) && !world->SolidAtPointForEntity(movePositionFoot,colliderD))
    {
        position += Vector3(0.0f,0.0f,movePosition1.z*speed);
    }
}


void Zombie::SetPosition(Vector3 position1)
{
    position = position1;
}


void Zombie::SetCollideBox(Vector3 collider1, Vector3 collider2)
{
    colliderD = collider1;
    colliderU = collider2;

    foot = Vector3(0,-collider1.y,0);
    head = Vector3(0,collider2.y,0);
}


void Zombie::UpdateBBox()
{
    bBox = BoundingBox(Vector3(position.x-colliderU.x*1.5,position.y-colliderU.y*1.5,position.z-colliderU.z*1.5),Vector3(position.x+colliderD.x*1.5,position.y+colliderD.y*1.5,position.z+colliderD.z*1.5));
}


void Zombie::BoxCollision()
{
    for(int x = 0; x < world->mZombies.size(); x++)
    {
        Zombie *TestZombie2 = world->mZombies[x];
        if(TestZombie2->number != number && (TestZombie2->position.x != position.x || TestZombie2->position.z != position.z || TestZombie2->position.y != position.y))
        {
            if(TestZombie2->bBox.intersect(bBox))
            {
                float angle1 = atan2f(position.x-TestZombie2->position.x,position.z-TestZombie2->position.z); // super secret function

                TryToMove(Vector3(sinf(angle1),0.0f,cosf(angle1)),SPD*0.05f);
            }
        }
    }
}


void Zombie::TakeDamage(float damage, float power, float criticalPercent, float dt)
{
    float AP = 2.0f;
    if(helmetId != -1)
    {
        AP += 2.0f;
    }
    if(chestplateId != -1)
    {
        AP += 4.0f;
    }
    if(leggingsId != -1)
    {
        AP += 3.0f;
    }
    if(bootsId != -1)
    {
        AP += 2.0f;
    }

    HP -= damage*(1.0+(AP-20.0f)/30.0f);
    if(rand() % 100 < criticalPercent)
    {
        HP -= damage;
    }

    kicked = true;
    damaged = true;
    damagedTimer = power*0.6f;
    velocity.y = (power+(rand()%5)/10.0f) * JUMPVELOCITY;
    walkingOnGround = false;

    position += velocity * dt;
    playHurtSound = true;
}


void Zombie::Update(CraftWorld *myWorld, Vector3 playerPos, float dt)
{
    world = myWorld;
    if(toDestroy == false)
    {
        relPlayerPos = playerPos;
        if(DistanceToPlayer() < 65)
        {
            freezedTimer = 0.0f;
            if(HP <= 0.0f)
            {
                killed = true;
                playDieSound = true;
                return;
            }

            UpdateBBox();


            /// TIMERS --- *

            jumpTimer += dt;
            if(jumpTimer > 0.2f)
            {
                jumpReady = true;
                jumpTimer = 0.0f;
            }

            sunTimer += dt;
            if(sunTimer > 1.5f)
            {
                if(world->worldDayTime > 6 && world->worldDayTime < 21)
                {
                    HP -= 2.0f;
                    damaged = true;
                    damagedTimer = 0.8f;

                    playHurtSound = true;
                }
                sunTimer = 0.0f;
            }



            if(damaged == true)
            {
                if(damagedTimer > 0.0f)
                {
                    damagedTimer -= dt;
                }
                else
                {
                    damagedTimer = 0.0f;
                    damaged = false;
                }
            }



            if(DistanceToPlayer() < 1.5)
            {
                if(nearToPlayer == false)
                {
                    kickTimer = 0.93f;
                }
                nearToPlayer = true;
            }
            else
            {
                nearToPlayer = false;
            }



            if(nearToPlayer == true)
            {
                kickTimer += dt;
                if(kickTimer >= 1.0f)
                {
                    if(world->HP > 0)
                    {
                        world->kickedStart = true;
                        world->kickedAngle = atan2f(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI;
                    }

                    kickTimer = 0.0f;
                }
            }

            /// * --- END



            /// BECOME ANGRY --- *
            if(DistanceToPlayer() < 15) // it sees you
            {
                haunting = false;
                hauntingTimer = 0.0f;
                hauntingTimerMax = 0.0f;
                hauntingPos = Vector3(0,0,0);
                hauntingAngle = 0.0f;

                if(DistanceToPlayer() > 1.3)
                {
                    angred = true;
                }
                else
                {
                    moving = false;
                }
            }
            else // it doesn't see the player
            {
                moving = false;
                angred = false;
                haunting = true;

                if(hauntingTimerMax == 0.0f)
                {
                    hauntingTimerMax = 5.0f + rand() % 6;
                }

                if(hauntingTimer < hauntingTimerMax)
                {
                    hauntingTimer += dt;
                }
                if(hauntingTimer >= hauntingTimerMax)
                {
                    hauntingTimer = 0.0f;
                    if(rand()%100 < 80) // walk to some point nearby
                    {

                        hauntingTimerMax = 6.0f + rand() % 5;

                        hauntingPos.x = position.x - 6 + (rand() % 130)/10.0f;
                        hauntingPos.z = position.z - 6 + (rand() % 130)/10.0f;

                        if(hauntingPos.x > 160)
                        {
                            hauntingPos.x = 160;
                        }
                        if(hauntingPos.x < 2)
                        {
                            hauntingPos.x = 2;
                        }

                        if(hauntingPos.z > 160)
                        {
                            hauntingPos.z = 160;
                        }
                        if(hauntingPos.z < 2)
                        {
                            hauntingPos.z = 2;
                        }

                        hauntingAngle = atan2f(position.x-hauntingPos.x,position.z-hauntingPos.z)+PI;
                    }
                    else // just rotate about its own position
                    {
                        hauntingTimerMax = 2.0f+rand()%3;
                        hauntingAngle = (rand() % 360)/180.0f*PI;

                        hauntingPos = Vector3(-1,-1,-1);
                    }
                }
            }
            /// * --- END


            /// SWIMING --- *
            if(world->PlayerInWater(position) == true && jumpReady == true)
            {
                TryToJump();
                jumpReady = false;
            }
            /// * --- END



            /// MOVING WHEN ANGRY ---- *
            if(angred == true && kicked == false)
            {
                checkCollisionTimer += dt;
                if(checkCollisionTimer >= 0.1f)
                {
                    BoxCollision();
                    checkCollisionTimer = 0.0f;
                }
                mainAngle = atan2f(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI; // super secret line
                TryToMove(Vector3(sinf(mainAngle),0.0f,cosf(mainAngle)),SPD*dt);
            }
            /// * --- END


            /// HAUNTING --- *
            if(haunting == true)
            {
                if(hauntingPos.x != 0 && hauntingPos.z != 0)
                {
                    if(DistanceToHauntingPos() > 0.5f)
                    {
                        if(hauntingPos != Vector3(-1,-1,-1))
                        {
                            mainAngle = hauntingAngle;
                            TryToMove(Vector3(sinf(mainAngle),0.0f,cosf(mainAngle)),SPD*dt);
                        }
                        else
                        {
                            if(mainAngle != hauntingAngle)
                            {
                                mainAngle += sinf(hauntingAngle-mainAngle)*0.07f;
                            }

                            if(abs(mainAngle - hauntingAngle) < 0.02f)
                            {
                                mainAngle = hauntingAngle;
                            }
                        }
                    }
                    else
                    {
                        hauntingPos.x = 0;
                        hauntingPos.z = 0;
                    }
                }
            }
            /// * --- END


            /// MOVING WHEN KICKED ---- *
            if(kicked == true)
            {
                mainAngle = atan2f(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI; // super secret function
                TryToMoveWithoutJump(Vector3(sinf(mainAngle+PI),0.0f,cosf(mainAngle+PI)),SPD*1.5f*dt);

                if (walkingOnGround == true || footInLava || footInWater)
                {
                    kicked = false;
                }
            }
            /// * --- END



            /// ANIMATIONS  --- *
            animHandAngleT += PI*dt*0.75;
            if(animHandAngleT >= PI*2)
            {
                animHandAngleT = 0.0f;
            }
            animHandAngle = sinf(animHandAngleT) * 0.09f;

            if(moving == true)
            {
                animLegAngleT += PI*dt*1.5;
                if(animLegAngleT >= PI*2)
                {
                    animLegAngleT = 0.0f;
                }
            }
            else
            {
                if (animLegAngleT > 0 && animLegAngleT < PI/2)
                {
                    animLegAngleT -= animLegAngleT * 0.3f;
                    if (animLegAngleT < 0.05)
                    {
                        animLegAngleT = 0;
                    }
                }
                if (animLegAngleT >= PI/2 && animLegAngleT < PI)
                {
                    animLegAngleT += (PI-animLegAngleT) * 0.3f;
                    if (animLegAngleT > PI - 0.05)
                    {
                        animLegAngleT = 0;
                    }
                }
                if (animLegAngleT > PI && animLegAngleT < PI*1.5)
                {
                    animLegAngleT -= (animLegAngleT-PI) * 0.3f;
                    if (animLegAngleT < PI + 0.05)
                    {
                        animLegAngleT = 0;
                    }
                }
                if (animLegAngleT >= PI*1.5 && animLegAngleT < PI*2)
                {
                    animLegAngleT += (2*PI-animLegAngleT) * 0.3f;
                    if (animLegAngleT > 2*PI - 0.05)
                    {
                        animLegAngleT = 0;
                    }
                }
            }
            animLegAngle = sinf(animLegAngleT) * 0.7f;
            /// * --- END



            /// SIMEPLE MOB PHYSICS --- *

                Vector3 footPosition = position + foot;
                Vector3 legsPosition = position + legs;
                Vector3 headPosition = position + head;

                if(world->PlayerInWater(legsPosition))
                    footInWater = true;
                else
                    footInWater = false;

                if(world->PlayerInWater(headPosition))
                {
                    if (velocity.y > -3)
                    {
                        velocity.y += (GRAVITY/3.0f) * dt;
                    }
                    else
                    {
                        velocity.y = -3;
                    }
                    headInWater = true;
                }
                else
                {
                    headInWater = false;
                    velocity.y += (GRAVITY*1.3 * dt) * 1.6f;
                }

                if(world->PlayerInLava(legsPosition))
                {
                    footInLava = true;
                    HP -= 0.5f;
                }
                else
                {
                    footInLava = false;
                }

                if(world->PlayerInLava(headPosition))
                {
                    velocity.y += (GRAVITY/3.0f) * dt;
                    headInLava = true;
                    HP -= 1;
                }
                else
                {
                    headInLava = false;
                    velocity.y += GRAVITY * dt;
                }

                if(world->SolidAtPointForEntity(footPosition,colliderD) || world->SolidAtPointForEntity(headPosition,colliderU))
                {
                    walkingOnGround = true;
                    if (world->SolidAtPointForEntity(headPosition,colliderU))
                    {
                        int blockIn = (int)(headPosition.y);
                        position.y = (float)(blockIn - colliderU.y - 0.05);
                    }
                    if (world->SolidAtPointForEntity(footPosition,colliderD))
                    {
                        int blockOn = (int)(footPosition.y);
                        position.y = (float)(blockOn + 1 + colliderD.y - 0.05);
                    }

                   /* if(velocity.y != 0.0f) /// FALL DAMAGE
                    {
                        if (!world->PlayerInWater(footPosition))
                        {
                            if(velocity.y < -12 && velocity.y > -19)
                            {
                                health -= (int)((velocity.y*-1) - 11) / 1.4;
                            }
                            if(velocity.y < -19)
                            {
                                health -= (int)((velocity.y*-1) - 11) * 1.3f;
                            }
                        }
                    }*/
                    velocity.y = 0.0f;

                    if(jumping == true)
                    {
                        velocity.y = 1.55f * JUMPVELOCITY;
                        jumping = false;
                        walkingOnGround = false;
                    }
                }
                else
                {
                    walkingOnGround = false;
                }
                position += velocity * dt;

            /// * --- END


        }
        else
        {
            freezedTimer += dt;
            if(freezedTimer >= 60.0f)
            {
                toDestroy = true;
            }
        }
    }
}

void Zombie::Render(Frustum &camFrustum)
{
    if(toDestroy == false)
    {
        if(DistanceToPlayer() < 60 && camFrustum.BoxInFrustum(bBox) == Frustum::Intersects)
        {
            float myLight = world->BlockFinalLight(position.x,position.y+1,position.z);
            if(damaged == true)
            {
                sceGuColor(GU_COLOR(0.8f,0.1,0.1,1.0f));
            }
            else
            {
                sceGuColor(GU_COLOR(myLight,myLight,myLight,1.0f));
            }

            sceGuEnable(GU_TEXTURE_2D);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuEnable(GU_ALPHA_TEST);
            sceGuEnable(GU_BLEND);

            sceGumPushMatrix();
            ScePspFVector3 loc = {position.x,position.y,position.z};
            sceGumTranslate(&loc);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->bodyVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc2 = {position.x,position.y+PIXEL*10,position.z};
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->headVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc3 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*6),position.y+PIXEL*4,position.z+(cosf(mainAngle-PI/2)*PIXEL*6)};
            sceGumTranslate(&loc3);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rHandAngle-animHandAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc4 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*6),position.y+PIXEL*4,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*6)};
            sceGumTranslate(&loc4);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lHandAngle+animHandAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc5 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle-PI/2)*PIXEL*2)};
            sceGumTranslate(&loc5);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rLegAngle+animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc6 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2)};
            sceGumTranslate(&loc6);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lLegAngle-animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            // boot
            if(bootsId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc11 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle-PI/2)*PIXEL*2)};
                sceGumTranslate(&loc11);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rLegAngle+animLegAngle);

                world->drawArmor(bootsId,myLight);
                sceGumPopMatrix();
            }


            // boot
            if(bootsId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc12 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2)};
                sceGumTranslate(&loc12);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lLegAngle-animLegAngle);

                world->drawArmor(bootsId,myLight);
                sceGumPopMatrix();
            }


            // legging
            if(leggingsId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc9 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle-PI/2)*PIXEL*2)};
                sceGumTranslate(&loc9);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rLegAngle+animLegAngle);

                world->drawArmor(leggingsId,myLight);
                sceGumPopMatrix();
            }


            // legging
            if(leggingsId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc10 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2),position.y-PIXEL*8,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2)};
                sceGumTranslate(&loc10);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lLegAngle-animLegAngle);

                world->drawArmor(leggingsId,myLight);
                sceGumPopMatrix();
            }


            // chestplate
            if(chestplateId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc8 = {position.x,position.y,position.z};
                sceGumTranslate(&loc8);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(0.0f);

                world->drawArmor(chestplateId,myLight);
                sceGumPopMatrix();

                // right shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc3 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*6),position.y+PIXEL*4,position.z+(cosf(mainAngle-PI/2)*PIXEL*6)};
                sceGumTranslate(&loc3);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rHandAngle-animHandAngle);
                world->drawShoulder(chestplateId,myLight);
                sceGumPopMatrix();

                // left shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc4 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*6),position.y+PIXEL*4,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*6)};
                sceGumTranslate(&loc4);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lHandAngle+animHandAngle);
                world->drawShoulder(chestplateId,myLight);
                sceGumPopMatrix();
            }


            // helmet
            if(helmetId != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc7 = {position.x,position.y+PIXEL*10,position.z};
                sceGumTranslate(&loc7);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(0.0f);

                world->drawArmor(helmetId,myLight);
                sceGumPopMatrix();
            }


            sceGuDisable(GU_BLEND);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDisable(GU_TEXTURE_2D);
            sceGuColor(0xFFFFFFFF);
        }
    }
}

