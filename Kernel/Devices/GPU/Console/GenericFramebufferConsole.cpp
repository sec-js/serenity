/*
 * Copyright (c) 2021, Liav A. <liavalb@hotmail.co.il>
 * Copyright (c) 2022, MacDue <macdue@dueutil.tech>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Kernel/Devices/GPU/Console/GenericFramebufferConsole.h>

namespace Kernel::Graphics {

// Note: This bitmap was generated from CathodeRegular10.font
constexpr unsigned char const font_cathode_8x16[128][16] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0000 (nul)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0001
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0002
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0003
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0004
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0005
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0006
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0007
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0008
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0009
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+000F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0010
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0011
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0012
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0013
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0014
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0015
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0016
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0017
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0018
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0019
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+001F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0020 ( )
    { 0x00, 0x00, 0x30, 0x78, 0x78, 0x78, 0x78, 0x78, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00 }, // U+0021 (!)
    { 0x00, 0x00, 0x6C, 0x6C, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0022 (")
    { 0x00, 0x00, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00 }, // U+0023 (#)
    { 0x00, 0x00, 0x30, 0x30, 0x78, 0xCC, 0xCC, 0x60, 0x18, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x00, 0x00 }, // U+0024 ($)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0xC4, 0x08, 0x10, 0x20, 0x46, 0x86, 0x00, 0x00, 0x00, 0x00 }, // U+0025 (%)
    { 0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x36, 0x5C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00 }, // U+0026 (&)
    { 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0027 (')
    { 0x00, 0x00, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x18, 0x0C, 0x00, 0x00 }, // U+0028 (()
    { 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00 }, // U+0029 ())
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x30, 0xFC, 0x30, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+002A (*)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+002B (+)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00 }, // U+002C (,)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+002D (-)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00 }, // U+002E (.)
    { 0x00, 0x00, 0x02, 0x06, 0x04, 0x0C, 0x18, 0x10, 0x30, 0x60, 0x40, 0xC0, 0x80, 0x00, 0x00, 0x00 }, // U+002F (/)
    { 0x00, 0x00, 0x7C, 0xC6, 0xCE, 0xCE, 0xDE, 0xD6, 0xF6, 0xE6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0030 (0)
    { 0x00, 0x00, 0x30, 0x70, 0xF0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00, 0x00, 0x00 }, // U+0031 (1)
    { 0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00 }, // U+0032 (2)
    { 0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x04, 0x38, 0x04, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0033 (3)
    { 0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00 }, // U+0034 (4)
    { 0x00, 0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x06, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0035 (5)
    { 0x00, 0x00, 0x1C, 0x30, 0x60, 0xC0, 0xC0, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0036 (6)
    { 0x00, 0x00, 0xFE, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00 }, // U+0037 (7)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0038 (8)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x0C, 0x18, 0x70, 0x00, 0x00, 0x00 }, // U+0039 (9)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00 }, // U+003A (:)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60, 0x00, 0x00 }, // U+003B (;)
    { 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xE0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00 }, // U+003C (<)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+003D (=)
    { 0x00, 0x00, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x0E, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x00, 0x00, 0x00 }, // U+003E (>)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00 }, // U+003F (?)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00, 0x00, 0x00 }, // U+0040 (@)
    { 0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+0041 (A)
    { 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 0x00 }, // U+0042 (B)
    { 0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC2, 0x66, 0x3C, 0x00, 0x00, 0x00 }, // U+0043 (C)
    { 0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00 }, // U+0044 (D)
    { 0x00, 0x00, 0xFE, 0x66, 0x62, 0x60, 0x68, 0x78, 0x68, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00 }, // U+0045 (E)
    { 0x00, 0x00, 0xFE, 0x66, 0x62, 0x60, 0x64, 0x7C, 0x64, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00 }, // U+0046 (F)
    { 0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xDE, 0xC6, 0xC6, 0xC6, 0x66, 0x3A, 0x00, 0x00, 0x00 }, // U+0047 (G)
    { 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+0048 (H)
    { 0x00, 0x00, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00 }, // U+0049 (I)
    { 0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00 }, // U+004A (J)
    { 0x00, 0x00, 0xE6, 0x66, 0x6C, 0x6C, 0x68, 0x78, 0x68, 0x6C, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00 }, // U+004B (K)
    { 0x00, 0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00 }, // U+004C (L)
    { 0x00, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+004D (M)
    { 0x00, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xFE, 0xDE, 0xCE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+004E (N)
    { 0x00, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00, 0x00, 0x00 }, // U+004F (O)
    { 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00 }, // U+0050 (P)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xDE, 0x7C, 0x0E, 0x00, 0x00 }, // U+0051 (Q)
    { 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x66, 0xF6, 0x00, 0x00, 0x00 }, // U+0052 (R)
    { 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0053 (S)
    { 0x00, 0x00, 0xFC, 0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00 }, // U+0054 (T)
    { 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0055 (U)
    { 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00 }, // U+0056 (V)
    { 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xFE, 0x7C, 0x6C, 0x00, 0x00, 0x00 }, // U+0057 (W)
    { 0x00, 0x00, 0xC6, 0xC6, 0x6C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+0058 (X)
    { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00 }, // U+0059 (Y)
    { 0x00, 0x00, 0xFE, 0xC6, 0x86, 0x0C, 0x18, 0x30, 0x60, 0x40, 0xC2, 0xC6, 0xFE, 0x00, 0x00, 0x00 }, // U+005A (Z)
    { 0x00, 0x00, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFC, 0x00, 0x00, 0x00 }, // U+005B ([)
    { 0x00, 0x00, 0x80, 0xC0, 0x40, 0x60, 0x30, 0x10, 0x18, 0x0C, 0x04, 0x06, 0x02, 0x00, 0x00, 0x00 }, // U+005C (\)
    { 0x00, 0x00, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0x00, 0x00, 0x00 }, // U+005D (])
    { 0x00, 0x00, 0x20, 0x70, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+005E (^)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00 }, // U+005F (_)
    { 0x00, 0x00, 0x60, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+0060 (`)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00 }, // U+0061 (a)
    { 0x00, 0x00, 0xE0, 0x60, 0x60, 0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x00, 0x00, 0x00 }, // U+0062 (b)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0063 (c)
    { 0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x3C, 0x6C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00 }, // U+0064 (d)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0065 (e)
    { 0x00, 0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00 }, // U+0066 (f)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xCC, 0x78, 0x00, 0x00 }, // U+0067 (g)
    { 0x00, 0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66, 0x66, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00 }, // U+0068 (h)
    { 0x00, 0x00, 0x30, 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00 }, // U+0069 (i)
    { 0x00, 0x00, 0x06, 0x06, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0xC6, 0xC6, 0x7C, 0x00, 0x00 }, // U+006A (j)
    { 0x00, 0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x68, 0x70, 0x68, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00 }, // U+006B (k)
    { 0x00, 0x00, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00 }, // U+006C (l)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFE, 0xD6, 0xD6, 0xD6, 0xD6, 0xC6, 0xC6, 0x00, 0x00, 0x00 }, // U+006D (m)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00 }, // U+006E (n)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+006F (o)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00, 0x00 }, // U+0070 (p)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E, 0x00, 0x00 }, // U+0071 (q)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x76, 0x66, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00 }, // U+0072 (r)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x40, 0x70, 0x1C, 0x04, 0xC6, 0x7C, 0x00, 0x00, 0x00 }, // U+0073 (s)
    { 0x00, 0x00, 0x10, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00 }, // U+0074 (t)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00 }, // U+0075 (u)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00, 0x00, 0x00 }, // U+0076 (v)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 0x00 }, // U+0077 (w)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x38, 0x38, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00 }, // U+0078 (x)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x0C, 0xF8, 0x00, 0x00 }, // U+0079 (y)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCC, 0x0C, 0x18, 0x30, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00 }, // U+007A (z)
    { 0x00, 0x00, 0x1E, 0x30, 0x30, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x30, 0x30, 0x1E, 0x00, 0x00, 0x00 }, // U+007B ({)
    { 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00 }, // U+007C (|)
    { 0x00, 0x00, 0xF0, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x18, 0xF0, 0x00, 0x00, 0x00 }, // U+007D (})
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // U+007E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  // U+007F
};

// FIXME: This assumes 32 bit BGR (Blue-Green-Red) palette
enum BGRColor : u32 {
    Black = 0,
    Blue = 0x0000FF,
    Green = 0x00FF00,
    Cyan = 0x0000FFFF,
    Red = 0xFF0000,
    Magenta = 0x00FF00FF,
    Brown = 0x00964B00,
    LightGray = 0x00D3D3D3,
    DarkGray = 0x00A9A9A9,
    BrightBlue = 0x0ADD8E6,
    BrightGreen = 0x0090EE90,
    BrightCyan = 0x00E0FFFF,
    BrightRed = 0x00D70A53,
    BrightMagenta = 0x00F984E5,
    Yellow = 0x00FFE135,
    White = 0x00FFFFFF,
};

static inline BGRColor convert_standard_color_to_bgr_color(Console::Color color)
{
    switch (color) {
    case Console::Color::Black:
        return BGRColor::Black;
    case Console::Color::Red:
        return BGRColor::Red;
    case Console::Color::Brown:
        return BGRColor::Brown;
    case Console::Color::Blue:
        return BGRColor::Blue;
    case Console::Color::Magenta:
        return BGRColor::Magenta;
    case Console::Color::Green:
        return BGRColor::Green;
    case Console::Color::Cyan:
        return BGRColor::Cyan;
    case Console::Color::LightGray:
        return BGRColor::LightGray;
    case Console::Color::DarkGray:
        return BGRColor::DarkGray;
    case Console::Color::BrightRed:
        return BGRColor::BrightRed;
    case Console::Color::BrightGreen:
        return BGRColor::BrightGreen;
    case Console::Color::Yellow:
        return BGRColor::Yellow;
    case Console::Color::BrightBlue:
        return BGRColor::BrightBlue;
    case Console::Color::BrightMagenta:
        return BGRColor::BrightMagenta;
    case Console::Color::BrightCyan:
        return BGRColor::BrightCyan;
    case Console::Color::White:
        return BGRColor::White;
    default:
        VERIFY_NOT_REACHED();
    }
}

size_t GenericFramebufferConsoleImpl::bytes_per_base_glyph() const
{
    // FIXME: We assume we have 32 bit bpp framebuffer.
    return 8 * 32;
}

size_t GenericFramebufferConsoleImpl::chars_per_line() const
{
    return max_column();
}

void GenericFramebufferConsoleImpl::set_cursor(size_t x, size_t y)
{
    hide_cursor();
    m_x = x;
    m_y = y;
    show_cursor();
}

GenericFramebufferConsoleImpl::FramebufferOffset GenericFramebufferConsoleImpl::framebuffer_offset(size_t x, size_t y)
{
    return { (&framebuffer_data()[x * sizeof(u32) * (m_glyph_columns + m_glyph_spacing) + y * m_glyph_rows * framebuffer_pitch()]) };
}

void GenericFramebufferConsoleImpl::hide_cursor()
{
    auto offset_in_framebuffer = framebuffer_offset(m_x, m_y);
    offset_in_framebuffer.bytes += framebuffer_pitch() * (m_glyph_rows - 1);
    for (size_t glyph_column = 0; glyph_column < m_glyph_columns; glyph_column++)
        offset_in_framebuffer.pixels[glyph_column] = m_cursor_overriden_pixels[glyph_column];
}

void GenericFramebufferConsoleImpl::show_cursor()
{
    auto offset_in_framebuffer = framebuffer_offset(m_x, m_y);
    offset_in_framebuffer.bytes += framebuffer_pitch() * (m_glyph_rows - 1);
    for (size_t glyph_column = 0; glyph_column < m_glyph_columns; glyph_column++) {
        m_cursor_overriden_pixels[glyph_column] = offset_in_framebuffer.pixels[glyph_column];
        memset(offset_in_framebuffer.pixels + glyph_column, 0xff, sizeof(u32));
    }
}

void GenericFramebufferConsoleImpl::clear(size_t x, size_t y, size_t length)
{
    if (x == 0 && length == max_column()) {
        // If we need to clear the entire row, just clean it with quick memset :)
        auto offset_in_framebuffer = framebuffer_offset(x, y);
        for (size_t glyph_row = 0; glyph_row < m_glyph_rows; glyph_row++) {
            memset(offset_in_framebuffer.pixels, 0, framebuffer_pitch());
            offset_in_framebuffer.bytes += framebuffer_pitch();
        }
        flush(0, m_glyph_rows * y, (m_glyph_columns + m_glyph_spacing) * length, 1);
        return;
    }
    for (size_t index = 0; index < length; index++) {
        if (x >= max_column()) {
            x = 0;
            y++;
            if (y >= max_row())
                y = 0;
        }
        clear_glyph(x, y);
    }
}

void GenericFramebufferConsoleImpl::clear_glyph(size_t x, size_t y)
{
    auto offset_in_framebuffer = framebuffer_offset(x, y);
    for (size_t glyph_row = 0; glyph_row < m_glyph_rows; glyph_row++) {
        memset(offset_in_framebuffer.pixels, 0, (m_glyph_columns + m_glyph_spacing) * sizeof(u32));
        offset_in_framebuffer.bytes += framebuffer_pitch();
    }
    flush_glyph(x, y);
}

void GenericFramebufferConsoleImpl::enable()
{
    memset(framebuffer_data(), 0, height() * framebuffer_pitch());
    m_enabled.store(true);
}

void GenericFramebufferConsoleImpl::disable()
{
    m_enabled.store(false);
}

void GenericFramebufferConsoleImpl::scroll_up()
{
    for (size_t row = 1; row < max_row(); row++) {
        auto prev_line = framebuffer_offset(0, row - 1);
        auto line = framebuffer_offset(0, row);
        for (size_t glyph_row = 0; glyph_row < m_glyph_rows; glyph_row++) {
            memmove(prev_line.pixels, line.pixels, width() * sizeof(*line.pixels));
            prev_line.bytes += framebuffer_pitch();
            line.bytes += framebuffer_pitch();
        }
    }

    for (size_t column = 0; column < max_column(); column++)
        clear_glyph(column, m_y);
}

void GenericFramebufferConsoleImpl::write(size_t x, size_t y, char ch, Color background, Color foreground, bool critical)
{
    if (!m_enabled.load())
        return;

    // If we are in critical printing mode, we need to handle new lines here
    // because there's no other responsible object to do that in the print call path
    if (critical && (ch == '\r' || ch == '\n')) {
        m_x = 0;
        m_y += 1;
        if (m_y >= max_row()) {
            m_y = max_row() - 1;
            scroll_up();
        }
        return;
    }

    if ((int)ch < 0x20 || (int)ch == 0x7f) {
        // FIXME: There's no point in printing empty glyphs...
        // Maybe try to add these special glyphs and print them.
        return;
    }

    clear_glyph(x, y);
    auto bitmap = font_cathode_8x16[(int)ch];
    auto offset_in_framebuffer = framebuffer_offset(x, y);
    BGRColor foreground_color = convert_standard_color_to_bgr_color(foreground);
    BGRColor background_color = convert_standard_color_to_bgr_color(background);
    for (size_t glyph_row = 0; glyph_row < m_glyph_rows; glyph_row++) {
        for (size_t glyph_column = m_glyph_columns; glyph_column > 0; glyph_column--) {
            bool pixel_set = bitmap[glyph_row] & (1 << glyph_column);
            offset_in_framebuffer.pixels[m_glyph_columns - glyph_column] = pixel_set ? foreground_color : background_color;
        }
        for (size_t spacing_column = 0; spacing_column < m_glyph_spacing; spacing_column++)
            offset_in_framebuffer.pixels[m_glyph_columns + spacing_column] = background_color;
        offset_in_framebuffer.bytes += framebuffer_pitch();
    }
    flush_glyph(x, y);

    m_x = x + 1;
    if (m_x >= max_column()) {
        m_x = 0;
        m_y = y + 1;
        if (m_y >= max_row()) {
            if (critical) {
                m_y = max_row() - 1;
                scroll_up();
            } else {
                m_y = 0;
            }
        }
    }
}

void GenericFramebufferConsoleImpl::flush_glyph(size_t x, size_t y)
{
    flush((m_glyph_columns + m_glyph_spacing) * x, m_glyph_rows * y, m_glyph_columns + m_glyph_spacing, m_glyph_rows);
}

void GenericFramebufferConsoleImpl::write(size_t x, size_t y, char ch, bool critical)
{
    write(x, y, ch, m_default_background_color, m_default_foreground_color, critical);
}

void GenericFramebufferConsoleImpl::write(char ch, bool critical)
{
    write(m_x, m_y, ch, m_default_background_color, m_default_foreground_color, critical);
}

void GenericFramebufferConsole::clear(size_t x, size_t y, size_t length)
{
    SpinlockLocker lock(m_lock);
    GenericFramebufferConsoleImpl::clear(x, y, length);
}

void GenericFramebufferConsole::clear_glyph(size_t x, size_t y)
{
    VERIFY(m_lock.is_locked());
    GenericFramebufferConsoleImpl::clear_glyph(x, y);
}

void GenericFramebufferConsole::enable()
{
    SpinlockLocker lock(m_lock);
    GenericFramebufferConsoleImpl::enable();
}

void GenericFramebufferConsole::disable()
{
    SpinlockLocker lock(m_lock);
    GenericFramebufferConsoleImpl::disable();
}

void GenericFramebufferConsole::write(size_t x, size_t y, char ch, Color background, Color foreground, bool critical)
{
    SpinlockLocker lock(m_lock);
    GenericFramebufferConsoleImpl::write(x, y, ch, background, foreground, critical);
}

}
