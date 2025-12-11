
//! \file

#ifndef Y_Fit_Parameters_Included
#define Y_Fit_Parameters_Included 1

#include "y/mkl/fit/parameter.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/mkl/fit/type/assembly.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            typedef SuffixSet<String,Parameter::Pointer> ParameterDB; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! global parameters collection
            //
            //
            //__________________________________________________________________
            class Parameters : public Ingress< const ParameterDB >, public Assembly
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const          CallSign;      //!< "Fit::Parameters"
                typedef ParameterDB::ConstIterator ConstIterator; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Parameters();                   //!< setup
                virtual ~Parameters() noexcept;          //!< cleanup
                explicit Parameters(const String &);     //!< setup with list
                explicit Parameters(const char * const); //!< setup with list
                Parameters(const Parameters &);          //!< duplicate

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! append a new named parameter \param uid requested name \return *this
                template <typename UID> inline
                Parameters & operator<<(const UID &uid)
                {
                    const Parameter::Pointer p = new Parameter(uid,db.size()+1);
                    return grow(p);
                }


                const Parameter & operator[](const String &)     const; //!< \return named parameter
                const Parameter & operator[](const char * const) const; //!< \return named parameter
                const Parameter & operator[](const char )        const; //!< \return named parameter

                //! query flag for each parameter \param used used flags
                void  queryEnv(Writable<bool> &used) const;

            private:
                Y_Disable_Assign(Parameters); //!< discaring
                Y_Ingress_Decl();                      //!< helper
                Parameters & grow(const Parameter::Pointer &); //!< \return *this*

                //! setup with a list of paramters
                /**
                 \param plist list of parameters separated with ':'
                 */
                void setup(const String &plist);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                ParameterDB db; //!< parameters
            };
        }

    }

}

#endif // !Y_Fit_Parameters_Included

