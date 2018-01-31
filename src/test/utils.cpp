#include "utils.h"

#include <random>
#include <chrono>
#include <algorithm>

void InitArray(std::vector<int>& values) {
  for (int i = 0; i < 10; ++i) {
    values.push_back(i);
  }

  unsigned seed = std::chrono::system_clock::now()
    .time_since_epoch().count();
  std::shuffle(values.begin(), values.end()
    , std::default_random_engine(seed));
}

void PrintString(std::string &str, const std::string& tag) {
  std::cout << "[" << tag << "]" << str << std::endl;
}

void MaxSubArrayKadane(std::vector<int>& values) {
  int max_sum = -10000000, sum = 0;
  int max_start = 0, second_left = 0, max_end = 0;
  for (int i = 0; i < values.size(); i++) {
    sum += values[i];
    if (sum <= 0) {
      sum = 0;
      second_left = i + 1;
    }

    if (max_sum < sum) {
      max_sum = sum;
      max_start = second_left;
      max_end = i;
    }
  }

  PrintArray(values, "max sub", max_start, max_end);
}

void MaxSubArrayDP(std::vector<int>& values) {
  int max_sum = -10000000, sum = 0;
  int max_start = 0, second_left = 0, max_end = 0;
  for (int i = 0; i < values.size(); i++) {
    sum = (sum + values[i] > values[i]) ? (sum + values[i]) : (max_start = i, values[i]);
    if (max_sum < sum) {
      max_sum = sum;
      max_end = i;
      PrintArray(values, "sub", max_start, max_end);
    }
  }

  PrintArray(values, "max sub", max_start, max_end);
}

std::string LCS(const std::string &_left, const std::string &_right) {
  std::string lcs;
  const std::string &left = (_left.length() < _right.length()) ? _right : _left;
  const std::string &right = (_left.length() < _right.length()) ? _left : _right;

  return lcs;
}

int EditDistance(const std::string &left, const std::string &right) {
  int distance[200][200];
  for (int i = 0; i < left.length(); i++) {
    distance[i][0] = i;
  }

  for (int j = 0; j < right.length(); j++) {
    distance[0][j] = j;
  }

  for (int i = 1; i < left.length(); i++) {
    for (int j = 1; j < right.length(); j++) {
      if (left[i-1] == right[j-1]) {
        distance[i][j] = distance[i - 1][j - 1];
      } else {
        distance[i][j] = 1 + Min(distance[i - 1][j], distance[i][j - 1]);
      }
    }
  }

  return distance[left.length() - 1][right.length() - 1];
}

void Reverse(std::string &str, int start, int end) {
  if (start == -1) {
    start = 0;
  }

  if (end == -1) {
    end = str.length() - 1;
  }

  for (int i = start; i < end - i; i++) {
    Swap(str[i], str[end - i]);
  }
}

void Shift(std::string &str, int k) {
  if (str.length() < k) {
    return;
  }

  Reverse(str, 0, k - 1);
  Reverse(str, k, str.length() - 1);
  Reverse(str, 0, str.length() - 1);
}

void TriCluster(std::string &str) {
  int begin = 0, current = 0, end = str.size() - 1;
  for (;current <= end;) {
    if (str[current] == 'a') {
      Swap(str[begin], str[current]);
      begin++;
      current++;
    } else if(str[current] == 'b') {
      current++;
    } else if (str[current] == 'c') {
      Swap(str[current], str[end]);
      end--;
    }
  }
}

int SumComponent(std::list<int>& components, int n, int sum) {
  if (n <= 0 || sum <= 0)
    return 0;

  if (n == sum) {
    components.reverse();
    for (std::list<int>::iterator iter = components.begin(); iter != components.end(); iter++)
      std::cout << *iter << " + ";
    std::cout << n << std::endl;
    components.reverse();
    return 1;
  }

  components.push_back(n);
  int n_1 = SumComponent(components, n - 1, sum - n);
  components.pop_back();
  int n_0 = SumComponent(components, n - 1, sum);

  return  n_0 + n_1;
}
