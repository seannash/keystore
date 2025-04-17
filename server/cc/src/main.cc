
#include "publicserver.h"
#include "privateserver.h"
#include "context.h"
#include "framework/genericappwithcontext.h"
#include <memory>

int main() {
    auto context = Context::Builder()
        .withId(1)
        .build();
    framework::GenericAppWithContext<Context, PublicServer, PrivateServer> app(
        crow::LogLevel::Debug,
        std::move(context));
    app.run(9001);
    return 0;
} 