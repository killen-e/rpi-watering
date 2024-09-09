#include "net/server.hpp"
#include "log/logger.hpp"

int main()
{
    Net::Server server{"127.0.0.1", 1234};
    Net::ServerError err = server.start();
    Log::write(Net::SERVER_ERR_MSGS[err], err != Net::ServerError::Success ? true : false);
    return 0;
}