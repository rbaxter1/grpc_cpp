#include <iostream>
#include "grpc/grpc.h"
#include "AdminImpl.h"
#include <thread>

using namespace std;

AdminImpl::AdminImpl()
{
}

grpc::Status AdminImpl::Tags(grpc::ServerContext* context, const TagsRequest* request, TagsReply* response) {

	cout << "Got a request for message " << request->message_name() << " on connection " << request->connection() << endl;

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_body();
		t->set_tag(i);
		t->set_name("body_tag" + std::to_string(i));
	}

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_header();
		t->set_tag(i);
		t->set_name("header_tag" + std::to_string(i));
	}

	for (int i = 1; i <= 10; ++i) {
		Tag* t = response->add_trailer();
		t->set_tag(i);
		t->set_name("trailer_tag" + std::to_string(i));
	}

	return grpc::Status::OK;
}

grpc::Status AdminImpl::TagMe(grpc::ServerContext* context, const TagsRequest* request, grpc::ServerWriter<TagsReply>* writer) {

	TagsReply response;

	for (int i = 1; i <= 10; ++i) {

		this_thread::sleep_for(chrono::milliseconds(1000));

		Tag* ht = response.add_header();
		ht->set_tag(i);
		ht->set_name("header_tag" + to_string(i));

		Tag* bt = response.add_body();
		bt->set_tag(i);
		bt->set_name("body_tag" + to_string(i));

		Tag* tt = response.add_trailer();
		tt->set_tag(i);
		tt->set_name("trailer_tag" + to_string(i));

		writer->Write(response);
	}

	return grpc::Status::OK;
}
