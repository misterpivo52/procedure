
#include <gtest/gtest.h>
extern "C" {
#include "c_list.h"
}

class CListTest : public ::testing::Test {
protected:
    c_list* list;

    void SetUp() override {
        list = create_list(2);
        ASSERT_NE(list, nullptr);
    }

    void TearDown() override {
        if (list != nullptr) {
            list->destroy(list);
        }
    }
};

TEST_F(CListTest, CreateList) {
    EXPECT_EQ(list->size, 0);
    EXPECT_GE(list->capacity, 2);
}

TEST_F(CListTest, AppendInt) {
    int val = 42;
    EXPECT_EQ(list->append(list, &val, int_type), 0);
    EXPECT_EQ(list->size, 1);

    int* result = (int*)list->get(list, 0);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 42);
}

TEST_F(CListTest, AppendFloat) {
    float val = 3.14f;
    EXPECT_EQ(list->append(list, &val, float_type), 0);
    EXPECT_EQ(list->size, 1);

    float* result = (float*)list->get(list, 0);
    ASSERT_NE(result, nullptr);
    EXPECT_FLOAT_EQ(*result, 3.14f);
}

TEST_F(CListTest, AppendString) {
    char* str = (char*)"hello";
    EXPECT_EQ(list->append(list, str, string_type), 0);
    EXPECT_EQ(list->size, 1);

    char* result = (char*)list->get(list, 0);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(CListTest, AppendMultiple) {
    int int_val = 10;
    float float_val = 2.5f;
    char* str_val = (char*)"test";

    list->append(list, &int_val, int_type);
    list->append(list, &float_val, float_type);
    list->append(list, str_val, string_type);

    EXPECT_EQ(list->size, 3);
}

TEST_F(CListTest, Pop) {
    int val = 100;
    list->append(list, &val, int_type);
    EXPECT_EQ(list->size, 1);

    EXPECT_EQ(list->pop(list), 0);
    EXPECT_EQ(list->size, 0);
}

TEST_F(CListTest, PopEmpty) {
    EXPECT_EQ(list->pop(list), -1);
}

TEST_F(CListTest, Set) {
    int val1 = 10;
    int val2 = 20;

    list->append(list, &val1, int_type);
    EXPECT_EQ(list->set(list, 0, &val2, int_type), 0);

    int* result = (int*)list->get(list, 0);
    EXPECT_EQ(*result, 20);
}

TEST_F(CListTest, GetInvalidIndex) {
    EXPECT_EQ(list->get(list, 0), nullptr);
    EXPECT_EQ(list->get(list, 100), nullptr);
}

TEST_F(CListTest, Copy) {
    int val1 = 5;
    float val2 = 1.5f;

    list->append(list, &val1, int_type);
    list->append(list, &val2, float_type);

    c_list* copy = list->copy(list);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->size, 2);

    int* int_result = (int*)copy->get(copy, 0);
    EXPECT_EQ(*int_result, 5);

    float* float_result = (float*)copy->get(copy, 1);
    EXPECT_FLOAT_EQ(*float_result, 1.5f);

    copy->destroy(copy);
}

TEST_F(CListTest, Clear) {
    int val = 7;
    list->append(list, &val, int_type);
    list->append(list, &val, int_type);

    EXPECT_EQ(list->size, 2);
    list->clear(list);
    EXPECT_EQ(list->size, 0);
}

TEST_F(CListTest, FileOperations) {
    int ival = 100;
    float fval = 3.14f;
    char* sval = (char*)"hello";

    list->append(list, &ival, int_type);
    list->append(list, &fval, float_type);
    list->append(list, sval, string_type);

    EXPECT_EQ(dump_list_to_file(list, "test.txt"), 0);

    c_list* loaded = create_list_from_file("test.txt");
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->size, 3);

    int* loaded_int = (int*)loaded->get(loaded, 0);
    EXPECT_EQ(*loaded_int, 100);

    float* loaded_float = (float*)loaded->get(loaded, 1);
    EXPECT_FLOAT_EQ(*loaded_float, 3.14f);

    char* loaded_str = (char*)loaded->get(loaded, 2);
    EXPECT_STREQ(loaded_str, "hello");

    loaded->destroy(loaded);
}

TEST_F(CListTest, Resize) {
    for (int i = 0; i < 10; i++) {
        list->append(list, &i, int_type);
    }
    EXPECT_EQ(list->size, 10);
    EXPECT_GE(list->capacity, 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}