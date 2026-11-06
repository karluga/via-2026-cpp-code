#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "SystemInfo.h"

class Dashboard {
public:
    Dashboard();
    ~Dashboard() = default;

    void InitStyle();
    void Render(SystemInfo& sysInfo);

private:
    void RenderHeader(SystemInfo& sysInfo);
    void RenderOverview(SystemInfo& sysInfo);
    void RenderCpuDetails(SystemInfo& sysInfo);
    void RenderRamDetails(SystemInfo& sysInfo);
    void RenderHardwareInfo(SystemInfo& sysInfo);

    int m_selectedTab;
    float m_chartHeight;
};

#endif // DASHBOARD_H
