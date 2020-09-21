#include "people_manager.h"

PeopleManager::PeopleManager(const Point& cashier_position)
    : cashier_position_(cashier_position),
      students_position_(kStudentsCenterPosition),
      student_move_data_(
          std::make_shared<StudentMoveData>(cashier_position_,
                                            students_position_,
                                            kStudentsCircleRadius)) {}

void PeopleManager::AddAggressiveLecturer() {
  if (aggressive_lecturers_count_ == 0) {
    student_move_data_->SetCenterPosition(kScaredStudentsCenterPosition);
  }
  aggressive_lecturers_count_++;
  lecturers_.AddPerson(std::make_shared<Lecturer>(kLecturerStartPosition,
                                                  kLecturerSpeed,
                                                  true));
}

void PeopleManager::AddLecturer() {
  lecturers_.AddPerson(std::make_shared<Lecturer>(kLecturerStartPosition,
                                                  kLecturerSpeed,
                                                  false));
}

void PeopleManager::AddStudent() {
  students_.AddPerson(std::make_shared<Student>(kStudentStartPosition,
                                                kStudentSpeed,
                                                student_move_data_));
}

void PeopleManager::ToggleDoubleDistance() {
  is_double_distance_ = !is_double_distance_;
}

void PeopleManager::UseCashier() {
  is_cashier_waiting_ = false;
}

bool PeopleManager::IsDoubleDistance() const {
  return is_double_distance_;
}

bool PeopleManager::IsCashierWaiting() const {
  return is_cashier_waiting_;
}

bool PeopleManager::AreStudentsScared() const {
  return aggressive_lecturers_count_ > 0;
}

void PeopleManager::Update(double time) {
  Point lecturer_position = kFirstLecturerPosition;
  double distance = kDistanceBetweenLecturers * (is_double_distance_ ? 2 : 1);

  std::vector<Lecturer*> lecturers_to_delete;
  for (auto iterator = lecturers_.Begin(); iterator.HasNext();) {
    auto lecturer = iterator.Next();

    if (!lecturer->IsServed()) {
      lecturer->SetTargetPosition(lecturer_position);
      lecturer_position.y += distance;
    } else if (lecturer->HasReached() && !lecturer->HasFood()) {
      lecturer->SetTargetPosition(kLecturerEndPosition);
      lecturer->GiveFood();
      if (lecturer->IsAggressive()) {
        AggressiveLecturerServed();
      }
      is_cashier_waiting_ = true;
    }

    if (lecturer->CanBeDestroyed()) {
      lecturers_to_delete.push_back(lecturer);
    }
    lecturer->Update(time);
  }
  for (const auto& lecturer : lecturers_to_delete) {
    lecturers_.RemovePerson(lecturer);
  }

  std::vector<Student*> students_to_delete;
  for (auto iterator = students_.Begin(); iterator.HasNext();) {
    auto student = iterator.Next();

    if (student->IsServed() && student->HasReached() && !student->HasFood()) {
      student->SetTargetPosition(kStudentEndPosition);
      student->GiveFood();
      is_cashier_waiting_ = true;
    }

    if (student->CanBeDestroyed()) {
      students_to_delete.push_back(student);
    }
    student->Update(time);
  }
  for (const auto& student : students_to_delete) {
    students_.RemovePerson(student);
  }
  students_.UpdateOrder();
}

Point PeopleManager::GetStudentsCenterPosition() const {
  return aggressive_lecturers_count_ == 0 ? kStudentsCenterPosition
                                          : kScaredStudentsCenterPosition;
}

double PeopleManager::GetStudentsCenterRadius() const {
  return kStudentsCircleRadius;
}

LecturerIterator PeopleManager::GetLecturerIterator() const {
  return lecturers_.Begin();
}

StudentIterator PeopleManager::GetStudentIterator() const {
  return students_.Begin();
}

void PeopleManager::AggressiveLecturerServed() {
  aggressive_lecturers_count_--;
  if (aggressive_lecturers_count_ == 0) {
    student_move_data_->SetCenterPosition(kStudentsCenterPosition);
  }
}
