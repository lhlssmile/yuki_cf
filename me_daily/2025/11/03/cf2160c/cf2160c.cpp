#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
using namespace std;

string toBinary(long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = (n % 2 == 0 ? "0" : "1") + result;
        n /= 2;
    }
    return result;
}

string padWithZeros(const string& binary, int length) {
    if (binary.length() >= length) return binary;
    return string(length - binary.length(), '0') + binary;
}

bool isPalindrome(const string& s) {
    string reversed = s;
    reverse(reversed.begin(), reversed.end());
    return s == reversed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long n;
        cin >> n;
        
        string binary = toBinary(n);
        string ans = "NO";
        
        for (int length = 1; length < 64; length++) {
            if (binary.length() <= length) {
                string padded = padWithZeros(binary, length);
                
                bool isValidPalindrome = isPalindrome(padded);
                
                // If odd length, middle bit must be 0
                if (length % 2 == 1) {
                    char middleChar = padded[length / 2];
                    isValidPalindrome = isValidPalindrome && (middleChar == '0');
                }
                
                if (isValidPalindrome) {
                    ans = "YES";
                    break;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}