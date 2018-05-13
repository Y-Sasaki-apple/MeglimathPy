#pragma once
#include "Agent.h"
#include "Types.h"

class Cell
{
private:
	/// <summary>
	/// �}�X�ɂ͂߂�ꂽ�^�C��
	/// </summary>
	TileType _tile;

	/// <summary>
	/// �}�X�̓_��
	/// </summary>
	int _point;

public:
	/// <summary>
	/// �w��̃`�[���ɂ���ăZ���Ƀ^�C�����u�����
	/// </summary>
	/// <param name="team">�Z���Ƀ^�C����u���`�[��</param>
	void PaintedBy(TeamType team);

	/// <summary>
	/// �u���ꂽ�^�C�������
	/// </summary>
	void RemoveTile();

	/// <summary>
	/// �Z���ɂ͂߂�ꂽ�^�C�����擾����
	/// </summary>
	/// <returns>�Z���ɂ���^�C��</returns>
	TileType GetTile() const;

	/// <summary>
	/// �Z���̓��_���擾����
	/// </summary>
	/// <returns>�Z���̓��_</returns>
	int GetPoint() const;

public:
	Cell();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="point">�Z���̓��_</param>
	Cell(int point);
	virtual ~Cell();

};
