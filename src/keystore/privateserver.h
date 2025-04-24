#pragma once

#include "framework/jsonserver.h"
#include "keystore/api/ping.h"   
#include <keystore/context.h>

namespace keystore {

class PrivateServer : public framework::JsonServer {

private:
    api::PingHandler ping_handler_;

public:
    PrivateServer(Context& context);
    ~PrivateServer() = default;

};

} // namespace keystore