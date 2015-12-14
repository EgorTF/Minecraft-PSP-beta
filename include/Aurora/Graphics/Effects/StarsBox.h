#ifndef STARSBOX_H_
#define STARSBOX_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <Aurora/Math/Frustum.h>

namespace Aurora
{
	namespace Graphics
	{
		class StarsBox
		{
		public:
			StarsBox();
			~StarsBox();

			void Update(float alpha);
			void Render();

		private:

			CraftPSPVertex *boxVertices;
			CraftPSPVertex *boxVertices2;
			CraftPSPVertex *boxVertices3;
			CraftPSPVertex *boxVertices4;
			CraftPSPVertex *boxVertices5;
			CraftPSPVertex *boxVertices6;

			float size;
		};
	}
}

#endif

