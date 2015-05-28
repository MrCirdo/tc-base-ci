/**
 ** \file target/mips/spim-layout.hh
 ** \brief Declaration of target::mips::SpimLayout.
 */

#ifndef TARGET_MIPS_SPIM_LAYOUT_HH
# define TARGET_MIPS_SPIM_LAYOUT_HH

# include <assem/layout.hh>

namespace target
{
  namespace mips
  {

    /// Abstract SPIM's fragments's layout.
    class SpimLayout : public assem::Layout
    {
      /** \name Construction.
       ** \{ */
    protected:
      /// Construct a SpimLayout.
      SpimLayout() = default;

    public:
      /// Return the unique instance of SpimLayout.
      static SpimLayout& instance();
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

  } // namespace mips
} // namespace target

#endif // !TARGET_MIPS_SPIM_LAYOUT_HH
