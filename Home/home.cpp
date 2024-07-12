#include "home.h"
#include <windows.h>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  ShellExecuteA(0, 0, "https://www.playredfox.com/rumble_fighter", 0, 0, 1);
  return 0;
}