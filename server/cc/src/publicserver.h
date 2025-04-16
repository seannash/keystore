#pragma once

#include "framework/jsonserver.h"
#include "api/ping.h"   

class PublicServer : public framework::JsonServer {

private:
    api::PingHandler ping_handler_;

public:
    PublicServer();
    ~PublicServer() = default;

};
