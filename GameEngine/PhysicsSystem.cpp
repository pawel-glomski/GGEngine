#include "PhysicsSystem.h"


Vec2f crossProduct(const Vec2f& vec, float a)
{
	return Vec2f(a*vec.y, -a * vec.x);
}


Vec2f crossProduct(float a, const Vec2f& vec)
{
	return -crossProduct(vec, a);
}



void PhysicsSystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void PhysicsSystem::update(epp::EntityManager & entityManager, float dt)
{
	fixSinking();
	resolveCollisions();
	applyGravity(dt);
	resolveVelocities(dt);
}

void PhysicsSystem::fixSinking()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		auto& transformC = it.getComponent<TransformComponent>();
		auto& collisionC = it.getComponent<CollisionComponent>();
		auto& physicsC = it.getComponent<PhysicsComponent>();

		for (const auto& collision : collisionC.getCollisions())
			if(physicsC.mass)
				for (size_t i = 0; i < collision.manifold.count; ++i)
					transformC.moveGlobal(-collision.manifold.n * collision.manifold.depths[i] * std::clamp(dotProduct(collision.manifold.n, physicsC.velocity) / physicsC.velocity.length(), 0.f, 1.f) / (float)collision.manifold.count);
	}
}

void PhysicsSystem::resolveCollisions()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		auto& transformC = it.getComponent<TransformComponent>();
		auto& collisionC = it.getComponent<CollisionComponent>();
		auto& physicsC = it.getComponent<PhysicsComponent>();

		if(physicsC.mass)
			for (auto& collision : collisionC.getCollisions())
			{
				auto& otherPhysicsC = *collision.entity.getComponent<PhysicsComponent>();
				auto& othertransformC = *collision.entity.getComponent<TransformComponent>();

				float e = minValue(physicsC.restitution, otherPhysicsC.restitution);

				for (size_t i = 0; i < collision.manifold.count; ++i)
				{
					Vec2f ra = collision.manifold.contact_points[i] - transformC.getPosition();
					Vec2f rb = collision.manifold.contact_points[i] - othertransformC.getPosition();

					Vec2f rVel = otherPhysicsC.velocity - physicsC.velocity + crossProduct(otherPhysicsC.angularVelocity, rb) - crossProduct(physicsC.angularVelocity, ra);
					float rVelMagnitudeAlongN = dotProduct(rVel, collision.manifold.n);
				
					if (rVelMagnitudeAlongN > 0)
						continue;

					float raCrossN = crossProduct(ra, collision.manifold.n);
					float rbCrossN = crossProduct(rb, collision.manifold.n);
					float invMassSum = physicsC.massInv + otherPhysicsC.massInv + raCrossN * raCrossN * physicsC.moiInv + rbCrossN * rbCrossN * otherPhysicsC.moiInv;

					float j = -(1.f + e) * rVelMagnitudeAlongN;
					j /= invMassSum;
					j /= collision.manifold.count;

					Vec2f impulse = j * collision.manifold.n;
					physicsC.applyImpulse(-impulse, ra);
					otherPhysicsC.applyImpulse(impulse, rb);

					rVel = otherPhysicsC.velocity - physicsC.velocity + crossProduct(otherPhysicsC.angularVelocity, rb) - crossProduct(physicsC.angularVelocity, ra);

					// Solve for the tangent vector
					Vec2f tangent = rVel - dotProduct(rVel, collision.manifold.n) * collision.manifold.n;

					tangent.normalize();

					// Solve for magnitude to apply along the friction vector
					float jt = -dotProduct(rVel, tangent);
					jt /= invMassSum;
					jt /= collision.manifold.count;

					if (abs(jt) <= 0.001f)
						continue;

					float mu = (physicsC.staticFriction + otherPhysicsC.staticFriction) * 0.5f;

					// Clamp magnitude of friction and create impulse vector
					Vec2f frictionImpulse;
					float dynamicFriction = 0.f;
					if (abs(jt) < j * mu)
						frictionImpulse = jt * tangent;
					else
					{
						dynamicFriction = (physicsC.dynamicFriction + otherPhysicsC.dynamicFriction) * 0.5f;
						frictionImpulse = -j * tangent * dynamicFriction;
					}

					physicsC.applyImpulse(-frictionImpulse, ra);
					otherPhysicsC.applyImpulse(frictionImpulse, rb);
				}
			}
	}
}

void PhysicsSystem::applyGravity(float dt)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
		if (auto& physicsC = it.getComponent<PhysicsComponent>(); physicsC.mass) // dont apply on static objects
			physicsC.velocity += Vec2f(0.f, 9.81f) * dt;
}

void PhysicsSystem::resolveVelocities(float dt)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		it.getComponent<TransformComponent>().moveGlobal(it.getComponent<PhysicsComponent>().velocity * dt);
		it.getComponent<TransformComponent>().rotate(it.getComponent<PhysicsComponent>().angularVelocity * dt);
	}
}