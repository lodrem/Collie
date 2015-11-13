#include "../../include/Global.hpp"
#include "../../include/tcp/TCPConnection.hpp"
#include "../../include/tcp/TCPSocket.hpp"
#include "../../include/SocketAddress.hpp"
#include "../../include/event/EventLoop.hpp"
#include "../../include/event/Channel.hpp"
#include <functional>
#include <algorithm>
#include <future>

namespace Collie {
namespace TCP {

TCPConnection::TCPConnection(std::shared_ptr<Event::Channel> channel,
                             std::shared_ptr<SocketAddress> localAddr,
                             std::shared_ptr<SocketAddress> remoteAddr)
    : connected(true),
      channel(channel),
      localAddr(localAddr),
      remoteAddr(remoteAddr) {

    // set channel callback and enable reading
    channel->setReadCallback(std::bind(&TCPConnection::handleRead, this));
    channel->setWriteCallback(std::bind(&TCPConnection::handleWrite, this));
    channel->setCloseCallback(std::bind(&TCPConnection::handleClose, this));
    channel->setErrorCallback(std::bind(&TCPConnection::handleError, this));
    channel->enableRead();
    channel->enableWrite();
    Log(TRACE) << "TCP Connection constructing";
}

TCPConnection::~TCPConnection() { Log(TRACE) << "TCP Connection destructing"; }

void
TCPConnection::disconnect() {
    connected = false;
    if(outputBuffer.empty()) shutdown();
}

void
TCPConnection::shutdown() {
    channel->remove();
    if(shutdownCallback) shutdownCallback(shared_from_this());
}

std::string
TCPConnection::recvAll() {
    // FIXME
    std::string buffer;
    std::swap(buffer, inputBuffer);
    return buffer;
}

void
TCPConnection::send(const std::string & buffer) {
    // FIXME
    outputBuffer += buffer;
    channel->enableWrite();
}

void
TCPConnection::handleRead() {
    const auto content = TCPSocket::recv(channel->getFd(), 0);
    if(!content.empty()) {
        inputBuffer += content;
        messageCallback(shared_from_this());
        channel->disableRead();
    } else {
        handleClose();
    }
    if(!connected && outputBuffer.empty()) shutdown();
}

void
TCPConnection::handleWrite() {
    if(!outputBuffer.empty()) {
        // FIXME slice outputBuffer
        TCPSocket::send(channel->getFd(), outputBuffer, 0);
        outputBuffer.clear();
    }
    channel->disableWrite();
    channel->enableRead();
    if(!connected) shutdown();
}

void
TCPConnection::handleClose() {
    disconnect();
}

void
TCPConnection::handleError() {
    disconnect();
}
}
}