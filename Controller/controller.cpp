#include "controller.h"

Controller::Controller(HINSTANCE instance_handle)
    : instance_handle_(instance_handle),
      view_(),
      people_manager_(kCashierPosition),
      cashier_(std::make_shared<Cashier>(kCashierPosition)),
      random_device_(),
      generator_(random_device_()),
      chance_generator_(0, 1) {}

LRESULT Controller::HandleMessages(HWND window_handle, UINT message_code,
                                   WPARAM w_param, LPARAM l_param) {
  if (window_handle_ == nullptr) {
    window_handle_ = window_handle;
  }

  switch (message_code) {
    case WM_CREATE: {
      SetTimer(window_handle_, kUpdateTimerId, kTimeBetweenFrames, nullptr);
      InitializeUI();
      break;
    }
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(window_handle, &ps);
      Draw(hdc);
      EndPaint(window_handle, &ps);
      break;
    }
    case WM_COMMAND: {
      auto control_handle = reinterpret_cast<HWND>(l_param);
      if (!ControlCommand(control_handle)) {
        return DefWindowProc(window_handle, message_code, w_param, l_param);
      }
      break;
    }
    case WM_TIMER: {
      if (w_param == kUpdateTimerId) {
        Update();
        InvalidateRect(window_handle_, nullptr, true);
      }
      break;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
    }
    default: {
      return DefWindowProc(window_handle, message_code, w_param, l_param);
    }
  }
  return 0;
}

void Controller::InitializeUI() {
  add_aggressive_lecturer_button_ =
      CreateButton(700, 100, 80, 50, "Aggressive");
  add_lecturer_button_ = CreateButton(700, 175, 80, 50, "Lecturer");
  add_student_button_ = CreateButton(700, 250, 80, 50, "Student");
  double_distance_button_ = CreateButton(700, 400, 80, 50, "COVID off");
}

void Controller::Update() {
  double time = kTimeBetweenFrames / 1000.;
  people_manager_.Update(time);

  if (people_manager_.IsCashierWaiting()) {
    auto lecturer = ChooseLecturerToServe();
    auto student = ChooseStudentToServe();

    if (lecturer == nullptr && student == nullptr) {
      return;
    }

    if (lecturer == nullptr) {
      student->Accept(cashier_);
    } else if (student == nullptr) {
      lecturer->Accept(cashier_);
    } else {
      double random_value = chance_generator_(generator_);
      double student_chance =
          kStudentServeChance / (people_manager_.AreStudentsScared() ? 2 : 1);

      if (random_value < student_chance) {
        student->Accept(cashier_);
      } else {
        lecturer->Accept(cashier_);
      }
    }
    people_manager_.UseCashier();
  }
}

void Controller::Draw(HDC hdc) {
  view_.StartDrawing(hdc);

  view_.DrawCashierMessage(cashier_->GetTextToDisplay());
  view_.DrawStudentsCenter(people_manager_.GetStudentsCenterPosition(),
                           people_manager_.GetStudentsCenterRadius());

  view_.DrawCashier(kCashierPosition);
  view_.DrawLecturers(people_manager_.GetLecturerIterator());
  view_.DrawStudents(people_manager_.GetStudentIterator());
}

bool Controller::ControlCommand(HWND control) {
  if (control == add_aggressive_lecturer_button_) {
    people_manager_.AddAggressiveLecturer();
  } else if (control == add_lecturer_button_) {
    people_manager_.AddLecturer();
  } else if (control == add_student_button_) {
    people_manager_.AddStudent();
  } else if (control == double_distance_button_) {
    people_manager_.ToggleDoubleDistance();
    std::string text = "COVID ";
    text += (people_manager_.IsDoubleDistance() ? "on" : "off");
    SetWindowTextA(double_distance_button_, text.c_str());
  } else {
    return false;
  }
  return true;
}

HWND Controller::CreateButton(int x, int y, int width, int height,
                              const std::string& text) {
  return CreateWindow(
      "button", text.c_str(),
      WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
      x, y, width, height, window_handle_, nullptr, instance_handle_, nullptr);
}

Lecturer* Controller::ChooseLecturerToServe() const {
  for (auto person = people_manager_.GetLecturerIterator(); person.HasNext();) {
    auto lecturer = person.Next();
    if (lecturer->IsServed()) {
      continue;
    }
    return (lecturer->CanBeServed() ? lecturer : nullptr);
  }
  return nullptr;
}

Student* Controller::ChooseStudentToServe() const {
  for (auto person = people_manager_.GetStudentIterator(); person.HasNext();) {
    auto student = person.Next();
    if (student->CanBeServed()) {
      return student;
    }
  }
  return nullptr;
}
