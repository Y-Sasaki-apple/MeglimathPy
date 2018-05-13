#pragma once

/// <summary>
/// �G�[�W�F���g�̓���
/// </summary>
enum class Action
{
	Move, RemoveTile, Stop
};

/// <summary>
/// ����̕���
/// </summary>
enum class Direction
{
	Right,
	RightUp,
	Up,
	LeftUp,
	Left,
	LeftDown,
	Down,
	RightDown,
	Stop
};

struct Step
{
	Step() :Step(Action::Stop, Direction::Right){}
	Step(Action a,Direction d):action(a),direction(d){}
	Action action;
	Direction direction;
};