#include "../include/files.hpp"
#include "../include/utility.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

File::File(std::string path) {
  name = std::filesystem::path(path).filename();
  this->path = path;
  hash = getFileHash(path);
}

File::File(std::string name, std::string path, std::string hash)
    : name(name), path(path), hash(hash) {};

std::string File::getName() { return name; }

std::string File::getHash() { return hash; }

std::string File::getPath() { return path; }

bool File::operator!=(const File &other) const {
  return name != other.name && hash != other.hash && path != other.path;
};

bool File::operator==(const File &other) const {
  return name == other.name && hash == other.hash && path == other.path;
};

Files::Files() { filesCount = 0; };

void Files::add(File file) {
  files.push_back(file);
  filesCount++;
};

void Files::serialize(std::string path) {

  Files indexedFiles;
  indexedFiles.deserialize(path);

  for (auto &file : files)
    if (!indexedFiles.isContain(file))
      indexedFiles.add(file);

  std::ofstream outputFile(path, std::ios::binary);

  for (auto &file : indexedFiles) {
    std::string fileData = "[" + file.getName() + "][" + file.getPath() + "][" +
                           file.getHash() + "]";
    size_t size = fileData.size();
    outputFile.write(reinterpret_cast<char *>(&size), sizeof(size));
    outputFile.write(&fileData[0], size);
  }
  outputFile.close();
}

void Files::deserialize(std::string path) {
  std::ifstream inputFile(path);
  std::string fileData = "";
  while (!inputFile.eof()) {
    size_t size = 0;
    inputFile.read(reinterpret_cast<char *>(&size), sizeof(size));
    fileData.resize(size);
    if (size == 0)
      break;
    inputFile.read(&fileData[0], size);

    std::string fileName = "";
    std::string filePath = "";
    std::string fileHash = "";

    for (int i = 1; fileData[i] != ']'; ++i) {
      fileName += fileData[i];
    }

    // [name][dir / name][efhqf823u424hfhu3i4sadxz]

    for (int i = fileName.size() + 3; fileData[i] != ']'; ++i) {
      filePath += fileData[i];
    }

    for (int i = fileName.size() + filePath.size() + 5; fileData[i] != ']';
         ++i) {
      fileHash += fileData[i];
    }
    this->add(File(fileName, filePath, fileHash));
  }
};

int Files::getSize() { return filesCount; }

File Files::getFile(int index) { return files[index]; }

File &Files::operator[](int index) { return files[index]; }

std::vector<File>::iterator Files::begin() { return files.begin(); };

std::vector<File>::iterator Files::end() { return files.end(); };

bool Files::isContain(File comparableFile) {
  for (auto &file : files) {
    // std::cout << "comparing: " << file.getPath() << " " << file.getHash()
    //           << " and " << comparableFile.getPath() << " "
    //           << comparableFile.getHash() << "\n";
    if (file == comparableFile)
      return true;
  }
  return false;
};

bool Files::isEmpty() { return files.empty(); };

Files Files::compareFiles(Files other) {
  // Files differentFiles;
  // for(auto& file : *this)
  return Files();
};
