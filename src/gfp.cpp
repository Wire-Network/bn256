#include <gfp.h>
#include <gfp_generic.h>
#include <constants.h>
#include <iostream>

namespace bn256 {

   void gfp::set_zero() noexcept {
      this->fill(0);
   }

   gfp gfp::invert() const noexcept {
      constexpr uint64_array_4_t bits = {
         0x3c208c16d87cfd45,
         0x97816a916871ca8d,
         0xb85045b68181585d,
         0x30644e72e131a029
      };

      gfp sum{}, power{};
      sum = constants::rn1;
      power = *this;

      for (auto word = 0; word < bits.size(); word++) {
         for (auto bit = 0; bit < 64; bit++) {
            if (((bits[word] >> bit) & 1) == 1) {
               gfp_mul(sum, sum, power);
            }
            gfp_mul(power, power, power);
         }
      }

      gfp_mul(sum, sum, constants::r3);
      return sum;
   }

   void gfp::marshal(nonstd::span<uint8_t, 32> out) const noexcept {
      for (auto w = 0; w < 4; w++) {
         for (auto b = 0; b < 8; b++) {
            uint8_t t = ((*this)[3-w] >> (56 - 8*b));
            out[8*w+b] = t;
         }
      }
   }

   std::error_code gfp::unmarshal(nonstd::span<const uint8_t, 32> in) noexcept {
      gfp& result = *this;
      // Unmarshal the bytes into little endian form
      for (auto w = 0; w < 4; w++) {
         result[3-w] = 0;
         for (auto b = 0; b < 8; b++) {
            result[3-w] += uint64_t(in[8*w+b]) << (56 - 8*b);
         }
      }

      // Ensure the point respects the curve modulus
      for (auto i = 3; i >= 0; i--) {
         if (result[i] < constants::p2[i]) {
            return {};
         }
         if (result[i] > constants::p2[i]) {
            return unmarshal_error::COORDINATE_EXCEEDS_MODULUS;
         }
      }
      return unmarshal_error::MALFORMED_POINT;
   }

   gfp gfp::mont_encode() const noexcept {
      gfp r;
      gfp_mul(r, *this, constants::r2);
      return r;
   }

   gfp gfp::mont_decode() const noexcept {
      constexpr gfp decode_b{1};
      gfp r;
      gfp_mul(r, *this, decode_b);
      return r;
   }

   std::string gfp::string() const noexcept {
      std::string result;
      result.resize(64);

      std::for_each(rbegin(), rend(), [buf = result.data()](uint64_t v) mutable{
         const char hex_table[]= "0123456789abcdef";
         unsigned char* p = reinterpret_cast<unsigned char*>(&v) + 8;
         for (int i = 0; i < sizeof(uint64_t); ++i) {
            unsigned x = *(--p);
            *buf++ = hex_table[(x >> 4)];
            *buf++ = hex_table[x & 0x0F];
         }
      });
      return result;
   }

   gfp new_gfp(int64_t x) noexcept {
      gfp out{};
      if (x >= 0) {
         out = {uint64_t(x)};
      } else {
         out = {uint64_t(-x)};
         out = -out;
      }
      out = out.mont_encode();
      return out;
   }

   std::ostream& operator << (std::ostream& os, const gfp& v) {
      os << v.string();
      return os;
   }
}
