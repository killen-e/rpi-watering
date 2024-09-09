#include "server.hpp"

namespace Net
{
    Server::Server(std::string hostname, uint16_t port)
    {
        endp = tcp::endpoint(boost::asio::ip::make_address(hostname), port);
        active = false;
    }

    ServerError Server::start()
    {
        ServerError start_err = ServerError::Success;

        boost::system::error_code err_c;

        // Initialize acceptor by opening it and binding it to the endpoint.
        acceptor.open(endp.protocol(), err_c);

        if (err_c == boost::system::errc::success) {
            acceptor.bind(endp, err_c);

            if (err_c == boost::system::errc::success) {
                acceptor.listen(boost::asio::socket_base::max_listen_connections, err_c);

                if (err_c == boost::system::errc::success) {
                    Log::write("Starting server. Bound to hostname (" + endp.address().to_string() + ") on port (" + std::to_string(endp.port()) + ")", false);
                    active = true;

                    tcp::socket client{io_service};
                    std::shared_ptr<tcp::socket> client_ptr = std::make_shared<tcp::socket>(std::move(client));              
                    acceptor.async_accept(client, [this, client_ptr] (const auto& err) {
                        accept_client(client_ptr, err);
                    });

                    acceptor.async_wait(tcp::acceptor::wait_read, [this] (const auto& err) {
                        read_event(err);
                    });

                    io_service.run();

                        
                } else {
                    start_err = ServerError::ListenFailed;
                }
            } else {
                start_err = ServerError::BindFailed;
            }
        } else {
            start_err = ServerError::OpenFailed;
        }

        return start_err;
    }

    void Server::accept_client(std::shared_ptr<tcp::socket> client, const boost::system::error_code& err)
    {
        if (err == boost::system::errc::success) {
            Log::write("Accepted client!", false);
            this->clients.push_back(std::move(*client));
        } else {
            Log::write("Failed to accept client.", true);
        }
    }

    void Server::read_event(const boost::system::error_code& err)
    {
        Log::write("help me please", false);
        /*
        ret = ServerError::Success;

        if (err == boost::system::errc::success) {
            Log::write("Some client is ready to be read from. Finding the client...", false);

            for (auto it = clients.begin(); it != clients.end(); it++) {

                boost::system::error_code err_c;
                std::size_t msg_len = it->available(err_c);

                if (err_c == boost::system::errc::success) {
                    boost::asio::streambuf buffer;
                    boost::system::error_code err_c;
                    it->read_some(buffer, err_c);

                    if (err_c == boost::system::errc::success) {
                        std::istream is(&buffer);
                        std::string message;
                        is >> message;
                        Log::write(message, false);
                    } else {
                        ret = ServerError::ClientReadFailed;
                    }
                } else {
                    ret = ServerError::ReadFailed;
                    break;
                }
            }
        } else {
            ret = ServerError::ReadFailed;
        }
        */
    }
}