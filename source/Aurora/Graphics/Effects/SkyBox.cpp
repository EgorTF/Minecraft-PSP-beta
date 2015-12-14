#include <Aurora/Graphics/Effects/SkyBox.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)

namespace Aurora
{
	namespace Graphics
	{
		SkyBox::SkyBox()
		{
			skyBoxVertices = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));
			skyBoxVertices2 = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));
			skyBoxVertices3 = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));
			skyBoxVertices4 = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));
			skyBoxVertices5 = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));
			skyBoxVertices6 = (SimplePSPVertex*)memalign(16,4 * sizeof(SimplePSPVertex));

			size = 0.5f;
		}

		SkyBox::~SkyBox()
		{
			free(skyBoxVertices);
			free(skyBoxVertices2);
			free(skyBoxVertices3);
			free(skyBoxVertices4);
			free(skyBoxVertices5);
			free(skyBoxVertices6);
		}

		void SkyBox::Update(Vector3 color1, Vector3 color2)
		{

			int i = 0;

			skyBoxVertices[i].x = -0.5f;
			skyBoxVertices[i].y = -0.3f;
			skyBoxVertices[i].z = -0.5f;
			skyBoxVertices[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices[i].x = -0.5f;
			skyBoxVertices[i].y = 0.5f;
			skyBoxVertices[i].z = -0.5f;
			skyBoxVertices[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices[i].x = -0.5f;
			skyBoxVertices[i].y = 0.5f;
			skyBoxVertices[i].z = 0.5f;
			skyBoxVertices[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices[i].x = -0.5f;
			skyBoxVertices[i].y = -0.3f;
			skyBoxVertices[i].z = 0.5f;
			skyBoxVertices[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices,4 * sizeof(SimplePSPVertex));

            i = 0;

			skyBoxVertices2[i].x = 0.5f;
			skyBoxVertices2[i].y = -0.3f;
			skyBoxVertices2[i].z = 0.5f;
			skyBoxVertices2[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices2[i].x = 0.5f;
			skyBoxVertices2[i].y = 0.5f;
			skyBoxVertices2[i].z = 0.5f;
			skyBoxVertices2[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices2[i].x = 0.5f;
			skyBoxVertices2[i].y = 0.5f;
			skyBoxVertices2[i].z = -0.5f;
			skyBoxVertices2[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices2[i].x = 0.5f;
			skyBoxVertices2[i].y = -0.3f;
			skyBoxVertices2[i].z = -0.5f;
			skyBoxVertices2[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices2,4 * sizeof(SimplePSPVertex));

            i = 0;

			skyBoxVertices3[i].x = -0.5f;
			skyBoxVertices3[i].y = -0.3f;
			skyBoxVertices3[i].z = -0.5f;
			skyBoxVertices3[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices3[i].x = 0.5f;
			skyBoxVertices3[i].y = -0.3f;
			skyBoxVertices3[i].z = -0.5f;
			skyBoxVertices3[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices3[i].x = 0.5f;
			skyBoxVertices3[i].y = 0.5f;
			skyBoxVertices3[i].z = -0.5f;
			skyBoxVertices3[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices3[i].x = -0.5f;
			skyBoxVertices3[i].y = 0.5f;
			skyBoxVertices3[i].z = -0.5f;
			skyBoxVertices3[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices3,4 * sizeof(SimplePSPVertex));

            i = 0;

			skyBoxVertices4[i].x = -0.5f;
			skyBoxVertices4[i].y = 0.5f;
			skyBoxVertices4[i].z = 0.5f;
			skyBoxVertices4[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices4[i].x = 0.5f;
			skyBoxVertices4[i].y = 0.5f;
			skyBoxVertices4[i].z = 0.5f;
			skyBoxVertices4[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices4[i].x = 0.5f;
			skyBoxVertices4[i].y = -0.3f;
			skyBoxVertices4[i].z = 0.5f;
			skyBoxVertices4[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices4[i].x = -0.5f;
			skyBoxVertices4[i].y = -0.3f;
			skyBoxVertices4[i].z = 0.5f;
			skyBoxVertices4[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices4,4 * sizeof(SimplePSPVertex));

            i = 0;

			skyBoxVertices5[i].x = -0.5f;
			skyBoxVertices5[i].y = -0.3f;
			skyBoxVertices5[i].z = 0.5f;
			skyBoxVertices5[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices5[i].x = 0.5f;
			skyBoxVertices5[i].y = -0.3f;
			skyBoxVertices5[i].z = 0.5f;
			skyBoxVertices5[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices5[i].x = 0.5f;
			skyBoxVertices5[i].y = -0.3f;
			skyBoxVertices5[i].z = -0.5f;
			skyBoxVertices5[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			skyBoxVertices5[i].x = -0.5f;
			skyBoxVertices5[i].y = -0.3f;
			skyBoxVertices5[i].z = -0.5f;
			skyBoxVertices5[i].color = GU_COLOR(color1.x,color1.y,color1.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices5,4 * sizeof(SimplePSPVertex));

            i = 0;

			skyBoxVertices6[i].x = -0.5f;
			skyBoxVertices6[i].y = 0.5f;
			skyBoxVertices6[i].z = -0.5f;
			skyBoxVertices6[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices6[i].x = 0.5f;
			skyBoxVertices6[i].y = 0.5f;
			skyBoxVertices6[i].z = -0.5f;
			skyBoxVertices6[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices6[i].x = 0.5f;
			skyBoxVertices6[i].y = 0.5f;
			skyBoxVertices6[i].z = 0.5f;
			skyBoxVertices6[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			skyBoxVertices6[i].x = -0.5f;
			skyBoxVertices6[i].y = 0.5f;
			skyBoxVertices6[i].z = 0.5f;
			skyBoxVertices6[i].color = GU_COLOR(color2.x,color2.y,color2.z,1);// * textureScale;
			i++;

			sceKernelDcacheWritebackInvalidateRange(skyBoxVertices6,4 * sizeof(SimplePSPVertex));
		}

		void SkyBox::Render()
		{
			sceGuEnable(GU_BLEND);

            sceGuDisable(GU_DEPTH_TEST);
			sceGuDepthMask(GU_TRUE);

			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices2);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices3);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices4);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices5);
			sceGumDrawArray(GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, skyBoxVertices6);

            sceGuDepthMask(GU_FALSE);
            sceGuEnable(GU_DEPTH_TEST);

			sceGuDisable(GU_BLEND);
		}
	}
}

