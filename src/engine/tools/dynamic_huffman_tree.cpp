// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>
#include <memory.h>
#include "tools/dynamic_huffman_tree.h"

namespace ve {

/**
    Default constructor.
    Sets all the code lengths to zero values.
    Prepares table for 'size' symbols.
    @param size - Number of symbols that this tree will hold.
*/
DynamicHuffmanTree::DynamicHuffmanTree(int size) {
  codes.resize(size);
  lengths.resize(size);
}

/**
  Sets all lengths to zero.
*/
void DynamicHuffmanTree::reset() {
  memset(&codes[0], 0, sizeof(int) * codes.size());
  memset(&lengths[0], 0, sizeof(int) * lengths.size());
}

/**
    Set length of the code symbol.
    @param symbol - Symbol to set code length for.
    @param length - Length of the code for the given symbol.
    @return OK if length was set correctly.
    @return INVALID_VALUE if symbol is out of bounds or length is negative.
*/
Outcome DynamicHuffmanTree::setLength(uint symbol, uint length) {
  ERROR_IF(symbol >= lengths.size(), L"Symbol: " + StringTool::intToStr(symbol) + L" is out of bounds", INVALID_VALUE);
  lengths[symbol] = length;
  return OK;
}

/**
    Returns code length for a given symbol.
    @return Code length for a given symbol.
    @return -1 if symbol is out of bounds.
*/
int DynamicHuffmanTree::getLength(uint symbol) {
  ERROR_IF(symbol >= lengths.size(), L"Symbol is out of bounds", -1);
  return lengths[symbol];
}

/**
    Sets code length for group of successive symbols starting
    from a given symbol.
    @param startSymbol - Symbol to start from.
    @param count - Number of symbols to set code length for.
    @param length - Code length to set.
    @return OK if operation suceeded.
    @return INVALID_VALUE if at least any symbol is out of bounds.
*/
Outcome DynamicHuffmanTree::fill(uint startSymbol, uint count, uint length) {
  ERROR_IF(startSymbol + count - 1 > lengths.size(), L"Too many symbols", INVALID_VALUE);

  for (uint i = 0; i < count; i++) {
    lengths[startSymbol + i] = length;
  }

  return OK;
}


/**
    Generates codes for symbols using code lengths table which was
    set before this call.
    @return OK if codes were computed successfully.
    @return non-OK if error occurred.
*/
Outcome DynamicHuffmanTree::genCodes() {
  int maxLen = 0;
  std::vector<uint> repeatTime;
  std::vector<uint> nextCode;

  for (uint i = 0; i < lengths.size(); i++) {
    maxLen = std::max(maxLen, lengths[i]);
  }

  /* Resize for value from 0 to maxLen inclusive */
  repeatTime.resize(maxLen + 1);
  lengthToCode.resize(maxLen + 1);

  for (int i = 0; i < maxLen + 1; i++) {
    lengthToCode[i].clear();
  }

  /* Fill repeatTime table */
  for (uint i = 0; i < lengths.size(); i++) {
    repeatTime[lengths[i]]++;
  }
  repeatTime[0] = 0;

  /* Prepare nextCode table */
  /* It also has indices from 0 to maxLen inclusive */
  nextCode.resize(maxLen + 1);
  uint code = 0;
  for (int i = 1; i <= maxLen; i++) {
    code = (code + repeatTime[i - 1]) << 1;
    nextCode[i] = code;
  }

  /* Finally, construct codes */
  for (uint i = 0; i < codes.size(); i++) {
    uint len = lengths[i];
    if (len != 0) {
      codes[i] = nextCode[len];
      lengthToCode[len].push_back(std::make_pair(codes[i], i));
      nextCode[len]++;
    }
  }

  return OK;
}

Outcome DynamicHuffmanTree::prepare() {
  int maxLen = 0;

  for (uint i = 0; i < lengths.size(); i++) {
    maxLen = std::max(maxLen, lengths[i]);
  }

  /* Resize for value from 0 to maxLen inclusive */
  lengthToCode.resize(maxLen + 1);

  for (int i = 0; i < maxLen + 1; i++) {
    lengthToCode[i].clear();
  }

  /* Fill lengthtoCode array */
  for (uint i = 0; i < codes.size(); i++) {
    uint len = lengths[i];
    if (len != 0) {
      lengthToCode[len].push_back(std::make_pair(codes[i], i));
    }
  }

  return OK;
}

/**
    Returns code of the symbol. genCodes() must be called prior to this call.
    @param symbol - Symbol to return Humman's code for.
    @return Code of the given symbol.
*/
uint DynamicHuffmanTree::getCode(uint symbol) {
  ERROR_IF(symbol >= codes.size(), L"Symbol: " + StringTool::intToStr(symbol) + L"is out of bounds", 0);
  return codes[symbol];
}

/**
    Changes code for a given symbol.
    @param symbol - Symbol to change Humman's code for.
    @param code - New code for symbol
    @return OK if change succeeded.
    @return INVALID_VALUE if symbol is out of range.
*/
Outcome DynamicHuffmanTree::setCode(uint symbol, uint code) {
  ERROR_IF(symbol >= codes.size(), L"Symbol: " + StringTool::intToStr(symbol) + L"is out of bounds", INVALID_VALUE);
  codes[symbol] = code;
  return OK;
}

/**
    Checks if given code with specified bit length exists in this Huffman tree.
    @return Symbol if it exists in this tree.
    @return -1 if there is no symbol with such code and bit length.
*/
int DynamicHuffmanTree::exists(uint code, uint length) {
  uint len = lengthToCode[length].size();

  for (uint i = 0; i < len; i++) {
    if (lengthToCode[length][i].first == (int)code) {
      return lengthToCode[length][i].second;
    }
  }

  return -1;
}

}
