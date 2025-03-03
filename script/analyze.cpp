#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

const int N = 1e6+5;
ofstream outFile("result.txt");
float sum = 0;

void QuickSort(vector<double>& a, int l, int r){	
    if(l >= r) return ;
    double pivot = a[(l + r) /2];
    int i=l,j=r;
    while(i <= j){
        while (a[i] < pivot) i++;
        while(a[j] > pivot) j--;
        if( i <= j) {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    QuickSort(a,l,j);
    QuickSort(a,i,r);
}
void heapify(vector<double>& a, int n, int i) {
    while (true) {
        int largest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < n && a[left] > a[largest]) largest = left;
        if (right < n && a[right] > a[largest]) largest = right;

        if (largest == i) break;  

        swap(a[i], a[largest]);
        i = largest;
    }
}
void HeapSort(vector<double>& a, int nothing, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(a, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
//void Merge(vector<double>& a, int left,int mid, int right) {
//    int n1 = mid - left + 1;
//    int n2 = right - mid;
//    vector<double> L(n1), R(n2);
//    for (int i = 0; i < n1; i++)
//        L[i] = a[left + i];
//    for (int j = 0; j < n2; j++)
//        R[j] = a[mid + 1 + j];
//    int i = 0, j = 0;
//    int k = left;
//    while (i < n1 && j < n2) {
//        if (L[i] <= R[j]) {
//            a[k] = L[i];
//            i++;
//        }
//        else {
//            a[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//    while (i < n1) {
//        a[k] = L[i];
//        i++;
//        k++;
//    }
//    while (j < n2) {
//        a[k] = R[j];
//        j++;
//        k++;
//    }
//}
void Merge(vector<double>& a, int left, int mid, int right) {
    inplace_merge(a.begin() + left, a.begin() + mid + 1, a.begin() + right + 1);
}
void MergeSort(vector<double>& a, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
}
void analyze(void (*sortFunc)(vector<double>&, int, int),string filename){	
	vector<double> a(N);
	ifstream inFile(filename);
	for (int i = 0; i < N; i++) {
		inFile >> a[i];
	}
	inFile.close();
    auto start = high_resolution_clock::now();
    sortFunc(a, 0, N-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
    int t = duration.count();
    outFile << t << " ms" << "\n";
	cout << t << " ms" << "\n";
	sum += t;

}
void run(void (*sortFunc)(vector<double>&, int, int), string name){
	outFile << name << "\n";
	cout << name << "\n";
    outFile << "Ordered Asc: ";
    cout << "Ordered Asc: ";
    analyze(sortFunc, "ordered_asc.txt");
    outFile << "Ordered Desc: ";
    cout << "Ordered Desc: ";
    analyze(sortFunc, "ordered_desc.txt");
    for (int i = 1; i <= 8; i++) {
    	string index = to_string(i);
    	string filename = "unordered_" + index + ".txt";
    	outFile << "Unordered " + index + ": ";
    	cout << "Unordered " + index + ": ";
    	analyze(sortFunc, filename);
	}
	outFile << "\n";
	outFile <<  "Average time: "<< sum/10 << "ms" << "\n";
	cout <<  "Average time: "<< sum/10 << "ms" << "\n";
	sum = 0;
}
void analyzeC(string filename){	
	vector<double> a(N);
	ifstream inFile(filename);
	for (int i = 0; i < N; i++) {
		inFile >> a[i];
	}
	inFile.close();
    auto start = high_resolution_clock::now();
    sort(a.begin(), a.end());
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);  
    int t = duration.count();
    outFile << t << " ms" << "\n";
	cout << t << " ms" << "\n";
	sum += t;
}
void runSortC(string name){
	outFile << name << "\n";
	cout << name << "\n";
    outFile << "Ordered Asc: ";
    cout << "Ordered Asc: ";
    analyzeC("ordered_asc.txt");
    outFile << "Ordered Desc: ";
    cout << "Ordered Desc: ";
    analyzeC("ordered_desc.txt");
    for (int i = 1; i <= 8; i++) {
    	string index = to_string(i);
    	string filename = "unordered_" + index + ".txt";
    	outFile << "Unordered " + index + ": ";
    	cout << "Unordered " + index + ": ";
    	analyzeC(filename);
	}
	outFile << "\n";
	outFile << "Average time: "<< sum/10 << "ms" << "\n";
	cout << "Average time: "<< sum/10 << "ms" << "\n";
	sum = 0;
}
int main()
{
    run(QuickSort,"QuickSort");
	cout << "\n";
    run(HeapSort,"HeapSort");
    cout << "\n";
    run(MergeSort,"MergeSort");
	cout << "\n";
    runSortC("sort (C++)");
	cout << "\n";
    outFile.close();
    system("python sort_numpy.py");
    cout << "Analyzed successfully!!";
    return 0;
}
