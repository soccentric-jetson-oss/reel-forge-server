// SPDX-License-Identifier: MIT
// Copyright (c) 2026 SoC Centric LLC
//
// reel_forge_service.cpp - gRPC service implementation
//
/// @brief Implements encode/decode pipeline management with simulated
///        hardware-accelerated video processing.

#include "service/reel_forge_service.hpp"
#include <iostream>

namespace reelforge {

grpc::Status ReelForgeServiceImpl::StartEncode(
    grpc::ServerContext*,
    const EncodeConfig* request,
    JobResponse* response)
{
    active_jobs_++;
    response->set_success(true);
    response->set_job_id("enc-" + std::to_string(active_jobs_.load()));
    std::cout << "Encode: " << request->width() << "x" << request->height()
              << " " << request->bitrate() << "bps\n";
    return grpc::Status::OK;
}

grpc::Status ReelForgeServiceImpl::StopEncode(
    grpc::ServerContext*,
    const JobRequest*,
    JobResponse* response)
{
    if (active_jobs_ > 0) active_jobs_--;
    response->set_success(true);
    return grpc::Status::OK;
}

grpc::Status ReelForgeServiceImpl::StartDecode(
    grpc::ServerContext*,
    const DecodeConfig* request,
    JobResponse* response)
{
    active_jobs_++;
    response->set_success(true);
    response->set_job_id("dec-" + std::to_string(active_jobs_.load()));
    std::cout << "Decode: " << request->width() << "x" << request->height() << "\n";
    return grpc::Status::OK;
}

grpc::Status ReelForgeServiceImpl::StopDecode(
    grpc::ServerContext*,
    const JobRequest*,
    JobResponse* response)
{
    if (active_jobs_ > 0) active_jobs_--;
    response->set_success(true);
    return grpc::Status::OK;
}

grpc::Status ReelForgeServiceImpl::GetStatus(
    grpc::ServerContext*,
    const StatusRequest*,
    StatusResponse* response)
{
    response->set_active_jobs(active_jobs_.load());
    response->set_bytes_processed(bytes_processed_.load());
    return grpc::Status::OK;
}

grpc::Status ReelForgeServiceImpl::HealthCheck(
    grpc::ServerContext*,
    const HealthRequest*,
    HealthResponse* response)
{
    response->set_status("SERVING");
    response->set_version("0.1.0");
    return grpc::Status::OK;
}

} // namespace reelforge
