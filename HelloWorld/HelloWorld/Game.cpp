#include "Game.h"

#include <random>

Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Blood-Grounds";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	m_scenes.push_back(new HelloWorld("New Scene"));
	m_activeScene = m_scenes[0];

	//m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	//std::cout << m_fireRate  << "\n" << m_reloadSpeed << "\n" << m_magazineSize << "\n" << m_currentWave << "\n\n";
	int animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim();

	if (m_magazineSize == 0 && m_reloadSpeed == 0.f) {
		if (animation == 0 || animation == 1 || animation == 2 || animation == 3) {
			m_reloadSpeed = 100.f;
		}
		else if (animation == 4 || animation == 5) {
			m_reloadSpeed = 200.f;
		}
		else {
			m_reloadSpeed = 350.f;
		}
	}

	m_bulletOffset = 0.f;
	if (animation == 0 || animation == 1) {
		m_bulletOffset = (float)(rand() % 11 - 5);
	}
	else if (animation == 2 || animation == 3) {
		m_bulletOffset = (float)(rand() % 11 - 5);
	}

	if (m_shotgunShooting > 0) {
		m_bulletOffset = (float)(rand() % 31 - 15);
		{
			auto bullet = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(bullet);
			ECS::AttachComponent<Transform>(bullet);
			ECS::AttachComponent<Bullet>(bullet);

			std::string fileName = "bullet.png";

			vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

			ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
			ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));
			ECS::GetComponent<Transform>(bullet).SetRotationAngleZ(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetRotationAngleZ() + (m_bulletOffset * PI / 180.f));
			ECS::GetComponent<Bullet>(bullet).SetDamage(10.f);
			ECS::GetComponent<Bullet>(bullet).SetSpeed(10.f);
			ECS::GetComponent<Bullet>(bullet).SetBulletPen(0);

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BulletBit();
			ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
			m_bullet.push_back(bullet);
		}
		m_bulletOffset = (float)(rand() % 31 - 15);
		{
			auto bullet = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(bullet);
			ECS::AttachComponent<Transform>(bullet);
			ECS::AttachComponent<Bullet>(bullet);

			std::string fileName = "bullet.png";

			vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

			ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
			ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));
			ECS::GetComponent<Transform>(bullet).SetRotationAngleZ(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetRotationAngleZ() + (m_bulletOffset * PI / 180.f));
			ECS::GetComponent<Bullet>(bullet).SetDamage(10.f);
			ECS::GetComponent<Bullet>(bullet).SetSpeed(10.f);
			ECS::GetComponent<Bullet>(bullet).SetBulletPen(0);

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BulletBit();
			ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
			m_bullet.push_back(bullet);
		}
		m_shotgunShooting -= 2;
	}

	int interval = 0, interval2 = 0;
	std::vector<int> deleteBullet;
	std::vector<int> deleteEnemy;
	
	for (auto bullet : m_bullet) {
		float angle = (ECS::GetComponent<Transform>(bullet).GetRotationAngleZ()) * (180.f / 3.1514f);
		vec2 bulletVelocity = vec2(ECS::GetComponent<Bullet>(bullet).GetSpeed(), ECS::GetComponent<Bullet>(bullet).GetSpeed());

		if (angle < 90.f) {
			bulletVelocity.x = bulletVelocity.x * cos(angle * (PI / 180.f));
			bulletVelocity.y = bulletVelocity.y * sin(angle * (PI / 180.f));
		}
		else if (angle < 180.f) {
			angle = 180.f - angle;
			bulletVelocity.x = -(bulletVelocity.x * cos(angle * (PI / 180.f)));
			bulletVelocity.y = bulletVelocity.y * sin(angle * (PI / 180.f));
		}
		else if (angle < 270.f) {
			angle -= 180.f;
			bulletVelocity.x = -(bulletVelocity.x * cos(angle * (PI / 180.f)));
			bulletVelocity.y = -(bulletVelocity.y * sin(angle * (PI / 180.f)));
		}
		else if (angle < 360.f) {
			angle = 360.f - angle;
			bulletVelocity.x = bulletVelocity.x * cos(angle * (PI / 180.f));
			bulletVelocity.y = -(bulletVelocity.y * sin(angle * (PI / 180.f)));
		}
		else if (angle == 90.f) {
			bulletVelocity.x = 0.f;
		}
		else if (angle == 180.f) {
			bulletVelocity.y = 0.f;
			bulletVelocity.x = -bulletVelocity.x;
		}
		else if (angle == 270.f) {
			bulletVelocity.y = -bulletVelocity.y;
			bulletVelocity.x = 0.f;
		}
		else {
			bulletVelocity.y = 0.f;
		}

		vec2 oldBulletPos = vec2(ECS::GetComponent<Transform>(bullet).GetPositionX(), ECS::GetComponent<Transform>(bullet).GetPositionY());
		ECS::GetComponent<Transform>(bullet).SetPosition(ECS::GetComponent<Transform>(bullet).GetPositionX() + bulletVelocity.x, ECS::GetComponent<Transform>(bullet).GetPositionY() + bulletVelocity.y, 10.f);
		vec2 bulletPos = vec2(ECS::GetComponent<Transform>(bullet).GetPositionX(), ECS::GetComponent<Transform>(bullet).GetPositionY());

		for (int i = 3; i <= 67; i++) {
			vec2 normal[4] = {
				vec2(-(bulletPos.y - oldBulletPos.y), bulletPos.x - oldBulletPos.x),
				vec2(bulletPos.x - oldBulletPos.x, bulletPos.y - oldBulletPos.y),
				vec2(0.f, 1.f), 
				vec2(1.f, 0.f) 
			};

			bool collide = true;

			for (vec2 n : normal) {
				float shape1Points[2] = {
					bulletPos.Dot(n),
					oldBulletPos.Dot(n)
				};
				
				float shape2Points[4] = {
					vec2(ECS::GetComponent<Transform>(i).GetPosition().x - (ECS::GetComponent<Transform>(i).GetScale().x / 2.f), ECS::GetComponent<Transform>(i).GetPosition().y - (ECS::GetComponent<Transform>(i).GetScale().y / 2.f)).Dot(n),
					vec2(ECS::GetComponent<Transform>(i).GetPosition().x + (ECS::GetComponent<Transform>(i).GetScale().x / 2.f), ECS::GetComponent<Transform>(i).GetPosition().y - (ECS::GetComponent<Transform>(i).GetScale().y / 2.f)).Dot(n),
					vec2(ECS::GetComponent<Transform>(i).GetPosition().x - (ECS::GetComponent<Transform>(i).GetScale().x / 2.f), ECS::GetComponent<Transform>(i).GetPosition().y + (ECS::GetComponent<Transform>(i).GetScale().y / 2.f)).Dot(n),
					vec2(ECS::GetComponent<Transform>(i).GetPosition().x + (ECS::GetComponent<Transform>(i).GetScale().x / 2.f), ECS::GetComponent<Transform>(i).GetPosition().y + (ECS::GetComponent<Transform>(i).GetScale().y / 2.f)).Dot(n)
				};

				float max1 = shape1Points[0], min1 = shape1Points[0], max2 = shape2Points[0], min2 = shape2Points[0];
				if (shape1Points[1] > max1) max1 = shape1Points[1];
				else min1 = shape1Points[1];

				for (int j = 1; j <= 3; j++) {
					if (max2 < shape2Points[j]) max2 = shape2Points[j];
					if (min2 > shape2Points[j]) min2 = shape2Points[j];
				}

				if (!((max1 <= max2 && max1 >= min2) || (min1 <= max2 && min1 >= min2))) {
					collide = false;
					break;
				}
			}
			
			if (bulletPos.x > 255.f || bulletPos.x < -245.f || bulletPos.y > 245.f || bulletPos.y < -255.f) {
				collide = true;
			}

			if (collide) {
				deleteBullet.push_back(interval);
				break;
			}
		}

		for (int enemy : m_enemy) {
			if (ECS::GetComponent<Enemy>(enemy).GetInvulnerability() == 0.f) {
				float enemyAngle = ECS::GetComponent<Transform>(enemy).GetRotationAngleZ() * (180.f / PI);
				if (enemyAngle >= 270.f) {
					enemyAngle -= 270.f;
				}
				else if (enemyAngle >= 180.f) {
					enemyAngle -= 180.f;
				}
				else if (enemyAngle >= 90.f) {
					enemyAngle -= 90.f;
				}
				enemyAngle *= PI / 180.f;

				vec2 enemyCorners[4] = {
					vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() + (abs(sqrt(50) * cos(enemyAngle))), ECS::GetComponent<Transform>(enemy).GetPositionY() + (abs(sqrt(50) * sin(enemyAngle)))),
					vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() + (-(abs(sqrt(50) * cos(enemyAngle)))), ECS::GetComponent<Transform>(enemy).GetPositionY() + (abs(sqrt(50) * sin(enemyAngle)))),
					vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() + (abs(sqrt(50) * cos(enemyAngle))), ECS::GetComponent<Transform>(enemy).GetPositionY() + (-(abs(sqrt(50) * sin(enemyAngle))))),
					vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() + (-(abs(sqrt(50) * cos(enemyAngle)))), ECS::GetComponent<Transform>(enemy).GetPositionY() + (-(abs(sqrt(50) * sin(enemyAngle)))))
				};

				vec2 normal[4] = {
					vec2(-(bulletPos.y - oldBulletPos.y), bulletPos.x - oldBulletPos.x),
					vec2(bulletPos.x - oldBulletPos.x, bulletPos.y - oldBulletPos.y),
					vec2(-(enemyCorners[0].y - enemyCorners[1].y), enemyCorners[0].x - enemyCorners[1].x),
					vec2(-(enemyCorners[0].y - enemyCorners[2].y), enemyCorners[0].x - enemyCorners[2].x)
				};

				bool collide = true;

				for (vec2 n : normal) {
					float shape1Points[2] = {
						bulletPos.Dot(n),
						oldBulletPos.Dot(n)
					};

					float shape2Points[4] = {
						enemyCorners[0].Dot(n),
						enemyCorners[1].Dot(n),
						enemyCorners[2].Dot(n),
						enemyCorners[3].Dot(n)
					};

					float max1 = shape1Points[0], min1 = shape1Points[0], max2 = shape2Points[0], min2 = shape2Points[0];
					if (shape1Points[1] > max1) max1 = shape1Points[1];
					else min1 = shape1Points[1];

					for (int j = 1; j <= 3; j++) {
						if (max2 < shape2Points[j]) max2 = shape2Points[j];
						if (min2 > shape2Points[j]) min2 = shape2Points[j];
					}

					if (!((max1 <= max2 && max1 >= min2) || (min1 <= max2 && min1 >= min2))) {
						collide = false;
						break;
					}
				}

				if (collide) {
					ECS::GetComponent<Enemy>(enemy).SetInvulnerability(2.f);

					ECS::GetComponent<Enemy>(enemy).SetHealth(ECS::GetComponent<Enemy>(enemy).GetHealth() - ECS::GetComponent<Bullet>(bullet).GetDamage());

					if (ECS::GetComponent<Enemy>(enemy).GetHealth() <= 0.f) {
						deleteEnemy.push_back(interval2);
						m_currentZombieNum--;
					}

					if (ECS::GetComponent<Bullet>(bullet).GetBulletPen() > 0) {
						ECS::GetComponent<Bullet>(bullet).SetBulletPen(ECS::GetComponent<Bullet>(bullet).GetBulletPen() - 1);
					}
					else {
						deleteBullet.push_back(interval);
						break;
					}
				}
			}

			if (ECS::GetComponent<Enemy>(enemy).GetInvulnerability() > 0.f) {
				ECS::GetComponent<Enemy>(enemy).SetInvulnerability(ECS::GetComponent<Enemy>(enemy).GetInvulnerability() - 1.f);
			}

			interval2++;
		}

		interval++;
	}

	for (int enemy : m_enemy) {
		vec2 enemyCollisionMax = vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() + (ECS::GetComponent<Transform>(enemy).GetScale().x / 2.f), ECS::GetComponent<Transform>(enemy).GetPositionY() + (ECS::GetComponent<Transform>(enemy).GetScale().y / 2.f));
		vec2 enemyCollisionMin = vec2(ECS::GetComponent<Transform>(enemy).GetPositionX() - (ECS::GetComponent<Transform>(enemy).GetScale().x / 2.f), ECS::GetComponent<Transform>(enemy).GetPositionY() - (ECS::GetComponent<Transform>(enemy).GetScale().y / 2.f));
		vec2 playerPosMax = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX() + (ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().x / 2.f), ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY() + (ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().y / 2.f));
		vec2 playerPosMin = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX() - (ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().x / 2.f), ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY() - (ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().y / 2.f));

		if (playerPosMax.x >= enemyCollisionMin.x && playerPosMin.x <= enemyCollisionMax.x && playerPosMax.y >= enemyCollisionMin.y && playerPosMin.y <= enemyCollisionMax.y) {
			if (m_playerInvulnerability == 0.f) {
				ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).SetHealth(ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).GetHealth() - ECS::GetComponent<Enemy>(enemy).GetDamage());
				m_playerInvulnerability = 200.f;
			}
		}
	}

	for (int x : deleteBullet) {
		interval = 0;
		ECS::DestroyEntity(m_bullet[x]);
		m_bullet.erase(m_bullet.begin() + x);
		for (int y : deleteBullet) {
			deleteBullet[interval] -= 1;
			interval++;
		}
	}
	deleteBullet.clear();

	for (int x : deleteEnemy) {
		interval2 = 0;
		ECS::DestroyEntity(m_enemy[x]);
		m_enemy.erase(m_enemy.begin() + x);
		for (int y : deleteEnemy) {
			deleteEnemy[interval2] -= 1;
			interval2++;
		}
	}
	deleteEnemy.clear();

	if (m_totalZombieNum == 0 && m_currentZombieNum == 0) {
		m_currentWave++;
		m_totalZombieNum = 1;
	}

	if (m_totalZombieNum > 0 && rand() % 100 == 0) {
		int spawner = rand() % 8 + 68;
		vec2 spawnLocation = vec2(ECS::GetComponent<Transform>(spawner).GetPositionX(), ECS::GetComponent<Transform>(spawner).GetPositionY());

		{
			auto enemy = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(enemy);
			ECS::AttachComponent<Transform>(enemy);
			ECS::AttachComponent<Enemy>(enemy);

			std::string fileName = "NO SPRITE";

			vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

			ECS::GetComponent<Sprite>(enemy).LoadSprite(fileName, 10, 10);
			ECS::GetComponent<Transform>(enemy).SetPosition(vec3(spawnLocation.x, spawnLocation.y, 11.f));
			ECS::GetComponent<Enemy>(enemy).SetHealth(10.f);
			ECS::GetComponent<Enemy>(enemy).SetSpeed(1.f);
			ECS::GetComponent<Enemy>(enemy).SetDamage(10.f);

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::EnemyBit();
			ECS::SetUpIdentifier(enemy, bitHolder, "enemy");
			m_enemy.push_back(enemy);
			ECS::GetComponent<Enemy>(enemy).SetEnemyX(ECS::GetComponent<Transform>(enemy).GetPositionX());
			ECS::GetComponent<Enemy>(enemy).SetEnemyY(ECS::GetComponent<Transform>(enemy).GetPositionY());

			vec2 nodePos = ECS::GetComponent<Enemy>(enemy).ToNode(spawnLocation);
			ECS::GetComponent<Enemy>(enemy).SetPosition(Node(nodePos.x, nodePos.y));
			std::cout << "Spawn: " << nodePos.x << " " << nodePos.y << "\n";
		}

		m_totalZombieNum--;
		m_currentZombieNum++;
	}

	for (int enemy : m_enemy) {
		int count = 0;
		if (!(ECS::GetComponent<Enemy>(enemy).AtTarget(count)) && ECS::GetComponent<Enemy>(enemy).GetTargets().size() > 2) {
			vec2 nodePos = ECS::GetComponent<Enemy>(enemy).ToNode(vec2(ECS::GetComponent<Transform>(enemy).GetPositionX(), ECS::GetComponent<Transform>(enemy).GetPositionY()));
			ECS::GetComponent<Enemy>(enemy).SetEnemyX(nodePos.x);
			ECS::GetComponent<Enemy>(enemy).SetEnemyY(nodePos.y);
			std::cout << "Go to:\t\t" << ECS::GetComponent<Enemy>(enemy).GetTargets()[1].x << " " << ECS::GetComponent<Enemy>(enemy).GetTargets()[1].y << "\n";
			std::cout << "I am at:\t" << nodePos.x << " " << nodePos.y << "\n\n";
			if (nodePos.x < ECS::GetComponent<Enemy>(enemy).GetTargets()[1].x) {
				ECS::GetComponent<Transform>(enemy).SetPositionX(ECS::GetComponent<Transform>(enemy).GetPositionX() + ECS::GetComponent<Enemy>(enemy).GetSpeed());
			}
			if (nodePos.x > ECS::GetComponent<Enemy>(enemy).GetTargets()[1].x) {
				ECS::GetComponent<Transform>(enemy).SetPositionX(ECS::GetComponent<Transform>(enemy).GetPositionX() - ECS::GetComponent<Enemy>(enemy).GetSpeed());
			}

			if (nodePos.y < ECS::GetComponent<Enemy>(enemy).GetTargets()[1].y) {
				ECS::GetComponent<Transform>(enemy).SetPositionY(ECS::GetComponent<Transform>(enemy).GetPositionY() - ECS::GetComponent<Enemy>(enemy).GetSpeed());
			}
			if (nodePos.y > ECS::GetComponent<Enemy>(enemy).GetTargets()[1].y) {
				ECS::GetComponent<Transform>(enemy).SetPositionY(ECS::GetComponent<Transform>(enemy).GetPositionY() + ECS::GetComponent<Enemy>(enemy).GetSpeed());
			}
		}
		else {
			if (ECS::GetComponent<Enemy>(enemy).GetTargets().size() > 2) {
				ECS::GetComponent<Enemy>(enemy).SetPosition(Node(ECS::GetComponent<Enemy>(enemy).ToNode(vec2(ECS::GetComponent<Transform>(enemy).GetPositionX(), ECS::GetComponent<Transform>(enemy).GetPositionY())).x, ECS::GetComponent<Enemy>(enemy).ToNode(vec2(ECS::GetComponent<Transform>(enemy).GetPositionX(), ECS::GetComponent<Transform>(enemy).GetPositionY())).y));
				ECS::GetComponent<Enemy>(enemy).RemoveTarget();
			}
			else {
				ECS::GetComponent<Enemy>(enemy).SetTargets(PathFinder::aStar(map, ECS::GetComponent<Enemy>(enemy).GetPosition(), Node(24, 24)));
				ECS::GetComponent<Enemy>(enemy).SetPosition(ECS::GetComponent<Enemy>(enemy).GetTargets()[0]);
			}
		}
		count++;
	}

	std::string fileName = "HealthBar.png";
	if (ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).GetHealth() <= 20.f) {
		fileName = "LowHealthBar.png";
	}
	ECS::GetComponent<Sprite>(76).LoadSprite(fileName, ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).GetHealth() * (float)BackEnd::GetAspectRatio(), 4);
	fileName = "NO SPRITE";
	ECS::GetComponent<Sprite>(77).LoadSprite(fileName, 102 * (float)BackEnd::GetAspectRatio(), 6);

	if (ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() == 2 || ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() == 3) {
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && !m_click && m_automaticSpeed > 0.f) {
			m_automaticSpeed -= 1.f;
		}
		else {
			m_click = true;
			m_automaticSpeed = 10.f;
		}
	}

	if (ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() % 2 == 1 && m_shootAnimation == 0.f) {
		ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() - 1);
	}

	if (m_reloadSpeed != 0.f) {
		m_reloadSpeed -= 1.f;
		if (m_reloadSpeed <= 0.f) {
			m_reloadSpeed = 0.f;
			if (animation == 0 || animation == 1) {
				m_magazineSize = 10;
			}
			else if (animation == 2 || animation == 3) {
				m_magazineSize = 30;
			}
			else if (animation == 4 || animation == 5) {
				m_magazineSize = 2;
			}
			else {
				m_magazineSize = 8;
			}
		}
	}

	if (m_fireRate != 0.f) {
		m_fireRate -= 1.f;
		if (m_fireRate <= 0.f) {
			m_fireRate = 0.f;
		}
	}

	if (m_playerInvulnerability != 0.f) {
		m_playerInvulnerability -= 1.f;
		if (m_playerInvulnerability <= 0.f) {
			m_playerInvulnerability = 0.f;
		}
	}

	if (m_shootAnimation != 0.f) {
		m_shootAnimation -= 1.f;
		if (m_shootAnimation <= 0.f) {
			m_shootAnimation = 0.f;
		}
	}
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::KeyboardHold()
{
	vec3 position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	vec2 playerSize = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().x / 2.f, ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().y / 2.f);
	float speed = 1.f, angle = 0.f;

	//Keyboard button held
	if ((Input::GetKey(Key::W) && (Input::GetKey(Key::A) || Input::GetKey(Key::D))) || (Input::GetKey(Key::S) && (Input::GetKey(Key::A) || Input::GetKey(Key::D))))
	{
		speed = sqrt(2.f) * 0.5f;
	}
	if (Input::GetKey(Key::W) || Input::GetKey(Key::A) || Input::GetKey(Key::S) || Input::GetKey(Key::D)) {
		ECS::GetComponent<AnimationController>(78).SetActiveAnim(1);
	}

	if (Input::GetKey(Key::A))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x - speed);
		position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		for (int i = 3; i <= 67; i++) {
			vec2 collisionPoint1 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x + ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y + ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			vec2 collisionPoint2 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x - ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y - ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			if (position.x - playerSize.x < collisionPoint1.x && position.x + playerSize.x > collisionPoint2.x && position.y - playerSize.y < collisionPoint1.y && position.y + playerSize.y > collisionPoint2.y) {
				ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(collisionPoint1.x + playerSize.x);
				break;
			}
		}
	}
	if (Input::GetKey(Key::D))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x + speed);
		position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		for (int i = 3; i <= 67; i++) {
			vec2 collisionPoint1 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x + ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y + ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			vec2 collisionPoint2 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x - ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y - ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			if (position.x - playerSize.x < collisionPoint1.x && position.x + playerSize.x > collisionPoint2.x&& position.y - playerSize.y < collisionPoint1.y && position.y + playerSize.y > collisionPoint2.y) {
				ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(collisionPoint2.x - playerSize.x);
				break;
			}
		}
	}
	if (Input::GetKey(Key::W))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y + speed);
		position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
		angle = 90.f;

		for (int i = 3; i <= 67; i++) {
			vec2 collisionPoint1 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x + ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y + ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			vec2 collisionPoint2 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x - ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y - ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			if (position.x - playerSize.x < collisionPoint1.x && position.x + playerSize.x > collisionPoint2.x&& position.y - playerSize.y < collisionPoint1.y && position.y + playerSize.y > collisionPoint2.y) {
				ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(collisionPoint2.y - playerSize.y);
				break;
			}
		}
	}
	if (Input::GetKey(Key::S))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y - speed);
		position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
		angle = 270.f;

		for (int i = 3; i <= 67; i++) {
			vec2 collisionPoint1 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x + ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y + ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			vec2 collisionPoint2 = vec2(ECS::GetComponent<Transform>(i).GetPosition().x - ECS::GetComponent<Transform>(i).GetScale().x / 2.f, ECS::GetComponent<Transform>(i).GetPosition().y - ECS::GetComponent<Transform>(i).GetScale().y / 2.f);
			if (position.x - playerSize.x < collisionPoint1.x && position.x + playerSize.x > collisionPoint2.x&& position.y - playerSize.y < collisionPoint1.y && position.y + playerSize.y > collisionPoint2.y) {
				ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(collisionPoint1.y + playerSize.y);
				break;
			}
		}
	}

	if (Input::GetKey(Key::A)) {
		angle = 180.f;
		if (Input::GetKey(Key::W)) {
			angle = 135.f;
		}
		else if (Input::GetKey(Key::S)) {
			angle = 225.f;
		}
	}
	else if (Input::GetKey(Key::D)) {
		angle = 0.f;
		if (Input::GetKey(Key::W)) {
			angle = 45.f;
		}
		else if (Input::GetKey(Key::S)) {
			angle = 315.f;
		}
	}

	position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	ECS::GetComponent<Transform>(78).SetPosition(position);
	ECS::GetComponent<Transform>(78).SetRotationAngleZ(angle * (PI / 180.f));

	ECS::GetComponent<Transform>(76).SetPosition(vec3(position.x, position.y - 90, 100.f));
	ECS::GetComponent<Transform>(77).SetPosition(vec3(position.x, position.y - 90, 99.f));

	for (int weapon : m_weaponDrop) {
		if (m_secondaryWeapon / 2 == ECS::GetComponent<AnimationController>(weapon).GetActiveAnim()) {
			vec2 weaponPos = vec2(ECS::GetComponent<Transform>(weapon).GetPositionX(), ECS::GetComponent<Transform>(weapon).GetPositionY());
			vec2 weaposSize = vec2(ECS::GetComponent<Transform>(weapon).GetScale().x / 2.f, ECS::GetComponent<Transform>(weapon).GetScale().y / 2.f);
			if (position.x + playerSize.x >= weaponPos.x - weaponPos.x && position.x - playerSize.x <= weaponPos.x + weaponPos.x && position.y + playerSize.y >= weaponPos.y - weaponPos.y && position.y - playerSize.y <= weaponPos.y + weaponPos.y) {
				m_secondaryAmmo += 10;
				m_weaponAmmo[m_secondaryWeapon / 2] += 10;
			}
		}
	}
}

void Game::KeyboardDown()
{
	//Keyboard button down
	int animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim();
	if (Input::GetKeyDown(Key::R)) {
		if (m_reloadSpeed == 0.f) {
			if (animation == 0 || animation == 1) {
				if (m_magazineSize < 10) {
					m_reloadSpeed = 100.f;
				}
			}
			else if (animation == 0 || animation == 1) {
				if (m_magazineSize < 30) {
					m_reloadSpeed = 100.f;
				}
			}
			else if (animation == 0 || animation == 1) {
				if (m_magazineSize < 2) {
					m_reloadSpeed = 200.f;
				}
			}
			else {
				if (m_magazineSize < 8) {
					m_reloadSpeed = 350.f;
				}
			}
		}
	}

	if (Input::GetKeyDown(Key::Space)) {
		if (m_secondaryWeapon != 0) {
			m_reloadSpeed = 0.f;

			if (ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() == 0 || ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() == 1) {
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(m_secondaryWeapon * 2);
				m_primaryAmmo = m_magazineSize;
				m_magazineSize = m_secondaryAmmo;
			}
			else {
				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(0);
				m_secondaryAmmo = m_magazineSize;
				m_magazineSize = m_primaryAmmo;
			}
		}
	}

	if (Input::GetKeyDown(Key::E)) {
		for (int weapon : m_weaponDrop) {
			if (m_secondaryWeapon / 2 != ECS::GetComponent<AnimationController>(weapon).GetActiveAnim()) {
				vec2 playerPos = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX(), ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY());
				vec2 playerSize = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().x / 2.f, ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetScale().y / 2.f);
				vec2 weaponPos = vec2(ECS::GetComponent<Transform>(weapon).GetPositionX(), ECS::GetComponent<Transform>(weapon).GetPositionY());
				vec2 weaposSize = vec2(ECS::GetComponent<Transform>(weapon).GetScale().x / 2.f, ECS::GetComponent<Transform>(weapon).GetScale().y / 2.f);
				if (playerPos.x + playerSize.x >= weaponPos.x - weaponPos.x && playerPos.x - playerSize.x <= weaponPos.x + weaponPos.x && playerPos.y + playerSize.y >= weaponPos.y - weaponPos.y && playerPos.y - playerSize.y <= weaponPos.y + weaponPos.y) {
					m_secondaryWeapon = ECS::GetComponent<AnimationController>(weapon).GetActiveAnim() * 2;
					m_weaponAmmo[ECS::GetComponent<AnimationController>(weapon).GetActiveAnim()] += 10;
					m_secondaryAmmo = 0;
				}
			}
		}
	}
}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}


	if (!(Input::GetKey(Key::W) || Input::GetKey(Key::A) || Input::GetKey(Key::S) || Input::GetKey(Key::D))) {
		ECS::GetComponent<AnimationController>(78).SetActiveAnim(0);
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	vec2 mousePos = vec2((BackEnd::GetWindowWidth() / 2.f) - evnt.x, (BackEnd::GetWindowHeight() / 2.f) - evnt.y);
	float angle = 0.f;

	if (mousePos.x < 0.f && mousePos.y > 0.f) {
		angle = abs((atan(float(mousePos.y) / float(mousePos.x))) * (180.f / PI));
	}
	else if (mousePos.x > 0.f && mousePos.y > 0.f) {
		angle = (atan(float(mousePos.x) / float(mousePos.y))) * (180.f / PI) + 90.f;
	}
	else if (mousePos.x > 0.f && mousePos.y < 0.f) {
		angle = abs((atan(float(mousePos.y) / float(mousePos.x))) * (180.f / PI)) + 180.f;
	}
	else if (mousePos.x < 0.f && mousePos.y < 0.f) {
		angle = (atan(float(mousePos.x) / float(mousePos.y))) * (180.f / PI) + 270.f;
	}
	else if (mousePos.y == 0.f) {
		if (mousePos.x > 0.f) {
			angle = 180.f;
		}
		else {
			angle = 0.f;
		}

	}
	else if (mousePos.x == 0.f) {
		if (mousePos.y > 0.f) {
			angle = 90.f;
		}
		else {
			angle = 270.f;
		}

	}

	ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetRotationAngleZ(angle * (PI / 180.f));

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (m_reloadSpeed == 0.f && m_fireRate == 0.f) {
		if (m_weaponAmmo[ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() / 2] != 0) {
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				int animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim();
				if (animation != 4 && animation != 5) {
					{
						auto bullet = ECS::CreateEntity();

						ECS::AttachComponent<Sprite>(bullet);
						ECS::AttachComponent<Transform>(bullet);
						ECS::AttachComponent<Bullet>(bullet);

						std::string fileName = "bullet.png";

						vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

						ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
						ECS::GetComponent<Transform>(bullet).SetRotationAngleZ(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetRotationAngleZ() + (m_bulletOffset * PI / 180.f));

						//float bulletRotation = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetRotationAngleZ() * (180.f / PI);
						vec2 bulletPos = vec2(playerPos.x, playerPos.y);
						/*float offset = (5.f / 3.f) * 1.9f;

						if (bulletRotation >= 270) {
							bulletPos = vec2();
						}
						else if (bulletRotation >= 180) {
							bulletPos = vec2();
						}
						else if (bulletRotation >= 90) {
							bulletPos = vec2();
						}
						else {
							bulletPos = vec2();
						}*/

						ECS::GetComponent<Transform>(bullet).SetPosition(vec3(bulletPos.x, bulletPos.y, 10.f));
						ECS::GetComponent<Bullet>(bullet).SetDamage(10.f);
						ECS::GetComponent<Bullet>(bullet).SetSpeed(10.f);
						if (animation == 6 || animation == 7) {
							ECS::GetComponent<Bullet>(bullet).SetBulletPen(2);
						}
						else {
							ECS::GetComponent<Bullet>(bullet).SetBulletPen(0);
						}

						unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BulletBit();
						ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
						m_bullet.push_back(bullet);
					}
				}
				else {
					m_shotgunShooting = 10;
				}

				ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).SetActiveAnim(ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() + 1);
				m_shootAnimation = 5.f;
				m_magazineSize -= 1;
				if (ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() / 2 != 0) {
					m_weaponAmmo[ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer()).GetActiveAnim() / 2] -= 1;
				}
				if (animation == 0 || animation == 1) {
					m_fireRate = 20.f;
				}
				else if (animation == 2 || animation == 3) {
					m_fireRate = 10.f;
				}
				else if (animation == 4 || animation == 5) {
					m_fireRate = 100.f;
				}
				else {
					m_fireRate = 150.f;
				}
			}
		}
	}

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//set the camera to focus on the main player
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));

	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}

void Game::GamepadInput()
{
	XInputController* tempCon;

	for (int i = 0; i < 3; i++) {
		if (XInputManager::ControllerConnected(i)) {
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.0f);
			tempCon->SetTriggerDeadZone(0.0f);

			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController* con)
{
	if (con->IsButtonStroked(Buttons::A)) {
		//printf("A Stroked\n");
	}
}

void Game::GamepadUp(XInputController* con)
{
	if (con->IsButtonReleased(Buttons::RB)) {
		//printf("RB Released\n");
	}
}

void Game::GamepadDown(XInputController* con)
{
	if (con->IsButtonPressed(Buttons::THUMB_LEFT)) {
		//printf("Left Thumbstick Clicked In.\n");
	}
}

void Game::GamepadStick(XInputController* con)
{
	Stick sticks[2];
	con->GetSticks(sticks);

	if (sticks[0].x < -0.1f) {
		//printf("Left Pointing\n");
	}
	if (sticks[0].x > 0.1f) {
		//printf("Right Pointing\n");
	}

	if (sticks[0].y < -0.1f) {
		//printf("Down Pointing\n");
	}
	if (sticks[0].y > 0.1f) {
		//printf("Up Pointing\n");
	}
}

void Game::GamepadTrigger(XInputController* con)
{
	Triggers triggers;
	con->GetTriggers(triggers);

	if (triggers.RT > 0.0f) {
		
	}
}