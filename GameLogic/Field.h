#pragma once
#include "Cell.h"
#include "Transform.h"
#include "GamePoints.h"

class Field
{
private:
	/// <summary>
	/// �t�B�[���h���
	/// </summary>
	_Grid<Cell> _cells;

	/// <summary>
	/// �̈�|�C���g���v�Z����Ƃ��T�����������i�[����
	/// </summary>
	_Grid<bool> _status;

	GamePoints _points[2];

private:
	/// <summary>
	/// �͂܂�Ă���̈��T������
	/// </summary>
	/// <param name="pos">�T�����J�n������W</param>
	/// <param name="tile">�ǂ̃^�C���ň͂܂�Ă��邩</param>
	void dfsAreaPoint(_Point<> pos, TileType tile);

	/// <summary>
	/// �w��̃^�C���ň͂܂ꂽ�̈�̓��_���W�v���܂�
	/// </summary>
	/// <param name="tile">�ǂ̃^�C���ň͂܂�Ă��邩</param>
	/// <returns>�̈�|�C���g</returns>
	int aggregateAreaPoint(TileType tile);

	/// <summary>
	/// �w��̃^�C���̃^�C���|�C���g���W�v���܂�
	/// </summary>
	/// <param name="tile">���_���W�v����^�C��</param>
	/// <returns>�^�C���|�C���g</returns>
	int aggregateTilePoint(TileType tile);

	int aggregateTotalPoint(TileType tile);

public:

	/// <summary>
	/// �^�C���Ɨ̈�̃|�C���g���W�v���A�f�[�^���X�V����
	/// </summary>
	void UpdatePoint();

	/// <summary>
	/// �Z�������擾����
	/// </summary>
	/// <returns>�t�B�[���h�̃Z�����</returns>
	_Grid<Cell> GetCells() const;

	std::vector<int> GetAreaPoints() const;
	std::vector<int> GetTilePoints() const;
	std::vector<int> GetTotalPoints() const;

	/// <summary>
	/// �Z����h��
	/// </summary>
	/// <param name="pos">�h��Z���̍��W</param>
	/// <param name="team">�Z����h��`�[��</param>
	void PaintCell(_Point<> pos, TeamType team);

	/// <summary>
	/// �^�C�������
	/// </summary>
	/// <param name="pos">�^�C���̍��W</param>
	void RemoveTile(_Point<> pos);

	/// <summary>
	/// �w����W���t�B�[���h�̒��ł��邩���肷��
	/// </summary>
	/// <param name="pos">�t�B�[���h�������肷����W</param>
	/// <returns>���W���t�B�[���h���ł��邩</returns>
	bool IsInField(_Point<> pos) const;

	/// <summary>
	/// ���W�ƕ����A�t�B�[���h��Ԃ���K�v�ȍs�������߂�
	/// </summary>
	/// <param name="pos">�w������ɓ����O�̍��W</param>
	/// <param name="dir">�s���������</param>
	/// <returns>�K�v�ȍs��</returns>
	Step DecideStepByDirection(_Point<> pos, Direction dir) const;

public:
	Field();

	void operator=(const Field& other);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="size">�t�B�[���h�̑傫��</param>
	Field(_Size size);

	/// <summary>
	/// �Z�������Ƀt�B�[���h�𐶐�����R���X�g���N�^
	/// </summary>
	/// <param name="cells">���ƂȂ�Z��</param>
	Field(_Grid<Cell> cells);

	/// <summary>
	/// �t�B�[���h�𐶐����܂�
	/// </summary>
	/// <param name="file">�t�B�[���h���̂���json�t�@�C��</param>
	Field(std::string json);

	virtual ~Field();
};
