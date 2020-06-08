#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <iostream>
#include <gmpxx.h>

class BigInt {
  private:
    mpz_class v;

  public:
    BigInt() : v(mpz_class(0)) {}

    template<class T>
    BigInt(const T& n) : v(mpz_class(n)) {}

    template<class T>
    BigInt(const T& n, int base) : v(mpz_class(n, base)) {}

    BigInt& operator=(BigInt rhs);

    bool operator==(const BigInt& rhs) const;

    bool operator!=(const BigInt& rhs) const;

    bool operator<(const BigInt& rhs) const;

    bool operator>(const BigInt& rhs) const;

    bool operator<=(const BigInt& rhs) const;

    bool operator>=(const BigInt& rhs) const;

    BigInt& operator++();

    BigInt operator++(int);

    BigInt operator+() const;

    BigInt operator-() const;

    BigInt operator!() const;

    BigInt& operator+=(const BigInt& rhs);

    BigInt operator+(const BigInt& rhs) const;

    BigInt& operator-=(const BigInt& rhs);

    BigInt operator-(const BigInt& rhs) const;

    BigInt& operator*=(const BigInt& rhs);

    BigInt operator*(const BigInt& rhs) const;

    BigInt& operator/=(const BigInt& rhs);

    BigInt operator/(const BigInt& rhs) const;

    BigInt& operator%=(const BigInt& rhs);

    BigInt operator%(const BigInt& rhs) const;

    BigInt& operator&=(const BigInt& rhs);

    BigInt operator&(const BigInt& rhs) const;

    BigInt& operator|=(const BigInt& rhs);

    BigInt operator|(const BigInt& rhs) const;

    BigInt& operator^=(const BigInt& rhs);

    BigInt operator^(const BigInt& rhs) const;

    BigInt& operator<<=(const BigInt& rhs);

    BigInt operator<<(const BigInt& rhs) const;

    BigInt& operator>>=(const BigInt& rhs);

    BigInt operator>>(const BigInt& rhs) const;

    BigInt pow(const BigInt& p) const;

    BigInt powm(const BigInt& p, const BigInt& m) const;

    BigInt invm(const BigInt& m) const;

    BigInt sqrtm(const BigInt& p) const;

    void setbit(const BigInt& i);

    void clrbit(const BigInt& i);

    int getbit(const BigInt& i) const;

    size_t bitwidth() const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& n);

    friend std::istream& operator>>(std::istream& is, BigInt& n);
};

template<class T>
inline bool operator==(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) == rhs;
}

template<class T>
inline bool operator!=(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) != rhs;
}

template<class T>
inline BigInt operator+(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) += rhs;
}

template<class T>
inline BigInt operator-(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) -= rhs;
}

template<class T>
inline BigInt operator*(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) *= rhs;
}

template<class T>
inline BigInt operator/(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) /= rhs;
}

template<class T>
inline BigInt operator%(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) %= rhs;
}

template<class T>
inline BigInt operator&(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) &= rhs;
}

template<class T>
inline BigInt operator|(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) |= rhs;
}

template<class T>
inline BigInt operator^(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) ^= rhs;
}

template<class T>
inline BigInt operator<<(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) <<= rhs;
}

template<class T>
inline BigInt operator>>(T& lhs, const BigInt& rhs) {
  return BigInt(lhs) >>= rhs;
}

#endif
