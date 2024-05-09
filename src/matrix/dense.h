#pragma once
#include "vector.h"
#include <fstream>
#include <string>

template<typename T>
class Dense {
private:
    std::vector<T> values;
    unsigned long int height;
    unsigned long int width;

public:
    Dense (const std::vector<T>& values, unsigned long int height, unsigned long int width):
        values(values), height(height), width(width) {}
    
    Dense (const std::vector<std::vector<T>>& data){
        height = data.size();
        width = data[0].size();
        for (unsigned long int i = 0; i < height; i++){
            values.insert(values.end(), data[i].begin(), data[i].end());
        }
    }

    const std::vector<T>& get_values() const{
        return values;
    }
    unsigned long int get_height() const{
        return height;
    }
    unsigned long int get_width() const{
        return width;
    }

    T operator()(unsigned long int i, unsigned long int j) const {
        return values[width * i + j];
    }
};

template<typename T, typename Q>
auto operator*(const Dense<T>& dense, const std::vector<Q>& v) {
    std::vector<decltype(std::declval<T>() + std::declval<Q>())> res(dense.get_height());
    for (unsigned long int i = 0; i < dense.get_height(); i++) {
        for (unsigned long int j = 0; j < dense.get_width(); j++){
            res[i] += dense.get_values()[dense.get_width() * i + j] * v[j];
        }
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Dense<T>& dense) {
    const std::vector<T> values = dense.get_values();
    unsigned long int height = dense.get_height();
    unsigned long int width = dense.get_width();
    for (unsigned long int i = 0; i < height; i++){
        for (unsigned long int j = 0; j < width; j++){
            std::cout << values[width * i + j] << ' ';
        }
        std:: cout << std::endl;
    }
    return os;
}