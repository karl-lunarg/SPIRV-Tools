// Copyright (c) 2015 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
// KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
// SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
//    https://www.khronos.org/registry/
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

#include "UnitSPIRV.h"

TEST(FixWord, Default) {
  spv_endianness_t endian;
  if (I32_ENDIAN_HOST == I32_ENDIAN_LITTLE) {
    endian = SPV_ENDIANNESS_LITTLE;
  } else {
    endian = SPV_ENDIANNESS_BIG;
  }
  uint32_t word = 0x53780921;
  ASSERT_EQ(word, spvFixWord(word, endian));
}

TEST(FixWord, Reorder) {
  spv_endianness_t endian;
  if (I32_ENDIAN_HOST == I32_ENDIAN_LITTLE) {
    endian = SPV_ENDIANNESS_BIG;
  } else {
    endian = SPV_ENDIANNESS_LITTLE;
  }
  uint32_t word = 0x53780921;
  uint32_t result = 0x21097853;
  ASSERT_EQ(result, spvFixWord(word, endian));
}