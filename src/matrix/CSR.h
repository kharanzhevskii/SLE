#pragma once
#include "vector.h"

template<typename T>
class CSR {
private:
    std::vector<T> values;
    std::vector<unsigned long int> cols;
    std::vector<unsigned long int> rows;

public:
    CSR (const std::vector<T>& values, const std::vector<unsigned long int>& cols, const std::vector<unsigned long int>& rows):
        values(values), cols(cols), rows(rows) {}

    const std::vector<T>& get_values() const{
        return values;
    }
    const std::vector<unsigned long int>& get_cols() const{
        return cols;
    }
    const std::vector<unsigned long int>& get_rows() const{
        return rows;
    }

    T operator()(unsigned long int i, unsigned long int j) const {
        for (unsigned long int k = rows[i]; k < rows[i + 1]; k++) {
            if (cols[k] == j) {
                return values[k];
            }
        }
        return 0;
    }
};

template<typename T, typename Q>
auto operator*(const CSR<T>& csr, const std::vector<Q>& v) {
    std::vector<decltype(std::declval<T>() + std::declval<Q>())> res;
    decltype(std::declval<T>() + std::declval<Q>()) storage = 0;
    for (unsigned long int i = 0; i < csr.get_rows().size() - 1; i++) {
        storage = 0;
        for (unsigned long int k = csr.get_rows()[i]; k < csr.get_rows()[i + 1]; k++) {
            storage += csr.get_values()[k] * v[csr.get_cols()[k]];
        }
        res.push_back(storage);
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CSR<T>& csr){
    const std::vector<T> values = csr.get_values();
    const std::vector<unsigned long int> cols = csr.get_cols();
    const std::vector<unsigned long int> rows = csr.get_rows();
    std::cout << "Values: ";
    for (unsigned long int i = 0; i < values.size(); i++){
        std::cout << values[i] << ' ';
    }
    std::cout << std::endl << "Cols: ";
    for (unsigned long int i = 0; i < cols.size(); i++){
        std::cout << cols[i] << ' ';
    }
    std::cout << std::endl << "Rows: ";
    for (unsigned long int i = 0; i < rows.size(); i++){
        std::cout << rows[i] << ' ';
    }
    std::cout << std::endl;
    return os;
}