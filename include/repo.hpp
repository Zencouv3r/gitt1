#include "../include/files.hpp"
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
  void add(Files filesToStage);
};
