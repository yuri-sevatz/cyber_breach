# Cyberpunk 2077 - Breach Protocol Auto-Solver

## Description

The Cyberpunk 2077 "Breach Protocol Auto-Solver" is a **Screen Capture + OCR + Solver + Auto-Clicker** for Breaches in Cyberpunk 2077 on PC.

My goal was to try and make the Breach Protocol minigame as easy as possible for PC players.

I think the minigame is fun, but I felt it detracts from the explosive ascension in the rest of the game, especailly for completionists like myself!

(+ I hate Sudokus, and all brute-force problems :P)

![Preview](/PREVIEW.apng?raw=true "Animated Preview")

## Usage

cyber_breach works by taking a screenshot of a running game, parsing it, solving it, and then generating clicks on the running game.

```
Usage: cyber_breach.exe [-h] [-l INPUT] [-s OUTPUT] [--interactive] [--no-autoclick]

Cyberpunk 2077 - Breach Protocol Auto-Solver

optional arguments:
  -h, --help            show this help message and exit
  --load INPUT, -l INPUT
                        input file to load screenshot (default: capture)
  --save OUTPUT, -s OUTPUT
                        output directory to save screenshot (default: disabled)
  --interactive, -i
                        enable interactive prompts (default: disabled)
  --no-autoclick
                        disable auto-clicking answer (default: autoclick, iff capture)

By default cyber_breach.exe will capture and auto-click a running copy of CP2077
```

When you launch cyber_breach, it tries to detect from a running instance of CP2077 (or from a previously saved image):

1. The buffer length
2. The matrix length
3. The sequence length(s)

It then performs:

- Optical character recognition on the matrix and sequences
- Calculates the highest scoring path through the matrix
- Displays the result on-screen

Additionally, if a screenshot was captured from a live game, it can:

- Generate mouse movements and clicks, to auto-solve most breaches in **less than 1/2 a second.**

It does all this without touching any of the in-game memory, so it's safe to use without any long-term effects.

You can also launch cyber_breach on a previously saved image.  Or you can instruct cyber_breach to save newly captured screenshots to a directory of your choosing.  Saved screenshots might be useful if cyber_breach cannot solve a particular breach, or if you are afraid of it making mistakes (though you may be hard-pressed to ever find any =P).  Saved images may be useful if filing Github Issues for new resolutions, and for developers to add expanding detection.

## Requirements

- The screenshot must be **FROM A 1080P DISPLAY**.  *(I am still working on support for different resolutions!)*

- The breach **MUST NOT HAVE ALREADY BEEN STARTED** with any boxes clicked, although pre-installed sequences are automatically skipped by the solver if detected.  *(i.e. You'll be good as long as none of the boxes in the matrix have already been clicked)*

## Build Dependencies

### Windows

- Visual Studio 2019 (with "Desktop Development with C++") or Build Tools for Visual Studio 2019 (with "MSVC142")
- Boost
- CMake
- OpenCV
- OpenCV Contrib
- TermColor
- Tesseract

### Linux

- Boost
- CMake
- OpenCV
- OpenCV Contrib
- TermColor
- Tesseract

## Compiling

### Windows
```
cd C:\
mkdir src && cd src
git clone git@github.com:microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install boost:x64-windows opencv:x64-windows opencv[contrib]:x64-windows termcolor:x64-windows
cd ..
git clone git@github.com:yuri-sevatz/cyberpunk-cpp.git
cd cyberpunk-cpp
git submodule update --init
mkdir build && cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DBUILD_TESTING:BOOL=OFF" "-DCYBER_BUNDLE_TESSDATA:BOOL=ON"
cmake --build . --config Release
```

Resulting binary is stored in C:\src\cyberpunk-cpp\build\bin\Release\*

### Linux

```
cd ~
git clone git@github.com:yuri-sevatz/cyberpunk-cpp.git
cd cyberpunk-cpp
mkdir build; cd build
cmake ..
cmake --build . --config Release
```

Resulting binary is stored in ~\cyberpunk-cpp\build\bin\*

## TODO

- Support Resolutions > 1080P (Need lots of high-quality example images of different screens)
