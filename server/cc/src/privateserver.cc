#include "privateserver.h"

PrivateServer::PrivateServer(model::Store& store)
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}
