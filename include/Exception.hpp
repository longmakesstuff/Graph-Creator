#pragma once
#include <utility>
#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string message_;
public:
    explicit Exception(std::string message);

    [[nodiscard]] const char *what() const noexcept override;
};