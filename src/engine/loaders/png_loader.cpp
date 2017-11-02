// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>

#include "common.h"
#include "loaders/png_loader.h"

namespace ve {

PNGLoader::PNGLoader() {
}

void PNGLoader::reverseLongInt(unsigned int *x) {
  unsigned int a, b, c, d, v;

  v = *x;
  a = (v >> 24) & 0x000000FF;
  b = (v >> 16) & 0x000000FF;
  c = (v >> 8) & 0x000000FF;
  d = v & 0x000000FF;
  *x = a | (b << 8) | (c << 16) | (d << 24);
}

void PNGLoader::reverseWord(unsigned short *x) {
  unsigned short a, b, v;
  v = *x;
  a = (v >> 8) & 0x00FF;
  b = v & 0x00FF;
  *x = a | (b << 8);
}

unsigned int PNGLoader::paethPredictor(unsigned char a, unsigned char b, unsigned char c) {
  unsigned int p, pa, pb, pc;
  // a = left, b = above, c = upper left
  p = a + b - c;        // initial estimate
  pa = abs((int)(p - a));      // distances to a, b, c
  pb = abs((int)(p - b));
  pc = abs((int)(p - c));
  // return nearest of a,b,c,
  // breaking ties in order a,b,c.
  if (pa <= pb && pa <= pc)
    return a;
  else
    if (pb <= pc)
      return b;
    else
      return c;
}

Outcome PNGLoader::load(FILE *source, size_t offset) {
  PNGHeader header;
  PNGHeader rightHeader = { 137, 80, 78, 71, 13, 10, 26, 10 };
  PNGChunk chunk;
  PNGCRC CRC;
  IHDRChunk IHDR;
  int filter;
  fpos_t savePos;

  fseek(source, offset, SEEK_SET);
  fread(&header, 1, sizeof(header), source);
  for (int i = 0; i < 8; i++) {
    ERROR_IF(rightHeader[i] != header[i], L"Wrong header of the file", ERROR);
  }

  std::vector<uchar> inflatedData;

  do {
    /* Read head of chunk and transform Words and LongInt types to most significent byte order */
    fread(&chunk, 1, sizeof(PNGChunk), source);
    reverseLongInt(&chunk.length);
    reverseLongInt(&chunk.type);

    switch (chunk.type) {
    case PNG_CHUNK_IHDR:
      fread(&IHDR, 1, sizeof(IHDRChunk), source);
      reverseLongInt(&IHDR.width);
      reverseLongInt(&IHDR.height);
      width = IHDR.width;
      height = IHDR.height;
      ERROR_IF(IHDR.colorType != PNG_RGB && IHDR.colorType != PNG_RGBA && IHDR.colorType != PNG_GRAYSCALE,
        L"Unsupported color type", ERROR);
      ERROR_IF(IHDR.compressionMethod != PNG_DEFLATE_METHOD, L"Unsupported compression method", ERROR);
      ERROR_IF(IHDR.interlaceMethod != PNG_NO_INTERLACE, L"Unsupported interlace method", ERROR);
      ERROR_IF(IHDR.filterMethod != PNG_5FILTERS, L"Unsupported filter method", ERROR);
      ERROR_IF(IHDR.bitDepth != 8, L"Unsupported bit depth", ERROR);

      switch (IHDR.colorType) {
      case PNG_RGB:
        components = 3;
        break;

      case PNG_RGBA:
        components = 4;
        break;

      case PNG_GRAYSCALE:
        components = 1;
        break;

      default:
        LOG_ERROR(L"Unknown color type");
      }

      /* Allocate memory for texture data */
      data.resize(width * height * components);

      break;

    case PNG_CHUNK_IDAT:
    {
      fgetpos(source, &savePos);

      uchar *buf = new uchar[chunk.length];
      ERROR_IF(fread(buf, chunk.length, 1, source) != 1, L"Read error", IO_ERROR);

      inflatedData.reserve(inflatedData.size() + chunk.length);
      for (uint i = 0; i < chunk.length; i++) {
        inflatedData.push_back(buf[i]);
      }

      delete[] buf;

      fsetpos(source, &savePos);
      fseek(source, chunk.length, SEEK_CUR);
      break;
    }

    default:
      fseek(source, chunk.length, SEEK_CUR);
      break;
    }
    fread(&CRC, 1, sizeof(PNGCRC), source);
  } while (chunk.type != PNG_CHUNK_IEND);

  /* Decompressed */
  vector<uchar> deflatedData;

  /* Compute expected data size, height bytes were added to store filter bytes */
  uint expectedSize = width * height * components + height;
  deflatedData.reserve(expectedSize);

  /* Deflate PNG data */
  CHECK_RESULT(zLib.deflate(deflatedData, inflatedData), L"Deflate failed");

  ERROR_IF(deflatedData.size() != expectedSize,
    L"Decoded data size (" + StringTool::intToStr(deflatedData.size()) + L") exceeds expected " +
    StringTool::intToStr(expectedSize), ERROR);

  /* Set filtered data current position to the first byte */
  uint filteredDataPos = 0;
  uint deflatedDataPos = 0;
  uint pitch = width * components;
  int buf_len = data.size();

  for (int i = 0; i < height; i++) {
    filteredDataPos = (height - i - 1) * pitch;  // i-th row from the bottom
    filter = deflatedData[deflatedDataPos];
    deflatedDataPos++;

    switch (filter) {
    case FILTER_NONE:
      for (uint j = 0; j < pitch; j++) {
        data[filteredDataPos++] = deflatedData[deflatedDataPos++];
      }
      break;

    case FILTER_SUB:
      /* Read first pixel */
      for (int j = 0; j < components; j++) {
        data[filteredDataPos++] = deflatedData[deflatedDataPos++];
      }

      /* Read other pixels */
      for (uint j = 0; j < pitch - components; j++) {
        data[filteredDataPos] = ((uint)deflatedData[deflatedDataPos] +
          (uint)data[filteredDataPos - components]) % 256;
        filteredDataPos++;
        deflatedDataPos++;
      }
      break;

    case FILTER_UP:
      for (uint j = 0; j < pitch; j++) {
        uint tmp = (filteredDataPos + pitch < (uint)buf_len) ?
          (uint)data[filteredDataPos + pitch] : 0;
        data[filteredDataPos] = ((uint)deflatedData[deflatedDataPos] + tmp) % 256;
        filteredDataPos++;
        deflatedDataPos++;
      }
      break;

    case FILTER_AVERAGE:
    {
      /* Read first pixel */
      for (int j = 0; j < components; j++) {
        uint tmp = (filteredDataPos + pitch < (uint)buf_len) ?
          data[filteredDataPos + pitch] : 0;
        data[filteredDataPos] = (uint)deflatedData[deflatedDataPos++] + tmp / 2;
        filteredDataPos++;
      }

      /* Read other pixels */
      for (uint j = 0; j < pitch - components; j++) {
        uint tmp = (filteredDataPos + pitch < (uint)buf_len) ?
          data[filteredDataPos + pitch] : 0;
        data[filteredDataPos] = ((uint)deflatedData[deflatedDataPos] +
          ((uint)data[filteredDataPos - components] +
          (uint)tmp) / 2) % 256;
        filteredDataPos++;
        deflatedDataPos++;
      }
    }
    break;

    case FILTER_PAETH:
      /* Read first pixel */
      for (int j = 0; j < components; j++) {
        uint tmp = (filteredDataPos + pitch < (uint)buf_len) ?
          data[filteredDataPos + pitch] : 0;
        data[filteredDataPos] = (deflatedData[deflatedDataPos] +
          paethPredictor(0, tmp, 0)) % 256;
        filteredDataPos++;
        deflatedDataPos++;
      }

      /* Read other pixels */
      for (uint j = 0; j < pitch - components; j++) {
        uint tmp1 = (filteredDataPos + pitch < (uint)buf_len) ?
          data[filteredDataPos + pitch] : 0;
        uint tmp2 = (filteredDataPos + pitch - components < (uint)buf_len) ?
          data[filteredDataPos + pitch - components] : 0;
        data[filteredDataPos] = (deflatedData[deflatedDataPos]
          + paethPredictor(data[filteredDataPos - components],
          tmp1, tmp2)) % 256;
        filteredDataPos++;
        deflatedDataPos++;
      }
      break;

    default:
      FAIL(L"Unrecognized filter", ERROR);
    }

  }

  return OK;
}

}
