#include "varMap.h"

T& varMap::reference::operator= (T val) {
  return vmap.set(key, val);
}

T& varMap::reference::operator= (reference ref) {
  return vmap.set(key, ref);
}

varMap::reference::operator T() {
  T* val = vmap.find(key);
  if(val)
    return *val;
  else
    throw std::domain_error(
        "Unable to find the variable '" + key + "'.");
}

varMap::varMap(std::map<std::string, T>* map) {
  if(map) {
    _map = map;
    selfMap = false;
  } else {
    _map = new std::map<std::string, T>();
    selfMap = true;
  }
}

varMap::~varMap() {
  if(selfMap) {
    delete _map;
  }
}

// No need to overwrite this function when subclassing
varMap::reference varMap::operator[](const std::string& key) {
  return reference(*this, key);
}

T* varMap::find(const std::string& key) {
  std::map<std::string, T>::iterator it = _map->find(key);
  if(it != _map->end()) {
    return &(_map->find(key)->second);
  }
  return NULL;
}

T& varMap::set(const std::string& key, T value) {
  (*_map)[key] = value;
  return (*_map)[key];
}

void varMap::erase(const std::string& key) {
  _map->erase(key);
}
