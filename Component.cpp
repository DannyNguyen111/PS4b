// Copyright 2025 Danny Nguyen
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "NullComponent.hpp"
#include "RectangleComponent.hpp"
#include "CircleComponent.hpp"
#include "CompositeComponent.hpp"
#include "ImageComponent.hpp"
#include "TextComponent.hpp"

namespace AP {

Component::Component(const json& data) {
    std::string hex;
if (data.contains("color")) {
    hex = data["color"];
} else if (data.contains("keyframes") && data["keyframes"].size() > 0 &&
data["keyframes"][0].contains("color")) {
    hex = data["keyframes"][0]["color"];
} else {
    hex = "FFFFFFFF";
}

    if (hex.length() == 6) hex += "FF";
    unsigned int r = std::stoul(hex.substr(0, 2), nullptr, 16);
    unsigned int g = std::stoul(hex.substr(2, 2), nullptr, 16);
    unsigned int b = std::stoul(hex.substr(4, 2), nullptr, 16);
    unsigned int a = std::stoul(hex.substr(6, 2), nullptr, 16);
    std::cout << "Parsed color: " << hex << "\n";
    std::cout << "RGBA = (" << r << "," << g << "," << b << "," << a << ")\n";
    color_ = sf::Color(r, g, b, a);

    if (data.contains("keyframes")) {
        for (const auto& kf : data["keyframes"]) {
            std::cout << "Added keyframe t=" << kf["t"] << "\n";
            keyframes_.emplace_back(kf);
        }
    }
}

sf::Color Component::color() const {
    return color_;
}

void Component::tween(sf::Time time) {
    float t = time.asSeconds();

    if (keyframes_.empty()) {
        currFrame_ = KeyFrame();
        validFrame_ = false;
        return;
    }

    if (keyframes_.size() == 1 || t <= keyframes_.front().time()) {
        currFrame_ = keyframes_.front();
        validFrame_ = true;
        return;
    }
    if (t >= keyframes_.back().time()) {
        currFrame_ = keyframes_.back();
        validFrame_ = true;
        return;
    }

    // Interpolate between frames
    for (size_t i = 0; i < keyframes_.size() - 1; ++i) {
        const KeyFrame& k1 = keyframes_[i];
        const KeyFrame& k2 = keyframes_[i + 1];

        if (t >= k1.time() && t < k2.time()) {
            float duration = k2.time() - k1.time();
            float elapsed = t - k1.time();
            float percent = duration > 0 ? elapsed / duration : 0.f;
            currFrame_ = k1.tween(k2, percent);
            validFrame_ = true;
            return;
        }
    }

    validFrame_ = false;
}



KeyFrame Component::currFrame() const {
    return currFrame_;
}


std::unique_ptr<Component> Component::fromJson(const json& data) {
    std::string type = data.value("shape", "");
    std::cout << "Creating component of shape: " << type << "\n";
    if (type == "circle") return std::make_unique<CircleComponent>(data);
    if (type == "rectangle" || type == "rect") return std::make_unique<RectangleComponent>(data);
    if (type == "composite") return std::make_unique<CompositeComponent>(data);
    if (type == "image") return std::make_unique<ImageComponent>(data);
    if (type == "text") return std::make_unique<TextComponent>(data);

    throw std::runtime_error("Unknown component shape: " + type);
}

bool Component::hasKeyframes() const {
    return !keyframes_.empty();
}


}  // namespace AP

