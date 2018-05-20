#include"Board.h"
#include<memory>
int main() {
	std::unique_ptr<Board> B(new Board());
	B->get_availables();
}