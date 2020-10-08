#include "person_drawer.h"

PersonDrawer::PersonDrawer()
    : person_pen_(CreatePen(PS_SOLID, 2, kPenColor)),
      aggressive_lecturer_brush_(CreateSolidBrush(kAggressiveLecturerColor)),
      lecturer_brush_(CreateSolidBrush(kLecturerColor)),
      student_brush_(CreateSolidBrush(kStudentColor)),
      lecturer_with_food_brush_(CreateSolidBrush(kLecturerWithFoodColor)),
      student_with_food_brush_(CreateSolidBrush(kStudentWithFoodColor)) {}

void PersonDrawer::SetDisplayContext(HDC hdc) {
  display_context_ = hdc;
}

void PersonDrawer::VisitStudent(Visitable* visitable) {
  auto student = dynamic_cast<Student*>(visitable);
  IntPoint position = student->GetPosition().ToInt();

  SelectPen(display_context_, person_pen_);
  SelectBrush(display_context_,
              student->HasFood() ? student_with_food_brush_ : student_brush_);

  Ellipse(display_context_,
          position.x - kStudentRadius,
          position.y - kStudentRadius,
          position.x + kStudentRadius,
          position.y + kStudentRadius);
}

void PersonDrawer::VisitLecturer(Visitable* visitable) {
  auto lecturer = dynamic_cast<Lecturer*>(visitable);
  IntPoint position = lecturer->GetPosition().ToInt();

  SelectPen(display_context_, person_pen_);
  if (lecturer->HasFood()) {
    SelectBrush(display_context_, lecturer_with_food_brush_);
  } else {
    SelectBrush(display_context_,
                lecturer->IsAggressive() ? aggressive_lecturer_brush_
                                         : lecturer_brush_);
  }

  Rectangle(display_context_,
            position.x - kLecturerWidth,
            position.y - kLecturerHeight,
            position.x + kLecturerWidth,
            position.y + kLecturerHeight);
}
