#include "../headers/repoClass.hpp"
#include "../headers/utility.hpp"
#include <exception>
#include <filesystem>

Repository::Repository(std::string path)
    : path(std::filesystem::absolute(path)) {}

bool Repository::checkIfRepoExists() { return std::filesystem::exists(path); }

void Repository::initRepo() {
  if (checkIfRepoExists()) {
    std::cout << "Repository already exists" << std::endl;
    return;
  }

  try {
    if (std::filesystem::create_directory(path)) {
      std::filesystem::create_directory(path + "/objects");
      std::filesystem::create_directory(path + "/refs");
      std::ofstream head(path + "/HEAD");
      head << "ref: refs/heads/main\n";
      std::ofstream trackedFiles(path + "/TRACKED");
      std::ofstream logFile(path + "/LOG");

      logFile << "------Reposotiry created------" << std::endl
              << "Date:   " << getCurrentTime() << std::endl;

      std::cout << "Repository created successfully" << std::endl;
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

void Repository::log() {
  try {
    std::ifstream logFile(path + "/LOG");
    std::string content, line;

    if (!logFile.is_open())
      throw std::exception();

    while (std::getline(logFile, line)) {
      content += line + "\n";
    }

    logFile.close();

    std::cout << content;
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return;
  }
}

void Repository::status() {
  for (const auto &entry : std::filesystem::directory_iterator("")) {
    if (entry.is_directory()) {
      std::cout << entry.path().filename() << std::endl;
      Repository subdirectory(
          entry.path()
              .string());    // Create new Repository instance for subdirectory
      subdirectory.status(); // Recursively call status on subdirectory
    }
  }
}
