#pragma once

#include "framework/jsonserver.h"
#include "keystore/api/put.h"
#include "keystore/api/get.h"
#include <keystore/context.h>

namespace keystore {    

class PublicServer : public framework::JsonServer {

private:
    api::Put put_key_handler_;
    api::Get get_key_handler_;

public:
    PublicServer(Context& context);
    ~PublicServer() = default;

};

} // namespace keystore
