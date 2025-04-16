#include "publicserver.h"

PublicServer::PublicServer()
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}
