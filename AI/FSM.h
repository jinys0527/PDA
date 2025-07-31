#pragma once
#include <functional>
#include <unordered_map>
#include <string>

using StateFunc = std::function<void()>;
using StateFuncFloat = std::function<void(float)>;
struct State
{
	StateFunc OnEnter;
	StateFuncFloat OnUpdate;
	StateFunc OnExit;
};

struct Transition
{
	std::string from, to, onEvent;
};

class FSM
{
	using StateID = std::string;
public:
	void AddState(const StateID& id, const State& state)
	{
		m_States[id] = state;
	}

	void SetOnEnter(const StateID& id, StateFunc onEnter)
	{
		m_States[id].OnEnter = onEnter;
	}
	void SetOnUpdate(const StateID& id, StateFuncFloat onUpdate)
	{ 
		m_States[id].OnUpdate = onUpdate;
	}
	void SetOnExit(const StateID& id, StateFunc onExit)
	{
		m_States[id].OnExit   = onExit;
	}

	State& GetState(const StateID& id) { return m_States.at(id); }

	void AddTransition(const std::string& from, const std::string& to, const std::string& evt)
	{
		m_Transitions[from][evt] = to;
	}

	void Update(float deltaTime);

	void SetInitialState(const StateID& id);
	
	void Trigger(const std::string& evt);

	void OnEvent(const std::string& evt)
	{
		Trigger(evt);
	}

	void ChangeState(const StateID& id);

	const StateID& GetCurrentState() const { return m_CurrentState; }

private:
	std::unordered_map<StateID, State> m_States;
	std::unordered_map <StateID, std::unordered_map <std::string, StateID>> m_Transitions;
	StateID m_CurrentState;
};

