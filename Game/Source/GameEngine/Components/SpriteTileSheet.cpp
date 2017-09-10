#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include "Graphics\Texture.h"
#include "SpriteTileSheet.h"

namespace Comp
{
	void SpriteTileSheet::SetScreenTargetLocationAndTileDimensions(sfloat screenPositionX, sfloat screenPositionY, glm::ivec2 spriteSheetTileDimensions)
	{
		tileDimensions = spriteSheetTileDimensions;

		sfloat halfWidth = this->width / 2;

		//Setting sprite origin at bottom middle of image by subtracting half width 
		this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner
		this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY + height, 0.0f });//Top left corner
		this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY, 0.0f });//Bottom right corner
		this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner

		glm::vec4 uvs;

		uint16 xTile = index % tileDimensions.x;
		uint16 yTile = index / tileDimensions.x;

		uvs.x = xTile / static_cast<sfloat>(tileDimensions.x);
		uvs.y = yTile / static_cast<sfloat>(tileDimensions.y);
		uvs.w = 1.0f / tileDimensions.x;
		uvs.z = 1.0f / tileDimensions.y;

		this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
		this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
		this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
		this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	}

	void SpriteTileSheet::SetWidthAndHeight(sfloat width, sfloat height)
	{
		this->width = width;
		this->height = height;
	}

	void SpriteTileSheet::SetTexture(Blz::Graphics::Texture texture)
	{
		this->textureID = texture.ID();
	}

	GLuint const SpriteTileSheet::GetTextureID() const
	{
		return textureID;
	}

	Blz::Array<Vector3D, 6> const SpriteTileSheet::GetVertexData() const
	{
		return vertexData;
	}

	void SpriteTileSheet::SetUVs(const uint16 displayTile)
	{
		glm::vec4 uvs;

		this->index = displayTile;

		uint16 tileXCoordinate = displayTile% tileDimensions.x;
		uint16 tileYCoordinate = displayTile/ tileDimensions.x;

		uvs.x = tileXCoordinate / static_cast<sfloat>(tileDimensions.x);
		uvs.y = tileYCoordinate / static_cast<sfloat>(tileDimensions.y);
		uvs.w = 1.0f / tileDimensions.x;
		uvs.z = 1.0f / tileDimensions.y;

		this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
		this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
		this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
		this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	}

	uint16 const SpriteTileSheet::CheckIndex() const
	{
		return this->index;
	}
}