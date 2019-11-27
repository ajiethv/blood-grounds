#include "Barrier.h"

Barrier::Barrier()
{
}

void Barrier::SetHealth(float h)
{
	m_health = h;
}

void Barrier::SetDamage(float d)
{
	m_damage = d;
}

float Barrier::GetHealth() const
{
	return m_health;
}

float Barrier::GetDamage() const
{
	return m_damage;
}
