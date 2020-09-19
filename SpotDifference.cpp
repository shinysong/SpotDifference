#include <bangtal.h>

using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	auto scene = Scene::create("틀린그림찾기", "Images/problem.png");
	auto problem = Object::create("Images/problem.png", scene, 0, 0, true);

	problem->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction)->bool {
		
		endGame();
		return true;
	});


	startGame(scene);

	return 0;
}