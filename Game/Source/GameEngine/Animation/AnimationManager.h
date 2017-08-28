#pragma once
#include "AnimationClip.h"
#include "Scene.h"

namespace Blz
{
	namespace Animation
	{
		class AnimationManager
		{
		public:
			AnimationManager() = default;
			~AnimationManager() = default;

			void Init(Scene& scene);
			void Update(Scene& scene);

		private:
			AnimClip animation;
		};
	}
}
