#pragma once

#include <string>
#include <optional>
#include <map>

class DB {
  private:
    std::map<std::string, std::string> db_;

  public:
    std::optional<std::string> get(const std::string& k);
    void put(const std::string& k, std::string v);
    void del(const std::string& k);
};