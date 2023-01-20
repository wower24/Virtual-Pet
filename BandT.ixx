#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

export module All_Modules:BandT;

export
{
	class Button
	{
	private:
		sf::RectangleShape button;
		sf::Text bText;

		int bWidth;
		int bHeight;

	public:
		Button(std::string text, sf::Vector2f bSize, int charSize, sf::Color bgColor, sf::Color textColor)
		{
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
				//if true change the text color
				return true;
			}
			return false;
		}


	};

	class Textbox
	{
	private:
		sf::Text textbox;

		std::ostringstream text;
		bool isSelected = false;
		bool hasLimit = true;
		int limit = 15;

		void deleteLastChar()
		{
			std::string oldText = text.str();
			std::string newText = "";
			//copy old text to a new one without the last character
			for (int i = 0; i < (oldText.length() - 1); i++)
				newText = oldText[i];

			text.str("");
			text << newText;
			textbox.setString(text.str() + ("_"));
		}

		//pass char to text string as long as it is not delete, escape or enter
		void inputLogic(int t)
		{
			if (t != DELETE_KEY && t != ENTER_KEY && t != ESCAPE_KEY)
				text << char(t);
			else if (t == DELETE_KEY)
			{
				if (text.str().length() > 0)
					deleteLastChar();
			}

			textbox.setString(text.str() + "_");
		}

	public:
		Textbox()
		{
			std::cout << "This is a default textbox constructor. It shouldn't be used if everything is allright." << std::endl;
		}

		//This constructior will be used, but maybe with a constant size (different colors for player name and dog name)
		Textbox(int size, sf::Color color, bool s)
		{
			textbox.setCharacterSize(size);
			textbox.setFillColor(color);
			isSelected = s;

			//if the textbox is selected - display a _, if not - display nothing
			if (isSelected)
				textbox.setString("_");
			else
				textbox.setString("");
		}

		void setFont(sf::Font& font)
		{
			textbox.setFont(font);
		}

		void setPosition(sf::Vector2f pos)
		{
			textbox.setPosition(pos);
		}

		void setSelected(bool s)
		{
			isSelected = s;

			if (!s)
			{
				std::string oldText = text.str();
				std::string newText = "";

				for (int i = 0; i < oldText.length(); i++)
					newText += oldText[i];

				textbox.setString(newText);
			}
		}

		std::string getText()
		{
			return text.str();
		}

		void drawTo(sf::RenderWindow& window)
		{
			window.draw(textbox);
		}

		void type(sf::Event input)
		{
			if (isSelected)
			{
				int typedIn = input.text.unicode;

				//allow only "regular" characters
				if (typedIn < 128)
				{
					//if there's still space in the textbox - pass the typed in character to logic function
					if ((text.str().length()) <= limit)
						inputLogic(typedIn);
					else
						deleteLastChar();
				}
			}
		}
	};
}
