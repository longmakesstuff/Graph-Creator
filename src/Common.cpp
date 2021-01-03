#include "Common.hpp"

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &vector) {
    os << "[x = " << vector.x << ", y = " << vector.y << "]";
    return os;
}

sf::Vector2f operator+(const sf::Vector2f &lhs, fpt scalar) {
    sf::Vector2f ret(lhs);
    ret.x += scalar;
    ret.y += scalar;
    return ret;
}

sf::Vector2f operator-(const sf::Vector2f &lhs, fpt scalar) {
    sf::Vector2f ret(lhs);
    ret.x -= scalar;
    ret.y -= scalar;
    return ret;
}

sf::Vector2f operator/(const sf::Vector2f &lhs, fpt scalar) {
    sf::Vector2f ret(lhs);
    ret.x /= scalar;
    ret.y /= scalar;
    return ret;
}

sf::Vector2f operator*(const sf::Vector2f &lhs, fpt scalar) {
    sf::Vector2f ret(lhs);
    ret.x *= scalar;
    ret.y *= scalar;
    return ret;
}
