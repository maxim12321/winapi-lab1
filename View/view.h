#ifndef MODEL_VIEW_H_
#define MODEL_VIEW_H_

#include <string>
#include <windows.h>
#include <windowsx.h>

#include "person_drawer.h"
#include "../Model/Containers/lecturer_container.h"
#include "../Model/Containers/student_container.h"
#include "../Model/Utils/point.h"

class View {
 public:
  View();

  void StartDrawing(HDC hdc);

  void DrawLecturers(LecturerIterator lecturer_iterator);
  void DrawStudents(StudentIterator student_iterator);
  void DrawCashier(const Point& cashier_position);

  void DrawStudentsCenter(const Point& position, double circle_radius);
  void DrawCashierMessage(const std::wstring& text);

 private:
  const int kTableWidth = 50;
  const int kTableHeight = 25;
  const int kCashierRadius = 15;

  const IntPoint kCashierMessagePosition = {150, 15};

  const COLORREF kTableColor = RGB(113, 128, 147);
  const COLORREF kCashierColor = RGB(72, 52, 212);
  const COLORREF kStudentsCenterColor = RGB(223, 249, 251);

  const COLORREF kPenColor = RGB(127, 140, 141);

 private:
  std::shared_ptr<PersonDrawer> person_drawer_;
  HDC display_context_ = nullptr;

  HPEN pen_ = nullptr;

  HBRUSH table_brush_ = nullptr;
  HBRUSH cashier_brush_ = nullptr;
  HBRUSH students_center_brush_ = nullptr;
};

#endif  // MODEL_VIEW_H_
