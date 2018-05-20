#pragma once
#include<memory>
#include"GameLogic/GameLogic.h"
#define BOOST_PYTHON_STATIC_LIB    
#define BOOST_NUMPY_STATIC_LIB    
#include<boost/python/numpy.hpp>
#include<boost/python.hpp>
namespace py = boost::python;
namespace np = boost::python::numpy;
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
	np::ndarray get_current_state();
	np::ndarray get_board_state();
	np::ndarray get_player_state();
	py::list get_availables()const;
	Board();
	Board(const Board &);
};