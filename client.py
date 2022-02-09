import grpc
from threading import Thread
import time
import sys
sys.path.insert(1, './protos')
import admin_pb2_grpc
import admin_pb2

def handle_stream(response):
    try:
        for data in response:
            print("Got data from stream: ", data)
    except Exception as e:
        print(e)

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = admin_pb2_grpc.AdminStub(channel)
    

    iter = stub.TagMe(admin_pb2.TagsRequest(message_name="NewOrderSingle", connection="Test"))
    print("Starting background thread")
    stream_thread = Thread(target=handle_stream, args=(iter, ))
    stream_thread.start()


    for i in range(1, 20):
        print("yawn ", i)
        time.sleep(1)
        if i == 5:
            print("Calling the request-response API while streaming is running.")
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

    iter.cancel()
    stream_thread.join()


if __name__ == '__main__':
    run()