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
