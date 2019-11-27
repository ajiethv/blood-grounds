#pragma once

#include "JSON.h"

class Enemy {
public:
	//empty constructor
	Enemy();

	//setters
	void SetHealth(float h);
	void SetDamage(float d);
	void SetSpeed(float s);
	void SetInvulnerability(float i);

	//getters
	float GetHealth() const;
	float GetDamage() const;
	float GetSpeed() const;
	float GetInvulnerability() const;

private:
	//variables
	float m_health = 0.f;
	float m_damage = 0.f;
	float m_speed = 0.f;
	float m_invulnerability = 0.f;
};

//Sends enemy TO json file
inline void to_json(nlohmann::json& j, const Enemy& enemy)
{
	//Save health
	j["EnemyHealth"] = enemy.GetHealth();
	//Save damage
	j["EnemyDamage"] = enemy.GetDamage();
	//Save speed
	j["EnemySpeed"] = enemy.GetSpeed();
	//Save Invulnerability
	j["EnemyInvulnerability"] = enemy.GetInvulnerability();
}

//Reads enemy in FROM json file
inline void from_json(const nlohmann::json& j, Enemy& enemy)
{
	//Set Health
	enemy.SetHealth(j["EnemyHealth"]);
	//Set Damage
	enemy.SetDamage(j["EnemyDamage"]);
	//Set Speed
	enemy.SetSpeed(j["EnemySpeed"]);
	//Set Invulnerability
	enemy.SetInvulnerability(j["EnemyInvulnerability"]);
}