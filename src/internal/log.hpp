#pragma once

#include <iostream>
#include <spdlog/fmt/fmt.h>

#define DEBUG(FORMAT, ...) // std::cout << fmt::format(FORMAT, ##__VA_ARGS__) << std::endl;
#define INFO(FORMAT, ...) std::cout << fmt::format(FORMAT, ##__VA_ARGS__) << std::endl;
#define ERR(FORMAT, ...) std::cout << fmt::format(FORMAT, ##__VA_ARGS__) << std::endl;