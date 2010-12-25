/*************************************************************************
 *
 * Copyright (c) 2010 Kohei Yoshida
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

#include "ooxml/schemas.hpp"

namespace orcus {

schema_t SCH_opc_content_types        = "http://schemas.openxmlformats.org/package/2006/content-types";
schema_t SCH_opc_relationships        = "http://schemas.openxmlformats.org/package/2006/relationships";
schema_t SCH_rels_extended_props      = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties";
schema_t SCH_rels_metadata_core_props = "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties";
schema_t SCH_rels_office_doc          = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument";

namespace {

schema_t schs[] = {
    SCH_opc_content_types,
    SCH_opc_relationships,
    SCH_rels_extended_props,
    SCH_rels_metadata_core_props,
    SCH_rels_office_doc,
    NULL
};

}

schema_t* SCH_all = schs;

}