/*  Copyright (C) 2023 Grim Schjetne
 *  Licensed under the GPLv3, see COPYING.md for details
 */

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "gbuffer.h"


Test(gbuffer, init_empty) {
    struct gbuffer gb;
    char *str;

    gb_init(&gb, 10);

    cr_expect_eq(gb_byte_length(&gb), 0, "nonzero byte length");

    cr_expect_eq(gb_char_length(&gb), 0, "nonzero char length");

    cr_expect_eq(gb_cursor_pos(&gb), 0, "cursor was not in the home position");

    str = malloc(gb_byte_length(&gb) + 1);

    gb_to_string(&gb, str);

    cr_expect_str_empty(str, "the string was not empty");

    gb_destroy(&gb);
    free(str);
}

Test(gbuffer, write_string) {
    struct gbuffer gb;
    char *str;

    gb_init(&gb, 10);

    gb_write(&gb, "hello");

    cr_expect_eq(gb_byte_length(&gb), 5, "buffer was not 5 bytes long");

    cr_expect_eq(gb_char_length(&gb), 5, "buffer was not 5 characters long");

    cr_expect_eq(gb_cursor_pos(&gb), 5, "cursor was not in the end position");

    str = malloc(gb_byte_length(&gb) + 1);

    gb_to_string(&gb, str);

    cr_expect_str_eq(str, "hello");

    gb_destroy(&gb);
    free(str);
}

Test(gbuffer, grow) {
    struct gbuffer gb;
    char *str;

    gb_init(&gb, 2);

    gb_write(&gb, "The quick brown fox jumps over the lazy dog");

    cr_expect_eq(gb_byte_length(&gb), 43, "buffer was not 43 bytes long");

    cr_expect_eq(gb_char_length(&gb), 43, "buffer was not 43 characters long");

    str = malloc(gb_byte_length(&gb) + 1);

    gb_to_string(&gb, str);

    cr_expect_str_eq(str, "The quick brown fox jumps over the lazy dog");

    gb_destroy(&gb);
    free(str);
}

Test(gbuffer, middle_insert) {
    struct gbuffer gb;
    char *str;

    gb_init(&gb, 16);

    gb_write(&gb, "The brown jumps");

    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);
    gb_move_left(&gb);

    cr_expect_eq(gb_cursor_pos(&gb), 4, "the cursor is not at col 4");

    gb_write(&gb, "quick ");

    str = malloc(gb_byte_length(&gb) + 1);

    gb_to_string(&gb, str);

    cr_expect_str_eq(str, "The quick brown jumps");

    gb_move_right(&gb);
    gb_move_right(&gb);
    gb_move_right(&gb);
    gb_move_right(&gb);
    gb_move_right(&gb);

    cr_expect_eq(gb_cursor_pos(&gb), 15, "the cursor is not at col 15");

    gb_write(&gb, " fox");

    free(str);
    str = malloc(gb_byte_length(&gb) + 1);

    gb_to_string(&gb, str);

    cr_expect_str_eq(str, "The quick brown fox jumps");

    gb_destroy(&gb);
    free(str);
}
