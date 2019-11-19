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

	m_bulletOffset = (float)(rand() % 20 - 10);

	//KINDA WORKS FOR A SHOTGUN ===========================================================================================================================================================
	/*if (m_shotgunShooting > 0) {
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

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BulletBit();
			ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
			m_bullet.push_back(bullet);
		}
		m_shotgunShooting -= 1;
	}*/

	int interval = 0;
	std::vector<int> deleteBullet;
	for (auto entity : m_bullet) {
		float angle = (ECS::GetComponent<Transform>(entity).GetRotationAngleZ()) * (180.f / 3.1514f);
		vec2 bulletVelocity = vec2(ECS::GetComponent<Bullet>(entity).GetSpeed(), ECS::GetComponent<Bullet>(entity).GetSpeed());

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

		ECS::GetComponent<Transform>(entity).SetPosition(ECS::GetComponent<Transform>(entity).GetPositionX() + bulletVelocity.x, ECS::GetComponent<Transform>(entity).GetPositionY() + bulletVelocity.y, 10.f);

		vec2 bulletPos = vec2(ECS::GetComponent<Transform>(entity).GetPositionX(), ECS::GetComponent<Transform>(entity).GetPositionY());
		vec2 playerPos = vec2(ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX(), ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY());

		if (bulletPos.x > playerPos.x + 100.f || bulletPos.x < playerPos.x - 100.f || bulletPos.y > playerPos.y + 100.f || bulletPos.y < playerPos.y - 100.f) {
			deleteBullet.push_back(interval);
		}
		interval++;
	}

	for (int x : deleteBullet) {
		ECS::DestroyEntity(m_bullet[x]);
		m_bullet.erase(m_bullet.begin() + x);
	}
	deleteBullet.clear();

	//WORKS FOR AN AUTOMATIC GUN =============================================================================================================================================================
	/*if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && !m_click && m_rateOfFire > 0.f) {
		m_rateOfFire -= 1.f;
	}
	else {
		m_click = true;
		m_rateOfFire = 10.f;
	}*/
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
	float speed = 1.f;
	//Keyboard button held
	if ((Input::GetKey(Key::W) && (Input::GetKey(Key::A) || Input::GetKey(Key::D))) || (Input::GetKey(Key::S) && (Input::GetKey(Key::A) || Input::GetKey(Key::D))))
	{
		speed = sqrt(2.f) * 0.5f;
	}

	if (Input::GetKey(Key::A))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x - speed);
	}
	if (Input::GetKey(Key::D))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x + speed);
	}
	if (Input::GetKey(Key::W))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y + speed);
	}
	if (Input::GetKey(Key::S))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(position.y - speed);
	}
}

void Game::KeyboardDown()
{
	//Keyboard button down
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
	bool shooting = false;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		//WORKS FOR A REALLY RAPIDFIRE GUN (MINIGUN) ============================================================================================================================================
		//shooting = true;

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

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BulletBit();
			ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
			m_bullet.push_back(bullet);
		}
		//KINDA WORKS FOR A SHOTGUN ==========================================================================================================================================================
		//m_shotgunShooting = 10;
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

	if (!shooting) {
		m_click = false;
	}
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