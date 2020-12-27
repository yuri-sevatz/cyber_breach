# Cyberpunk 2077 - Breach Protocol Solver

## Description

The Cyberpunk 2077 "Breach Protocol Solver" is a **Screen Capture + OCR + Solver** for Cyberpunk 2077 on PC.

My goal was to try and make the Breach Protocol minigame as easy as possible for PC players.

I think the minigame is fun, but I felt it detracts from the mood of the rest of the game, especailly for completionists like myself.

(+ I hate Sudokus, and all brute-force problems :P)

![Screenshot](/SCREENSHOT.png?raw=true "Optional Title")

## Usage

cyber_breach works by either taking a screenshot of a running game, or importing an image from a file.

To run the OCR, cyber_breach needs to know:
1. The buffer length
2. The matrix length
3. The sequence length(s)

The screenshot must have **NOTHING COVERING (A) THE MATRIX BOX, (B) THE BUFFER BOX, OR (C) THE SEQUENCE BOX; INCLUDING THE BLUE CURSOR OR THE TERMINAL USED TO EXECUTE THE SOLVER**.  Anything else covered is fine.

The screenshot must also be **DISPLAYED IN 1080P**.  *(I am still working on support for different resolutions!)*

The breach protocol must not be already started with any boxes clicked, although you can skip INSTALLED sequences by entering a `0` in -s 0,N,M... in their place.

```
Usage: ./cyber_breach [-h] [--path PATH] [--buffer_length BUFFER_LENGTH] [--matrix_length MATRIX_LENGTH] [--sequence_length SEQUENCE_LENGTHS]

Cyberpunk 2077 - Breach Solver

optional arguments:
  -h, --help            show this help message and exit
  --path PATH, -p PATH  input image (default: screen-capture)
```

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
vcpkg install boost opencv opencv[contrib]
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

For the OCR to work, you will also need a copy of the the Tesseract Latin script training data from Google:

https://github.com/tesseract-ocr/tessdata_best/blob/master/script/Latin.traineddata

This data is used for character recognition of the fixed size hexadecimal characters, in the matrix and sequence boxes.

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

- Automatically install Latin tessdata
- Support Resolutions > 1080P (Need lots of high-quality example images of different screens)
