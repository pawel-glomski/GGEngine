#pragma once
#include <cstdint>
#include <corecrt_math.h>
#include <array>
#include <vector>
#include <iostream>

class ActionCommand
{
public:
	// for server package 
	enum class ID : uint16_t
	{
		NoActionCommand, WalkForwardCommand, WalkBackwardCommand, WalkLeftCommand, WalkRightCommand, Count
	};

protected:
	template<class T>
	class Singleton
	{
	public:
		static T & instance()
		{
			static T inst;
			return inst;
		}
	protected:
		Singleton() = default;
	private:
		T & operator=(const Singleton& right) = delete;
		Singleton(const Singleton& right) = delete;
	};
public:
	struct ExecutionData
	{
		float_t actionExecutingTime = 0.f;	// action progress
		uint8_t timelineBreakPoint = 0;		// current BreakPoint
		float_t chargingTime = 0;			// for charging actions
		float_t chargedValue = 0;
		bool endAction = false;				// if true, ControllerButton was released
	};

public:
	static ActionCommand* getActionByID(ActionCommand::ID id);

	// return true if finished executing (false if it is repeatable action), may modify "ExecutionData" if it is repeatable command
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const = 0;

	ActionCommand::ID getID() const;

protected:
	ActionCommand() = default;

protected:
	static std::array<ActionCommand*, (uint8_t)ID::Count> actionByID;	// indices 

	ID id = ID::NoActionCommand;
	bool repeatable = false;					// after finishing execution, restart whole process and keep executing (modify ExecutionData passed to "execute" member function)
	bool playerStopable = false;				// if player can stop this action (or only some part of it (stop charging, etc.))
	float_t executionTime = 0;					// time needed to execute whole action
	std::vector<float_t> timelineBreakPoints;	// points in time, that behaviour of action changes
};

class NoActionCommand : public ActionCommand, public ActionCommand::Singleton<NoActionCommand>
{
	friend class ActionCommand::Singleton<NoActionCommand>;
	NoActionCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkForwardCommand : public ActionCommand, public ActionCommand::Singleton<WalkForwardCommand>
{
	friend class ActionCommand::Singleton<WalkForwardCommand>;
	WalkForwardCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkBackwardCommand : public ActionCommand, public ActionCommand::Singleton<WalkBackwardCommand>
{
	friend class ActionCommand::Singleton<WalkBackwardCommand>;
	WalkBackwardCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkLeftCommand : public ActionCommand, public ActionCommand::Singleton<WalkLeftCommand>
{
	friend class ActionCommand::Singleton<WalkLeftCommand>;
	WalkLeftCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};

class WalkRightCommand : public ActionCommand, public ActionCommand::Singleton<WalkRightCommand>
{
	friend class ActionCommand::Singleton<WalkRightCommand>;
	WalkRightCommand();
public:
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) const override;
};
