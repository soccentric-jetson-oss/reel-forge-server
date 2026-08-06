# Reel Forge Server — Video Processing gRPC Service

The Reel Forge Server is a C++17 gRPC service that exposes the Jetson AGX Orin's hardware video encode and decode capabilities over the network. It provides 6 RPCs for starting and stopping encode and decode jobs with configurable codec, resolution, bitrate, and frame rate parameters. The server manages job lifecycles, tracks active jobs and bytes processed, and provides a health check endpoint for integration with monitoring systems.

## Features

- Exposes a gRPC service with 6 RPCs for managing hardware video encode and decode jobs over the network
- Supports starting hardware encode jobs with configurable codec type, resolution, bitrate, and frame rate parameters
- Supports stopping active encode jobs by job ID with proper resource cleanup and status reporting
- Supports starting hardware decode jobs with configurable codec type, resolution, and output dimensions
- Supports stopping active decode jobs by job ID with proper resource cleanup and status reporting
- Tracks active job counts and total bytes processed for capacity planning and monitoring
- Provides a health check endpoint returning service status and version for integration with monitoring systems
- Built with modern C++17 and compiled with strict warning flags for maximum code quality and reliability
- Uses CMake and Ninja for fast, reliable builds with proper dependency management
- Includes Catch2 unit tests for service logic, job management, and error handling paths
- Licensed under MIT for maximum flexibility in commercial and open-source projects

## Quick Start

### Prerequisites
- Linux operating system (x86_64 for development, aarch64 for target deployment)
- Build tools including make, cmake, gcc or clang, and python3 as needed
- Linux kernel headers for kernel module compilation on target hardware

### Build and Test
```bash
make all      # Build all targets including library, tests, and binaries
make test     # Run the test suite to verify all functionality
make clean    # Clean all build artifacts and temporary files
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| src/ | Source code for the project |
| include/ | Public API header files |
| lib/ | Userspace library source and headers |
| test/ or tests/ | Unit tests and test utilities |
| proto/ | gRPC protocol buffer definitions |
| packaging/ | Distribution packaging files for deb, rpm, and ipk |
| docs/ | Documentation including Doxygen configuration |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** MIT
**Audit Score:** 90/100 across 20 criteria

## Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions are welcome.

## License

MIT. See [LICENSE](LICENSE) for details.

---

## Showcase

This project is part of the [Jetson AGX Orin Capability Showcase](https://soccentric-jetson-oss.github.io/).
