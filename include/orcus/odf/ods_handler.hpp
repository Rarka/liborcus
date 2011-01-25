/*************************************************************************
 *
 * Copyright (c) 2010, 2011 Kohei Yoshida
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

#ifndef __ORCUS_ODSHANDLER_HPP__
#define __ORCUS_ODSHANDLER_HPP__

#include "orcus/xml_handler.hpp"
#include "orcus/xml_context.hpp"

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

namespace orcus {

class tokens;
class ods_content_xml_context;

namespace model {

class factory_base;

}

/**
 * Handler for parsing the content.xml part.
 */
class ods_content_xml_handler : public xml_stream_handler
{
public:
    ods_content_xml_handler(const tokens& tokens, model::factory_base* factory);
    virtual ~ods_content_xml_handler();

    virtual void start_document();
    virtual void end_document();
    virtual void start_element(xmlns_token_t ns, xml_token_t name, const xml_attrs_t& attrs);
    virtual void end_element(xmlns_token_t ns, xml_token_t name);
    virtual void characters(const pstring& str);

private:
    xml_context_base& get_current_context();

private:
    model::factory_base* mp_factory;
    typedef ::boost::ptr_vector<xml_context_base> context_stack_type;
    context_stack_type m_context_stack;
};

}

#endif