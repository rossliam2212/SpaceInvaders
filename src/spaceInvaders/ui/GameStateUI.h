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
    static constexpr const float BAR_LENGTH{220.f};
    static constexpr const float BAR_HEIGHT{35.f};
    static constexpr const float UI_Y_POS{50.f};

    Player* player;
    AssetManager assetManager;
    SoundManager soundManager;

    sf::Text scoreText;

    float healthBarValue;
    sf::Sprite heartIcon;
    sf::Sprite healthBar;
    sf::RectangleShape healthBarBackground;

    bool hasShield{false};
    sf::Sprite shieldIcon;
    sf::Sprite shieldBar;
    sf::RectangleShape shieldBarBackground;

public:
    GameStateUI(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void calculateHealthBarValue();
    void calculateShieldBarValue();
    void initText();
    void initSprites();
};


#endif //SPACE_INVADERS_GAMESTATEUI_H
