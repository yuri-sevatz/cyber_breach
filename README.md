# Cyberpunk 2077 - Breach Protocol Auto Solver

## Description

The Cyberpunk 2077 "Breach Protocol Auto Solver" is a **Screen Capture + OCR + Auto Solver** for Cyberpunk 2077 on PC.

My goal was to try and make the Breach Protocol minigame as easy as possible for PC players.

I think the minigame is fun, but I felt it detracts from the mood of the rest of the game, especailly for completionists like myself.

(+ I hate Sudokus, and all brute-force problems :P)

![Screenshot](/SCREENSHOT.png?raw=true "Optional Title")

## Usage

cyber_breach works by either taking a screenshot of a running game, or importing an image from a file.


```
Usage: cyber_breach.exe [-h] [--load INPUT] [--save OUTPUT]

Cyberpunk 2077 - Breach Solver
  
optional arguments:
  -h, --help            show this help message and exit
  --load INPUT, -l INPUT
                        input image to load screenshot (default: screenshot)
  --save OUTPUT, -s OUTPUT
                        output dir to save screenshot (default: disabled)

By default, cyber_breach.exe will take screenshots from a running copy of CP2077
```

When you launch cyber_breach, it tries to detect from a running instance of CP2077 (or from a previously saved image):

1. The buffer length
2. The matrix length
3. The sequence length(s)

It then performs:

- Optical character recognition on the matrix and sequences
- Calculates the highest scoring path through the matrix
- Displays the result on-screen

You can optionally launch cyber_breach on a saved image.  You can also tell cyber_breach to save newly captured screenshots to a directory of your choosing.

## Requirements

- The screenshot must be **FROM A 1080P DISPLAY**.  *(I am still working on support for different resolutions!)*

- The breach **MUST NOT HAVE ALREADY BEEN STARTED** with any boxes clicked, although pre-installed sequences are automatically skipped by the solver if detected.  *(i.e. You'll be good as long as none of the boxes in the matrix have already been clicked)*

- The screenshot must have nothing covering **(A) THE MATRIX BOX**, **(B) THE BUFFER BOX**, or **(C) THE SEQUENCE BOX**; including **THE BLUE CURSOR** or **ANY WINDOW** you used to launch the solver.  Covering any other part of Breach Protocol screen outside of the above exceptions is fine.

## Build Dependencies

### Windows

- Visual Studio 2019 (with "Desktop Development with C++") or Build Tools for Visual Studio 2019 (with "MSVC142")
- CMake

### Linux

- CMake
- Boost
- OpenCV
- OpenCV Contrib
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
mkdir build && cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake"
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

## Runtime Dependencies

For the OCR to work, you will also need a copy of the the Tesseract Latin script training data from Google.  This data is already included in all pre-built releases.

https://github.com/tesseract-ocr/tessdata_best/blob/master/script/Latin.traineddata

The training data is used for character recognition of the fixed size hexadecimal characters, in the matrix and sequence boxes.

### Windows

```
cd C:\src\cyberpunk-cpp\build\bin\Release
mkdir tessdata && cd tessdata
curl -o Latin.traineddata https://raw.githubusercontent.com/tesseract-ocr/tessdata_best/master/script/Latin.traineddata
```

### Linux

```
cd ~/cyberpunk-cpp/build/bin
mkdir tessdata; cd tessdata
wget https://raw.githubusercontent.com/tesseract-ocr/tessdata_best/master/script/Latin.traineddata
```

## TODO

- Automatically install Latin tessdata with cmake
- Support Resolutions > 1080P (Need lots of high-quality example images of different screens)
