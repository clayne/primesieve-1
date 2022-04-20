///
/// @file   LookupTables.cpp
/// @brief  Static gobal arrays.
///
/// Copyright (C) 2022 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#include <primesieve/bits.hpp>
#include <primesieve/forward.hpp>
#include <primesieve/Wheel.hpp>

#include <array>
#include <stdint.h>

namespace primesieve {

/// primesieve uses a bit array for sieving in which the 8 bits
/// of each byte correspond to the offsets:
/// { 1, 7, 11, 13, 17, 19, 23, 29 }. However, in order to more
/// efficiently sieve prime k-tuplets (e.g. twin primes) we
/// rearrange these offsets to { 7, 11, 13, 17, 19, 23, 29, 31 }.
/// 64 bits of the sieve array correspond to 8 bytes which span
/// an interval of size 30 * 8 = 240.
///
/// The index for this lookup table is computed using the count
/// trailing zeros CPU instruction. As a special case CTZ may return
/// the operand size (number of bits) if the input is zero. Hence
/// the maximum index is 64 for e.g. TZCNT(0) (on x64 CPUs)
/// therefore we add an additional 0 at the end of the array to
/// prevent out of bounds acceses.
///
const std::array<uint64_t, 65> bitValues =
{
    7,  11,  13,  17,  19,  23,  29, 31,
   37,  41,  43,  47,  49,  53,  59, 61,
   67,  71,  73,  77,  79,  83,  89, 91,
   97, 101, 103, 107, 109, 113, 119, 121,
  127, 131, 133, 137, 139, 143, 149, 151,
  157, 161, 163, 167, 169, 173, 179, 181,
  187, 191, 193, 197, 199, 203, 209, 211,
  217, 221, 223, 227, 229, 233, 239, 241,
  0
};

/// The De Bruijn bitscan is a fast method to compute the index of
/// the first set bit in a 64-bit integer using only integer
/// operations. For primesieve's use case this is as fast as the
/// bsf or tzcnt instructions on x64 (but more portable).
/// https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication
///
const std::array<uint64_t, 64> bruijnBitValues =
{
    7,  47,  11,  49,  67, 113,  13,  53,
   89,  71, 161, 101, 119, 187,  17, 233,
   59,  79,  91,  73, 133, 139, 163, 103,
  149, 121, 203, 169, 191, 217,  19, 239,
   43,  61, 109,  83, 157,  97, 181, 229,
   77, 131, 137, 143, 199, 167, 211,  41,
  107, 151, 179, 227, 127, 197, 209,  37,
  173, 223, 193,  31, 221,  29,  23, 241
};

/// Used to find the next multiple (of a prime)
/// that is not divisible by 2, 3 and 5.
///
const WheelInit wheel30Init[30] =
{
  { 1, 0 }, { 0, 0 }, { 5, 1 }, { 4, 1 }, { 3, 1}, { 2, 1 }, { 1, 1 }, { 0, 1 },
  { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 1, 3}, { 0, 3 }, { 3, 4 }, { 2, 4 },
  { 1, 4 }, { 0, 4 }, { 1, 5 }, { 0, 5 }, { 3, 6}, { 2, 6 }, { 1, 6 }, { 0, 6 },
  { 5, 7 }, { 4, 7 }, { 3, 7 }, { 2, 7 }, { 1, 7}, { 0, 7 }
};

/// Used to find the next multiple (of a prime)
/// that is not divisible by 2, 3, 5 and 7.
///
const WheelInit wheel210Init[210] =
{
  { 1, 0 },  { 0, 0 },  { 9, 1 },  { 8, 1 },  { 7, 1 },  { 6, 1 },  { 5, 1 },  { 4, 1 }, 
  { 3, 1 },  { 2, 1 },  { 1, 1 },  { 0, 1 },  { 1, 2 },  { 0, 2 },  { 3, 3 },  { 2, 3 }, 
  { 1, 3 },  { 0, 3 },  { 1, 4 },  { 0, 4 },  { 3, 5 },  { 2, 5 },  { 1, 5 },  { 0, 5 }, 
  { 5, 6 },  { 4, 6 },  { 3, 6 },  { 2, 6 },  { 1, 6 },  { 0, 6 },  { 1, 7 },  { 0, 7 }, 
  { 5, 8 },  { 4, 8 },  { 3, 8 },  { 2, 8 },  { 1, 8 },  { 0, 8 },  { 3, 9 },  { 2, 9 }, 
  { 1, 9 },  { 0, 9 },  { 1, 10 }, { 0, 10 }, { 3, 11 }, { 2, 11 }, { 1, 11 }, { 0, 11 }, 
  { 5, 12 }, { 4, 12 }, { 3, 12 }, { 2, 12 }, { 1, 12 }, { 0, 12 }, { 5, 13 }, { 4, 13 }, 
  { 3, 13 }, { 2, 13 }, { 1, 13 }, { 0, 13 }, { 1, 14 }, { 0, 14 }, { 5, 15 }, { 4, 15 }, 
  { 3, 15 }, { 2, 15 }, { 1, 15 }, { 0, 15 }, { 3, 16 }, { 2, 16 }, { 1, 16 }, { 0, 16 }, 
  { 1, 17 }, { 0, 17 }, { 5, 18 }, { 4, 18 }, { 3, 18 }, { 2, 18 }, { 1, 18 }, { 0, 18 }, 
  { 3, 19 }, { 2, 19 }, { 1, 19 }, { 0, 19 }, { 5, 20 }, { 4, 20 }, { 3, 20 }, { 2, 20 }, 
  { 1, 20 }, { 0, 20 }, { 7, 21 }, { 6, 21 }, { 5, 21 }, { 4, 21 }, { 3, 21 }, { 2, 21 }, 
  { 1, 21 }, { 0, 21 }, { 3, 22 }, { 2, 22 }, { 1, 22 }, { 0, 22 }, { 1, 23 }, { 0, 23 }, 
  { 3, 24 }, { 2, 24 }, { 1, 24 }, { 0, 24 }, { 1, 25 }, { 0, 25 }, { 3, 26 }, { 2, 26 }, 
  { 1, 26 }, { 0, 26 }, { 7, 27 }, { 6, 27 }, { 5, 27 }, { 4, 27 }, { 3, 27 }, { 2, 27 }, 
  { 1, 27 }, { 0, 27 }, { 5, 28 }, { 4, 28 }, { 3, 28 }, { 2, 28 }, { 1, 28 }, { 0, 28 }, 
  { 3, 29 }, { 2, 29 }, { 1, 29 }, { 0, 29 }, { 5, 30 }, { 4, 30 }, { 3, 30 }, { 2, 30 }, 
  { 1, 30 }, { 0, 30 }, { 1, 31 }, { 0, 31 }, { 3, 32 }, { 2, 32 }, { 1, 32 }, { 0, 32 }, 
  { 5, 33 }, { 4, 33 }, { 3, 33 }, { 2, 33 }, { 1, 33 }, { 0, 33 }, { 1, 34 }, { 0, 34 }, 
  { 5, 35 }, { 4, 35 }, { 3, 35 }, { 2, 35 }, { 1, 35 }, { 0, 35 }, { 5, 36 }, { 4, 36 }, 
  { 3, 36 }, { 2, 36 }, { 1, 36 }, { 0, 36 }, { 3, 37 }, { 2, 37 }, { 1, 37 }, { 0, 37 }, 
  { 1, 38 }, { 0, 38 }, { 3, 39 }, { 2, 39 }, { 1, 39 }, { 0, 39 }, { 5, 40 }, { 4, 40 }, 
  { 3, 40 }, { 2, 40 }, { 1, 40 }, { 0, 40 }, { 1, 41 }, { 0, 41 }, { 5, 42 }, { 4, 42 }, 
  { 3, 42 }, { 2, 42 }, { 1, 42 }, { 0, 42 }, { 3, 43 }, { 2, 43 }, { 1, 43 }, { 0, 43 }, 
  { 1, 44 }, { 0, 44 }, { 3, 45 }, { 2, 45 }, { 1, 45 }, { 0, 45 }, { 1, 46 }, { 0, 46 }, 
  { 9, 47 }, { 8, 47 }, { 7, 47 }, { 6, 47 }, { 5, 47 }, { 4, 47 }, { 3, 47 }, { 2, 47 }, 
  { 1, 47 }, { 0, 47 }
};

const WheelElement wheel30[8*8] =
{
  { BIT0, 6, 1, 1 }, { BIT4, 4, 1, 2 }, { BIT3, 2, 0, 3 }, { BIT7, 4, 1, 4 }, { BIT6, 2, 1, 5 }, { BIT2, 4, 1, 6 }, { BIT1, 6, 1, 7 }, { BIT5, 2, 1, 0 }, 
  { BIT1, 6, 2, 9 }, { BIT3, 4, 1, 10 }, { BIT7, 2, 1, 11 }, { BIT5, 4, 2, 12 }, { BIT0, 2, 0, 13 }, { BIT6, 4, 2, 14 }, { BIT2, 6, 2, 15 }, { BIT4, 2, 1, 8 }, 
  { BIT2, 6, 2, 17 }, { BIT7, 4, 2, 18 }, { BIT5, 2, 1, 19 }, { BIT4, 4, 2, 20 }, { BIT1, 2, 1, 21 }, { BIT0, 4, 1, 22 }, { BIT6, 6, 3, 23 }, { BIT3, 2, 1, 16 }, 
  { BIT3, 6, 3, 25 }, { BIT6, 4, 3, 26 }, { BIT0, 2, 1, 27 }, { BIT1, 4, 2, 28 }, { BIT4, 2, 1, 29 }, { BIT5, 4, 2, 30 }, { BIT7, 6, 4, 31 }, { BIT2, 2, 1, 24 }, 
  { BIT4, 6, 4, 33 }, { BIT2, 4, 2, 34 }, { BIT6, 2, 2, 35 }, { BIT0, 4, 2, 36 }, { BIT5, 2, 1, 37 }, { BIT7, 4, 3, 38 }, { BIT3, 6, 4, 39 }, { BIT1, 2, 1, 32 }, 
  { BIT5, 6, 5, 41 }, { BIT1, 4, 3, 42 }, { BIT2, 2, 1, 43 }, { BIT6, 4, 3, 44 }, { BIT7, 2, 2, 45 }, { BIT3, 4, 3, 46 }, { BIT4, 6, 5, 47 }, { BIT0, 2, 1, 40 }, 
  { BIT6, 6, 6, 49 }, { BIT5, 4, 4, 50 }, { BIT4, 2, 2, 51 }, { BIT3, 4, 4, 52 }, { BIT2, 2, 2, 53 }, { BIT1, 4, 4, 54 }, { BIT0, 6, 5, 55 }, { BIT7, 2, 2, 48 }, 
  { BIT7, 6, 1, 57 }, { BIT0, 4, 0, 58 }, { BIT1, 2, 0, 59 }, { BIT2, 4, 0, 60 }, { BIT3, 2, 0, 61 }, { BIT4, 4, 0, 62 }, { BIT5, 6, 0, 63 }, { BIT6, 2, 0, 56 }
};

const WheelElement wheel210[8*48] =
{
  { BIT0, 10, 2, 1 }, { BIT3, 2, 0, 2 }, { BIT7, 4, 1, 3 }, { BIT6, 2, 1, 4 }, { BIT2, 4, 1, 5 }, { BIT1, 6, 1, 6 }, { BIT5, 2, 1, 7 }, { BIT0, 6, 1, 8 }, 
  { BIT4, 4, 1, 9 }, { BIT3, 2, 0, 10 }, { BIT7, 4, 1, 11 }, { BIT6, 6, 2, 12 }, { BIT1, 6, 1, 13 }, { BIT5, 2, 1, 14 }, { BIT0, 6, 1, 15 }, { BIT4, 4, 1, 16 }, 
  { BIT3, 2, 0, 17 }, { BIT7, 6, 2, 18 }, { BIT2, 4, 1, 19 }, { BIT1, 6, 1, 20 }, { BIT5, 8, 2, 21 }, { BIT4, 4, 1, 22 }, { BIT3, 2, 0, 23 }, { BIT7, 4, 1, 24 }, 
  { BIT6, 2, 1, 25 }, { BIT2, 4, 1, 26 }, { BIT1, 8, 2, 27 }, { BIT0, 6, 1, 28 }, { BIT4, 4, 1, 29 }, { BIT3, 6, 1, 30 }, { BIT6, 2, 1, 31 }, { BIT2, 4, 1, 32 }, 
  { BIT1, 6, 1, 33 }, { BIT5, 2, 1, 34 }, { BIT0, 6, 1, 35 }, { BIT4, 6, 1, 36 }, { BIT7, 4, 1, 37 }, { BIT6, 2, 1, 38 }, { BIT2, 4, 1, 39 }, { BIT1, 6, 1, 40 }, 
  { BIT5, 2, 1, 41 }, { BIT0, 6, 1, 42 }, { BIT4, 4, 1, 43 }, { BIT3, 2, 0, 44 }, { BIT7, 4, 1, 45 }, { BIT6, 2, 1, 46 }, { BIT2, 10, 2, 47 }, { BIT5, 2, 1, 0 }, 
  { BIT1, 10, 3, 49 }, { BIT7, 2, 1, 50 }, { BIT5, 4, 2, 51 }, { BIT0, 2, 0, 52 }, { BIT6, 4, 2, 53 }, { BIT2, 6, 2, 54 }, { BIT4, 2, 1, 55 }, { BIT1, 6, 2, 56 }, 
  { BIT3, 4, 1, 57 }, { BIT7, 2, 1, 58 }, { BIT5, 4, 2, 59 }, { BIT0, 6, 2, 60 }, { BIT2, 6, 2, 61 }, { BIT4, 2, 1, 62 }, { BIT1, 6, 2, 63 }, { BIT3, 4, 1, 64 }, 
  { BIT7, 2, 1, 65 }, { BIT5, 6, 2, 66 }, { BIT6, 4, 2, 67 }, { BIT2, 6, 2, 68 }, { BIT4, 8, 3, 69 }, { BIT3, 4, 1, 70 }, { BIT7, 2, 1, 71 }, { BIT5, 4, 2, 72 }, 
  { BIT0, 2, 0, 73 }, { BIT6, 4, 2, 74 }, { BIT2, 8, 3, 75 }, { BIT1, 6, 2, 76 }, { BIT3, 4, 1, 77 }, { BIT7, 6, 3, 78 }, { BIT0, 2, 0, 79 }, { BIT6, 4, 2, 80 }, 
  { BIT2, 6, 2, 81 }, { BIT4, 2, 1, 82 }, { BIT1, 6, 2, 83 }, { BIT3, 6, 2, 84 }, { BIT5, 4, 2, 85 }, { BIT0, 2, 0, 86 }, { BIT6, 4, 2, 87 }, { BIT2, 6, 2, 88 }, 
  { BIT4, 2, 1, 89 }, { BIT1, 6, 2, 90 }, { BIT3, 4, 1, 91 }, { BIT7, 2, 1, 92 }, { BIT5, 4, 2, 93 }, { BIT0, 2, 0, 94 }, { BIT6, 10, 4, 95 }, { BIT4, 2, 1, 48 }, 
  { BIT2, 10, 4, 97 }, { BIT5, 2, 1, 98 }, { BIT4, 4, 2, 99 }, { BIT1, 2, 1, 100 }, { BIT0, 4, 1, 101 }, { BIT6, 6, 3, 102 }, { BIT3, 2, 1, 103 }, { BIT2, 6, 2, 104 }, 
  { BIT7, 4, 2, 105 }, { BIT5, 2, 1, 106 }, { BIT4, 4, 2, 107 }, { BIT1, 6, 2, 108 }, { BIT6, 6, 3, 109 }, { BIT3, 2, 1, 110 }, { BIT2, 6, 2, 111 }, { BIT7, 4, 2, 112 }, 
  { BIT5, 2, 1, 113 }, { BIT4, 6, 3, 114 }, { BIT0, 4, 1, 115 }, { BIT6, 6, 3, 116 }, { BIT3, 8, 3, 117 }, { BIT7, 4, 2, 118 }, { BIT5, 2, 1, 119 }, { BIT4, 4, 2, 120 }, 
  { BIT1, 2, 1, 121 }, { BIT0, 4, 1, 122 }, { BIT6, 8, 4, 123 }, { BIT2, 6, 2, 124 }, { BIT7, 4, 2, 125 }, { BIT5, 6, 3, 126 }, { BIT1, 2, 1, 127 }, { BIT0, 4, 1, 128 }, 
  { BIT6, 6, 3, 129 }, { BIT3, 2, 1, 130 }, { BIT2, 6, 2, 131 }, { BIT7, 6, 3, 132 }, { BIT4, 4, 2, 133 }, { BIT1, 2, 1, 134 }, { BIT0, 4, 1, 135 }, { BIT6, 6, 3, 136 }, 
  { BIT3, 2, 1, 137 }, { BIT2, 6, 2, 138 }, { BIT7, 4, 2, 139 }, { BIT5, 2, 1, 140 }, { BIT4, 4, 2, 141 }, { BIT1, 2, 1, 142 }, { BIT0, 10, 4, 143 }, { BIT3, 2, 1, 96 }, 
  { BIT3, 10, 6, 145 }, { BIT0, 2, 1, 146 }, { BIT1, 4, 2, 147 }, { BIT4, 2, 1, 148 }, { BIT5, 4, 2, 149 }, { BIT7, 6, 4, 150 }, { BIT2, 2, 1, 151 }, { BIT3, 6, 3, 152 }, 
  { BIT6, 4, 3, 153 }, { BIT0, 2, 1, 154 }, { BIT1, 4, 2, 155 }, { BIT4, 6, 3, 156 }, { BIT7, 6, 4, 157 }, { BIT2, 2, 1, 158 }, { BIT3, 6, 3, 159 }, { BIT6, 4, 3, 160 }, 
  { BIT0, 2, 1, 161 }, { BIT1, 6, 3, 162 }, { BIT5, 4, 2, 163 }, { BIT7, 6, 4, 164 }, { BIT2, 8, 4, 165 }, { BIT6, 4, 3, 166 }, { BIT0, 2, 1, 167 }, { BIT1, 4, 2, 168 }, 
  { BIT4, 2, 1, 169 }, { BIT5, 4, 2, 170 }, { BIT7, 8, 5, 171 }, { BIT3, 6, 3, 172 }, { BIT6, 4, 3, 173 }, { BIT0, 6, 3, 174 }, { BIT4, 2, 1, 175 }, { BIT5, 4, 2, 176 }, 
  { BIT7, 6, 4, 177 }, { BIT2, 2, 1, 178 }, { BIT3, 6, 3, 179 }, { BIT6, 6, 4, 180 }, { BIT1, 4, 2, 181 }, { BIT4, 2, 1, 182 }, { BIT5, 4, 2, 183 }, { BIT7, 6, 4, 184 }, 
  { BIT2, 2, 1, 185 }, { BIT3, 6, 3, 186 }, { BIT6, 4, 3, 187 }, { BIT0, 2, 1, 188 }, { BIT1, 4, 2, 189 }, { BIT4, 2, 1, 190 }, { BIT5, 10, 6, 191 }, { BIT2, 2, 1, 144 }, 
  { BIT4, 10, 6, 193 }, { BIT6, 2, 2, 194 }, { BIT0, 4, 2, 195 }, { BIT5, 2, 1, 196 }, { BIT7, 4, 3, 197 }, { BIT3, 6, 4, 198 }, { BIT1, 2, 1, 199 }, { BIT4, 6, 4, 200 }, 
  { BIT2, 4, 2, 201 }, { BIT6, 2, 2, 202 }, { BIT0, 4, 2, 203 }, { BIT5, 6, 4, 204 }, { BIT3, 6, 4, 205 }, { BIT1, 2, 1, 206 }, { BIT4, 6, 4, 207 }, { BIT2, 4, 2, 208 }, 
  { BIT6, 2, 2, 209 }, { BIT0, 6, 3, 210 }, { BIT7, 4, 3, 211 }, { BIT3, 6, 4, 212 }, { BIT1, 8, 5, 213 }, { BIT2, 4, 2, 214 }, { BIT6, 2, 2, 215 }, { BIT0, 4, 2, 216 }, 
  { BIT5, 2, 1, 217 }, { BIT7, 4, 3, 218 }, { BIT3, 8, 5, 219 }, { BIT4, 6, 4, 220 }, { BIT2, 4, 2, 221 }, { BIT6, 6, 4, 222 }, { BIT5, 2, 1, 223 }, { BIT7, 4, 3, 224 }, 
  { BIT3, 6, 4, 225 }, { BIT1, 2, 1, 226 }, { BIT4, 6, 4, 227 }, { BIT2, 6, 4, 228 }, { BIT0, 4, 2, 229 }, { BIT5, 2, 1, 230 }, { BIT7, 4, 3, 231 }, { BIT3, 6, 4, 232 }, 
  { BIT1, 2, 1, 233 }, { BIT4, 6, 4, 234 }, { BIT2, 4, 2, 235 }, { BIT6, 2, 2, 236 }, { BIT0, 4, 2, 237 }, { BIT5, 2, 1, 238 }, { BIT7, 10, 7, 239 }, { BIT1, 2, 1, 192 }, 
  { BIT5, 10, 8, 241 }, { BIT2, 2, 1, 242 }, { BIT6, 4, 3, 243 }, { BIT7, 2, 2, 244 }, { BIT3, 4, 3, 245 }, { BIT4, 6, 5, 246 }, { BIT0, 2, 1, 247 }, { BIT5, 6, 5, 248 }, 
  { BIT1, 4, 3, 249 }, { BIT2, 2, 1, 250 }, { BIT6, 4, 3, 251 }, { BIT7, 6, 5, 252 }, { BIT4, 6, 5, 253 }, { BIT0, 2, 1, 254 }, { BIT5, 6, 5, 255 }, { BIT1, 4, 3, 256 }, 
  { BIT2, 2, 1, 257 }, { BIT6, 6, 5, 258 }, { BIT3, 4, 3, 259 }, { BIT4, 6, 5, 260 }, { BIT0, 8, 6, 261 }, { BIT1, 4, 3, 262 }, { BIT2, 2, 1, 263 }, { BIT6, 4, 3, 264 }, 
  { BIT7, 2, 2, 265 }, { BIT3, 4, 3, 266 }, { BIT4, 8, 6, 267 }, { BIT5, 6, 5, 268 }, { BIT1, 4, 3, 269 }, { BIT2, 6, 4, 270 }, { BIT7, 2, 2, 271 }, { BIT3, 4, 3, 272 }, 
  { BIT4, 6, 5, 273 }, { BIT0, 2, 1, 274 }, { BIT5, 6, 5, 275 }, { BIT1, 6, 4, 276 }, { BIT6, 4, 3, 277 }, { BIT7, 2, 2, 278 }, { BIT3, 4, 3, 279 }, { BIT4, 6, 5, 280 }, 
  { BIT0, 2, 1, 281 }, { BIT5, 6, 5, 282 }, { BIT1, 4, 3, 283 }, { BIT2, 2, 1, 284 }, { BIT6, 4, 3, 285 }, { BIT7, 2, 2, 286 }, { BIT3, 10, 8, 287 }, { BIT0, 2, 1, 240 }, 
  { BIT6, 10, 10, 289 }, { BIT4, 2, 2, 290 }, { BIT3, 4, 4, 291 }, { BIT2, 2, 2, 292 }, { BIT1, 4, 4, 293 }, { BIT0, 6, 5, 294 }, { BIT7, 2, 2, 295 }, { BIT6, 6, 6, 296 }, 
  { BIT5, 4, 4, 297 }, { BIT4, 2, 2, 298 }, { BIT3, 4, 4, 299 }, { BIT2, 6, 6, 300 }, { BIT0, 6, 5, 301 }, { BIT7, 2, 2, 302 }, { BIT6, 6, 6, 303 }, { BIT5, 4, 4, 304 }, 
  { BIT4, 2, 2, 305 }, { BIT3, 6, 6, 306 }, { BIT1, 4, 4, 307 }, { BIT0, 6, 5, 308 }, { BIT7, 8, 8, 309 }, { BIT5, 4, 4, 310 }, { BIT4, 2, 2, 311 }, { BIT3, 4, 4, 312 }, 
  { BIT2, 2, 2, 313 }, { BIT1, 4, 4, 314 }, { BIT0, 8, 7, 315 }, { BIT6, 6, 6, 316 }, { BIT5, 4, 4, 317 }, { BIT4, 6, 6, 318 }, { BIT2, 2, 2, 319 }, { BIT1, 4, 4, 320 }, 
  { BIT0, 6, 5, 321 }, { BIT7, 2, 2, 322 }, { BIT6, 6, 6, 323 }, { BIT5, 6, 6, 324 }, { BIT3, 4, 4, 325 }, { BIT2, 2, 2, 326 }, { BIT1, 4, 4, 327 }, { BIT0, 6, 5, 328 }, 
  { BIT7, 2, 2, 329 }, { BIT6, 6, 6, 330 }, { BIT5, 4, 4, 331 }, { BIT4, 2, 2, 332 }, { BIT3, 4, 4, 333 }, { BIT2, 2, 2, 334 }, { BIT1, 10, 9, 335 }, { BIT7, 2, 2, 288 }, 
  { BIT7, 10, 1, 337 }, { BIT1, 2, 0, 338 }, { BIT2, 4, 0, 339 }, { BIT3, 2, 0, 340 }, { BIT4, 4, 0, 341 }, { BIT5, 6, 0, 342 }, { BIT6, 2, 0, 343 }, { BIT7, 6, 1, 344 }, 
  { BIT0, 4, 0, 345 }, { BIT1, 2, 0, 346 }, { BIT2, 4, 0, 347 }, { BIT3, 6, 0, 348 }, { BIT5, 6, 0, 349 }, { BIT6, 2, 0, 350 }, { BIT7, 6, 1, 351 }, { BIT0, 4, 0, 352 }, 
  { BIT1, 2, 0, 353 }, { BIT2, 6, 0, 354 }, { BIT4, 4, 0, 355 }, { BIT5, 6, 0, 356 }, { BIT6, 8, 1, 357 }, { BIT0, 4, 0, 358 }, { BIT1, 2, 0, 359 }, { BIT2, 4, 0, 360 }, 
  { BIT3, 2, 0, 361 }, { BIT4, 4, 0, 362 }, { BIT5, 8, 0, 363 }, { BIT7, 6, 1, 364 }, { BIT0, 4, 0, 365 }, { BIT1, 6, 0, 366 }, { BIT3, 2, 0, 367 }, { BIT4, 4, 0, 368 }, 
  { BIT5, 6, 0, 369 }, { BIT6, 2, 0, 370 }, { BIT7, 6, 1, 371 }, { BIT0, 6, 0, 372 }, { BIT2, 4, 0, 373 }, { BIT3, 2, 0, 374 }, { BIT4, 4, 0, 375 }, { BIT5, 6, 0, 376 }, 
  { BIT6, 2, 0, 377 }, { BIT7, 6, 1, 378 }, { BIT0, 4, 0, 379 }, { BIT1, 2, 0, 380 }, { BIT2, 4, 0, 381 }, { BIT3, 2, 0, 382 }, { BIT4, 10, 0, 383 }, { BIT6, 2, 0, 336 }
};

} // namespace
