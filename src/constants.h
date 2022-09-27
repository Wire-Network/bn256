#pragma once
#include <gfp.h>
#include <gfp2.h>
#include <gfp6.h>
#include <boost/multiprecision/cpp_int.hpp>

namespace bn256::constants {

   using namespace boost::multiprecision::literals;
   using namespace boost::multiprecision;

   // u is the BN parameter.
   inline constexpr int512_t u = 0x44E992B44A6909F1_cppi512;

   // Order is the number of elements in both G₁ and G₂: 36u⁴+36u³+18u²+6u+1.
   // Needs to be highly 2-adic for efficient SNARK key and proof generation.
   // Order - 1 = 2^28 * 3^2 * 13 * 29 * 983 * 11003 * 237073 * 405928799 * 1670836401704629 * 13818364434197438864469338081.
   // Refer to https://eprint.iacr.org/2013/879.pdf and https://eprint.iacr.org/2013/507.pdf for more information on these parameters.
   // order is 21888242871839275222246405745257275088548364400416034343698204186575808495617 dec 254 bits
   inline constexpr int512_t order = 0x30644E72E131A029B85045B68181585D2833E84879B9709143E1F593F0000001_cppi512;

   // p is a prime over which we form a basic field: 36u⁴+36u³+24u²+6u+1.
   // p is 21888242871839275222246405745257275088696311157297823662689037894645226208583 dec 254 bits
   inline constexpr int512_t p = 0x30644E72E131A029B85045B68181585D97816A916871CA8D3C208C16D87CFD47_cppi512;

   // p2 is p, represented as little-endian 64-bit words.
   inline constexpr gfp p2 = {
      0x3c208c16d87cfd47,
      0x97816a916871ca8d,
      0xb85045b68181585d,
      0x30644e72e131a029
   };

   // np is the negative inverse of p, mod 2^256.
   inline constexpr uint64_array_4_t np = {
      0x87d20782e4866389,
      0x9ede7d651eca6ac9,
      0xd8afcbd01833da80,
      0xf57a22b791888c6b
   };

   // rn1 is R^-1 where R = 2^256 mod p.
   inline constexpr gfp rn1 = {0xed84884a014afa37, 0xeb2022850278edf8, 0xcf63e9cfb74492d9, 0x2e67157159e5c639};

   // r2 is R^2 where R = 2^256 mod p.
   inline constexpr gfp r2 = {0xf32cfc5b538afa89, 0xb5e71911d44501fb, 0x47ab1eff0a417ff6, 0x06d89f71cab8351f};

   // r3 is R^3 where R = 2^256 mod p.
   inline constexpr gfp r3 = {0xb1cd6dafda1530df, 0x62f210e6a7283db6, 0xef7f0b0c0ada0afb, 0x20fd6e902d592544};

   // xi_to_p_minus_1_over_6 is ξ^((p-1)/6) where ξ = i+9.
   inline constexpr gfp2 xi_to_p_minus_1_over_6 = {
      {0xa222ae234c492d72, 0xd00f02a4565de15b, 0xdc2ff3a253dfc926, 0x10a75716b3899551},
      {0xaf9ba69633144907, 0xca6b1d7387afb78a, 0x11bded5ef08a2087, 0x02f34d751a1f3a7c}
   };

   // xi_to_p_minus_1_over_3 is ξ^((p-1)/3) where ξ = i+9.
   inline constexpr gfp2 xi_to_p_minus_1_over_3 = {
      {0x6e849f1ea0aa4757, 0xaa1c7b6d89f89141, 0xb6e713cdfae0ca3a, 0x26694fbb4e82ebc3},
      {0xb5773b104563ab30, 0x347f91c8a9aa6454, 0x7a007127242e0991, 0x1956bcd8118214ec}
   };

   // xi_to_p_minus_1_over_2 is ξ^((p-1)/2) where ξ = i+9.
   inline constexpr gfp2 xi_to_p_minus_1_over_2 = {
      {0xa1d77ce45ffe77c7, 0x07affd117826d1db, 0x6d16bd27bb7edc6b, 0x2c87200285defecc},
      {0xe4bbdd0c2936b629, 0xbb30f162e133bacb, 0x31a9d1b6f9645366, 0x253570bea500f8dd}
   };

   // xi_to_p_squared_minus_1_over_3 is ξ^((p²-1)/3) where ξ = i+9.
   inline constexpr gfp xi_to_p_squared_minus_1_over_3 = {
      0x3350c88e13e80b9c,
      0x7dce557cdb5e56b9,
      0x6001b4b8b615564a,
      0x2682e617020217e0
   };

   // xi_to_2p_squared_minus_2_over_3 is ξ^((2p²-2)/3) where ξ = i+9 (a cubic root of unity, mod p).
   inline constexpr gfp xi_to_2p_squared_minus_2_over_3 = {
      0x71930c11d782e155,
      0xa6bb947cffbe3323,
      0xaa303344d4741444,
      0x2c3b3f0d26594943
   };

   // xi_to_p_squared_minus_1_over_6 is ξ^((1p²-1)/6) where ξ = i+9 (a cubic root of -1, mod p).
   inline constexpr gfp xi_to_p_squared_minus_1_over_6 = {
      0xca8d800500fa1bf2,
      0xf0c5d61468b39769,
      0x0e201271ad0d4418,
      0x04290f65bad856e6
   };

   // xi_to_2p_minus_2_over_3 is ξ^((2p-2)/3) where ξ = i+9.
   inline constexpr gfp2 xi_to_2p_minus_2_over_3 = {
      {0x5dddfd154bd8c949, 0x62cb29a5a4445b60, 0x37bc870a0c7dd2b9, 0x24830a9d3171f0fd},
      {0x7361d77f843abe92, 0xa5bb2bd3273411fb, 0x9c941f314b3e2399, 0x15df9cddbb9fd3ec}
   };
}