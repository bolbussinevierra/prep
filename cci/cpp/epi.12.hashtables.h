#pragma once

namespace epi_12 {
const uint PRIME_MOD = 10007;
const uint HASH_BASE = 101;
//
// 12.1 - rolling hash for strings
// 
template <typename T>
T _modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
template <typename T>
T _modpow2(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    for (uint i = 1; i <= exp; ++i) {
        result *= base;
        result %= modulus;
    }
    return result;
}

uint get_hash(string const& s) {
    uint val = 0;
    for (char c : s) {
        val = (val * HASH_BASE) + c;
        val %= PRIME_MOD;
    }
    return val; 
}
// TODO: Look into rabin-karp algorithm!
uint roll_hash_broken(string const& s, char n) {
    uint add_char = ((get_hash(s) * HASH_BASE) + n) % PRIME_MOD;
    printf("%u == %d\n", add_char, get_hash(s + string(1, n)));
    uint size = s.size() + 1;
    uint rem_char = (s[0] * _modpow(HASH_BASE, size-1, PRIME_MOD));
    return (add_char - rem_char) % PRIME_MOD;
}

}