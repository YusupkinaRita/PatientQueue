cmake_minimum_required(VERSION 3.8)


project(MyApp)
	
	
set(CMAKE_CXX_STANDARD 17)

add_executable(app main main.cpp ConnectionHandlerClient.cpp ConnectionHandlerServer.cpp)
target_link_libraries(app ws2_32)
