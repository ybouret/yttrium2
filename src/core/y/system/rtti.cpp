
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


        RTTI:: RTTI( const std::type_info &ti ) :
        CountedObject(),
        uuid( ti.name() ),
        aliases()
        {
        }

        const String & RTTI:: key() const noexcept { return uuid; }

        const String & RTTI:: name() const noexcept
        {
            return aliases.size ? *aliases.head : uuid;
        }


    }

}

#include "y/singleton.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace System
    {

        class RTTI:: DataBase : public Singleton<DataBase,ClassLockPolicy>
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime = 100;

            inline virtual void display(std::ostream &os,
                                        size_t        depth) const
            {
                init(os,depth);

                quit(os,depth);
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

        public:
            SuffixSet<String,RTTI::Pointer> rtti;
            HashMap<String,RTTI::Pointer>   rmap;

        };

        const char * const RTTI::DataBase::CallSign = "RTTI";

        RTTI & RTTI:: Get(const std::type_info &ti)
        {
            static DataBase &db = DataBase::Instance();
            Y_Lock(db.access);

            const String     id( ti.name() );

            // check existence
            if(RTTI::Pointer *pp = db.rtti.search(id) )
            {
                assert(db.rmap.search(id));
                return **pp;
            }

            assert(!db.rmap.search(id));

            // creation
            RTTI::Pointer p = new RTTI( ti );
            if(!db.rtti.insert(p)) throw Specific::Exception(DataBase::CallSign,"could not insert '%s'", id.c_str());

            // reverse lookup
            try
            {
                if(!db.rmap.insert(id,p)) throw Specific::Exception(DataBase::CallSign,"could not map <%s>",id.c_str());
            }
            catch(...)
            {
                db.rtti.remove(id);
                assert(!db.rmap.search(id));
                assert(!db.rtti.search(id));
                throw;
            }

            return *p;
        }

        RTTI & RTTI:: aka(const String &pseudo)
        {
            static DataBase &db = DataBase::Instance();
            Y_Lock(db.access);

            RTTI::Pointer * const self = db.rtti.search(uuid);
            if(!self) throw Specific::Exception(DataBase::CallSign,"<%s> was not recorded", uuid.c_str());

            {
                const RTTI::Pointer * const p = db.rmap.search(pseudo);
                if( p ) throw Specific::Exception(DataBase::CallSign,"<%s> already exist for <%s>", pseudo.c_str(), (**p).name().c_str() );
            }

            Coerce(aliases).pushHead( new Alias(pseudo) );
            try
            {
                if( !db.rmap.insert(pseudo,*self))
                    throw Specific::Exception(DataBase::CallSign,"could not map <%s>", pseudo.c_str());
            }
            catch(...)
            {
                delete Coerce(aliases).popHead();
                throw;
            }

            return *this;
        }

        RTTI & RTTI:: aka(const char * const pseudo)
        {
            const String _(pseudo);
            return aka(_);
        }


    }

}




namespace Yttrium
{
    namespace System
    {
        void RTTI:: DataBase :: setup()
        {

        }
    }

}
