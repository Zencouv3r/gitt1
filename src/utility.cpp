#include "../include/utility.hpp"
#include <chrono>
#include <ctime>

std::string getCurrentTime() {
  auto cltime = std::chrono::system_clock::now();
  std::time_t eptime = std::chrono::system_clock::to_time_t(cltime);

  auto actualTime = std::ctime(&eptime);
  return std::string(actualTime);
}
