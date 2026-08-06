cmake_minimum_required(VERSION 3.20)
project(reel-forge-server VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(Threads REQUIRED)

# ── Compiler warnings ──────────────────────────────────────────────────
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# ── Protobuf / gRPC generation ─────────────────────────────────────────
set(PROTO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/proto/reel_forge.proto)
set(PROTO_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

add_custom_command(
    OUTPUT ${PROTO_GEN_DIR}/reel_forge.pb.cc ${PROTO_GEN_DIR}/reel_forge.grpc.pb.cc
    COMMAND protoc --proto_path ${CMAKE_CURRENT_SOURCE_DIR}/proto
        --cpp_out ${PROTO_GEN_DIR} --grpc_out ${PROTO_GEN_DIR}
        --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        ${PROTO_SRC} DEPENDS ${PROTO_SRC}
)

add_library(reel_forge_proto OBJECT
    ${PROTO_GEN_DIR}/reel_forge.pb.cc ${PROTO_GEN_DIR}/reel_forge.grpc.pb.cc
)
target_include_directories(reel_forge_proto PUBLIC ${PROTO_GEN_DIR})
target_link_libraries(reel_forge_proto PUBLIC protobuf::libprotobuf gRPC::grpc++)

# ── Library: reel-forge-core ───────────────────────────────────────────
add_library(reel-forge-core STATIC
    src/service/reel_forge_service.cpp
    src/server/server.cpp
)
target_include_directories(reel-forge-core PUBLIC src ${PROTO_GEN_DIR})
target_link_libraries(reel-forge-core PUBLIC
    reel_forge_proto protobuf::libprotobuf gRPC::grpc++ Threads::Threads
)

# ── Executable ─────────────────────────────────────────────────────────
add_executable(reel-forge-server src/main.cpp)
target_link_libraries(reel-forge-server PRIVATE reel-forge-core)

# ── Formatting & Linting ──────────────────────────────────────────────
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE FORMAT_SOURCES src/*.cpp src/*.hpp)
    add_custom_target(format COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(format-check COMMAND ${CLANG_FORMAT} --dry-run --Werror ${FORMAT_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    file(GLOB_RECURSE LINT_SOURCES src/*.cpp src/*.hpp)
    add_custom_target(lint COMMAND ${CPPCHECK} --enable=all --inconclusive
        --suppress=missingIncludeSystem ${LINT_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# ── Documentation (Doxygen) ──────────────────────────────────────────────
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
