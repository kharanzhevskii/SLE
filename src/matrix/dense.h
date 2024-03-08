#pragma once

#include "vector.h"

template<typename T>
class Dense {
private:
    std::vector<T> values;
    int height;
    int width;

public:
    Dense (const std::vector<T>& values, int height, int width):
        values(values), height(height), width(width) {}
    
    const std::vector<T>& get_values() const{
        return values;
    }
    const int get_height() const{
        return height;
    }
    const int get_width() const{
        return width;
    }

    T operator()(int i, int j) const {
        return values[width * i + j];
    }
};

template<typename T>
std::vector<T> operator*(const Dense<T>& dense, const std::vector<T>& v) {
    std::vector<T> res(dense.get_height());
    for (int i = 0; i < dense.get_height(); i++) {
        for (int j = 0; j < dense.get_width(); j++){
            res[i] += dense.get_values()[dense.get_width() * i + j] * v[j];
        }
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Dense<T>& dense) {
    const std::vector<T> values = dense.get_values();
    int height = dense.get_height();
    int width = dense.get_width();
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << values[width * i + j] << ' ';
        }
        std:: cout << std::endl;
    }
    return os;
}