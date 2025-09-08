#include "board.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

// take a string (i.e. K) and return the PieceType
PieceType char_to_piece(const char c) {
    switch (c) {
        case 'P':
            return W_PAWN;
        case 'N':
            return W_KNIGHT;
        case 'B':
            return W_BISHOP;
        case 'R':
            return W_ROOK;
        case 'Q':
            return W_QUEEN;
        case 'K':
            return W_KING;
        case 'p':
            return B_PAWN;
        case 'n':
            return B_KNIGHT;
        case 'b':
            return B_BISHOP;
        case 'r':
            return B_ROOK;
        case 'q':
            return B_QUEEN;
        case 'k':
            return B_KING;
        default:
            return EMPTY;
    }
}

char piece_to_char(PieceType piece) {
    switch (piece) {
        case W_PAWN:
            return 'P';
        case W_KNIGHT:
            return 'N';
        case W_BISHOP:
            return 'B';
        case W_ROOK:
            return 'R';
        case W_QUEEN:
            return 'Q';
        case W_KING:
            return 'K';
        case B_PAWN:
            return 'p';
        case B_KNIGHT:
            return 'n';
        case B_BISHOP:
            return 'b';
        case B_ROOK:
            return 'r';
        case B_QUEEN:
            return 'q';
        case B_KING:
            return 'k';
        case EMPTY:
        default:
            return '.';
    }
}

// take a string (i.e. a1) and return the Square
Square str_to_square(const char* sq) {
    if (strlen(sq) != 2) return -1;

    char file = sq[0];
    char rank = sq[1];

    if (file < 'a' || file > 'h') return -1;
    if (rank < '1' || rank > '8') return -1;

    return (rank - '1') * 8 + (file - 'a');
}

// set a piece on the board, including updating utility bitboards
void set_piece(board_t* board, Square sq, PieceType piece) {
    if (piece != EMPTY && sq >= 0 && sq < 64) {
        board->squares[sq] = piece;                // set square
        board->pcbb[piece] |= bitboard_masks[sq];  // set bitboard for piece
        board->occupied[PIECE_SIDE(piece)] |=
            bitboard_masks[sq];  // set bitboard for color
    }
}

// parses placement, i.e. rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
int parse_piece_placement(board_t* board, const char* placement) {
    if (board == NULL || placement == NULL) {
        return -1;
    }

    clear_board(board);

    int rank = 7;
    int file = 0;

    for (int i = 0; placement[i] != '\0'; i++) {
        char c = placement[i];

        if (c == '/') {
            // Move to next rank
            if (file != 8) return -1;
            rank--;
            file = 0;
            if (rank < 0) return -1;
        } else if (isdigit(c)) {
            // Empty squares
            int empty_count = c - '0';
            if (empty_count < 1 || empty_count > 8) return -1;
            file += empty_count;
            if (file > 8) return -1;
        } else {
            // Piece character
            PieceType piece = char_to_piece(c);
            if (piece == EMPTY) return -1;

            if (file >= 8) return -1;

            int square = rank * 8 + file;
            set_piece(board, square, piece);
            file++;
        }
    }

    // Should end on rank 1 with all files filled
    if (rank != 0 || file != 8) return -1;

    return 0;
}

// parse side to move
int parse_side_to_move(board_t* board, const char* side) {
    if (strlen(side) != 1) return -1;

    switch (side[0]) {
        case 'w':
            board->sideToMove = WHITE;
            break;
        case 'b':
            board->sideToMove = BLACK;
            break;
        default:
            return -1;
    }

    return 0;
}

// parse castling availability
int parse_castling(board_t* pos, const char* castling) {
    pos->castlingRights = 0;

    if (strcmp(castling, "-") == 0) {
        return 0;  // No castling rights
    }

    for (int i = 0; castling[i] != '\0'; i++) {
        switch (castling[i]) {
            case 'K':
                pos->castlingRights |= CASTLE_WHITE_KING;
                break;
            case 'Q':
                pos->castlingRights |= CASTLE_WHITE_QUEEN;
                break;
            case 'k':
                pos->castlingRights |= CASTLE_BLACK_KING;
                break;
            case 'q':
                pos->castlingRights |= CASTLE_BLACK_QUEEN;
                break;
            default:
                return -1;
        }
    }

    return 0;
}

// parse en passant target square
int parse_en_passant(board_t* pos, const char* en_passant) {
    if (strcmp(en_passant, "-") == 0) {
        pos->enPassantSquare = ER;
        return 0;
    }

    int square = str_to_square(en_passant);
    if (square < 0) return -1;

    int rank = square / 8;
    if (rank != 2 && rank != 5) return -1;

    pos->enPassantSquare = square;
    return 0;
}

// public FEN parsing function
int set_fen(board_t* board, char* fen) {
    if (!board || !fen) return -1;

    clear_board(board);

    char* fen_copy = malloc(strlen(fen) + 1);
    if (!fen_copy) return -1;
    strcpy(fen_copy, fen);

    char* tokens[6];
    int token_count = 0;
    char* token = strtok(fen_copy, " ");

    while (token && token_count < 6) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    if (token_count < 4) {
        free(fen_copy);
        return -1;
    }

    int ret;

    ret = parse_piece_placement(board, tokens[0]);
    if (ret) {
        free(fen_copy);
        return ret;
    }

    ret = parse_side_to_move(board, tokens[1]);
    if (ret) {
        free(fen_copy);
        return ret;
    }

    ret = parse_castling(board, tokens[2]);
    if (ret) {
        free(fen_copy);
        return ret;
    }

    ret = parse_en_passant(board, tokens[3]);
    if (ret) {
        free(fen_copy);
        return ret;
    }

    if (token_count >= 5) {
        char* endptr;
        long halfmove = strtol(tokens[4], &endptr, 10);
        if (*endptr != '\0' || halfmove < 0) {
            free(fen_copy);
            return -1;
        }
        board->halfMoves = (int)halfmove;
    }

    if (token_count >= 6) {
        char* endptr;
        long fullmove = strtol(tokens[5], &endptr, 10);
        if (*endptr != '\0' || fullmove < 1) {
            free(fen_copy);
            return -1;
        }
        board->fullMoves = (int)fullmove;
    } else {
        board->fullMoves = 1;
    }

    free(fen_copy);
    return 0;
}

// public init board function
void init_board(board_t* board) { set_fen(board, STARTING_FEN); }

// public clear board function
int clear_board(board_t* board) {
    if (board == NULL) return -1;
    memset(board, 0, sizeof(board_t));
    board->enPassantSquare = ER;

    return 0;
}

// public print board function
void print_board(board_t* board) {
    printf("\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int rank = 7; rank >= 0; rank--) {
        printf("%d |", rank + 1);

        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            char piece_char = piece_to_char(board->squares[square]);
            printf(" %c |", piece_char);
        }

        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }

    // Print file labels (A-H)
    printf("    A   B   C   D   E   F   G   H\n");
    printf("\n");

    // Print additional game state
    printf("Side to move: %s\n", board->sideToMove ? "Black" : "White");
    printf("Castling: ");
    if (board->castlingRights & CASTLE_WHITE_KING) printf("K");
    if (board->castlingRights & CASTLE_WHITE_QUEEN) printf("Q");
    if (board->castlingRights & CASTLE_BLACK_KING) printf("k");
    if (board->castlingRights & CASTLE_BLACK_QUEEN) printf("q");
    if (board->castlingRights == 0) printf("-");
    printf("\n");
}