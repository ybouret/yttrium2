
#include "y/ink/image/format/pnm.hpp"
#include "y/string/boolean.hpp"
#include "y/system/exception.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/ascii/convert.hpp"
#include "y/color/conv.hpp"

namespace Yttrium
{
    namespace Ink
    {
        namespace
        {
            typedef V2D<unsigned long> ZoomType;

            static inline
            void  EmitWxH(OutputStream& fp,
                          const Bitmap& bmp,
                          const ZoomType& zoom)
            {
                fp("%lu %lu\n", zoom.x * static_cast<unsigned long>(bmp.w), zoom.y * static_cast<unsigned long>(bmp.h));
            }

            // black/white
            static inline void ToPBM(OutputStream& fp,
                                     const RGBA& c)
            {
                if (c.r > 0 || c.g > 0 || c.b > 0) fp << '0'; else fp << '1';
            }

            //! gray scale
            static inline void ToPGM(OutputStream& fp,
                                     const RGBA& c)
            {
                // const uint8_t gs = 0;
                const uint8_t gs = Color::Conv::GrayScale<uint8_t>::From(c);
                fp("%3u", gs);
            }

            //! color
            static inline void ToPPM(OutputStream& fp,
                                     const RGBA& c)
            {
                fp("%3u %3u %3u", c.r, c.g, c.b);
            }


            template <typename PROC>
            static inline void WriteRGBA(OutputStream& fp,
                                         const Image& image,
                                         PROC& proc,
                                         const ZoomType& zoom)
            {
                for (size_t j = 0; j < image.h; ++j)
                {
                    const Image::Row& line = image(j);
                    for (size_t ny = zoom.y; ny > 0; --ny)
                    {
                        for (size_t i = 0; i < image.w; ++i)
                        {
                            const RGBA& c = line(i);
                            for (size_t nx = zoom.x; nx > 0; --nx)
                            {
                                proc(fp, c);
                                fp << '\n';
                            }
                        }
                    }

                }
            }

            static inline
            void WriteComments(OutputStream& fp, const Options* const options)
            {
                const String* const com = Options::Query(options, "comment");
                if (0 != com)
                {
                    fp << "# " << *com << '\n';
                }
            }

            static inline
            ZoomType GetZoom(const Options* options)
            {
                static const char name[] = "zoom";
                const String* zoom = Options::Query(options, name);
                if (!zoom)
                {
                    return ZoomType(1, 1);
                }

                Vector<String> args;
                Tokenizer::AppendTo(args, *zoom, ',');
                for (size_t i = args.size(); i > 0; --i) Algo::Crop(args[i], isspace);
                ZoomType res(1, 1);
                switch (args.size())
                {
                    case 1:
                        res.x = res.y = ASCII::Convert::To<unsigned long>(args[1], "zoom.x");
                        break;

                    case 2:
                        res.x = ASCII::Convert::To<unsigned long>(args[1], "zoom.x");
                        res.y = ASCII::Convert::To<unsigned long>(args[2], "zoom.y");
                        break;

                    default:
                        throw Specific::Exception(FormatPNM::CallSign, "invalid 'zoom=%s'", zoom->c_str());
                }
                if (res.x <= 0 || res.y <= 0) throw Specific::Exception(FormatPNM::CallSign, "invalid zoom=%lu,%lu", res.x, res.y);
                return res;
            }

            static inline
            void SaveP1(const Image& image,
                        const String& filename,
                        const Options* const options)
            {
                OutputFile fp(filename);
                fp << "P1\n";
                WriteComments(fp, options);
                const ZoomType zoom = GetZoom(options);
                EmitWxH(fp, image, zoom);
                WriteRGBA(fp, image, ToPBM, zoom);
            }


            static inline
            void SaveP2(const Image& image,
                        const String& filename,
                        const Options* const  options)
            {
                OutputFile fp(filename);
                fp << "P2\n";
                WriteComments(fp, options);
                const ZoomType zoom = GetZoom(options);
                EmitWxH(fp, image, zoom);
                fp << "255\n";
                WriteRGBA(fp, image, ToPGM, zoom);
            }

            static inline
            void SaveP3(const Image& image,
                        const String& filename,
                        const Options* const options)
            {
                OutputFile fp(filename);
                fp << "P3\n";
                WriteComments(fp, options);
                const ZoomType zoom = GetZoom(options);
                EmitWxH(fp, image, zoom);
                fp << "255\n";
                WriteRGBA(fp, image, ToPPM, zoom);
            }

            static   bool QueryBinary(const Options* const options)
            {
                static const char    name[] = "binary";
                const String* const args = Options::Query(options, "binary");
                if (0 == args) return false;
                return StringToBoolean::Get(*args, name);
            }

        }
#define Y_PNM_SAVE(FMT) case FMT: Save##FMT(image,fileName,options); break

        void  FormatPNM:: onSave(const Image& image,
                                 const String& fileName,
                                 const Options* options) const
        {
            const bool   binary = QueryBinary(options);
            const String ext = LowerCaseExt(fileName);
            const Kind   kind = GetKind(ext, binary);
            switch (kind)
            {
                    Y_PNM_SAVE(P1);
                    Y_PNM_SAVE(P2);
                    Y_PNM_SAVE(P3);
                case P4:
                case P5:
                case P6:
                    throw Specific::Exception(CallSign, "%s not implemented yet", ext.c_str());
            }
        }


    }

}


