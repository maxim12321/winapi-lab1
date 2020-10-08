#ifndef MODEL_VISITORS_CASHIER_H_
#define MODEL_VISITORS_CASHIER_H_

#include <string>

#include "person_visitor.h"
#include "../student.h"
#include "../lecturer.h"
#include "../Utils/point.h"

class Cashier : public PersonVisitor {
 public:
  explicit Cashier(const Point& position);

  void VisitLecturer(Visitable* visitable) override;
  void VisitStudent(Visitable* visitable) override;

  std::wstring GetTextToDisplay() const;

 private:
  const std::wstring kAggressiveLecturerText =
      L"Товарищ преподаватель, вы распугали всех студентов!";
  const std::wstring kLecturerText =
      L"Товарищ преподаватель, подходите за едой :)";
  const std::wstring kStudentText =
      L"Эй, студент, забирай свою жижу побыстрее.";

 private:
  Point position_;

  std::wstring text_to_display_;
};

#endif  // MODEL_VISITORS_CASHIER_H_
