//
// Created by Liam Ross on 27/03/2023.
//

#include "Weapon.h"

Weapon::Weapon(float shootCoolDown, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : shootCoolDown{shootCoolDown},
      isShooting{false},
      shootCoolDownTimer{false},
      assetManager{assetManager},
      soundManager{soundManager} {
}

float Weapon::getShootCoolDown() const {
    return shootCoolDown;
}

bool Weapon::getIsShooting() const {
    return isShooting;
}

void Weapon::setIsShooting(bool shooting) {
    isShooting = shooting;
}

bool Weapon::getShootCoolDownTimer() const {
    return shootCoolDownTimer;
}

void Weapon::setShootCoolDownTimer(bool timer) {
    shootCoolDownTimer = timer;
}