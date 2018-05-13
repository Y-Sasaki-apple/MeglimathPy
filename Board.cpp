#define BOOST_PYTHON_STATIC_LIB    
#include"Board.h"
#include"GameLogic/GameLogic.h"
#include<boost\python\tuple.hpp>
void Board::init_board(int start_player)
{
	gamelogic.reset(new GameLogic());
}
void Board::do_move(int move)
{
	auto team = gamelogic->getTeamLogics()[0];
	int move1 = move / 17;
	int move2 = move % 17;
	Action act1{ move1 / 8 };
	Action act2{ move2 / 8 };
	Direction dir1{ (int)act1 == 8 ? 8 : move1 % 8 };
	Direction dir2{ (int)act1 == 8 ? 8 : move2 % 8 };
	Think think{ {act1,dir1},{act2,dir2} };
	_thinks[turn] = think;
	if (turn != first) {
		gamelogic->NextTurn(_thinks);
	}
	turn = turn == TeamType::A ? TeamType::B : TeamType::A;
}
py::tuple Board::has_a_winner()
{
	return py::make_tuple(gamelogic->GetGameEnd(), gamelogic->GetWinner());
}
py::tuple Board::game_end()
{
	return py::make_tuple(gamelogic->GetWinner() != -1, gamelogic->GetWinner());
}
int Board::get_current_player()
{
	return (int)turn;
}
Board::Board() :gamelogic(new GameLogic())
{

}

Board::Board(const Board &):gamelogic(new GameLogic())
{
}
