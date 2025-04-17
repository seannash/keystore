#include "publicserver.h"

PublicServer::PublicServer(model::Store& store)
: framework::JsonServer()
, put_key_handler_(store)
, get_key_handler_(store) {
    REGISTER_HANDLER("put", put_key_handler_);
    REGISTER_HANDLER("get", get_key_handler_);
}
