#include <string>
#include <unordered_map>

class Commit {
private:
  std::string id;
  std::string message;
  std::string author;
  std::time_t time;
  std::unordered_map<std::string, std::string> changes;

public:
  void commit();
  std::string hash();
};
