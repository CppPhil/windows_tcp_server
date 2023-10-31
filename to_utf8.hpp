#pragma once
#include <string>
#include <string_view>

namespace wts {
std::string toUtf8(std::wstring_view utf16);
} // namespace wts
