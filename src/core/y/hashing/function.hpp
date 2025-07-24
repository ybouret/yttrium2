//! \file
#ifndef Y_HASHING_FUNCTION_INCLUDED
#define Y_HASHING_FUNCTION_INCLUDED 1


#include "y/object.hpp"
#include "y/counted.hpp"
#include "y/ability/identifiable.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    
    namespace Memory { class ReadOnlyBuffer; }

	namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //! base class for hashing function
        //
        //______________________________________________________________________
		class Function : public Object, public Counted, public Identifiable
		{
		public:
            //__________________________________________________________________
            //
            // types and definitions
            //__________________________________________________________________
            typedef ArcPtr<Function> Pointer; //!< alias
            const size_t length;              //!< output generation
			const size_t window;              //!< internal window size

            //__________________________________________________________________
            //
            // virtual interface
            //__________________________________________________________________
            virtual            ~Function()                             noexcept;     //!< destructor
            virtual void        set()                                  noexcept = 0; //!< initialize
			virtual void        run(const void *buffer, size_t buflen) noexcept = 0; //!< process bytes \param buffer address \param buflen length
            virtual void        get(void *output, size_t outlen)       noexcept = 0; //!< finalize/fill array \param output address \param outlen length

            //__________________________________________________________________
            //
            // non virtual interface
            //__________________________________________________________________

            //! helper, usually used by the virtual 'get' method.
            /**
             \param output output buffer
             \param outlen output length
             \param input input buffer
             \param inlen input length
             */
			static void fill(void *output, size_t outlen, const void *input, size_t inlen) noexcept;
            
            //! run(block_addr,block_size)
            void operator()(const void *block_addr, const size_t block_size) noexcept;
            
            //! run(msg)
            void operator()(const char *msg) noexcept;
            
            //! run(buffer.ro_addr(),buffer.measure());
            void operator()(const Memory::ReadOnlyBuffer &) noexcept;
            
            
            
            //! hash a block
            void        block(void *output, size_t outlen, const void *block_addr, const size_t block_size) noexcept;
            
            //! hash a memory buffer
            void        block(void *output, size_t outlen, const Memory::ReadOnlyBuffer &) noexcept;
            
            //! hash a message
            void        block(void *output, size_t outlen, const char *msg) noexcept;
            
        protected:
            //! initialize function \param L length \param W window
			explicit Function( size_t L, size_t W) noexcept;
			
		private:
            Y_Disable_Copy_And_Assign(Function); //!< discarding
		};
		
        //! format hashing function prototype
#define Y_HASHING_FUNCTION_DECL(NAME,L,W)                                \
static const char * const CallSign;                                      \
explicit NAME() noexcept;                                                \
virtual ~NAME() noexcept;                                                \
static inline Function * Create() { return new NAME(); }                 \
static const size_t __length = L ;                                       \
static const size_t __window = W ;                                       \
inline virtual const char *callSign() const noexcept { return CallSign;} \
virtual void set() noexcept;                                             \
virtual void run( const void *buf, size_t len ) noexcept;                \
virtual void get( void *output, size_t outlen ) noexcept 
        
	}

    
}


#endif
