#ifndef DL_H
#define DL_H
#include <string>
#include <vector>
#include "Command.h"


using namespace std;
class Download : protected Command {
private:
    vector<string> clsifics;
    string path;

public:
    Download(vector<string>, string);
    string getPath();
    void setPath(string);
    vector<string> getClsifics();
    void setClsifics(vector<string>);
    virtual void execute();
};


#endif