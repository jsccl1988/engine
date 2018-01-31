#ifndef _SORT_H
#define _SORT_H

#include <vector>

void Bubble(std::vector<int>& values);
void Select(std::vector<int>& values);
void Insert(std::vector<int>& values);
void Shell(std::vector<int>& values);
void Quick(std::vector<int>& values);
void Merge(std::vector<int>& values);
void Heap(std::vector<int>& values);
void OddEven(std::vector<int>& values);

void BinarySearch(const std::vector<int>& values, int key);

#endif // !_SORT_H
