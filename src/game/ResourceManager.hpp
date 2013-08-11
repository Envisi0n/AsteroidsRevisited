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

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();
	// Loads texture if not already and returns a pointer to it
	static sf::Texture* loadTexture(std::string path);
	// Loads font if not already and returns a pointer to it
	static sf::Font* loadFont(std::string path);
	// Loads image if not already and returns a pointer to it
	static sf::Image* loadImage(std::string path);
private:
	static std::map<std::string,sf::Texture*> textures;
	static std::map<std::string,sf::Font*> fonts;
	static std::map<std::string,sf::Image*> images;
};

#endif /* TEXTUREMANAGER_HPP_ */
