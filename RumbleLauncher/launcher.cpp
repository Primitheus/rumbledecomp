#include "launcher.h"

HINSTANCE dword_44AD78 = nullptr;

int dword_44AD74 = 0;
int dword_44B1E0 = 0;
int dword_44B1DC = 0;

int __cdecl sub_414850(int a1, HINSTANCE a2)
{
  int result; // eax

  result = a1;
  dword_44AD74 = a1;
  dword_44AD78 = a2;
  return result;
}

int __cdecl sub_42DA60(int a1, int a2)
{
  int result; // eax

  result = a1;
  dword_44B1E0 = a1;
  dword_44B1DC = a2;
  return result;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  sub_414850((int)hInstance, hInstance);
  sub_42DA60((int)hInstance, 101);
  
}