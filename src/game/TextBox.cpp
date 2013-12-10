/*
 * TextBox.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Dave
 */

#include "TextBox.hpp"
#include <iostream>

TextBox::TextBox(float x, float y, sf::Font* font, float pWidth) {
	setPosition(x, y);
	setSize(pWidth);
	setHasFocus(false);

	// Set Text field
	Text.setPosition(x + 3, y + 2);
	Text.setCharacterSize(14);

	Text.setFont(*font);
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

void TextBox::update(sf::Vector2f mouseLoc, sf::Event event) {

	sf::String tmp;

	// User click on the text box
	if (rectangle.getGlobalBounds().contains(mouseLoc)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus(true);

		}
	}
	// User clicked elsewhere 
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			setHasFocus(false);

		}
	}

	// This textbox is in focus
	if (getHasFocus()) {

		// User typed text
		if (event.type == sf::Event::TextEntered) {

			// Limit the number of times a character repeats
			if ((prevEvent == event.text.unicode && 
					reset.getElapsedTime().asMilliseconds() > TYPE_DELAY) ||
					 prevEvent != event.text.unicode) {

				// Handle backspace
				if (event.text.unicode == 8) {

					// Get current text
					tmp = Text.getString();

					// If not blank erase one character then update
					if (tmp != "") {
						tmp.erase(tmp.getSize() - 1, 1);
						Text.setString(tmp);
					}

					// Restart repeat timeout
					reset.restart();

				} 
				// Valid character
				else if (event.text.unicode > 0x21
						&& event.text.unicode < 0x7e) {

					// Get current text
					tmp = Text.getString();
					// Append character
					tmp = tmp + (event.text.unicode);
					// Update text fields
					Text.setString(tmp);

					// Reset repeat timeout
					reset.restart();

				} 
				// Invalid character
				else {
					
				}
			}

			// Remember last character
			prevEvent = event.text.unicode;
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

std::string TextBox::toString() {

	return Text.getString();

}
