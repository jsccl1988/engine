// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>
#include <memory.h>

#include "zlib/zlib.h"
#include "tools/dynamic_huffman_tree.h"

namespace ve {

ZLib::ZLib() {
}

uchar ZLib::getBit(std::vector<uchar> &source) {
  uint byteNo = (position / 8);
  uchar bitNo = (position % 8);

  ERROR_IF(byteNo >= source.size(), L"Buffer size exceeded", 0);
  uchar value = (source[byteNo] & (1 << bitNo)) ? 1 : 0;

  position++;
  return value;
}

uint ZLib::getMSBvalue(std::vector<uchar> &source, uchar bits) {
  uint result = 0;
  ERROR_IF(bits > 48, L"bits > 48", 0);

  for (int i = 0; i < bits; i++) {
    result = (result << 1) | getBit(source);
  }

  return result;
}

uint ZLib::getLSBvalue(std::vector<uchar> &source, uchar bits) {
  uint result = 0;
  ERROR_IF(bits > 48, L"bits > 48", 0);

  for (int i = 0; i < bits; i++) {
    result = result | (getBit(source) << i);
  }

  return result;
}

uint ZLib::getLength(std::vector<uchar> &source, uint literalCode) {
  /*

        Extra               Extra               Extra
  Code Bits Length(s) Code Bits Lengths   Code Bits Length(s)
  ---- ---- ------     ---- ---- -------   ---- ---- -------
    257   0     3       267   1   15,16     277   4   67-82
    258   0     4       268   1   17,18     278   4   83-98
    259   0     5       269   2   19-22     279   4   99-114
    260   0     6       270   2   23-26     280   4  115-130
    261   0     7       271   2   27-30     281   5  131-162
    262   0     8       272   2   31-34     282   5  163-194
    263   0     9       273   3   35-42     283   5  195-226
    264   0    10       274   3   43-50     284   5  227-257
    265   1  11,12      275   3   51-58     285   0    258
    266   1  13,14      276   3   59-66

    */
  uchar extraBits[29] = { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0 };
  uint  baseLength[29] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59,
                            67, 83, 99, 115, 131, 163, 195, 227, 258
  };

  uint extraLength = getLSBvalue(source, extraBits[literalCode - 257]);
  return baseLength[literalCode - 257] + extraLength;
}

uint ZLib::getDistance(std::vector<uchar> &source, uint distanceCode) {
  /*

        Extra           Extra               Extra
    Code Bits Dist  Code Bits   Dist     Code Bits Distance
    ---- ---- ----  ---- ----  ------    ---- ---- --------
      0   0    1     10   4     33-48    20    9   1025-1536
      1   0    2     11   4     49-64    21    9   1537-2048
      2   0    3     12   5     65-96    22   10   2049-3072
      3   0    4     13   5     97-128   23   10   3073-4096
      4   1   5,6    14   6    129-192   24   11   4097-6144
      5   1   7,8    15   6    193-256   25   11   6145-8192
      6   2   9-12   16   7    257-384   26   12  8193-12288
      7   2  13-16   17   7    385-512   27   12 12289-16384
      8   3  17-24   18   8    513-768   28   13 16385-24576
      9   3  25-32   19   8   769-1024   29   13 24577-32768

  */
  uchar extraBits[30] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };
  uint baseDistance[30] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385,
                            513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577
  };
  ERROR_IF(distanceCode > 29, L"Distance > 29", 0);

  uint extraDistance = getLSBvalue(source, extraBits[distanceCode]);
  return baseDistance[distanceCode] + extraDistance;
}

void ZLib::repeat(std::vector<uchar> &data, uint repLength, uint repDistance) {
  uint readPos = data.size() - repDistance;

  for (uint i = 0; i < repLength; i++) {
    data.push_back(data[readPos++]);
  }
}

/**
    Decodes next symbol from a given file.
    @param source - File to get bytes from.
    @param tree - Huffman tree to use for decoding.
    @return Next decoded from a stream symbol.
*/
uint ZLib::decodeSymbol(std::vector<uchar> &source, DynamicHuffmanTree *tree) {
  uint dataCode = 0;
  uint bits = 0;

  do {
    dataCode = (dataCode << 1) | getBit(source);
    bits++;

    ERROR_IF(bits > 32, L"It seems that this is an infinite loop :(", 0)
  } while (tree->exists(dataCode, bits) == -1);

    return tree->exists(dataCode, bits);
}

Outcome ZLib::deflate(std::vector<uchar> &data, std::vector<uchar> &sourceData) {
  /*

      5 Bits: HLIT, # of Literal/Length codes - 257 (257 - 286)
      5 Bits: HDIST, # of Distance codes - 1        (1 - 32)
      4 Bits: HCLEN, # of Code Length codes - 4     (4 - 19)

      (HCLEN + 4) x 3 bits: code lengths for the code length
        alphabet given just above, in the order: 16, 17, 18,
        0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15

        These code lengths are interpreted as 3-bit integers
        (0-7); as above, a code length of 0 means the
        corresponding symbol (literal/length or distance code
        length) is not used.

      HLIT + 257 code lengths for the literal/length alphabet,
        encoded using the code length Huffman code

      HDIST + 1 code lengths for the distance alphabet,
        encoded using the code length Huffman code

      The actual compressed data of the block,
        encoded using the literal/length and distance Huffman
        codes

      The literal/length symbol 256 (end of data),
        encoded using the literal/length Huffman code

  */
  uchar CMF, FLG, compressionMethod, compressionInfo, check, dict, level;
  uint adler32;
  uchar final, blockType;
  uint HLIT, HDIST, HCLEN;

  /* for decoding lengths Huffman table */
  uchar lengthPosition[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
  uint decodedSymbol = 0;
  uint repLength, repDistance;

  /*  Initialize buffer position */
  position = 0;

  CMF = getLSBvalue(sourceData, 8);
  compressionMethod = CMF & 0x0F;
  compressionInfo = (CMF & 0xF0) >> 4;
  ERROR_IF(compressionMethod != DEFLATE_COMPRESSION, L"Unsupported compression method", ERROR);
  ERROR_IF(compressionInfo > WINDOW_32K, L"Unsupported sliding window size", ERROR);

  FLG = getLSBvalue(sourceData, 8);
  check = FLG & 0x1F;
  dict = (FLG & 0x20) >> 5;
  level = (FLG & 0xC0) >> 6;
  ERROR_IF(((ushort)CMF * 256 + FLG) % 32 != check, L"Deflate check error", ERROR);

  if (dict) {
    adler32 = getLSBvalue(sourceData, 32);
  }

  DynamicHuffmanTree literalTree(MAX_LITERAL_NUMBER);
  DynamicHuffmanTree distanceTree(MAX_DISTANCE_NUMBER);
  DynamicHuffmanTree lengthTree(19);

  do {
    literalTree.reset();
    distanceTree.reset();
    lengthTree.reset();

    final = getBit(sourceData);
    blockType = getBit(sourceData);
    blockType = blockType | (getBit(sourceData) << 1);

    if (blockType == BLOCK_NO_COMPRESSION) {
      FAIL(L"Block without compression", ERROR);
    } else {
      if (blockType == BLOCK_DYNAMIC_HUFFMAN) {
        HLIT = getLSBvalue(sourceData, 5) + 257;
        HDIST = getLSBvalue(sourceData, 5) + 1;
        ERROR_IF(HDIST <= 1, L"HDIST <= 1", ERROR);
        HCLEN = getLSBvalue(sourceData, 4) + 4;

        /* Read lengths for code lengths alphabet */
        for (uint i = 0; i < HCLEN; i++) {
          ASSERT(lengthTree.setLength(lengthPosition[i], getLSBvalue(sourceData, 3)));
        }

        ASSERT(lengthTree.genCodes());

        /* Decode lengths for literal/lengths alphabet */
        uint curLiteral = 0;
        do {
          decodedSymbol = decodeSymbol(sourceData, &lengthTree);
          /* Length decoded */
          if (decodedSymbol < 16) {
            /* if it is length */
            ASSERT(literalTree.setLength(curLiteral, decodedSymbol));
            curLiteral++;
          } else {
            uint fillCode = 0;
            uint extraLength = 0;

            /* if it is repeat command */
            switch (decodedSymbol) {
            case 16:
              ERROR_IF(curLiteral == 0, L"curLiteral == 0", ERROR);
              extraLength = getLSBvalue(sourceData, 2) + 3;
              fillCode = literalTree.getLength(curLiteral - 1);
              break;

            case 17:
              extraLength = getLSBvalue(sourceData, 3) + 3;
              fillCode = 0;
              break;

            case 18:
              extraLength = getLSBvalue(sourceData, 7) + 11;
              fillCode = 0;
              break;

            default:
              LOG_ERROR(L"Wrong symbol decoded");
            }

            /* Repeat length */
            ASSERT(literalTree.fill(curLiteral, extraLength, fillCode));
            curLiteral = curLiteral + extraLength;
          }
        } while (curLiteral < HLIT);

        /* Decode distance codes */
        uint curDistance = 0;
        do {
          decodedSymbol = decodeSymbol(sourceData, &lengthTree);

          /* Length decoded */
          if (decodedSymbol < 16) {
            /* if it is length */
            ASSERT(distanceTree.setLength(curDistance, decodedSymbol));
            curDistance++;
          } else {
            uint extraLength = 0;
            uint fillCode = 0;

            switch (decodedSymbol) {
            case 16:
              ERROR_IF(curDistance == 0, L"curDistance == 0", ERROR);
              extraLength = getLSBvalue(sourceData, 2) + 3;
              fillCode = distanceTree.getLength(curDistance - 1);
              break;

            case 17:
              extraLength = getLSBvalue(sourceData, 3) + 3;
              fillCode = 0;
              break;

            case 18:
              extraLength = getLSBvalue(sourceData, 7) + 11;
              fillCode = 0;
              break;

            default:
              LOG_ERROR(L"Wrong symbol decoded");
            }

            ASSERT(distanceTree.fill(curDistance, extraLength, fillCode));
            curDistance = curDistance + extraLength;
          }
        } while (curDistance < HDIST);

        /* Make Huffman table for lengths   */
        ASSERT(literalTree.genCodes());

        /* Make Huffman table for distances */
        ASSERT(distanceTree.genCodes());
      } else {
        /*
            Lit Value    Bits        Codes
            ---------    ----        -----
            0 - 143     8          00110000 through
                      10111111
            144 - 255     9          110010000 through
                      111111111
            256 - 279     7          0000000 through
                      0010111
            280 - 287     8          11000000 through
                      11000111
        */

        /* In case of fixed Huffman tree */
        for (int i = 0; i <= 143; i++) {
          literalTree.setLength(i, 8);
          literalTree.setCode(i, 48 + i);
        }

        for (int i = 144; i <= 255; i++) {
          literalTree.setLength(i, 9);
          literalTree.setCode(i, 400 + (i - 144));
        }

        for (int i = 256; i <= 279; i++) {
          literalTree.setLength(i, 7);
          literalTree.setCode(i, i - 256);
        }

        for (int i = 280; i <= 287; i++) {
          literalTree.setLength(i, 8);
          literalTree.setCode(i, 192 + (i - 280));
        }

        ASSERT(literalTree.prepare());
      }

      /* Decode data stream */
      do {
        /* Decode byte from stream */
        decodedSymbol = decodeSymbol(sourceData, &literalTree);
        if (decodedSymbol < 256) {
          /* If it is literal code and there is a spare place in buffer */
          data.push_back(decodedSymbol);
        } else {
          if (decodedSymbol > 256) {
            /* Decode <length, distance> pair */
            repLength = getLength(sourceData, decodedSymbol);
            if (blockType == BLOCK_FIXED_HUFFMAN) {
              repDistance = getMSBvalue(sourceData, 5);
              repDistance = getDistance(sourceData, repDistance);
            } else {
              /* Decode distance code */
              repDistance = decodeSymbol(sourceData, &distanceTree);
              repDistance = getDistance(sourceData, repDistance);
            }
            repeat(data, repLength, repDistance);
          }
        }
      } while (decodedSymbol != 256);
    }

  } while (!final);

  return OK;
}

}
