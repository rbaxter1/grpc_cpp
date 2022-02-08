cmake_minimum_required(VERSION 3.0)

project(grpc_cpp)

set(PROTOS_DIR protos)

include_directories(${PROTOS_DIR})

find_package(Protobuf CONFIG REQUIRED)
find_package(grpc CONFIG REQUIRED)

add_executable(grpc_cpp
    main.cpp
    AdminImpl.cpp
    ${PROTOS_DIR}/admin.grpc.pb.cc
    ${PROTOS_DIR}/admin.pb.cc)

if(WIN32)
    target_link_libraries(grpc_cpp PRIVATE ws2_32 gRPC::grpc++)
else()
    target_link_libraries(grpc_cpp PRIVATE gRPC::grpc++)
endif()















