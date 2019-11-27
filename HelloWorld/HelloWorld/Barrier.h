#pragma once

#include "JSON.h"

class Barrier {
public:
	//empty constructor
	Barrier();

	//setters
	void SetHealth(float h);
	void SetDamage(float d);

	//getters
	float GetHealth() const;
	float GetDamage() const;

private:
	//variables
	float m_health = 0.f;
	float m_damage = 0.f;
};

//Sends barrier TO json file
inline void to_json(nlohmann::json& j, const Barrier& barrier)
{
	//Save health
	j["BulletHealth"] = barrier.GetHealth();
	//Save damage
	j["BulletDamage"] = barrier.GetDamage();
}

//Reads barrier in FROM json file
inline void from_json(const nlohmann::json& j, Barrier& barrier)
{
	//Set health
	barrier.SetHealth(j["BulletHealth"]);
	//Set Damage
	barrier.SetDamage(j["BulletDamage"]);
}