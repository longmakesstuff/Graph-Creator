#pragma once

#include <cstdint>
#include <eigen3/Eigen/Dense>
#include <ostream>
#include "Common.hpp"

class Polynomial {
private:
    uint32_t order;
    Eigen::VectorXd coefficients{};

public:
    explicit Polynomial(uint32_t order);

    [[nodiscard]] void fit(const Eigen::VectorXd& x, const Eigen::VectorXd& y);

    [[nodiscard]] Eigen::VectorXd calculate(const Eigen::VectorXd& data) const;

    [[nodiscard]] Eigen::MatrixXd vandermonde(const Eigen::VectorXd& data) const;

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial);
};