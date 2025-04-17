#include "privateserver.h"

PrivateServer::PrivateServer(Context& context)
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}
