
#include "y/apex/block/model.hpp"
#include "y/type/destroy.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Apex
    {


        


        const ViewType Model:: SmallView[Ops] =
        {
            View8,  View8,  View8,
            View16, View16,
            View32
        };

        Model:: Model(const size_t   userBytes,
                      const ViewType userView) :
        Object(),
        Blocks(userBytes),
        view(userView),
        bytes(block<uint8_t>().size),
        space(block<uint8_t>().maxi),
        bits(0)
        {

        }




        template <typename T> static inline
        void ModelCopy(Model &       target,
                       const Model & source,
                       BlockAPI *  const  sync[]) noexcept
        {
            assert(0==target.bits);

            Block<T>       &to   = target.get<T>(); assert(0==to.size); assert( to.isValid() );
            const Block<T> &from = source.get<T>(); assert( from.isValid() );
            const size_t    size = from.size;       assert(size<=to.maxi);
            memcpy(to.data,from.data, (to.size=size) * sizeof(T) );
            assert(to.isValid());
            
            const size_t numBits = ( Coerce(source.bits) = target.bits );
            sync[0]->resize(numBits);  
            sync[1]->resize(numBits);
            sync[2]->resize(numBits);
        }



        void Model:: cpy(const Model &other) noexcept
        {
            assert(this!=&other);
            assert(block<uint8_t>().maxi>=other.bytes);

            switch(ldz(other.view).view)
            {
                case View8:  ModelCopy<uint8_t> (*this,other,sync[0]); break;
                case View16: ModelCopy<uint16_t>(*this,other,sync[1]); break;
                case View32: ModelCopy<uint32_t>(*this,other,sync[2]); break;
                case View64: ModelCopy<uint64_t>(*this,other,sync[3]); break;
            }

            assert(view == other.view);
            switch(view)
            {
                case View8:  assert( block<uint8_t>().isValid()  ); break;
                case View16: assert( block<uint16_t>().isValid() ); break;
                case View32: assert( block<uint32_t>().isValid() ); break;
                case View64: assert( block<uint64_t>().isValid() ); break;
            }

        }

        Model:: Model(const Model &  userModel,
                      const ViewType userView) :
        Object(),
        Blocks( userModel ),
        view(   userModel.view ),
        bytes(block<uint8_t>().size),
        space(block<uint8_t>().maxi),
        bits(userModel.bits)
        {
            // transmogrify
            update();
            set(userView);
        }

        Model:: Model(const CopyOf_ &, const natural_t n) :
        Object(),
        Blocks( sizeof(n) ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        space(block<uint8_t>().maxi),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = 1;
            b64.data[0] = n;
            update();
        }



        Model:: Model(const natural_t * const arr, const size_t num) :
        Object(),
        Blocks( sizeof(natural_t) * num ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        space(block<uint8_t>().maxi),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = num;
            memcpy(b64.data,arr,num*sizeof(uint64_t));
            update();
        }

        unsigned Model:: BytesPerUnit(const ViewType v) noexcept
        {
            static const unsigned one = 1;
            return one << unsigned(v);
        }

        namespace
        {
#if 0
            template <typename T> static inline
            void BlockCopy(T *                target,
                           const void * const source,
                           size_t             length) noexcept
            {
                assert(Good(target,length));
                assert(Good(source,length));
                const T * C = (const T *)source;
                while(length-- > 0)
                    *(target++) = *(C++);
            }
#endif

            template <typename T> static inline
            void BlockCopy(Block<T> &         block,
                           const void * const source,
                           const size_t       length) noexcept
            {
                assert(Good(source,length));
                assert(length<=block.maxi);
                memcpy(block.data,source,(block.size=length)*sizeof(T));
            }


        }


        Model:: Model(const void * const entry,
                      const size_t       count,
                      const ViewType     tview) :
        Object(),
        Blocks(  count * BytesPerUnit(tview)  ),
        view( tview ),
        bytes(block<uint8_t>().size),
        space(block<uint8_t>().maxi),
        bits(0)
        {
            assert( Good(entry,count) );
            switch(view)
            {
                case View8:  BlockCopy( block<uint8_t>(),  entry, count); break;
                case View16: BlockCopy( block<uint16_t>(), entry, count); break;
                case View32: BlockCopy( block<uint32_t>(), entry, count); break;
                case View64: BlockCopy( block<uint64_t>(), entry, count); break;
            }
            update();
        }

        

        Model:: ~Model() noexcept
        {
        }

        Model & Model:: set(const ViewType vtgt) noexcept
        {
            (*this.*ChangeTo[vtgt][view])();
            Coerce(view) = vtgt;
            return *this;
        }

        Model & Model:: ldz(const ViewType userView) noexcept
        {
            switch(view)
            {
                case View8:  block<uint8_t>().naught(sync[View8]);   break;
                case View16: block<uint16_t>().naught(sync[View16]); break;
                case View32: block<uint32_t>().naught(sync[View32]); break;
                case View64: block<uint64_t>().naught(sync[View64]); break;
            }
            Coerce(bits) = 0;
            Coerce(view) = userView;
            return *this;
        }

        Model & Model:: ld1(const ViewType userView) noexcept
        {
            switch(view)
            {
                case View8:  block<uint8_t>(). build1(sync[View8]);   break;
                case View16: block<uint16_t>().build1(sync[View16]); break;
                case View32: block<uint32_t>().build1(sync[View32]); break;
                case View64: block<uint64_t>().build1(sync[View64]); break;
            }
            Coerce(bits) = 1;
            Coerce(view) = userView;
            return *this;
        }





        const BlockAPI & Model:: api() const noexcept
        {
            switch(view)
            {
                case View8:  return block<uint8_t>();
                case View16: return block<uint16_t>();
                case View32: return block<uint32_t>();
                case View64:
                    break;
            }
            return block<uint64_t>();
        }





        void Model:: update() noexcept
        {
            Coerce(bits) =  (*this.*Updating[view])();
        }


#define Y_APM_(TARGET,SOURCE) & Model::To<uint##TARGET##_t,uint##SOURCE##_t>
#define Y_APM(TARGET) { Y_APM_(TARGET,8), Y_APM_(TARGET,16), Y_APM_(TARGET,32), Y_APM_(TARGET,64) }

        Model::Change const Model:: ChangeTo[Metrics::Views][Metrics::Views] =
        {
            Y_APM(8), Y_APM(16), Y_APM(32), Y_APM(64)
        };

        Model::Update const Model:: Updating[Metrics::Views] =
        {
            & Model::Go<uint8_t>, & Model::Go<uint16_t>, & Model::Go<uint32_t>, & Model::Go<uint64_t>
        };

        
        std::ostream & operator<<(std::ostream &os, const Model &self)
        {
            switch(self.view)
            {
                case View8:  os << self.block<uint8_t>();  break;
                case View16: os << self.block<uint16_t>(); break;
                case View32: os << self.block<uint32_t>(); break;
                case View64: os << self.block<uint64_t>(); break;
            }
            if(View8!=self.view)
                os << ":byte" << ASCII::Plural::s(self.bytes) << "=" << self.bytes;
            os     << ":bit"  << ASCII::Plural::s(self.bits)  << "=" << self.bits;
            return os;
        }






    }

}

 

#include "y/stream/output.hpp"


namespace Yttrium
{
    namespace Apex
    {

        size_t Model:: save(OutputStream &fp)
        {
            const Block<uint8_t> &b = make<uint8_t>();
            size_t res = fp.emitVBR(b.size);
            fp.frame(b.data,b.size);
            return res + b.size;
        }
    }

}


#include "y/stream/input.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Model * Model:: Load(InputStream &     fp,
                             const ViewType     userView,
                             const char * const name)
        {
            static const char fn[]   = "Apex::Model::Load";
            static const char fmt[]  = " for %s";
            const size_t    numBytes = fp.readVBR<size_t>(name,"bytes");
            AutoPtr<Model>  result   = new Model(numBytes,View8);

            {
                Block<uint8_t> &target   = result->block<uint8_t>();
                assert(target.maxi>=numBytes);
                for(size_t i=0;i<numBytes;++i)
                {
                    if( 1 != fp.readCBR<uint8_t>(target.data[i]) )
                    {
                        Specific::Exception excp(fn,
                                                 "missing byte %s+1/%s",
                                                 Decimal(i).c_str(),
                                                 Decimal(numBytes).c_str());
                        if(name) excp.add(fmt,name);
                        throw excp;
                    }
                }
                result->update();
                if(target.size!=numBytes)
                {
                    Specific::Exception excp(fn,"corrupted input");
                    if(name) excp.add(fmt,name);
                    throw excp;
                }
            }

            return & result.yield()->set(userView);
        }
    }

}
