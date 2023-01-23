cmake_minimum_required(VERSION 3.24)
project(B11)

set(CMAKE_CXX_STANDARD 11)

add_executable(B11 CheckInput.h CheckInput.cpp CLI.cpp Command.h Command.cpp Classify.cpp Classify.h UploadC.cpp UploadC.h
        KnnServer.cpp KnnDB.cpp Display.cpp Download.cpp Settings.cpp StandardIO.cpp VectorCalDis.h
        VectorCalDis.cpp KnnVec.h KnnVec.cpp)
