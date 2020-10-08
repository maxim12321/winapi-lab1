#ifndef MODEL_STUDENT_MOVE_DATA_H_
#define MODEL_STUDENT_MOVE_DATA_H_

#include <random>

#include "Utils/point.h"

class StudentMoveData {
 public:
  StudentMoveData(const Point& cashier_position,
                  const Point& students_center_position,
                  double radius);

  Point GetRandomInsideCircle();
  Point GetCashierPosition() const;

  bool IsInsideCircle(const Point& position) const;

  void SetCenterPosition(const Point& point);

 private:
  Point cashier_position_;
  Point students_center_position_;
  double radius_;

  std::random_device random_device_;
  std::mt19937 generator_;
  std::uniform_real_distribution<double> angle_generator_;
  std::uniform_real_distribution<double> radius_generator_;
};

#endif  // MODEL_STUDENT_MOVE_DATA_H_
