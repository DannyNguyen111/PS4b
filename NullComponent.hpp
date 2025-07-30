// Copyright 2025 Danny Nguyen
#pragma once

#include "Component.hpp"

namespace AP {

class NullComponent : public Component {
 public:
    explicit NullComponent(const json& data);
    void tween(sf::Time time) override;
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}  // namespace AP

