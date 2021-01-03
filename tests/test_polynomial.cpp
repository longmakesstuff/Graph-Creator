#include <Polynomial.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


class TestPolynomial : public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestPolynomial);
        CPPUNIT_TEST(testVandermonde);
        CPPUNIT_TEST(testCalculate);
        CPPUNIT_TEST(testFitWorking);
        CPPUNIT_TEST(testLinearRegression);
        CPPUNIT_TEST(testQuadraticRegression);
        CPPUNIT_TEST(testCubicRegression);
    CPPUNIT_TEST_SUITE_END();


public:
    void setUp() override {

    }

    void tearDown() override {

    }

    static void testVandermonde() {
        Polynomial polynomial(7);
        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }
        Eigen::MatrixXd vandermonde = polynomial.vandermonde(xData);
        CPPUNIT_ASSERT_EQUAL(xData.rows(), vandermonde.rows());
        CPPUNIT_ASSERT_EQUAL(8L, vandermonde.cols());
    }

    static void testCalculate() {
        Polynomial polynomial(7);
        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }
        Eigen::VectorXd ret = polynomial.calculate(xData);
        CPPUNIT_ASSERT_EQUAL(ret.rows(), xData.rows());
    }

    static void testFitWorking() {
        Polynomial polynomial(7);
        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }
        Eigen::VectorXd yData(5);
        for (int32_t x = 0; x < yData.rows(); x++) {
            yData(x) = x + 1;
        }
        polynomial.fit(xData, yData);
    }

    static void testLinearRegression() {
        Polynomial polynomial(2);

        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }

        Eigen::VectorXd yData(5);
        for (int32_t x = 0; x < yData.rows(); x++) {
            yData(x) = x + 1;
        }

        polynomial.fit(xData, yData);

        Eigen::VectorXd result = polynomial.calculate(xData);
        for (int32_t x = 0; x < yData.rows(); x++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(yData(x), result(x), 1.0);
        }
    }

    static void testQuadraticRegression() {
        Polynomial polynomial(3);

        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }

        Eigen::VectorXd yData(5);
        for (int32_t x = 0; x < yData.rows(); x++) {
            yData(x) = std::pow(x + 1, 2);
        }

        polynomial.fit(xData, yData);

        Eigen::VectorXd result = polynomial.calculate(xData);
        for (int32_t x = 0; x < yData.rows(); x++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(yData(x), result(x), 1.0);
        }
    }

    static void testCubicRegression() {
        Polynomial polynomial(3);

        Eigen::VectorXd xData(5);
        for (int32_t x = 0; x < xData.rows(); x++) {
            xData(x) = x + 1;
        }

        Eigen::VectorXd yData(5);
        for (int32_t x = 0; x < yData.rows(); x++) {
            yData(x) = std::pow(x + 1, 3);
        }

        polynomial.fit(xData, yData);

        Eigen::VectorXd result = polynomial.calculate(xData);
        for (int32_t x = 0; x < yData.rows(); x++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(yData(x), result(x), 1.0);
        }
    }
};

int main() {
    CPPUNIT_TEST_SUITE_REGISTRATION(TestPolynomial);
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool success = runner.run();
    return !success;
}
