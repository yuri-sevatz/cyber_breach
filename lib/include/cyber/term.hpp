#pragma once

#include <termcolor/termcolor.hpp>

#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_OS_WINDOWS
#elif defined(__APPLE__)
#   define TERMCOLOR_OS_MACOS
#elif defined(__unix__) || defined(__unix)
#   define TERMCOLOR_OS_LINUX
#else
#   error unsupported platform
#endif


namespace term {
    using namespace termcolor;

    inline
    std::ostream& high_grey(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[90m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
            0                                           // grey (black)
        );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_red(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[91m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_RED | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_green(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[92m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_yellow(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[93m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_blue(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[94m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_magenta(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[95m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_cyan(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[96m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& high_white(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[97m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }



    inline
    std::ostream& on_high_grey(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[100m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                0                                           // grey (black)
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_red(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[101m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_RED | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_green(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[102m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_yellow(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[103m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_blue(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[104m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_magenta(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[105m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_cyan(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[106m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
            );
    #endif
        }
        return stream;
    }

    inline
    std::ostream& on_high_white(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
    #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[107m";
    #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
    #endif
        }

        return stream;
    }

} // namespace term

#undef TERMCOLOR_OS_WINDOWS
#undef TERMCOLOR_OS_MACOS
#undef TERMCOLOR_OS_LINUX
