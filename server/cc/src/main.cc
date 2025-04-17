
#include "publicserver.h"
#include "privateserver.h"
#include "framework/genericapp.h"

int main() {    
    framework::GenericApp<PublicServer, PrivateServer> app(crow::LogLevel::Debug);
    app.run(9001);
    return 0;
} 