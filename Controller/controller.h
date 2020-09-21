#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <random>
#include <string>
#include <windows.h>
#include <commctrl.h>

#include "abstract_controller.h"
#include "people_manager.h"
#include "../Model/Utils/point.h"
#include "../Model/Visitors/cashier.h"
#include "../View/view.h"

class Controller : public AbstractController {
 public:
  explicit Controller(HINSTANCE instance_handle);

  LRESULT HandleMessages(HWND window_handle, UINT message_code,
                         WPARAM w_param, LPARAM l_param) override;

 protected:
  void InitializeUI() override;
  void Update() override;
  void Draw(HDC hdc) override;
  bool ControlCommand(HWND control);

 private:
  HWND CreateButton(int x, int y, int width, int height,
                    const std::string& text);

  Lecturer* ChooseLecturerToServe() const;
  Student* ChooseStudentToServe() const;

 private:
  const unsigned int kUpdateTimerId = 1;
  const int kTimeBetweenFrames = 30;

  const Point kCashierPosition = {300, 100};

  const double kStudentServeChance = 0.5;

 private:
  HWND window_handle_ = nullptr;
  HINSTANCE instance_handle_ = nullptr;

  View view_;
  PeopleManager people_manager_;
  std::shared_ptr<Cashier> cashier_;

  HWND add_aggressive_lecturer_button_ = nullptr;
  HWND add_lecturer_button_ = nullptr;
  HWND add_student_button_ = nullptr;
  HWND double_distance_button_ = nullptr;

  std::random_device random_device_;
  std::mt19937 generator_;
  std::uniform_real_distribution<double> chance_generator_;
};

#endif  // CONTROLLER_CONTROLLER_H_
