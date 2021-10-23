#include <gtest/gtest.h>
#include "../Matrix.hpp"
#include <random>

struct MatrixTest : public ::testing::Test
{
	virtual void SetUp() override
	{

	}
	virtual void TearDown() override
	{

	}
};
TEST(MatrixTest, DemonstrateGTestMacros)
{
	using namespace LinearAlgebra;

	Matrix<long double>A(2, 3);
	Matrix<long double>B(4, 24);
	EXPECT_ANY_THROW(A * B);
	Matrix<long double>C(3, 24);
	EXPECT_NO_THROW(A * C);
	EXPECT_EQ(A, A) << "B is not equal to B!\n";
	EXPECT_EQ(B,B)<<"B is not equal to B!\n";
	EXPECT_EQ(A, A);
	EXPECT_TRUE(A==A);
	
}