/*
 * Copyright 2026 Jill M. Goodridge, d/b/a Dobrya-Sydney-Gleeman (DSG) Systems
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://apache.org
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * =========================================================================
 * SECURITY NOTICE & ARCHITECTURAL DISCLAIMER:
 * This source file contains foundational, primitive implementations of the 
 * multiplier-free software interface layers for the DSG Systems ecosystem. 
 * Hardware-level implementations, specific register trace paths, and advanced 
 * cryptographic multi-state gating subsystems (including Tri_Hole_Guard core 
 * layouts and the T++ extended macro dictionary) are subject to independent 
 * provisional patent priorities filed with the USPTO.
 * =========================================================================
 */

# T++ Data Language Specification v1.0
## Balanced 6-Trit Positional Serialization Protocol for Multiplier-Free Substrates

This document defines the official data layout, encoding rules, and character map definitions for **T++**, the full-stack data serialization language engineered for the **Dobrya-Sydney-Gleeman (DSG) Systems** edge ecosystem. 

Traditional serialization protocols parse characters into binary bits, which mandates expensive multi-bit address translation layers when mapping data to specialized hardware registers. T++ bypasses this constraint by mapping symbols directly to a balanced ternary radix configuration spectrum $\{-1, 0, +1\}$ (notated inside the compiler arrays as `-, 0, +`).

## ⚙️ Core Architecture: The 6-Trit Envelope

Each individual character sequence is encapsulated within a strict **6-Trit Symbol Envelope**. 
*   **Mathematical Capacity:** A 6-trit configuration space provides a maximum mathematical envelope of $3^6 = 729$ unique execution states.
*   **Vocabulary Allocation:** The standard 128-character ASCII map occupies states $0$ through $127$. 
*   **Systemic Room:** The remaining 602 execution states are strictly unallocated within the public specification, serving as a clean architectural perimeter for localized hardware control lines, boundary break indicators, and advanced macro safety layers.

---

## 📑 Complete 128-Character Balanced Ternary Map

| Dec | Char | Tritcode Sequence | | Dec | Char | Tritcode Sequence | | Dec | Char | Tritcode Sequence |
|---|---|---|---|---|---|---|---|---|---|---|
| **0** | NUL | `000000` | | **43** | + | `00+0-+` | | **86** | V | `0+-000` |
| **1** | SOH | `00000+` | | **44** | , | `00+00-` | | **87** | W | `0+-00+` |
| **2** | STX | `0000+-` | | **45** | - | `00+000` | | **88** | X | `0+-0+-` |
| **3** | ETX | `0000+0` | | **46** | . | `00+00+` | | **89** | Y | `0+-0+0` |
| **4** | EOT | `0000++` | | **47** | / | `00+0+-` | | **90** | Z | `0+-0++` |
| **5** | ENQ | `0000-+` | | **48** | 0 | `00+0+0` | | **91** | [ | `0+--0-` |
| **6** | ACK | `0000-0` | | **49** | 1 | `00+0++` | | **92** | \ | `0+--00` |
| **7** | BEL | `0000--` | | **50** | 2 | `00+-0-` | | **93** | ] | `0+--0+` |
| **8** | BS | `000+--` | | **51** | 3 | `00+-00` | | **94** | ^ | `0+---0` |
| **9** | HT | `000+-0` | | **52** | 4 | `00+-0+` | | **95** | _ | `0+----+` |
| **10** | LF | `000+-+` | | **53** | 5 | `00+--0` | | **96** | ` | `0+--+-` |
| **11** | VT | `000+0-` | | **54** | 6 | `00+---+` | | **97** | a | `0+--+0` |
| **12** | FF | `000+00` | | **55** | 7 | `00+--+-` | | **98** | b | `0+--++` |
| **13** | CR | `000+0+` | | **56** | 8 | `00+--+0` | | **99** | c | `0+-+0-` |
| **14** | SO | `000++-` | | **57** | 9 | `00+--++` | | **100** | d | `0+-+00` |
| **15** | SI | `000++0` | | **58** | : | `0+0---` | | **101** | e | `0+-+0+` |
| **16** | DLE | `000+++` | | **59** | ; | `0+0--0` | | **102** | f | `0+-++-` |
| **17** | DC1 | `0000-+` | | **60** | < | `0+0--+` | | **103** | g | `0+-++0` |
| **18** | DC2 | `0000-0` | | **61** | = | `0+0-0-` | | **104** | h | `0+-+++` |
| **19** | DC3 | `0000--` | | **62** | > | `0+0-00` | | **105** | i | `0+000-` |
| **20** | DC4 | `00+---` | | **63** | ? | `0+0-0+` | | **106** | j | `0+0000` |
| **21** | NAK | `00+--0` | | **64** | @ | `0+0-+-` | | **107** | k | `0+000+` |
| **22** | SYN | `00+--+` | | **65** | A | `0+0-+0` | | **108** | l | `0+00+-` |
| **23** | ETB | `00+-0-` | | **66** | B | `0+0-++` | | **109** | m | `0+00+0` |
| **24** | CAN | `00+-00` | | **67** | C | `0+00--` | | **110** | n | `0+00++` |
| **25** | EM | `00+-0+` | | **68** | D | `0+00-0` | | **111** | o | `0+0+0-` |
| **26** | SUB | `00+-+-` | | **69** | E | `0+00-+` | | **112** | p | `0+0+00` |
| **27** | ESC | `00+-+0` | | **70** | F | `0+000-` | | **113** | q | `0+0+0+` |
| **28** | FS | `00+-++` | | **71** | G | `0+0000` | | **114** | r | `0+0++-` |
| **29** | GS | `00++--` | | **72** | H | `0+000+` | | **115** | s | `0+0++0` |
| **30** | RS | `00++-0` | | **73** | I | `0+00+-` | | **116** | t | `0+0+++` |
| **31** | US | `00++-+` | | **74** | J | `0+00+0` | | **117** | u | `0++---` |
| **32** | Space | `00++0-` | | **75** | K | `0+00++` | | **118** | v | `0++--0` |
| **33** | ! | `00++00` | | **76** | L | `0+0+0-` | | **119** | w | `0++--+` |
| **34** | " | `00++0+` | | **77** | M | `0+0+00` | | **120** | x | `0++-0-` |
| **35** | # | `00+++-` | | **78** | N | `0+0+0+` | | **121** | y | `0++-00` |
| **36** | \$ | `00+++0` | | **79** | O | `0+0++-` | | **122** | z | `0++-0+` |
| **37** | % | `00++++` | | **80** | P | `0+0++0` | | **123** | { | `0++-+-` |
| **38** | & | `00+---` | | **81** | Q | `0+0+++` | | **124** | \| | `0++-+0` |
| **39** | ' | `00+--0` | | **82** | R | `0+-0--` | | **125** | } | `0++-++` |
| **40** | ( | `00+--+` | | **83** | S | `0+-0-0` | | **126** | ~ | `0++0--` |
| **41** | ) | `00+-0-` | | **84** | T | `0+-0-+` | | **127** | DEL | `0++0-0` |
| **42** | * | `00+000` | | **85** | U | `0+-00-` | | | | |

---

## 🔢 Native Decimal-to-Trit Integer Blueprint

These raw numerical vectors feed directly into the T-TPU accumulator logic blocks, matching numerical magnitudes via direct base-3 positional weights: 3⁵(243), 3⁴(81), 3³(27), 3²(9), 3¹(3), 3⁰(1).

The core native decimal-to-trit integer map is established as follows:

*   `[Int 0]`  ::  `000000`  (Absolute Operational Zero / Register Purge State)
*   `[Int 1]`  ::  `00000+`  (Base Unit Positive / +1)
*   `[Int 2]`  ::  `0000+-`  (Sign Cancellation Unit / +3 - 1 = 2)
*   `[Int 3]`  ::  `0000+0`  (First Triad Base / +3)
*   `[Int 4]`  ::  `0000++`  (First Triad Maxima / +3 + 1 = 4)
*   `[Int 5]`  ::  `000+--`  (Second Triad Minima / +9 - 3 - 1 = 5)
*   `[Int 6]`  ::  `000+-0`  (Second Triad Vector / +9 - 3 = 6)
*   `[Int 7]`  ::  `000+-+`  (Second Triad Dynamic / +9 - 3 + 1 = 7)
*   `[Int 8]`  ::  `000+0-`  (Sub-Base Maxima / +9 - 1 = 8)
*   `[Int 9]`  ::  `000+00`  (Second Triad Base Anchor / +9)

## 🛠️ Compilation and Execution Bridge

In active environments using the open-source execution framework (`unpacker.cpp`), strings are converted into these 6-trit arrays using simple, low-overhead lookup arrays. Because execution logic maps directly to base-3 signs, characters do not pass through complex CPU arithmetic shift buffers, delivering maximum hardware-level memory isolation and zero runtime multiplier performance penalties.
