#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <Aurora/Math/Frustum.h>

namespace Aurora
{
	namespace Graphics
	{
		class SkyBox
		{
		public:
			SkyBox();
			~SkyBox();

			void Update(Vector3 color1, Vector3 color2);
			void Render();

		private:

			SimplePSPVertex *skyBoxVertices;
			SimplePSPVertex *skyBoxVertices2;
			SimplePSPVertex *skyBoxVertices3;
			SimplePSPVertex *skyBoxVertices4;
			SimplePSPVertex *skyBoxVertices5;
			SimplePSPVertex *skyBoxVertices6;

			float size;
		};
	}
}

#endif

