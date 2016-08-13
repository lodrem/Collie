#ifndef COLLIE_TCP_STREAM_H_
#define COLLIE_TCP_STREAM_H_

#include <memory>
#include "../base/String.h"
#include "../util/NonCopyable.h"
#include "TCPSocket.h"

namespace collie {

namespace tcp {

class TCPStream : public util::NonCopyable {
 public:
  TCPStream(std::unique_ptr<TCPSocket>) noexcept;
  virtual ~TCPStream();

  virtual void Write(const String&) const;
  virtual String Read(const SizeType size = 0) const;
  virtual String ReadUntil(const String&) const;
  virtual String ReadLine() const;

  std::shared_ptr<const InetAddress> LocalAddress() const noexcept {
    return socket->LocalAddress();
  }
  std::shared_ptr<const InetAddress> PeerAddress() const noexcept {
    return socket->PeerAddress();
  }

  void SetReadSize(SizeType size) noexcept { read_size = size; }
  SizeType ReadSize() const noexcept { return read_size; }

 private:
  const std::unique_ptr<TCPSocket> socket;
  SizeType read_size;
};
}
}

#endif /* COLLIE_TCP_STREAM_H_ */