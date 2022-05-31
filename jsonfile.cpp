#include "jsonfile.hpp"

jsonFile::jsonFile()
{

}

bool jsonFile::loadJsonFile(const std::string fileName)
{
    std::ifstream jsonFile(fileName, std::ifstream::in);
    Json::CharReaderBuilder reader;
    reader["collectComments"] = true;
    JSONCPP_STRING errs;
    return Json::parseFromStream(reader, jsonFile, &m_Root, &errs);
}

void jsonFile::saveJsonFile(const std::string fileName)
{
    std::ofstream jsonFile(fileName, std::ofstream::out);
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(m_Root, &jsonFile);

}
