#include "lecturer.h"

Lecturer::Lecturer(Point position, double speed, bool is_aggressive)
    : Person(position, speed), is_aggressive_(is_aggressive) {}

void Lecturer::Update(double time) {
  Person::Update(time);
}

bool Lecturer::CanBeServed() const {
  return !IsServed() && HasReached();
}

bool Lecturer::IsAggressive() const {
  return is_aggressive_;
}

void Lecturer::Accept(const std::shared_ptr<PersonVisitor>& visitor) {
  visitor->VisitLecturer(this);
}
