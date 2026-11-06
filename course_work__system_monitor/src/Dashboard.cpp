#include "Dashboard.h"
#include "imgui.h"
#include <cstdio>
#include <cmath>

Dashboard::Dashboard()
    : m_selectedTab(0),
      m_chartHeight(160.0f)
{
}

void Dashboard::InitStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 8.0f;
    style.FrameRounding = 5.0f;
    style.PopupRounding = 5.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 6.0f;

    style.WindowPadding = ImVec2(14, 14);
    style.FramePadding = ImVec2(8, 5);
    style.ItemSpacing = ImVec2(10, 10);
    style.ItemInnerSpacing = ImVec2(6, 6);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]             = ImVec4(0.11f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_Header]               = ImVec4(0.18f, 0.22f, 0.28f, 1.00f);
    colors[ImGuiCol_HeaderHovered]        = ImVec4(0.24f, 0.30f, 0.38f, 1.00f);
    colors[ImGuiCol_HeaderActive]         = ImVec4(0.20f, 0.26f, 0.34f, 1.00f);
    colors[ImGuiCol_Button]               = ImVec4(0.18f, 0.22f, 0.28f, 1.00f);
    colors[ImGuiCol_ButtonHovered]        = ImVec4(0.26f, 0.34f, 0.44f, 1.00f);
    colors[ImGuiCol_ButtonActive]         = ImVec4(0.20f, 0.28f, 0.38f, 1.00f);
    colors[ImGuiCol_FrameBg]              = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.20f, 0.24f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive]        = ImVec4(0.24f, 0.28f, 0.34f, 1.00f);
    colors[ImGuiCol_Tab]                  = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    colors[ImGuiCol_TabHovered]           = ImVec4(0.24f, 0.32f, 0.42f, 1.00f);
    colors[ImGuiCol_TabSelected]          = ImVec4(0.20f, 0.28f, 0.38f, 1.00f);
    colors[ImGuiCol_TabDimmed]            = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_TabDimmedSelected]    = ImVec4(0.16f, 0.20f, 0.26f, 1.00f);
    colors[ImGuiCol_TitleBg]              = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgActive]        = ImVec4(0.16f, 0.20f, 0.26f, 1.00f);
    colors[ImGuiCol_PlotLines]            = ImVec4(0.00f, 0.80f, 0.95f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]     = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]        = ImVec4(0.18f, 0.80f, 0.44f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 0.90f, 0.50f, 1.00f);
    colors[ImGuiCol_Text]                 = ImVec4(0.92f, 0.94f, 0.96f, 1.00f);
    colors[ImGuiCol_TextDisabled]         = ImVec4(0.50f, 0.55f, 0.60f, 1.00f);
    colors[ImGuiCol_Border]               = ImVec4(0.22f, 0.25f, 0.30f, 0.60f);
}

void Dashboard::Render(SystemInfo& sysInfo) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                   ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoCollapse |
                                   ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("System Monitor Dashboard", nullptr, windowFlags);

    RenderHeader(sysInfo);

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::BeginTabBar("MainTabBar", ImGuiTabBarFlags_Reorderable)) {
        if (ImGui::BeginTabItem("  Overview  ")) {
            RenderOverview(sysInfo);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  CPU Details  ")) {
            RenderCpuDetails(sysInfo);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  RAM Details  ")) {
            RenderRamDetails(sysInfo);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("  System Info  ")) {
            RenderHardwareInfo(sysInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void Dashboard::RenderHeader(SystemInfo& sysInfo) {
    ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "SYSTEM MONITOR");
    ImGui::SameLine();
    ImGui::TextDisabled("| Windows C++ Dashboard");

    ImGui::Spacing();

    if (ImGui::BeginTable("HeaderMetrics", 4, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingStretchSame)) {
        // --- Card 1: CPU Usage ---
        ImGui::TableNextColumn();
        ImGui::TextDisabled("CPU USAGE");
        float cpuUsage = sysInfo.GetOverallCpuUsage();
        ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "%.1f %%", cpuUsage);
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 0.82f, 0.95f, 1.00f));
        ImGui::ProgressBar(cpuUsage / 100.0f, ImVec2(-1, 8), "");
        ImGui::PopStyleColor();

        // --- Card 2: RAM Usage ---
        ImGui::TableNextColumn();
        ImGui::TextDisabled("RAM USAGE");
        const auto& ram = sysInfo.GetRamData();
        double usedGB = static_cast<double>(ram.usedBytes) / (1024.0 * 1024.0 * 1024.0);
        double totalGB = static_cast<double>(ram.totalBytes) / (1024.0 * 1024.0 * 1024.0);
        ImGui::TextColored(ImVec4(0.18f, 0.80f, 0.44f, 1.00f), "%.1f / %.1f GB (%.0f%%)", usedGB, totalGB, ram.usagePercent);
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.18f, 0.80f, 0.44f, 1.00f));
        ImGui::ProgressBar(ram.usagePercent / 100.0f, ImVec2(-1, 8), "");
        ImGui::PopStyleColor();

        // --- Card 3: Cores & Arch ---
        ImGui::TableNextColumn();
        ImGui::TextDisabled("HARDWARE");
        ImGui::Text("%d Cores", sysInfo.GetLogicalCoreCount());
        ImGui::TextDisabled("%s", sysInfo.GetArchitecture().c_str());

        // --- Card 4: Uptime ---
        ImGui::TableNextColumn();
        ImGui::TextDisabled("SYSTEM UPTIME");
        ImGui::TextColored(ImVec4(0.95f, 0.65f, 0.15f, 1.00f), "%s", sysInfo.GetFormattedUptime().c_str());
        ImGui::TextDisabled("Active Session");

        ImGui::EndTable();
    }
}

void Dashboard::RenderOverview(SystemInfo& sysInfo) {
    ImGui::Spacing();

    // Live charts side by side
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float chartWidth = (windowWidth - 20.0f) * 0.5f;

    ImGui::BeginChild("CpuChartPanel", ImVec2(chartWidth, m_chartHeight + 50.0f), true);
    ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "CPU Load History");
    const auto& cpuHist = sysInfo.GetCpuHistory();
    char cpuOverlay[64];
    snprintf(cpuOverlay, sizeof(cpuOverlay), "Current: %.1f%%", sysInfo.GetOverallCpuUsage());
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.0f, 0.82f, 0.95f, 1.00f));
    ImGui::PlotLines("##CpuOverviewHist", cpuHist.data(), static_cast<int>(cpuHist.size()), 0, cpuOverlay, 0.0f, 100.0f, ImVec2(-1, m_chartHeight));
    ImGui::PopStyleColor();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("RamChartPanel", ImVec2(chartWidth, m_chartHeight + 50.0f), true);
    ImGui::TextColored(ImVec4(0.18f, 0.80f, 0.44f, 1.00f), "RAM Load History");
    const auto& ramHist = sysInfo.GetRamData().history;
    char ramOverlay[64];
    snprintf(ramOverlay, sizeof(ramOverlay), "Current: %.1f%%", sysInfo.GetRamData().usagePercent);
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.18f, 0.80f, 0.44f, 1.00f));
    ImGui::PlotLines("##RamOverviewHist", ramHist.data(), static_cast<int>(ramHist.size()), 0, ramOverlay, 0.0f, 100.0f, ImVec2(-1, m_chartHeight));
    ImGui::PopStyleColor();
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Core Summary Grid
    ImGui::TextDisabled("CPU CORE LOAD QUICK VIEW");
    const auto& cores = sysInfo.GetCores();
    int columns = 4;
    if (windowWidth < 600.0f) columns = 2;
    if (windowWidth < 400.0f) columns = 1;

    if (ImGui::BeginTable("CoreQuickGrid", columns, ImGuiTableFlags_SizingStretchSame)) {
        for (const auto& core : cores) {
            ImGui::TableNextColumn();
            char label[32];
            snprintf(label, sizeof(label), "Core %d", core.id);
            ImGui::Text("%s", label);
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "%.1f%%", core.usagePercent);

            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 0.82f, 0.95f, 1.00f));
            ImGui::ProgressBar(core.usagePercent / 100.0f, ImVec2(-1, 6), "");
            ImGui::PopStyleColor();
        }
        ImGui::EndTable();
    }
}

void Dashboard::RenderCpuDetails(SystemInfo& sysInfo) {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "Per-Core Processor Performance");

    const auto& cores = sysInfo.GetCores();
    float availWidth = ImGui::GetContentRegionAvail().x;
    int columns = 2;
    if (availWidth < 700.0f) columns = 1;

    if (ImGui::BeginTable("CpuCoreDetailTable", columns, ImGuiTableFlags_SizingStretchSame)) {
        for (const auto& core : cores) {
            ImGui::TableNextColumn();
            ImGui::PushID(core.id);

            char boxTitle[32];
            snprintf(boxTitle, sizeof(boxTitle), "Logical Core #%d", core.id);
            ImGui::BeginChild(boxTitle, ImVec2(0, 110.0f), true);

            ImGui::Text("%s", boxTitle);
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "%.1f%%", core.usagePercent);

            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 0.82f, 0.95f, 1.00f));
            ImGui::ProgressBar(core.usagePercent / 100.0f, ImVec2(-1, 6), "");
            ImGui::PopStyleColor();

            if (!core.history.empty()) {
                ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.0f, 0.82f, 0.95f, 0.80f));
                ImGui::PlotLines("##CoreHist", core.history.data(), static_cast<int>(core.history.size()), 0, nullptr, 0.0f, 100.0f, ImVec2(-1, 40));
                ImGui::PopStyleColor();
            }

            ImGui::EndChild();
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

void Dashboard::RenderRamDetails(SystemInfo& sysInfo) {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.18f, 0.80f, 0.44f, 1.00f), "Physical Memory (RAM) Analysis");

    const auto& ram = sysInfo.GetRamData();
    double totalGB = static_cast<double>(ram.totalBytes) / (1024.0 * 1024.0 * 1024.0);
    double usedGB = static_cast<double>(ram.usedBytes) / (1024.0 * 1024.0 * 1024.0);
    double availGB = static_cast<double>(ram.availBytes) / (1024.0 * 1024.0 * 1024.0);

    if (ImGui::BeginTable("RamDetailStats", 3, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingStretchSame)) {
        ImGui::TableNextColumn();
        ImGui::TextDisabled("TOTAL INSTALLED RAM");
        ImGui::Text("%.2f GB", totalGB);

        ImGui::TableNextColumn();
        ImGui::TextDisabled("USED MEMORY");
        ImGui::TextColored(ImVec4(0.95f, 0.35f, 0.35f, 1.00f), "%.2f GB (%.1f%%)", usedGB, ram.usagePercent);

        ImGui::TableNextColumn();
        ImGui::TextDisabled("AVAILABLE MEMORY");
        ImGui::TextColored(ImVec4(0.18f, 0.80f, 0.44f, 1.00f), "%.2f GB", availGB);

        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.18f, 0.80f, 0.44f, 1.00f));
    char overlay[64];
    snprintf(overlay, sizeof(overlay), "RAM Load: %.1f%%", ram.usagePercent);
    ImGui::ProgressBar(ram.usagePercent / 100.0f, ImVec2(-1, 20.0f), overlay);
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("REAL-TIME MEMORY USAGE GRAPH");
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.18f, 0.80f, 0.44f, 1.00f));
    ImGui::PlotLines("##RamDetailedHistory", ram.history.data(), static_cast<int>(ram.history.size()), 0, nullptr, 0.0f, 100.0f, ImVec2(-1, 220.0f));
    ImGui::PopStyleColor();
}

void Dashboard::RenderHardwareInfo(SystemInfo& sysInfo) {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.95f, 0.65f, 0.15f, 1.00f), "System Hardware & Configuration");

    if (ImGui::BeginTable("HardwareInfoTable", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Processor (CPU)");
        ImGui::TableNextColumn(); ImGui::TextColored(ImVec4(0.0f, 0.82f, 0.95f, 1.00f), "%s", sysInfo.GetCpuName().c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("System Architecture");
        ImGui::TableNextColumn(); ImGui::Text("%s", sysInfo.GetArchitecture().c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Logical Processors / Cores");
        ImGui::TableNextColumn(); ImGui::Text("%d", sysInfo.GetLogicalCoreCount());

        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("System Uptime");
        ImGui::TableNextColumn(); ImGui::TextColored(ImVec4(0.95f, 0.65f, 0.15f, 1.00f), "%s", sysInfo.GetFormattedUptime().c_str());

        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("MONITORING SETTINGS");
    float interval = sysInfo.GetUpdateInterval();
    if (ImGui::SliderFloat("Refresh Interval (seconds)", &interval, 0.1f, 3.0f, "%.1f s")) {
        sysInfo.SetUpdateInterval(interval);
    }
}
