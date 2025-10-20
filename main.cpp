#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void inversedBubbleSort(vector<int>& arr) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr[i] < arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int getAmount(bool testing = true) {
    if(testing) {
        return 230;
    }

    cout << "Enter the amount to change (0 to quit): ";
    int amount;
    cin >> amount;
    return amount;
}

vector<int> getCoins(bool testing = true) {
    if(testing) {
        return {100, 50, 25, 10, 5, 1};
    }

    cout << "Enter coin values and end it with zero (example: 1 5 10 25 50 100 0): ";
    vector<int> coins;
    int coin;
    while (cin >> coin) {
        if(coin <= 0) {
            break;
        }
        coins.push_back(coin);
    }

    inversedBubbleSort(coins);

    return coins;
}

vector<int> greedyChange(int amount, const vector<int>& coins) {
    vector<int> result;
    for (auto coin: coins) {
        while (amount >= coin) {
            amount -= coin;
            result.push_back(coin);
        }
    }
    if(amount > 0) {
        cout << "Cannot provide exact change for the given amount with the provided coins using the greedy algorithm." << endl;
        result = {};
    }
    return result;
}

void printChange(const vector<int>& change) {
    if (change.empty()) {
        cout << "No change to give." << endl;
        return;
    }
    cout << "Change given: ";
    int currentCoinValue = change[0];
    int currentCoinCount = 0;
    for (auto coin: change) {
        if (coin == currentCoinValue) {
            currentCoinCount++;
        } else {
            cout << currentCoinValue << " x " << currentCoinCount << ", ";
            currentCoinValue = coin;
            currentCoinCount = 1;
        }
    }
    cout << currentCoinValue << " x " << currentCoinCount << endl;
    cout << "Total coins given: " << change.size() << endl;
}

int coinChange(vector<int>& coins, int n) {
    int dp[++n];
    dp[0] = 0;

    sort(begin(coins), end(coins));

    for (int i = 1; i < n; i++) {
        dp[i] = INT_MAX;
        for (int c: coins) {
            if (i - c < 0) break;
            if (dp[i - c] != INT_MAX) dp[i] = min(dp[i], 1 + dp[i - c]);
        }
    }
    return dp[--n] == INT_MAX ? -1 : dp[n];
}

int main() {
    bool testing = false; 

    do {
        int amount = getAmount(testing);
        if(amount <= 0) {
            break;
        }
        vector<int> coins = getCoins(testing);
        vector<int> change = greedyChange(amount, coins);
        
        int minCoins = coinChange(coins, amount);
        cout << endl;
        cout << "Minimum number of coins needed (dynamic programming): " << minCoins << endl;
        
        if(change.empty()) {
            continue;
        }

        cout << endl;
        printChange(change);
        cout << endl;

    } while (!testing);

    return 0;
}