// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ZLIB_H__
#define __VE_ZLIB_H__

#include <vector>

#include "engine/common.h"
#include "engine/tools/dynamic_huffman_tree.h"

#define DEFLATE_COMPRESSION   8
#define WINDOW_32K            7

#define ZLIB_BUFFER_SIZE      32 * 1024 // 32Kb

#define MAX_LITERAL_NUMBER    286
#define MAX_DISTANCE_NUMBER   32

// Block types
#define BLOCK_NO_COMPRESSION  0
#define BLOCK_FIXED_HUFFMAN   1
#define BLOCK_DYNAMIC_HUFFMAN 2
#define BLOCK_RESERD          3

namespace ve {

/**
    Class for decompressing inflated data.
    @warning It was written long time ago and now
    I understand almost nothing in this class. I will leave
    here only basic comments.
*/
class ZLib {
private:
  uint position;                                                             // Position in buffer (bits)

  uchar getBit(std::vector<uchar> &source);                                  // Get bit from source stream
  uchar getByte(std::vector<uchar> &source);
  uint getMSBvalue(std::vector<uchar> &source, uchar bits);                  // Get "bits" bits from input stream stored in MSB order
  uint getLSBvalue(std::vector<uchar> &source, uchar bits);                  // Get "bits" bits from input stream stored in LSB order
  uint getLength(std::vector<uchar> &source, uint literalCode);              // Get real repeat length from length code ans reads extra bits if it need
  uint getDistance(std::vector<uchar> &source, uint distanceCode);           // Get real distance from distance code and reads extra bits if need
  void repeat(std::vector<uchar> &data, uint repLength, uint repDistance); // Apply <length, distance> pait to output stream

  /**
      Decodes next symbol from a given file.
      @param source - File to get bytes from.
      @param tree - Huffman tree to use for decoding.
      @return Next decoded from a stream symbol.
  */
  uint decodeSymbol(std::vector<uchar> &source, DynamicHuffmanTree *tree);

public:
  /**
      Default constructor.
  */
  ZLib();

  /**
      Deflates data from file and stores decompressed data in
      the 'data' array.
      @param data - Uncompressed data.
      @param sourceData - Source file to uncompress.
  */
  Outcome deflate(std::vector<uchar> &data, std::vector<uchar> &sourceData);
};

}

#endif // __VE_ZLIB_H__
