// Copyright 2025 Danny Nguyen
#include "KeyFrame.hpp"

namespace AP {

KeyFrame::KeyFrame() : t_(0), x_(0), y_(0), scaleX_(1), scaleY_(1), theta_(0) {}

KeyFrame::KeyFrame(const json& data):t_(data.at("t").get<float>()),
x_(data.value("x", 0.0f)), y_(data.value("y", 0.0f)),
 scaleX_(data.value("scale-x", 1.0f)), scaleY_(data.value("scale-y", 1.0f)),
theta_(data.value("theta", 0.0f)) {}
float KeyFrame::time() const {
    return t_;
}
float AP::KeyFrame::x() const {
  return x_;
}
float AP::KeyFrame::y() const {
  return y_;
}
float AP::KeyFrame::theta() const {
  return theta_;
}
void KeyFrame::transform(sf::Transform& state) const {
    state.translate(x_, y_);
    state.rotate(theta_);
    state.scale(scaleX_, scaleY_);
}


KeyFrame KeyFrame::tween(KeyFrame other, float t) const {
    KeyFrame result;
    result.x_      = x_   + (other.x_      - x_)   * t;
    result.y_      = y_   + (other.y_      - y_)   * t;
    result.scaleX_ = scaleX_ + (other.scaleX_ - scaleX_) * t;
    result.scaleY_ = scaleY_ + (other.scaleY_ - scaleY_) * t;
    result.theta_  = theta_  + (other.theta_  - theta_)  * t;
    return result;
}

}  // namespace AP

