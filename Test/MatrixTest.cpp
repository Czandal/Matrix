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
		distr = std::uniform_real_distribution<long double>(-10.0l, 10.l);
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
	std::cout << determinantC<<"\n";
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

TEST_F(MatrixTest, MatrixSpecificOperationsTest)
{
	given("3x3 matrix A:");
	Mat A(3, 3);
	A(0, 0) = 5.l;
	A(0, 1) = 1.l;
	A(0, 2) = 3.l;
	A(1, 0) = -4.l;
	A(1, 1) = 1.l;
	A(1, 2) = -2.l;
	A(2, 0) = 0.l;
	A(2, 1) = 7.l;
	A(2, 2) = 0.l;
	A.print();

	then("Determinant is defined and is equal "+ std::to_string(-14.l));
	ASSERT_EQ(A.det(), -14.l);

	then("By transposing matrix A we receive a new matrix equal to:");
	Mat traA(3, 3);
	traA(0, 0) = 5.l;
	traA(0, 1) = -4.l;
	traA(0, 2) = 0.l;
	traA(1, 0) = 1.l;
	traA(1, 1) = 1.l;
	traA(1, 2) = 7.l;
	traA(2, 0) = 3.l;
	traA(2, 1) = -2.l;
	traA(2, 2) = 0.l;
	traA.print();
	ASSERT_TRUE(A.transposed()==traA)<<"Transposition of Matrix A is not equal to A.transposed()!\n";

	then("There exists adjugate of A equal to: ");
	Mat adjA(3, 3);
	adjA(0, 0) = 14.l;
	adjA(0, 1) = 21.l;
	adjA(0, 2) = -5.l;
	adjA(1, 0) = 0.l;
	adjA(1, 1) = 0.l;
	adjA(1, 2) = -2.l;
	adjA(2, 0) = -28.l;
	adjA(2, 1) = -35.l;
	adjA(2, 2) = 9.l;
	adjA.print();
	EXPECT_TRUE(A.adjoint()==adjA) << "Adjoint of Matrix A is not equal to A.adjoint()!\n";

	then("There exists an inverse of A equal to which multiplied by A yields identity matrix: ");
	Mat inv(3,3);
	ASSERT_NO_THROW(inv = A.inverse())<<"Inverse of A is undefined!\n";
	inv.print();
	EXPECT_EQ(identityMultiplicativeSquare(3), inv * A)<<"A.inv()*A doesn't yield multiplicative identity!\n";
	(inv * A).print();
}