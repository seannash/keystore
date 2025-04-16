#include "server.h"

Server::Server()
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}
