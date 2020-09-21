#ifndef MODEL_CONTAINERS_PERSON_CONTAINER_H_
#define MODEL_CONTAINERS_PERSON_CONTAINER_H_

#include <memory>

#include "../person.h"

class PersonContainer {
 public:
  virtual void AddPerson(const std::shared_ptr<Person>& person) = 0;
  virtual void RemovePerson(Person* person) = 0;

  bool Empty() const;
  int Size() const;

 protected:
  int size_ = 0;
};

#endif  // MODEL_CONTAINERS_PERSON_CONTAINER_H_
