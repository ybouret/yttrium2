#include "y/format/hexadecimal.hpp"
#include <cstring>
#include <iostream>

namespace Yttrium
{
    const char Hexadecimal:: Header[2] = { '0' , 'x' };
    

    const char Hexadecimal:: LowerChar[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    const char Hexadecimal:: UpperChar[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    const char Hexadecimal:: LowerByte[256][4] =
    {
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
        "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
        "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
        "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
        "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
        "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
        "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
        "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
        "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
        "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
        "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
        "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
        "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
    };

    const char Hexadecimal:: UpperByte[256][4] =
    {
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F",
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1A", "1B", "1C", "1D", "1E", "1F",
        "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2A", "2B", "2C", "2D", "2E", "2F",
        "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3A", "3B", "3C", "3D", "3E", "3F",
        "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4A", "4B", "4C", "4D", "4E", "4F",
        "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5A", "5B", "5C", "5D", "5E", "5F",
        "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
        "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7A", "7B", "7C", "7D", "7E", "7F",
        "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8A", "8B", "8C", "8D", "8E", "8F",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9A", "9B", "9C", "9D", "9E", "9F",
        "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF",
        "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF",
        "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF",
        "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
        "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "EA", "EB", "EC", "ED", "EE", "EF",
        "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "FA", "FB", "FC", "FD", "FE", "FF"
    };


    void Hexadecimal:: clear() noexcept
    {
        memset(array,0,sizeof(array));
    }

    Hexadecimal:: Hexadecimal() noexcept :
    array()
    {
        prolog();
        array[sizeof(Header)] = '0';
    }

    Hexadecimal:: ~Hexadecimal() noexcept
    {
        clear();
    }

    Hexadecimal:: Hexadecimal(const Hexadecimal &other) noexcept :
    LegacyString(),
    array()
    {
        memcpy(array,other.array,sizeof(array));
    }

    const char * Hexadecimal:: c_str() const noexcept
    {
        return array;
    }

    void Hexadecimal:: prolog() noexcept
    {
        clear();
        memcpy(array,Header,sizeof(Header));
    }



    void Hexadecimal:: epilog(const Explanation explanation) noexcept
    {
        switch(explanation)
        {
            case Diffuse: return;
            case Concise: break;
        }
        char * const text  = array+sizeof(Header);
        size_t       size  = strlen(text);
        size_t       skip  = 0; //!< number of leading 0
        for(size_t i=0;i<size;++i)
        {
            if( '0' == text[i] ) { ++skip; continue; };
            break;
        }
        if(skip>0)
        {
            if(size==skip) --skip;
            if(skip>0)
            {
                //std::cerr << "Should skip " << skip << std::endl;
                memmove(text,text+skip,size-=skip);
                memset(text+size,0,skip);
            }
        }
    }

    void Hexadecimal:: format(const uint8_t &u) noexcept
    {
        memcpy(array+2,LowerByte[u],2);
    }

    void Hexadecimal:: format(const uint16_t &u) noexcept
    {
        memcpy(array+2,LowerByte[uint8_t(u>>8)],2);
        memcpy(array+4,LowerByte[uint8_t(u)   ],2);
    }

    void Hexadecimal:: format(const uint32_t &u) noexcept
    {
        memcpy(array+2,LowerByte[uint8_t(u>>24)], 2);
        memcpy(array+4,LowerByte[uint8_t(u>>16)], 2);
        memcpy(array+6,LowerByte[uint8_t(u>>8)],  2);
        memcpy(array+8,LowerByte[uint8_t(u)   ],  2);
    }

    void Hexadecimal:: format(const uint64_t &u) noexcept
    {
        memcpy(array+2, LowerByte[uint8_t(u>>56)], 2);
        memcpy(array+4, LowerByte[uint8_t(u>>48)], 2);
        memcpy(array+6, LowerByte[uint8_t(u>>40)], 2);
        memcpy(array+8, LowerByte[uint8_t(u>>32)], 2);
        memcpy(array+10,LowerByte[uint8_t(u>>24)], 2);
        memcpy(array+12,LowerByte[uint8_t(u>>16)], 2);
        memcpy(array+14,LowerByte[uint8_t(u>>8)],  2);
        memcpy(array+16,LowerByte[uint8_t(u)   ],  2);
    }

    int Hexadecimal:: ToDec(const char c) noexcept
    {

        switch(c)
        {
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;

            case 'a':
            case 'A': return 10;

            case 'b':
            case 'B': return 11;

            case 'c':
            case 'C': return 12;

            case 'd':
            case 'D': return 13;

            case 'e':
            case 'E': return 14;

            case 'f':
            case 'F': return 15;


            default:
                break;
        }
        return -1;
    }


}
