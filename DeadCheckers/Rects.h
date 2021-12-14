#pragma once

#include <string>

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct CellRect {
    float y;
    float x;
    float scale;
};

struct BoardCords {
    int x;
    int y;

    friend bool operator== (const BoardCords& c1, const BoardCords& c2) {
        return !memcmp(&c1, &c2, sizeof(BoardCords));
    }
};
