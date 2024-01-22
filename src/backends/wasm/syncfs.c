/*
 * Copyright (C) 2024 Gregory Maynard-Hoare
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Quake 2 WebAssembly browser database sync code
 *
 * =======================================================================
 */

#include "header/syncfs.h"

#include <emscripten.h>

void wasm_sync_fs(void)
{
	// Sync to IDBFS in the background
	EM_ASM(
		console.info("Saving data...");
		FS.syncfs(function (err) {
			if (err)
				console.warn("Failed to save data: " + err);
			else
				console.info("Data saved.");
		});
	);
}
