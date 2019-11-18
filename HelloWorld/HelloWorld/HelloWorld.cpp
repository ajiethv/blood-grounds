#include "HelloWorld.h"
#include "Game.h"

HelloWorld::HelloWorld(std::string name)
	: Scene(name)
{
}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	//set up window
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = 1.f;

	//set up camera component
	{
		//create entity
		auto camera = ECS::CreateEntity();
		EntityIdentifier::MainCamera(camera);

		//attach camera components
		ECS::AttachComponent<Camera>(camera);
		ECS::AttachComponent<HorizontalScroll>(camera);
		ECS::AttachComponent<VerticalScroll>(camera);

		vec4 temp = ECS::GetComponent<Camera>(camera).GetOrthoSize();

		ECS::GetComponent<Camera>(camera).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(camera).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		ECS::GetComponent<HorizontalScroll>(camera).SetCam(&ECS::GetComponent<Camera>(camera));
		ECS::GetComponent<HorizontalScroll>(camera).SetOffset(0.f);
		ECS::GetComponent<VerticalScroll>(camera).SetCam(&ECS::GetComponent<Camera>(camera));
		ECS::GetComponent<VerticalScroll>(camera).SetOffset(0.f);

		//set camera
		unsigned int bitHolder = EntityIdentifier::VertiScrollCameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(camera, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(camera, true);
	}

	//set main player
	{
		//auto animations = File::LoadJSON("Animation Name.json");

		auto player = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(player);

		ECS::AttachComponent<Sprite>(player);
		ECS::AttachComponent<Transform>(player);
		//ECS::AttachComponent<AnimationController>(player);

		std::string fileName = "download.png";
		//auto& animController = ECS::GetComponent<AnimationController>(player);
		//animController.InitUVs(fileName);

		//animController.AddAnimation(animations["Specific Animation Name"]);

		//animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(player).LoadSprite(fileName, 10, 10/*, true, &animController*/);
		ECS::GetComponent<Transform>(player).SetPosition(vec3(0.f, 0.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()/* | EntityIdentifier::AnimationBit()*/;
		ECS::SetUpIdentifier(player, bitHolder, "Main Character");
		ECS::SetIsMainPlayer(player, true);
	}

	//set bullets
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}
	{
		auto bullet = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(bullet);
		ECS::AttachComponent<Transform>(bullet);

		std::string fileName = "bullet.png";

		vec3 playerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		ECS::GetComponent<Sprite>(bullet).LoadSprite(fileName, 1, 1);
		ECS::GetComponent<Transform>(bullet).SetPosition(vec3(playerPos.x, playerPos.y, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(bullet, bitHolder, "bullet");
	}

	//set the camera to focus on the main player
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}