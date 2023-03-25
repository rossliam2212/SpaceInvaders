//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_MAINMENUSTATE_H
#define SPACE_INVADERS_MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public State {
private:
    sf::RectangleShape backGround;
    sf::Sprite logoSprite;
    std::unordered_map<std::string, std::unique_ptr<Button>> buttons;

    bool startPressed{false};

public:
    MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
                  const std::unordered_map<std::string, int>& supportedKeys, const AssetManager& assetManager,
                  const SoundManager& soundManager) noexcept;
    ~MainMenuState() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void updateButtons();
    void renderButtons(const std::shared_ptr<sf::RenderWindow>& window);

    void initBackground();
    void initSprites();
    void initText();
    void initButtons();
};


#endif //SPACE_INVADERS_MAINMENUSTATE_H
