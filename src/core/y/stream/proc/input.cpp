

#include "y/stream/proc/input.hpp"
#include "y/system/exception.hpp"
#include <cstdio>

namespace Yttrium
{
    InputProcess:: ~InputProcess() noexcept
    {
    }


    const char * const InputProcess:: How      = "r";
    const char * const InputProcess:: CallSign = "InputProcess";

    InputProcess:: InputProcess(const String &cmd) :
    ProcessStream(cmd.c_str(), How),
    buffer()
    {
    }


    InputProcess:: InputProcess(const char * const cmd) :
    ProcessStream(cmd,How),
    buffer()
    {
    }

    
    static inline bool forceQuery(void * const handle,
                                  char &       data)
    {
        FILE *fp = (FILE *)handle;
        if(feof(fp)) return false;
        const size_t nr = fread(&data, 1, 1, fp);
        if(nr<=0) 
        {
            if(feof(fp)) return false;
            throw Specific::Exception(InputProcess::CallSign, "fread failure");
        }
        return true;
    }

    bool InputProcess:: query(char &data)
    {
        assert(0!=handle);

        if(buffer->size>0)
        {
            data = char(buffer.pullHead());
            return true;
        }
        else
        {
            return forceQuery(handle,data);
        }

    }

    void InputProcess:: store(const char C)
    {
        buffer >> uint8_t(C);
    }

#if 0
    bool ProcInput:: ready()
    {
        if(buffer->size>0)
        {
            return true;
        }
        else
        {
            char data = 0;
            if(forceQuery(handle,data))
            {
                store(data);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
#endif

}
