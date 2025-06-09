#include "TransceiverAPI.h"
#include "VoltageDevice.h"
#include "Singleton.h"
#include "IOConfig.h"

static VoltageDevice* gDevice = nullptr;

bool openTransceiver(const std::string& configPath, std::string& errorMsg)
{
    gDevice = Singleton<VoltageDevice>::getInstance();

    
    IOConfig ioConfig(const_cast<std::string&>(configPath));
    if (!ioConfig.parse())
    {
        errorMsg = ioConfig.getErrorText();
        return false;
    }

    
    const std::string& configContent = ioConfig.getTransceiverConfig();
    return gDevice->open(configContent, errorMsg);
}


bool writeTransceiver(double value, std::string& errorMsg)
{
    if (!gDevice) {
        errorMsg = "Device not initialized.";
        return false;
    }
    return gDevice->write(value, errorMsg);
}

bool readTransceiver(double& value, std::string& errorMsg)
{
    if (!gDevice) {
        errorMsg = "Device not initialized.";
        return false;
    }
    return gDevice->read(value, errorMsg);
}

void closeTransceiver()
{
    if (gDevice) {
        gDevice->close();
        gDevice = nullptr;
    }
}
