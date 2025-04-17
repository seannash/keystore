#include "publicserver.h"

PublicServer::PublicServer(Context& context)
: framework::JsonServer()
, put_key_handler_(context)
, get_key_handler_(context) {
    REGISTER_HANDLER("put", put_key_handler_);
    REGISTER_HANDLER("get", get_key_handler_);
}
