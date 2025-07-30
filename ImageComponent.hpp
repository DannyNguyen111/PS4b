// Copyright 2025 Danny Nguyen
#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace AP {

class ImageComponent : public Component {
 public:
    explicit ImageComponent(const json& data);
    float maxKeyFrameTime() const override;
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    sf::Texture texture_;
    sf::Sprite sprite_;
};

}  // namespace AP

