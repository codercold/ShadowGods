#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "ShaderProgram.h"
#include "../Vector3D.h"
#include "RenderSystem.h"
#include "../Fighter.h"

namespace Blz
{
	namespace Graphics
	{
		namespace RenderSystem
		{
			void Init(Fighter& fighter)
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.sprite.vertexData.size()), &fighter.sprite.vertexData.front(), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void Update(Fighter& fighter, ShaderProgram& shader)
			{
				glm::mat4 orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(1024), 0.0f, static_cast<sfloat>(768));
				GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

				GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
				glUniform1i(uniformLocation, 0);

				glm::vec3 newFighterPosition;
				static GLuint vboID = 0;

				//TODO: Don't tie rendering update function to specific number of fighters
				++vboID;
				if (vboID > 2)
				{
					vboID = 1;
				};

				newFighterPosition = fighter.localPosition;
				glm::mat4 transformationMatrix = glm::translate(orthoProjection, newFighterPosition);
				glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

				glBindTexture(GL_TEXTURE_2D, fighter.sprite.texture.id);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}