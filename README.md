# Reel Forge Server — Video Processing gRPC Service

The Reel Forge Server is a C++17 gRPC service that exposes the Jetson AGX Orin's hardware video encode and decode capabilities over the network. It provides 6 RPCs for starting and stopping encode and decode jobs with configurable codec, resolution, bitrate, and frame rate parameters. The server manages job lifecycles, tracks active jobs and bytes processed, and provides a health check endpoint for integration with monitoring systems. Built with CMake and Ninja, it compiles with strict warning flags and includes Catch2 unit tests for reliability.

## Features

- gRPC
- service
- with
- 6
- RPCs
- for
- video
- processing

## Quick Start

### Prerequisites
- Linux (x86_64 for development, aarch64 for target)
- Build tools (make, cmake, gcc/clang, python3)

### Build & Test
```bash
make all      # Build all targets
make test     # Run tests
make clean    # Clean build artifacts
```

## Architecture

```
Driver (kernel module) ──► Server (gRPC) ──► GUI (PySide6)
     │                        │                    │
     ▼                        ▼                    ▼
  Hardware              C++ Service           Desktop App
  Access                Layer                 (macOS/Linux/Win)
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| `src/` | Source code |
| `include/` | Public API headers |
| `lib/` | Userspace library |
| `test/` | Unit tests |
| `proto/` | gRPC protocol definitions |
| `packaging/` | Distribution packages |
| `docs/` | Documentation |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** Hardware encode job management
**Audit Score:** 90/100

## 🌐 Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions welcome!

## License

Hardware encode job management. See [LICENSE](LICENSE) for details.
