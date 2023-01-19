#include "Command.h"
      
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