#include <vector>

#include "sort.h"
#include "utils.h"
void test_sort() {
  std::vector<int> values;

  InitArray(values);
  PrintArray(values, "origin");
  int key = values[0];
  //MaxSubArrayKadane(values);
  //MaxSubArrayDP(values);
  //Bubble(values);
  //Select(values);
  //Insert(values);
  //Shell(values);
  //Quick(values);
  //Merge(values);
  //Heap(values);
  //OddEven(values);
  //BinarySearch(values, key);
  PrintArray(values, "sorted");
}

void test_utils() {
  std::string str = "ababcefd";
  PrintString(str, "origin");
  Reverse(str);
  PrintString(str, "reverse");
  Reverse(str);
  PrintString(str, "reverse");
  Shift(str, 2);
  PrintString(str, "shift");

  std::string  left = "bbaabcdd";
  std::string right = "ababcefdg";
  PrintString(left, "left");
  PrintString(right, "right");
  PrintString(LCS(left, right), "lcs");
  Print(EditDistance(left, right), "edit distance");

  std::string tri = "ababcccbbaa";
  TriCluster(tri);
  PrintString(tri, "tri cluster");

  std::list<int> components;
  Print(SumComponent(components, 5, 6), "componet number");
}

int main(int argc, char* argv[]) {
  test_sort();
  test_utils();

  system("pause");
  return 0;
}