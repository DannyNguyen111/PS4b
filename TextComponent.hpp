// Copyright 2025 Danny Nguyen
#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace AP {

class TextComponent : public Component {
 public:
    explicit TextComponent(const json& data);
    float maxKeyFrameTime() const override;

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    sf::Font font_;
    sf::Text text_;
};

}  // namespace AP

