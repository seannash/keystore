#pragma once

#include "framework/jsonserver.h"
#include "api/ping.h"   
#include <context.h>

class PrivateServer : public framework::JsonServer {

private:
    api::PingHandler ping_handler_;

public:
    PrivateServer(Context& context);
    ~PrivateServer() = default;

};
