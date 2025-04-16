#pragma once

#include "framework/jsonserver.h"
#include "api/ping.h"   

class Server : public framework::JsonServer {

private:
    api::PingHandler ping_handler_;

public:
    Server();
    ~Server() = default;

};
