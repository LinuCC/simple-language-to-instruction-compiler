#ifndef RISC_GEN_RISCV_TYPES_HH_
#define RISC_GEN_RISCV_TYPES_HH_

#include <iostream>
#include <string>
#include <vector>

namespace risc_gen {

/**
 * Register der RISC-V Architektur
 */
enum Register {
  ZERO = 0, // Hard-wired zero
  RA = 1,   // Return address
  SP = 2,   // Stack pointer
  GP = 3,   // Global pointer
  TP = 4,   // Thread pointer
  T0 = 5,   // Temporaries
  T1 = 6,
  T2 = 7,
  FP = 8,  // Frame pointer
  S1 = 9,  // Saved registers
  A0 = 10, // Function arguments/return values
  A1 = 11,
  A2 = 12,
  A3 = 13,
  A4 = 14,
  A5 = 15,
  A6 = 16,
  A7 = 17,
  S2 = 18, // Saved registers
  S3 = 19,
  S4 = 20,
  S5 = 21,
  S6 = 22,
  S7 = 23,
  S8 = 24,
  S9 = 25,
  S10 = 26,
  S11 = 27,
  T3 = 28, // Temporaries
  T4 = 29,
  T5 = 30,
  T6 = 31
};
} // namespace risc_gen

#endif /* !RISC_GEN_RISCV_TYPES_HH_  */
