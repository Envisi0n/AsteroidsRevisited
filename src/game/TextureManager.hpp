/*
 * TextureManager.hpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Cam
 */

#ifndef TEXTUREMANAGER_HPP_
#define TEXTUREMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
class TextureManager {
public:
	TextureManager();
	virtual ~TextureManager();
	// Loads texture if not already and returns a pointer to it
	virtual sf::Texture* loadTexture(std::string path);
private:
	std::map<std::string,sf::Texture*> textures;
};

#endif /* TEXTUREMANAGER_HPP_ */
