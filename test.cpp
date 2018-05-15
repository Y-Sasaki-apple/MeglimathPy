#include"Board.h"
#include<memory>
int main() {
	std::unique_ptr<Board> B(new Board());
	B->init_board(1);
	B->do_move(30);
	B->do_move(30);
	B->get_current_state();
}