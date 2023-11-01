#include <cstdio>
#include <stdio.h>

#include <thread>

#include "finally.hpp"
#include "format_error.hpp"
#include "launch_client_handler.hpp"

namespace wts {
namespace {
void threadFunction(SOCKET clientSocket)
{
  auto socketCloser{finally([&clientSocket] {
    shutdown(clientSocket, SD_BOTH);
    closesocket(clientSocket);
    clientSocket = INVALID_SOCKET;
  })};

  static constexpr std::size_t bufferSize{512};
  char                         recvbuf[bufferSize]{};
  int                          receiveResult{};
  int                          sendResult{};

  do {
    receiveResult = recv(clientSocket, recvbuf, bufferSize, 0);

    if (receiveResult > 0) {
      std::printf("Bytes received: %d\n", receiveResult);
      sendResult = send(clientSocket, recvbuf, receiveResult, 0);

      if (sendResult == SOCKET_ERROR) {
        const std::wstring errorMessage{formatError(WSAGetLastError())};
        wprintf(L"send failed with error: %ls\n", errorMessage.c_str());
        return;
      }

      std::printf("Bytes sent: %d\n", sendResult);
    }
    else if (receiveResult == 0) {
      std::printf("Connection closing...\n");
    }
    else {
      const std::wstring errorMessage{formatError(WSAGetLastError())};
      wprintf(L"recv failed with error: %ls\n", errorMessage.c_str());
      return;
    }
  } while (receiveResult > 0);
}
} // anonymous namespace

void launchClientHandler(SOCKET clientSocket)
{
  std::thread thread{&threadFunction, clientSocket};
  thread.detach();
}
} // namespace wts
