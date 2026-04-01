#pragma once

#include "../Component.h"
#include "../LevelData.h"
#include "../Texture2D.h"
#include <memory>
#include <vector>

namespace dae { class Texture2D;}

class LevelComponent : public Component
{
public:
	static const int TILE_SIZE = 36; 
	static const int GRID_WIDTH = 17;
	static const int GRID_HEIGHT = 13;

	LevelComponent(const std::string& levelFile);

	void Update(float /*deltaTime*/) override {}
	void Render() override;

private:
	TileType m_grid[GRID_HEIGHT][GRID_WIDTH]{};

	std::shared_ptr<dae::Texture2D> m_emptyTexture;
	std::shared_ptr<dae::Texture2D> m_wallTexture;
	std::shared_ptr<dae::Texture2D> m_solidWallTexture;

	dae::Texture2D* GetTextureForTile(TileType tile) const;
	void InitGrid(const std::string& levelFile);
};