#include <iostream>
#include "Command.h"
#include "StandardIO.h"
#include "UploadC.h"
#include "Settings.h"
#include "Classify.h"
#include "Display.h"
#include "Download.h"
#include "CheckInput.h"
#define NUM_OF_CMDS 5


string printMenu(Command** cmd) {
    string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
    for (int i = 0; i < NUM_OF_CMDS; i++) {
        menu.append(std::to_string(i+1));
        menu.append(". ");
        menu.append(cmd[i][0].getDesc());
        menu.append("\n");
    }
    menu.append("8. exit\n");
    return menu;
}

class CLI {

public:
    void start() {
        ShareData *sd = new ShareData();
        StandardIO tempIO = StandardIO();
        DefaultIO& IO = tempIO;
        UploadC upload = UploadC("upload an unclassified csv data file", IO, sd);
        Settings settings = Settings("algorithm settings", IO, sd);
        Classify classify = Classify("classify data", IO, sd);
        Display display = Display("display results", IO, sd);
        Download download = Download("download results", IO, sd);
        Command* commands[NUM_OF_CMDS] = {&upload, &settings, &classify, &display, &download};
        int option = 0;
        bool isEight = false;
        string input;
        while (!isEight) {
            switch (option) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    commands[option-1]->execute();
                    break;
                case 8:
                    isEight = true;
                    break;
                default:
                    break;
            }
            if (!isEight) {
                cout  << printMenu(commands);
                getline(std::cin, input);
                if (isNumber(&input[0])) {
                    option = stoi(input);
                } else {
                    option = 0;
                }
            }
        }
    }
};



int main(int argc, char *argv[]) {
    CLI cli;
    cli.start();
    return 0;
}


