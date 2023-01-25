#ifndef CHKIN_H
#define CHKIN_H
#include <string.h>
#include <string>
#include <ctype.h>
#include <regex>

using namespace std;

bool isNumber(char[]);
bool isNumber(const char[]);
bool isLegalPort(int);
bool isLegalIp(string);

#endif