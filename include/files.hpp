#include <string>
#include <vector>

class File {
private:
  std::string name;
  std::string path;
  std::string hash;

public:
  File(std::string path);
  File(std::string name, std::string path, std::string hash);
  std::string getName();
  std::string getHash();
  std::string getPath();
  bool operator!=(const File &other) const;
  bool operator==(const File &other) const;
};

class Files {
private:
  std::vector<File> files;
  int filesCount;

public:
  Files();
  void add(File file);
  void serialize(std::string path);
  void deserialize(std::string path);
  int getSize();
  File getFile(int index);
  File &operator[](int index);
  bool isContain(File file);
  bool isEmpty();
  std::vector<File>::iterator begin();
  std::vector<File>::iterator end();
  Files compareFiles(Files other);
};
