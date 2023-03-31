//
// Created by Liam Ross on 30/03/2023.
//

#include "GameStateUI.h"

GameStateUI::GameStateUI(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      assetManager{assetManager},
      soundManager{soundManager} {
    initText();
}

void GameStateUI::update(const float& dt) {
    scoreText.setString("Score: " + std::to_string(player->getScore()));
}

void GameStateUI::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(scoreText);
}

void GameStateUI::initText() {
    scoreText.setCharacterSize(50);
    scoreText.setPosition(sf::Vector2f{100, 50});
    scoreText.setFont(assetManager.getFont("PixelFont"));
    scoreText.setFillColor(assetManager.getColor("white"));
}