
#include "y/system/rtti.hpp"

namespace Yttrium
{
    namespace System
    {

        RTTI:: Alias:: ~Alias() noexcept {}
        RTTI:: Alias:: Alias(const String &     id) : String(id), next(0), prev(0) {}
        RTTI:: Alias:: Alias(const char * const id) : String(id), next(0), prev(0) {}

    }

}


namespace Yttrium
{
    namespace System
    {

        RTTI:: ~RTTI() noexcept
        {

        }


        RTTI:: RTTI( const std::type_info &ti, const size_t len) :
        CountedObject(),
        uuid( ti.name() ),
        bytes( len ),
        aliases()
        {
            assert(bytes>0);
        }

        const String & RTTI:: key() const noexcept { return uuid; }

        const String & RTTI:: name() const noexcept
        {
            return aliases.size ? *aliases.head : uuid;
        }


    }

}

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace System
    {

        //______________________________________________________________________
        //
        //
        //
        //! RTTI Database
        //
        //
        //______________________________________________________________________
        class RTTI:: DataBase : public Singleton<DataBase,ClassLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const               CallSign;
            static const Longevity                  LifeTime = LifeTimeOf::RTTI;
            typedef SuffixSet<String,RTTI::Pointer> RTTI_Set;
            typedef HashMap<String,RTTI::Pointer>   RTTI_Map;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void display(std::ostream &os,
                                        size_t        depth) const
            {
                init(os,depth);
                ++depth;
                for(RTTI_Set::ConstIterator it=rtti.begin();it!=rtti.end();++it)
                {
                    XML::Indent(os,depth) << **it << std::endl;
                }
                --depth;
                quit(os,depth);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline RTTI & get(const std::type_info &ti,
                              const size_t          len)
            {
                const String id( ti.name() );

                // check existence
                if(RTTI::Pointer *pp = rtti.search(id) )
                {
                    assert(rmap.search(id));
                    RTTI &r = **pp;
                    if(len!=r.bytes) throw Specific::Exception(CallSign,"bytes mismatch for <%s>", id.c_str());
                    return r;
                }

                assert(!rmap.search(id));

                // creation
                RTTI::Pointer p = new RTTI( ti, len );
                if(!rtti.insert(p)) throw Specific::Exception(CallSign,"could not insert '%s'", id.c_str());

                // reverse lookup
                try
                {
                    if(!rmap.insert(id,p)) throw Specific::Exception(CallSign,"could not map <%s>",id.c_str());
                }
                catch(...)
                {
                    rtti.remove(id);
                    assert(!rmap.search(id));
                    assert(!rtti.search(id));
                    throw;
                }

                return *p;
            }

            inline RTTI & aka(RTTI &r, const String &pseudo)
            {
                RTTI::Pointer * const self = rtti.search(r.uuid);
                if(!self) throw Specific::Exception(CallSign,"<%s> was not recorded", r.uuid.c_str());

                if( r.called(pseudo) ) return r;

                {
                    const RTTI::Pointer * const p = rmap.search(pseudo);
                    if( p ) throw Specific::Exception(CallSign,"<%s> already exist for <%s>", pseudo.c_str(), (**p).name().c_str() );
                }

                Coerce(r.aliases).pushTail( new Alias(pseudo) );
                try
                {
                    if( !rmap.insert(pseudo,*self))
                        throw Specific::Exception(CallSign,"could not map <%s>", pseudo.c_str());
                }
                catch(...)
                {
                    delete Coerce(r.aliases).popTail();
                    throw;
                }
                return r;
            }

            inline RTTI & aka(RTTI &r, const char * const pseudo)
            {
                const String _(pseudo);
                return aka(r,_);
            }


        private:
            Y_Disable_Copy_And_Assign(DataBase);
            friend class Singleton<DataBase,ClassLockPolicy>;
            inline explicit DataBase() :
            Singleton<DataBase,ClassLockPolicy>(),
            rtti(),
            rmap()
            {
                setup();
            }

            inline virtual ~DataBase() noexcept
            {
            }

            void setup();

            template <typename T> inline
            void record(const char * const id)
            {
                aka( get( typeid(T), sizeof(T) ), id );
            }



        public:
            RTTI_Set rtti;
            RTTI_Map rmap;

        };

        const char * const RTTI::DataBase::CallSign = "RTTI";

        RTTI & RTTI:: Get(const std::type_info &ti, const size_t len)
        {
            static DataBase &db = DataBase::Instance();
            Y_Lock(db.access);
            return db.get(ti,len);

        }

        RTTI & RTTI:: aka(const String &pseudo)
        {
            static DataBase &db = DataBase::Instance();
            Y_Lock(db.access);
            return db.aka(*this,pseudo);
        }

        RTTI & RTTI:: aka(const char * const pseudo)
        {
            const String _(pseudo);
            return aka(_);
        }

        bool RTTI:: called(const String & id) const noexcept
        {
            if(id == uuid) return true;
            for(const Alias *a=aliases.head;a;a=a->next)
            {
                if( id == *a ) return true;
            }
            return false;
        }

        std::ostream & operator<<(std::ostream &os, const RTTI &rtti)
        {
            os << rtti.uuid;
            if(rtti.aliases.size)
            {
                os << ' ' << '[';
                const RTTI::Alias * a = rtti.aliases.head;
                os << *a;
                for(a=a->next;a;a=a->next)
                    os << ',' << *a;
                os << ']';
            }
            os << " -> |" << rtti.name() << "| = " << rtti.bytes;
            return os;
        }

        void RTTI:: Display(std::ostream &os)
        {
            static const DataBase &db = DataBase::Instance();
            db.display(os,0);
            
        }
    }

}


#include "y/mkl/xreal.hpp"
#include "y/mkl/v3d.hpp"

namespace Yttrium
{
    namespace System
    {


#define Y_RTTI(TYPE) record<TYPE>( #TYPE )

        void RTTI:: DataBase :: setup()
        {
            Y_Lock(access);
            Y_RTTI(float);
            Y_RTTI(double);
            Y_RTTI(long double);

            Y_RTTI(uint8_t);
            Y_RTTI(uint16_t);
            Y_RTTI(uint32_t);
            Y_RTTI(uint64_t);

            Y_RTTI(int8_t);
            Y_RTTI(int16_t);
            Y_RTTI(int32_t);
            Y_RTTI(int64_t);

            Y_RTTI(unsigned char);
            Y_RTTI(unsigned short);
            Y_RTTI(unsigned int);
            Y_RTTI(unsigned long);
            Y_RTTI(unsigned long long);

            Y_RTTI(char);
            Y_RTTI(short);
            Y_RTTI(int);
            Y_RTTI(long);
            Y_RTTI(long long);

            Y_RTTI(size_t);
            Y_RTTI(ptrdiff_t);

            Y_RTTI(XReal<float>);
            Y_RTTI(XReal<double>);
            Y_RTTI(XReal<long double>);

            Y_RTTI(V2D<float>);
            Y_RTTI(V2D<double>);
            Y_RTTI(V3D<float>);
            Y_RTTI(V3D<double>);
        }
    }

}
