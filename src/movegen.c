#include "movegen.h"

#include "constants.h"
#include "util.h"

static uint64_t knightAttacks[64];
static uint64_t kingAttacks[64];
static uint64_t pawnAttacks[2][64];  // [side][square]

static uint64_t bishopAttacks[64][1 << 9];
static uint64_t rookAttacks[64][1 << 12];

static uint8_t rookShifts[64] = {
    52, 53, 53, 53, 53, 53, 53, 52, 53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53, 53, 54, 54, 53, 53, 53, 53, 53};

static uint64_t rookMagics[64] = {
    0x0080001020400080, 0x0040001000200040, 0x0080081000200080,
    0x0080040800100080, 0x0080020400080080, 0x0080010200040080,
    0x0080008001000200, 0x0080002040800100, 0x0000800020400080,
    0x0000400020005000, 0x0000801000200080, 0x0000800800100080,
    0x0000800400080080, 0x0000800200040080, 0x0000800100020080,
    0x0000800040800100, 0x0000208000400080, 0x0000404000201000,
    0x0000808010002000, 0x0000808008001000, 0x0000808004000800,
    0x0000808002000400, 0x0000010100020004, 0x0000020000408104,
    0x0000208080004000, 0x0000200040005000, 0x0000100080200080,
    0x0000080080100080, 0x0000040080080080, 0x0000020080040080,
    0x0000010080800200, 0x0000800080004100, 0x0000204000800080,
    0x0000200040401000, 0x0000100080802000, 0x0000080080801000,
    0x0000040080800800, 0x0000020080800400, 0x0000020001010004,
    0x0000800040800100, 0x0000204000808000, 0x0000200040008080,
    0x0000100020008080, 0x0000080010008080, 0x0000040008008080,
    0x0000020004008080, 0x0000010002008080, 0x0000004081020004,
    0x0000204000800080, 0x0000200040008080, 0x0000100020008080,
    0x0000080010008080, 0x0000040008008080, 0x0000020004008080,
    0x0000800100020080, 0x0000800041000080, 0x00FFFCDDFCED714A,
    0x007FFCDDFCED714A, 0x003FFFCDFFD88096, 0x0000040810002101,
    0x0001000204080011, 0x0001000204000801, 0x0001000082000401,
    0x0001FFFAABFAD1A2};

static uint64_t rookMasks[64] = {
    0x000101010101017E, 0x000202020202027C, 0x000404040404047A,
    0x0008080808080876, 0x001010101010106E, 0x002020202020205E,
    0x004040404040403E, 0x008080808080807E, 0x0001010101017E00,
    0x0002020202027C00, 0x0004040404047A00, 0x0008080808087600,
    0x0010101010106E00, 0x0020202020205E00, 0x0040404040403E00,
    0x0080808080807E00, 0x00010101017E0100, 0x00020202027C0200,
    0x00040404047A0400, 0x0008080808760800, 0x00101010106E1000,
    0x00202020205E2000, 0x00404040403E4000, 0x00808080807E8000,
    0x000101017E010100, 0x000202027C020200, 0x000404047A040400,
    0x0008080876080800, 0x001010106E101000, 0x002020205E202000,
    0x004040403E404000, 0x008080807E808000, 0x0001017E01010100,
    0x0002027C02020200, 0x0004047A04040400, 0x0008087608080800,
    0x0010106E10101000, 0x0020205E20202000, 0x0040403E40404000,
    0x0080807E80808000, 0x00017E0101010100, 0x00027C0202020200,
    0x00047A0404040400, 0x0008760808080800, 0x00106E1010101000,
    0x00205E2020202000, 0x00403E4040404000, 0x00807E8080808000,
    0x007E010101010100, 0x007C020202020200, 0x007A040404040400,
    0x0076080808080800, 0x006E101010101000, 0x005E202020202000,
    0x003E404040404000, 0x007E808080808000, 0x7E01010101010100,
    0x7C02020202020200, 0x7A04040404040400, 0x7608080808080800,
    0x6E10101010101000, 0x5E20202020202000, 0x3E40404040404000,
    0x7E80808080808000};

static uint64_t bishopShifts[64] = {
    58, 59, 59, 59, 59, 59, 59, 58, 59, 59, 59, 59, 59, 59, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59, 59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59, 59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 59, 59, 59, 59, 59, 59, 58, 59, 59, 59, 59, 59, 59, 58};

static uint64_t bishopMagics[64] = {
    0x0002020202020200, 0x0002020202020000, 0x0004010202000000,
    0x0004040080000000, 0x0001104000000000, 0x0000821040000000,
    0x0000410410400000, 0x0000104104104000, 0x0000040404040400,
    0x0000020202020200, 0x0000040102020000, 0x0000040400800000,
    0x0000011040000000, 0x0000008210400000, 0x0000004104104000,
    0x0000002082082000, 0x0004000808080800, 0x0002000404040400,
    0x0001000202020200, 0x0000800802004000, 0x0000800400A00000,
    0x0000200100884000, 0x0000400082082000, 0x0000200041041000,
    0x0002080010101000, 0x0001040008080800, 0x0000208004010400,
    0x0000404004010200, 0x0000840000802000, 0x0000404002011000,
    0x0000808001041000, 0x0000404000820800, 0x0001041000202000,
    0x0000820800101000, 0x0000104400080800, 0x0000020080080080,
    0x0000404040040100, 0x0000808100020100, 0x0001010100020800,
    0x0000808080010400, 0x0000820820004000, 0x0000410410002000,
    0x0000082088001000, 0x0000002011000800, 0x0000080100400400,
    0x0001010101000200, 0x0002020202000400, 0x0001010101000200,
    0x0000410410400000, 0x0000208208200000, 0x0000002084100000,
    0x0000000020880000, 0x0000001002020000, 0x0000040408020000,
    0x0004040404040000, 0x0002020202020000, 0x0000104104104000,
    0x0000002082082000, 0x0000000020841000, 0x0000000000208800,
    0x0000000010020200, 0x0000000404080200, 0x0000040404040400,
    0x0002020202020200};

static uint64_t bishopMasks[64] = {
    0x0040201008040200, 0x0000402010080400, 0x0000004020100A00,
    0x0000000040221400, 0x0000000002442800, 0x0000000204085000,
    0x0000020408102000, 0x0002040810204000, 0x0020100804020000,
    0x0040201008040000, 0x00004020100A0000, 0x0000004022140000,
    0x0000000244280000, 0x0000020408500000, 0x0002040810200000,
    0x0004081020400000, 0x0010080402000200, 0x0020100804000400,
    0x004020100A000A00, 0x0000402214001400, 0x0000024428002800,
    0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
    0x0008040200020400, 0x0010080400040800, 0x0020100A000A1000,
    0x0040221400142200, 0x0002442800284400, 0x0004085000500800,
    0x0008102000201000, 0x0010204000402000, 0x0004020002040800,
    0x0008040004081000, 0x00100A000A102000, 0x0022140014224000,
    0x0044280028440200, 0x0008500050080400, 0x0010200020100800,
    0x0020400040201000, 0x0002000204081000, 0x0004000408102000,
    0x000A000A10204000, 0x0014001422400000, 0x0028002844020000,
    0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
    0x0000020408102000, 0x0000040810204000, 0x00000A1020400000,
    0x0000142240000000, 0x0000284402000000, 0x0000500804020000,
    0x0000201008040200, 0x0000402010080400, 0x0002040810204000,
    0x0004081020400000, 0x000A102040000000, 0x0014224000000000,
    0x0028440200000000, 0x0050080402000000, 0x0020100804020000,
    0x0040201008040200};

static void init_pawn_attacks() {
    for (int square = A1; square <= H8; square++) {
        int file = square % 8;
        int rank = square / 8;

        uint64_t whiteAttacks = 0ULL;
        if (rank < 7) {
            if (file > 0)
                whiteAttacks |=
                    (1ULL << ((rank + 1) * 8 + (file - 1)));  // left capture
            if (file < 7)
                whiteAttacks |=
                    (1ULL << ((rank + 1) * 8 + (file + 1)));  // right capture
        }
        pawnAttacks[WHITE][square] = whiteAttacks;

        uint64_t blackAttacks = 0ULL;
        if (rank > 0) {
            if (file > 0)
                blackAttacks |=
                    (1ULL << ((rank - 1) * 8 + (file - 1)));  // left capture
            if (file < 7)
                blackAttacks |=
                    (1ULL << ((rank - 1) * 8 + (file + 1)));  // right capture
        }
        pawnAttacks[BLACK][square] = blackAttacks;
    }
}

static void init_knight_attacks() {
    // attack offsets
    int knightDeltas[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                              {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (int square = A1; square <= H8; square++) {
        uint64_t attacks = 0ULL;
        int file = square % 8;
        int rank = square / 8;

        for (int i = 0; i < 8; i++) {
            int newFile = file + knightDeltas[i][0];
            int newRank = rank + knightDeltas[i][1];

            // ensure pos is on the board
            if (newFile >= 0 && newFile < 8 && newRank >= 0 && newRank < 8) {
                int targetSquare = newRank * 8 + newFile;
                attacks |= (1ULL << targetSquare);
            }
        }

        knightAttacks[square] = attacks;
    }
}

static void init_king_attacks() {
    for (int square = A1; square <= H8; square++) {
        uint64_t attacks = 0ULL;
        int file = square % 8;
        int rank = square / 8;

        // All 8 king directions
        for (int df = -1; df <= 1; df++) {
            for (int dr = -1; dr <= 1; dr++) {
                if (df == 0 && dr == 0) continue;

                int newFile = file + df;
                int newRank = rank + dr;

                if (newFile >= 0 && newFile < 8 && newRank >= 0 &&
                    newRank < 8) {
                    int targetSquare = newRank * 8 + newFile;
                    attacks |= (1ULL << targetSquare);
                }
            }
        }
        kingAttacks[square] = attacks;
    }
}

static void init_attack_tables() {
    init_king_attacks();
    init_knight_attacks();
    init_pawn_attacks();
}

// convert index to occupancy pattern
static uint64_t index_to_occupancy(int index, uint64_t mask) {
    uint64_t occupancy = 0ULL;
    int bitCount = popcount(mask);

    for (int i = 0; i < bitCount; i++) {
        int square = pop_lsb(&mask);
        if (index & (1 << i)) {
            occupancy |= (1ULL << square);
        }
    }

    return occupancy;
}

// generate rook attacks tables
static uint64_t generate_rook_attacks_from_occupancy(int square,
                                                     uint64_t occupancy) {
    uint64_t attacks = 0ULL;
    int file = square % 8;
    int rank = square / 8;

    // N
    for (int r = rank + 1; r < 8; r++) {
        int sq = r * 8 + file;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // S
    for (int r = rank - 1; r >= 0; r--) {
        int sq = r * 8 + file;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // E
    for (int f = file + 1; f < 8; f++) {
        int sq = rank * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // W
    for (int f = file - 1; f >= 0; f--) {
        int sq = rank * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    return attacks;
}

// generate bishop attacks tables
static uint64_t generate_bishop_attacks_from_occupancy(int square,
                                                       uint64_t occupancy) {
    uint64_t attacks = 0ULL;
    int file = square % 8;
    int rank = square / 8;

    // NE
    for (int r = rank + 1, f = file + 1; r < 8 && f < 8; r++, f++) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // NW
    for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; r++, f--) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // SE
    for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; r--, f++) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // SW
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    return attacks;
}

static void init_rook_attacks(void) {
    for (int square = A1; square <= H8; square++) {
        uint64_t mask = rookMasks[square];
        int bitCount = popcount(mask);
        int permutations = 1 << bitCount;

        for (int i = 0; i < permutations; i++) {
            uint64_t occupancy = index_to_occupancy(i, mask);
            uint64_t attacks =
                generate_rook_attacks_from_occupancy(square, occupancy);

            // magic index
            uint64_t index =
                (occupancy * rookMagics[square]) >> rookShifts[square];
            rookAttacks[square][index] = attacks;
        }
    }
}

static void init_bishop_attacks(void) {
    for (int square = A1; square <= H8; square++) {
        uint64_t mask = bishopMasks[square];
        int bitCount = popcount(mask);
        int permutations = 1 << bitCount;

        for (int i = 0; i < permutations; i++) {
            uint64_t occupancy = index_to_occupancy(i, mask);
            uint64_t attacks =
                generate_bishop_attacks_from_occupancy(square, occupancy);

            uint64_t index =
                (occupancy * bishopMagics[square]) >> bishopShifts[square];
            bishopAttacks[square][index] = attacks;
        }
    }
}

static void init_magic_tables() {
    init_rook_attacks();
    init_bishop_attacks();
}

void initialize_movegen() {
    init_attack_tables();
    init_magic_tables();
}

uint64_t get_pawn_attacks(Square square, Side side) {
    return pawnAttacks[side][square];
}

uint64_t get_knight_attacks(Square square) { return knightAttacks[square]; }

uint64_t get_king_attacks(Square square) { return kingAttacks[square]; }

uint64_t get_rook_attacks(Square square, uint64_t occupied) {
    uint64_t blockers = occupied & rookMasks[square];
    int index = (blockers * rookMagics[square]) >> rookShifts[square];

    return rookAttacks[square][index];
}

uint64_t get_bishop_attacks(Square square, uint64_t occupied) {
    uint64_t blockers = occupied & bishopMasks[square];
    int index = (blockers * bishopMagics[square]) >> bishopShifts[square];
    return bishopAttacks[square][index];
}

uint64_t get_queen_attacks(Square square, uint64_t occupied) {
    return get_rook_attacks(square, occupied) |
           get_bishop_attacks(square, occupied);
}

static uint64_t get_attack_bitboard(board_t *board, Side side) {
    bb64 occupied = board->occupied[side] | board->occupied[!side];
    bb64 attacks = 0;
    bb64 pcbb;

    pcbb = board->pcbb[W_PAWN + side * 6];
    while (pcbb) {
        attacks |= get_pawn_attacks(pop_lsb(&pcbb), side);
    }

    pcbb = board->pcbb[W_KNIGHT + side * 6];
    while (pcbb) {
        attacks |= get_knight_attacks(pop_lsb(&pcbb));
    }

    pcbb = board->pcbb[W_BISHOP + side * 6];
    while (pcbb) {
        attacks |= get_bishop_attacks(pop_lsb(&pcbb), occupied);
    }

    pcbb = board->pcbb[W_ROOK + side * 6];
    while (pcbb) {
        attacks |= get_rook_attacks(pop_lsb(&pcbb), occupied);
    }

    pcbb = board->pcbb[W_QUEEN + side * 6];
    while (pcbb) {
        attacks |= get_queen_attacks(pop_lsb(&pcbb), occupied);
    }

    pcbb = board->pcbb[W_KING + side * 6];
    while (pcbb) {
        attacks |= get_king_attacks(pop_lsb(&pcbb));
    }

    return attacks;
}

static void add_promo_variations(board_t *board, movelist_t *moves,
                                 move_t move) {
    uint8_t existingFlags = MOVE32_FLAGS(move.move32);
    MOVE32_SET_FLAGS(move.move32, existingFlags | MOVE_FLAG_KNIGHT_PROMO);
    rate_move(board, &move);
    movelist_add(moves, move);
    MOVE32_SET_FLAGS(move.move32, existingFlags | MOVE_FLAG_BISHOP_PROMO);
    rate_move(board, &move);
    movelist_add(moves, move);
    MOVE32_SET_FLAGS(move.move32, existingFlags | MOVE_FLAG_ROOK_PROMO);
    rate_move(board, &move);
    movelist_add(moves, move);
    MOVE32_SET_FLAGS(move.move32, existingFlags | MOVE_FLAG_QUEEN_PROMO);
    rate_move(board, &move);
    movelist_add(moves, move);
}

void generate_pawn_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_PAWN + side * 6;
    bb64 pcbb = board->pcbb[moved];
    PieceType captured = EMPTY;
    move_t move = {0};
    int8_t dir = side == WHITE ? 1 : -1;
    int8_t rank_promo = side == WHITE ? 7 : 0;

    while (pcbb) {  // loop over all pawns of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        uint8_t rank_src = src / 8;
        uint8_t rank_target = rank_src + dir;

        // add attacking moves
        bb64 attacks = get_pawn_attacks(src, side) & board->occupied[!side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];
            move = create_move(src, target, moved, captured,
                               board->castlingRights, MOVE_FLAG_CAPTURE);

            // cant be quiet if promo
            if (rank_target == rank_promo) {
                add_promo_variations(board, moves, move);
            } else {
                rate_move(board, &move);
                movelist_add(moves, move);
            }
        }

        // pawn push, one square
        target = src + dir * 8;
        if (SQUARE_VALID(target) && board->squares[target] == EMPTY) {
            move = create_move(src, target, moved, EMPTY, board->castlingRights,
                               MOVE_FLAG_QUITE);
            // cant be quiet if promo
            if (rank_target == rank_promo) {
                add_promo_variations(board, moves, move);
            } else {
                rate_move(board, &move);
                movelist_add(moves, move);
            }

            // pawn push, two squares
            target = target + dir * 8;
            if (((rank_src == 1 && side == WHITE) ||   // white double push
                 (rank_src == 6 && side == BLACK)) &&  // black double push
                SQUARE_VALID(target) &&
                board->squares[target] == EMPTY) {
                MOVE32_SET_DST(move.move32, target);
                MOVE32_SET_FLAGS(move.move32, MOVE_FLAG_DOUBLE_PAWN_PUSH);
                rate_move(board, &move);
                movelist_add(moves, move);
            }
        }

        // en passant
        if (SQUARE_VALID(board->enPassantSquare)) {
            // valid EP attackers are the same as the squares that the EP square
            // could attack, from the other sides POV
            uint64_t ep_attacked = get_pawn_attacks(src, board->sideToMove) &
                                   bitboard_masks[board->enPassantSquare];
            if (ep_attacked) {
                move = create_move(src, board->enPassantSquare, moved,
                                   side == WHITE ? B_PAWN : W_PAWN,
                                   board->castlingRights, MOVE_FLAG_EN_PASSANT);
                rate_move(board, &move);
                movelist_add(moves, move);
            }
        }
    }
}

void generate_knight_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_KNIGHT + side * 6;
    PieceType captured = EMPTY;
    bb64 pcbb = board->pcbb[moved];

    while (pcbb) {  // loop over all knights of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        move_t move;

        bb64 attacks = get_knight_attacks(src) & ~board->occupied[side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];

            move = create_move(
                src, target, moved, captured, board->castlingRights,
                captured == EMPTY ? MOVE_FLAG_QUITE : MOVE_FLAG_QUITE);
            rate_move(board, &move);
            movelist_add(moves, move);
        }
    }
}

void generate_king_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_KING + side * 6;
    PieceType captured = EMPTY;
    bb64 pcbb = board->pcbb[moved];

    while (pcbb) {  // loop over all kings of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        move_t move;
        bb64 attacks = get_king_attacks(src) & ~board->occupied[side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];

            move = create_move(
                src, target, moved, captured, board->castlingRights,
                captured == EMPTY ? MOVE_FLAG_QUITE : MOVE_FLAG_QUITE);
            rate_move(board, &move);
            movelist_add(moves, move);
        }
    }
}

void generate_rook_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_ROOK + side * 6;
    PieceType captured = EMPTY;
    bb64 pcbb = board->pcbb[moved];

    while (pcbb) {  // loop over all rooks of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        move_t move;
        bb64 occupied = board->occupied[side] | board->occupied[!side];
        bb64 attacks = get_rook_attacks(src, occupied) & ~board->occupied[side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];

            move = create_move(
                src, target, moved, captured, board->castlingRights,
                captured == EMPTY ? MOVE_FLAG_QUITE : MOVE_FLAG_QUITE);
            rate_move(board, &move);
            movelist_add(moves, move);
        }
    }
}

void generate_bishop_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_BISHOP + side * 6;
    PieceType captured = EMPTY;
    bb64 pcbb = board->pcbb[moved];

    while (pcbb) {  // loop over all bishops of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        move_t move;
        bb64 occupied = board->occupied[side] | board->occupied[!side];
        bb64 attacks =
            get_bishop_attacks(src, occupied) & ~board->occupied[side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];

            move = create_move(
                src, target, moved, captured, board->castlingRights,
                captured == EMPTY ? MOVE_FLAG_QUITE : MOVE_FLAG_QUITE);
            rate_move(board, &move);
            movelist_add(moves, move);
        }
    }
}

void generate_queen_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;
    PieceType moved = W_QUEEN + side * 6;
    PieceType captured = EMPTY;
    bb64 pcbb = board->pcbb[moved];

    while (pcbb) {  // loop over all queens of side to move
        Square src = pop_lsb(&pcbb);
        Square target;
        move_t move;
        bb64 occupied = board->occupied[side] | board->occupied[!side];
        bb64 attacks =
            get_queen_attacks(src, occupied) & ~board->occupied[side];
        while (attacks) {  // loop over valid attacks on enemy pieces
            target = pop_lsb(&attacks);
            captured = board->squares[target];

            move = create_move(
                src, target, moved, captured, board->castlingRights,
                captured == EMPTY ? MOVE_FLAG_QUITE : MOVE_FLAG_QUITE);
            rate_move(board, &move);
            movelist_add(moves, move);
        }
    }
}

int is_square_attacked_by(board_t *board, Square square, Side side) {
    return (bitboard_masks[square] & get_attack_bitboard(board, side)) != 0;
}

int is_in_check(board_t *board, Side side) {
    PieceType moved = W_KING + side * 6;
    bb64 pcbb = board->pcbb[moved];

    // loop over all kings, to support gamemodes with multiple
    while (pcbb) {
        Square src = pop_lsb(&pcbb);
        if (is_square_attacked_by(board, src, !side)) return 1;
    }

    return 0;
}

static int can_castle_kingside(board_t *board, Side side) {
    // check rights
    uint8_t required_right =
        (side == WHITE) ? CASTLE_WHITE_KING : CASTLE_BLACK_KING;
    if (!(board->castlingRights & required_right)) return 0;

    // check squares
    Square f_square = (side == WHITE) ? F1 : F8;
    Square g_square = (side == WHITE) ? G1 : G8;

    if (board->squares[f_square] != EMPTY || board->squares[g_square] != EMPTY)
        return 0;

    // ensure rook and king in correct spots
    Square king_square = (side == WHITE) ? E1 : E8;
    Square rook_square = (side == WHITE) ? H1 : H8;

    if (board->squares[king_square] != (W_KING + side * 6) ||
        board->squares[rook_square] != (W_ROOK + side * 6))
        return 0;

    // ensure f and g are not attacked
    if (is_square_attacked_by(board, f_square, (~side) & 1) ||
        is_square_attacked_by(board, g_square, (~side) & 1))
        return 0;

    return 1;
}

static int can_castle_queenside(board_t *board, Side side) {
    // check rights
    uint8_t required_right =
        (side == WHITE) ? CASTLE_WHITE_QUEEN : CASTLE_BLACK_QUEEN;
    if (!(board->castlingRights & required_right)) return 0;

    // check squares
    Square b_square = (side == WHITE) ? B1 : B8;
    Square c_square = (side == WHITE) ? C1 : C8;
    Square d_square = (side == WHITE) ? D1 : D8;

    if (board->squares[b_square] != EMPTY ||
        board->squares[c_square] != EMPTY || board->squares[d_square] != EMPTY)
        return 0;

    // ensure rook and king in correct spots
    Square king_square = (side == WHITE) ? E1 : E8;
    Square rook_square = (side == WHITE) ? A1 : A8;

    if (board->squares[king_square] != (W_KING + side * 6) ||
        board->squares[rook_square] != (W_ROOK + side * 6)) {
        return 0;
    }

    // check squares c and d are not attacked
    if (is_square_attacked_by(board, c_square, !side) ||
        is_square_attacked_by(board, d_square, !side)) {
        return 0;
    }

    return 1;
}

void generate_castling_moves(board_t *board, movelist_t *moves) {
    Side side = board->sideToMove;

    if (board->inCheck) return;

    // check kingside castling
    if (can_castle_kingside(board, side)) {
        Square king_from = (side == WHITE) ? E1 : E8;
        Square king_to = (side == WHITE) ? G1 : G8;

        move_t move = create_move(king_from, king_to, W_KING + side * 6, EMPTY,
                                  board->castlingRights, MOVE_FLAG_KING_CASTLE);
        rate_move(board, &move);
        movelist_add(moves, move);
    }

    // check queenside castling
    if (can_castle_queenside(board, side)) {
        Square king_from = (side == WHITE) ? E1 : E8;
        Square king_to = (side == WHITE) ? C1 : C8;

        move_t move =
            create_move(king_from, king_to, W_KING + side * 6, EMPTY,
                        board->castlingRights, MOVE_FLAG_QUEEN_CASTLE);
        rate_move(board, &move);
        movelist_add(moves, move);
    }
}

void generate_moves(board_t *board, movelist_t *moves) {
    generate_pawn_moves(board, moves);
    generate_knight_moves(board, moves);
    generate_king_moves(board, moves);
    generate_rook_moves(board, moves);
    generate_bishop_moves(board, moves);
    generate_queen_moves(board, moves);
    generate_castling_moves(board, moves);
}

void movelist_add(movelist_t *moves, move_t move) {
    if (moves->moveCount >= MOVELIST_SIZE) return;  // safety
    moves->move[moves->moveCount++] = move;
}

void movelist_clear(movelist_t *moves) {
    moves->moveCount = 0;
    moves->index = 0;
}

void movelist_print(movelist_t *moves) {
    for (int i = 0; i < moves->moveCount; i++) {
        print_move(moves->move[i]);
    }
}

static uint64_t perft_twig(board_t *board, int depth) {
    movelist_t moves = {0};
    uint64_t nodes = 0;
    int ret = 0;

    if (depth == 0) return 1ULL;

    generate_moves(board, &moves);

    for (int i = 0; i < moves.moveCount; i++) {
        ret = make_move(board, moves.move[i]);
        if (!ret) {  // move is legal
            nodes += perft_twig(board, depth - 1);
        }
        unmake_move(board);
    }
    return nodes;
}

uint64_t perft(board_t *board, int depth) {
    movelist_t moves = {0};
    uint64_t nodes = 0;
    uint64_t twig_nodes = 0;
    int ret = 0;

    if (depth == 0) return 1ULL;

    generate_moves(board, &moves);

    for (int i = 0; i < moves.moveCount; i++) {
        ret = make_move(board, moves.move[i]);
        if (!ret) {  // move is legal
            twig_nodes = perft_twig(board, depth - 1);
            nodes += twig_nodes;
            // print_move(moves.move[i]);
            // printf("\t%lu nodes\n", twig_nodes);
        }
        unmake_move(board);
    }
    return nodes;
}

// TODO unimplemented!
void rate_move(board_t *board, move_t *move) { return; }