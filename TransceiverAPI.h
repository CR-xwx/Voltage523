#pragma once
#include <string>
#include <vector>

#ifdef _WIN32
#ifdef TRANSCEIVER_EXPORTS
#define TRANSCEIVER_API __declspec(dllexport)
#else
#define TRANSCEIVER_API __declspec(dllimport)
#endif
#else
#define TRANSCEIVER_API
#endif


#ifdef __cplusplus
extern "C" {
#endif
    using RawData = std::vector<double>;  

    TRANSCEIVER_API bool openTransceiver(const std::string& configPath, std::string& errorMsg);
    TRANSCEIVER_API bool writeTransceiver(double value, std::string& errorMsg);
    TRANSCEIVER_API bool readTransceiver(double& value, std::string& errorMsg);
    TRANSCEIVER_API void closeTransceiver();

#ifdef __cplusplus
}
#endif
