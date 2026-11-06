#include "SystemInfo.h"
#include <windows.h>
#include <winternl.h>
#include <cstdio>
#include <algorithm>

typedef NTSTATUS (WINAPI *pfnNtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

SystemInfo::SystemInfo(size_t maxHistorySize)
    : m_maxHistorySize(maxHistorySize),
      m_updateInterval(0.5f),
      m_timeSinceLastUpdate(0.5f),
      m_logicalCoreCount(0),
      m_overallCpuUsage(0.0f),
      m_uptimeSeconds(0),
      m_prevIdleTime(0),
      m_prevKernelTime(0),
      m_prevUserTime(0)
{
    InitStaticInfo();
}

void SystemInfo::InitStaticInfo() {
    // 1. Processor count & Architecture
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    m_logicalCoreCount = static_cast<int>(sysInfo.dwNumberOfProcessors);

    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            m_architecture = "x86_64 (64-bit)";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            m_architecture = "x86 (32-bit)";
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            m_architecture = "ARM64";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            m_architecture = "ARM";
            break;
        default:
            m_architecture = "Unknown Architecture";
            break;
    }

    // 2. CPU Name from Registry
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char nameBuf[256] = {0};
        DWORD bufSize = sizeof(nameBuf);
        DWORD type = 0;
        if (RegQueryValueExA(hKey, "ProcessorNameString", NULL, &type, reinterpret_cast<LPBYTE>(nameBuf), &bufSize) == ERROR_SUCCESS) {
            m_cpuName = nameBuf;
        }
        RegCloseKey(hKey);
    }

    if (m_cpuName.empty()) {
        m_cpuName = "Generic Processor";
    } else {
        // Trim leading spaces
        size_t start = m_cpuName.find_first_not_of(" \t\r\n");
        if (start != std::string::npos) {
            m_cpuName = m_cpuName.substr(start);
        }
    }

    // Initialize core data structures
    m_cores.resize(m_logicalCoreCount);
    m_prevCoreStates.resize(m_logicalCoreCount, {0, 0, 0});

    for (int i = 0; i < m_logicalCoreCount; ++i) {
        m_cores[i].id = i;
        m_cores[i].usagePercent = 0.0f;
    }

    // Initial query to prime delta counters
    QueryCpuUsage();
    QueryRamUsage();
    QueryUptime();
}

void SystemInfo::Update(float deltaTime) {
    m_timeSinceLastUpdate += deltaTime;
    if (m_timeSinceLastUpdate >= m_updateInterval) {
        m_timeSinceLastUpdate = 0.0f;

        QueryCpuUsage();
        QueryRamUsage();
        QueryUptime();
    }
}

void SystemInfo::QueryCpuUsage() {
    // --- Overall CPU Usage ---
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        uint64_t idle = (static_cast<uint64_t>(idleTime.dwHighDateTime) << 32) | idleTime.dwLowDateTime;
        uint64_t kernel = (static_cast<uint64_t>(kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
        uint64_t user = (static_cast<uint64_t>(userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;

        uint64_t idleDiff = idle - m_prevIdleTime;
        uint64_t kernelDiff = kernel - m_prevKernelTime;
        uint64_t userDiff = user - m_prevUserTime;

        uint64_t totalSys = kernelDiff + userDiff;
        if (totalSys > 0) {
            uint64_t active = totalSys - idleDiff;
            m_overallCpuUsage = (static_cast<float>(active) / static_cast<float>(totalSys)) * 100.0f;
            m_overallCpuUsage = std::clamp(m_overallCpuUsage, 0.0f, 100.0f);
        }

        m_prevIdleTime = idle;
        m_prevKernelTime = kernel;
        m_prevUserTime = user;

        m_cpuHistory.push_back(m_overallCpuUsage);
        if (m_cpuHistory.size() > m_maxHistorySize) {
            m_cpuHistory.erase(m_cpuHistory.begin());
        }
    }

    // --- Per-Core CPU Usage ---
    static pfnNtQuerySystemInformation NtQuerySystemInformationPtr = nullptr;
    static bool initializedNtQuery = false;

    if (!initializedNtQuery) {
        HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
        if (hNtdll) {
            NtQuerySystemInformationPtr = reinterpret_cast<pfnNtQuerySystemInformation>(
                GetProcAddress(hNtdll, "NtQuerySystemInformation")
            );
        }
        initializedNtQuery = true;
    }

    if (NtQuerySystemInformationPtr && m_logicalCoreCount > 0) {
        std::vector<SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION> perfInfo(m_logicalCoreCount);
        ULONG returnLength = 0;
        NTSTATUS status = NtQuerySystemInformationPtr(
            8, // SystemProcessorPerformanceInformation
            perfInfo.data(),
            static_cast<ULONG>(sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * m_logicalCoreCount),
            &returnLength
        );

        if (status == 0) { // STATUS_SUCCESS
            for (int i = 0; i < m_logicalCoreCount; ++i) {
                uint64_t idle = perfInfo[i].IdleTime.QuadPart;
                uint64_t kernel = perfInfo[i].KernelTime.QuadPart;
                uint64_t user = perfInfo[i].UserTime.QuadPart;

                uint64_t idleDiff = idle - m_prevCoreStates[i].idleTime;
                uint64_t kernelDiff = kernel - m_prevCoreStates[i].kernelTime;
                uint64_t userDiff = user - m_prevCoreStates[i].userTime;

                uint64_t total = kernelDiff + userDiff;
                float coreUsage = 0.0f;
                if (total > 0) {
                    uint64_t active = total - idleDiff;
                    coreUsage = (static_cast<float>(active) / static_cast<float>(total)) * 100.0f;
                    coreUsage = std::clamp(coreUsage, 0.0f, 100.0f);
                }

                m_cores[i].usagePercent = coreUsage;
                m_cores[i].history.push_back(coreUsage);
                if (m_cores[i].history.size() > m_maxHistorySize) {
                    m_cores[i].history.erase(m_cores[i].history.begin());
                }

                m_prevCoreStates[i].idleTime = idle;
                m_prevCoreStates[i].kernelTime = kernel;
                m_prevCoreStates[i].userTime = user;
            }
        }
    }
}

void SystemInfo::QueryRamUsage() {
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memStatus)) {
        m_ramData.totalBytes = memStatus.ullTotalPhys;
        m_ramData.availBytes = memStatus.ullAvailPhys;
        m_ramData.usedBytes = m_ramData.totalBytes - m_ramData.availBytes;
        m_ramData.usagePercent = static_cast<float>(memStatus.dwMemoryLoad);

        m_ramData.history.push_back(m_ramData.usagePercent);
        if (m_ramData.history.size() > m_maxHistorySize) {
            m_ramData.history.erase(m_ramData.history.begin());
        }
    }
}

void SystemInfo::QueryUptime() {
    m_uptimeSeconds = GetTickCount64() / 1000;
}

std::string SystemInfo::GetFormattedUptime() const {
    uint64_t days = m_uptimeSeconds / 86400;
    uint64_t hours = (m_uptimeSeconds % 86400) / 3600;
    uint64_t mins = (m_uptimeSeconds % 3600) / 60;
    uint64_t secs = m_uptimeSeconds % 60;

    char buf[128];
    if (days > 0) {
        snprintf(buf, sizeof(buf), "%llud %02lluh %02llum %02llus", days, hours, mins, secs);
    } else {
        snprintf(buf, sizeof(buf), "%02lluh %02llum %02llus", hours, mins, secs);
    }
    return std::string(buf);
}
