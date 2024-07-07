/*  Copyright (C) 2023 Grim Schjetne
 *  Licensed under the GPLv3, see COPYING.md for details
 */

#include "gbuffer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gb_grow(struct gbuffer *gb);

void gb_init(struct gbuffer *gb, size_t size) {
    gb->buffer = malloc(size);
    if (gb->buffer == NULL) {
        perror("gb_init");
        exit(EXIT_FAILURE);
    }

    gb->gap_start = 0;
    gb->gap_end = size;
    gb->buffer_length = size;
}

void gb_destroy(struct gbuffer *gb) {
    free(gb->buffer);
    gb->buffer = NULL;
}

size_t gb_byte_length(struct gbuffer *gb) {
    return gb->gap_start + gb->buffer_length - gb->gap_end;
}

size_t gb_char_length(struct gbuffer *gb) {
    // TODO: add support for Unicode
    return gb_byte_length(gb);
}

size_t gb_cursor_pos(struct gbuffer *gb) { return gb->gap_start; }

void gb_to_string(struct gbuffer *gb, char *dest) {
    size_t prefix_length = gb->gap_start;
    size_t suffix_length = gb->buffer_length - gb->gap_end;

    memcpy(dest, gb->buffer, prefix_length);
    memcpy(dest + prefix_length, gb->buffer + gb->gap_end, suffix_length);

    dest[prefix_length + suffix_length] = '\0';
}

void gb_write(struct gbuffer *gb, char *src) {
    while (*src) {
        if (gb->gap_end - gb->gap_start == 0) {
            gb_grow(gb);
        }

        gb->buffer[gb->gap_start] = *src;
        gb->gap_start++;
        src++;
    }
}

void gb_move_left(struct gbuffer *gb) {
    // TODO: add support for Unicode
    if (gb->gap_start > 0) {
        gb->gap_start--;
        gb->gap_end--;
        gb->buffer[gb->gap_end] = gb->buffer[gb->gap_start];
    }
}

void gb_move_right(struct gbuffer *gb) {
    // TODO: add support for Unicode
    if (gb->gap_end < gb->buffer_length) {
        gb->buffer[gb->gap_start] = gb->buffer[gb->gap_end];
        gb->gap_end++;
        gb->gap_start++;
    }
}

void gb_delete_left(struct gbuffer *gb) {
    if (gb->gap_start > 0) {
        gb->gap_start--;
    }
}

void gb_delete_right(struct gbuffer *gb) {
    if (gb->gap_end < gb->buffer_length) {
        gb->gap_end++;
    }
}

void gb_grow(struct gbuffer *gb) {
    size_t new_length = gb->buffer_length * 2;
    size_t suffix_length = gb->buffer_length - gb->gap_end;
    size_t new_gap_end = new_length - suffix_length;

    gb->buffer = realloc(gb->buffer, new_length);
    if (gb->buffer == NULL) {
        perror("gb_grow");
        exit(EXIT_FAILURE);
    }

    memcpy(gb->buffer + new_gap_end, gb->buffer + gb->gap_end, suffix_length);

    gb->buffer_length = new_length;
    gb->gap_end = new_gap_end;
}
