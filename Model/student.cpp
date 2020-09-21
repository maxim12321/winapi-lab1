#include "student.h"

Student::Student(Point position, double speed,
                 std::shared_ptr<StudentMoveData> move_data)
    : Person(position, speed), move_data_(std::move(move_data)) {}

void Student::Update(double time) {
  if (!IsServed()
      && (!move_data_->IsInsideCircle(target_position_) || HasReached())) {
    SetTargetPosition(move_data_->GetRandomInsideCircle());
  }

  Person::Update(time);
}

bool Student::CanBeServed() const {
  return !IsServed() && move_data_->IsInsideCircle(current_position_);
}

double Student::DistanceToCashier() const {
  return (current_position_ - move_data_->GetCashierPosition()).Length();
}

void Student::Accept(const std::shared_ptr<PersonVisitor>& visitor) {
  visitor->VisitStudent(this);
}
