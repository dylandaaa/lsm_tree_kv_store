#include <gtest/gtest.h>
#include <lsm/db.h>

// Unit tests for the engine module.
TEST(DBTest, OverwriteReturnsNewestValue) {
    // This test tests if the put operation overwrittes values given the same key but different value
    DB test_db{};

    test_db.put("test_key", "test_val_1");
    test_db.put("test_key", "test_val_2");

    auto result = test_db.get("test_key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "test_val_2");
}

TEST(DBTest, GetOnDeletedKeyReturnsEmpty) {
    // This test tests if a deleted key returns empty
    DB test_db{};

    test_db.put("test_key", "test_val_1");
    test_db.del("test_key");

    auto result = test_db.get("test_key");
    EXPECT_FALSE(result.has_value());
}

TEST(DBTest, GetOnMissingKeyReturnsEmpty) {
    // This test tests if get on a non-existing key returns empty
    DB test_db{};

    auto result = test_db.get("test_key");

    EXPECT_FALSE(result.has_value());
}

TEST(DBTest, DeleteOnMissingKeyIsSafeAndReadsEmpty) {
    // This test tests if deleting a non-existing key and retrieving it returns empty
    DB test_db{};

    test_db.del("test_key");
    auto result = test_db.get("test_key");

    EXPECT_FALSE(result.has_value());
}

TEST(DBTest, KeysIterateInSortedOrder) {
    // This test tests if the iterator returns a sorted vector
    DB test_db{};
    std::vector<DB::KeyInfo> key_vector;
    std::vector<DB::KeyInfo> sorted_key_vector = {
        {"test_key_1", false},
        {"test_key_2", true},
        {"test_key_3", false},
        {"test_key_4", false},
        {"test_key_5", false}
    };

    test_db.put("test_key_5", "test_value_5");
    test_db.put("test_key_3", "test_value_3");
    test_db.put("test_key_1", "test_value_1");
    test_db.put("test_key_2", "test_value_2");
    test_db.put("test_key_4", "test_value_4");
    
    test_db.del("test_key_2");

    key_vector = test_db.scan();
    
    EXPECT_EQ(key_vector, sorted_key_vector);
}