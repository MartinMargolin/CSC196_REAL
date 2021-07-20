#include "Game.h"

#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<nc::Engine>(); // New Engine
	engine->Startup();
	scene = std::make_unique<nc::Scene>(); // New Scene
	scene->engine = engine.get();

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "explosion.wav");

	stateFunction = &Game::UpdateTitle;

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	(this->*stateFunction)(dt);

	/*switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
		shape->Load("shape.txt");

		std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 }, };

		std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 0, 1, 0 });
		std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });

		scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, shape, 300));
		for (size_t i = 0; i < 100; i++)
		{
			scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2 }, shape2, 300));
		}

		state = eState::Game;
	
	}
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}*/

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(nc::Color::cyan);
		graphics.DrawString(300, 300 + static_cast<int>(std::sin(stateTimer * 6.0f) * 10.0f), "DUMBASS ENTERPRISES");
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(300, 400, "Press Space To Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());
	
	scene->Draw(graphics);
	engine->Get<nc::ParticleSystem>()->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		stateFunction = &Game::UpdateLevelStart;
	}
	
}

void Game::UpdateLevelStart(float dt)
{
	std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
	shape->Load("shape.txt");

	std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 }, };

	std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 0, 1, 0 });
	std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });

	scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, shape, 300));
	for (size_t i = 0; i < 100; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2 }, shape2, 300));
	}

}
