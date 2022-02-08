I found the easiest way to use gRPC with c++ is install it via vcpkg. This is a Mircosoft package management
utility which has promise, but still lacks some import package management features such as easily specifying
versions (it's possible to anchor a package to a version but it's so onerous from the CLI that it's not
practical. Microsoft has added this ability to their Visual Studio integration... of course)

Install vcpgk. It's painless. Instructions here:
https://vcpkg.io/en/getting-started.html

For this template, you will need to install both gRPC and protobuff. From the command line:
vcpkg install protobuf
vcpkg install grpc

In order to integrate these packages with Visual Studio (so that all the directories references for 
includes and libraries are available), do this:
vcpkg integrate install

We are creating a c++ client, so we need to use the grpc c++ plugin to generate the code with protoc (the protobuf compiler).
You will need to run protoc twice, once to generate the grpc c++ native service interfaces and a second time to generate the protobuf classes:
protoc --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin.exe admin.proto
protoc --cpp_out=. admin.proto

The server is in c++, but I created the test client in Python. Similiarly, call protoc twice, specifying you need native python classes:

protoc --grpc_out=. --plugin=protoc-gen-grpc=grpc_python_plugin.exe admin.proto
protoc --python_out=. admin.proto

Note: you will need to install gprc modile for python using pip or anaconda. If you want to you could call protoc directly
from python like so:
python -m grpc_tools.protoc --python_out=. --grpc_python_out=. admin.proto

CMake is awesome. For those who have not used it, it's very helpful. It will autogenerate the Visual Studio solutions files
with all the proper library references. It's great if you are building cross platform c++ (Windows and Linux). CMake will auto
generate the make files on ubuntu. I provide an example of this in the docker container that runs the grpc_cpp service.

Checkout the CMakeLists.txt file which has all the configuration for CMake. Notice on Windows we need to include these 2 libraries:
grpc++.lib and WS2_32.lib (WinSock)

You can generate the Visual Studio solution file with this command. Since we are using vcpkg you need to add a reference to the
toolchain file. Make sure the path to vcpkg is correct for you.
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\git\vcpkg\scripts\buildsystems\vcpkg.cmake


There is a Dockerfile to build this on ubuntu.
docker build .

add  --no-cache if you want to rebuild the entire container.

The compose file expects the container to be tagged rbaxter\grpc_cpp

docker tag <image_id> rbaxter\grpc_cpp:latest

There is docker-compose.yml to orchestrate the stack. You can run it with the following command:
docker compose up



