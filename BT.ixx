import <SFML/Graphics.hpp>;
import <iostream>;

#include "C:\SFML\include\SFML\Graphics\RenderTarget.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

export module All_Modules:BT;
export import :GlobalGame;

export
{
	class Button
	{
	private:
		
		sf::Text bText;

		int bWidth;
		int bHeight;

	public:
		sf::RectangleShape button;

		Button()
		{

		}

		Button(std::string text, sf::Vector2f bSize, int charSize, sf::Color bgColor, sf::Color textColor)
		{
			std::cout << "Creating a button..." << std::endl;

			button.setSize(bSize);
			button.setFillColor(bgColor);

			bWidth = bSize.x;
			bHeight = bSize.y;

			bText.setString(text);
			bText.setCharacterSize(charSize);
			bText.setFillColor(textColor);
		}

		void setFont(sf::Font& font)
		{
			bText.setFont(font);
		}

		void setBackgroundColor(sf::Color color)
		{
			button.setFillColor(color);
		}

		void setTextColor(sf::Color color)
		{
			bText.setFillColor(color);
		}

		void setPosition(sf::Vector2f point)
		{
			button.setPosition(point);

			//Center Text
			float x = (point.x + bWidth / 2) - (bText.getLocalBounds().width / 2);
			float y = (point.y + bHeight / 2.2) - (bText.getLocalBounds().height / 2);

			bText.setPosition(x, y);
		}

		void drawTo(sf::RenderWindow& window)
		{
			//make window global
			//first button, then text (nakładanie warstw)
			window.draw(button);
			window.draw(bText);
		}

		bool isMouseOver(sf::RenderWindow& window)
		{
			int mX = sf::Mouse::getPosition(window).x;
			int mY = sf::Mouse::getPosition(window).y;

			int bX = button.getPosition().x;
			int bY = button.getPosition().y;

		
			int btnxPosWidth = button.getPosition().x + bWidth;
			int btnyPosHeight = button.getPosition().y + bHeight;

			if (mX < btnxPosWidth && mX > bX && mY < btnyPosHeight && mY > bY)
			{
				return true;
			}
			return false;
		}


	};
	
	class Textbox : public sf::Transformable, public sf::Drawable
	{
	private:
		int tSize;
		sf::Font tFont;
		sf::Text tText;
		sf::RectangleShape tRec;
		
		
	public:
		bool isSelected;

		Textbox()
		{
			std::cout << "Default Textbox Constructor" << std::endl;
		}

		Textbox(int max, int r, int g, int b)
		{
			this->tSize = max;
			this->tRec.setSize(sf::Vector2f(10*70, 80));
			this->isSelected = false;
			


			if (!tFont.loadFromFile("C:/Users/marta/Desktop/93c59897-gr11-repo/Project/x64/Release/CollegiateBlackFLF.ttf"))
				std::cout << "ERROR! Textbox font not loaded." << std::endl;
			else
			{
				tText.setCharacterSize(50);
				tText.setFont(tFont);
				tText.setFillColor(sf::Color::Black);
				tRec.setOutlineThickness(5);
				tRec.setFillColor(sf::Color(255, 255, 224));
				tRec.setOutlineColor(sf::Color(r, g, b)); //outlines same as button colors
				tRec.setPosition(this->getPosition());
			}
		}

		std::string getText()
		{
			return this->tText.getString();
		}

		
		void setPosition(float x, float y)
		{
			sf::Transformable::setPosition(x, y);
			tRec.setPosition(x, y);

			tText.setPosition(x+5, y+3);
		}

		bool isInside(sf::Vector2f point)
		{
			return tRec.getGlobalBounds().contains(point);
		}

		void setSelected(bool sel)
		{
			this->isSelected = sel;

			if (!sel)
				tRec.setOutlineColor(sf::Color(127, 127, 127));
			else
				tRec.setOutlineColor(sf::Color::Cyan);
		}

		std::string inputLogic(sf::Event e, std::string &x)
		{
			if (!isSelected || e.type != sf::Event::TextEntered)
				return "";
			else if (e.text.unicode == 8)
			{
				x = x.substr(0, x.size() - 1);
				tText.setString(x);
			}
			else if (x.size() < tSize)
			{
				x += e.text.unicode;
				tText.setString(x);
			}
			else if (e.text.unicode == 13 || e.text.unicode == 27)
			{
				std::cout << "INPUT: " << x << std::endl;
				this->isSelected = false;
			}

			return x;
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(tRec);
			target.draw(tText);
		}
	};
	
}
