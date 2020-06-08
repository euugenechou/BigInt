#include "bigint.h"
#include <algorithm>
#include <utility>

BigInt& BigInt::operator=(BigInt rhs) {
  std::swap(v, rhs.v);
  return *this;
}

bool BigInt::operator==(const BigInt& rhs) const {
  return mpz_cmp(v.get_mpz_t(), rhs.v.get_mpz_t()) == 0;
}

bool BigInt::operator!=(const BigInt& rhs) const {
  return !operator==(rhs);
}

bool BigInt::operator<(const BigInt& rhs) const {
  return mpz_cmp(v.get_mpz_t(), rhs.v.get_mpz_t()) < 0;
}

bool BigInt::operator>(const BigInt& rhs) const {
  return rhs.operator<(*this);
}

bool BigInt::operator<=(const BigInt& rhs) const {
  return !operator>(rhs);
}

bool BigInt::operator>=(const BigInt& rhs) const {
  return !operator<(rhs);
}

BigInt& BigInt::operator++() {
  mpz_add_ui(v.get_mpz_t(), v.get_mpz_t(), 1);
  return *this;
}

BigInt BigInt::operator++(int) {
  BigInt temp(*this);
  operator++();
  return temp;
}

BigInt BigInt::operator+() const {
  BigInt temp;
  mpz_abs(temp.v.get_mpz_t(), v.get_mpz_t());
  return temp;
}

BigInt BigInt::operator-() const {
  BigInt temp;
  mpz_neg(temp.v.get_mpz_t(), v.get_mpz_t());
  return temp;
}

BigInt BigInt::operator!() const {
  BigInt temp;
  mpz_com(temp.v.get_mpz_t(), v.get_mpz_t());
  return temp;
}

BigInt& BigInt::operator+=(const BigInt& rhs) {
  mpz_add(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator+(const BigInt& rhs) const {
  return BigInt(*this) += rhs;
}

BigInt& BigInt::operator-=(const BigInt& rhs) {
  mpz_sub(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator-(const BigInt& rhs) const {
  return BigInt(*this) -= rhs;
}

BigInt& BigInt::operator*=(const BigInt& rhs) {
  mpz_mul(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator*(const BigInt& rhs) const {
  return BigInt(*this) *= rhs;
}

BigInt& BigInt::operator/=(const BigInt& rhs) {
  mpz_fdiv_q(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator/(const BigInt& rhs) const {
  return BigInt(*this) /= rhs;
}

BigInt& BigInt::operator%=(const BigInt& rhs) {
  mpz_mod(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator%(const BigInt& rhs) const {
  return BigInt(*this) %= rhs;
}

BigInt& BigInt::operator&=(const BigInt& rhs) {
  mpz_and(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator&(const BigInt& rhs) const {
  return BigInt(*this) &= rhs;
}

BigInt& BigInt::operator|=(const BigInt& rhs) {
  mpz_ior(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator|(const BigInt& rhs) const {
  return BigInt(*this) |= rhs;
}

BigInt& BigInt::operator^=(const BigInt& rhs) {
  mpz_xor(v.get_mpz_t(), v.get_mpz_t(), rhs.v.get_mpz_t());
  return *this;
}

BigInt BigInt::operator^(const BigInt& rhs) const {
  return BigInt(*this) ^= rhs;
}

BigInt& BigInt::operator<<=(const BigInt& rhs) {
  mpz_mul_2exp(v.get_mpz_t(), v.get_mpz_t(), mpz_get_ui(rhs.v.get_mpz_t()));
  return *this;
}

BigInt BigInt::operator<<(const BigInt& rhs) const {
  return BigInt(*this) <<= rhs;
}

BigInt& BigInt::operator>>=(const BigInt& rhs) {
  mpz_fdiv_q_2exp(v.get_mpz_t(), v.get_mpz_t(), mpz_get_ui(rhs.v.get_mpz_t()));
  return *this;
}

BigInt BigInt::operator>>(const BigInt& rhs) const {
  return BigInt(*this) >>= rhs;
}

BigInt BigInt::pow(const BigInt& p) const {
  BigInt temp;
  mpz_pow_ui(temp.v.get_mpz_t(), v.get_mpz_t(), mpz_get_ui(p.v.get_mpz_t()));
  return temp;
}

BigInt BigInt::powm(const BigInt& p, const BigInt& m) const {
  BigInt temp;
  mpz_powm(
    temp.v.get_mpz_t(), v.get_mpz_t(), p.v.get_mpz_t(), m.v.get_mpz_t()
  );
  return temp;
}

BigInt BigInt::invm(const BigInt& m) const {
  BigInt temp;
  mpz_invert(temp.v.get_mpz_t(), v.get_mpz_t(), m.v.get_mpz_t());
  return temp;
}

BigInt BigInt::sqrtm(const BigInt& p) const {
  BigInt q = p - 1;
  BigInt ss = 0;
  BigInt z = 2;
  BigInt c, r, t, m;

  if (powm((p - 1) / 2, p) != 1) {
    return 0;
  }

  while ((q & 1) == 0) {
    ss += 1;
    q >>= 1;
  }

  if (ss == 1) {
    return powm((p + 1) / 4, p);
  }

  while (z.powm((p - 1) / 2, p) != p - 1) {
    z += 1;
  }

  c = z.powm(q, p);
  r = powm((q + 1) / 2, p);
  t = powm(q, p);
  m = ss;

  for (;;) {
    BigInt e = 0;
    BigInt i = 0;
    BigInt b = c;
    BigInt zz = t;

    if (t == 1) {
      return r;
    }

    while (zz != 1 && i < (m - 1)) {
      zz = (zz * zz) % p;
      i += 1;
    }

    e = m - i - 1;

    while (e > 0) {
      b = (b * b) % p;
      e -= 1;
    }

    r = (r * b) % p;
    c = (b * b) % p;
    t = (t * c) % p;
    m = i;
  }

  return BigInt(-1);
}

void BigInt::setbit(const BigInt& i) {
  mpz_setbit(v.get_mpz_t(), mpz_get_ui(i.v.get_mpz_t()));
  return;
}

void BigInt::clrbit(const BigInt& i) {
  mpz_clrbit(v.get_mpz_t(), mpz_get_ui(i.v.get_mpz_t()));
  return;
}

int BigInt::getbit(const BigInt& i) const {
  return mpz_tstbit(v.get_mpz_t(), mpz_get_ui(i.v.get_mpz_t()));
}

size_t BigInt::bitwidth() const {
  return mpz_sizeinbase(v.get_mpz_t(), 2);
}

std::vector<uint8_t> bigint_to_bytes(const BigInt& n) {
  size_t nbytes = (mpz_sizeinbase(n.v.get_mpz_t(), 2) + 7) / 8;
  std::vector<uint8_t> v(nbytes);
  mpz_export(v.data(), &nbytes, 1, 1, 0, 0, n.v.get_mpz_t());
  v.resize(nbytes);
  return v;
}

BigInt bigint_from_bytes(const std::vector<uint8_t>& v) {
  BigInt temp;
  mpz_import(temp.v.get_mpz_t(), v.size(), 1, 1, 0, 0, v.data());
  return temp;
}

std::string bigint_to_string(const BigInt& n) {
  char *s_ = new char[mpz_sizeinbase(n.v.get_mpz_t(), 16) / 2 + 2]();
  mpz_export(s_, NULL, 1, sizeof(char), 0, 0, n.v.get_mpz_t());
  std::string s = std::string(s_);
  delete[] s_;
  return s;
}

BigInt bigint_from_string(const std::string& s) {
  BigInt temp;
  mpz_import(temp.v.get_mpz_t(), s.size(), 1, sizeof(char), 0, 0, s.data());
  return temp;
}

std::ostream& operator<<(std::ostream& os, const BigInt& n) {
  os << n.v;
  return os;
}

std::istream& operator>>(std::istream& is, BigInt& n) {
  is >> n.v;
  return is;
}
