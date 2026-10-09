#include <lsm/db.h>

std::optional<std::string> DB::get(const std::string& k) const {
    auto it = db_.find(k);
    if (it == db_.end()) {
        return std::nullopt;
    }
    const Record& r = it->second;
    if (r.type == RecordType::TOMB) {
        return std::nullopt;
    }
    return r.value;
}
    
void DB::put(const std::string& k, std::string v_str) {
    Record r;
    r.type = RecordType::VALUE;
    r.value = v_str;
    db_[k] = r;
}
    
void DB::del(const std::string& k) {
    Record r;
    r.type = RecordType::TOMB;
    db_[k] = r;
}

std::vector<DB::KeyInfo> DB::scan() const {
    std::vector<KeyInfo> key_vector;
    key_vector.reserve(db_.size());
    for (auto it = db_.begin(); it != db_.end(); ++it) {
        const auto& key = it->first;
        const auto& record = it->second;

        key_vector.push_back({key, record.type == RecordType::TOMB});
    }

    return key_vector;
}