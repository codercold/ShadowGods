#include "SDL.h"
#include "EngineFramework/Window.h"
#include "EngineFramework/GLLogging.h"
#include "GL/glew.h"
#include <iostream>
#include <spine/Atlas.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/SkeletonBinary.h>
#include <spine/SkeletonJson.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>

Blz::Window window;

typedef struct Vertex {
	// Position in x/y plane
	float x, y;

	// UV coordinates
	float u, v;

	// Color, each channel in the range from 0-1
	// (Should really be a 32-bit RGBA packed color)
	float r, g, b, a;
} Vertex;


enum class GameState
{
	PLAY,
	EXIT
};

int main(int agrc, char** argv)
{
	window.Initialize();


	spAtlas* atlas = spAtlas_createFromFile("spineboy.atlas", 0);

	RUNTIME_ASSERT(atlas != nullptr, "Atlas not loading properly!");

	spSkeletonBinary* binary = spSkeletonBinary_create(atlas);

	spSkeletonData* skeletonData = spSkeletonBinary_readSkeletonDataFile(binary, "spineboy-ess.skel");

	if (!skeletonData)
	{
		LOG("%s\n", binary->error);
		spSkeletonBinary_dispose(binary);
	};

	spSkeletonBinary_dispose(binary);

	spSkeleton* skeleton = spSkeleton_create(skeletonData);

	spSkeleton_updateWorldTransform(skeleton);

	spSlot* slot = skeleton->drawOrder[0];

	RUNTIME_ASSERT(slot != nullptr, "Slot not loaded properly!");

	spAttachment* attachment = slot->attachment;


	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	while (gamestate != GameState::EXIT)
	{
		unsigned int startTime = SDL_GetTicks();

		//Game Logic Update
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				gamestate = GameState::EXIT;

			default:
				break;
			}
		}

		GLfloat verts[] =
		{
			0.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, -1.0f,
		};

		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		window.ClearBuffers();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.SwapBuffers();
	}

	return 0;
}
