#include "privateserver.h"

namespace keystore {

PrivateServer::PrivateServer(Context& context)
: framework::JsonServer()
, ping_handler_() {
    REGISTER_HANDLER("Ping", ping_handler_);
}

} // namespace keystore
