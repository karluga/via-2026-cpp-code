#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <string>
#include <vector>
#include <cstdint>

struct CpuCoreData {
    int id;
    float usagePercent;
    std::vector<float> history;
};

struct RamData {
    uint64_t totalBytes;
    uint64_t usedBytes;
    uint64_t availBytes;
    float usagePercent;
    std::vector<float> history;
};

class SystemInfo {
public:
    explicit SystemInfo(size_t maxHistorySize = 120);
    ~SystemInfo() = default;

    void Update(float deltaTime);

    // CPU Info
    float GetOverallCpuUsage() const { return m_overallCpuUsage; }
    const std::vector<float>& GetCpuHistory() const { return m_cpuHistory; }
    const std::vector<CpuCoreData>& GetCores() const { return m_cores; }

    // Memory Info
    const RamData& GetRamData() const { return m_ramData; }

    // System Hardware Meta
    const std::string& GetCpuName() const { return m_cpuName; }
    const std::string& GetArchitecture() const { return m_architecture; }
    int GetLogicalCoreCount() const { return m_logicalCoreCount; }

    // Uptime
    uint64_t GetUptimeSeconds() const { return m_uptimeSeconds; }
    std::string GetFormattedUptime() const;

    // Config
    float GetUpdateInterval() const { return m_updateInterval; }
    void SetUpdateInterval(float interval) { m_updateInterval = interval; }

private:
    void InitStaticInfo();
    void QueryCpuUsage();
    void QueryRamUsage();
    void QueryUptime();

    size_t m_maxHistorySize;
    float m_updateInterval;
    float m_timeSinceLastUpdate;

    std::string m_cpuName;
    std::string m_architecture;
    int m_logicalCoreCount;

    float m_overallCpuUsage;
    std::vector<float> m_cpuHistory;

    RamData m_ramData;
    std::vector<CpuCoreData> m_cores;

    uint64_t m_uptimeSeconds;

    // CPU sampling state
    uint64_t m_prevIdleTime;
    uint64_t m_prevKernelTime;
    uint64_t m_prevUserTime;

    struct CoreTimeState {
        uint64_t idleTime;
        uint64_t kernelTime;
        uint64_t userTime;
    };
    std::vector<CoreTimeState> m_prevCoreStates;
};

#endif // SYSTEM_INFO_H
