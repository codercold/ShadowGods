#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"
#include "../../Components/Animation.h"
#include "AnimationSystems.h"

namespace Blz
{
	namespace Animation 
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetAnimationFrameToDisplay(Comp::SpriteTileSheet fighterSprite, Comp::Animation fighterAnimations)
			{
				uint16 currentFrame = fighterAnimations.GetCurrentAnimation().GetCurrentAnimationFrame();

				fighterSprite.SetUVs(currentFrame);

				return fighterSprite;
			}
		}
	}
}