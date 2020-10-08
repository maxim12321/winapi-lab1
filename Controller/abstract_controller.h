#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <windows.h>

class AbstractController {
 public:
  virtual LRESULT HandleMessages(HWND window_handle, UINT message_code,
                                 WPARAM w_param, LPARAM l_param) = 0;

 protected:
  virtual void InitializeUI() = 0;
  virtual void Update() = 0;
  virtual void Draw(HDC hdc) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
