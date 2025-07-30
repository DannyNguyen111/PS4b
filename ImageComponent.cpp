// Copyright 2025 Danny Nguyen
#include <stdexcept>
#include <iostream>
#include "ImageComponent.hpp"

namespace AP {

ImageComponent::ImageComponent(const json& data) : Component(data) {
    std::string path = data.value("file", "");
    if (path.empty()) {
        throw std::runtime_error("Missing image file path in JSON.");
    }

    if (!texture_.loadFromFile(path)) {
        throw std::runtime_error("Could not load image: " + path);
    }

    sprite_.setTexture(texture_);
    sprite_.setOrigin(texture_.getSize().x / 2.f, texture_.getSize().y / 2.f);
}


void ImageComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!validFrame_ || keyframes_.empty()) return;

    sf::Transform local;
    currFrame_.transform(local);
    states.transform *= local;

    sf::Sprite sprite = sprite_;
    sprite.setColor(color_);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    target.draw(sprite, states);
}

float ImageComponent::maxKeyFrameTime() const {
    float maxTime = 0.0f;
    for (const auto& kf : keyframes_) {
        if (kf.time() > maxTime) maxTime = kf.time();
    }
    return maxTime;
}


}  // namespace AP

