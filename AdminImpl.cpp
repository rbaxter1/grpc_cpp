#include <iostream>
#include "grpc/grpc.h"
#include "AdminImpl.h"

using namespace std;

AdminImpl::AdminImpl()
{
}

grpc::Status AdminImpl::Tags(grpc::ServerContext* context, const TagsRequest* request, TagsReply* response) {

	cout << "Got a request for message " << request->message_name() << " on connection " << request->connection() << endl;

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_body();
		t->set_tag(i);
		t->set_name("header_tag" + std::to_string(i));
	}

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_header();
		t->set_tag(i);
		t->set_name("body_tag" + std::to_string(i));
	}

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_trailer();
		t->set_tag(i);
		t->set_name("trailer_tag" + std::to_string(i));
	}

	return grpc::Status::OK;
}
