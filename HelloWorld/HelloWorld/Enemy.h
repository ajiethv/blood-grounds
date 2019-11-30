#pragma once

#include "JSON.h"
#include "PathFinder.h"
#include "Vector.h"
#include <math.h>

class Enemy {
public:
	//empty constructor
	Enemy();

	//setters
	void SetHealth(float h);
	void SetDamage(float d);
	void SetSpeed(float s);
	void SetInvulnerability(float i);
	void SetEnemyX(float x);
	void SetEnemyY(float y);
	void SetTargets(std::vector<Node> t);
	void SetPosition(Node p);

	//getters
	float GetHealth() const;
	float GetDamage() const;
	float GetSpeed() const;
	float GetInvulnerability() const;
	Node GetPosition();
	std::vector<Node> GetTargets();

	//Ai stuff
	bool AtTarget(int i);
	void RemoveTarget();
	vec2 ToNode(vec2 pos);
	vec2 FromNode(vec2 pos);

private:
	//variables
	float m_health = 0.f;
	float m_damage = 0.f;
	float m_speed = 0.f;
	float m_invulnerability = 0.f;

	Node m_position;
	std::vector<Node> m_targets;
	std::vector<float> m_enemyX;
	std::vector<float> m_enemyY;
	void NewTarget(Map map, Node pos, Node goTo);
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