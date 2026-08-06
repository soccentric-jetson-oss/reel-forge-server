// SPDX-License-Identifier: MIT
// Copyright (c) 2026 SoC Centric LLC
//
// reel_forge_service.hpp - gRPC service for Reel Forge
//
/// @brief Declares ReelForgeServiceImpl implementing encode/decode
///        pipeline management and health check RPCs.

#pragma once

#include <reel_forge.grpc.pb.h>
#include <grpcpp/grpcpp.h>
#include <atomic>

namespace reelforge {

class ReelForgeServiceImpl final : public ReelForge::Service {
public:
    grpc::Status StartEncode(grpc::ServerContext* context,
                             const EncodeConfig* request,
                             JobResponse* response) override;

    grpc::Status StopEncode(grpc::ServerContext* context,
                            const JobRequest* request,
                            JobResponse* response) override;

    grpc::Status StartDecode(grpc::ServerContext* context,
                             const DecodeConfig* request,
                             JobResponse* response) override;

    grpc::Status StopDecode(grpc::ServerContext* context,
                            const JobRequest* request,
                            JobResponse* response) override;

    grpc::Status GetStatus(grpc::ServerContext* context,
                           const StatusRequest* request,
                           StatusResponse* response) override;

    grpc::Status HealthCheck(grpc::ServerContext* context,
                             const HealthRequest* request,
                             HealthResponse* response) override;

private:
    std::atomic<int> active_jobs_{0};
    std::atomic<uint64_t> bytes_processed_{0};
};

} // namespace reelforge
