/*
 * smb2-handler - SMB2 file system client
 *
 * Copyright (C) 2022-2025 Fredrik Wikstrom <fredrik@a500.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (in the main directory of the smb2-handler
 * distribution in the file COPYING); if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SMB2FS_H
#define SMB2FS_H 1

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/filesysbox.h>

#define ID_SMB2_DISK (0x534D4202UL)

#ifdef __amigaos4__
struct Interface *open_interface(CONST_STRPTR name, int version);
void close_interface(struct Interface *interface);
#endif

char *request_password(const char *user, const char *server);
void request_error(const char *error_string, ...);
LONG request_reconnect(const char *server);

int smb2fs_main(struct DosPacket *pkt);

struct smb2_context;
int smb2_utimens(struct smb2_context *smb2, const char *path, const struct timespec tv[2]);

#ifdef __libnix__
size_t strlcpy(char *dst, const char *src, size_t size);
size_t strlcat(char *dst, const char *src, size_t size);
#endif

#endif /* SMB2FS_H */
