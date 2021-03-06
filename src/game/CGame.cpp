/*
 * CGame.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Cam
 */

#include "CGame.hpp"
#include <iostream>
#include <string.h>
#include "MD5.h"
#include <SFML/Network.hpp>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

CGame::CGame() {
	setState(INIT);
}

CGame::~CGame() {
	config.saveConfig();
}

void CGame::init() {

	// Load game config
	config.loadConfig();

	// Init the background.
	background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setTexture(ResourceHandler.loadTexture("images/background.png"));

	// Init the Main Menu
	gameMenu.addButton(50, 0, ResourceHandler.loadTexture("images/title.gif"),
			BUT_NOTHING);
	gameMenu.addButton(283.5, 100,
			ResourceHandler.loadTexture("images/sub2.gif"), BUT_NOTHING);
	gameMenu.addButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			ResourceHandler.loadTexture("images/test.png"), BUT_PLAY);
	gameMenu.addButton(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50,
			ResourceHandler.loadTexture("images/quit.png"), BUT_QUIT);

	// Init login menu
	loginMenu.addButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			ResourceHandler.loadTexture("images/login.png"), BUT_LOGIN);
	loginMenu.addButton(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2,
			ResourceHandler.loadTexture("images/register.png"), BUT_REGISTER);
	loginMenu.addTextBox(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 60,
			ResourceHandler.loadFont("fonts/TitilliumWeb-Regular.ttf"), 150);
	loginMenu.addTextBox(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 30,
			ResourceHandler.loadFont("fonts/TitilliumWeb-Regular.ttf"), 150);
	loginMenu.addButton(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50,
			ResourceHandler.loadTexture("images/quit.png"), BUT_QUIT);
	// Init networking
	setupConnection();

	setState(MENU);

}

void CGame::run() {

	// Init window
	SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;
	SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
	// Set window fullscreen
	if (config.isFullScreen()) {
		window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",
				sf::Style::Fullscreen);
	} else {
		window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids",
				sf::Style::Close);
	}
	window.setIcon(96, 96,
			ResourceHandler.loadImage("images/icon.png")->getPixelsPtr());
	// This will regulate the draw rate and the amount of the time the thread sleeps
	window.setFramerateLimit(FRAMES_PER_SECOND);
	gameView.setSize(800, 600);
	gameView.setCenter(400, 300);
	window.setView(gameView);

	// Game speed control
	int loops;
	sf::Clock gameClock;
	float nextTick = gameClock.getElapsedTime().asMilliseconds();
	float sendAc = 0;
	float sendRate = 30;
	sf::Clock delta;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		switch (getState()) {
		case INIT:
			// Error message here.
			break;
		case MENU:

			// Draw the background.
			window.clear();
			window.draw(background);
			// Draw menu buttons.
			handleButton(
					gameMenu.update(
							window.mapPixelToCoords(
									sf::Mouse::getPosition(window)), event));

			gameMenu.draw(&window);
			break;

		case LOGIN:
			window.clear();
			window.draw(background);
			handleButton(
					loginMenu.update(
							window.mapPixelToCoords(
									sf::Mouse::getPosition(window)), event));

			loginMenu.draw(&window);
			break;

		case PLAYING:
			loops = 0;
			while (gameClock.getElapsedTime().asMilliseconds() > nextTick
					&& loops < MAX_FRAMESKIP) {
				receiveServerUpdate();
				sendUserInput();
				//sendHeartbeat();
				gameClient.update(1.0f/TICKS_PER_SECOND);
				//gameClient.printStats();
				nextTick += SKIP_TICKS;
				loops++;
			}
			window.clear();
			window.draw(background);
			gameWorld.draw(&window,
					((gameClock.getElapsedTime().asMilliseconds() + SKIP_TICKS
							- nextTick) / ( SKIP_TICKS)));
			break;
		case PAUSE:
			break;
		case QUIT:
			return;
			break;
		default:
			// Error message here.
			break;
		}

		window.display();

	}

}

void CGame::receiveServerUpdate() {

	sf::Packet serverPacket;
	short packetType;

	while (gameClient.receive(&serverPacket) != 0) {

		serverPacket >> packetType;

		switch (packetType) {

		case SERVER_UPDATE:
			gameWorld.packetToWorld(serverPacket);
			break;
		case HEARTBEAT:
			sendHeartbeat();
			break;
		case DISCONNECT:
			setState(LOGIN);
			break;
		}
	}
}

void CGame::sendHeartbeat() {

	sf::Packet packet;
	genericPacket heartbeat;

	heartbeat.packetType = HEARTBEAT;
	packet << heartbeat;
	gameClient.send(packet);

}

void CGame::handlePacket(sf::Packet packet) {
}

void CGame::update() {

}

int CGame::getState() const {
	return state;
}

void CGame::showMenu() {
}

void CGame::setState(int state) {
	this->state = state;
}

void CGame::handleButton(int action) {

	switch (action) {

	case BUT_PLAY:
		setState(LOGIN);
		break;
	case BUT_LOGIN:
		login();
		break;
	case BUT_REGISTER:
		gameRegister();
		break;
	case BUT_QUIT:
		setState(QUIT);
		break;

	}

	sf::RectangleShape test;
}

void CGame::login() {

	sf::Packet packet;
	loginPacket info;
	std::string tmp;
	short packetType;
	sf::Clock retry;

	std::cout << "Sending login..." << std::endl;

	// Setup login packet
	info.packetType = GAMELOGIN;
	strcpy(info.username, loginMenu.getTextBoxes().at(0)->toString().c_str());
	tmp = loginMenu.getTextBoxes().at(1)->toString() + "coolsalt";
	strcpy(info.password, md5(tmp).c_str());
	packet << info;

	// Init connection
	setupConnection();

	// Send login packet to server
	if (!gameClient.send(packet)) {
		std::cout << "failed to login" << std::endl;
		setState(QUIT);
	}

	// Wait from response
	packet.clear();
	std::cout << "Waiting for server response...";
	retry.restart();
	while (gameClient.receive(&packet) == 0) {

		if (retry.getElapsedTime().asSeconds() > 3) {
			std::cout << "timed out" << std::endl;
			gameClient.Reset();
			return;
		}

	}

	packet >> packetType;

	switch (packetType) {

	case LOGIN_AUTH_VALID:
		std::cout << "Logged in!" << std::endl;
		setState(PLAYING);
		return;
		break;
	case LOGIN_AUTH_UNKNOWN_USER:
		std::cout << "Invalid user!" << std::endl;
		setState(LOGIN);
		return;
		break;
	case LOGIN_AUTH_INVALID_PASSWORD:
		std::cout << "Unknown password!" << std::endl;
		setState(LOGIN);
		return;
		break;
	default:
		std::cout << "Unexpected response: " << packetType << std::endl;
		setState(LOGIN);
		gameClient.Reset();
		return;
		break;
	}

	setState(LOGIN);

}

void CGame::draw(sf::RenderWindow* window) {
}

void CGame::sendUserInput() {

	sf::Packet clientUpdate;
	short packetType;
	int input;

	packetType = CLIENT_UPDATE;
	clientUpdate << packetType;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		input = THRUSTUP;
		clientUpdate << input;

		gameClient.send(clientUpdate);
		return;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		input = THRUSTDOWN;
		clientUpdate << input;

		gameClient.send(clientUpdate);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		input = TURNLEFT;
		clientUpdate << input;

		gameClient.send(clientUpdate);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		input = TURNRIGHT;
		clientUpdate << input;

		gameClient.send(clientUpdate);
		return;
	}
	sendHeartbeat();
}

void CGame::setupConnection() {

	gameClient.Connect(config.getServerIp());
}

void CGame::gameRegister() {

	sf::Packet packet;
	loginPacket info;
	std::string tmp;
	short packetType;
	sf::Clock retry;

	std::cout << "Sending register..." << std::endl;

	// Setup connection
	setupConnection();

	// Setup login packet
	info.packetType = GAMEREGISTER;
	strcpy(info.username, loginMenu.getTextBoxes().at(0)->toString().c_str());
	tmp = loginMenu.getTextBoxes().at(1)->toString() + "coolsalt";
	strcpy(info.password, md5(tmp).c_str());
	packet << info;

	// Send login packet to server
	if (!gameClient.send(packet)) {
		std::cout << "failed to login" << std::endl;
		setState(QUIT);
	}

	// Wait from response
	packet.clear();
	std::cout << "Waiting for server response...";
	retry.restart();
	while (gameClient.receive(&packet) == 0) {

		if (retry.getElapsedTime().asSeconds() > 3) {
			gameClient.Reset();

			return;
		}
	}

	packet >> packetType;

	switch (packetType) {

	case LOGIN_REG_SUCCESS:
		std::cout << "Registered & Logged in!" << std::endl;
		setState(PLAYING);
		return;
		break;
	case LOGIN_REG_INUSE:
		std::cout << "User already in use!" << std::endl;
		setState(LOGIN);
		return;
		break;
	default:
		std::cout << "Unexpected response: " << packetType << std::endl;
		setState(LOGIN);
		gameClient.Reset();
		return;
		break;
	}

	setState(LOGIN);

}
