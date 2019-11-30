#pragma once
#include <array>
#include <cfloat>
#include <stack>
#include "Map.h"
inline bool operator < (const Node& a, const Node& b)
{
	return a.fCost < b.fCost;
}
class PathFinder
{
private:
	static float CalculateH(uint16_t x, uint16_t y, Node target)
	{
		return sqrt(
			((x - target.x) * (x - target.x))
			+ ((y - target.y) * (y - target.y)));
	}
	static std::vector<Node> MakePath(std::array<std::array<Node, SMAX>, SMAX> map, Node dest)
	{
		try
		{
			uint16_t x = dest.x;
			uint16_t y = dest.y;
			std::stack<Node> path;
			std::vector<Node> usablePath;
			while (!(map[x][y].pX == x && map[x][y].pY == y) && map[x][y].x != -1 && map[x][y].y != -1)
			{
				path.push(map[x][y]);
				uint16_t tempX = map[x][y].pX;
				uint16_t tempY = map[x][y].pY;
				x = tempX;
				y = tempY;
			}
			path.push(map[x][y]);
			while (!path.empty()) {
				Node top = path.top();
				path.pop();
				usablePath.emplace_back(top);
			}
			return usablePath;
		}
		catch (const std::exception& e) 
		{
			std::cout << e.what() << std::endl;
		}
	}
public:
	static float MAXDISTANCE() { return sqrt(2 * ((0 - SMAX) * (0 - SMAX))); };
	static int howFar(Node ai, Node target, int max)
	{
		float distance = sqrt(((ai.x - target.x) * (ai.x - target.x)) + ((ai.y - target.y) * (ai.y - target.y)));
		return ((max - 2) * (distance / MAXDISTANCE()) + 2);
	}
	static std::vector<Node> aStar(Map map, Node pFinder, Node target) 
	{
		std::vector<Node> empty;
		bool closedList[SMAX][SMAX];
		std::array<std::array<Node, SMAX>, SMAX> allMap;
		for (uint16_t x = 0; x < SMAX; x++)
		{
			for (uint16_t y = 0; y < SMAX; y++)
			{
				allMap[x][y].fCost = FLT_MAX;
				allMap[x][y].gCost = FLT_MAX;
				allMap[x][y].hCost = FLT_MAX;
				allMap[x][y].pX = -1;
				allMap[x][y].pY = -1;
				allMap[x][y].x = x;
				allMap[x][y].y = y;

				closedList[x][y] = false;
			}
		}
		uint16_t x = pFinder.x;
		uint16_t y = pFinder.y;
		allMap[x][y].fCost = 0.0;
		allMap[x][y].gCost = 0.0;
		allMap[x][y].hCost = 0.0;
		allMap[x][y].pX = x;
		allMap[x][y].pY = y;

		std::vector<Node> openList;
		openList.emplace_back(allMap[x][y]);

		while (!openList.empty() && openList.size() < SMAX * SMAX)
		{
			Node node;
			do
			{
				float temp = FLT_MAX;
				uint16_t j = 0;
				for (uint16_t i = 0; i < openList.size(); i++)
				{
					Node n = openList[i];
					if (n.fCost < temp) 
					{
						temp = n.fCost;
						j = i;
					}
				}
				node = openList[j];
				openList.erase(openList.begin() + j);

			} while (map.Viable(node) == false);
			x = node.x;
			y = node.y;
			closedList[x][y] = true; 

			//std::cout << "If i was at " << x << ", " << y << "...\n";
			for (int16_t newX = -1; newX < 2; newX++)
			{
				for (int16_t newY = -1; newY < 2; newY++)
				{
					//std::cout << "X = " << newX << ' ';
					//std::cout << "Y = " << newY << '\n';
					//std::cout << x + newX << ", " << y + newY << '\n';
					float gNew, hNew, fNew;
					if (x + newX >= 0 && x + newX < SMAX && y + newY >= 0 && y + newY < SMAX)
					{
						if (map.Viable(x + newX, y + newY))
						{
							//std::cout << "maybe... ";
							if (target.x == x + newX && target.y == y + newY)
							{
								//std::cout << "AH HA!\n";
								allMap[x + newX][y + newY].pX = x;
								allMap[x + newX][y + newY].pY = y;
								return MakePath(allMap, target);
							}
							else if (closedList[x + newX][y + newY] == false)
							{
								//std::cout << "here? ";
								if (newX == newY)
								{
									gNew = node.gCost + 1.414;
								}
								else
								{
									gNew = node.gCost + 1.0;
								}
								hNew = CalculateH(x + newX, y + newY, target);
								fNew = gNew + hNew;
								if (allMap[x + newX][y + newY].fCost == FLT_MAX || allMap[x + newX][y + newY].fCost > fNew)
								{
									allMap[x + newX][y + newY].fCost = fNew;
									allMap[x + newX][y + newY].gCost = gNew;
									allMap[x + newX][y + newY].hCost = hNew;
									allMap[x + newX][y + newY].pX = x;
									allMap[x + newX][y + newY].pY = y;
									openList.emplace_back(allMap[x + newX][y + newY]);
								}
								//std::cout << "or... ";
							}
							else
							{
								//std::cout << "no, but ";
							}
						}
						else
						{
							//std::cout << "thats not gonna work... ";
						}
					}
					else
					{
						//std::cout << "that is out of range! ";
					}
					//std::cout << '\n';
				}
			}
			//std::cout << "\nokay!\n\n";
		}
		//std::cout << "No Valid Path\n";
		return empty;
	}
};