#pragma once

#include "genericapp.h"
#include <memory>

namespace framework {

template<typename Context, typename PublicServer, typename PrivateServer>
class GenericAppWithContext : public GenericApp<PublicServer, PrivateServer> {
private:
    std::unique_ptr<Context> context_;

public:
    GenericAppWithContext(
        crow::LogLevel loglevel,
        std::unique_ptr<Context> context);

    Context& context();
};

template<typename Context, typename PublicServer, typename PrivateServer>
GenericAppWithContext<Context, PublicServer, PrivateServer>::GenericAppWithContext(
    crow::LogLevel loglevel,
    std::unique_ptr<Context> context)
: GenericApp<PublicServer, PrivateServer>(
    loglevel,
    std::move(std::make_unique<PublicServer>(*context)),
    std::move(std::make_unique<PrivateServer>(*context)))
, context_(std::move(context)) {

}

} // namespace framework 