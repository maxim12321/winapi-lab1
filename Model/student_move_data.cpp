#include "student_move_data.h"

StudentMoveData::StudentMoveData(const Point& cashier_position,
                                 const Point& students_center_position,
                                 double radius)
    : cashier_position_(cashier_position),
      students_center_position_(students_center_position),
      radius_(radius),
      random_device_(),
      generator_(random_device_()),
      angle_generator_(0, 2 * M_PI),
      radius_generator_(0, radius_) {}

Point StudentMoveData::GetRandomInsideCircle() {
  double angle = angle_generator_(generator_);
  double radius = radius_generator_(generator_);
  return {students_center_position_.x + cos(angle) * radius,
          students_center_position_.y + sin(angle) * radius};
}

Point StudentMoveData::GetCashierPosition() const {
  return cashier_position_;
}

bool StudentMoveData::IsInsideCircle(const Point& position) const {
  return (position - students_center_position_).Length() < radius_;
}

void StudentMoveData::SetCenterPosition(const Point& point) {
  students_center_position_ = point;
}
