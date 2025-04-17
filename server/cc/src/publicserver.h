#pragma once

#include "framework/jsonserver.h"
#include "api/public/put.h"
#include "api/public/get.h"
#include <model/store.h>

class PublicServer : public framework::JsonServer {

private:
    api::Put put_key_handler_;
    api::Get get_key_handler_;

public:
    PublicServer(model::Store& store);
    ~PublicServer() = default;

};
