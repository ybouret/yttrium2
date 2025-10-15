//! \file
//!
#ifndef Y_FLTK_CURVE_INCLUDED
#define Y_FLTK_CURVE_INCLUDED 1

#include "y/string.hpp"
#include "y/mkl/v2d.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"
#include "y/counted.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/associative/hash/set.hpp"

#include <FL/fl_draw.H>

namespace Yttrium
{
    namespace FLTK 
    {
        
        typedef V2D<double>   Point;   //!< alias
        typedef Vector<Point> Points;  //!< alias

        //! named points+color
        class Curve : public Object, public Counted, public Points
        {
        public:
            enum Style
            {
                WithLines,
                WithPoints
            };

            enum PointShape
            {
                Circle,
                Square
            };

            enum PointStyle
            {
                Filled,
                Border
            };

            explicit Curve(const String &id);
            explicit Curve(const char   *id);
            virtual ~Curve() throw();
            
            const String name;
            Fl_Color     color;
            Style        style;
            int          pointSize;
            PointShape   pointShape;
            PointStyle   pointStyle;

            const String &key() const throw();
            typedef Keyed<String,ArcPtr<Curve> >   Pointer;
            typedef HashSet<String,Curve::Pointer> Set;

            Point getMin() const;
            Point getMax() const;

        private:
            Y_Disable_Copy_And_Assign(Curve);
        };
        
        //! a set of named curves
        class Curves : public Curve::Set
        {
        public:
            explicit Curves() throw(); //!< setup
            virtual ~Curves() throw(); //!< desctructor
            
            Curve &       operator[]( const String &id );       //!< existing or create
            const Curve & operator[]( const String &id ) const; //!< must exist
            
            Curve &       operator[]( const char * );           //!< alias: get existing or create
            const Curve & operator[]( const char *) const;      //!< alias: must exist

            Point getMin() const;
            Point getMax() const;
        private:
            Y_Disable_Copy_And_Assign(Curves);
        };
        
    }
}

#endif // !Y_FLTK_CURVE_INCLUDED
