// SPDX-License-Identifier: MIT
// Copyright (c) 2026 SoC Centric LLC
//
// main.cpp - Entry point for Reel Forge gRPC server
//
/// @brief Thin entry point: parses CLI args, starts server, waits for signal.

#include "server/server.hpp"
#include <iostream>
#include <csignal>
#include <atomic>
#include <thread>

static std::atomic<bool> g_running{true};
static void signal_handler(int) { g_running.store(false); }

int main(int argc, char** argv) {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    std::string addr = "127.0.0.1:50053";
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--address" && i + 1 < argc) addr = argv[++i];
    }

    reelforge::Server server(addr);
    auto status = server.Start();
    if (!status.ok()) {
        std::cerr << "Failed: " << status.error_message() << "\n";
        return 1;
    }

    while (g_running.load())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    server.Shutdown();
    return 0;
}
