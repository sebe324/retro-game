#include "SubMenu.h"


SubMenu::SubMenu(std::string fontPath, std::string texturePath, std::string menu_type) {

	menuType = menu_type;

	if (!font.loadFromFile(fontPath)) {}
	if (!texture.loadFromFile(texturePath)) {}

	if (menuType == "game_over") {

		logo.setString("GAME OVER");
		logo.setCharacterSize(80);
		logo.setFont(font);
		logo.setPosition(500 - (logo.getGlobalBounds().width / 2), 50.f);
		logo.setFillColor(sf::Color::White);
		overlay.setSize({1000.f,1000.f});
		overlay.setFillColor(sf::Color(100,20,20,100));
	}

	if (menuType == "escape_key") {

		bResume = Button("Resume Game", 62, sf::Color::Black, { 250.f, 50.f }, { 500.f,150.f }, sf::Color(92, 64, 51), font);
		bResume.hoverContentColor = sf::Color::White;
		bResume.activeContentColor = sf::Color::White;

		bSettings = Button("Settings", 62, sf::Color::Black, { 250.f, 250.f }, { 500.f,150.f }, sf::Color(92, 64, 51), font);
		bSettings.hoverContentColor = sf::Color::White;
		bSettings.activeContentColor = sf::Color::White;
		overlay.setSize({1000.f,1000.f});
		overlay.setFillColor(sf::Color(100,100,100,100));
	}

	bMainMenu = Button("Main Menu", 62, sf::Color::Black, { 250, 450.f }, { 500.f,150.f }, sf::Color(92, 64, 51), font);
	bMainMenu.hoverContentColor = sf::Color::White;
	bMainMenu.activeContentColor = sf::Color::White;
	bExitGame = Button("Exit", 62, sf::Color::Black, { 250, 650.f }, { 500.f,150.f }, sf::Color(92, 64, 51), font);
	bExitGame.hoverContentColor = sf::Color::White;
	bExitGame.activeContentColor = sf::Color::White;
}

void SubMenu::update(sf::Vector2f pos) {

	if (menuType == "escape_key") {

		bResume.update(pos);
		bSettings.update(pos);
	}

	bExitGame.update(pos);
	bMainMenu.update(pos);
}

void SubMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(overlay);
	if (menuType == "escape_key") {

		target.draw(bSettings);
		target.draw(bResume);
	}

	if (menuType == "game_over")
		target.draw(logo);

	target.draw(bMainMenu);
	target.draw(bExitGame);
}
