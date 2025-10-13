
//! \file

#ifndef Y_Fit_Variables_Included
#define Y_Fit_Variables_Included 1

#include "y/mkl/fit/variable.hpp"
#include "y/mkl/fit/parameters.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            typedef SuffixSet<String,Variable::Pointer> VariableDB; //!< alias


            //__________________________________________________________________
            //
            //
            //
            //! Alias a global parameter to a local name
            //
            //
            //__________________________________________________________________
            class Alias
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param uid local name
                 \param prm gobal parameter
                 */
                template <typename UID> inline
                Alias(const UID &uid, const Parameter &prm) :
                target(uid),source(prm)
                {
                }

                Alias(const Alias &); //!< duplicate
                ~Alias() noexcept;    //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const String     target; //!< target name
                const Parameter &source; //!< source parameter

            private:
                Y_Disable_Assign(Alias); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Local variables
            //
            //
            //__________________________________________________________________
            class Variables : public Ingress<const VariableDB>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const CallSign; //!< "Fit::Variables"

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Variables();           //!< setup
                virtual ~Variables() noexcept;  //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return primary variable
                Variables & operator<<(const Parameter &);

                //! \return replica variable
                Variables & operator<<(const Alias &);

                const Variable & get(const String &)     const; //!< \return variable by name
                const Variable & get(const char * const) const; //!< \return variable by name
                const Variable & get(const char)         const; //!< \return variable by name

                //! access variable \param uid name \return variable.name == uid
                template <typename UID> inline
                const Variable & operator[](const UID &uid) const
                {
                    return get(uid);
                }

                



            private:
                Y_Disable_Copy_And_Assign(Variables); //!< discarding
                Y_Ingress_Decl();                     //!< helper

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                VariableDB db; //!< variables
            };

        }
    }
}

#endif // !Y_Fit_Variables_Included
