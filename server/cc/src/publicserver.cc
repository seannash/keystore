#include "publicserver.h"

PublicServer::PublicServer()
: framework::JsonServer()
, put_key_handler_()
, get_key_handler_() {
    REGISTER_HANDLER("put", put_key_handler_);
    REGISTER_HANDLER("get", get_key_handler_);
}
