#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class BigInt {
public:
    BigInt() { // конструктор с default values
        number.resize(1);
        number[0] = 0;
    }
    BigInt(string s) { // конструкторы от строкових типов данных
        int i = 0;
        if (s[0] == '-') {
            number.push_back((s[1] - '0') * (-1));
            i = 2;
        }
        for (i; i < s.size(); i++) {
            auto digit = s[i];
            number.push_back(digit - '0');
        }
        reverse(number.begin(), number.end());
    }
    BigInt(char c) {
        auto digit = c;
        number.push_back(digit - '0');
    }
    BigInt(unsigned char c) {
        auto digit = c;
        number.push_back(digit - '0');
    }
    BigInt(vector<int> number) { // конструктор от вектора
        this->number = number;
    }
    BigInt(short number) { // конструкоторы от целочисленных
        int flag = 0;
        if (number < 0) {
            number *= -1;
            flag++;
        }
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
        if (flag) {
            number *= -1;
            this->number.push_back(number % base);
        }
        else {
            this->number.push_back(number % base);
        }
    }
    BigInt(unsigned short number) {
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
    }
    BigInt(int number) {
        int flag = 0;
        if (number < 0) {
            number *= -1;
            flag++;
        }
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
        if (flag) {
            number *= -1;
            this->number.push_back(number % base);
        }
        else {
            this->number.push_back(number % base);
        }
    }
    BigInt(unsigned int number) {
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
    }
    BigInt(long number) {
        int flag = 0;
        if (number < 0) {
            number *= -1;
            flag++;
        }
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
        if (flag) {
            number *= -1;
            this->number.push_back(number % base);
        }
        else {
            this->number.push_back(number % base);
        }
    }
    BigInt(unsigned long number) {
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
    }
    BigInt(long long number) {
        int flag = 0;
        if (number < 0) {
            number *= -1;
            flag++;
        }
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
        if (flag) {
            number *= -1;
            this->number.push_back(number % base);
        }
        else {
            this->number.push_back(number % base);
        }
    }
    BigInt(unsigned long long number) {
        while (number / base > 0) {
            this->number.push_back(number % base);
            number /= base;
        }
    }
    ~BigInt() { // деструктор
        number.clear();
    }

    // вывод
    void write_reversed() const { // const потому что внутри функции класс не должен меняться
        for (int i = 0; i < number.size(); i++) {
            auto digit = number[i];
            cout << digit;
        }
        cout << endl;
    }
    void write() const { // то же самое
        for (size_t i = number.size(); i > 0; i--) {
            auto digit = number[i - 1];
            cout << digit;
        }
        cout << endl;
    }

    // арифметические унарные операции
    BigInt operator - () const {
        BigInt a = *this;
        a.number.back() = a.number.back() * (-1);
        return a;
    }
    BigInt operator -- () {
        BigInt c(1);
        BigInt a = *this;
        a -= c;
        return a;
    }
    BigInt operator -- (int) {
        BigInt a = *this;
        BigInt c(1);
        a -= c;
        return a;
    }
    BigInt operator + () const {
        BigInt a = *this;
        return a;
    }
    BigInt operator ++ () {
        BigInt a = *this;
        BigInt c(1);
        a += c;
        return a;
    }
    BigInt operator ++ (int) {
        BigInt a = *this;
        BigInt c(1);
        a += c;
        return a;
    }


    // арифметические бинарные операции 
    [[nodiscard]] BigInt operator + (const BigInt& a) const {
        if ((this->number.back() >= 0) && ((a.number.back() >= 0))) {
            vector<int> result;
            int carry = 0;
            for (int i = 0; i < min(a.number.size(), this->number.size()); i++) {
                int cur_sum = carry + a.number[i] + this->number[i];
                result.push_back(cur_sum % 10);
                carry = cur_sum / 10;
            }
            for (size_t i = min(a.number.size(), this->number.size()); i < max(a.number.size(), this->number.size()); i++) {
                if (a.number.size() > this->number.size()) {
                    int cur_sum = carry + a.number[i];
                    result.push_back(cur_sum % 10);
                    carry = cur_sum / 10;
                }
                else {
                    int cur_sum = carry + this->number[i];
                    result.push_back(cur_sum % 10);
                    carry = cur_sum / 10;
                }
            }
            if (carry != 0) {
                result.push_back(carry);
            }
            BigInt c(result);
            return c;
        }
        if ((this->number.back() <= 0) && ((a.number.back() <= 0))) {
            BigInt b = -(*this);
            BigInt d = a;
            d = -d;
            vector<int> result;
            int carry = 0;
            for (int i = 0; i < min(d.number.size(), b.number.size()); i++) {
                int cur_sum = carry + d.number[i] + b.number[i];
                result.push_back(cur_sum % 10);
                carry = cur_sum / 10;
            }
            for (size_t i = min(d.number.size(), b.number.size()); i < max(d.number.size(), b.number.size()); i++) {
                if (d.number.size() > b.number.size()) {
                    int cur_sum = carry + d.number[i];
                    result.push_back(cur_sum % 10);
                    carry = cur_sum / 10;
                }
                else {
                    int cur_sum = carry + b.number[i];
                    result.push_back(cur_sum % 10);
                    carry = cur_sum / 10;
                }
            }
            if (carry != 0) {
                result.push_back(carry);
            }
            BigInt c(result);
            return -c;
        }
        if ((this->number.back() >= 0) && ((a.number.back() <= 0))) {
            BigInt d = a;
            BigInt th = (*this);
            return th - (-d);
        }
        else {
            BigInt d = a;
            BigInt th = *this;
            return d - (-th);
        }
    }
    BigInt operator += (const BigInt& a) {
        //*this = *this + a;
        return *this + a;
    }
    [[nodiscard]] BigInt operator - (const BigInt& a) const {
        BigInt c = *this;
        BigInt b = a;
        if (BigInt() <= c && BigInt() <= b) {
            if (c >= b) {
                vector<int> result;
                int carry = 0;
                for (int i = 0; i < b.number.size(); i++) {
                    int cur_diff = c.number[i] - b.number[i] - carry;
                    if (cur_diff < 0) {
                        cur_diff += 10;
                        carry = 1;
                    }
                    else {
                        carry = 0;
                    }
                    result.push_back(cur_diff);
                }
                for (size_t i = b.number.size(); i < c.number.size(); i++) {
                    if (c.number[i] - carry < 0) {
                        result.push_back(c.number[i] + 10 - carry);
                        carry = 1;
                    }
                    else {
                        result.push_back(c.number[i] - carry);
                        carry = 0;
                    }
                }
                while (!result.back() && result.size() > 1) {
                    result.pop_back();
                }
                BigInt r(result);
                return r;
            }
            else {
                vector<int> result;
                int carry = 0;
                for (int i = 0; i < c.number.size(); i++) {
                    int cur_diff = b.number[i] - c.number[i] - carry;
                    if (cur_diff < 0) {
                        cur_diff += 10;
                        carry = 1;
                    }
                    else {
                        carry = 0;
                    }
                    result.push_back(cur_diff);
                }
                for (size_t i = c.number.size(); i < b.number.size(); i++) {
                    if (b.number[i] - carry < 0) {
                        result.push_back(b.number[i] + 10 - carry);
                        carry = 1;
                    }
                    else {
                        result.push_back(b.number[i] - carry);
                        carry = 0;
                    }
                }
                while (!result.back() && result.size() > 1) {
                    result.pop_back();
                }
                BigInt r(result);
                return -r;
            }
        }
        if (BigInt() >= c && BigInt() >= b) {
            c = -(*this);
            b = -a;
            if (-c >= -b) {
                vector<int> result;
                int carry = 0;
                for (int i = 0; i < c.number.size(); i++) {
                    int cur_diff = b.number[i] - c.number[i] - carry;
                    if (cur_diff < 0) {
                        cur_diff += 10;
                        carry = 1;
                    }
                    else {
                        carry = 0;
                    }
                    result.push_back(cur_diff);
                }
                for (size_t i = c.number.size(); i < b.number.size(); i++) {
                    if (b.number[i] - carry < 0) {
                        result.push_back(b.number[i] + 10 - carry);
                        carry = 1;
                    }
                    else {
                        result.push_back(b.number[i] - carry);
                        carry = 0;
                    }
                }
                while (!result.back() && result.size() > 1) {
                    result.pop_back();
                }
                BigInt r(result);
                return r;
            }
            else {
                vector<int> result;
                int carry = 0;
                for (int i = 0; i < b.number.size(); i++) {
                    int cur_diff = c.number[i] - b.number[i] - carry;
                    if (cur_diff < 0) {
                        cur_diff += 10;
                        carry = 1;
                    }
                    else {
                        carry = 0;
                    }
                    result.push_back(cur_diff);
                }
                for (size_t i = b.number.size(); i < c.number.size(); i++) {
                    if (c.number[i] - carry < 0) {
                        result.push_back(c.number[i] + 10 - carry);
                        carry = 1;
                    }
                    else {
                        result.push_back(c.number[i] - carry);
                        carry = 0;
                    }
                }
                while (!result.back() && result.size() > 1) {
                    result.pop_back();
                }
                BigInt r(result);
                return -r;
            }
        }
        if (BigInt() <= c && BigInt() >= b) {
            b = -a;
            c = *this;
            return c + b;
        }
        else {
            return -(-(c) + b);
        }
    }

    BigInt operator -= (const BigInt& a) {
        *this = *this - a;
        return *this;
    }
    [[nodiscard]] BigInt operator * (const BigInt& a) const {             // например 124 = 4*10^0 + 2*10^1 + 1*10^2, тогда
        int flag = 0;                                                     // (a * b)[i + j] += a[i] * b[j]
        BigInt c = *this;                                                 // Воспользовавшись этой формулой можно решить  
        BigInt b = a;
        if (c < BigInt()) {
            c = -c;
            flag++;
        }
        if (b < BigInt()) {
            b = -b;
            flag++;
        }
        vector<int> result(c.number.size() * b.number.size() + 1, 0);
        for (size_t i = 0; i < c.number.size(); i++) {
            int carry = 0;
            for (size_t j = 0; j < b.number.size(); j++) {
                int cur = result[i + j] + c.number[i] * b.number[j] + carry;
                carry = cur / c.base;
                result[i + j] = cur % c.base;
            }
            size_t cur = b.number.size();
            while (carry) {
                result[i + cur] = carry % c.base;
                cur++;
                carry /= c.base;
            }
        }
        while (!result.back() && result.size() > 1) {
            result.pop_back();
        }
        BigInt r(result);
        if (flag % 2 != 0) {
            r = -r;
        }
        return r;
    }
    BigInt operator *= (const BigInt& a) {
        *this = *this * a;
        return *this;
    }
    [[nodiscard]] BigInt operator / (const BigInt& a) const {
        int flag = 0;
        BigInt c = *this;
        BigInt b = a;
        if (b == BigInt()) {
            cout << "ОШИБКА, ДЕЛИТЬ НА НОЛЬ НЕЛЬЗЯ";
            return 0;
        }
        if (c < b) {
            return BigInt();
        }
        else {
            if (c < BigInt()) {
                c = -c;
                flag++;
            }
            if (b < BigInt()) {
                b = -b;
                flag++;
            }
            vector<int> result(c.number.size() - b.number.size() + 1, 0);
            BigInt r(result);
            for (size_t i = result.size(); i > 0; i--) {
                while (r * b <= c) {
                    r.number[i - 1]++;
                }
                r.number[i - 1]--;
            }
            while (!r.number.back() && r.number.size() > 1) {
                r.number.pop_back();
            }
            if (flag % 2 != 0) {
                r = -r;
            }
            return r;
        }
    }
    BigInt operator /= (const BigInt& a) {
        *this = *this / a;
        return *this;
    }
    [[nodiscard]] BigInt operator % (const BigInt& a) const {
        BigInt c = *this - (*this / a) * a;
        return c;
    }
    BigInt operator %= (const BigInt& a) {
        *this = *this % a;
        return *this;
    }

    // касты
    [[nodiscard]] explicit operator bool() const {
        if (BigInt() != *this) {
            return false;
        }
        else {
            return true;
        }
    }
    [[nodiscard]] explicit operator char unsigned() const {
        return this->number.back();
    }
    [[nodiscard]] explicit operator char() const {
        return this->number.back();
    }
    [[nodiscard]] explicit operator short unsigned() const {
        BigInt a = *this;
        short unsigned r = 0;
        for (size_t i = a.number.size(); i > 0; i--) {
            r += a.number.back() * short unsigned(pow(10, i - 1));
            a.number.pop_back();
        }
        return r;
    }
    [[nodiscard]] explicit operator short() const {
        BigInt a;
        if (BigInt() < *this) {
            BigInt a = *this;
            short r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * short(pow(10, i - 1));
                a.number.pop_back();
            }
            return r;
        }
        else {
            BigInt a = -(*this);
            short r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * short(pow(10, i - 1));
                a.number.pop_back();
            }
            return -r;
        }
    }
    [[nodiscard]] explicit operator int unsigned() const {
        BigInt a = *this;
        int unsigned r = 0;
        for (size_t i = a.number.size(); i > 0; i--) {
            r += a.number.back() * int unsigned(pow(10, i - 1));
            a.number.pop_back();
        }
        return r;
    }
    [[nodiscard]] explicit operator int() const {
        BigInt a;
        if (BigInt() < *this) {
            BigInt a = *this;
            int r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * int(pow(10, i - 1));
                a.number.pop_back();
            }
            return r;
        }
        else {
            BigInt a = -(*this);
            int r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * int(pow(10, i - 1));
                a.number.pop_back();
            }
            return -r;
        }
    }
    [[nodiscard]] explicit operator long unsigned() const {
        BigInt a = *this;
        long unsigned r = 0;
        for (size_t i = a.number.size(); i > 0; i--) {
            r += a.number.back() * long unsigned(pow(10, i - 1));
            a.number.pop_back();
        }
        return r;
    }
    [[nodiscard]] explicit operator long() const {
        BigInt a;
        if (BigInt() < *this) {
            BigInt a = *this;
            long r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * long(pow(10, i - 1));
                a.number.pop_back();
            }
            return r;
        }
        else {
            BigInt a = -(*this);
            long r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * long(pow(10, i - 1));
                a.number.pop_back();
            }
            return -r;
        }
    }
    [[nodiscard]] explicit operator long long unsigned() const {
        BigInt a = *this;
        long long unsigned r = 0;
        for (size_t i = a.number.size(); i > 0; i--) {
            r += a.number.back() * long long unsigned(pow(10, i - 1));
            a.number.pop_back();
        }
        return r;
    }
    [[nodiscard]] explicit operator long long() const {
        BigInt a;
        if (BigInt() < *this) {
            BigInt a = *this;
            long long r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * long long(pow(10, i - 1));
                a.number.pop_back();
            }
            return r;
        }
        else {
            BigInt a = -(*this);
            long long r = 0;
            for (size_t i = a.number.size(); i > 0; i--) {
                r += a.number.back() * long long(pow(10, +i - 1));
                a.number.pop_back();
            }
            return -r;
        }
    }

    // операторы сравнения
    [[nodiscard]] bool operator <= (const BigInt& a) {
        if (this->number.back() >= 0 && a.number.back() >= 0) {
            if (this->number.size() < a.number.size()) {
                return true;
            }
            else if (this->number.size() > a.number.size()) {
                return false;
            }
            else {
                for (size_t i = this->number.size(); i > 0; i--) {
                    if (this->number[i - 1] > a.number[i - 1]) {
                        return false;
                    }
                    if (a.number[i - 1] > this->number[i - 1]) {
                        return true;
                    }
                }
                return true;
            }
        }
        if (this->number.back() <= 0 && a.number.back() <= 0) {
            BigInt b = -a;
            BigInt c = -(*this);
            if (c.number.back() > 0 && b.number.back() > 0) {
                if (c.number.size() < b.number.size()) {
                    return false;
                }
                else if (c.number.size() > b.number.size()) {
                    return true;
                }
                else {
                    for (size_t i = c.number.size(); i > 0; i--) {
                        if (c.number[i - 1] > b.number[i - 1]) {
                            return true;
                        }
                        if (b.number[i - 1] > c.number[i - 1]) {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (this->number.back() >= 0 && a.number.back() <= 0) {
            return false;
        }
        else {
            return true;
        }
    }
    [[nodiscard]] bool operator >= (const BigInt& a) {
        if (this->number.back() >= 0 && a.number.back() >= 0) {
            if (this->number.size() > a.number.size()) {
                return true;
            }
            else if (this->number.size() < a.number.size()) {
                return false;
            }
            else {
                for (size_t i = this->number.size(); i > 0; i--) {
                    if (this->number[i - 1] < a.number[i - 1]) {
                        return false;
                    }
                    if (a.number[i - 1] < this->number[i - 1]) {
                        return true;
                    }
                }
                return true;
            }
        }
        if (this->number.back() <= 0 && a.number.back() <= 0) {
            BigInt b = -a;
            BigInt c = -(*this);
            if (c.number.back() > 0 && b.number.back() > 0) {
                if (c.number.size() > b.number.size()) {
                    return false;
                }
                else if (c.number.size() < b.number.size()) {
                    return true;
                }
                else {
                    for (size_t i = c.number.size(); i > 0; i--) {
                        if (c.number[i - 1] < b.number[i - 1]) {
                            return true;
                        }
                        if (b.number[i - 1] < c.number[i - 1]) {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (this->number.back() >= 0 && a.number.back() <= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    [[nodiscard]] bool operator < (const BigInt& a) {
        if (this->number.back() >= 0 && a.number.back() >= 0) {
            if (this->number.size() < a.number.size()) {
                return true;
            }
            else if (this->number.size() > a.number.size()) {
                return false;
            }
            else {
                for (size_t i = this->number.size(); i > 0; i--) {
                    if (this->number[i - 1] > a.number[i - 1]) {
                        return false;
                    }
                    if (a.number[i - 1] > this->number[i - 1]) {
                        return true;
                    }
                }
                return false;
            }
        }
        else if (this->number.back() <= 0 && a.number.back() <= 0) {
            BigInt b = -a;
            BigInt c = -(*this);
            if (c.number.size() < b.number.size()) {
                return false;
            }
            else if (c.number.size() > b.number.size()) {
                return true;
            }
            else {
                for (size_t i = c.number.size(); i > 0; i--) {
                    if (c.number[i - 1] > b.number[i - 1]) {
                        return true;
                    }
                    if (b.number[i - 1] > c.number[i - 1]) {
                        return false;
                    }
                }
                return false;
            }
        }
        else if (this->number.back() >= 0 && a.number.back() <= 0) {
            return false;
        }
        else {
            return true;
        }
    }
    [[nodiscard]] bool operator > (const BigInt& a) {
        if (this->number.back() >= 0 && a.number.back() >= 0) {
            if (this->number.size() > a.number.size()) {
                return true;
            }
            else if (this->number.size() < a.number.size()) {
                return false;
            }
            else {
                for (size_t i = this->number.size(); i > 0; i--) {
                    if (this->number[i - 1] < a.number[i - 1]) {
                        return false;
                    }
                    if (a.number[i - 1] < this->number[i - 1]) {
                        return true;
                    }
                }
                return false;
            }
        }
        if (this->number.back() <= 0 && a.number.back() <= 0) {
            BigInt b = -a;
            BigInt c = -(*this);
            if (c.number.back() >= 0 && b.number.back() >= 0) {
                if (c.number.size() > b.number.size()) {
                    return false;
                }
                else if (c.number.size() < b.number.size()) {
                    return true;
                }
                else {
                    for (size_t i = c.number.size(); i > 0; i--) {
                        if (c.number[i - 1] < b.number[i - 1]) {
                            return true;
                        }
                        if (b.number[i - 1] < c.number[i - 1]) {
                            return false;
                        }
                    }
                    return false;
                }
            }
        }
        if (this->number.back() >= 0 && a.number.back() <= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    [[nodiscard]] bool operator == (const BigInt& a) {
        if ((*this >= a) && (*this <= a)) {
            return true;
        }
        else {
            return false;
        }
    }
    [[nodiscard]] bool operator != (const BigInt& a) {
        if (*this == a) {
            return false;
        }
        else {
            return true;
        }
    }
private:
    int base = 10;
    vector<int> number;
};