#include "../headers/repoClass.hpp"

Repository::Repository(std::string path) : path(path) {}

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
      logFile << "Repo init";
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

    while (std::getline(logFile, line)) {
      content += line;
    }

    logFile.close();

    std::cout << content;
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return;
  }
}

void Repository::status() {}
