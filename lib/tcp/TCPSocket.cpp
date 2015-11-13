#include <netinet/in.h>
#include "../../include/tcp/TCPSocket.hpp"
#include "../../include/SocketAddress.hpp"
#include "../../include/Global.hpp"

namespace Collie {
namespace TCP {

TCPSocket::TCPSocket() : Socket(), sendFlag(0), recvFlag(0) {
    Log(TRACE) << "TCPSocket client is constructing";
}

TCPSocket::TCPSocket(std::shared_ptr<SocketAddress> addr)
    : Socket(addr), sendFlag(0), recvFlag(0) {
    Log(TRACE) << "TCPSocket server is constructing";
}

TCPSocket::~TCPSocket() { Log(TRACE) << "TCPSocket is destructing"; }

void
TCPSocket::setSendFlag(const int flag) {
    sendFlag = flag;
}

void
TCPSocket::setRecvFlag(const int flag) {
    recvFlag = flag;
}

void
TCPSocket::listen() {
    if(localAddr->getIPVersion() == IP::V4) {
        listenV4();
    } else {
        listenV6();
    }
}

void
TCPSocket::listenV4() {
    if(!localAddr) {
        THROW_("local address is null");
    }
    struct sockaddr_in servAddr = localAddr->getAddrV4();

    fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd < 0) {
        THROW_SYS;
    }

    int ret = bind(fd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if(ret < 0) {
        THROW_SYS;
    }
    Log(TRACE) << "Socket " << fd << " is binding";

    Log(TRACE) << "Socket is listening";

    if(::listen(fd, SOMAXCONN) < 0) {
        THROW_SYS;
    }
}

void
TCPSocket::listenV6() {
    // TODO
}

void
TCPSocket::connect(std::shared_ptr<SocketAddress> servAddr) {
    if(servAddr->getIPVersion() == IP::V4) {
        connectV4(servAddr);
    } else {
        connectV6(servAddr);
    }
}

void
TCPSocket::connectV4(std::shared_ptr<SocketAddress> servAddr) {
    struct sockaddr_in serv = servAddr->getAddrV4();
    fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd < 0) {
        THROW_SYS;
    }
    int ret = ::connect(fd, (struct sockaddr *)&serv, sizeof(serv));
    if(ret == -1) {
        THROW_SYS;
    }
    struct sockaddr_in local;
    int addrLen = sizeof(local);
    ::getsockname(fd, (struct sockaddr *)&local, (socklen_t *)&addrLen);
    *localAddr = local;
}

void TCPSocket::connectV6(std::shared_ptr<SocketAddress>) {
    // TODO
}

int
TCPSocket::accept(std::shared_ptr<SocketAddress> connAddr) const {
    return TCPSocket::accept(fd, connAddr);
}

int
TCPSocket::accept(const int fd, std::shared_ptr<SocketAddress> connAddr) {
    // IPv4
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    clientAddrLen = sizeof(clientAddr);

    int connFd;
    connFd = ::accept(fd, (struct sockaddr *)&clientAddr, &clientAddrLen);

    Log(TRACE) << "Socket accept connection " << connFd;
    if(connFd < 0) {
        THROW_SYS;
    }
    *connAddr = clientAddr;

    return connFd;
}

std::string
TCPSocket::recv(const int connFd) {
    return recv(connFd, recvFlag);
}

std::string
TCPSocket::recv() {
    return recv(fd, recvFlag);
}

std::string
TCPSocket::recv(const int connFd, const int recvFlag) {
    if(connFd < 2) {
        Log(WARN) << "Illegal connection fd " << connFd;
    }
    constexpr size_t msgLength = 8192; // FIXME
    char msg[msgLength];
    const auto size = ::recv(connFd, msg, msgLength, recvFlag);
    if(size <= 0) {
        Log(WARN) << "TCPSocket received nothing";
        return "";
    }
    Log(TRACE) << "Socket received msg";
    return msg;
}

void
TCPSocket::send(const std::string & msg) {
    send(fd, msg, sendFlag);
}

void
TCPSocket::send(const int connFd, const std::string & msg) {
    send(connFd, msg, sendFlag);
}

void
TCPSocket::send(const int connFd, const std::string & msg, const int sendFlag) {
    char content[msg.length() + 1];
    std::strcpy(content, msg.c_str());
    const auto size = ::send(connFd, content, sizeof(content), sendFlag);
    if(size <= 0) {
        Log(WARN) << "TCPSocket received nothing";
    } else {
        Log(TRACE) << "Socket send msg";
    }
}
}
}