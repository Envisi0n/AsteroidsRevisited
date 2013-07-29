/*
 * TextBox.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Dave
 */

#include "TextBox.hpp"

TextBox::TextBox(float x, float y, float pWidth) {
	setPosition(x, y);
	setSize(pWidth);
	setHasFocus(false);

	// Set Text field
	Text.setPosition(x + 3, y + 2);
	Text.setCharacterSize(14);

	// Load font
	if (!font.loadFromFile("fonts/TitilliumWeb-Regular.ttf")) {
		// error
	}
	Text.setFont(font);
	Text.setColor(sf::Color::Black);
	Text.setStyle(sf::Text::Regular);

}

TextBox::~TextBox() {
	// TODO Auto-generated destructor stub
}

void TextBox::draw(sf::RenderWindow* window) {
	window->draw(rectangle);
	window->draw(Text);
	return;
}

void TextBox::setPosition(float x, float y) {

	this->rectangle.setPosition(x, y);
}

void TextBox::setSize(float pWidth) {

	this->rectangle.setSize(sf::Vector2f(pWidth, 20));
}

void TextBox::update(sf::Vector2i mouseLoc, sf::Event event) {

	sf::Vector2f tmp;
	tmp.x = mouseLoc.x;
	tmp.y = mouseLoc.y;

	bool Focus = getHasFocus();
	sf::String myString;

	if (rectangle.getGlobalBounds().contains(tmp)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus(true);

		}
	} else {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus(false);

		}
	}

	if (Focus) {

		if (event.type == sf::Event::TextEntered && !flag) {

			//backspace
			if (event.text.unicode == 8) {

				myString = Text.getString();
				myString.erase(myString.getSize() - 1, 1);
				Text.setString(myString);
				flag = true;
			} else {

				myString = Text.getString();
				myString = myString + (event.text.unicode);
				Text.setString(myString);
				flag = true;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			flag = false;
		}
	}
}

bool TextBox::getHasFocus() const {
	return hasFocus;
}

void TextBox::setHasFocus(bool hasFocus) {
	this->hasFocus = hasFocus;
}

const sf::Text& TextBox::getText() const {
	return Text;
}

void TextBox::setText(const sf::Text& text) {
	Text = text;
}
