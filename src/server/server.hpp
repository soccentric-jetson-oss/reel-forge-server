// SPDX-License-Identifier: MIT
/**
 * @file server.hpp
 * @brief gRPC server wrapper for Reel Forge
 *
 * Manages the gRPC server lifecycle: start, shutdown, and signal handling.
 *
 * @copyright Copyright (c) 2026 SoC Centric LLC
 * @author Sandesh Ghimire
 */

#pragma once

#include <string>
#include <memory>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

namespace reelforge {

/// @brief Wraps a gRPC server with Reel Forge service implementation.
class Server {
public:
    /// @brief Construct a server bound to the given address.
    /// @param address Host:port string (e.g., "127.0.0.1:50053").
    explicit Server(const std::string& address);

    /// @brief Start the gRPC server.
    /// @return OK on success, error status otherwise.
    grpc::Status Start();

    /// @brief Gracefully shut down the server.
    void Shutdown();

    /// @brief Check if the server is currently running.
    bool IsRunning() const;

private:
    std::string address_;
    std::unique_ptr<grpc::Server> server_;
    bool running_{false};
};

} // namespace reelforge
