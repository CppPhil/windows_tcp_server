#include <string>

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

#include "exception.hpp"
#include "finally.hpp"
#include "launch_client_handler.hpp"
#include "port.hpp"
#include "socket_library_manager.hpp"
#include "win_exception.hpp"

int main()
{
  try {
    wts::SocketLibraryManager socketLibraryManager{};
    struct addrinfo           hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;

    struct addrinfo*  addrinfoList{nullptr};
    const std::string portText{std::to_string(wts::port)};
    int               statusCode{
      getaddrinfo(nullptr, portText.c_str(), &hints, &addrinfoList)};

    if (statusCode != 0) {
      WTS_WIN_THROW(
        static_cast<DWORD>(statusCode), L"{}", L"getaddrinfo failed");
    }

    auto addrinfoListCleaner{wts::finally([&addrinfoList] {
      if (addrinfoList != nullptr) {
        freeaddrinfo(addrinfoList);
        addrinfoList = nullptr;
      }
    })};

    SOCKET serverSocket{socket(
      addrinfoList->ai_family,
      addrinfoList->ai_socktype,
      addrinfoList->ai_protocol)};

    if (serverSocket == INVALID_SOCKET) {
      WTS_WIN_THROW(
        static_cast<DWORD>(WSAGetLastError()),
        L"{}",
        L"Could not create server socket");
    }

    auto serverSocketCloser{wts::finally([&serverSocket] {
      closesocket(serverSocket);
      serverSocket = INVALID_SOCKET;
    })};

    statusCode = bind(
      serverSocket,
      addrinfoList->ai_addr,
      static_cast<int>(addrinfoList->ai_addrlen));

    if (statusCode == SOCKET_ERROR) {
      WTS_WIN_THROW(
        static_cast<DWORD>(WSAGetLastError()),
        L"{}",
        L"Could not bind server socket");
    }

    freeaddrinfo(addrinfoList);
    addrinfoList = nullptr;

    statusCode = listen(serverSocket, SOMAXCONN);

    if (statusCode == SOCKET_ERROR) {
      WTS_WIN_THROW(
        static_cast<DWORD>(WSAGetLastError()),
        L"{}",
        L"Server socket failed to start listening");
    }

    SOCKET clientSocket{INVALID_SOCKET};

    while ((clientSocket = accept(serverSocket, nullptr, nullptr))
           != INVALID_SOCKET) {
      wts::launchClientHandler(clientSocket);
    }

    WTS_THROW(L"{}", L"Failed to accept client socket!");
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
