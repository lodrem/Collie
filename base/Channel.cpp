#include "../Httpd.hpp"
#include "Channel.hpp"
#include "EventLoop.hpp"


namespace MiniHttp { namespace Base {

Channel::Channel(std::shared_ptr<EventLoop> eventLoop, const int& fd) :
    inEventLoop(false),
    fd(fd),
    events(0),
    eventLoop(eventLoop) {
    Log(TRACE) << "Channel " << fd << " constructing";
    closeCallback = [](const int fd) {
        // TODO remove channel
        Log(TRACE) << "Close channel " << fd;
    };
    errorCallback = [](const int fd) {
        // TODO remove channel
        Log(TRACE) << "Channel " << fd << " meets ERROR";
    };
}

Channel::~Channel() {
    Log(TRACE) << "Channel " << fd << " destructing";
}

void Channel::goInEventLoop() {
    if( ! inEventLoop) {
        inEventLoop = true;
    } else {
        Log(WARN) << "Channel " << fd << " is already in a EventLoop";
    }
}

void Channel::goOutEventLoop() {
    if(inEventLoop) {
        inEventLoop = false;
    } else {
        Log(WARN) << "Channel " << fd << " is not in a EventLoop";
    }
}

void Channel::activate(const unsigned & revents) const {
    if(Event::isError(revents)) {
        Log(TRACE) << "Activate ERROR callback with events " << revents;
        errorCallback(fd);
    } else if(Event::isClose(revents)) {
        Log(TRACE) << "Activate CLOSE callback with events" << revents;
        closeCallback(fd);
    } else if(Event::isRead(revents)) {
        if(isRead()) {
            Log(TRACE) << "Activate READ callback with events " << revents;
            readCallback(fd);
        } else {
            Log(WARN) << "READ callback is not available";
        }
    } else if(Event::isWrite(revents)) {
        if(isWrite()) {
            Log(TRACE) << "Activate WRITE callback with events" << revents;
            writeCallback(fd);
        } else {
            Log(WARN) << "WRITE callback is not available";
        }
    }
}

void Channel::update() const {
    eventLoop->updateChannel(fd);
}

void Channel::remove() const {
    close(fd);  // FIXME
    eventLoop->removeChannel(fd);
}

}}
