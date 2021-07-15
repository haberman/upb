/*
 * Copyright (c) 2009-2021, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2009-2021, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* TODO: High-level file comment. */

/*
 * Copyright (c) 2009-2021 Google LLC All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

// Author: Wang Yi <godspeed_china@yeah.net>
#include <stdint.h>
#include <string.h>
#ifndef WYHASH32_BIG_ENDIAN
static inline unsigned _wyr32(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return v;}
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline unsigned _wyr32(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return __builtin_bswap32(v);}
#elif defined(_MSC_VER)
static inline unsigned _wyr32(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return _byteswap_ulong(v);}
#endif
static inline unsigned _wyr24(const uint8_t *p, unsigned k) { return (((unsigned)p[0])<<16)|(((unsigned)p[k>>1])<<8)|p[k-1];}
static inline void _wymix32(unsigned  *A,  unsigned  *B){
  uint64_t  c=*A^0x53c5ca59u;  c*=*B^0x74743c1bu;
  *A=(unsigned)c;
  *B=(unsigned)(c>>32);
}
static inline unsigned wyhash32(const void *key, uint64_t len, unsigned seed) {
  const uint8_t *p=(const uint8_t *)key; uint64_t i=len;
  unsigned see1=(unsigned)len; seed^=(unsigned)(len>>32); _wymix32(&seed, &see1);
  for(;i>8;i-=8,p+=8){  seed^=_wyr32(p); see1^=_wyr32(p+4); _wymix32(&seed, &see1); }
  if(i>=4){ seed^=_wyr32(p); see1^=_wyr32(p+i-4); } else if (i) seed^=_wyr24(p,i);
  _wymix32(&seed, &see1); _wymix32(&seed, &see1); return seed^see1;
}
static inline uint64_t wyrand(uint64_t *seed){  
  *seed+=0xa0761d6478bd642full; 
  uint64_t  see1=*seed^0xe7037ed1a0b428dbull;
  see1*=(see1>>32)|(see1<<32);
  return  (*seed*((*seed>>32)|(*seed<<32)))^((see1>>32)|(see1<<32));
}
static inline unsigned wy32x32(unsigned a,  unsigned  b) { _wymix32(&a,&b); _wymix32(&a,&b); return a^b;  }
static inline float wy2u01(unsigned r) { const float _wynorm=1.0f/(1ull<<23); return (r>>9)*_wynorm;}
static inline float wy2gau(unsigned r) { const float _wynorm=1.0f/(1ull<<9); return ((r&0x3ff)+((r>>10)&0x3ff)+((r>>20)&0x3ff))*_wynorm-3.0f;}
