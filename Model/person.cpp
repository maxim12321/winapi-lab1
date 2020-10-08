#include "person.h"

Person::Person(Point position, double speed)
    : current_position_(position), target_position_(position), speed_(speed) {}

void Person::Update(double time) {
  if (HasReached()) {
    current_position_ = target_position_;
    return;
  }

  double length = (target_position_ - current_position_).Length();

  current_position_ = current_position_
      + (target_position_ - current_position_) / length * time * speed_;
  if (length < time * speed_) {
    current_position_ = target_position_;
  }
}

Point Person::GetPosition() const {
  return current_position_;
}

bool Person::HasReached() const {
  return (target_position_ - current_position_).Length() < kReachDistance;
}

bool Person::IsServed() const {
  return is_served_;
}

bool Person::HasFood() const {
  return has_food_;
}

bool Person::CanBeDestroyed() const {
  return HasFood() && HasReached();
}

void Person::SetTargetPosition(Point position) {
  target_position_ = position;
}

void Person::Serve() {
  is_served_ = true;
}

void Person::GiveFood() {
  has_food_ = true;
}
