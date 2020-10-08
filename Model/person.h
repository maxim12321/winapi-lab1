#ifndef MODEL_PERSON_H_
#define MODEL_PERSON_H_

#include <cmath>
#include <memory>

#include "Utils/point.h"
#include "Visitors/visitable.h"

class Person : public Visitable {
 public:
  Person(Point position, double speed);

  virtual void Update(double time);
  virtual bool CanBeServed() const = 0;

  Point GetPosition() const;
  bool HasReached() const;
  bool IsServed() const;
  bool HasFood() const;
  bool CanBeDestroyed() const;

  void SetTargetPosition(Point position);
  void Serve();
  void GiveFood();

  void Accept(const std::shared_ptr<PersonVisitor>& visitor) override = 0;

 protected:
  Point current_position_;
  Point target_position_;

 private:
  double speed_;
  bool is_served_ = false;
  bool has_food_ = false;

 private:
  const double kReachDistance = 1;
};

#endif  // MODEL_PERSON_H_
