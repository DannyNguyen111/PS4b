// Copyright 2025 Danny Nguyen

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "AniPlayer.hpp"
using json = nlohmann::json;

namespace AP {

AniPlayer::AniPlayer(const std::string& filename) {
    std::ifstream ifs(filename);
    json data;
    ifs >> data;

    width_ = data["width"];
    height_ = data["height"];

    if (data.contains("scene")) {
        scene_ = Component::fromJson(data["scene"]);
        if (!scene_) {
            std::cerr << "Failed to create scene component\n";
        } else {
            std::cout << "Scene successfully loaded.\n";
            maxTime_ = scene_->maxKeyFrameTime();
        }
    } else {
        std::cerr << "JSON missing 'scene' key\n";
    }
    clock_.restart();
    currentTime_ = sf::Time::Zero;
}

void AniPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (scene_) {
        target.draw(*scene_, states);
    }
}

unsigned int AniPlayer::pixelWidth() const {
    return width_;
}

unsigned int AniPlayer::pixelHeight() const {
    return height_;
}
void AniPlayer::togglePause() {
    if (paused_) {
        clock_.restart();
        paused_ = false;
    } else {
        pausedTime_ = clock_.getElapsedTime();
        paused_ = true;
    }
}
void AniPlayer::tween(sf::Time time) {
    if (!paused_ && scene_) {
        currentTime_ = time;
        scene_->tween(time);
    }
}

void AniPlayer::restart() {
    clock_.restart();
    paused_ = false;
}
void AniPlayer::setTime(float t) {
    currentTime_ = sf::seconds(t);
    if (scene_) {
        scene_->tween(currentTime_);
    }
}
}  // namespace AP

