#pragma once
#include <WinSock2.h>

#include "noncopyable.hpp"

namespace wts {
class SocketLibraryManager {
public:
  WTS_NONCOPYABLE(SocketLibraryManager);

  SocketLibraryManager();

  ~SocketLibraryManager();

private:
  WSADATA m_wsaData;
};
} // namespace wts
