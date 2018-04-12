#include "MotionSystem.h"


void MotionSystem::update(float_t dt, const UsedMDepPack_t & dependencies, ObjectModule & objectModule)
{
	for (auto & packNode : objectsCPacks->getStdContainer())
	{
		auto & cPack = packNode.second;
		auto & controllerC = cPack.get<CRef_t<ControllerComponent>>();
		auto & skeletonC = cPack.get<CRef_t<SkeletonComponent>>();

		TranslationData attackAccelerations;

		if (controllerC.keysStates[(uint8_t)ControllerAction::FirstAbility] == KeyState::Pressed)
		{
			skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<PhysicsComponent>>()->resetVelocitites();

			Transform startingTransform;
			startingTransform.position = Vec2f(-0.2f, - 0.5f);
			startingTransform.rotation = -PI_F / 1.5f;
			skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<TransformComponent>>()->setGlobalTransform(startingTransform);
		}

		static float_t lastRotation = 0.f;


		if (controllerC.keysStates[(uint8_t)ControllerAction::PrimaryAttack] != KeyState::Released)
		{
			attackAccelerations.local = Vec2f(0, sign(controllerC.joystickRotation - lastRotation) * 17.f);
			attackAccelerations.angular = sign(controllerC.joystickRotation - lastRotation) * 10.f * PI_F;

			lastRotation = controllerC.joystickRotation;
		}

		if (controllerC.keysStates[(uint8_t)ControllerAction::ThridAbility] != KeyState::Released)
			skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<TransformComponent>>()->setGlobalRotation(controllerC.joystickRotation);

		if (controllerC.keysStates[(uint8_t)ControllerAction::PrimaryAttack] != KeyState::Released && controllerC.keysStates[(uint8_t)ControllerAction::SecondaryAttack] != KeyState::Released)
		{
			attackAccelerations.local = Vec2f(17.f, 0);
		}

		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<PhysicsComponent>>()->addAccelerations(attackAccelerations);
		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<PhysicsComponent>>()->applyAccelerations(dt);

		TranslationData velocities = skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<PhysicsComponent>>()->getGlobalVelocities();
		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<TransformComponent>>()->moveLocal(velocities.local * dt);
		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<TransformComponent>>()->moveGlobal(velocities.global * dt);
		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<TransformComponent>>()->rotate(velocities.angular * dt);

		skeletonC.getJoint(JointIndex::RightHand).get<CPtr_t<PhysicsComponent>>()->resetAccelerations();
	}
}
