#pragma once
#include <Windows.h>

#include "exception.hpp"

namespace wts {
#define WTS_WIN_THROW(ErrorCode, FormatString, ...)        \
  throw ::wts::WinException                                \
  {                                                        \
    ::wts::toUtf16(__FILE__), ::wts::toUtf16(__FUNCSIG__), \
      static_cast<std::size_t>(__LINE__),                  \
      std::format(FormatString, __VA_ARGS__), ErrorCode    \
  }

class WinException : public Exception {
public:
  WinException(
    std::wstring file,
    std::wstring function,
    std::size_t  line,
    std::wstring message,
    DWORD        errorCode);

  void printOn(std::wostream& wos) const override;

  DWORD errorCode() const noexcept;

private:
  DWORD        m_errorCode;
  std::wstring m_winErrorMessage;
};
} // namespace wts
