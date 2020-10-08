#ifndef MODEL_VISITORS_VISITABLE_H_
#define MODEL_VISITORS_VISITABLE_H_

#include <memory>

#include "person_visitor.h"

class Visitable {
 public:
  virtual void Accept(const std::shared_ptr<PersonVisitor>& visitor) = 0;
};

#endif  // MODEL_VISITORS_VISITABLE_H_
