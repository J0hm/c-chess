#include "move.h"

#include "types.h"
#include "util.h"

move_t create_move(Square from, Square to, PieceType moved, PieceType captured,
                   uint8_t castling, uint8_t flags) {
    move_t move = {0};
    MOVE32_SET_SRC(move.move32, from);
    MOVE32_SET_DST(move.move32, to);
    MOVE32_SET_MOVED_PIECE_TYPE(move.move32, moved);
    MOVE32_SET_CAPTURED_PIECE_TYPE(move.move32, captured);
    MOVE32_SET_CASTLING_RIGHTS(move.move32, castling);
    MOVE32_SET_FLAGS(move.move32, flags);

    return move;
}

void print_move(move_t move) {
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

void to_lan(move_t move, char *buffer) {
    
}