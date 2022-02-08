#include <iostream>
#include <string>
#include "grpc/grpc.h"
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "AdminImpl.h"

using namespace std;

void RunServer() {
	string server_address("0.0.0.0:50051");
	AdminImpl service;

	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService((grpc::Service *)&service);
	unique_ptr<grpc::Server> server(builder.BuildAndStart());
	cout << "Server listening on " << server_address << endl;
	server->Wait();
}

int main()
{
	RunServer();
	return 0;
}

