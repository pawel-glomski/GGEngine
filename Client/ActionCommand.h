#pragma once
#include <cstdint>
#include <corecrt_math.h>
#include <array>
#include <vector>
#include <iostream>
#include "Singleton.h"
#include "Vec2.h"

class ActionCommandsManager
{
	// ...
};

class ActionCommand
{
public:

	enum class ID : uint16_t
	{
		NoActionCommand, RotateCommand, WalkForwardCommand, WalkBackwardCommand, WalkLeftCommand, WalkRightCommand, 
		DashCommand,
		Count
	};
	enum class ExecutionStage : uint8_t
	{
		// when action starts execution (changes to MidWay after first frame of execution)
		Beginning,	

		/*when action is executing non-last stage, or is repeatable (only in this stage, player can change action behaviour by releasing button)
		(changes to Ending on player button release, or action by itself after reaching the last stage of execution) */
		MidWay,		

		// when action is executing the last stage, or when player released button
		Ending		
	};

protected:

public:
	struct ExecutionData
	{
		float_t executingTime = 0.f; // action progress
		float_t chargingTime = 0;	 // for charging actions
		ExecutionStage stage = ExecutionStage::Beginning;

		Vect2f activationMousePosition;
		class Entity* actionTarget = nullptr;
	};

public:
	static ActionCommand* getActionByID(ActionCommand::ID id);

	// return true if finished executing (false if it is repeatable action)
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const = 0;

	bool isFinished(const ExecutionData & data) const;

	ActionCommand::ID getID() const;

protected:
	ActionCommand() = delete;
	ActionCommand(ActionCommand::ID id);

protected:
	static std::array<ActionCommand*, (uint8_t)ID::Count> actionByID;

	ID id = ID::NoActionCommand;
	float_t executionTime = 0;		// time needed to execute whole action
	bool repeatable = false;		// after finishing execution, restart the whole process and keep executing (modifies ExecutionData (time))
};

class RotateCommand : public ActionCommand, public Singleton<RotateCommand>
{
	friend class Singleton<RotateCommand>;
	RotateCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class NoActionCommand : public ActionCommand, public Singleton<NoActionCommand>
{
	friend class Singleton<NoActionCommand>;
	NoActionCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkForwardCommand : public ActionCommand, public Singleton<WalkForwardCommand>
{
	friend class Singleton<WalkForwardCommand>;
	WalkForwardCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkBackwardCommand : public ActionCommand, public Singleton<WalkBackwardCommand>
{
	friend class Singleton<WalkBackwardCommand>;
	WalkBackwardCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkLeftCommand : public ActionCommand, public Singleton<WalkLeftCommand>
{
	friend class Singleton<WalkLeftCommand>;
	WalkLeftCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkRightCommand : public ActionCommand, public Singleton<WalkRightCommand>
{
	friend class Singleton<WalkRightCommand>;
	WalkRightCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class DashCommand : public ActionCommand, public Singleton<DashCommand>
{
	friend class Singleton<DashCommand>;
	DashCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};
