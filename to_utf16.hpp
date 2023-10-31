#pragma once
#include <string>
#include <string_view>

namespace wts {
std::wstring toUtf16(std::string_view utf8);
} // namespace wts
