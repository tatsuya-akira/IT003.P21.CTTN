#include <bits/stdc++.h>
using namespace std;

const int N = 1e6; 

int main() {
    mt19937 rng(random_device{}());
    uniform_real_distribution<double> dist(-N, N);
    vector<double> arr;
    for (int i = 0; i < N; i++) {
    	arr.push_back(dist(rng));
	}
	sort(arr.begin(),arr.end());
	ofstream Asc("/test/ordered_asc.txt");
	for (double num : arr) {
        Asc << fixed << setprecision(6) << num << " ";
    }
    Asc.close();
    cout << "Generated file: " << "ordered_asc.txt" << "\n";
    sort(arr.rbegin(),arr.rend());
	ofstream Desc("/test/ordered_desc.txt");
	for (double num : arr) {
        Desc << fixed << setprecision(6) << num << " ";
    }
    Desc.close();
    cout << "Generated file: " << "/test/ordered_desc.txt" << "\n";
    for (int i = 1; i <= 8; i++) {
        string filename = "/test/unordered_" + to_string(i) + ".txt";
        ofstream Unordered(filename);
        for (int j = 0; j < N; j++) {
            Unordered << fixed << setprecision(6) << dist(rng) << " ";
        }

        Unordered.close();
        cout << "Generated file: " << filename << "\n";
    }
    cout << "All files generated successfully!" << "\n";
    return 0;
}

