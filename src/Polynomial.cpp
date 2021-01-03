#include "Polynomial.hpp"

Polynomial::Polynomial(uint32_t order) : order(order), coefficients(order + 1) {
    coefficients << Eigen::ArrayXd::Ones(order + 1);
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
    os << "Polynomial " << polynomial.order << ". Order" << ", Coefficients: " << polynomial.coefficients;
    return os;
}

Eigen::VectorXd Polynomial::calculate(const Eigen::VectorXd &data) const {
    Eigen::MatrixXd vandermondeMatrix = this->vandermonde(data);
    return vandermondeMatrix * this->coefficients;
}

Eigen::MatrixXd Polynomial::vandermonde(const Eigen::VectorXd &data) const {
    Eigen::MatrixXd vandermondeMatrix(data.rows(), this->order + 1);
    for (int32_t y = 0; y < data.rows(); y++) {
        for (int32_t x = 0; x <= this->order; x++) {
            vandermondeMatrix(y, x) = std::pow(data(y), x);
        }
    }
    return vandermondeMatrix;
}

void Polynomial::fit(const Eigen::VectorXd &x, const Eigen::VectorXd &y) {
    Eigen::MatrixXd X = this->vandermonde(x);
    this->coefficients = (X.transpose() * X).inverse() * X.transpose() * y;
}