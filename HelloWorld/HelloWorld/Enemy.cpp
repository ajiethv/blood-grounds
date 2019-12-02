#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::SetHealth(float h)
{
	m_health = h;
}

void Enemy::SetDamage(float d)
{
	m_damage = d;
}

void Enemy::SetSpeed(float s)
{
	m_speed = s;
}

void Enemy::SetInvulnerability(float i)
{
	m_invulnerability = i;
}

void Enemy::SetEnemyX(float x)
{
	m_enemyX = (x + 240) / 10;
}

void Enemy::SetEnemyY(float y)
{
	m_enemyY = (y + 250) / 10;
}

void Enemy::SetTargets(std::vector<Node> t)
{
	m_targets = t;
}

void Enemy::DeleteTargets()
{
	m_targets.clear();
}

void Enemy::SetNewTarget(Node t)
{
	m_targets.push_back(t);
}

void Enemy::SetPosition(Node p)
{
	m_position = p;
}

float Enemy::GetHealth() const
{
	return m_health;
}

float Enemy::GetDamage() const
{
	return m_damage;
}

float Enemy::GetSpeed() const
{
	return m_speed;
}

float Enemy::GetInvulnerability() const
{
	return m_invulnerability;
}

Node Enemy::GetPosition()
{
	return m_position;
}

std::vector<Node> Enemy::GetTargets()
{
	return m_targets;
}

bool Enemy::AtTarget()
{
	if (m_targets.size() >= 2) {
		if (abs(this->m_targets[1].x - m_enemyX) <= 1.f && abs(this->m_targets[1].y - m_enemyY) <= 1.f) {
			return true;
		}
	}
	return false;
}

void Enemy::RemoveTarget()
{
	if (m_targets.size() > 0) {
		m_targets.erase(m_targets.begin());
	}
}

vec2 Enemy::ToNode(vec2 pos)
{
	pos.x -= 10;
	pos.y += 10;
	pos.y = -pos.y;

	pos.x = (pos.x / 10) + 25;
	pos.y = (pos.y / 10) + 25;

	return vec2(pos);
}

vec2 Enemy::FromNode(vec2 pos)
{
	pos.x = (pos.x - 25) * 10;
	pos.y = (pos.y - 25) * 10;

	pos.y = -pos.y;
	pos.y -= 10;
	pos.x += 10;

	return vec2(pos);
}

Node Enemy::playerNode(vec2 pos)
{
	pos.x -= 10;
	pos.y += 10;
	pos.y = -pos.y;

	pos.x = (pos.x / 10) + 25;
	pos.y = (pos.y / 10) + 25;

	return Node(pos.x, pos.y);
}

void Enemy::NewTarget(Map map, Node pos, Node goTo)
{
	std::vector<Node> p = PathFinder::aStar(map, pos, goTo);
	int howMany = PathFinder::howFar(pos, goTo, 25);
	m_targets.clear();
	for (int j = 1; j < howMany && j < p.size(); j++)
	{
		m_targets.push_back(p[j]);
	}
}
