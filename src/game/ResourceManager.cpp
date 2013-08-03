/*
 * TextureManager.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Cam
 */

#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager() {
	// TODO Auto-generated constructor stub

}

ResourceManager::~ResourceManager() {
	// Delete all the textures
	for (std::map<std::string, sf::Texture*>::iterator it = textures.begin();
			it != textures.end(); ++it) {

		delete (*it).second;

	}
	// Delete all the fonts
	for (std::map<std::string, sf::Font*>::iterator it = fonts.begin();
			it != fonts.end(); ++it) {

		delete (*it).second;

	}
	// Delete all the images
	for (std::map<std::string, sf::Image*>::iterator it = images.begin();
			it != images.end(); ++it) {

		delete (*it).second;

	}

}

sf::Texture* ResourceManager::loadTexture(std::string path) {

	sf::Texture *tmp;

	// Not loaded
	if (textures[path] == NULL) {

		tmp = new sf::Texture();

		if (!tmp->loadFromFile(path)) {
			return NULL;
		}

		std::cout << "Loading texture: " << path << std::endl;

		textures[path] = tmp;
		return tmp;
	}

	// Already loaded
	return textures[path];
}

sf::Font* ResourceManager::loadFont(std::string path) {

	sf::Font *tmp;

	// Not loaded
	if (fonts[path] == NULL) {

		tmp = new sf::Font();

		if (!tmp->loadFromFile(path)) {
			return NULL;
		}

		std::cout << "Loading font: " << path << std::endl;

		fonts[path] = tmp;
		return tmp;
	}

	// Already loaded
	return fonts[path];

}

sf::Image* ResourceManager::loadImage(std::string path) {

	sf::Image *tmp;

	// Not loaded
	if (images[path] == NULL) {

		tmp = new sf::Image();

		if (!tmp->loadFromFile(path)) {
			return NULL;
		}

		std::cout << "Loading image: " << path << std::endl;

		images[path] = tmp;
		return tmp;
	}

	// Already loaded
	return images[path];

}
