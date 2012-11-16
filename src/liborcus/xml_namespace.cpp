/*************************************************************************
 *
 * Copyright (c) 2012 Kohei Yoshida
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

#include "orcus/xml_namespace.hpp"
#include "orcus/exception.hpp"
#include "string_pool.hpp"

#include <boost/unordered_map.hpp>
#include <vector>
#include <limits>

namespace orcus {

typedef boost::unordered_map<pstring, size_t, pstring::hash> strid_map_type;

struct xmlns_repository_impl
{
    string_pool m_pool; /// storage of live string instances.
    std::vector<pstring> m_identifiers; /// map strings to numerical identifiers.
    strid_map_type m_strid_map;
};

xmlns_repository::xmlns_repository() : mp_impl(new xmlns_repository_impl) {}

xmlns_repository::~xmlns_repository()
{
    delete mp_impl;
}

xmlns_id_t xmlns_repository::intern(const pstring& uri)
{
    if (uri.empty())
        return XMLNS_UNKNOWN_ID;

    try
    {
        std::pair<pstring, bool> r = mp_impl->m_pool.intern(uri);
        pstring uri_interned = r.first;
        if (!uri_interned.empty())
        {
            // Intern successful.
            if (r.second)
            {
                // This is a new instance. Assign a numerical identifier.
                mp_impl->m_strid_map.insert(
                    strid_map_type::value_type(r.first, mp_impl->m_identifiers.size()));
                mp_impl->m_identifiers.push_back(r.first);

                assert(mp_impl->m_pool.size() == mp_impl->m_identifiers.size());
                assert(mp_impl->m_pool.size() == mp_impl->m_strid_map.size());
            }
            return uri_interned.get();
        }
    }
    catch (const general_error&)
    {
    }

    return XMLNS_UNKNOWN_ID;
}

xmlns_context xmlns_repository::create_context()
{
    return xmlns_context(*this);
}

size_t xmlns_repository::get_index(xmlns_id_t ns_id) const
{
    strid_map_type::const_iterator it = mp_impl->m_strid_map.find(ns_id);
    if (it == mp_impl->m_strid_map.end())
        return xmlns_context::index_not_found;

    return it->second;
}

typedef boost::unordered_map<pstring, pstring, pstring::hash> alias_map_type;

struct xmlns_context_impl
{
    xmlns_repository& m_repo;
    xmlns_id_t m_default;
    alias_map_type m_map;

    xmlns_context_impl(xmlns_repository& repo) : m_repo(repo), m_default(XMLNS_UNKNOWN_ID) {}
    xmlns_context_impl(const xmlns_context_impl& r) : m_repo(r.m_repo), m_default(r.m_default), m_map(r.m_map) {}
};

size_t xmlns_context::index_not_found = std::numeric_limits<size_t>::max();

xmlns_context::xmlns_context(xmlns_repository& repo) : mp_impl(new xmlns_context_impl(repo)) {}
xmlns_context::xmlns_context(const xmlns_context& r) : mp_impl(new xmlns_context_impl(*r.mp_impl)) {}

xmlns_context::~xmlns_context()
{
    delete mp_impl;
}

xmlns_id_t xmlns_context::set(const pstring& key, const pstring& uri)
{
    if (uri.empty())
        return XMLNS_UNKNOWN_ID;

    pstring uri_interned = mp_impl->m_repo.intern(uri);

    if (key.empty())
    {
        // empty key value is associated with default namespace.
        mp_impl->m_default = uri_interned.get();
        return mp_impl->m_default;
    }

    // Overwrite an existing value if one exists.
    std::pair<alias_map_type::iterator,bool> r =
        mp_impl->m_map.insert(alias_map_type::value_type(key, uri_interned));

    if (!r.second)
        // insertion failed.
        throw general_error("Failed to insert new namespace.");

    return r.first->second.get();
}

xmlns_id_t xmlns_context::get(const pstring& key) const
{
    if (key.empty())
        return mp_impl->m_default;

    alias_map_type::const_iterator it = mp_impl->m_map.find(key);
    if (it == mp_impl->m_map.end())
        return XMLNS_UNKNOWN_ID;

    return it->second.get();
}

size_t xmlns_context::get_index(xmlns_id_t ns_id) const
{
    return mp_impl->m_repo.get_index(ns_id);
}

void xmlns_context::get_keys(std::vector<pstring>& keys) const
{
    std::vector<pstring> _keys;
    alias_map_type::const_iterator it = mp_impl->m_map.begin(), it_end = mp_impl->m_map.end();
    for (; it != it_end; ++it)
        _keys.push_back(it->first);

    keys.swap(_keys);
}

}
