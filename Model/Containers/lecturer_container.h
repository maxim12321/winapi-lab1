#ifndef MODEL_CONTAINERS_LECTURER_CONTAINER_H_
#define MODEL_CONTAINERS_LECTURER_CONTAINER_H_

#include <algorithm>
#include <memory>
#include <vector>

#include "person_container.h"
#include "../lecturer.h"

class LecturerIterator;

class LecturerContainer : public PersonContainer {
 public:
  void AddPerson(const std::shared_ptr<Person>& person) override;
  void RemovePerson(Person* person) override;

  LecturerIterator Begin() const;

 private:
  std::vector<std::shared_ptr<Lecturer>> lecturers_;

  friend class LecturerIterator;
};

class LecturerIterator {
 public:
  explicit LecturerIterator(const LecturerContainer* container);

  bool HasNext() const;
  Lecturer* Next();

 private:
  const LecturerContainer* container_;
  int current_index_;
};

#endif  // MODEL_CONTAINERS_LECTURER_CONTAINER_H_
