/*
 * smb2-handler - SMB2 file system client
 *
 * Copyright (C) 2022-2023 Fredrik Wikstrom <fredrik@a500.org>
 * Copyright (C) 2024 Walter Licht https://github.com/sirwalt
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

#define GROWSIZE 1024
#define INCARNATION_BITS 10
#define INDEX_BITS 22
#define MAX_INDEX ((1 << INDEX_BITS) - 1)

#include <stdlib.h>

struct FreeIndexNode {
    size_t index;
    struct FreeIndexNode* next;
};

struct PointerHandleRegistry{
    void** pointers;    // Array of pointers
    size_t size;        // Size of the array
    size_t capacity;    // Max. capacity of the array 
    uint32_t incarnation;   // Incarnation of the registry
    struct FreeIndexNode* freeHead; // Head of list of free indicies
};


// Prototypes
uint32_t AllocateHandleForPointer(struct PointerHandleRegistry* registry, void* ptr);
void* HandleToPointer(struct PointerHandleRegistry* registry, uint32_t handle);
void RemoveHandle(struct PointerHandleRegistry* registry, uint32_t handle);
struct PointerHandleRegistry* AllocateNewRegistry(uint32_t incarnation);
void FreeRegistry(struct PointerHandleRegistry* registry);

