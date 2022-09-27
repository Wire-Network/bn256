#pragma once
#include <gfp.h>

namespace bn256 {
   void gfp_neg(gfp& c, const gfp& a);
   void gfp_add(gfp& c, const gfp& a, const gfp& b);
   void gfp_sub(gfp& c, const gfp& a, const gfp& b);
   void gfp_mul(gfp& c, const gfp& a, const gfp& b);
}