// Copyright 2025 Danny Nguyen
#include <stdexcept>
#include "TextComponent.hpp"
namespace AP {

TextComponent::TextComponent(const json& data)
    : Component(data) {
    std::string fontPath = data.at("font").get<std::string>();
    if (!font_.loadFromFile(fontPath)) {
        throw std::runtime_error("Could not load font: " + fontPath);
    }

    text_.setFont(font_);
    text_.setString(data.value("text", ""));
    text_.setCharacterSize(30);
    text_.setFillColor(color());
}
void TextComponent::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (!hasKeyframes()) return;
    KeyFrame frame = currFrame();
    sf::Transform local;
    frame.transform(local);
    states.transform *= local;
    sf::Text temp = text_;
    temp.setFillColor(color());
    window.draw(text_, states);
}

float TextComponent::maxKeyFrameTime() const {
    float maxTime = 0.0f;
    for (const auto& kf : keyframes_) {
        if (kf.time() > maxTime) maxTime = kf.time();
    }
    return maxTime;
}

}  // namespace AP

