#pragma once
#include"Think.h"
#include "Field.h"
#include"TeamLogic.h"
#include<unordered_map>
#include<vector>
class GameLogic
{
private:
	Field _field;
	int _turn;
	std::vector<TeamLogic> _teamlogics;

public:

	/// <summary>
	/// �G�[�W�F���g�������_���ɏ���������
	/// </summary>
	void initAgentsPos();

	/// <summary>
	/// �G�[�W�F���g�̏������������s��
	/// </summary>
	/// <param name="init_pos">�G�[�W�F���g�̏������W�̂��ƂɂȂ鍶��̍��W</param>
	void initAgentsPos(_Point<> init_pos);

public:
	std::vector<TeamLogic>& getTeamLogics();
	/// <summary>
	/// json����Q�[��������������
	/// </summary>
	/// <param name="path">json</param>
	void InitalizeFromJson(const std::string json);

	int GetTurn() const;

	Field GetField() const;

	/// <summary>
	/// �Q�[���̏�Ԃ��X�V����
	/// ���ׂẴG�[�W�F���g�����擾����
	/// </summary>
	/// <returns>���ׂẴG�[�W�F���g��񃊃X�g</returns>
	std::vector<Agent> GetAgents() const;

	/// <summary>
	/// �`�[�����Ƃ̃G�[�W�F���g�̏����擾����
	/// </summary>
	/// <returns>�`�[�����Ƃ̃G�[�W�F���g���</returns>
	std::unordered_map<TeamType, std::vector<Agent>> GetAgentMap() const;

	/// <summary>
	/// �Q�[�������̃^�[���ɐi�߂�
	/// </summary>
	void NextTurn(std::unordered_map<TeamType, Think> &_thinks);

	bool GetGameEnd();
	int GetWinner();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameLogic();
	GameLogic(int turn);

	virtual ~GameLogic();
};
