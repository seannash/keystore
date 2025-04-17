
#include "keystore/publicserver.h"
#include "keystore/privateserver.h"
#include "keystore/context.h"
#include "framework/genericappwithcontext.h"
#include <memory>

int main() {
    auto context = keystore::Context::Builder()
        .withId(9001)
        .build();
    std::cout << "Context ID: " << context->id() << std::endl;
    framework::GenericAppWithContext<keystore::Context, keystore::PublicServer, keystore::PrivateServer> app(
        crow::LogLevel::Debug,
        std::move(context));
    app.run(9001);
    return 0;
} 