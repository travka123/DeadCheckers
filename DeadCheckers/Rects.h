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

struct CellCords {
    int x;
    int y;

    friend bool operator== (const CellCords& c1, const CellCords& c2) {
        return !memcmp(&c1, &c2, sizeof(CellCords));
    }
};
