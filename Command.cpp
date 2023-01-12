#include "Command.h"
   
   
Command::Command(string _desc, DefaultIO _dio) {
    desc = _desc;
    dio = _dio;
}

void Command::setDesc(string _desc) {
    desc = desc;
}

void Command::setDio(DefaultIO _dio) {
    dio = _dio;
}

string Command::getDesc() {
    return desc;
}

DefaultIO Command::getDio() {
    return dio;
}   