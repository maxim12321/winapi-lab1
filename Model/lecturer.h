#ifndef MODEL_LECTURER_H_
#define MODEL_LECTURER_H_

#include <memory>

#include "person.h"

class Lecturer : public Person {
 public:
  Lecturer(Point position, double speed, bool is_aggressive);

  void Update(double time) override;
  bool CanBeServed() const override;

  bool IsAggressive() const;

  void Accept(const std::shared_ptr<PersonVisitor>& visitor) override;

 private:
  bool is_aggressive_;
};

#endif  // MODEL_LECTURER_H_
