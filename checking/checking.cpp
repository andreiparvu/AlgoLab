#include <iostream>
#include <vector>

using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
  int nrTests;

  cin >> nrTests;

  while (nrTests--) {
    int nrC, nrSamples;

    cin >> nrC >> nrSamples;

    vector<int> d(10005, inf);

    d[0] = 0;

    for (int i = 0; i < nrC; i++) {
      int value;
      cin >> value;

      for (int j = 0; j <= 10000; j++) {
        if (d[j] != inf && j + value <= 10000) {
          if (d[j + value] > d[j] + 1) {
            d[j + value] = d[j] + 1;
          }
        }
      }
    }
    for (int i = 0; i < nrSamples; i++) {
      int sample;
      cin >> sample;
      if (d[sample] == inf) {
        cout << "not possible\n";
      } else {
        cout << d[sample] << "\n";
      }
    }
  }

  return 0;
}

