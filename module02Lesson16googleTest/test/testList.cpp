#include "myList.hpp"

#include <gtest/gtest.h>

/*
    const size_t count              // кол-во элементов тестового списка
    List<typename> list             // тестовый список
    size_t sample                   // тестовое вставляемое значение
    size_t idx                      // тестовая позиция для вставки в середину
*/

TEST(List, empty)
{
    // Arrange
    List<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.getSize(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(List, notEmpty)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }

    // Assert
    ASSERT_EQ(list.getSize(), count);
    ASSERT_FALSE(list.empty());
}

TEST(List, copyConstructor)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list1;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list1.pushBack(i);
    }
    List<size_t> list2 = list1;

    // Assert
    bool comparison = true;
    for (size_t i = 0; i < count; ++i)
    {
        if (list1[i] != list2[i])
        {
            comparison = false;
            break;
        }
    }

    ASSERT_EQ(true, comparison);
}

TEST(List, copyAassignmentOperator)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list1, list2;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list1.pushBack(i);
    }
    list2 = list1;

    // Assert
    bool comparison = true;
    for (size_t i = 0; i < count; ++i)
    {
        if (list1[i] != list2[i])
        {
            comparison = false;
            break;
        }
    }

    ASSERT_EQ(true, comparison);
}

TEST(List, pushFront)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.pushFront(sample);

    // Assert
    ASSERT_EQ(sample, list[0]);
    ASSERT_EQ(list.getSize(), 11);
}

TEST(List, eraseFront)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.pushFront(sample);
    list.erase(0);

    // Assert
    ASSERT_NE(sample, list[0]);
    ASSERT_EQ(list.getSize(), count);
}

TEST(List, pushMiddle)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;
    size_t idx = 6;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.insert(idx, sample);

    // Assert
    ASSERT_EQ(sample, list[idx]);
    ASSERT_EQ(list.getSize(), count + 1);
}

TEST(List, eraseMiddle)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;
    size_t idx = 6;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.insert(idx, sample);
    list.erase(idx);

    // Assert
    ASSERT_NE(sample, list[idx]);
    ASSERT_EQ(list.getSize(), count);
}

TEST(List, pushBack)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.pushBack(sample);

    // Assert
    ASSERT_EQ(sample, list[count]);
    ASSERT_EQ(list.getSize(), count + 1);
}

TEST(List, eraseBack)
{
    // Arrange
    const size_t count = 10;
    List<size_t> list;
    size_t sample = 555;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pushBack(i);
    }
    list.pushBack(sample);
    list.erase(count);

    // Assert
    ASSERT_NE(sample, list[count]);
    ASSERT_EQ(list.getSize(), count);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
