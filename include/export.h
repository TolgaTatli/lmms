/*
 * export.h - macros for export-declarations
 *
 * Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _EXPORT_H
#define _EXPORT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#ifdef BUILD_WIN32

#ifdef PLUGIN_NAME
#define EXPORT __declspec(dllimport)
#define PLUGIN_EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

#else

#define EXPORT
#define PLUGIN_EXPORT

#endif

#endif
