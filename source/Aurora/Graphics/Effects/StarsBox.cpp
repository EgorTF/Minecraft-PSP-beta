#include <Aurora/Graphics/Effects/StarsBox.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)

namespace Aurora
{
	namespace Graphics
	{
		StarsBox::StarsBox()
		{
			boxVertices = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			boxVertices2 = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			boxVertices3 = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			boxVertices4 = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			boxVertices5 = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			boxVertices6 = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));

			size = 0.4f;
		}

		StarsBox::~StarsBox()
		{
			free(boxVertices);
			free(boxVertices2);
			free(boxVertices3);
			free(boxVertices4);
			free(boxVertices5);
			free(boxVertices6);
		}

		void StarsBox::Update(float alpha)
		{
		    int i = 0;

		    if(alpha > 1.0f)
            {
                alpha = 1.0f;
            }
		    if(alpha < 0.0f)
            {
                alpha = 0.0f;
            }

			boxVertices[i].x = size;
			boxVertices[i].y = -size;
			boxVertices[i].z = size;
			boxVertices[i].u = 1;
			boxVertices[i].v = 1;
			boxVertices[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices[i].x = size;
			boxVertices[i].y = size;
			boxVertices[i].z = size;
            boxVertices[i].u = 1;
			boxVertices[i].v = 0;
			boxVertices[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices[i].x = size;
			boxVertices[i].y = size;
			boxVertices[i].z = -size;
            boxVertices[i].u = 0;
			boxVertices[i].v = 0;
			boxVertices[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices[i].x = size;
			boxVertices[i].y = -size;
			boxVertices[i].z = -size;
			boxVertices[i].u = 0;
			boxVertices[i].v = 1;
			boxVertices[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices,4 * sizeof(CraftPSPVertex));

            i = 0;

			boxVertices2[i].x = -size;
			boxVertices2[i].y = -size;
			boxVertices2[i].z = -size;
			boxVertices2[i].u = 1;
			boxVertices2[i].v = 1;
			boxVertices2[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices2[i].x = -size;
			boxVertices2[i].y = size;
			boxVertices2[i].z = -size;
            boxVertices2[i].u = 1;
			boxVertices2[i].v = 0;
			boxVertices2[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices2[i].x = -size;
			boxVertices2[i].y = size;
			boxVertices2[i].z = size;
            boxVertices2[i].u = 0;
			boxVertices2[i].v = 0;
			boxVertices2[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices2[i].x = -size;
			boxVertices2[i].y = -size;
			boxVertices2[i].z = size;
			boxVertices2[i].u = 0;
			boxVertices2[i].v = 1;
			boxVertices2[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices2,4 * sizeof(CraftPSPVertex));

            i = 0;

			boxVertices3[i].x = -size;
			boxVertices3[i].y = size;
			boxVertices3[i].z = size;
			boxVertices3[i].u = 1;
			boxVertices3[i].v = 0;
			boxVertices3[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices3[i].x = size;
			boxVertices3[i].y = size;
			boxVertices3[i].z = size;
			boxVertices3[i].u = 0;
			boxVertices3[i].v = 0;
			boxVertices3[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices3[i].x = size;
			boxVertices3[i].y = -size;
			boxVertices3[i].z = size;
			boxVertices3[i].u = 0;
			boxVertices3[i].v = 1;
			boxVertices3[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices3[i].x = -size;
			boxVertices3[i].y = -size;
			boxVertices3[i].z = size;
			boxVertices3[i].u = 1;
			boxVertices3[i].v = 1;
			boxVertices3[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices3,4 * sizeof(CraftPSPVertex));

            i = 0;

			boxVertices4[i].x = -size;
			boxVertices4[i].y = -size;
			boxVertices4[i].z = -size;
			boxVertices4[i].u = 0;
			boxVertices4[i].v = 1;
			boxVertices4[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices4[i].x = size;
			boxVertices4[i].y = -size;
			boxVertices4[i].z = -size;
            boxVertices4[i].u = 1;
			boxVertices4[i].v = 1;
			boxVertices4[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices4[i].x = size;
			boxVertices4[i].y = size;
			boxVertices4[i].z = -size;
            boxVertices4[i].u = 1;
			boxVertices4[i].v = 0;
			boxVertices4[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices4[i].x = -size;
			boxVertices4[i].y = size;
			boxVertices4[i].z = -size;
			boxVertices4[i].u = 0;
			boxVertices4[i].v = 0;
			boxVertices4[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices4,4 * sizeof(CraftPSPVertex));

            i = 0;

			boxVertices5[i].x = -size;
			boxVertices5[i].y = size;
			boxVertices5[i].z = -size;
			boxVertices5[i].u = 0;
			boxVertices5[i].v = 0;
			boxVertices5[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices5[i].x = size;
			boxVertices5[i].y = size;
			boxVertices5[i].z = -size;
			boxVertices5[i].u = 1;
			boxVertices5[i].v = 0;
			boxVertices5[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices5[i].x = size;
			boxVertices5[i].y = size;
			boxVertices5[i].z = size;
			boxVertices5[i].u = 1;
			boxVertices5[i].v = 1;
			boxVertices5[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices5[i].x = -size;
			boxVertices5[i].y = size;
			boxVertices5[i].z = size;
			boxVertices5[i].u = 0;
			boxVertices5[i].v = 1;
			boxVertices5[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices5,4 * sizeof(CraftPSPVertex));

            i = 0;

			boxVertices6[i].x = -size;
			boxVertices6[i].y = -size;
			boxVertices6[i].z = size;
			boxVertices6[i].u = 0;
			boxVertices6[i].v = 0;
			boxVertices6[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices6[i].x = size;
			boxVertices6[i].y = -size;
			boxVertices6[i].z = size;
			boxVertices6[i].u = 1;
			boxVertices6[i].v = 0;
			boxVertices6[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices6[i].x = size;
			boxVertices6[i].y = -size;
			boxVertices6[i].z = -size;
			boxVertices6[i].u = 1;
			boxVertices6[i].v = 1;
			boxVertices6[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			boxVertices6[i].x = -size;
			boxVertices6[i].y = -size;
			boxVertices6[i].z = -size;
			boxVertices6[i].u = 0;
			boxVertices6[i].v = 1;
			boxVertices6[i].color = GU_COLOR(alpha,alpha,alpha,alpha);
			i++;

			sceKernelDcacheWritebackInvalidateRange(boxVertices6,4 * sizeof(CraftPSPVertex));
		}

		void StarsBox::Render()
		{
			sceGuEnable(GU_TEXTURE_2D);
            sceGuEnable(GU_BLEND);
			sceGuDisable(GU_DEPTH_TEST);
			sceGuDepthMask(GU_TRUE);
            sceGuBlendFunc(GU_ADD, GU_FIX,GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            sceGuEnable(GU_ALPHA_TEST);

			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices2);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices3);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices4);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices5);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, boxVertices6);

            sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDepthMask(GU_FALSE);
            sceGuEnable(GU_DEPTH_TEST);
			//sceGuDisable(GU_TEXTURE_2D);
			sceGuDisable(GU_BLEND);
			sceGuDisable(GU_TEXTURE_2D);
		}
	}
}

