// Copyright 2025 Danny Nguyen
#include <iostream>
#include "CompositeComponent.hpp"

namespace AP {

CompositeComponent::CompositeComponent(const json& data)
    : Component(data) {
    if (data.contains("children")) {
        for (const auto& child : data["children"]) {
            children_.push_back(Component::fromJson(child));
        }
    }
}

void CompositeComponent::tween(sf::Time time) {
    for (const auto& child : children_) {
        child->tween(time);
    }
    Component::tween(time);
}


void CompositeComponent::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Transform local;
    currFrame().transform(local);
    states.transform *= local;

    for (const auto& child : children_) {
        window.draw(*child, states);
    }
}

float CompositeComponent::maxKeyFrameTime() const {
    float maxTime = 0.0f;
    for (const auto& child : children_) {
        maxTime = std::max(maxTime, child->maxKeyFrameTime());
    }
    for (const auto& kf : keyframes_) {
        maxTime = std::max(maxTime, kf.time());
    }
    return maxTime;
}



}  // namespace AP

