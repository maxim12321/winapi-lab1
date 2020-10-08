#ifndef MODEL_CONTAINERS_STUDENT_CONTAINER_H_
#define MODEL_CONTAINERS_STUDENT_CONTAINER_H_

#include <algorithm>
#include <memory>
#include <set>
#include <vector>

#include "person_container.h"
#include "../student.h"

class StudentIterator;

class StudentContainer : public PersonContainer {
 public:
  void AddPerson(const std::shared_ptr<Person>& person) override;
  void RemovePerson(Person* person) override;

  void UpdateOrder();

  StudentIterator Begin() const;

 private:
  static bool CompareStudents(const std::shared_ptr<Student>& a,
                              const std::shared_ptr<Student>& b);

 private:
  std::vector<std::shared_ptr<Student>> students_;

  friend class StudentIterator;
};

class StudentIterator {
 public:
  explicit StudentIterator(const StudentContainer* container);

  bool HasNext() const;
  Student* Next();

 private:
  std::shared_ptr<Student> ChooseNextStudent() const;

 private:
  const StudentContainer* container_;
  std::shared_ptr<Student> current_student_ = nullptr;
};

#endif  // MODEL_CONTAINERS_STUDENT_CONTAINER_H_
