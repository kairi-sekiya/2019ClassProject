#pragma once

constexpr int WINDOW_WIDTH = 1980;
constexpr int WINDOW_HEIGHT = 1080;
constexpr bool BACK = false;
constexpr bool Front = true;

#define CARD_NUM(card)  card % 100;
#define CARD_MARK(card) card / 100; 