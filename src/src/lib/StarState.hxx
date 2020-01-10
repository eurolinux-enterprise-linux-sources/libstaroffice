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

/*
 * StarPool to store the state
 *
 */
#ifndef STAR_STATE_HXX
#  define STAR_STATE_HXX

#include <vector>

#include "libstaroffice_internal.hxx"

#include "STOFFCellStyle.hxx"
#include "STOFFFont.hxx"
#include "STOFFFrameStyle.hxx"
#include "STOFFGraphicStyle.hxx"
#include "STOFFParagraph.hxx"
#include "STOFFPageSpan.hxx"
#include "STOFFSection.hxx"

class StarItemPool;
class StarObject;
class StarZone;
class StarObjectNumericRuler;
class STOFFList;

namespace SWFieldManagerInternal
{
struct Field;
}

/** \brief class to store an state: ie. the current page, section, ... style
 */
class StarState
{
public:
  //! small struct use to store global data
  struct GlobalState {
    //! constructor
    GlobalState(StarItemPool const *pool, StarObject &object, double relUnit=0.05) :
      m_pool(pool), m_object(object), m_numericRuler(),
      m_page(), m_pageName(""), m_pageNameList(), m_pageZone(STOFFPageSpan::Page), m_pageOccurence("all"),
      m_list(), m_listLevel(-1),
      m_relativeUnit(relUnit)
    {
    }
    //! destructor
    ~GlobalState();
    /** the pool */
    StarItemPool const *m_pool;
    /** the object */
    StarObject &m_object;
    /// the numeric ruler manager
    shared_ptr<StarObjectNumericRuler> m_numericRuler;
    /// the page
    STOFFPageSpan m_page;
    /// the page name
    librevenge::RVNGString m_pageName;
    /// the list of page name
    std::vector<librevenge::RVNGString> m_pageNameList;
    /// the actual page zone: document, header, footer
    STOFFPageSpan::ZoneType m_pageZone;
    /// the page occurence: all, first, left, right
    std::string m_pageOccurence;
    /// the current list
    shared_ptr<STOFFList> m_list;
    /// the current list level
    int m_listLevel;
    /** the relative unit uses to transform rel font height in point, default 1/20 */
    double m_relativeUnit;

  private:
    GlobalState(GlobalState const &);
    GlobalState &operator=(GlobalState const &);
  };
  //! constructor
  StarState(StarItemPool const *pool, StarObject &object, double relUnit=0.05)
    : m_global(new GlobalState(pool, object, relUnit))
    , m_styleName("")
    , m_break(0)
    , m_cell()
    , m_frame()
    , m_graphic()
    , m_paragraph()
    , m_font(), m_content(false), m_footnote(false), m_link(""), m_refMark(""), m_field()
  {
  }
  //! constructor
  explicit StarState(shared_ptr<GlobalState> global) :
    m_global(global),
    m_styleName(""),
    m_break(0),
    m_cell(),
    m_frame(),
    m_graphic(),
    m_paragraph(),
    m_font(), m_content(false), m_footnote(false), m_link(""), m_refMark(""), m_field()
  {
  }
  //! copy constructor
  explicit StarState(StarState const &orig);
  //! destructor
  ~StarState();
  //! reinit the local data: break, font, content, footnote, ...
  void reinitializeLineData();
  //! global state
  shared_ptr<GlobalState> m_global;
  /// the style name
  librevenge::RVNGString m_styleName;

  //! a page/column break: 1=columnBefore, 2=columnAfter, 3=columnBoth, 4=pageBefore, 5=pageAfter,n 6=pageBoth
  int m_break;

  /// the cell style
  STOFFCellStyle m_cell;
  /// the frame style
  STOFFFrameStyle m_frame;
  /// the graphic style
  STOFFGraphicStyle m_graphic;

  /// the paragraph style
  STOFFParagraph m_paragraph;
  /// the font
  STOFFFont m_font;
  /// flag to know if this is a content zone
  bool m_content;
  /// flag to know if this is a footnote
  bool m_footnote;
  /** the link url */
  librevenge::RVNGString m_link;
  /// the ref mark
  librevenge::RVNGString m_refMark;
  /** the field */
  shared_ptr<SWFieldManagerInternal::Field> m_field;
private:
  StarState &operator=(StarState const &);
};
#endif
// vim: set filetype=cpp tabstop=2 shiftwidth=2 cindent autoindent smartindent noexpandtab:
