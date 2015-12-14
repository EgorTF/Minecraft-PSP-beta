#ifndef DESTROYER_H_
#define DESTROYER_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <Aurora/Math/Frustum.h>
#include <LameCraft/CraftWorld2.h>
#include <Aurora/Math/BoundingBox.h>

namespace Aurora
{
	namespace Graphics
	{
		class Destroyer
		{
		public:
			Destroyer();
			~Destroyer();

			void Update(float stad, CraftWorld* crft, int blockId);
			void Render();

		private:

			TexturesPSPVertex *boxVertices;
			TexturesPSPVertex *boxVertices2;
			TexturesPSPVertex *boxVertices3;
			TexturesPSPVertex *boxVertices4;
			TexturesPSPVertex *boxVertices5;
			TexturesPSPVertex *boxVertices6;

			float size;
		};
	}
}

#endif

