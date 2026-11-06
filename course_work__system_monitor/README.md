# System Monitor

A Windows desktop system monitoring application developed in C++ using Dear ImGui, GLFW and the Windows API.

## Technologies

- **C++** – Main programming language.
- **Dear ImGui** – Graphical user interface.
- **GLFW** – Window management and input handling.
- **OpenGL** – Graphics rendering.
- **Windows API** – Retrieving system information.
- **CMake** – Project build configuration.
- **GCC (MinGW-w64)** – C++ compiler.

## Features

- CPU usage monitoring.
- RAM usage monitoring.
- CPU core information.
- System uptime.
- Live monitoring dashboard.
- Historical performance charts.

## Requirements

- Windows 10 or newer.
- MSYS2 with UCRT64 environment.
- GCC / G++ compiler.
- Git.
- CMake.
- Ninja.

## Installation

### 1. Install MSYS2 dependencies

Open the **MSYS2 UCRT64** terminal.

Update the package database and installed packages:

```bash
pacman -Syu
```

If requested, restart the terminal and run the update again.

Install the required development packages:

```bash
pacman -S --needed \
    mingw-w64-ucrt-x86_64-gcc \
    mingw-w64-ucrt-x86_64-cmake \
    mingw-w64-ucrt-x86_64-ninja \
    mingw-w64-ucrt-x86_64-glfw \
    mingw-w64-ucrt-x86_64-gdb \
    git
```

### 2. Clone the repository

```bash
git clone --recurse-submodules YOUR_REPOSITORY_URL
```

### 3. Dear ImGui

Dear ImGui is included as a Git submodule in:

```text
libs/imgui/
```

If the submodule was not downloaded during cloning:

```bash
git submodule update --init --recursive
```

### 4. Build

#### Build Workflow

```text
[ VS Code Editor ] ──> [ Extensions ] ──> [ System Compiler ]
                       • C/C++            • GCC  (or Clang, MSVC)
                       • CMake Tools
```

#### Terminal Build

Open **MSYS2 UCRT64** terminal and navigate to the `course_work__system_monitor` directory:

```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```

Run the application:

```bash
./SystemMonitor.exe
```

## Project Structure

```text
SystemMonitor/
│
├── include/
│   ├── SystemInfo.h
│   └── Dashboard.h
│
├── src/
│   ├── main.cpp
│   ├── SystemInfo.cpp
│   └── Dashboard.cpp
│
├── libs/
│   └── imgui/
│
├── CMakeLists.txt
└── README.md
```

## License

This project is developed for educational purposes.

Dear ImGui and other third-party dependencies retain their respective licenses.
