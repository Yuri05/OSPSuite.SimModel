#include <gtest/gtest.h>
#include "SimModel/TObjectVector.h"
#include "SimModel/ConstantFormula.h"

using namespace SimModelNative;

// Simple test class for TObjectVector
class TestObject {
public:
    int value;
    TestObject(int v) : value(v) {}
    virtual ~TestObject() {}
};

// Test suite for TObjectVector
class TObjectVectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for each test
    }
    
    void TearDown() override {
        // Cleanup after each test
    }
};

TEST_F(TObjectVectorTest, DefaultConstructor) {
    TObjectVector<TestObject> vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST_F(TObjectVectorTest, PushBackSingleElement) {
    TObjectVector<TestObject> vec;
    TestObject* obj = new TestObject(42);
    vec.push_back(obj);
    
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0]->value, 42);
}

TEST_F(TObjectVectorTest, PushBackMultipleElements) {
    TObjectVector<TestObject> vec;
    
    for (int i = 0; i < 10; i++) {
        vec.push_back(new TestObject(i));
    }
    
    EXPECT_EQ(vec.size(), 10);
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(vec[i]->value, i);
    }
    
    vec.clear();
}

TEST_F(TObjectVectorTest, Clear) {
    TObjectVector<TestObject> vec;
    
    vec.push_back(new TestObject(1));
    vec.push_back(new TestObject(2));
    vec.push_back(new TestObject(3));
    
    EXPECT_EQ(vec.size(), 3);
    
    vec.clear();
    
    EXPECT_EQ(vec.size(), 0);
}

TEST_F(TObjectVectorTest, ClearEmptyVector) {
    TObjectVector<TestObject> vec;
    EXPECT_EQ(vec.size(), 0);
    
    // Clearing an empty vector should be safe
    EXPECT_NO_THROW(vec.clear());
    EXPECT_EQ(vec.size(), 0);
}

TEST_F(TObjectVectorTest, GetVector) {
    TObjectVector<TestObject> vec;
    
    vec.push_back(new TestObject(10));
    vec.push_back(new TestObject(20));
    
    TestObject** array = vec.GetVector();
    
    EXPECT_NE(array, nullptr);
    EXPECT_EQ(array[0]->value, 10);
    EXPECT_EQ(array[1]->value, 20);
    
    vec.clear();
}

TEST_F(TObjectVectorTest, FreeVector) {
    TObjectVector<TestObject> vec;
    
    // Create objects that we'll manage manually
    TestObject* obj1 = new TestObject(100);
    TestObject* obj2 = new TestObject(200);
    
    vec.push_back(obj1);
    vec.push_back(obj2);
    
    EXPECT_EQ(vec.size(), 2);
    
    // FreeVector only clears the vector, not the objects
    vec.FreeVector();
    
    EXPECT_EQ(vec.size(), 0);
    
    // Manually delete the objects we created
    delete obj1;
    delete obj2;
}

TEST_F(TObjectVectorTest, WithConstantFormula) {
    TObjectVector<ConstantFormula> vec;
    
    vec.push_back(new ConstantFormula(1.5));
    vec.push_back(new ConstantFormula(2.5));
    vec.push_back(new ConstantFormula(3.5));
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0]->DE_Compute(nullptr, 0.0, Formula::ignore), 1.5);
    EXPECT_EQ(vec[1]->DE_Compute(nullptr, 0.0, Formula::ignore), 2.5);
    EXPECT_EQ(vec[2]->DE_Compute(nullptr, 0.0, Formula::ignore), 3.5);
    
    vec.clear();
}

TEST_F(TObjectVectorTest, IndexOperator) {
    TObjectVector<TestObject> vec;
    
    for (int i = 0; i < 5; i++) {
        vec.push_back(new TestObject(i * 10));
    }
    
    // Test const operator[]
    const TObjectVector<TestObject>& constVec = vec;
    
    EXPECT_EQ(constVec[0]->value, 0);
    EXPECT_EQ(constVec[1]->value, 10);
    EXPECT_EQ(constVec[2]->value, 20);
    EXPECT_EQ(constVec[3]->value, 30);
    EXPECT_EQ(constVec[4]->value, 40);
    
    vec.clear();
}

TEST_F(TObjectVectorTest, SizeAfterOperations) {
    TObjectVector<TestObject> vec;
    
    EXPECT_EQ(vec.size(), 0);
    
    vec.push_back(new TestObject(1));
    EXPECT_EQ(vec.size(), 1);
    
    vec.push_back(new TestObject(2));
    EXPECT_EQ(vec.size(), 2);
    
    vec.push_back(new TestObject(3));
    EXPECT_EQ(vec.size(), 3);
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}
