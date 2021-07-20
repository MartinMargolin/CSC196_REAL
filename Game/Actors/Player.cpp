#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
#include <vector>
#include <memory>


void Player::Update(float dt)
{
	Actor::Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	if (Core::Input::IsPressed('S')) thrust = -speed;

	transform.position += nc::Vector2::Rotate(nc::Vector2::up, transform.rotation) * thrust * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire

	if (Core::Input::IsPressed(VK_SPACE))
	{
	
		std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
		std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 0, 1, 0 });

		nc::Transform t = transform;
		t.scale = 0.25f;
		scene->AddActor(std::make_unique<Projectile>(t, shape2, 600.0f));


	}

		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 10);
}

