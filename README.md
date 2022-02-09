## Why does this repo exist?
The purpose of this repo is to provide an example of using gRPC with C++ on Windows (and Linux via a Docker container). I ran into some friction with standard instructions and so I took a different path to simply the setup.

## Installation Notes

### Vcpkg

I found the easiest way to use gRPC with C++ on Windows is to install it via [vcpkg](https://vcpkg.io/en/index.html). This is a Microsoft package management utility which has promise, but still lacks some important package management features such as easily anchoring packages to specific versions (it's possible to anchor a package to a version but it's so onerous from the CLI that it's not
practical. Microsoft has added this ability to their Visual Studio integration only)

Installing vcpkg is painless. Instructions are here:
https://vcpkg.io/en/getting-started.html

The you will need to install both the gRPC and protobuff package. From the command line:

`vcpkg install protobuf`

`vcpkg install grpc`

In order to integrate these packages with Visual Studio (so that all the directories references for includes and libraries are available) simply run this command (more details are in the vcpkg installation instructions):

`vcpkg integrate install`

### Compiling Proto Files

In this example, I created a C++ gRPC server and a Python gRPC test client that calls the server. The interfaces are defined in the proto file which has to be compiled into the native language.

Use the gRPC C++ plugin to generate the code with protoc (protobuf compiler).

You will need to run protoc twice, once to generate the gRPB C++ native service interfaces and a second time to generate the protobuf classes:

`protoc --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin.exe admin.proto`

`protoc --cpp_out=. admin.proto`

The test client is written in Python. Similarly, call protoc twice but with the Python plugin:

`protoc --grpc_out=. --plugin=protoc-gen-grpc=grpc_python_plugin.exe admin.proto`

`protoc --python_out=. admin.proto`

Note: you will need to install gprc module for Python using pip or Anaconda. If you want to you could call protoc directly
from python like so:

`python -m grpc_tools.protoc --python_out=. --grpc_python_out=. admin.proto`

### CMake

CMake is awesome. For those who have not used it, it's very helpful. It will autogenerate the Visual Studio solutions files
with all the proper library references. It's great if you are building cross platform C++ (Windows and Linux) software. CMake will auto generate the make files on Ubuntu for example. I provide an example of this in the Docker container that runs the grpc_cpp service.

Take a glance at the CMakeLists.txt file which has all the configuration for CMake. Notice on Windows we need to include both the *grpc++.lib* and *WS2_32.lib* (WinSock) libraries.

You can generate the Visual Studio solution file with the following  command. Since we are using vcpkg, you need to add a reference to the
CMake toolchain file. Make sure the path to vcpkg is correct for you.

`mkdir build`

`cd build`

`cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\git\vcpkg\scripts\buildsystems\vcpkg.cmake`

### Docker Integration

To demostrate running this on Linux, I created a Docker container based off Ubuntu.

From the root directory in the repo there is a Dockerfile you can build simply with this command:
`docker build .`

add  --no-cache if you want to rebuild the entire container like so:
`docker build . --no-cache`


The compose file expects the container to be tagged rbaxter\grpc_cpp so you could either change the compose file to point to the proper container or tag the container with this name:

`docker tag <image_id> rbaxter\grpc_cpp:latest`

I included a docker-compose.yml to orchestrate the stack. You can run it with the following command:
`docker compose up`

