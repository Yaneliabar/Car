#include <SFML/Graphics.hpp> // подключил библиотеку SFML
using namespace sf;
int x, xCar1, xCar2;
float yCar1, yCar2, y, coorfone;
bool gameover; // переменные будут использоваться ниже, те что  float связаны со временем
void setup()
{
	gameover = false;
	x = 3;
	y = 520;
	xCar1 = (rand() % 2);
	xCar2 = 1 + (rand() % 2);
	yCar1 = 300;
	yCar2 = 1; // необязательно выводить отдельную функцию но мне так проще, наверное
}
void drow()
{
	RenderWindow window(VideoMode(300, 600), "Cars"); // создаю окно
	float timer = 0, delay = 0.3;
	Clock clock;  // переменные непосредственно связанные со временем
	while (window.isOpen()) // цикл выполнения
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time; // само время

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				gameover = true; // событие на закрытие если нажать закрытие окна
			}
			if (event.type == Event::KeyPressed) {
				if (x >= 1 && event.key.code == Keyboard::Left) x--;
				if (x <= 2 && event.key.code == Keyboard::Right) x++;
			} // проверка на нажатие кнопок вправо и влево, более не надо
		}
		Texture texture;
		Texture texture1;
		Texture texture2;
		Texture texture3; 



		texture.loadFromFile("C:\\Car.png");
		texture1.loadFromFile("C:\\Car1.png");
		texture2.loadFromFile("C:\\2.png");
		texture3.loadFromFile("C:\\printgameover.png"); // загружаем текстуры

		window.clear(Color(120, 110, 100, 0));

		Sprite fone(texture2);
		fone.setPosition(0, 0);
		fone.setTextureRect(IntRect(coorfone, 0, 300, 600));
		if (timer > delay) {
			coorfone += 300;
			if (coorfone == 1200) {
				coorfone = 0;
			}
		} // фон меняестя от времени в одной текстуре прорисованно 4 фона, меняем их по координатам
		window.draw(fone);

		Sprite printCar(texture);
		printCar.setPosition(60 + x * 50, y);
		window.draw(printCar); // прорисовка главной машины, которая управляеться игроком

		Sprite printCar1(texture1);
		printCar1.setPosition(60 + xCar1 * 50, yCar1);
		if (timer > delay * 3) {
			yCar1 += 10;
			if (yCar1 > 600) {
				yCar1 = 0;
				xCar1 = (rand() % 2);
			}
		} 
		window.draw(printCar1); // прорисовка первой "враждебной" машины, координата х меняется рандомно, либо 1 либо 2 полоса

		Sprite printCar2(texture1);
		printCar2.setPosition(60 + xCar2 * 50, yCar2);
		if (timer > delay * 3) {
			yCar2 += 10;
			if (yCar2 > 600) {
				yCar2 = 0;
				xCar2 = 2 + (rand() % 2);
			}
		}
		window.draw(printCar2); // прорисовка второй "враждебной" машины, координата х меняется рандомно, либо 3 либо 4 полоса

		if ((x == xCar1 && y == yCar1 + 50) || (x == xCar2 && y == yCar2 + 50)) {
			delay = 1000;
			Sprite gameover(texture3);
			gameover.setPosition(0, 0);
			window.draw(gameover);
		} // условия проигрыша и вывод картинки геймовера


		window.display(); // отрисовка всего окна
	}

}
int main() {
	setup();
	while (!gameover)
		drow(); // вызовы функций
	return 0;
}
