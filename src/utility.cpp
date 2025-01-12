#include "../include/utility.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <vector>

std::string getCurrentTime() {
  auto cltime = std::chrono::system_clock::now();
  std::time_t eptime = std::chrono::system_clock::to_time_t(cltime);

  auto actualTime = std::ctime(&eptime);
  return std::string(actualTime);
}

std::string getFileHash(const std::string &filePath) {
  // Open the file in binary mode
  std::ifstream file(filePath, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file.");
  }

  // Create a SHA256 context
  SHA256_CTX sha256;
  SHA256_Init(&sha256);

  // Read the file in chunks and update the hash
  const size_t bufferSize = 8192; // 8 KB buffer
  std::vector<char> buffer(bufferSize);
  while (file) {
    file.read(buffer.data(), bufferSize);
    SHA256_Update(&sha256, buffer.data(), file.gcount());
  }

  // Finalize the hash
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_Final(hash, &sha256);

  // Convert the hash to a hex string
  std::ostringstream oss;
  for (unsigned char c : hash) {
    oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
  }

  return oss.str();
}
