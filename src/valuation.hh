#pragma once

#include <vector>

#include "bitboards/moves/all.hh"

int piece_count(std::vector<unsigned long long> bitBoard, size_t piece_place);

int white_count(std::vector<unsigned long long> bitBoard);
int back_count(std::vector<unsigned long long> bitBoard);
int score(std::vector<unsigned long long> bitBoard);
