// Copyright 2025 Danny Nguyen
#include <iostream>
#include "RectangleComponent.hpp"

namespace AP {

RectangleComponent::RectangleComponent(const json& data): Component(data),
width_(data.value("width", 0.0f)),
height_(data.value("height", 0.0f)),
size_(width_, height_) {}
void RectangleComponent::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (!hasKeyframes()) return;
    KeyFrame frame = currFrame();
    sf::Transform local;
    frame.transform(local);
    states.transform *= local;

    sf::RectangleShape rect(sf::Vector2f(width_, height_));
    rect.setFillColor(color_);
    rect.setPosition(x_, y_);

    window.draw(rect, states);
}


float RectangleComponent::maxKeyFrameTime() const {
    float maxTime = 0.0f;
    for (const auto& kf : keyframes_) {
        if (kf.time() > maxTime) maxTime = kf.time();
    }
    return maxTime;
}
}  // namespace AP
