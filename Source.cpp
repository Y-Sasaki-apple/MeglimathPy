#include"Board.h"
#include"simulater/MeglimathCore/GameLogic/GameLogic.h"
#define BOOST_PYTHON_STATIC_LIB  
#include<boost\python.hpp>

BOOST_PYTHON_MODULE(MeglimathPy) {
	using namespace boost::python;
	namespace np = boost::python::numpy;
	Py_Initialize();
	np::initialize();
	class_<Board>("Board")
		.def("init_board", &Board::init_board)
		.def("do_move", &Board::do_move)
		.def("has_a_winner", &Board::has_a_winner)
		.def("game_end", &Board::game_end)
		.def("get_current_player",&Board::get_current_player)
		.def("get_current_state",&Board::get_current_state)
		.def("get_board_state",&Board::get_board_state)
		.def("get_player_state", &Board::get_player_state)
		.add_property("availables",&Board::get_availables)
		;
}