/**
 ** \file target/ia32/gas-layout.hh
 ** \brief Print assembly for IA-32 a la GAS
 */

#ifndef TARGET_IA32_GAS_LAYOUT_HH
# define TARGET_IA32_GAS_LAYOUT_HH

# include <assem/layout.hh>

namespace target
{
  namespace ia32
  {

    /// Abstract GAS' fragments's layout.
    class GasLayout : public assem::Layout
    {
      /** \name Construction.
       ** \{ */
    protected:
      /// Construct a GasLayout.
      GasLayout() = default;

    public:
      /// Return the unique instance of GasLayout
      static GasLayout& instance();
      /** \} */

      /** \name Fragments's visitor.
       ** \{ */
    public:
      /// Layout an assembly procedure fragment.
      virtual void operator()(const assem::ProcFrag& a) override;
      /// Layout an assembly data fragment.
      virtual void operator()(const assem::DataFrag& a) override;
    public:
      /// Layout a list of assembly fragments.
      virtual void operator()(const assem::Fragments& a) override;
      /** \} */
    };

  } // namespace ia32
} // namespace target

#endif // !TARGET_IA32_GAS_LAYOUT_HH
