#include "../headers/init.hpp"
#include <filesystem>

// function to check if file exist
bool CheckIfRepoExist(std::string path) {
  return std::filesystem::exists(path);
}

// function for initializing repo
void InitRepo(std::string path) {
  if (CheckIfRepoExist(path)) {
    std::cout << "Repository arleady exist";
    return;
  }
  try {
    if (std::filesystem::create_directory(path))
      std::filesystem::create_directory(path + "/objects");
    std::filesystem::create_directory(path + "/refs");
    std::ofstream headFile(path + "/HEAD");

    std::cout << "Repository created succesfully";
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}
