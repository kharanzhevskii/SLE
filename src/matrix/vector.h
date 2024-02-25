#pragma once

#include <vector>
#include <iostream>

template<typename T>
std::vector<T> operator+(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] + second[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] - second[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& first, T second){
	std::vector<T> res(first.size());
	for(std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T>
std::vector<T> operator*(T second, const std::vector<T>& first){
	std::vector<T> res(first.size());
	for(std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T>
T operator*(const std::vector<T>& first, const std::vector<T>& second){
    T res = 0;
    for (std::size_t i = 0; i < first.size(); i++){
        res += first[i] * second[i];
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& first){
    for (std::size_t i = 0; i < first.size(); i++){
        std::cout << first[i] << std::endl;
    }
    return os;
}