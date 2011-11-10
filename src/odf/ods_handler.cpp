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

#include "orcus/odf/ods_handler.hpp"
#include "orcus/odf/ods_context.hpp"
#include "orcus/global.hpp"

#include <iostream>

using namespace std;

namespace orcus {

ods_content_xml_handler::ods_content_xml_handler(const tokens& tokens, model::iface::factory* factory) :
    mp_factory(factory)
{
    m_context_stack.push_back(new ods_content_xml_context(tokens, factory));
}

ods_content_xml_handler::~ods_content_xml_handler()
{
}

void ods_content_xml_handler::start_document()
{
}

void ods_content_xml_handler::end_document()
{
}

void ods_content_xml_handler::start_element(
    xmlns_token_t ns, xml_token_t name, const xml_attrs_t& attrs)
{
    xml_context_base& cur = get_current_context();
    if (!cur.can_handle_element(ns, name))
        m_context_stack.push_back(cur.create_child_context(ns, name));

    get_current_context().start_element(ns, name, attrs);
}

void ods_content_xml_handler::end_element(xmlns_token_t ns, xml_token_t name)
{
    bool ended = get_current_context().end_element(ns, name);

    if (ended)
    {
        if (m_context_stack.size() > 1)
        {
            // Call end_child_context of the parent context to provide a way for
            // the two adjacent contexts to communicate with each other.
            context_stack_type::reverse_iterator itr_cur = m_context_stack.rbegin();
            context_stack_type::reverse_iterator itr_par = itr_cur + 1;
            itr_par->end_child_context(ns, name, &(*itr_cur));
        }
        m_context_stack.pop_back();
    }
}

void ods_content_xml_handler::characters(const pstring& str)
{
    get_current_context().characters(str);
}

xml_context_base& ods_content_xml_handler::get_current_context()
{
    if (m_context_stack.empty())
        throw general_error("context stack is empty");

    return m_context_stack.back();
}

}
