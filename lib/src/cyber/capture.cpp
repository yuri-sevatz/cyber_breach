#include <cyber/capture.hpp>
#include <cyber/mouse.hpp>

#include <iostream>
#include <vector>

#include <Windows.h>

namespace {

/**
 * Create a Bitmap file header..
 *
 * @param widht     : image width.
 * @param height    : image height.
 *
 * @return Bitmap header.
 */
BITMAPINFOHEADER createBitmapHeader(int width, int height) {
    BITMAPINFOHEADER  bi;

    // create a bitmap
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    return bi;
}

/**
 * Capture a screen window as a matrix.
 *
 * @param hwnd : window handle.
 *
 * @return Mat (Mat of the captured image)
 */
cv::Mat captureScreenMat(HWND hwnd) {
    // Retrieve handle to the display device context
    HDC hdcScreen = GetDC(NULL);
    if (!hdcScreen) {
        std::cerr << "GetDC returned NULL" << std::endl;
        return cv::Mat();
    }

    // Create a compatible DC, which is used in a BitBlt from the ScreenDC
    HDC hdcScreenCompatibleDC = CreateCompatibleDC(hdcScreen);
    if (!hdcScreenCompatibleDC) {
        std::cerr << "CreateCompatibleDC returned NULL" << std::endl;
        return cv::Mat();
    }

    // Get the window area for size calculation
    RECT rect;
    if (!GetWindowRect(hwnd, &rect)) {
        std::cerr << "GetWindowRect returned FALSE" << std::endl;
        return cv::Mat();
    }

    int screenx = rect.left;
    int screeny = rect.top;
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // create a bitmap
    HBITMAP hbwindow = CreateCompatibleBitmap(hdcScreen, width, height);
    if (!hbwindow) {
        std::cerr << "CreateCompatibleBitmap returned NULL" << std::endl;
        return cv::Mat();
    }

    BITMAPINFOHEADER bi = createBitmapHeader(width, height);

    // use the previously created device context with the bitmap
    if (!SelectObject(hdcScreenCompatibleDC, hbwindow)) {
        std::cerr << "SelectObject returned NULL" << std::endl;
        return cv::Mat();
    }

    // This is the best stretch mode
    SetStretchBltMode(hdcScreenCompatibleDC, COLORONCOLOR);

    // The source DC is the entire screen, and the destination is the screen compatible DC
    if (!StretchBlt(hdcScreenCompatibleDC, 0, 0, width, height, hdcScreen, screenx, screeny, width, height, SRCCOPY)) {
        std::cerr << "StretchBlt returned NULL" << std::endl;
        return cv::Mat();
    }

    // create mat object
    cv::Mat mat;
    mat.create(height, width, CV_8UC4);

    // Gets the "bits" from the bitmap, and copies them into the buffer that's pointed to by mat.data
    GetDIBits(hdcScreenCompatibleDC, hbwindow, 0, height, mat.data, (BITMAPINFO*) &bi, DIB_RGB_COLORS);

    // avoid memory leak
    if (!DeleteObject(hbwindow)) {
        std::cerr << "DeleteObject returned FALSE" << std::endl;
    }
    if (!DeleteDC(hdcScreenCompatibleDC)) {
        std::cerr << "DeleteDC returned FALSE" << std::endl;
    }
    if (!ReleaseDC(NULL, hdcScreen)) {
        std::cerr << "ReleaseDC returned NULL" << std::endl;
    }

    return mat;
}

} // namespace

cv::Mat capture(const char * name) {
    HWND hwnd = FindWindowA(NULL, name);
    if (!hwnd) {
        std::cerr << "FindWindowA returned NULL" << std::endl;
        return cv::Mat();
    }

    if (!SetForegroundWindow(hwnd)) {
        std::cerr << "SetForegroundWindow returned NULL" << std::endl;
        return cv::Mat();
    }

    const std::chrono::seconds wait(5);
    const std::chrono::high_resolution_clock::duration poll = std::chrono::milliseconds(100);
    const std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    const std::chrono::high_resolution_clock::time_point finish = start + wait;
    while (GetForegroundWindow() != hwnd) {
        if (finish < std::chrono::high_resolution_clock::now()) {
            std::cerr << "GetForegroundWindow failed after " << wait.count() << " seconds" << std::endl;
            return cv::Mat();
        } else {
            std::this_thread::sleep_for(poll);
        }
    }

    mouse_move(cv::Point(-65535,-65535));
    std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)) / 10 /* FPS */);

    cv::Mat src = captureScreenMat(hwnd);
    if (src.empty()) {
        return cv::Mat();
    }

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGRA2BGR);
    return dst;
}
