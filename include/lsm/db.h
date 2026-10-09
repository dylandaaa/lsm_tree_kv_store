#pragma once

#include <string>
#include <optional>
#include <map>

class DB {
  public:
    std::optional<std::string> get(const std::string& k);
    void put(const std::string& k, std::string v_str);
    void del(const std::string& k);

  private:
    enum class ValueType {
        VALUE,
        TOMB
    };

    struct Value {
        ValueType type;
        std::string value;
        };

    std::map<std::string, Value> db_;
};