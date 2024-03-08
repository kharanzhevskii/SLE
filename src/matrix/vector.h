#pragma once

#include <vector>
#include <iostream>

template<typename T, typename Q>
std::vector<decltype(std::declval<T>() + std::declval<Q>())> operator+(const std::vector<T>& first, const std::vector<Q>& second){
    std::vector<decltype(std::declval<T>() + std::declval<Q>())> res(first.size());
    for (std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] + second[i];
    }
    return res;
}

template<typename T, typename Q>
std::vector<decltype(std::declval<T>() + std::declval<Q>())> operator-(const std::vector<T>& first, const std::vector<Q>& second){
    std::vector<decltype(std::declval<T>() + std::declval<Q>())> res(first.size());
    for (std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] - second[i];
    }
    return res;
}

template<typename T, typename Q>
std::vector<decltype(std::declval<T>() + std::declval<Q>())> operator*(const std::vector<T>& first, Q second){
	std::vector<decltype(std::declval<T>() + std::declval<Q>())> res(first.size());
	for(std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T, typename Q>
std::vector<decltype(std::declval<T>() + std::declval<Q>())> operator*(T second, const std::vector<Q>& first){
	std::vector<decltype(std::declval<T>() + std::declval<Q>())> res(first.size());
	for(std::size_t i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T, typename Q>
decltype(std::declval<T>() + std::declval<Q>()) operator*(const std::vector<T>& first, const std::vector<Q>& second){
    decltype(std::declval<T>() + std::declval<Q>()) res = 0;
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