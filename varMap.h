#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

// Extend this class to add
// your own vars map implementation.
template <class T>
class varMap {
private:
  bool selfMap;
  std::map<std::string, T>* _map;

  // Used as return value of varMap::operator[]()
  class reference {
    varMap<T> &vmap;
    const std::string& key;
  public:
    reference(varMap<T>& vmap, const std::string& key) : vmap(vmap), key(key) {}

    // For implicit coercion to T:
    T& operator= (T val);
    // For implicit coercion to ref e.g. map[val] = map[val2]:
    T& operator= (reference ref);
    operator T();
  };

public:
  varMap(std::map<std::string, T>* map = 0);

  virtual ~varMap();

  // No need to overwrite this function when subclassing
  reference operator[](const std::string& key);

  // To extend overwrite these functions:
  virtual T* find(const std::string& key);
  virtual T& set(const std::string& key, T value);
  virtual void erase(const std::string& key);
};
