#include "myVector.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(Vector, Empty)
{
    // Arrange
    Vector<int> vector;

    // Act (empty for this test)

    // Assert
    ASSERT_TRUE(vector.empty());
}

TEST(Vector, notEmpty)
{
    // Arrange
    Vector<int> vector;

    // Act (empty for this test)
    vector.pushBack(10);

    // Assert
    ASSERT_FALSE(vector.empty());
}

struct VectorFixture : public testing::Test
{
    const size_t elementCount = 10; // кол-во элементов тестового вектора
    Vector<size_t> vector;          // тестовый вектор
    size_t sample = 555;            // тестовое вставляемое значение
    size_t idx = 6;                 // тестовая позиция для вставки в середину

    // Per-test-suite set-up.
    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    // Per-test-suite tear-down.
    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    // Per-test set-up
    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;

        // Create vector with elementCount elements
        for (size_t i = 0; i < elementCount; ++i)
            vector.pushBack(i);
    }

    // You can define per-test tear-down logic as usual.
    void TearDown() override
    {
        std::cout << "TearDown" << std::endl;

        // Nothing to do for now
    }
};

TEST_F(VectorFixture, pushFront)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    std::cout << "Test body" << std::endl;
    vector.insert(0, sample);

    // Assert
    ASSERT_EQ(sample, vector[0]);
    ASSERT_EQ(vector.getSize(), elementCount + 1);
}

TEST_F(VectorFixture, eraseFront)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    std::cout << "Test body" << std::endl;
    vector.insert(0, sample);
    vector.erase(0);

    // Assert
    ASSERT_NE(sample, vector[0]);
    ASSERT_EQ(vector.getSize(), elementCount);
}

TEST_F(VectorFixture, pushMiddle)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    std::cout << "Test body" << std::endl;
    vector.insert(idx, sample);

    // Assert
    ASSERT_EQ(sample, vector[idx]);
    ASSERT_EQ(vector.getSize(), elementCount + 1);
}

TEST_F(VectorFixture, eraseMiddle)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    vector.insert(idx, sample);
    vector.erase(idx);

    // Assert
    ASSERT_NE(sample, vector[idx]);
    ASSERT_EQ(vector.getSize(), elementCount);
}

TEST_F(VectorFixture, pushBack)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    std::cout << "Test body" << std::endl;
    vector.pushBack(sample);

    // Assert
    EXPECT_EQ(sample, vector[elementCount]);
    EXPECT_EQ(vector.getSize(), elementCount + 1);
}

TEST_F(VectorFixture, eraseBack)
{
    // Arrange
    // nothing to do here, because we have fixture

    // Act
    std::cout << "Test body" << std::endl;
    vector.pushBack(sample);
    vector.erase(elementCount);
    
    // Assert
    EXPECT_NE(sample, vector[elementCount - 1]);
    EXPECT_EQ(vector.getSize(), elementCount);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(Vector, copyConstructor)
{
    // Arrange
    const size_t count = 10;
    Vector<size_t> vector1;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        vector1.pushBack(i);
    }
    Vector<size_t> vector2 = vector1;

    // Assert
    bool comparison = true;
    for (size_t i = 0; i < count; ++i)
    {
        if (vector1[i] != vector2[i])
        {
            comparison = false;
            break;
        }
    }

    ASSERT_EQ(true, comparison);
}

TEST(Vector, copyAassignmentOperator)
{
    // Arrange
    const size_t count = 10;
    Vector<size_t> vector1, vector2;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        vector1.pushBack(i);
    }
    vector2 = vector1;

    // Assert
    bool comparison = true;
    for (size_t i = 0; i < count; ++i)
    {
        if (vector1[i] != vector2[i])
        {
            comparison = false;
            break;
        }
    }

    ASSERT_EQ(true, comparison);
}