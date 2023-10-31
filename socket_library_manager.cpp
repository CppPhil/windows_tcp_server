#include <winsock.h>

#include "socket_library_manager.hpp"

namespace wts {
// Windows Sockets API 2.2
constexpr WORD requestedVersion{MAKEWORD(2, 2)};

SocketLibraryManager::SocketLibraryManager() : m_wsaData{}
{
  const int statusCode{WSAStartup(requestedVersion, &m_wsaData)};

  if (statusCode != 0) {
    // TODO: Handle error.
  }
}

SocketLibraryManager::~SocketLibraryManager()
{
}
} // namespace wts
