#include <iostream>
#include <vector>
#include <deque>
#include <iomanip>

using namespace std;

class StockTickCorrectionSystem {
private:
    deque<double> window;
    int WINDOW_SIZE;

public:
    StockTickCorrectionSystem(int size) {
        WINDOW_SIZE = size;
    }

    // Optimized Bubble Sort
    void bubbleSort(vector<double>& arr) {

        int n = arr.size();

        for (int i = 0; i < n - 1; i++) {

            bool swapped = false;

            for (int j = 0; j < n - i - 1; j++) {

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            // Stop if already sorted
            if (!swapped)
                break;
        }
    }

    // Median Calculation
    double findMedian(vector<double> arr) {

        bubbleSort(arr);

        int n = arr.size();

        if (n % 2 == 0) {
            return (arr[n / 2] + arr[n / 2 - 1]) / 2.0;
        }

        return arr[n / 2];
    }

    // Process each stock tick
    void processTick(double price) {

        // Maintain sliding window
        if (window.size() >= WINDOW_SIZE) {
            window.pop_front();
        }

        window.push_back(price);

        // Copy window into vector
        vector<double> prices(window.begin(), window.end());

        // Calculate corrected price
        double correctedPrice = findMedian(prices);

        cout << fixed << setprecision(2);

        cout << "\n----------------------------------\n";
        cout << "Original Tick Price : ₹" << price << endl;
        cout << "Corrected Price     : ₹" << correctedPrice << endl;

        // Detect spike
        if (price > correctedPrice * 2 ||
            price < correctedPrice * 0.5) {

            cout << " Spike Detected & Corrected!\n";
        }
        else {
            cout << " Normal Tick\n";
        }

        // Display current sliding window
        cout << "Current Window      : ";

        for (double p : window) {
            cout << p << " ";
        }

        cout << endl;
    }
};

int main() {

    int windowSize;
    int totalTicks;

    cout << " REAL-TIME STOCK TICK CORRECTION SYSTEM\n";

    // User input
    cout << "\nEnter Sliding Window Size: ";
    cin >> windowSize;

    cout << "Enter Number of Stock Ticks: ";
    cin >> totalTicks;

    // Create object
    StockTickCorrectionSystem engine(windowSize);

    cout << "\nEnter Stock Prices:\n";

    for (int i = 0; i < totalTicks; i++) {

        double tick;
        cin >> tick;

        engine.processTick(tick);
    }

    cout << "\n Processing Completed Successfully.\n";

    return 0;
}