#include "IOConfig.h"
#include <json/json.h>
#include <fstream>
#include <sstream>

IOConfig::IOConfig(std::string& configFile)
    : mConfigFile(configFile) {
}

IOConfig::~IOConfig() {}

bool IOConfig::parse()
{
    Json::Value root;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;

    std::ifstream in(mConfigFile);
    if (!in.is_open()) {
        mError = "Configuration file does not exist£º" + mConfigFile;
        return false;
    }

    bool result = Json::parseFromStream(builder, in, &root, &mError);
    in.close();
    if (!result) return false;

    // ÌáÈ¡×Ö¶Î
    if (root.isObject()) {
        if (root.isMember("Name") && root["Name"].isString()) mName = root["Name"].asString();
        if (root.isMember("Description") && root["Description"].isString()) mDescription = root["Description"].asString();
        if (root.isMember("PartNumber") && root["PartNumber"].isString()) mPartNumber = root["PartNumber"].asString();
        if (root.isMember("Version") && root["Version"].isString()) mVersion = root["Version"].asString();
        if (root.isMember("Type") && root["Type"].isString()) mType = root["Type"].asString();
        if (root.isMember("Transceiver") && root["Transceiver"].isString()) mTransceiverFile = root["Transceiver"].asString();
        if (root.isMember("TransceiverConfig") && root["TransceiverConfig"].isArray() && root["TransceiverConfig"].size() > 0) {
            Json::StreamWriterBuilder swBuilder;
            mTransceiverConfig = Json::writeString(swBuilder, root["TransceiverConfig"][0]);
        }



        return true;
    }

    mError = "Configuration format error";
    return false;
}

const std::string& IOConfig::getName() const { return mName; }
const std::string& IOConfig::getDescription() const { return mDescription; }
const std::string& IOConfig::getPartNumber() const { return mPartNumber; }
const std::string& IOConfig::getVersion() const { return mVersion; }
const std::string& IOConfig::getType() const { return mType; }
const std::string& IOConfig::getTransceiverFile() const { return mTransceiverFile; }
const std::string& IOConfig::getTransceiverConfig() const { return mTransceiverConfig; }
const std::string& IOConfig::getErrorText() const { return mError; }
