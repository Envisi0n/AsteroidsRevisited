/*
 * TextureManager.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Cam
 */

#include "TextureManager.hpp"
#include <iostream>

TextureManager::TextureManager() {
	// TODO Auto-generated constructor stub

}

TextureManager::~TextureManager() {
	// Delete all the textures
	for (std::map<std::string,sf::Texture*>::iterator it = textures.begin(); it != textures.end();
			++it) {

		delete (*it).second;

	}
}

sf::Texture* TextureManager::loadTexture(std::string path) {

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
