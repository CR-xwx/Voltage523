#include "VoltageDevice.h"
#include <json/json.h>
#include <cmath>

bool VoltageDevice::open(const std::string& kvJson, std::string& err)
{
    Json::Value root;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    JSONCPP_STRING errs;

    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    bool parseSuccess = reader->parse(kvJson.c_str(), kvJson.c_str() + kvJson.length(), &root, &errs);
    if (!parseSuccess || !root.isObject()) {
        err = "VoltageDevice::open(): Configuration parsing failed: " + errs;
        return false;
    }

    mDevice = root.get("device", "").asString();
    std::string mode = root.get("mode", "").asString();
    std::string clkSrc = root.get("sampleClkSrc", "").asString();
    std::string trigSrc = root.get("triggerSrc", "").asString();
    double sampleRate = root.get("sampleRate", 1000.0).asDouble();
    double trigLevel = root.get("trigLevel", 1.0).asDouble();

    int termCfg = 10106;  
    std::string termStr = root.get("terminalConfig", "").asString();
    if (termStr == "RSE") termCfg = 10083;
    else if (termStr == "NRSE") termCfg = 10078;

    std::vector<double> waveform(1000);
    for (int i = 0; i < 1000; ++i)
        waveform[i] = 5.0 * std::sin(i * 2.0 * 3.1415926535 / 1000.0);

    if (mode == "contExtClk")
        return writeContExtClk(waveform, clkSrc, sampleRate, err);
    else if (mode == "contExtClkDigStart")
        return writeContExtClkDigStart(waveform, clkSrc, trigSrc, sampleRate, err);
    else if (mode == "contIntClk")
        return writeContIntClk(waveform, sampleRate, err);
    else if (mode == "contIntClkAnlgStart")
        return writeContIntClkAnlgStart(waveform, sampleRate, trigSrc, trigLevel, err);
    else if (mode == "contIntClkNotRegen")
        return writeContIntClkNotRegen(waveform, sampleRate, err);
    else if (mode == "contIntClkTermCfg")
        return writeContIntClkTermCfg(waveform, sampleRate, termCfg, err);
    else if (mode == "multVoltUpdatesIntClk")
        return writeMultVoltUpdatesIntClk(waveform, sampleRate, err);
    else if (mode == "multVoltUpdatesIntClkDigStart")
        return writeMultVoltUpdatesIntClkDigStart(waveform, sampleRate, trigSrc, err);
    else if (mode == "swTimed")
        return mCore.write(mDevice, sampleRate, err);
    else if (mode == "swTimedLoop") {
        int loopCount = root.get("loopCount", 1000).asInt();
        int interval = root.get("intervalMs", 1).asInt();
        return writeSwTimedLoop(waveform, loopCount, interval, err);
    }
    else {
        err = "Unrecognized mode type: " + mode;
        return false;
    }

}

bool VoltageDevice::write(double value, std::string& err) {
    return mCore.write(mDevice, value, err);
}

bool VoltageDevice::read(double& value, std::string& err) {
    err = "Analog read not supported.";
    return false;
}

void VoltageDevice::close() {
    mCore.shutdown();
}

bool VoltageDevice::writeContExtClk(const std::vector<double>& waveform,
    const std::string& clkSrc,
    double sampleRate,
    std::string& err)
{
    return mCore.writeContExtClk(mDevice, waveform, clkSrc, sampleRate, err);
}

bool VoltageDevice::writeContExtClkDigStart(const std::vector<double>& waveform,
    const std::string& clkSrc,
    const std::string& trigSrc,
    double sampleRate,
    std::string& err)
{
    return mCore.writeContExtClkDigStart(mDevice, waveform, clkSrc, trigSrc, sampleRate, err);
}

bool VoltageDevice::writeContIntClk(const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    return mCore.writeContIntClk(mDevice, waveform, sampleRate, err);
}

bool VoltageDevice::writeContIntClkAnlgStart(const std::vector<double>& waveform,
    double sampleRate,
    const std::string& trigSrc,
    double trigLevel,
    std::string& err)
{
    return mCore.writeContIntClkAnlgStart(mDevice, waveform, sampleRate, trigSrc, trigLevel, err);
}

bool VoltageDevice::writeContIntClkNotRegen(const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    return mCore.writeContIntClkNotRegen(mDevice, waveform, sampleRate, err);
}

bool VoltageDevice::writeContIntClkTermCfg(const std::vector<double>& waveform,
    double sampleRate,
    int terminalConfig,
    std::string& err)
{
    return mCore.writeContIntClkTermCfg(mDevice, waveform, sampleRate, terminalConfig, err);
}

bool VoltageDevice::writeMultVoltUpdatesIntClk(const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    return mCore.writeMultVoltUpdatesIntClk(mDevice, waveform, sampleRate, err);
}

bool VoltageDevice::writeMultVoltUpdatesIntClkDigStart(const std::vector<double>& waveform,
    double sampleRate,
    const std::string& trigSrc,
    std::string& err)
{
    return mCore.writeMultVoltUpdatesIntClkDigStart(mDevice, waveform, sampleRate, trigSrc, err);
}

bool VoltageDevice::writeSwTimedLoop(const std::vector<double>& waveform,
    int loopCount,
    int intervalMs,
    std::string& err)
{
    return mCore.writeSwTimedLoop(mDevice, waveform, loopCount, intervalMs, err);
}
