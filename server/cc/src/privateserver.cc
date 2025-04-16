#include "privateserver.h"

PrivateServer::PrivateServer()
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}
