#include "../include/repo.hpp"
#include "../include/utility.hpp"
#include <filesystem>
#include <iostream>
int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No arguments given.";
    return 0;
  }

  Repository repo(std::filesystem::current_path().filename());

  std::string command = argv[1];
  if (command == "init")
    repo.initRepo();
  else if (command == "log")
    repo.log();
  else if (command == "status")
    repo.status();
  else if (command == "add") {
    Files filesToStage;
    if (argc < 3)
      std::cout << "Nothing to index\n";
    for (int i = 2; i < argc; ++i) {
      if (std::filesystem::exists(argv[i])) {
        filesToStage.add(File(argv[i]));
      } else
        std::cout << "File not found: " << argv[i] << "\n";
    }
    repo.add(filesToStage);
  } else
    std::cout << "Unknown command: " << command;
  return 0;
}
