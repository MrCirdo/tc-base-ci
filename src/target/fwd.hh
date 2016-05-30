/**
 ** \file target/fwd.hh
 ** \brief Forward declarations for target:: items.
 */

#pragma once

/// Multiple target support.
namespace target
{
  // cpu.hh.
  class Cpu;

  // cpu-limits.hh.
  class CpuLimits;

  // target.hh.
  class Target;

  // codegen.hh.
  class Codegen;

  // assembly.hh.
  class Assembly;

  namespace mips
  {
    // mips/cpu.hh.
    class Cpu;

    // ia32/target.hh.
    class Target;
  }

  namespace ia32
  {
    // ia32/cpu.hh.
    class Cpu;

    // ia32/target.hh.
    class Target;
  }
}
