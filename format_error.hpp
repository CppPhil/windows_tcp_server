#pragma once
#include <string>

#include <Windows.h>

namespace wts
{
std::wstring formatError(DWORD errorCode);
} // namespace wts
