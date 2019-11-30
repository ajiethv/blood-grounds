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
	m_enemyX.push_back((x + 240) / 10);
}

void Enemy::SetEnemyY(float y)
{
	m_enemyY.push_back((y + 250) / 10);
}

void Enemy::SetTargets(std::vector<Node> t)
{
	m_targets = t;
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

bool Enemy::AtTarget(int i)
{
	if (abs(this->m_position.x - m_enemyX[i]) < 5.f && abs(this->m_position.y - m_enemyY[i]) < 5.f) {
		return true;
	}
	return false;
}

void Enemy::RemoveTarget()
{
	m_targets.erase(m_targets.begin());
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
