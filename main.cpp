#include <iostream>

#include <sstream>
#include <thread>

#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>

#include <RSocket.h>
#include <transports/tcp/TcpConnectionAcceptor.h>

DEFINE_int32(port, 9898, "port to connect to");
using namespace rsocket;
using namespace yarpl::flowable;
class HelloStreamRequestResponder : public rsocket::RSocketResponder {
public:
    /// Handles a new inbound Stream requested by the other end.
    std::shared_ptr<Flowable<rsocket::Payload>> handleRequestStream(
            rsocket::Payload request,
            rsocket::StreamId streamId) override {
        std::cout << "HelloStreamRequestResponder.handleRequestStream " << request
                  << std::endl;

        // string from payload data
        auto requestString = request.moveDataToString();

        return Flowable<>::range(1, 10)->map(
                [name = std::move(requestString)](int64_t v) {
                    std::stringstream ss;
                    ss << "Hello " << name << " " << v << "!";
                    std::string s = ss.str();
                    return Payload(s, "metadata");
                });
    }
};

int main(int argc, char **argv) {
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;
    folly::init(&argc, &argv);

    TcpConnectionAcceptor::Options opts;
    opts.address = folly::SocketAddress("::", FLAGS_port);
    opts.threads = 2;

    // RSocket server accepting on TCP
    auto rs = RSocket::createServer(
            std::make_unique<TcpConnectionAcceptor>(std::move(opts)));

    auto rawRs = rs.get();
    auto serverThread = std::thread([=] {
        // start accepting connections
        rawRs->startAndPark([](const rsocket::SetupParameters &params)
        ->  std::shared_ptr<RSocketResponder> {
            std::cout << "server.startAndPark " << params << std::endl;
                return std::make_unique<HelloStreamRequestResponder>(); // create connection to rtmp server
         //   return std::make_shared<HelloStreamRequestResponder>();
        });
    });

    // Wait for a newline on the console to terminate the server.

    // @todo: luanch  all other listners herer
    std::getchar();

    rs->unpark();
    serverThread.join();

    return 0;
}
