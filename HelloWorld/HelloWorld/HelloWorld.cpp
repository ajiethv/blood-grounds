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

	//set up the map
	{
		auto background = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(background);
		ECS::AttachComponent<Transform>(background);

		std::string fileName = "mapfinal.png";

		ECS::GetComponent<Sprite>(background).LoadSprite(fileName, 500, 500);
		ECS::GetComponent<Transform>(background).SetPosition(vec3(5.f, -5.f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(background, bitHolder, "Background");
	}

	//set up collision boxes
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 30, 500);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(240.f, -5.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 30, 500);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-230.f, -5.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 500, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(5.f, 230.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 500, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(5.f, -240.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 40, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-35.f, 100.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 40, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-35.f, 140.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-55.f, 150.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-65.f, 160.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-75.f, 170.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 100, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-125.f, 180.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-175.f, 170.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 100);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-180.f, 115.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 30, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-160.f, 70.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 60, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-85.f, 70.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-55.f, 80.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-50.f, 90.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 30, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(30.f, 140.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 40);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(40.f, 165.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(30.f, 185.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(20.f, 200.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 200, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(125.f, 210.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 60);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(220.f, 175.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(210.f, 145.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(200.f, 140.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 30, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(30.f, 100.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(40.f, 85.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(50.f, 75.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(65.f, 70.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(75.f, 60.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(85.f, 50.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(95.f, 40.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(105.f, 30.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(110.f, 20.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(185.f, 30.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(170.f, 35.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 190);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(190.f, -70.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(180.f, -160.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 60);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(140.f, -135.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(130.f, -105.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(120.f, -95.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(110.f, -85.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(100.f, -75.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 40);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(90.f, -55.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(105.f, -40.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(110.f, -25.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-60.f, -35.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 50);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-50.f, -60.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-40.f, -90.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-30.f, -110.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 60, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(5.f, -120.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(35.f, -130.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(45.f, -140.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(55.f, -150.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(65.f, -160.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 60);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(70.f, -195.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 200, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-35.f, -220.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-130.f, -175.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-140.f, -165.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-150.f, -155.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-160.f, -145.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-170.f, -135.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 100);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-180.f, -85.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 10, 20);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-170.f, -35.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 70, 10);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(-130.f, -30.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}

	{
		auto collision = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(collision);
		ECS::AttachComponent<Transform>(collision);

		std::string fileName = "NoSprite";

		ECS::GetComponent<Sprite>(collision).LoadSprite(fileName, 60, 30);
		ECS::GetComponent<Transform>(collision).SetPosition(vec3(165.f, 90.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(collision, bitHolder, "Collision Box");
	}
	
	//set the camera to focus on the main player
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}