#include "../headers/repoClass.hpp"

#define PATH ".gitt"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No arguments given.";
    return 0;
  }

  Repository repo(PATH);

  std::string command = argv[1];
  if (command == "init")
    repo.initRepo();
  else if (command == "log")
    repo.log();
  // else if (command == "status")
  //   status();
  // else if (command == "add")
  //   add();
  else
    std::cout << "Unknown command: " << command;
  return 0;
}
