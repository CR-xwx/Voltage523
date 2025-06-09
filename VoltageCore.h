#pragma once
#include <vector>
#include <string>
#include "Art_DAQ.h"

class VoltageCore {
public:
    bool writeContExtClk(const std::string& device,
        const std::vector<double>& waveform,
        const std::string& sampleClkSrc,
        double sampleRate,
        std::string& err);

    bool writeContExtClkDigStart(const std::string& device,
        const std::vector<double>& waveform,
        const std::string& clkSrc,
        const std::string& trigSrc,
        double sampleRate,
        std::string& err);

    bool writeContIntClk(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeContIntClkAnlgStart(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        const std::string& trigSrc,
        double trigLevel,
        std::string& err);

    bool writeContIntClkNotRegen(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeContIntClkTermCfg(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        int terminalConfig,
        std::string& err);

    bool writeMultVoltUpdatesIntClk(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        std::string& err);

    bool writeMultVoltUpdatesIntClkDigStart(const std::string& device,
        const std::vector<double>& waveform,
        double sampleRate,
        const std::string& trigSrc,
        std::string& err);

    bool writeSwTimedLoop(const std::string& device,
        const std::vector<double>& waveform,
        int loopCount,
        int intervalMs,
        std::string& err);


    bool write(const std::string& device,
        double voltage,
        std::string& err);

    void stop();
    void shutdown();

private:
    TaskHandle mTask = nullptr;
};
