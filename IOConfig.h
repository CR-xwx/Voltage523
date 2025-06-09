#pragma once
#include <string>

class IOConfig final
{
public:
    IOConfig(std::string& configFile);
    ~IOConfig();

    bool parse();

    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getPartNumber() const;
    const std::string& getVersion() const;
    const std::string& getType() const;
    const std::string& getTransceiverFile() const;
    const std::string& getTransceiverConfig() const;
    const std::string& getErrorText() const;

private:
    std::string mConfigFile{ "" };
    std::string mError{ "" };

    std::string mName{ "" };
    std::string mDescription{ "" };
    std::string mPartNumber{ "" };
    std::string mVersion{ "" };
    std::string mType{ "" };
    std::string mTransceiverFile{ "" };
    std::string mTransceiverConfig{ "" }; 
};
