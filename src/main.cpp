#include <csignal>
#include <atomic>
static std::atomic<bool> g_running{true};
static void signal_handler(int) { g_running.store(false); }
#include <iostream>
#include <grpcpp/grpcpp.h>
#include <reel_forge.grpc.pb.h>

class ReelForgeServiceImpl final : public reelforge::ReelForge::Service {
    grpc::Status StartEncode(grpc::ServerContext*, const reelforge::EncodeConfig* req, reelforge::JobResponse* resp) override {
        resp->set_success(true); resp->set_job_id("enc-1");
        std::cout << "Encode: " << req->width() << "x" << req->height() << " " << req->bitrate() << "bps\n";
        return grpc::Status::OK;
    }
    grpc::Status StopEncode(grpc::ServerContext*, const reelforge::JobRequest*, reelforge::JobResponse* resp) override {
        resp->set_success(true); return grpc::Status::OK;
    }
    grpc::Status StartDecode(grpc::ServerContext*, const reelforge::DecodeConfig* req, reelforge::JobResponse* resp) override {
        resp->set_success(true); resp->set_job_id("dec-1");
        std::cout << "Decode: " << req->width() << "x" << req->height() << "\n";
        return grpc::Status::OK;
    }
    grpc::Status StopDecode(grpc::ServerContext*, const reelforge::JobRequest*, reelforge::JobResponse* resp) override {
        resp->set_success(true); return grpc::Status::OK;
    }
    grpc::Status GetStatus(grpc::ServerContext*, const reelforge::StatusRequest*, reelforge::StatusResponse* resp) override {
        resp->set_active_jobs(0); resp->set_bytes_processed(0); return grpc::Status::OK;
    }
    grpc::Status HealthCheck(grpc::ServerContext*, const reelforge::HealthRequest*, reelforge::HealthResponse* resp) override {
        resp->set_status("SERVING"); resp->set_version("0.1.0"); return grpc::Status::OK;
    }
};

int main() {
    std::string addr = "0.0.0.0:50053";
    ReelForgeServiceImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    std::cout << "Reel Forge Server on " << addr << "\n";
    while (g_running.load()) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
    std::cout << "Shutting down...\n";
    server->Shutdown();
    std::cout << "Done.\n";
    return 0;
}
