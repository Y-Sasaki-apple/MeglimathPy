#pragma once
#include<memory>
#include<boost/python.hpp>
#include"GameLogic/GameLogic.h"
namespace py = boost::python;

class Board {
	std::unique_ptr<GameLogic> gamelogic;
	std::unordered_map<TeamType, Think> _thinks;
	TeamType turn{ TeamType::A };
	TeamType first{ TeamType::A };
public:
	void init_board(int start_player);
	void do_move(int move);
	py::tuple has_a_winner();
	py::tuple game_end();
	int get_current_player();

	Board();
	Board(const Board &);
};