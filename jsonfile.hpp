#ifndef    __jsonFile__
#define    __jsonFile__

#include <fstream>
#include "json\json.h"

class jsonFile{

public:
    jsonFile();
    bool loadJsonFile(const std::string fileName);
    void saveJsonFile(const std::string fileName);

    Json::Value m_Root;
private:

};
#endif
