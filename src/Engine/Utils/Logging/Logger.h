#ifndef OPENGL_LOGGER_H
#define OPENGL_LOGGER_H

#include <string>
#include <iostream>
#include <iomanip>

enum LogType {
    INFO,
    DEBUG,
    ERROR,
    WARNING
};

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST


class Logger {
    public:

        inline static std::vector<std::string> buffer;

        template <typename T>
        static void Log(LogType type, T caller, const std::stringstream & ss) {
            Logger::Log(type, caller, ss.str());
        }

        template <typename T>
        static void Log(LogType type, T caller, const std::string & message) {
            std::stringstream ss;

            std::string typeMessage;

            switch(type) {

                case INFO:
                    typeMessage = BOLD(FGRN("INFO"));
                    break;
                case DEBUG:
                    typeMessage = BOLD(FCYN("DEBUG"));
                    break;
                case ERROR:
                    typeMessage = BOLD(FRED("ERROR"));
                    break;
                case WARNING:
                    typeMessage = BOLD(FYEL("WARNING"));
                    break;
            }

            time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            std::string timeStr = ctime(&tt);
            timeStr.erase(std::remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());

            ss << std::left << std::setw(25);
            ss << std::setw(30) << timeStr;

            if (caller != nullptr) {
                ss << std::setw(25) << typeid(T).name();
            }
            ss << message << std::endl;

            buffer.push_back(ss.str());
        }

        static void Log(const std::string & s) {
            Logger::Log(INFO, nullptr, s);
        }
};

#endif //OPENGL_LOGGER_H
