#pragma once
#include <functional>
#include <unordered_map>
#include <string>

class FSM
{
	using StateID = std::string;
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

	void AddState(const StateID& id, const State& state)
	{
		m_States[id] = state;
	}

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

