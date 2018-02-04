#include "ActionCommand.h"
#include "Character.h"
#include "MathUtilities.h"

std::array<ActionCommand*, (uint16_t)ActionCommand::ID::Count> ActionCommand::actionByID;

ActionCommand::ActionCommand(ActionCommand::ID id)
{
	this->id = id;
	actionByID[(uint8_t)id] = this;
}

ActionCommand * ActionCommand::getActionByID(ActionCommand::ID id)
{
	return actionByID[(uint8_t)id];
}

bool ActionCommand::isFinished(const ExecutionData & data) const
{
	return 	(data.executingTime >= executionTime) && (!repeatable || data.stage == ExecutionStage::Ending);
}

ActionCommand::ID ActionCommand::getID() const
{
	return id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

NoActionCommand::NoActionCommand() : ActionCommand(ActionCommand::ID::NoActionCommand)
{
	//////////////////////////////
	// must have

	// must have
	//////////////////////////////
}

bool NoActionCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	std::cout << "Do Nothing" << std::endl;
	data.stage = ExecutionStage::Ending;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkForwardCommand::WalkForwardCommand() : ActionCommand(ActionCommand::ID::WalkForwardCommand)
{	
	repeatable = true;
}

bool WalkForwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	if (data.stage != ExecutionStage::Ending)
	{
		data.stage = ExecutionStage::MidWay;
		data.executingTime += deltaTime;
		executor.moveForward({ 500 * deltaTime });
	}
	return isFinished(data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkBackwardCommand::WalkBackwardCommand() : ActionCommand(ActionCommand::ID::WalkBackwardCommand)
{
	repeatable = true;
}

bool WalkBackwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	if (data.stage != ExecutionStage::Ending)
	{
		data.stage = ExecutionStage::MidWay;
		data.executingTime += deltaTime;
		executor.moveForward({ -500 * deltaTime });
	}
	return isFinished(data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkLeftCommand::WalkLeftCommand() : ActionCommand(ActionCommand::ID::WalkLeftCommand)
{
	repeatable = true;
}

bool WalkLeftCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	if (data.stage != ExecutionStage::Ending)
	{
		data.stage = ExecutionStage::MidWay;
		data.executingTime += deltaTime;
		executor.moveRight({ -500 * deltaTime });
	}
	return isFinished(data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkRightCommand::WalkRightCommand() : ActionCommand(ActionCommand::ID::WalkRightCommand)
{
	repeatable = true;
}

bool WalkRightCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	if (data.stage != ExecutionStage::Ending)
	{
		data.stage = ExecutionStage::MidWay;
		data.executingTime += deltaTime;
		executor.moveRight({ 500 * 0.016 });
	}
	return isFinished(data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

DashCommand::DashCommand() : ActionCommand(ActionCommand::ID::DashCommand)
{
	executionTime = 5.2f;
}

bool DashCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	if (data.stage == ExecutionStage::Beginning)
	{
		data.activationMousePosition = RawInputReceiver::instance().getCurrentInput().mousePos;
		data.stage = ExecutionStage::Ending;
	}
	auto delta = data.activationMousePosition - executor.getGlobalPosition();

	data.executingTime += deltaTime;
	float_t distance = 1000 * deltaTime;

	clamp(distance, 0.f, delta.length());
	executor.moveForward(distance);
	std::cout << distance << std::endl;
	if (distance < 0.5)
		data.executingTime = executionTime;

	return isFinished(data);
}

RotateCommand::RotateCommand() : ActionCommand(ID::RotateCommand)
{
	repeatable = true;
}

bool RotateCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	float_t delta = angleBetweenVectors(executor.getForwardVector(), (Vect2f)RawInputReceiver::instance().getCurrentInput().mousePos - executor.getGlobalPosition());
	if (delta != 0)
	{
		float_t rotationSpeed = 2.f*PI_F / 0.35f * deltaTime;	// speed: can rotate 360 degrees in 0.3 of a second
		rotationSpeed = clamp(rotationSpeed, 0.f, abs(delta));
		rotationSpeed *= sign(delta);

		executor.rotate(rotationSpeed);
	}
	// never ends
	return false;
}
