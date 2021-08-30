#include "internal/server.hpp"
#include "internal/cmdline.h"
#include "Msg_TestService_Stream.hpp"

int main(int argc, char **argv)
{
    cmdline::parser args;
    args.add<std::string>("port", 'p', "server port", false, "22222");
    args.parse_check(argc, argv);
    ServerImpl gserver;
    auto service = new test::TestService::AsyncService();
    gserver.RegisterService(service);
    gserver.RegisterMsg(new Msg_TestService_Stream(service));
    gserver.Run("0.0.0.0", args.get<std::string>("port"));
    gserver.Stop();
    return 0;
}
