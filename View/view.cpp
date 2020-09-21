#include "view.h"

View::View() : person_drawer_(std::make_shared<PersonDrawer>()),
               pen_(CreatePen(PS_SOLID, 1, kPenColor)),
               table_brush_(CreateSolidBrush(kTableColor)),
               cashier_brush_(CreateSolidBrush(kCashierColor)),
               students_center_brush_(CreateSolidBrush(kStudentsCenterColor)) {}

void View::StartDrawing(HDC hdc) {
  display_context_ = hdc;
  person_drawer_->SetDisplayContext(hdc);
}

void View::DrawLecturers(LecturerIterator lecturer_iterator) {
  while (lecturer_iterator.HasNext()) {
    lecturer_iterator.Next()->Accept(person_drawer_);
  }
}

void View::DrawStudents(StudentIterator student_iterator) {
  while (student_iterator.HasNext()) {
    student_iterator.Next()->Accept(person_drawer_);
  }
}

void View::DrawCashier(const Point& cashier_position) {
  IntPoint position = cashier_position.ToInt();
  SelectPen(display_context_, pen_);
  SelectBrush(display_context_, table_brush_);

  Rectangle(display_context_,
            position.x - kTableWidth,
            position.y - kTableHeight,
            position.x + kTableWidth,
            position.y + kTableHeight);

  SelectBrush(display_context_, cashier_brush_);

  Ellipse(display_context_,
          position.x - kCashierRadius,
          position.y - kTableHeight - 2 * kCashierRadius,
          position.x + kCashierRadius,
          position.y - kTableHeight);
}

void View::DrawStudentsCenter(const Point& position, double circle_radius) {
  auto center = position.ToInt();
  int radius = static_cast<int>(circle_radius);
  SelectPen(display_context_, pen_);
  SelectBrush(display_context_, students_center_brush_);

  Ellipse(display_context_,
          center.x - radius,
          center.y - radius,
          center.x + radius,
          center.y + radius);
}

void View::DrawCashierMessage(const std::wstring& text) {
  TextOutW(display_context_,
           kCashierMessagePosition.x, kCashierMessagePosition.y,
           text.c_str(), text.length());
}
