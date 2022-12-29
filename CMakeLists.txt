cmake_minimum_required(VERSION 3.24)
project(ex1)

set(CMAKE_CXX_STANDARD 11)


add_executable(client client.cpp ReadDataSet.h ReadDataSet.cpp Knn.cpp Knn.h Distance.cpp Distance.h ParseAndValidate.cpp ParseAndValidate.h)
add_executable(server server.cpp ReadDataSet.h ReadDataSet.cpp Knn.cpp Knn.h Distance.cpp Distance.h ParseAndValidate.cpp ParseAndValidate.h)