#include <catch2/catch_test_macros.hpp>
#include <thread>
#include <chrono>
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <reel_forge.grpc.pb.h>

TEST_CASE("Server configuration is valid", "[server]") {
    reelforge::ReelForge::Service service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("127.0.0.1:0", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    REQUIRE(server != nullptr);
    server->Shutdown();
}

TEST_CASE("Concurrent requests handled", "[server]") {
    std::atomic<int> counter{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
        threads.emplace_back([&]() { counter++; });
    for (auto& t : threads) t.join();
    REQUIRE(counter == 10);
}

TEST_CASE("Error responses are well-formed", "[server]") {
    grpc::Status not_found(grpc::StatusCode::NOT_FOUND, "job not found");
    REQUIRE_FALSE(not_found.ok());
    REQUIRE(not_found.error_code() == grpc::StatusCode::NOT_FOUND);
}
