#include "student_container.h"

void StudentContainer::AddPerson(const std::shared_ptr<Person>& person) {
  auto student = std::dynamic_pointer_cast<Student>(person);
  if (student != nullptr) {
    students_.push_back(student);
    size_++;
  }
}

void StudentContainer::RemovePerson(Person* person) {
  auto lecturer_to_remove = dynamic_cast<Student*>(person);
  for (auto iterator = students_.begin(); iterator != students_.end();
       iterator++) {
    if (iterator->get() == lecturer_to_remove) {
      students_.erase(iterator);
      size_--;
      return;
    }
  }
}

void StudentContainer::UpdateOrder() {
  std::sort(students_.begin(), students_.end(), CompareStudents);
}

StudentIterator StudentContainer::Begin() const {
  return StudentIterator(this);
}

bool StudentContainer::CompareStudents(const std::shared_ptr<Student>& a,
                                       const std::shared_ptr<Student>& b) {
  return a->DistanceToCashier() < b->DistanceToCashier();
}

StudentIterator::StudentIterator(const StudentContainer* container)
    : container_(container) {
  if (!container->Empty()) {
    current_student_ = *container->students_.begin();
  }
}

bool StudentIterator::HasNext() const {
  return current_student_ != nullptr;
}

Student* StudentIterator::Next() {
  if (!HasNext()) {
    return nullptr;
  }

  auto student = current_student_;
  current_student_ = ChooseNextStudent();
  return student.get();
}

std::shared_ptr<Student> StudentIterator::ChooseNextStudent() const {
  if (current_student_ == nullptr) {
    return nullptr;
  }

  auto next_student = std::upper_bound(container_->students_.begin(),
                                       container_->students_.end(),
                                       current_student_,
                                       StudentContainer::CompareStudents);

  if (next_student == container_->students_.end()) {
    return nullptr;
  }
  return *next_student;
}
