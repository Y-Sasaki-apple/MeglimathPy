#pragma once
#include "Types.h"
#include "Action.h"

class Agent
{
private:
	/// <summary>
	/// �擾�����^�C���|�C���g
	/// </summary>
	int _tile_point;

	/// <summary>
	/// ���W
	/// </summary>
	_Point<> _position;

public:
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���݂̍��W</returns>
	_Point<> GetPosition() const;

	/// <summary>
	/// �G�[�W�F���g�𓮂���
	/// </summary>
	/// <param name="dir">����������</param>
	void Move(Direction dir);

public:
	Agent();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	Agent(_Point<> position);

	virtual ~Agent();
};

