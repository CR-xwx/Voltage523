#include "TransceiverAPI.h"
#include <iostream>
#include <string>

int main() {
    std::string errMsg;

    
    std::string configPath = "test.json"; 

    if (!openTransceiver(configPath, errMsg)) {
        std::cerr << "Failed to open transceiver: " << errMsg << std::endl;
        return -1;
    }

    std::cout << "Transceiver opened successfully." << std::endl;

    
    if (!writeTransceiver(3.3, errMsg)) {
        std::cerr << "Failed to write transceiver: " << errMsg << std::endl;
        return -1;
    }

    std::cout << "Write completed." << std::endl;

   
    double value = 0.0;
    if (!readTransceiver(value, errMsg)) {
        std::cerr << "Read failed: " << errMsg << std::endl;
    }
    else {
        std::cout << "Read value: " << value << std::endl;
    }

    closeTransceiver();

    return 0;
}
