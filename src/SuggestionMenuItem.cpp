// This file is part of DSpellCheck Plug-in for Notepad++
// Copyright (C)2018 Sergey Semushin <Predelnik@gmail.com>
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "SuggestionMenuItem.h"
#include "MainDef.h"

SuggestionsMenuItem::SuggestionsMenuItem(const wchar_t *text_arg, int id_arg,
                                         bool separator_arg /*= false*/) {
  text = text_arg;
  id = static_cast<BYTE>(id_arg);
  separator = separator_arg;
}

void insert_sugg_menu_item(HMENU menu, const wchar_t *text, BYTE id,
                           int insert_pos, bool separator) {
  MENUITEMINFO mi;
  memset(&mi, 0, sizeof(mi));
  mi.cbSize = sizeof(MENUITEMINFO);
  if (separator) {
    mi.fType = MFT_SEPARATOR;
  } else {
    mi.fType = MFT_STRING;
    mi.fMask = MIIM_ID | MIIM_TYPE;
    if (!get_use_allocated_ids())
      mi.wID = MAKEWORD(id, DSPELLCHECK_MENU_ID);
    else
      mi.wID = get_context_menu_id_start() + id;

    mi.dwTypeData = const_cast<wchar_t *>(text);
    mi.cch = static_cast<int>(wcslen(text)) + 1;
  }
  if (insert_pos == -1)
    InsertMenuItem(menu, GetMenuItemCount(menu), 1, &mi);
  else
    InsertMenuItem(menu, insert_pos, 1, &mi);
}