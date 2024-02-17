#pragma once

#include <vector>
#include <iostream>

template<typename T>
std::vector<T> operator+=(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (int i = 0; i < first.size(); i++){
        res[i] = first[i] + second[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator+(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (int i = 0; i < first.size(); i++){
        res[i] = first[i] + second[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator-=(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (int i = 0; i < first.size(); i++){
        res[i] = first[i] - second[i];
    }
    return res;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> res(first.size());
    for (int i = 0; i < first.size(); i++){
        res[i] = first[i] - second[i];
    }
    return res;
}

template<typename T, typename Q>
std::vector<T> operator*(const std::vector<T>& first, Q second){
	std::vector<T> res(first.size());
	for(int i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T, typename Q>
std::vector<T> operator*(Q second, const std::vector<T>& first){
	std::vector<T> res(first.size());
	for(int i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T, typename Q>
std::vector<T> operator*=(const std::vector<T>& first, Q second){
	std::vector<T> res(first.size());
	for(int i = 0; i < first.size(); i++){
        res[i] = first[i] * second;
    }
	return res;
}

template<typename T>
T operator*(const std::vector<T>& first, const std::vector<T>& second){
    T res = 0;
    for (int i = 0; i < first.size(); i++){
        res += first[i] * second[i];
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& first){
    for (int i = 0; i < first.size(); i++){
        std::cout << first[i] << std::endl;
    }
    return os;
}