import grpc

import sys
sys.path.insert(1, './protos')
import admin_pb2_grpc
import admin_pb2

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = admin_pb2_grpc.AdminStub(channel)
    response = stub.Tags(admin_pb2.TagsRequest(message_name="NewOrderSingle", connection="Test"))

    print('header tags')
    for h in response.header:
        print(h)

    print('body tags')
    for b in response.body:
        print(b)

    print('trailer tags')
    for t in response.trailer:
        print(t)

if __name__ == '__main__':
    run()