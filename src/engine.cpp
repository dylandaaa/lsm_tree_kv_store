#include <lsm/db.h>

std::optional<std::string> DB::get(const std::string& k) {
    auto it = db_.find(k);
    if (it == db_.end()) {
        return std::nullopt;
    }
    Value& v = it->second;
    ValueType vType = v.type;
    if (vType == ValueType::TOMB) {
        return std::nullopt;
    }
    return v.value;
}
    
void DB::put(const std::string& k, std::string v_str) {
    Value v;
    v.type = ValueType::VALUE;
    v.value = v_str;
    db_[k] = v;
}
    
void DB::del(const std::string& k) {
    Value v;
    v.type = ValueType::TOMB;
    db_[k] = v;
}