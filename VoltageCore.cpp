#include "VoltageCore.h"
#include <cstring>
#include <windows.h> 

#define ArtDAQErrChk(functionCall) if(ArtDAQFailed(error = (functionCall))) goto Error; else

//ʹ����ʱ���������ɵ�ѹ����
bool VoltageCore::writeContExtClk(const std::string& device,        
    const std::vector<double>& waveform,
    const std::string& sampleClkSrc,
    double sampleRate,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, sampleClkSrc.c_str(), sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//ʹ����ʱ���������ɵ�ѹ���ݣ���ʹ�������ź���Ϊ��ʼ����
bool VoltageCore::writeContExtClkDigStart(const std::string& device,
    const std::vector<double>& waveform,
    const std::string& clkSrc,
    const std::string& trigSrc,
    double sampleRate,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, clkSrc.c_str(), sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_CfgDigEdgeStartTrig(taskHandle, trigSrc.c_str(), ArtDAQ_Val_Rising));
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//ʹ����ʱ���������ɵ�ѹ����
bool VoltageCore::writeContIntClk(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//ʹ����ʱ���������ɵ�ѹ���ݣ���ʹ��ģ���ź���Ϊ��ʼ����
bool VoltageCore::writeContIntClkAnlgStart(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    const std::string& trigSrc,
    double trigLevel,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_CfgAnlgEdgeStartTrig(taskHandle, trigSrc.c_str(), ArtDAQ_Val_Rising, trigLevel));
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//ʹ���ڲ�ʱ��������� + ������ģʽ
bool VoltageCore::writeContIntClkNotRegen(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQErrChk(ArtDAQ_SetWriteRegenMode(taskHandle, ArtDAQ_Val_DoNotAllowRegen));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//�ն������������
bool VoltageCore::writeContIntClkTermCfg(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    int terminalConfig,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQErrChk(ArtDAQ_SetAOTermCfg(taskHandle, device.c_str(), terminalConfig));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    mTask = taskHandle;
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

//ʹ����ʱ���������޵��ѹ����
bool VoltageCore::writeMultVoltUpdatesIntClk(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    ArtDAQErrChk(ArtDAQ_WaitUntilTaskDone(taskHandle, 10.0));

    ArtDAQ_StopTask(taskHandle);
    ArtDAQ_ClearTask(taskHandle);
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

// ʹ����ʱ���������޵��ѹ���ݣ���ʹ�������ź���Ϊ��ʼ����
bool VoltageCore::writeMultVoltUpdatesIntClkDigStart(const std::string& device,
    const std::vector<double>& waveform,
    double sampleRate,
    const std::string& trigSrc,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQ_CfgSampClkTiming(taskHandle, "", sampleRate,
        ArtDAQ_Val_Rising, ArtDAQ_Val_ContSamps, waveform.size());
    ArtDAQErrChk(ArtDAQ_CfgDigEdgeStartTrig(taskHandle, trigSrc.c_str(), ArtDAQ_Val_Rising));
    ArtDAQErrChk(ArtDAQ_WriteAnalogF64(taskHandle, waveform.size(), 0, 10.0,
        ArtDAQ_Val_GroupByChannel, waveform.data(), NULL, NULL));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    ArtDAQErrChk(ArtDAQ_WaitUntilTaskDone(taskHandle, 10.0));

    ArtDAQ_StopTask(taskHandle);
    ArtDAQ_ClearTask(taskHandle);
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}


//�����ʱѭ�������ѹ����
bool VoltageCore::writeSwTimedLoop(const std::string& device,
    const std::vector<double>& waveform,
    int loopCount,
    int intervalMs,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));

    for (int i = 0; i < loopCount; ++i) {
        float64 value = waveform[i % waveform.size()];
        ArtDAQErrChk(ArtDAQ_WriteAnalogScalarF64(taskHandle, TRUE, 10.0, value, NULL));
        Sleep(intervalMs);
    }

    ArtDAQ_StopTask(taskHandle);
    ArtDAQ_ClearTask(taskHandle);
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) {
        ArtDAQ_StopTask(taskHandle);
        ArtDAQ_ClearTask(taskHandle);
    }
    return false;
}


//���ε�ѹ�������
bool VoltageCore::write(const std::string& device,
    double voltage,
    std::string& err)
{
    int32 error = 0;
    char errBuff[2048] = { '\0' };
    TaskHandle taskHandle = nullptr;

    ArtDAQErrChk(ArtDAQ_CreateTask("", &taskHandle));
    ArtDAQErrChk(ArtDAQ_CreateAOVoltageChan(taskHandle, device.c_str(), "", -10.0, 10.0, ArtDAQ_Val_Volts, ""));
    ArtDAQErrChk(ArtDAQ_StartTask(taskHandle));
    ArtDAQErrChk(ArtDAQ_WriteAnalogScalarF64(taskHandle, TRUE, 10.0, voltage, NULL));

    ArtDAQ_StopTask(taskHandle);
    ArtDAQ_ClearTask(taskHandle);
    return true;

Error:
    if (ArtDAQFailed(error)) ArtDAQ_GetExtendedErrorInfo(errBuff, sizeof(errBuff));
    err = errBuff;
    if (taskHandle) { ArtDAQ_StopTask(taskHandle); ArtDAQ_ClearTask(taskHandle); }
    return false;
}

void VoltageCore::stop() {
    if (mTask) {
        ArtDAQ_StopTask(mTask);
    }
}

void VoltageCore::shutdown() {
    if (mTask) {
        ArtDAQ_ClearTask(mTask);
        mTask = nullptr;
    }
}
