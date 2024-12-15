#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

class Repository {
private:
  std::string path;

public:
  Repository(std::string path);
  bool checkIfRepoExists();
  void initRepo();
  void log();
  void status();
};
