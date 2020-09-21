#include "cashier.h"

Cashier::Cashier(const Point& position) : position_(position) {}

void Cashier::VisitLecturer(Visitable* visitable) {
  auto lecturer = dynamic_cast<Lecturer*>(visitable);
  lecturer->Serve();
  lecturer->SetTargetPosition(position_);

  text_to_display_ = lecturer->IsAggressive() ? kAggressiveLecturerText
                                              : kLecturerText;
}

void Cashier::VisitStudent(Visitable* visitable) {
  auto student = dynamic_cast<Student*>(visitable);
  student->Serve();
  student->SetTargetPosition(position_);

  text_to_display_ = kStudentText;
}

std::wstring Cashier::GetTextToDisplay() const {
  return text_to_display_;
}
