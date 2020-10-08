#ifndef MODEL_STUDENT_H_
#define MODEL_STUDENT_H_

#include <memory>
#include <utility>

#include "person.h"
#include "student_move_data.h"

class Student : public Person {
 public:
  Student(Point position, double speed,
          std::shared_ptr<StudentMoveData> move_data);

  void Update(double time) override;
  bool CanBeServed() const override;

  double DistanceToCashier() const;

  void Accept(const std::shared_ptr<PersonVisitor>& visitor) override;

 private:
  std::shared_ptr<StudentMoveData> move_data_;
};

#endif  // MODEL_STUDENT_H_
