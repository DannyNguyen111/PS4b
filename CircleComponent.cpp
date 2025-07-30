// Copyright 2025 Danny Nguyen
#include "CircleComponent.hpp"
#include <iostream>

namespace AP {

CircleComponent::CircleComponent(const json& data)
    : Component(data), radius_(data.value("radius", 10.0f)) {}

void CircleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!validFrame_ || keyframes_.empty()) return;

    sf::Transform local;
    currFrame().transform(local);
    states.transform *= local;

    sf::CircleShape circle(radius_);
    circle.setOrigin(radius_, radius_);
    circle.setFillColor(color_);

    target.draw(circle, states);
}


float CircleComponent::maxKeyFrameTime() const {
    float maxTime = 0.0f;
    for (const auto& kf : keyframes_) {
        if (kf.time() > maxTime) maxTime = kf.time();
    }
    return maxTime;
}

}  // namespace AP

