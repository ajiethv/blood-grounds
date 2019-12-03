#pragma once
#define SMAX 50
#include <iostream>
#include <vector>


struct Node
{
	uint16_t x, y, pX, pY;
	float gCost, hCost, fCost;
	Node(uint16_t vx, uint16_t vy)
	{
		x = vx;
		y = vy;
	}
	Node()
	{
		x = 0;
		y = 0;
	}
};
class Map
{
private:
	std::vector<std::vector<uint8_t>> local;
public:
	bool Viable(uint16_t x, uint16_t y)
	{
		try
		{
			if (local[x][y] == 0)
			{
				return true;
			}
			return false;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			return false;
		}
	}
	bool Viable(Node a)
	{

		try
		{
			if (local[a.x][a.y] == 0)
			{
				return true;
			}
			return false;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			return false;
		}
	}
	uint8_t GetAt(uint16_t x, uint16_t y)
	{
		return local[x][y];
	}
	uint8_t GetAt(Node a)
	{
		return local[a.x][a.y];
	}
	Node Target()
	{
		Node target;
		for (uint16_t x = 0; x < local.size(); x++)
		{
			for (uint16_t y = 0; y < local[x].size(); y++)
			{
				if (local[x][y] == 2)
				{
					target.x = x;
					target.y = y;
				}
			}
		}
		return target;
	}
	Node Spawn()
	{
		Node target = Node(0, 0);
		for (uint16_t x = 0; x < local.size(); x++)
		{
			for (uint16_t y = 0; y < local[x].size(); y++)
			{
				if (local[x][y] == 3)
				{
					target.x = x;
					target.y = y;
				}
			}
		}
		SetAt(target, 0);
		return target;
	}
	bool IsTarget(uint16_t x, uint16_t y)
	{
		Node temp = Target();
		return (temp.x == x && temp.y == y);
	}
	bool IsTarget(Node a)
	{
		Node temp = Target();
		return (temp.x == a.x && temp.y == a.y);
	}
	void Set(std::vector<std::vector<uint8_t>> v)
	{
		local.resize(v.size());
		for (uint16_t x = 0; x < v.size(); x++)
		{
			local[x].resize(v[x].size());
			for (uint16_t y = 0; y < local[x].size(); y++)
				local[x][y] = v[x][y];
		}
	}
	void SetAt(uint16_t x, uint16_t y, uint8_t v)
	{
		local[x][y] = v;
	}
	void SetAt(Node a, uint8_t v)
	{
		local[a.x][a.y] = v;
	}
	Map(std::vector<std::vector<uint8_t>> v)
	{
		local.resize(v.size());
		for (uint16_t x = 0; x < v.size(); x++)
		{
			local[x].resize(v[x].size());
			for (uint16_t y = 0; y < local[x].size(); y++)
				local[x][y] = v[y][x];
		}
	}
};