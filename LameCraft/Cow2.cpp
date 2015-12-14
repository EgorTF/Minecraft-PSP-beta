#include "Cow2.h"
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define PIXEL 1.0f / 16.0f
#define GRAVITY -6.8f
#define JUMPVELOCITY 4.6f
#include "CraftWorld2.h"

Cow::Cow(Vector3 position1, int number1)
{
    world = NULL;

    position = position1;
    number = number1;

    legs = Vector3(0,-6*PIXEL,0);
    body = Vector3(0,0,0);
    foot = Vector3(0,0,0);
    head = Vector3(0,0,0);
    colliderD = Vector3(0,0,0);
    colliderU = Vector3(0,0,0);

    SetCollideBox(Vector3(PIXEL*7,PIXEL*17,PIXEL*7),Vector3(PIXEL*7,PIXEL*10,PIXEL*7));
    bBox = BoundingBox(Vector3(0,0,0),Vector3(0,0,0));

    relPlayerPos = Vector3(0,0,0);
    velocity = Vector3(0,0,0);

    animLegAngle = 0.0f;
    animLegAngleT = 0.0f;

    rLegAngle = PI;
    lLegAngle = PI;

    mainAngle = 0.0f;

    SPD = 1.0f;
    HP = 14.0f;

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
    rotate1 = false;

    playDieSound = false;
    playHurtSound = false;


    kickTimer = 0.0f;
    damagedTimer = 0.0f;
    freezedTimer = 0.0f;
    jumpTimer = 0.0f;
    checkCollisionTimer = 0.0f;

    hauntingTimer = 0.0f;
    hauntingTimerMax = 0.0f;
    hauntingAngle = 0.0f;
    hauntingPos = Vector3(0,0,0);

    UpdateBBox();
}


Cow::~Cow()
{

}


float Cow::DistanceToPlayer() /// TAXICAB DISTANCE
{
    return abs(relPlayerPos.x-position.x) + abs(relPlayerPos.z-position.z) + abs(relPlayerPos.y-position.y);
}


float Cow::DistanceToHauntingPos() /// TAXICAB DISTANCE
{
    return abs(hauntingPos.x-position.x) + abs(hauntingPos.z-position.z);
}


void Cow::TryToJump()
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


void Cow::TryToMove(Vector3 movePosition1, float speed)
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


void Cow::TryToMoveWithoutJump(Vector3 movePosition1, float speed)
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


void Cow::SetPosition(Vector3 position1)
{
    position = position1;
}


void Cow::SetCollideBox(Vector3 collider1, Vector3 collider2)
{
    colliderD = collider1;
    colliderU = collider2;

    foot = Vector3(0,-collider1.y,0);
    head = Vector3(0,collider2.y,0);
}


void Cow::UpdateBBox()
{
    bBox = BoundingBox(Vector3(position.x-colliderU.x*1.5,position.y-colliderU.y*1.5,position.z-colliderU.z*1.5),Vector3(position.x+colliderD.x*1.5,position.y+colliderD.y*1.5,position.z+colliderD.z*1.5));
}


void Cow::BoxCollision()
{
    for(int x = 0; x < world->mCows.size(); x++)
    {
        Cow *TestCow2 = world->mCows[x];
        if(TestCow2->number != number && (TestCow2->position.x != position.x || TestCow2->position.z != position.z || TestCow2->position.y != position.y))
        {
            if(TestCow2->bBox.intersect(bBox))
            {
                float angle1 = atan2f(position.x-TestCow2->position.x,position.z-TestCow2->position.z); // super secret function

                TryToMove(Vector3(sinf(angle1),0.0f,cosf(angle1)),SPD*0.05f);
            }
        }
    }
}


void Cow::TakeDamage(float damage, float power, float criticalPercent, float dt)
{
    HP -= damage;
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


void Cow::Update(CraftWorld *myWorld, Vector3 playerPos, float dt)
{
    world = myWorld;
    relPlayerPos = playerPos;
    if(toDestroy == false)
    {
        relPlayerPos = playerPos;
        if(DistanceToPlayer() < 65)
        {
            freezedTimer = 0.0f;
            if(HP <= 0.0f)
            {
                killed = true;
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
                nearToPlayer = true;
            }
            else
            {
                nearToPlayer = false;
            }
            /// * --- END


            /// SWIMING --- *
            if(world->PlayerInWater(position) == true && jumpReady == true)
            {
                TryToJump();
                jumpReady = false;
            }
            /// * --- END


            /// HAUNTING --- *
            moving = false;


            if(hauntingTimer < hauntingTimerMax)
            {
                hauntingTimer += dt;
            }
            if(hauntingTimer >= hauntingTimerMax)
            {
                rotate1 = false;
                hauntingTimer = 0.0f;
                if(rand()%100 < 80)
                {
                    hauntingTimerMax = 5.0f + rand() % 3;

                    hauntingPos.x = position.x - 6 + (rand() % 120)/10.0f;
                    hauntingPos.z = position.z - 6 + (rand() % 120)/10.0f;

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
                    hauntingTimerMax = 2.0f+(rand()%20)/10.0f;
                    hauntingAngle = (rand() % 360)/180.0f*PI;

                    hauntingPos = Vector3(-1,-1,-1);
                }
            }


            if(hauntingPos.x != 0 && hauntingPos.z != 0)
            {
                if(DistanceToHauntingPos() > 0.5f)
                {
                    if(hauntingPos != Vector3(-1,-1,-1))
                    {
                        if(mainAngle != hauntingAngle)
                        {
                            mainAngle += sinf(hauntingAngle-mainAngle)*0.07f;
                        }

                        if(abs(mainAngle - hauntingAngle) < 0.02f)
                        {
                            mainAngle = hauntingAngle;
                        }
                       // mainAngle = hauntingAngle;
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

            if(kicked == true)
            {
                checkCollisionTimer += dt;
                if(checkCollisionTimer >= 0.1f)
                {
                    BoxCollision();
                    checkCollisionTimer = 0.0f;
                }
            }
            /// * --- END


            /// MOVING WHEN KICKED ---- *
            if(kicked == true)
            {
                haunting = false;
                hauntingTimer = 0.0f;
                hauntingPos.x = 0;
                hauntingPos.z = 0;

                float mainAngle2 = atan2f(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI; // super secret function
                TryToMoveWithoutJump(Vector3(sinf(mainAngle2+PI),0.0f,cosf(mainAngle2+PI)),SPD*1.5f*dt);

                if (walkingOnGround == true || footInLava || footInWater)
                {
                    kicked = false;

                    hauntingTimerMax = 3.0f + rand() % 3;

                    hauntingPos.x = position.x - 5 + (rand() % 100)/10.0f;
                    hauntingPos.z = position.z - 5 + (rand() % 100)/10.0f;

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
            }
            /// * --- END



            /// ANIMATIONS  --- *
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
            animLegAngle = sinf(animLegAngleT) * 0.8f;
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
            if(freezedTimer >= 240.0f)
            {
                toDestroy = true;
            }
        }
    }
}

void Cow::Render(Frustum &camFrustum)
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

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowBodyVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc2 = {position.x+(sinf(mainAngle)*PIXEL*12),position.y+PIXEL*3,position.z+(cosf(mainAngle)*PIXEL*12)};
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowHeadVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc3 = {position.x+(sinf(mainAngle+atan2f(-PIXEL*4,PIXEL*7))*PIXEL*7),position.y-PIXEL*6,position.z+(cosf(mainAngle+atan2f(-PIXEL*4,PIXEL*7))*PIXEL*7)};
            sceGumTranslate(&loc3);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rLegAngle+animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowLegVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc4 = {position.x+(sinf(mainAngle+atan2f(PIXEL*4,PIXEL*7))*PIXEL*7),position.y-PIXEL*6,position.z+(cosf(mainAngle+atan2f(PIXEL*4,PIXEL*7))*PIXEL*7)};
            sceGumTranslate(&loc4);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lLegAngle-animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowLegVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc5 = {position.x+(sinf(mainAngle+atan2f(-PIXEL*4,-PIXEL*7))*PIXEL*7),position.y-PIXEL*6,position.z+(cosf(mainAngle+atan2f(-PIXEL*4,-PIXEL*7))*PIXEL*7)};
            sceGumTranslate(&loc5);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rLegAngle+animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowLegVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc6 = {position.x+(sinf(mainAngle+atan2f(PIXEL*4,-PIXEL*7))*PIXEL*7),position.y-PIXEL*6,position.z+(cosf(mainAngle+atan2f(PIXEL*4,-PIXEL*7))*PIXEL*7)};
            sceGumTranslate(&loc6);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lLegAngle-animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->cowLegVertices);
            sceGumPopMatrix();


            sceGuDisable(GU_BLEND);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDisable(GU_TEXTURE_2D);
            sceGuColor(0xFFFFFFFF);
        }
    }
}

