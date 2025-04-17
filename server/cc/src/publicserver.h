#pragma once

#include "framework/jsonserver.h"
#include "api/put.h"
#include "api/get.h"
#include <context.h>

class PublicServer : public framework::JsonServer {

private:
    api::Put put_key_handler_;
    api::Get get_key_handler_;

public:
    PublicServer(Context& context);
    ~PublicServer() = default;

};
