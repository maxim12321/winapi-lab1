#ifndef CONTROLLER_PEOPLE_MANAGER_H_
#define CONTROLLER_PEOPLE_MANAGER_H_

#include <memory>

#include "../Model/lecturer.h"
#include "../Model/student.h"
#include "../Model/student_move_data.h"
#include "../Model/Containers/lecturer_container.h"
#include "../Model/Containers/student_container.h"
#include "../Model/Utils/point.h"

class PeopleManager {
 public:
  explicit PeopleManager(const Point& cashier_position);

  void AddAggressiveLecturer();
  void AddLecturer();
  void AddStudent();

  void ToggleDoubleDistance();
  void UseCashier();

  bool IsDoubleDistance() const;
  bool IsCashierWaiting() const;
  bool AreStudentsScared() const;

  void Update(double time);

  Point GetStudentsCenterPosition() const;
  double GetStudentsCenterRadius() const;

  LecturerIterator GetLecturerIterator() const;
  StudentIterator GetStudentIterator() const;

 private:
  void AggressiveLecturerServed();

 private:
  const Point kStudentStartPosition = {500, 600};
  const Point kStudentEndPosition = {1000, 50};
  const double kStudentSpeed = 150;

  const Point kStudentsCenterPosition = {450, 250};
  const Point kScaredStudentsCenterPosition = {600, 450};
  const double kStudentsCircleRadius = 75;

  const Point kLecturerStartPosition = {0, 600};
  const Point kLecturerEndPosition = {-100, 50};
  const double kLecturerSpeed = 100;

  const Point kFirstLecturerPosition = {150, 170};
  const double kDistanceBetweenLecturers = 30;

 private:
  Point cashier_position_;
  Point students_position_;
  std::shared_ptr<StudentMoveData> student_move_data_;

  LecturerContainer lecturers_;
  StudentContainer students_;

  bool is_double_distance_ = false;
  bool is_cashier_waiting_ = true;

  int aggressive_lecturers_count_ = 0;
};

#endif  // CONTROLLER_PEOPLE_MANAGER_H_
