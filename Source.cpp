#define BOOST_PYTHON_STATIC_LIB    
#include"Board.h"
#include"GameLogic/GameLogic.h"
#include<boost\python.hpp>

BOOST_PYTHON_MODULE(MeglimathPy) {
	using namespace boost::python;
	class_<Board>("Board")
		.def("init_board", &Board::init_board)
		.def("do_move", &Board::do_move)
		.def("has_a_winner", &Board::has_a_winner)
		.def("game_end", &Board::game_end)
		;
}