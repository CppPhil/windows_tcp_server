#include <Windows.h>

#include "exception.hpp"
#include "win_exception.hpp"

int main()
{
  try {
    // TODO: HERE
  }
  catch (const wts::WinException& winException) {
    const std::wstring exceptionText{winException.toString()};
    MessageBoxW(
      nullptr,
      exceptionText.c_str(),
      L"wts::WinException caught",
      MB_ICONERROR | MB_OK);
  }
  catch (const wts::Exception& exception) {
    const std::wstring exceptionText{exception.toString()};
    MessageBoxW(
      nullptr,
      exceptionText.c_str(),
      L"wts::Exception caught",
      MB_ICONERROR | MB_OK);
  }
  catch (const std::exception& exception) {
    MessageBoxA(
      nullptr, exception.what(), "std::exception caught", MB_ICONERROR | MB_OK);
  }
  catch (...) {
    MessageBoxW(
      nullptr,
      L"Unknown exception caught!",
      L"Unknown exception caught",
      MB_ICONERROR | MB_OK);
  }
}
