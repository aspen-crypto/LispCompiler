#include "OutputFileHandler.h"
#include <fstream>

void stringToFile(const std::string &fileName, const std::string &inputString){
    std::ofstream t (fileName + ".asp", std::ios::binary);
    t << inputString;
    t.close();
}