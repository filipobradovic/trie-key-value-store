#include <Trie.h>
#include <gtest/gtest.h>

TEST(SimpleTrieTest, Insert)
{
    std::unique_ptr<Trie> trie = std::make_unique<Trie>();

    EXPECT_TRUE(trie->insert<int>("abc", 10));
    EXPECT_TRUE(trie->insert<double>("mnbn", 11.0));
    EXPECT_TRUE(trie->insert<int>("mn", 12));
    EXPECT_TRUE(trie->insert<double>("abcc", 13.6));
    EXPECT_TRUE(trie->insert<int>("abcd", 14));
    EXPECT_TRUE(trie->insert<double>("abce", 15.0));
    EXPECT_TRUE(trie->insert<int>("abccd", 16));
    EXPECT_FALSE(trie->insert<int>("abc", 17));
    EXPECT_FALSE(trie->insert<int>("abcd", 18));
    EXPECT_FALSE(trie->insert<int>("mn", 19));
}

TEST(SimpleTrieTest, Delete)
{
    std::unique_ptr<Trie> trie = std::make_unique<Trie>();

    EXPECT_TRUE(trie->insert<int>("abc", 10));
    EXPECT_TRUE(trie->insert<double>("mnbn", 11.0));
    EXPECT_TRUE(trie->insert<int>("mn", 12));
    EXPECT_TRUE(trie->insert<double>("abcc", 13.6));
    EXPECT_TRUE(trie->insert<int>("abcd", 14));
    EXPECT_TRUE(trie->insert<double>("abce", 15.0));
    EXPECT_TRUE(trie->insert<int>("abccd", 16));
    EXPECT_TRUE(trie->insert<int>("mne", 17));
    EXPECT_FALSE(trie->insert<int>("abc", 17));
    EXPECT_FALSE(trie->insert<int>("abcd", 18));
    EXPECT_FALSE(trie->insert<int>("mn", 19));

    EXPECT_TRUE(trie->remove("abc"));
    EXPECT_TRUE(trie->remove("mn"));
    EXPECT_TRUE(trie->remove("mne"));
    EXPECT_TRUE(trie->remove("abce"));
    EXPECT_TRUE(trie->remove("abcc"));
    EXPECT_FALSE(trie->remove("abce"));
    EXPECT_FALSE(trie->remove("aaa"));
    EXPECT_FALSE(trie->remove("mne"));

    bool status = false;
    int tmp_int = -1;
    double tmp_double = -1.0;

    tmp_int = trie->get_value<int>("abccd", &status);
    EXPECT_EQ(tmp_int, 16);
    EXPECT_TRUE(status);

    tmp_int = trie->get_value<int>("abcd", &status);
    EXPECT_EQ(tmp_int, 14);
    EXPECT_TRUE(status);

    tmp_double = trie->get_value<double>("mnbn", &status);
    EXPECT_EQ(tmp_double, 11.0);
    EXPECT_TRUE(status);

    tmp_double = trie->get_value<double>("abbc", &status);
    EXPECT_FALSE(status);

    tmp_double = trie->get_value<double>("mne", &status);
    EXPECT_FALSE(status);
}

TEST(SimpleTrieTest, GetValue)
{
    std::unique_ptr<Trie> trie = std::make_unique<Trie>();

    EXPECT_TRUE(trie->insert<int>("abc", 10));
    EXPECT_TRUE(trie->insert<double>("mnbn", 11.0));
    EXPECT_TRUE(trie->insert<int>("mn", 12));
    EXPECT_TRUE(trie->insert<double>("abcc", 13.6));
    EXPECT_TRUE(trie->insert<int>("abcd", 14));
    EXPECT_TRUE(trie->insert<double>("abce", 15.0));
    EXPECT_TRUE(trie->insert<int>("abccd", 16));
    EXPECT_FALSE(trie->insert<int>("abc", 17));
    EXPECT_FALSE(trie->insert<int>("abcd", 18));
    EXPECT_FALSE(trie->insert<int>("mn", 19));

    bool status = false;
    int tmp_int = -1;
    double tmp_double = -1.0;

    tmp_int = trie->get_value<int>("abccd", &status);
    EXPECT_EQ(tmp_int, 16);
    EXPECT_TRUE(status);

    tmp_int = trie->get_value<int>("abcd", &status);
    EXPECT_EQ(tmp_int, 14);
    EXPECT_TRUE(status);

    tmp_double = trie->get_value<double>("mnbn", &status);
    EXPECT_EQ(tmp_double, 11.0);
    EXPECT_TRUE(status);

    tmp_double = trie->get_value<double>("abbc", &status);
    EXPECT_FALSE(status);

    tmp_double = trie->get_value<double>("mne", &status);
    EXPECT_FALSE(status);

    tmp_double = trie->get_value<double>("abcd", &status);
    EXPECT_FALSE(status);
}
