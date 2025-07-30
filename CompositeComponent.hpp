// Copyright 2025 Danny Nguyen
#pragma once

#include "Component.hpp"

namespace AP {

class CompositeComponent : public Component {
 public:
    explicit CompositeComponent(const json& data);
    float maxKeyFrameTime() const override;
    void tween(sf::Time time) override;

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    std::vector<std::unique_ptr<Component>> children_;
};

}  // namespace AP

