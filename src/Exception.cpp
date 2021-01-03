#include <Exception.hpp>

const char *Exception::what() const noexcept {
    return message_.c_str();
}

Exception::Exception(std::string message) : message_(std::move(message)) {

}
