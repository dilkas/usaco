/*
  ID: paulius10
  PROG: shopping
  LANG: C++
*/

#include <fstream>
#include <limits>

using namespace std;

int dot_product(int a[], int b[]) {
  int s = 0;
  for (int i = 0; i < 5; i++) s += a[i] * b[i];
  return s;
}

bool all_fit(int indices[], int req[]) {
  for (int i = 0; i < 5; i++) {
    if (indices[i] < 0 || indices[i] > req[i]) return false;
  }
  return true;
}

int main() {
  ifstream fin("shopping.in");
  int s;
  fin >> s;
  int offer_counts[s];
  int offer_codes[s][5];
  int offer_quantities[s][5];
  int offer_prices[s];
  for (int i = 0; i < s; i++) {
    fin >> offer_counts[i];
    for (int j = 0; j < offer_counts[i]; j++)
      fin >> offer_codes[i][j] >> offer_quantities[i][j];
    fin >> offer_prices[i];
  }
  int b;
  fin >> b;
  int n_options = b + s;
  int codes[b];
  int req[5];
  int prices[n_options];
  int quantities[n_options][5];
  int sum_limit = 1;
  for (int i = 0; i < b; i++) {
    fin >> codes[i] >> req[i] >> prices[i];
    sum_limit += req[i];
    for (int j = 0; j < 5; j++) quantities[i][j] = 0;
    quantities[i][i] = 1;
  }
  fin.close();
  for (int i = b; i < 5; i++) req[i] = 0;
  int multipliers[6];
  multipliers[0] = 1;
  for (int i = 1; i < 6; i++) multipliers[i] = multipliers[i - 1] * (req[i - 1] + 1);
  for (int i = b; i < n_options; i++) {
    for (int j = 0; j < 5; j++) quantities[i][j] = 0;
    for (int j = 0; j < b; j++) {
      for (int k = 0; k < offer_counts[i - b]; k++) {
        if (offer_codes[i - b][k] == codes[j]) {
          quantities[i][j] = offer_quantities[i - b][k];
          break;
        }
      }
    }
    prices[i] = offer_prices[i - b];
  }
  int *price = new int[multipliers[5]];
  price[0] = 0;
  for (int i = 1; i < multipliers[5]; i++) price[i] = numeric_limits<int>::max();
  for (int sum = 0; sum < sum_limit; sum++) {
    for (int i = 0; i <= req[0]; i++) {
      for (int j = 0; j <= req[1]; j++) {
        for (int k = 0; k <= req[2]; k++) {
          for (int l = 0; l <= req[3]; l++) {
            int m = sum - i - j - k - l;
            if (m < 0 || m > req[4]) continue;
            int indices[] = {i, j, k, l, m};
            int index = dot_product(indices, multipliers);
            for (int n = 0; n < n_options; n++) {
              int new_indices[5];
              for (int o = 0; o < 5; o++)
                new_indices[o] = indices[o] - quantities[n][o];
              int new_index = dot_product(new_indices, multipliers);
              if (all_fit(new_indices, req) && price[new_index] != numeric_limits<int>::max()) {
                int new_price = price[new_index] + prices[n];
                if (new_price < price[index])
                  price[index] = new_price;
              }
            }
          }
        }
      }
    }
  }
  ofstream fout("shopping.out");
  fout << price[multipliers[5] - 1] << endl;
  fout.close();
  delete[] price;
  return 0;
}
