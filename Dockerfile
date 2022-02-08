FROM ubuntu:20.04
RUN apt-get update -y
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y git make gcc g++ nano cmake curl zip unzip tar pkg-config

RUN mkdir /src/vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git /src/vcpkg
WORKDIR /src/vcpkg
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install
RUN ./vcpkg update
RUN ./vcpkg install grpc
RUN ./vcpkg install protobuf

# need this to call protoc
ENV PATH="/src/vcpkg/packages/protobuf_x64-linux/tools/protobuf:${PATH}"

COPY ./ /src/grpc_cpp

WORKDIR /src/grpc_cpp/protos
RUN protoc --grpc_out=. --plugin=protoc-gen-grpc=/src/vcpkg/packages/grpc_x64-linux/tools/grpc/grpc_cpp_plugin admin.proto
RUN protoc --cpp_out=. admin.proto
RUN protoc --grpc_out=. --plugin=protoc-gen-grpc=/src/vcpkg/packages/grpc_x64-linux/tools/grpc/grpc_python_plugin admin.proto
RUN protoc --python_out=. admin.proto

RUN mkdir /src/grcp_cpp/build_ubuntu
WORKDIR /src/grcp_cpp/build_ubuntu
RUN apt-get install -y make
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=/src/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN make

