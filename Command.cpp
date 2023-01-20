#include "Command.h"


/*
* Func name: setDesc
* Input: string _desc (command description)
* Output: None
* Function operation: A setter for the description
*/ 
void Command::setDesc(string _desc) {
    desc = desc;
}

/*
* Func name: setDio
* Input: DefaultIO _dio (The IO object)
* Output: None
* Function operation: A setter for the IO object
*/  
void Command::setDio(DefaultIO _dio) {
    dio = _dio;
}

/*
* Func name: getDesc
* Input: None
* Output: string (the command description)
* Function operation: A getter for the description
*/  
string Command::getDesc() {
    return desc;
}

/*
* Func name: getDio
* Input: None
* Output: DefaultIO (The IO object)
* Function operation: A getter for the IO object
*/  
DefaultIO Command::getDio() {
    return dio;
}   