#include <iostream>

#include "robust_iterator.h"
#include "gtest/gtest.h"

using namespace std;

class RobustIteratorTest : public ::testing::Test {
protected:
    RobustIteratorTest* test;
    Group<int>* root;
    Data<int>** array;

    RobustIteratorTest() {
        array = new Data<int>*[10];
        for (int i = 0; i < 10; i++) {
            array[i] = new Data<int>(i);
        }
    }

    virtual ~RobustIteratorTest() {}

    virtual void SetUp() {
        root = new Group<int>();
    }

    virtual void TearDown() {
        root = nullptr;
    }

    void add_n_ints_to_root(int number) {
        for (int i = 0; i < number; i++) {
            root->add(new Data<int>(i));
        }
    }

    string traverse(Iterator<int>* iterator) {
        string str = "";
        while (!iterator->is_done()) {
            Component<int>* item = iterator->next();
            str += item->to_string();

            if (!iterator->is_done())
                str += " ";
        }
        return str;
    }
};

TEST_F(RobustIteratorTest, can_iterate_over_simple_list) {
    add_n_ints_to_root(9);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ("0 1 2 3 4 5 6 7 8", traverse(iterator));
}

TEST_F(RobustIteratorTest, can_iterate_over_nested_list) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(array[2]);
    root->add(group);
    add_n_ints_to_root(1);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ("1 2 0", traverse(iterator));
}

TEST_F(RobustIteratorTest, can_iterate_over_nested_list_of_nested_lists) {
    Group<int>* nested_group = new Group<int>();
    nested_group->add(array[2]);
    nested_group->add(array[3]);

    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(nested_group);
    group->add(array[4]);

    root->add(group);
    root->add(array[5]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ("1 2 3 4 5", traverse(iterator));
}

TEST_F(RobustIteratorTest, can_ignore_addition_to_left_side_of_iter_ptr) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    root->add(group);
    root->add(array[3]);
    root->add(array[4]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    EXPECT_EQ(array[3], iterator->next());
    group->add(array[2]);
    EXPECT_EQ(array[4], iterator->next());
}

TEST_F(RobustIteratorTest, can_add_to_right_side_of_iter_ptr_and_then_iterate) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    root->add(group);
    root->add(array[3]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    group->add(array[2]);
    EXPECT_EQ(array[2], iterator->next());
    EXPECT_EQ(array[3], iterator->next());
}

TEST_F(RobustIteratorTest, can_add_and_remove_more_than_one_items) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    root->add(group);
    root->add(array[3]);
    root->add(array[4]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    EXPECT_EQ(array[3], iterator->next());
    group->add(array[6]);
    root->add(array[7]);
    root->remove(array[4]);
    EXPECT_EQ(array[7], iterator->next());
}

TEST_F(RobustIteratorTest, can_remove_from_head) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(array[2]);
    root->add(group);
    root->add(array[4]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    EXPECT_EQ(array[2], iterator->next());
    group->remove(array[1]);
    EXPECT_EQ(array[4], iterator->next());
}

TEST_F(RobustIteratorTest, can_remove_current_item) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(array[2]);
    root->add(group);
    root->add(array[3]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    EXPECT_EQ(array[2], iterator->next());
    group->remove(group);
    EXPECT_EQ(array[3], iterator->next());
}

TEST_F(RobustIteratorTest, can_remove_from_tail) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(array[2]);
    group->add(array[3]);
    root->add(group);
    root->add(array[4]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    group->remove(array[3]);
    EXPECT_EQ(array[2], iterator->next());
    EXPECT_EQ(array[4], iterator->next());
}

TEST_F(RobustIteratorTest, can_remove_nested_list_and_get_nullptr) {
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(array[2]);
    group->add(array[3]);
    root->add(group);
    root->add(array[4]);

    Iterator<int>* iterator = root->create_iterator();

    root->remove(group);
    root->remove(array[4]);

    EXPECT_EQ(nullptr, iterator->next());
}

TEST_F(RobustIteratorTest, can_remove_nested_current_item) {
    Group<int>* nested_group = new Group<int>();
    nested_group->add(array[2]);
    nested_group->add(array[3]);
    Group<int>* group = new Group<int>();
    group->add(array[1]);
    group->add(nested_group);
    group->add(array[4]);

    root->add(group);
    root->add(array[5]);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ(array[1], iterator->next());
    EXPECT_EQ(array[2], iterator->next());
    root->remove(group);
    EXPECT_EQ(array[5], iterator->next());
}

TEST_F(RobustIteratorTest, can_iterate_over_hard_nested_list) {
    Group<int>* nested_group_1 = new Group<int>();
    nested_group_1->add(array[0]);
    Group<int>* nested_group_2 = new Group<int>();
    nested_group_2->add(array[1]);
    Group<int>* nested_group_3 = new Group<int>();
    nested_group_3->add(array[2]);
    Group<int>* nested_group_4 = new Group<int>();
    nested_group_4->add(array[3]);
    Group<int>* nested_group_5 = new Group<int>();
    nested_group_5->add(array[4]);
    Group<int>* nested_group_6 = new Group<int>();
    nested_group_6->add(array[5]);
    nested_group_5->add(nested_group_6);
    nested_group_5->add(array[6]);
    nested_group_4->add(nested_group_5);
    nested_group_4->add(array[7]);
    nested_group_3->add(nested_group_4);
    nested_group_3->add(array[8]);
    nested_group_2->add(nested_group_3);
    nested_group_2->add(array[9]);
    nested_group_1->add(nested_group_2);

    root->add(nested_group_1);

    Iterator<int>* iterator = root->create_iterator();

    EXPECT_EQ("0 1 2 3 4 5 6 7 8 9", traverse(iterator));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
