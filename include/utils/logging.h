#ifndef UTILS_LOGGING_H
#define UTILS_LOGGING_H

#include <iostream>

#define LOG_INFO(msg) std::cout << "INFO: " << msg << std::endl
#define LOG_ERROR(msg) std::cerr << "ERROR: " << msg << std::endl
#define log std::cout

#endif  // UTILS_LOGGING_H