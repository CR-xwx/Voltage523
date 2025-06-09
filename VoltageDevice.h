#pragma once
#include <string>
#include <vector>
#include "VoltageCore.h"

class VoltageDevice {
public:
    bool open(const std::string& kvJson, std::string& err);
    bool write(double value, std::string& err);
    bool read(double& value, std::string& err);
    void close();

    bool writeContExtClk(const std::vector<double>& waveform,
        const std::string& clkSrc,
        double sampleRate,
        std::string& err);

    bool writeContExtClkDigStart(const std::vector<double>& waveform,
        const std::string& clkSrc,
        const std::string& trigSrc,
        double sampleRate,
        std::string& err);

    bool writeContIntClk(const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeContIntClkAnlgStart(const std::vector<double>& waveform,
        double sampleRate,
        const std::string& trigSrc,
        double trigLevel,
        std::string& err);

    bool writeContIntClkNotRegen(const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeContIntClkTermCfg(const std::vector<double>& waveform,
        double sampleRate,
        int terminalConfig,
        std::string& err);

    bool writeMultVoltUpdatesIntClk(const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeMultVoltUpdatesIntClkDigStart(const std::vector<double>& waveform,
        double sampleRate,
        const std::string& trigSrc,
        std::string& err);

    bool writeSwTimedLoop(const std::vector<double>& waveform,
        int loopCount,
        int intervalMs,
        std::string& err);


private:
    VoltageCore mCore;
    std::string mDevice; 
};
