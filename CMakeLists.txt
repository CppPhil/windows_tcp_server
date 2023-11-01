cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("windows_tcp_server")

add_executable(
  windows_tcp_server
  exception.cpp
  exception.hpp
  finally.hpp
  format_error.cpp
  format_error.hpp
  launch_client_handler.cpp
  launch_client_handler.hpp
  main.cpp
  noncopyable.hpp
  port.hpp
  socket_library_manager.cpp
  socket_library_manager.hpp
  to_utf16.cpp
  to_utf16.hpp
  to_utf8.cpp
  to_utf8.hpp
  win_exception.cpp
  win_exception.hpp
)

set_property(TARGET windows_tcp_server PROPERTY CXX_STANDARD 20)

if (WIN32)
  target_link_libraries(windows_tcp_server PRIVATE wsock32 ws2_32)
  target_compile_definitions(windows_tcp_server PRIVATE WIN32_LEAN_AND_MEAN)
endif()
