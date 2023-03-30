#include <SFML/Graphics.hpp>
#include <ctime>

class GameMap
{
private:
	const int Height_Map;
	const int Weidth_Map;
	sf::String* m_TileMap;
public:
	GameMap(int height, const int weidth) :Height_Map(height), Weidth_Map(Weidth_Map)
	{
		m_TileMap = new sf::String[Height_Map];
	}
	sf::String* get_TileMap() { return m_TileMap; }
	const int& getHeight() { return Height_Map; }
	const int& getWeidth() { return Weidth_Map; }
	void generateMap() {}
};
void GameMap::generateMap()
{
	srand(time(NULL));
	int zapov = 0;
	for(int i = 0; i < Height_Map; i ++)
	{
		for(int j = 0; j < Weidth_Map; j++)
		{
			if(i == 0 || (Height_Map - 1))
			{
				m_TileMap[i][j] = '0';
			}
			else if(j == 0 || (Weidth_Map - 1))
			{
				m_TileMap[i][j] = '0';
			}
			else
			{
				m_TileMap[i][j] = ' ';
			}
		}
	}
	for(int spikes = 0; spikes < 21;)
	{
		for (int i = 1; i < (Height_Map - 1); i++)
		{
			short lineSpikes = 0;
			for (int j = 1; j < (Weidth_Map - 1); j++)
			{
				int gnrtdV = 1 + (rand() % Weidth_Map);
				if(lineSpikes != 3)
				{
					 if((m_TileMap[i][gnrtdV - 1] != '0' || 's')
						 && (m_TileMap[i][gnrtdV - 2] != '0' || 's'))
					 {
						 if((m_TileMap[i - 1][gnrtdV] != '0' || 's')
							 && (m_TileMap[i - 2][gnrtdV] != '0' || 's')
							 && (m_TileMap[i - 3][gnrtdV] != '0' || 's'))
						 {
							 m_TileMap[i][gnrtdV] = 's';
							 lineSpikes++;
							 spikes++;
						 }
					 }
				}
			}
		}
	}
}