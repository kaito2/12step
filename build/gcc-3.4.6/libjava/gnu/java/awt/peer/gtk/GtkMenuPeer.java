/* GtkMenuPeer.java -- Implements MenuPeer with GTK+
   Copyright (C) 1999 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


package gnu.java.awt.peer.gtk;

import java.awt.Component;
import java.awt.Menu;
import java.awt.MenuContainer;
import java.awt.MenuItem;
import java.awt.MenuShortcut;
import java.awt.peer.MenuPeer;
import java.awt.peer.MenuItemPeer;

public class GtkMenuPeer extends GtkMenuItemPeer
  implements MenuPeer
{
  native void create (String label);
  native void addItem (MenuItemPeer item, int key, boolean shiftModifier);
  native void setupAccelGroup (GtkGenericPeer container);

  public GtkMenuPeer (Menu menu)
  {
    super (menu);
    
    MenuContainer parent = menu.getParent ();
    if (parent instanceof Menu)
      setupAccelGroup ((GtkGenericPeer)((Menu)parent).getPeer ());
    else if (parent instanceof Component)
      setupAccelGroup ((GtkGenericPeer)((Component)parent).getPeer ());
    else
      setupAccelGroup (null);
  }

  public void addItem (MenuItem item)
  {
    int key = 0;
    boolean shiftModifier = false;

    MenuShortcut ms = item.getShortcut ();
    if (ms != null)
      {
	key = ms.getKey ();
	shiftModifier = ms.usesShiftModifier ();
      }

    addItem ((MenuItemPeer) item.getPeer (), key, shiftModifier);
  }

  public void addItem (MenuItemPeer item, MenuShortcut ms)
  {
    int key = 0;
    boolean shiftModifier = false;

    if (ms != null)
      {
	key = ms.getKey ();
	shiftModifier = ms.usesShiftModifier ();
      }

    addItem (item, key, shiftModifier);
  }

  public void addSeparator ()
  {
    addItem (new MenuItem ("-"));
  }

  native public void delItem (int index);
}
