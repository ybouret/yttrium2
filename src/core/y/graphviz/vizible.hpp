//! \file

#ifndef Y_Vizible_Included
#define Y_Vizible_Included 1

#include "y/string/fwd.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{
    class OutputStream;

    //__________________________________________________________________________
    //
    //
    //
    //! helper to emit GraphViz code
    //
    //
    //__________________________________________________________________________
    class Vizible
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Vizible() noexcept; //!< setup
        virtual ~Vizible() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        OutputStream & nodeName(OutputStream &) const;                  //!< address to node name \return output stream
        OutputStream & to(const Vizible * const, OutputStream &) const; //!< arrow from this \return output stream

        static OutputStream & Label(OutputStream &, const Core::String<char> &); //!< emit label \return output stream
        static OutputStream & Label(OutputStream &, const char * const); //!< emit lable \return output stream
        static OutputStream & Label(OutputStream &, const char); //!< emit label \return output stream
        static OutputStream & Endl(OutputStream &); //!< ";\n" \return output stream

        static OutputStream & Enter(OutputStream &); //!< prolog \return output stream
        static OutputStream & Leave(OutputStream &); //!< epilog \return output stream

        //! save Vizible object with a 'viz(OutputStream&)' method
        /**
         \param fp output stream
         \param obj object with 'OutputStream & viz(OutputStream&)' method
         \return output stream
         */
        template <typename CLASS> static inline
        OutputStream & Save(OutputStream &fp, const CLASS &obj)
        {
            return Leave( obj.viz( Enter(fp) ) );
        }

        //! save Vizible object with a 'viz(OutputStream&,ARG &)' method
        /**
         \param fp  output stream
         \param obj object with 'OutputStream & viz(OutputStream&)' method
         \param arg argument
         \return output stream
         */
        template <typename CLASS, typename ARG> static inline
        OutputStream & Save(OutputStream &fp, const CLASS &obj, ARG &arg)
        {
            return Leave( obj.viz( Enter(fp), arg ) );
        }



        //! convert 'file.dot' to 'file.png'
        /**
         \param dotFile graphViz dot file
         \param keepDot don't remove dotFile upon success
         */
        static void DotToPng(const Core::String<char> &dotFile,const bool keepDot=false);
        static void DotToPng(const char * const,const bool = false); //!< wrapper

        //! save Vizible object to output file
        /**
         \param dotFile filename
         \param obj     object with 'viz(OutputStream&)' method
         */
        template <typename FILENAME, typename CLASS> static inline
        void SaveAs(const FILENAME &dotFile, const CLASS &obj)
        {
            OutputStream * const fp = NewDotFile(dotFile);
            try { Save(*fp,obj); DelDotFile(fp); }
            catch(...) { DelDotFile(fp); throw; }
        }

        //! save Vizible object to output file
        /**
         \param dotFile filename
         \param obj     object with 'viz(OutputStream&)' method
         \param arg argument
         */
        template <typename FILENAME, typename CLASS, typename ARG> static inline
        void SaveAs(const FILENAME &dotFile, const CLASS &obj, ARG &arg)
        {
            OutputStream * const fp = NewDotFile(dotFile);
            try { Save(*fp,obj,arg); DelDotFile(fp); }
            catch(...) { DelDotFile(fp); throw; }
        }



        //! save and render vizible object
        /**
         \param dotFile 'file.dot'
         \param obj     object with 'viz(OutputStream&)' method
         \param keepDot don't remove dotFile upon success
         - upon success 'file.png' is created
         */
        template <typename FILENAME, typename CLASS> static inline
        void Render(const FILENAME &dotFile, const CLASS &obj, const bool keepDot=false)
        {
            SaveAs(dotFile,obj);
            DotToPng(dotFile,keepDot);
        }





    private:
        Y_Disable_Copy_And_Assign(Vizible); //!< discarding
        static OutputStream * NewDotFile(const Core::String<char> &);    //!< \return output file
        static OutputStream * NewDotFile(const char * const);            //!< \return output file
        static void           DelDotFile(OutputStream * const) noexcept; //!< close file

    };
}

#endif

