#brew install libuv
#brew install protobuf
g++ -luv -lprotobuf -o server Queue.cpp Server.cpp QueueService.cpp ../Common/QueueService.pb.cc
