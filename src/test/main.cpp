#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

void Swap(int &a, int &b) {
  int c = a;a = b;b = c;
}

void InitArray(std::vector<int>& values) {
  for (int i = 0; i < 20; ++i) {
    values.push_back(i);
  }

  unsigned seed = std::chrono::system_clock::now()
    .time_since_epoch().count();
  std::shuffle(values.begin(), values.end()
    , std::default_random_engine(seed));
}

void PrintArray(const std::vector<int>& values) {
  for (auto& it : values) {
    std::cout << it << " ";
  }
  std::cout << "\n";
}

void Bubble(std::vector<int>& values) {
  for (int i = 0; i < values.size(); i++) {
    for (int j = 0; j < values.size() - 1 - i; j++) {
      if (values[j] > values[j + 1]) {
        Swap(values[j], values[j + 1]);
      }
    }
  }
}

void Select(std::vector<int>& values) {
  for (int i = 0; i < values.size(); i++) {
    int max_index = 0;
    for (int j = 0; j < values.size() - i; j++) {
      max_index = (values[j] > values[max_index]) ? j : max_index;
    }
    if (max_index != values.size() - i - 1) {
      Swap(values[values.size() - i - 1], values[max_index]);
    }
  }
}

void Insert(std::vector<int>& values) {
  for (int i = 1; i < values.size(); i++) {
    int j = i;
    int value = values[j];
    for (; j > 0 && values[j-1] > value; j--) {
      values[j] = values[j-1];
    }
    if (j != i) {
      values[j] = value;
    }
  }
}

void Shell(std::vector<int>& values) {
  int step = values.size();
  while (step /= 2) {
    for (int i = step; i < values.size(); i++) {
      int j = i;
      int value = values[i];
      for (; j >= step && values[j - step] > value; j -= step) {
        values[j] = values[j - step];
      }
      if (j != i) {
        values[j] = value;
      }
    }
  }
}
int Pivot(std::vector<int>& values, int left, int right) {
  int pivot = left;
  int i = left, j = right;
  for (;i < j;) {
    while (i < j && values[pivot] < values[j]) j--;
    while (i < j && values[pivot] > values[i]) i++;
    Swap(values[j], values[i]);
  }

  Swap(values[pivot], values[i]);
  pivot = i;

  return pivot;
}

void Quick(std::vector<int>& values, int left, int right) {
  if (left > right)
    return;

  int pivot = Pivot(values, left, right);
  Quick(values, left, pivot - 1);
  Quick(values, pivot + 1, right);
}

void Quick(std::vector<int>& values) {
  Quick(values, 0, values.size() - 1);
}

void Merge(std::vector<int>& merged, const std::vector<int>& lefts
  , const std::vector<int>& rights) {
  merged.resize(lefts.size() + rights.size());
  int index = 0;
  int i = 0, j = 0;
  for (; i < lefts.size() && j < rights.size();) {
    merged[index++] = (lefts[i] < rights[j]) ? lefts[i++] : rights[j++];
  }

  for (; i < lefts.size(); i++) {
    merged[index++] = lefts[i];
  }

  for (; j < rights.size(); j++) {
    merged[index++] = rights[j];
  }
}

void MergeSort(std::vector<int>& values, std::vector<int>& merged, int left, int right) {
  if (left >= right) {
    merged.resize(1);
    merged[0] = values[left];
    return;
  }

  int mid = (left + right) / 2;
  std::vector<int> lefts, rights;
  MergeSort(values, lefts, left, mid);
  MergeSort(values, rights, mid + 1, right);

  Merge(merged, lefts, rights);
}

void Merge(std::vector<int>& values) {
  std::vector<int> merges;
  MergeSort(values, merges, 0, values.size() - 1);
  for (int i = 0; i < merges.size(); i++) {
    values[i] = merges[i];
  }
}

void Heap(std::vector<int>& values) {
}

int main(int argc, char* argv[]) {
  std::vector<int> values;

  InitArray(values);
  PrintArray(values);
  //Bubble(values);
  //Select(values);
  //Insert(values);
  Shell(values);
  //Quick(values);
  //Merge(values);
  PrintArray(values);

  system("pause");

  return 0;
}