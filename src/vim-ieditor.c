/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * anjuta-gvim
 * Copyright (C) Arun Tejasvi Chaganty 2008 <arunchaganty@gmail.com>
 * 
 * anjuta-gvim is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * anjuta-gvim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with anjuta-gvim.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 *
 *
 * 	Implementation of the IAnjutaFile Interface
 */



#include <libanjuta/interfaces/ianjuta-editor.h>
#include "vim-editor.h"
#include "vim-dbus.h"



static gint
ieditor_get_tabsize (IAnjutaEditor *editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* reply = NULL;
	gint result;

	g_assert (e == NULL);
	reply = vim_dbus_query (vim, "&tabstop", e);
	
	// TODO: Error Handling...

	if (reply)
	{
		result = (gint)g_ascii_strtod (reply, NULL);
		g_free (reply);
		return result;	
	}
	else
	{
		return 0;
	}

}

static void
ieditor_set_tabsize (IAnjutaEditor *editor, gint tabsize, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* query = NULL;

	g_assert (e == NULL);
	// Create query string
	query = g_strnfill (20, '\0');
	g_strdup_printf (":set tabstop=%s", tabsize);

	vim_dbus_exec_without_reply (vim, query, e);
	
	// TODO: Error Handling...

	g_free (query);
}

static gboolean
ieditor_get_use_spaces (IAnjutaEditor *editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* reply = NULL;
	gint result;

	g_assert (e == NULL);
	reply = vim_dbus_query (vim, "&expandtab", e);
	
	// TODO: Error Handling...
	if (reply)
	{
		result = (gboolean)g_ascii_strtod (reply, NULL);
		g_free (reply);
		return result;	
	}

	return TRUE;
}

static void
ieditor_set_use_spaces (IAnjutaEditor *editor, gboolean use_spaces, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* query = NULL;

	g_assert (e == NULL);
	// Create query string
	if (use_spaces)
		g_strdup_printf (":set expandtab");
	else
		g_strdup_printf (":set noexpandtab");


	vim_dbus_exec_without_reply (vim, query, e);
	
	// TODO: Error Handling...

	g_free (query);
}

static void
ieditor_set_auto_indent (IAnjutaEditor *editor, gboolean auto_indent, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* query = NULL;

	g_assert (e == NULL);
	// Create query string
	if (auto_indent)
		g_strdup_printf (":set autoindent");
	else
		g_strdup_printf (":set noautoindent");


	vim_dbus_exec_without_reply (vim, query, e);
	
	// TODO: Error Handling...

	g_free (query);
}


/* Scroll to line */
static void 
ieditor_goto_line(IAnjutaEditor *editor, gint line, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* query = NULL;

	g_assert (e == NULL);
	// Create query string
	query = g_strdup_printf (":%d ", line);

	vim_dbus_exec_without_reply (vim, query, e);
	
	// TODO: Error Handling...

	g_free (query);

}

/* Scroll to position */
static void 
ieditor_goto_position(IAnjutaEditor *editor, IAnjutaIterable* icell,
								  GError **e)
{
}

/* Return a newly allocated pointer containing the whole text */
static gchar* 
ieditor_get_text (IAnjutaEditor* editor, 
				IAnjutaIterable* start,
				IAnjutaIterable* end, GError **e)
{
	return NULL;
}

static gchar*
ieditor_get_text_all (IAnjutaEditor* editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* reply = NULL;

	g_assert (e == NULL);
	reply = vim_dbus_get_buf_full (vim, e);
	
	// TODO: Error Handling...

	return reply;	
}

/* Get cursor position */
static IAnjutaIterable*
ieditor_get_position (IAnjutaEditor* editor, GError **e)
{
	return IANJUTA_ITERABLE (NULL);
}

static gint
ieditor_get_offset (IAnjutaEditor* editor, GError **e)
{
	return 0;
}

/* Return line of cursor */
static gint
ieditor_get_lineno(IAnjutaEditor *editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* reply = NULL;
	gint result;

	g_assert (e == NULL);
	reply = vim_dbus_query (vim, "line ('.')", e);
	
	// TODO: Error Handling...

	if (reply)
	{
		result = (gint)g_ascii_strtod (reply, NULL);
		g_free (reply);
		return result;	
	}

	return 0;
}

/* Return the length of the text in the buffer */
static gint 
ieditor_get_length(IAnjutaEditor *editor, GError **e)
{
	return 0;
}

/* Return word on cursor position */
static gchar*
ieditor_get_current_word(IAnjutaEditor *editor, GError **e)
{
	return NULL;
}

/* Insert text at position */
static void 
ieditor_insert(IAnjutaEditor *editor, IAnjutaIterable* icell,
							   const gchar* text, gint length, GError **e)
{
}

/* Append text to buffer */
static void 
ieditor_append(IAnjutaEditor *editor, const gchar* text,
							   gint length, GError **e)
{
}

static void 
ieditor_erase(IAnjutaEditor* editor, IAnjutaIterable* istart_cell, 
						  IAnjutaIterable* iend_cell, GError **e)
{
}

static void 
ieditor_erase_all(IAnjutaEditor *editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;

	g_assert (e == NULL);

	vim_dbus_exec_without_reply (vim, ":\%del", e);
	
	// TODO: Error Handling...
	
}

/* Return column of cursor */
static gint 
ieditor_get_column(IAnjutaEditor *editor, GError **e)
{
	VimEditor *vim = (VimEditor*) editor;
	gchar* reply = NULL;
	gint result;

	g_assert (e == NULL);
	reply = vim_dbus_query (vim, "col ('.')", e);
	
	// TODO: Error Handling...

	if (reply)
	{
		result = (int)g_ascii_strtod (reply, NULL);
		g_free (reply);
		return result;	
	}
}

/* Return TRUE if editor is in overwrite mode */
static gboolean 
ieditor_get_overwrite(IAnjutaEditor *editor, GError **e)
{
	return FALSE;
}


/* Set the editor popup menu */
static void 
ieditor_set_popup_menu(IAnjutaEditor *editor, 
								   GtkWidget* menu, GError **e)
{
}

/* Convert from position to line */
static gint 
ieditor_get_line_from_position(IAnjutaEditor *editor, 
										   IAnjutaIterable* icell, GError **e)
{
	return 0;
}

static IAnjutaIterable* 
ieditor_get_line_begin_position(IAnjutaEditor *editor,
											gint line, GError **e)
{
	return NULL;
}

static IAnjutaIterable*
ieditor_get_line_end_position(IAnjutaEditor *editor,
											gint line, GError **e)
{
	return NULL;
}

static IAnjutaIterable*
ieditor_get_position_from_offset(IAnjutaEditor* edit, gint position, GError** e)
{
	return NULL;
}

static IAnjutaIterable*
ieditor_get_start_position (IAnjutaEditor* edit, GError** e)
{
	return NULL;
}

static IAnjutaIterable*
ieditor_get_end_position (IAnjutaEditor* edit, GError** e)
{
	return NULL;
}

static void
ieditor_goto_start (IAnjutaEditor* editor, GError** e)
{
	VimEditor *vim = (VimEditor*) editor;

	g_assert (e == NULL);

	vim_dbus_exec_without_reply (vim, ":goto 1", e);
	
	// TODO: Error Handling...
	
}

static void
ieditor_goto_end (IAnjutaEditor* editor, GError** e)
{
	VimEditor *vim = (VimEditor*) editor;

	g_assert (e == NULL);

	vim_dbus_exec_without_reply (vim, ":%", e);
	
	// TODO: Error Handling...
	
}

void 
ieditor_iface_init (IAnjutaEditorIface *iface)
{
	iface->get_tabsize = ieditor_get_tabsize;
	iface->set_tabsize = ieditor_set_tabsize;
	iface->get_use_spaces = ieditor_get_use_spaces;
	iface->set_use_spaces = ieditor_set_use_spaces;
	iface->set_auto_indent = ieditor_set_auto_indent;
	iface->goto_line = ieditor_goto_line;
	iface->goto_position = ieditor_goto_position;
	iface->get_text = ieditor_get_text;
	iface->get_text_all = ieditor_get_text_all;
	iface->get_position = ieditor_get_position;
	iface->get_offset = ieditor_get_offset;
	iface->get_lineno = ieditor_get_lineno;
	iface->get_length = ieditor_get_length;
	iface->get_current_word = ieditor_get_current_word;
	iface->insert = ieditor_insert;
	iface->append = ieditor_append;
	iface->erase = ieditor_erase;
	iface->erase_all = ieditor_erase_all;
	iface->get_column = ieditor_get_column;
	iface->get_overwrite = ieditor_get_overwrite;
	iface->set_popup_menu = ieditor_set_popup_menu;
	iface->get_line_from_position = ieditor_get_line_from_position;
	iface->get_line_begin_position = ieditor_get_line_begin_position;
	iface->get_line_end_position = ieditor_get_line_end_position;
	iface->goto_start = ieditor_goto_start;
	iface->goto_end = ieditor_goto_end;
	iface->get_position_from_offset = ieditor_get_position_from_offset;
	iface->get_start_position = ieditor_get_start_position;
	iface->get_end_position = ieditor_get_end_position;
}

