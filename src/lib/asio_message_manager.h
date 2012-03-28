// Copyright (C) 2012  JINMEI Tatuya
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __QUERYPERF_ASIO_MESSAGE_MANAGER_H
#define __QUERYPERF_ASIO_MESSAGE_MANAGER_H 1

#include <message_manager.h>

#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <string>

#include <stdint.h>

namespace Queryperf {

class ASIOMessageSocket : public MessageSocket {
protected:
    ASIOMessageSocket() {}
public:
    virtual ~ASIOMessageSocket() {}
    virtual void send(const void* data, size_t datalen) = 0;
    virtual void cancel() = 0;

    /// \brief Return the native socket descriptor.
    ///
    /// Provided for debugging purposes only.
    virtual int native() = 0;
};

class ASIOMessageManager : public MessageManager {
public:
    ASIOMessageManager();

    virtual ~ASIOMessageManager();

    virtual MessageSocket* createMessageSocket(
        int proto, const std::string& address, uint16_t port,
        void* recvbuf, size_t recvbuf_len,
        MessageSocket::Callback callback);

    virtual MessageTimer* createMessageTimer(MessageTimer::Callback callback);

    virtual void run();

    virtual void stop();

    /// \brief Returns a TCP port number likely to be available at the time of
    /// call.
    uint16_t getNextTCPPort();

private:
    struct ASIOMessageManagerImpl;
    ASIOMessageManagerImpl* impl_;
};

} // end of QueryPerf

#endif // __QUERYPERF_ASIO_MESSAGE_MANAGER_H 

// Local Variables:
// mode: c++
// End:
