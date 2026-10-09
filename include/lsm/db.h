#pragma once

#include <string>
#include <optional>
#include <map>
#include <vector>

class DB {
  public:
    enum class RecordType {
        VALUE,
        TOMB
    };

    struct KeyInfo {
        std::string key;
        bool is_deleted;

        friend bool operator==(const KeyInfo& a, const KeyInfo& b) {
          return (a.key == b.key) && (a.is_deleted == b.is_deleted);
        }
    };

    std::optional<std::string> get(const std::string& k) const;
    void put(const std::string& k, std::string v_str);
    void del(const std::string& k);
    std::vector<KeyInfo> scan() const;

  private:
    struct Record {
        RecordType type;
        std::string value;
        };

    std::map<std::string, Record> db_;
};