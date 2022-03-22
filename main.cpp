#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

//Variables
sf::Vector2u resolution = { 400, 400 };

bool cirPickedUp = false;
bool cannotPlaceCir = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "SFML Window", sf::Style::Close | sf::Style::Titlebar);

	//Shapes
	sf::CircleShape cir;
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;
	sf::RectangleShape rect3;

	cir.setRadius(25);
	cir.setOrigin(cir.getRadius(), cir.getRadius());
	cir.setPosition(resolution.x / 2, resolution.y / 2);
	cir.setFillColor(sf::Color::Red);

	rect1.setSize(sf::Vector2f(50, 100));
	rect1.setOrigin(sf::Vector2f(rect1.getSize().x / 2, rect1.getSize().y / 2));
	rect1.setPosition(sf::Vector2f(resolution.x / 4, resolution.y / 2));
	rect1.setFillColor(sf::Color::Blue);
	sf::FloatRect rect1BoundingBox = rect1.getGlobalBounds();

	rect2.setSize(sf::Vector2f(50, 100));
	rect2.setOrigin(sf::Vector2f(rect2.getSize().x / 2, rect2.getSize().y / 2));
	rect2.setPosition(resolution.x / 4 * 3, resolution.y / 2);
	rect2.setFillColor(sf::Color::Blue);
	sf::FloatRect rect2BoundingBox = rect2.getGlobalBounds();

	rect3.setSize(sf::Vector2f(50, 100));
	rect3.setOrigin(sf::Vector2f(rect3.getSize().x / 2, rect3.getSize().y / 2));
	rect3.setPosition(resolution.x / 2, resolution.y / 4);
	rect3.setFillColor(sf::Color::Blue);
	sf::FloatRect rect3BoundingBox = rect3.getGlobalBounds();

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed:
				switch (e.key.code)
				{
				case sf::Keyboard::Up:
					cir.setRadius(cir.getRadius() + 1);
					cir.setOrigin(cir.getRadius(), cir.getRadius());
					cir.setPosition(resolution.x / 2, resolution.y / 2);
					break;
				case sf::Keyboard::Down:
					cir.setRadius(cir.getRadius() - 1); 
					cir.setOrigin(cir.getRadius(), cir.getRadius());
					cir.setPosition(resolution.x / 2, resolution.y / 2);
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					cout << "lmb" << endl;

					if (cirPickedUp)
					{
						if (!cannotPlaceCir)
						{
							cirPickedUp = false;
						}
					}
					else
					{
						sf::FloatRect cirBoundingBox = cir.getGlobalBounds();
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);

						if (cirBoundingBox.contains(sf::Vector2f(mousePos)))
						{
							cout << "hit" << endl;
							if (!cirPickedUp)
							{
								cirPickedUp = true;
							}
						}
					}
					
				}
			default:	break;
			}
		}

		if (cirPickedUp)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::FloatRect cirBoundingBox = cir.getGlobalBounds();

			cir.setFillColor(sf::Color::White);
			cir.setPosition(sf::Vector2f(mousePos));

			if (rect1BoundingBox.intersects(cirBoundingBox) || rect2BoundingBox.intersects(cirBoundingBox) || rect3BoundingBox.intersects(cirBoundingBox))
			{
				cir.setFillColor(sf::Color::Red);
				cannotPlaceCir = true;
			}
			else
			{
				cir.setFillColor(sf::Color::Green);
				cannotPlaceCir = false;
			}
		}
		else
		{
			cir.setFillColor(sf::Color::Green);
		}

		window.clear(sf::Color::Black);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(cir);
		window.display();
	}

	return 0;
}
