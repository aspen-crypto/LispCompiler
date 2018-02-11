#include "InputFileHandler.h"
#include <fstream>

std::string fileToString(const std::string &fileName){
    std::ifstream t(fileName + ".lasp", std::ios::binary);
    std::string out;
    out.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());
    return out;
}