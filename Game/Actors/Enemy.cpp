#include "Enemy.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor))
	{
		destroy = true;	
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 0.5f, nc::Color::red, 10);
	}
}
