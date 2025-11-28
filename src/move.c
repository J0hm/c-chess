#include "move.h"

#include "types.h"
#include "util.h"

move_t create_move(Square from, Square to, PieceType moved, PieceType captured,
                   uint8_t castling, uint8_t flags)
{
    move_t move = {0};
    MOVE32_SET_SRC(move.move32, from);
    MOVE32_SET_DST(move.move32, to);
    MOVE32_SET_MOVED_PIECE_TYPE(move.move32, moved);
    MOVE32_SET_CAPTURED_PIECE_TYPE(move.move32, captured);
    MOVE32_SET_CASTLING_RIGHTS(move.move32, castling);
    MOVE32_SET_FLAGS(move.move32, flags);

    return move;
}

void print_move(move_t move)
{
    printf(
        "%s %s -> %s (%s), castling 0x%x, flags 0x%x, "
        "rating %d\n",
        piece_type_to_string(MOVE32_PIECE_TYPE(move.move32)),
        square_to_string(MOVE32_SRC(move.move32)),
        square_to_string(MOVE32_DST(move.move32)),
        piece_type_to_string(MOVE32_CAPTURED_PIECE(move.move32)),
        MOVE32_CASTLING_RIGHTS(move.move32), MOVE32_FLAGS(move.move32),
        move.rating);
}

void to_lan(move_t move, char *buffer)
{
    uint32_t m = move.move32;

    int dest = m & 0x3F;
    int orig = (m >> 6) & 0x3F;
    int flags = (m >> 12) & 0xF;

    char orig_file = 'a' + (orig & 7);
    char orig_rank = '1' + (orig >> 3);
    char dest_file = 'a' + (dest & 7);
    char dest_rank = '1' + (dest >> 3);

    int pos = 0;

    buffer[pos++] = orig_file;
    buffer[pos++] = orig_rank;

    if (flags & 0x4)
    {
        buffer[pos++] = 'x';
    }

    buffer[pos++] = dest_file;
    buffer[pos++] = dest_rank;

    if (flags & 0x8)
    {
        buffer[pos++] = '=';
        int promo_type = flags & 0x3;
        switch (promo_type)
        {
        case 0:
            buffer[pos++] = 'N';
            break;
        case 1:
            buffer[pos++] = 'B';
            break;
        case 2:
            buffer[pos++] = 'R';
            break;
        case 3:
            buffer[pos++] = 'Q';
            break;
        }
    }

    buffer[pos] = '\0';
}