#include "../headers/init.hpp"

#define PATH ".gitt"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No arguments given.";
    return 0;
  }
  std::string command = argv[1];
  if (command == "init")
    InitRepo(PATH);
  else
    std::cout << "Unknown command: " << command;
  return 0;
}
