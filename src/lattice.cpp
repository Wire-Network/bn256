#include <lattice.h>
#include <bitlen.h>

namespace bn256 {

   using namespace boost::multiprecision::literals;
   using namespace boost::multiprecision;

   // decompose takes a scalar mod order as input and finds a short,
   // positive decomposition of it wrt to the lattice basis.
   std::vector<int512_t> lattice::decompose(const int512_t& k) const {
      auto n = inverse_.size();
      std::vector<int512_t> c(n);

      // Calculate closest vector in lattice to <k,0,0,...> with Babai's rounding.
      for (std::size_t i = 0; i < n; i++) {
         c[i] = k * inverse_[i];
         round(c[i], det_);
      }

      // Transform vectors according to c and subtract <k,0,0,...>.
      std::vector<int512_t> out(n);
      int512_t temp;
      for (std::size_t i = 0; i < n; i++) {
         out[i] = 0;
         for (std::size_t j = 0; j < n; j++) {
            temp = c[j] * vectors_[j][i];
            out[i] += temp;
         }
         out[i].backend().negate();
         out[i] += vectors_[0][i];
         out[i] += vectors_[0][i];
      }
      out[0] += k;
      return out;
   }

   std::vector<uint8_t> lattice::multi(const int512_t& scalar) const {
      std::vector<int512_t> decomp = decompose(scalar);

      std::size_t maxlen = 0;
      for (const auto& x: decomp) {
         const auto len = bitlen(x);
         if (len > maxlen) {
            maxlen = len;
         }
      }

      std::vector<uint8_t> out(maxlen);
      for (std::size_t j = 0; j < decomp.size(); ++j) {
         for (std::size_t i = 0; i < maxlen; ++i) {
            if (bit_test(decomp[j], i)) {
               out[i] += (1 << j);
            }
         }
      }

      return out;
   }

   // round sets num to num/denom rounded to the nearest integer.
   void lattice::round(int512_t& num, const int512_t& denom) {
      if (denom != 0) {
         const int512_t half = constants::order >> 1;
         num /= denom;
         int512_t rem = num % denom;
         auto compare_result = rem.compare(half);
         if (compare_result > 0) {
            num++;
         }
      }
   }
}