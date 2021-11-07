#include <opencv2/core/utils/logger.hpp>

#include <cyber/init.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#ifdef _WIN32
bool init_terminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (SetConsoleMode(hOut, dwMode)) {
                return true;
            }
        }
    }
    return false;
}
#endif // _WIN32

bool init() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_WARNING);
#ifdef _WIN32
    if (!init_terminal()) {
        return false;
    } else if (!IsValidCodePage(CP_UTF8)) {
        return false;
    } else if (!SetConsoleCP(CP_UTF8)) {
        return false;
    } else if (!SetConsoleOutputCP(CP_UTF8)) {
        return false;
    }
#endif // _WIN32
    return true;
}
