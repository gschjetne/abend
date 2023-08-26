/*  Copyright (C) 2023 Grim Schjetne
 *  Licensed under the GPLv3, see COPYING.md for details
 */

#ifndef GBUFFER_H_
#define GBUFFER_H_

#include <stdlib.h>

struct gbuffer {
    char *buffer;
    size_t gap_start;
    size_t gap_end;
    size_t buffer_length;
};

void gb_init(struct gbuffer *gb, size_t size);

void gb_destroy(struct gbuffer *gb);

size_t gb_byte_length(struct gbuffer *gb);

size_t gb_char_length(struct gbuffer *gb);

size_t gb_cursor_pos(struct gbuffer *gb);

void gb_to_string(struct gbuffer *gb, char *dest);

void gb_write(struct gbuffer *gb, char *src);

void gb_move_left(struct gbuffer *gb);

void gb_move_right(struct gbuffer *gb);

#endif
