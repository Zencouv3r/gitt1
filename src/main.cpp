#include "../include/repoClass.hpp"
#include "../include/utility.hpp"
#include <filesystem>

#define FOLDERNAME ".gitt/"

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
  // else if (command == "add")
  //   add();
  else
    std::cout << "Unknown command: " << command;
  return 0;
}
