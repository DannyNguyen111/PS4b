// Copyright 2025 Danny Nguyen
#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <SFML/Graphics.hpp>

namespace AP {
class KeyFrame {
 public:
    KeyFrame();
    explicit KeyFrame(const json& ptree);
    float x() const;
    float y() const;
    float theta() const;
    float time() const;

    KeyFrame tween(KeyFrame alt, float t) const;  // For part B
    void transform(sf::Transform& state) const;
 private:
    float t_;
    float x_;
    float y_;
    float scaleX_;
    float scaleY_;
    float theta_;
};
}  // namespace AP
