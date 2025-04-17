#pragma once

#include "framework/jsonserver.h"
#include "api/ping.h"   
#include <model/store.h>
class PrivateServer : public framework::JsonServer {

private:
    api::PingHandler ping_handler_;

public:
    PrivateServer(model::Store& store);
    ~PrivateServer() = default;

};
