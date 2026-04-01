#include "LevelComponent.h"
#include "../ResourceManager.h"
#include "Renderer.h"
#include <fstream>

using W = TileType; // more explanation needed

LevelComponent::LevelComponent(const std::string& levelFile)
{
	m_emptyTexture = dae::ResourceManager::GetInstance().LoadTexture("empty.png");
	m_wallTexture = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
	m_solidWallTexture = dae::ResourceManager::GetInstance().LoadTexture("solidwall.png");
	InitGrid(levelFile);
}

void LevelComponent::Render()
{
	for (int row = 0; row < GRID_HEIGHT; row++)
	{
		for (int col = 0; col < GRID_WIDTH; col++)
		{
			TileType tile = m_grid[row][col];
			
			dae::Texture2D* texture = GetTextureForTile(tile);
			if (texture == nullptr)
			{
				continue;
			}

			float x = static_cast<float>(col * TILE_SIZE);
			float y = static_cast<float>(row * TILE_SIZE);

			dae::Renderer::GetInstance().RenderTexture(*texture, x, y);
		}
	}
}

dae::Texture2D* LevelComponent::GetTextureForTile(TileType tile) const
{
	switch (tile)
	{
	case TileType::Empty:
		return m_emptyTexture.get();
		break;
	case TileType::Wall:
		return m_wallTexture.get();
		break;
	case TileType::SolidWall:
		return m_solidWallTexture.get();
		break;
	default:
		return nullptr;
		break;
	}
}

void LevelComponent::InitGrid(const std::string& levelFile)
{
	//S = Solid, W = Wall, E = Empty

	const auto dataPath = dae::ResourceManager::GetInstance().GetDataPath();
	const auto fullPath = dataPath / levelFile;

	std::ifstream file(fullPath);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open level file:" + levelFile);
	}

	std::string line;
	int row = 0;

	while (std::getline(file, line) && row < GRID_HEIGHT)
	{
		for (int col = 0; col < GRID_WIDTH && col < static_cast<int>(line.size()); ++col)
		{
			switch (line[col])
			{
			case 'S':
				m_grid[row][col] = TileType::SolidWall;
				break;
			case 'W':
				m_grid[row][col] = TileType::Wall;
				break;
			case 'E':
				m_grid[row][col] = TileType::Empty;
				break;
			default:
				m_grid[row][col] = TileType::Empty;
				break;
			}
		}
		++row;
	}

}
