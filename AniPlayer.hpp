// Copyright 2025 Danny Nguyen
#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace AP {
class AniPlayer: public sf::Drawable {
 public:
    explicit AniPlayer(const std::string& filename);

    void tween(sf::Time time);  // For part B
    void togglePause();
    void restart();
    void setTime(float t);
    unsigned int pixelWidth() const;
    unsigned int pixelHeight() const;
 protected:
    void draw(sf::RenderTarget& target,
    sf::RenderStates states) const override;
 private:
    unsigned int width_ = 0;
    unsigned int height_ = 0;
    std::unique_ptr<Component> scene_;
    mutable sf::Clock clock_;
    sf::Time pausedTime_ = sf::Time::Zero;
    bool paused_ = false;
    float maxTime_ = 0.0f;
    sf::Time currentTime_;
};
}  // namespace AP
