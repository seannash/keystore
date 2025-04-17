
#include "publicserver.h"
#include "privateserver.h"
#include "framework/genericapp.h"
#include <context.h>
#include <memory>

int main() {
    Context context(1);
    auto public_server = std::make_unique<PublicServer>(context);
    auto private_server = std::make_unique<PrivateServer>(context);
    framework::GenericApp<PublicServer, PrivateServer> app(crow::LogLevel::Debug, std::move(public_server), std::move(private_server));
    app.run(9001);
    return 0;
} 