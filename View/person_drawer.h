#ifndef VIEW_PERSON_DRAWER_H_
#define VIEW_PERSON_DRAWER_H_

#include <windows.h>
#include <windowsx.h>

#include "../Model/Visitors/person_visitor.h"
#include "../Model/lecturer.h"
#include "../Model/student.h"

class PersonDrawer : public PersonVisitor {
 public:
  PersonDrawer();

  void SetDisplayContext(HDC hdc);

  void VisitLecturer(Visitable* visitable) override;
  void VisitStudent(Visitable* visitable) override;

 private:
  const int kLecturerWidth = 15;
  const int kLecturerHeight = 15;
  const int kStudentRadius = 13;

  const COLORREF kAggressiveLecturerColor = RGB(192, 57, 43);
  const COLORREF kLecturerColor = RGB(22, 160, 133);
  const COLORREF kStudentColor = RGB(240, 147, 43);

  const COLORREF kLecturerWithFoodColor = RGB(41, 128, 185);
  const COLORREF kStudentWithFoodColor = RGB(142, 68, 173);

  const COLORREF kPenColor = RGB(83, 92, 104);

 private:
  HDC display_context_ = nullptr;

  HPEN person_pen_ = nullptr;

  HBRUSH aggressive_lecturer_brush_ = nullptr;
  HBRUSH lecturer_brush_ = nullptr;
  HBRUSH student_brush_ = nullptr;

  HBRUSH lecturer_with_food_brush_ = nullptr;
  HBRUSH student_with_food_brush_ = nullptr;
};

#endif  // VIEW_PERSON_DRAWER_H_
