#include <bangtal.h>

using namespace bangtal;

//좌표를 구조체로만들기
//struct Rect {
//	int centerX, centerY, radius;
//};

//클래스로 사실 구조체랑 같지만 구조체는 퍼블릭이 기본, 클래스는 프라이빗이 기본
class Rect {
public:	
	int centerX, centerY, radius;
	//생성자 함수
	Rect(int cx, int cy, int r) : centerX(cx), centerY(cy), radius(r) {};

	bool checkin(int x, int y) {
		return (x > centerX - radius) && (x < centerX + radius)
			&& (y > centerY - radius) && (y < centerY + radius);
	}
};

//bool checkin(int x, int y, const Rect& rect)
//{
//	//이 좌표의 사각형안에 클릭이 되면 x,y값이 참이면 true, 안되면 false를 반환하게
//	return (x > rect.centerX - rect.radius) && (x < rect.centerX + rect.radius) 
//		&& (y > rect.centerY - rect.radius) && (y < rect.centerY + rect.radius);
//}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	auto scene = Scene::create("틀린그림찾기", "Images/problem.png");
	auto problem = Object::create("Images/problem.png", scene, 0, 0, true);

	//구조체 사용
	/*Rect left_rect1; left_rect1.centerX = 568; left_rect1.centerY = 594; left_rect1.radius = 54;
	Rect right_rect1; right_rect1.centerX = 1186; right_rect1.centerY = 594; right_rect1.radius = 54;*/

	//클래스 사용
	Rect left_rect1(568,594,54);
	Rect right_rect1(1168,594,54);
	
	//7개의 체크포인트는 배열을 이용
	const int num_difference = 7;
	Rect left_rects[num_difference] = {
		{568, 594, 54}, {99, 551, 17}, {383, 482, 16}, {401,158,27}, {61, 255, 36}, {592, 421, 35}, {320, 117, 13}
	};
	Rect right_rects[num_difference] = {
		{1186, 594, 54}, {717, 551, 17}, {1001, 482, 16}, {1019,158,27}, {679, 255, 36}, {1210, 421, 35}, {938, 117, 13}
	};

	const int check_size = 25;
	//체크 7개 선언만 함.
	ObjectPtr left_check[num_difference];
	ObjectPtr right_check[num_difference];

	//반복문으로 할당
	for (int i = 0; i < num_difference; ++i) {
		left_check[i] = Object::create("Images/check.png", scene, left_rects[i].centerX - check_size, left_rects[i].centerY - check_size, false);
		right_check[i] = Object::create("Images/check.png", scene, right_rects[i].centerX - check_size, right_rects[i].centerY - check_size, false);
	}
	
	int count = 0;
	problem->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction)->bool {
		//중심이 (568, 564), 달 중앙점이 대충 54인 사각형에 (x,y)가 포함되면 체크를 보인다. ->조건문 이용
		// 간략하고 알기쉽게
		bool checked = false;
		for (int i = 0; i < num_difference; ++i) {
			if (left_rects[i].checkin(x, y) || right_rects[i].checkin(x, y)) { //왼쪽달을 클릭했거나 오른쪽달을 클릭하면
				left_check[i]->show();
				right_check[i]->show();
				checked = true;
				count++;
			}
		}
			if (checked == false) {
				endGame();
			}

			if (count == num_difference) {
				showMessage("다 찾았다!");
			}
		
		
		//그렇지 않으면 게임을 종료한다.
		return true;
	});


	startGame(scene);

	return 0;
}