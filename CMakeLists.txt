cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("windows_tcp_server")

add_executable(windows_tcp_server "main.cpp" "format_error.cpp" "socket_library_manager.cpp" "exception.cpp" "to_utf8.cpp" "to_utf16.cpp" "win_exception.cpp"  "launch_client_handler.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET windows_tcp_server PROPERTY CXX_STANDARD 20)
endif()

if (WIN32)
  target_link_libraries(windows_tcp_server PRIVATE wsock32 ws2_32)
  target_compile_definitions(windows_tcp_server PRIVATE WIN32_LEAN_AND_MEAN)
endif()
