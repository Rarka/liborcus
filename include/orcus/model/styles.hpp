/*************************************************************************
 *
 * Copyright (c) 2011 Kohei Yoshida
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************/

#ifndef __ORCUS_MODEL_STYLES_HPP__
#define __ORCUS_MODEL_STYLES_HPP__

#include "orcus/model/interface.hpp"
#include "orcus/pstring.hpp"

#include <vector>

namespace orcus { namespace model {

class styles : public styles_base
{
public:
    struct font
    {
        pstring name;
        double size;
        bool bold:1;
        bool italic:1;

        font();
        void reset();
    };

    struct fill
    {
        pstring pattern_type;

        fill();
        void reset();
    };

    struct border_attrs
    {
        pstring style;

        border_attrs();
        void reset();
    };

    struct border
    {
        border_attrs top;
        border_attrs bottom;
        border_attrs left;
        border_attrs right;
        border_attrs diagonal;

        border();
        void reset();
    };

    styles();
    virtual ~styles();

    virtual void set_font_count(size_t n);
    virtual void set_font_bold(bool b);
    virtual void set_font_italic(bool b);
    virtual void set_font_name(const char* s, size_t n);
    virtual void set_font_size(double point);
    virtual void commit_font();

    virtual void set_fill_count(size_t n);
    virtual void set_fill_pattern_type(const char* s, size_t n);
    virtual void commit_fill();

    virtual void set_border_count(size_t n);
    virtual void set_border_style(border_direction_t dir, const char* s, size_t n);
    virtual void commit_border();

    virtual void set_cell_style_xf_count(size_t n);
    virtual void set_cell_style_xf_number_format(size_t index);
    virtual void set_cell_style_xf_font(size_t index);
    virtual void set_cell_style_xf_fill(size_t index);
    virtual void set_cell_style_xf_border(size_t index);
    virtual void commit_cell_style_xf();

    virtual void set_cell_xf_count(size_t n);
    virtual void set_cell_xf_number_format(size_t index);
    virtual void set_cell_xf_font(size_t index);
    virtual void set_cell_xf_fill(size_t index);
    virtual void set_cell_xf_border(size_t index);
    virtual void set_cell_xf_style_xf(size_t index);
    virtual void commit_cell_xf();

    const font* get_font(size_t index) const;

private:
    font m_cur_font;
    fill m_cur_fill;
    border m_cur_border;
    ::std::vector<font> m_fonts;
    ::std::vector<fill> m_fills;
    ::std::vector<border> m_borders;
};

}}

#endif
