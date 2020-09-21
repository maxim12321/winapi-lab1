#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <memory>

#include "Controller/controller.h"

std::shared_ptr<Controller> controller;

void InitializeController(HINSTANCE instance_handle) {
  controller = std::make_shared<Controller>(instance_handle);
}

LRESULT CALLBACK MessagesHandle(HWND window_handle, UINT message_code,
                                WPARAM w_param, LPARAM l_param) {
  return controller->HandleMessages(window_handle, message_code,
                                    w_param, l_param);
}

INT WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE,
                   LPSTR, int n_cmd_show) {
  InitializeController(instance_handle);

  // Register the window class.
  const wchar_t kClassName[] = L"msg_server_class";

  WNDCLASS window_class = {};
  window_class.lpfnWndProc = MessagesHandle;
  window_class.hInstance = instance_handle;
  window_class.lpszClassName = kClassName;
  window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
  window_class.hbrBackground = GetStockBrush(WHITE_BRUSH);
  RegisterClass(&window_class);

  // Create the window.
  HWND window_handle = CreateWindowEx(
      /* dwExStyle =    */ 0,
      /* lpClassName =  */ kClassName,
      /* lpWindowName = */ L"F*cking WinAPI",
      /* dwStyle =      */ WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
      /* X =            */ CW_USEDEFAULT,
      /* Y =            */ CW_USEDEFAULT,
      /* nWidth =       */ 800,
      /* nHeight =      */ 600,
      /* hWndParent =   */ nullptr,
      /* hMenu =        */ nullptr,
      /* hInstance =    */ instance_handle,
      /* lpParam =      */ nullptr
  );
  if (window_handle == nullptr) {
    return 1;
  }

  // Show the window.
  ShowWindow(window_handle, n_cmd_show);

  // Run the message loop.
  MSG message = {};
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return (int) message.wParam;
}
