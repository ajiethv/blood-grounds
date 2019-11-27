#pragma once

#include "JSON.h"

class Bullet {
public:
	//empty constructor
	Bullet();

	//setters
	void SetDamage(float d);
	void SetSpeed(float s);
	void SetBulletPen(int p);

	//getters
	float GetDamage() const;
	float GetSpeed() const;
	int GetBulletPen() const;

private:
	//variables
	float m_damage = 0.f;
	float m_speed = 0.f;
	int m_bulletPen = 0;
};

//Sends bullet TO json file
inline void to_json(nlohmann::json& j, const Bullet& bullet)
{
	//Save damage
	j["BulletDamage"] = bullet.GetDamage();
	//Save speed
	j["BulletSpeed"] = bullet.GetSpeed();
	//Save bullet penetration
	j["BulletPenetration"] = bullet.GetBulletPen();
}

//Reads bullet in FROM json file
inline void from_json(const nlohmann::json& j, Bullet& bullet)
{
	//Set Damage
	bullet.SetDamage(j["BulletDamage"]);
	//Set Speed
	bullet.SetSpeed(j["BulletSpeed"]);
	//Set bullet penetration
	bullet.SetBulletPen(j["BulletPenetration"]);
}