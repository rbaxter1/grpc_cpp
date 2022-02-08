#pragma once

#include "admin.grpc.pb.h"

class AdminImpl final : public Admin::Service {
public:
	AdminImpl();
	grpc::Status Tags(grpc::ServerContext* context, const TagsRequest* request, TagsReply* response);
};
