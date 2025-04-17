#pragma once

#include "framework/jsonserver.h"
#include "api/public/putkey.h"
#include "api/public/getkey.h"

class PublicServer : public framework::JsonServer {

private:
    api::PutKey put_key_handler_;
    api::GetKey get_key_handler_;

public:
    PublicServer();
    ~PublicServer() = default;

};
