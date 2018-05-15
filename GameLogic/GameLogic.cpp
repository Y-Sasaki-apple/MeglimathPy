#include "GameLogic.h"
#include<random>
#include <rapidjson/document.h>
std::unordered_map<TeamType, std::vector<Agent>> GameLogic::GetAgentMap() const
{
	std::unordered_map<TeamType, std::vector<Agent>> agents;
	agents[TeamType::A] = _teamlogics[0].GetAgents();
	agents[TeamType::B] = _teamlogics[1].GetAgents();

	return agents;
}
std::vector<Agent> GameLogic::GetAgents() const
{
	std::vector<Agent> ret{ _teamlogics[0].GetAgents() };
	std::vector<Agent> con{ _teamlogics[1].GetAgents() };
	ret.insert(ret.end(),con.begin(),con.end());
	return ret;
}
std::vector<TeamLogic>& GameLogic::getTeamLogics()
{
	return _teamlogics;
}
void GameLogic::initAgentsPos()
{
	_Size size = _field.GetCells().size();

	initAgentsPos(_Point<int>(std::rand() / (double)INT_MAX*(size.x - 2) / 2, std::rand() / (double)INT_MAX*(size.x - 2) / 2));
}

void GameLogic::initAgentsPos(_Point<> init_pos)
{
	_Size size = _field.GetCells().size();

	size -= _Point(1, 1);
	_Point<> agent_pos[] =
	{
		init_pos,
		_Point<int>(size.x - init_pos.x, init_pos.y),
		_Point<int>(init_pos.x, size.y - init_pos.y),
		size - init_pos
	};

	// �G�[�W�F���g�̏����ʒu�̃^�C����h��
	_field.PaintCell(agent_pos[0], TeamType::A);
	_field.PaintCell(agent_pos[1], TeamType::A);

	_field.PaintCell(agent_pos[2], TeamType::B);
	_field.PaintCell(agent_pos[3], TeamType::B);

	_teamlogics[0].InitAgentsPos(agent_pos[0], agent_pos[1]);
	_teamlogics[1].InitAgentsPos(agent_pos[2], agent_pos[3]);
}


void GameLogic::InitalizeFromJson(const std::string json)
{
	rapidjson::Document document;
	document.Parse(json.data());

	//JSONReader json(path);

	_field = Field(json);
	if (document.HasMember("InitPos")) {
		initAgentsPos(_Point{ document["InitPos"].GetString() });
	}
	else {
		initAgentsPos();
	}
	//if (json[U"InitPos"].isNull())
	//{
	//	initAgentsPos();
	//}
	//else
	//{
	//	initAgentsPos(json[U"InitPos"].get<Point>());
	//}
	_turn = document["Turn"].GetInt();
	//_turn = json[U"Turn"].get<int>();
}


int GameLogic::GetTurn() const
{
	return _turn;
}

void GameLogic::NextTurn(std::unordered_map<TeamType, Think> &_thinks)
{
	if (_turn <= 0)
	{
		return;
	}
	auto agents_map = GetAgentMap();
	auto agents = GetAgents();

	// �V�~�����[�V����
	std::vector<std::pair<_Point<>, std::pair<Direction, TeamType>>> move_point_arr;
	std::vector<_Point<>> remove_points;
	for (TeamType team : {TeamType::A, TeamType::B})
	{
		for (int i = 0; i < 2; i++)
		{
			Direction dir = _thinks[team].steps[i].direction;
			// �G�[�W�F���g�𓮂������������ɓ��������ꍇ�̍��W
			_Point pos = agents_map[team][i].GetPosition() + Transform::DirToDelta(dir);

			// �G�[�W�F���g�����삷����W��ǉ�
			switch (_thinks[team].steps[i].action)
			{
			case Action::Move:
				move_point_arr.push_back(std::make_pair(pos, std::make_pair(dir, team)));
				break;
			case Action::RemoveTile:
				remove_points.push_back(pos);
				break;
			}
		}
	}

	// �Փ˂��Ă��Ȃ��G�[�W�F���g�̍s���̂ݎ��s����
	for (auto & pos_map : move_point_arr)
	{
		auto pos = pos_map.first;

		// ���̍��W�ɍs���G�[�W�F���g����l�A�t�B�[���h��
		// �^�C�����u����Ă��Ȃ��A�ǂ̃G�[�W�F���g�����Ȃ�

		if (std::count_if(move_point_arr.cbegin(), move_point_arr.cend(), [pos](std::pair<_Point<>, std::pair<Direction, TeamType>> itr) {return itr.first == pos; }) == 1
			&& _field.IsInField(pos)
			&& _field.GetCells()[pos.y][pos.x].GetTile() == TileType::None
			&& std::count_if(agents.cbegin(), agents.cend(), [pos](Agent agent) { return agent.GetPosition() == pos; }) == 0)
		{
			auto dir = pos_map.second.first;
			auto team = pos_map.second.second;

			// �i�񂾃Z����h��
			_field.PaintCell(pos, team);

			// ���̍��W�ɖ߂�
			pos -= Transform::DirToDelta(dir);

			// �G�[�W�F���g�𓮂���
			_teamlogics[static_cast<int>(team)].MoveAgent(pos, dir);
		}
	}

	// �^�C�������s�������s
	for (auto & remove_point : remove_points)
	{
		if (std::count_if(remove_points.cbegin(), remove_points.cend(), [remove_point](auto p) {return p == remove_point; }) == 1 && _field.IsInField(remove_point))
		{
			_field.RemoveTile(remove_point);
		}
	}

	// �^�[����i�߂�
	_turn--;

	// �`�[���̓��_���X�V
	_field.UpdatePoint();
}

bool GameLogic::GetGameEnd()
{
	return GetTurn() == 0;
}

int GameLogic::GetWinner()
{
	if (GetTurn() != 0)return -1;
	if (_teamlogics[0].GetTotalPoint() > _teamlogics[1].GetTotalPoint()) {
		return (int)TeamType::A;
	}
	else if (_teamlogics[0].GetTotalPoint() < _teamlogics[1].GetTotalPoint()) {
		return (int)TeamType::B;
	}
	else {
		return -1;
	}
}

Field GameLogic::GetField() const
{
	return _field;
}

GameLogic::GameLogic() :_teamlogics({ TeamLogic(),TeamLogic() })
{

}

GameLogic::GameLogic(int turn) : _turn(turn), _teamlogics({ TeamLogic(),TeamLogic() })
{
}

GameLogic::~GameLogic()
{
}
