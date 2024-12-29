#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

class Repository {
private:
  std::string path;
  std::string trackedDirPath;

public:
  Repository(std::string path);
  bool checkIfRepoExists();
  void initRepo();
  void log();
  void status();
};
