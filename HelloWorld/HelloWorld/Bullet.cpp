#include "Bullet.h"

Bullet::Bullet()
{
}

void Bullet::SetDamage(float d)
{
	m_damage = d;
}

void Bullet::SetSpeed(float s)
{
	m_speed = s;
}

void Bullet::SetBulletPen(int p)
{
	m_bulletPen = p;
}

float Bullet::GetDamage() const
{
	return m_damage;
}

float Bullet::GetSpeed() const
{
	return m_speed;
}

int Bullet::GetBulletPen() const
{
	return m_bulletPen;
}
