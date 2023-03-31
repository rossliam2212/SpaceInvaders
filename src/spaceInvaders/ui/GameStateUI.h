//
// Created by Liam Ross on 30/03/2023.
//

#ifndef SPACE_INVADERS_GAMESTATEUI_H
#define SPACE_INVADERS_GAMESTATEUI_H

#include "../characters/Player.h"
#include "../managers/AssetManager.h"
#include "../managers/SoundManager.h"

class GameStateUI {
private:
    Player* player;
    AssetManager assetManager;
    SoundManager soundManager;

    sf::Text scoreText;
    sf::Text healthText;

public:
    GameStateUI(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void initText();
};


#endif //SPACE_INVADERS_GAMESTATEUI_H
