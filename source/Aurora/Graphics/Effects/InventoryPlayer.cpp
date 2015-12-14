#include <Aurora/Graphics/Effects/InventoryPlayer.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define PIXEL 1.0f / 16.0f
#define GRAVITY -6.8f
#define JUMPVELOCITY 4.6f

namespace Aurora
{
	namespace Graphics
	{
		InventoryPlayer::InventoryPlayer()
		{
            rHandAngle = PI;
            lHandAngle = PI;
            rLegAngle = PI;
            lLegAngle = PI;

            mainAngle = 0.0f;
            scale = 1.0f;

            position = Vector3(0,0,0);
            animT = 0.0f;
		}

		InventoryPlayer::~InventoryPlayer()
		{

		}

		void  InventoryPlayer::Update()
		{

		}

		void InventoryPlayer::Render(CraftWorld *world, float dt, float angle, int texNum)
		{
            animT += PI*dt*0.5f;
            if(animT >= 2*PI)
            {
                animT = 0.0f;
            }

            sceGuEnable(GU_TEXTURE_2D);
            sceGuEnable(GU_ALPHA_TEST);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);

            // right hand
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc3 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*6*scale),position.y+PIXEL*4*scale,position.z+(cosf(mainAngle-PI/2)*PIXEL*6*scale)};
            sceGumTranslate(&loc3);

            sceGumRotateX(-0.125+sinf(animT)*0.125);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rHandAngle-0.125+sinf(animT)*0.125);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();

            // left hand
            sceGumPushMatrix();
            ScePspFVector3 loc4 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*6*scale),position.y+PIXEL*4*scale,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*6*scale)};
            sceGumTranslate(&loc4);

            sceGumRotateX(0.125+sinf(animT+PI)*0.125);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lHandAngle+0.125+sinf(animT+PI)*0.125);
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();


            // right leg
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc5 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle-PI/2)*PIXEL*2*scale)};
            sceGumTranslate(&loc5);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(rLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            // left leg
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc6 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2*scale)};
            sceGumTranslate(&loc6);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(lLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            // body
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc = {position.x,position.y,position.z};
            sceGumTranslate(&loc);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->bodyVertices);
            sceGumPopMatrix();



            // head
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc2 = {position.x,position.y+PIXEL*10*scale,position.z};
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(mainAngle-PI/2);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->headVertices);
            sceGumPopMatrix();


            // boot
            if(world->armorId[3] != 327)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc11 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle-PI/2)*PIXEL*2*scale)};
                sceGumTranslate(&loc11);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rLegAngle);

                world->drawArmor(world->armorId[3],1.0f);
                sceGumPopMatrix();
            }


            // boot
            if(world->armorId[3] != 327)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc12 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2*scale)};
                sceGumTranslate(&loc12);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lLegAngle);

                world->drawArmor(world->armorId[3],1.0f);
                sceGumPopMatrix();
            }


            // legging
            if(world->armorId[2] != 326)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc9 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle-PI/2)*PIXEL*2*scale)};
                sceGumTranslate(&loc9);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rLegAngle);

                world->drawArmor(world->armorId[2],1.0f);
                sceGumPopMatrix();
            }


            // legging
            if(world->armorId[2] != 326)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc10 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*2*scale),position.y-PIXEL*8*scale,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*2*scale)};
                sceGumTranslate(&loc10);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lLegAngle);

                world->drawArmor(world->armorId[2],1.0f);
                sceGumPopMatrix();
            }


            // chestplate
            if(world->armorId[1] != 325)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc8 = {position.x,position.y,position.z};
                sceGumTranslate(&loc8);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(0.0f);

                world->drawArmor(world->armorId[1],1.0f);
                sceGumPopMatrix();

                // right shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc3 = {position.x+(sinf(mainAngle-PI/2)*PIXEL*6*scale),position.y+PIXEL*4*scale,position.z+(cosf(mainAngle-PI/2)*PIXEL*6*scale)};
                sceGumTranslate(&loc3);

                sceGumRotateX(-0.125+sinf(animT)*0.125);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(rHandAngle-0.125+sinf(animT)*0.125);
                world->drawShoulder(world->armorId[1],1.0f);
                sceGumPopMatrix();

                // left shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc4 = {position.x+(sinf(mainAngle+PI-PI/2)*PIXEL*6*scale),position.y+PIXEL*4*scale,position.z+(cosf(mainAngle+PI-PI/2)*PIXEL*6*scale)};
                sceGumTranslate(&loc4);

                sceGumRotateX(0.125+sinf(animT+PI)*0.125);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(lHandAngle+0.125+sinf(animT+PI)*0.125);
                world->drawShoulder(world->armorId[1],1.0f);
                sceGumPopMatrix();
            }


            // helmet
            if(world->armorId[0] != 324)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc7 = {position.x,position.y+PIXEL*10*scale,position.z};
                sceGumTranslate(&loc7);

                sceGumRotateX(0.0f);
                sceGumRotateY(mainAngle-PI/2);
                sceGumRotateZ(0.0f);

                world->drawArmor(world->armorId[0],1.0f);
                sceGumPopMatrix();
            }


            sceGuDisable(GU_DEPTH_TEST);
            sceGuDisable(GU_BLEND);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_TEXTURE_2D);
            sceGuColor(0xFFFFFFFF);
		}
	}
}

