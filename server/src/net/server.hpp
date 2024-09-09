#ifndef NET_SERVER_HPP
#define NET_SERVER_HPP

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../log/logger.hpp"

using boost::asio::ip::tcp;

namespace Net
{
    enum ServerError
    {
        Success,
        Generic,
        OpenFailed,
        BindFailed,
        ListenFailed,
        AcceptFailed,
        ReadFailed,
        ClientReadFailed
    };

    // To get a server error message, use SERVER_ERR_MSGS[ServerError::...]
    const std::string SERVER_ERR_MSGS[] = {
        "The operation was successful.",
        "A generic error occurred.",
        "Failed to open acceptor.",
        "Failed to bind acceptor to given endpoint.",
        "Failed to listen on acceptor.",
        "Failed to accept client.",
        "Failed waiting to read from client.",
    };

    class Server
    {
        bool active;

        boost::asio::io_service io_service{};
        tcp::endpoint endp;
        tcp::acceptor acceptor{io_service};
        
        std::vector<tcp::socket> clients;

        void accept_client(std::shared_ptr<tcp::socket> client, const boost::system::error_code& err);
        void read_event(const boost::system::error_code& err);

        public:
            Server(std::string hostname, uint16_t port);
            ServerError start();
    };
}

#endif