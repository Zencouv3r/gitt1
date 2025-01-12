#include "../include/repo.hpp"
#include "../include/utility.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

#define FOLDERNAME ".gitt"

Repository::Repository(std::string path) : path(std::filesystem::path(path)) {};

bool Repository::checkIfRepoExists() {
  return std::filesystem::exists(FOLDERNAME);
}

void Repository::initRepo() {
  if (checkIfRepoExists()) {
    std::cout << "Repository already exists" << std::endl;
    return;
  }
  std::string trackedDirPath =
      std::filesystem::absolute(std::filesystem::current_path());
  try {
    if (std::filesystem::create_directory(std::string(FOLDERNAME))) {
      std::filesystem::create_directory(std::string(FOLDERNAME) + "/objects");
      std::filesystem::create_directory(std::string(FOLDERNAME) + "/refs");
      std::ofstream head(std::string(FOLDERNAME) + "/HEAD");
      head << "ref: refs/heads/main\n";
      std::ofstream index(std::string(FOLDERNAME) + "/INDEX");
      std::ofstream logFile(std::string(FOLDERNAME) + "/LOG");

      logFile << "------Repository created------" << std::endl
              << "Date:   " << getCurrentTime() << std::endl;

      index.close();
      logFile.close();

      std::cout << "Repository created successfully" << std::endl;
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

void Repository::log() {
  try {
    std::ifstream logFile(std::string(FOLDERNAME) + "/LOG");
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
  try {
    if (!checkIfRepoExists()) {
      std::cout << "Repository does not exist!" << std::endl;
      return;
    }

    Files indexedFiles;
    Files actualFiles;

    std::filesystem::recursive_directory_iterator dirIterator(
        std::filesystem::absolute(path).parent_path());
    std::filesystem::recursive_directory_iterator endIterator;

    // Iterate through each file in the repo
    for (; dirIterator != endIterator; ++dirIterator) {
      if (std::filesystem::is_regular_file(dirIterator->path())) {
        std::string pathStr =
            std::filesystem::relative(dirIterator->path()).string();
        if (pathStr.find('.'))
          actualFiles.add(File(std::filesystem::relative(dirIterator->path())));
      }
    }
    indexedFiles.deserialize(std::string(FOLDERNAME) + "/INDEX");

    for (auto &actualFile : actualFiles) {
      if (!indexedFiles.isContain(actualFile))
        std::cout << "Detected not indexed files: " << actualFile.getPath()
                  << "\n";
    }

  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

void Repository::add(Files filesToStage) {
  filesToStage.serialize(std::string(FOLDERNAME) + "/INDEX");
}
