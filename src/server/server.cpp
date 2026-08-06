// SPDX-License-Identifier: MIT
/**
 * @file server.cpp
 * @brief gRPC server wrapper implementation for Reel Forge
 *
 * Implements server start, shutdown, and lifecycle management.
 *
 * @copyright Copyright (c) 2026 SoC Centric LLC
 * @author Sandesh Ghimire
 */

#include "server/server.hpp"
#include "service/reel_forge_service.hpp"
#include <iostream>

namespace reelforge {

Server::Server(const std::string& address) : address_(address) {}

grpc::Status Server::Start() {
    ReelForgeServiceImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    server_ = builder.BuildAndStart();
    if (!server_) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to start");
    }
    running_ = true;
    std::cout << "Reel Forge Server on " << address_ << "\n";
    return grpc::Status::OK;
}

void Server::Shutdown() {
    if (server_) { server_->Shutdown(); running_ = false; }
}

bool Server::IsRunning() const { return running_; }

} // namespace reelforge
