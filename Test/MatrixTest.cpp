#include <gtest/gtest.h>
#include "../Matrix.hpp"
#include <random>

struct MatrixTest : public ::testing::Test
{
	typedef LinearAlgebra::Matrix<long double> Mat;
	std::default_random_engine engine;
	std::uniform_real_distribution<long double> distr;
	virtual void SetUp() override
	{
		std::random_device rd;
		engine.seed(rd());
		distr = std::uniform_real_distribution<long double>(0.0l, 1.l);
	}
	virtual void TearDown() override
	{

	}
	long double roll() { return distr(engine); }
	Mat randomMatrix(const size_t& m, const size_t& n)
	{
		Mat ret(m, n);
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				ret(i, j) = roll();
			}
		}
		return ret;
	}
	Mat identityMultiplicativeSquare(const size_t& m)
	{
		Mat id(m, m);
		for (size_t i = 0; i < m; i++)
		{
			id(i, i) = (1.l);
		}
		return id;
	}
	void given(const std::string &msg, std::ostream& str = std::cout)
	{
		str <<"Given: " << msg << "\n";
	}
	void then(const std::string& msg, std::ostream& str = std::cout)
	{
		str << "Then: " << msg << "\n";
	}
	void when(const std::string& msg, std::ostream& str = std::cout)
	{
		str << "When: " << msg << "\n";
	}

	
};
TEST_F(MatrixTest, MatrixMultiplicationTest)
{
	using namespace LinearAlgebra;
	typedef LinearAlgebra::Matrix<long double> Mat;

	given("2x3 matrix of random real numbers called A:");
	Mat A=randomMatrix(2,3);
	A.print();

	given("3x2 matrix of random real numbers called B:");
	Mat B=randomMatrix(3,2);
	B.print();

	then("A*B should not fail");
	ASSERT_NO_THROW(A * B);

	then("Define C as B*A:");
	Mat C;
	ASSERT_NO_THROW(C = B*A)<<"Error: multiplication failed!\n";
	C.print();
	EXPECT_FALSE(LinearAlgebra::isnan(C)) << "Error: Records of C contain nan!\n";

	then("C is 3x3");
	EXPECT_TRUE(C.getCountColumns() == C.getCountRows() && C.getCountColumns() == 3)<<"Error: C is not a 3x3 matrix!\n";

	then("There exists multiplicative identity of C:");
	Mat id = identityMultiplicativeSquare(3);
	id.print();
	EXPECT_TRUE(C * id==C&&id*C==C)<<"Error: C multiplied by multiplicative identity doesn't yield C!\n";

	then("Determinant of C exists and is equal to: ");

	long double determinantC;
	ASSERT_NO_THROW(determinantC = C.det()) << "Error: Determinant is not defined\n";
	
	if (determinantC != 0.l)
	{
		when("Determinant of C is not equal to 0");

		then("There exists multiplicative inverse D such that C*D=identity:");
		Mat D;
		ASSERT_NO_THROW(D=C.adjoint().transposed()/determinantC)<<"Error: C is not invertible!\n";
		ASSERT_TRUE(C * D == id)<<"Error: C*D is not equal to identity matrix!\n";
		D.print();
	}
}
TEST_F(MatrixTest, MatrixAdditionTest)
{
	using namespace LinearAlgebra;
	typedef LinearAlgebra::Matrix<long double> Mat;

	given("2x3 matrix of random real numbers called A:");
	Mat A=randomMatrix(2,3);
	A.print();

	given("3x2 matrix of random real numbers called B:");
	Mat B=randomMatrix(2,3);
	B.print();

	then("Define C as B+A:");
	Mat C;
	ASSERT_NO_THROW(C = B+A)<<"Error: addition failed!\n";
	C.print();
	EXPECT_FALSE(LinearAlgebra::isnan(C)) << "Error: Records of C contain nan!\n";

	then("Define D as A+B:");
	Mat D;
	ASSERT_NO_THROW(D=A+B);

	then("C is equal to D");
	EXPECT_TRUE(C == D)<<"Error: C is not equal to D\n";

	then("There exists additive identity of C:");
	Mat id(2, 3);
	EXPECT_TRUE(C + id==C&&id+C==C)<<"Error: C plus identity is not equal to C!\n";
	id.print();
}
