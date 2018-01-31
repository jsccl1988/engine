#ifndef _UTILS_H
#define _UTILS_H

#include <list>
#include <iostream>
#include <string>
#include <vector>

template <class T>
inline void Swap(T &a, T &b) {
  T c = a; a = b; b = c;
}

template <class T>
inline int Max(const T& a,const T& b) {
  return (a > b) ? a : b;
}

template <class T>
inline int Min(const T& a, const T& b) {
  return (a < b) ? a : b;
}

template <class T>
void PrintArray(const std::vector<T>& values, const std::string& tag,
  int start = -1, int end = -1) {
  if (start == -1) {
    start = 0;
  }

  if (end == -1) {
    end = values.size() - 1;
  }

  std::cout << "["<< tag <<"]";
  for (int i = start; i <= end; i++) {
    std::cout << values[i] << " ";
  }
  std::cout << "\n";
}

template <class T>
void Print(const T& data, const std::string& tag) {
  std::cout << "[" << tag << "]" << data << std::endl;
}

void PrintString(std::string &str, const std::string& tag);


void InitArray(std::vector<int>& values);

void MaxSubArrayKadane(std::vector<int>& values);
void MaxSubArrayDP(std::vector<int>& values);

std::string LCS(const std::string &left, const std::string &right);
int EditDistance(const std::string &left, const std::string &right);

void Reverse(std::string &str, int start = -1, int end = -1);
void Shift(std::string &str, int k);
void TriCluster(std::string &str);

int SumComponent(std::list<int>& components, int n, int sum);

#endif // !_UTILS_H

