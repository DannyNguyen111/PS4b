// Copyright 2025 Danny Nguyen
#include "NullComponent.hpp"

namespace AP {

NullComponent::NullComponent(const json& data)
    : Component(data) {
    // Does nothing
}

void NullComponent::tween(sf::Time) {
    // No-op
}

void NullComponent::draw(sf::RenderTarget&, sf::RenderStates) const {
    // No-op
}

}  // namespace AP

