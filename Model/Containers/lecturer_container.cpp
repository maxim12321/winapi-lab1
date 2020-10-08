#include "lecturer_container.h"

void LecturerContainer::AddPerson(const std::shared_ptr<Person>& person) {
  auto lecturer = std::dynamic_pointer_cast<Lecturer>(person);
  if (lecturer != nullptr) {
    lecturers_.push_back(lecturer);
    size_++;
  }
}

void LecturerContainer::RemovePerson(Person* person) {
  auto lecturer_to_remove = dynamic_cast<Lecturer*>(person);
  for (int i = 0; i < Size(); i++) {
    if (lecturers_[i].get() == lecturer_to_remove) {
      lecturers_.erase(lecturers_.begin() + i);
      size_--;
      return;
    }
  }
}

LecturerIterator LecturerContainer::Begin() const {
  return LecturerIterator(this);
}

LecturerIterator::LecturerIterator(const LecturerContainer* container)
    : container_(container), current_index_(0) {}

bool LecturerIterator::HasNext() const {
  return current_index_ < container_->Size();
}

Lecturer* LecturerIterator::Next() {
  if (!HasNext()) {
    return nullptr;
  }

  auto lecturer = container_->lecturers_[current_index_];
  current_index_++;
  return lecturer.get();
}
