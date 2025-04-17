
#include "publicserver.h"
#include "privateserver.h"
#include "framework/genericapp.h"
#include <model/store.h>
#include <memory>

int main() {
    model::Store store;
    auto public_server = std::make_unique<PublicServer>(store);
    auto private_server = std::make_unique<PrivateServer>(store);
    framework::GenericApp<PublicServer, PrivateServer> app(crow::LogLevel::Debug, std::move(public_server), std::move(private_server));
    app.run(9001);
    return 0;
} 