/* -*- Mode: C++; c-default-style: "k&r"; indent-tabs-mode: nil; tab-width: 2; c-basic-offset: 2 -*- */

/* libstaroffice
* Version: MPL 2.0 / LGPLv2+
*
* The contents of this file are subject to the Mozilla Public License Version
* 2.0 (the "License"); you may not use this file except in compliance with
* the License or as specified alternatively below. You may obtain a copy of
* the License at http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* Major Contributor(s):
* Copyright (C) 2002 William Lachance (wrlach@gmail.com)
* Copyright (C) 2002,2004 Marc Maurer (uwog@uwog.net)
* Copyright (C) 2004-2006 Fridrich Strba (fridrich.strba@bluewin.ch)
* Copyright (C) 2006, 2007 Andrew Ziem
* Copyright (C) 2011, 2012 Alonso Laurent (alonso@loria.fr)
*
*
* All Rights Reserved.
*
* For minor contributions see the git repository.
*
* Alternatively, the contents of this file may be used under the terms of
* the GNU Lesser General Public License Version 2 or later (the "LGPLv2+"),
* in which case the provisions of the LGPLv2+ are applicable
* instead of those above.
*/

#include <sstream>

#include <librevenge/librevenge.h>

#include "libstaroffice_internal.hxx"

#include "STOFFFrameStyle.hxx"

// frame style function

std::ostream &operator<<(std::ostream &o, STOFFFrameStyle const &frameStyle)
{
  o << frameStyle.m_propertyList.getPropString().cstr() << ",";
  return o;
}

bool STOFFFrameStyle::operator==(STOFFFrameStyle const &frameStyle) const
{
  return m_propertyList.getPropString() == frameStyle.m_propertyList.getPropString() &&
         m_frameSize == frameStyle.m_frameSize;
}

void STOFFFrameStyle::addTo(librevenge::RVNGPropertyList &pList) const
{
  librevenge::RVNGPropertyList::Iter i(m_propertyList);
  for (i.rewind(); i.next();) {
    if (i.child()) {
      STOFF_DEBUG_MSG(("STOFFFrameStyle::addTo: find unexpected property child\n"));
      pList.insert(i.key(), *i.child());
      continue;
    }
    pList.insert(i.key(), i()->clone());
  }
}

// vim: set filetype=cpp tabstop=2 shiftwidth=2 cindent autoindent smartindent noexpandtab:
