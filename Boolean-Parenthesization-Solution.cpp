##################################################################################  Question  ################################################################################################################################

Given a boolean expression s of length n with following symbols.
Symbols
    'T' ---> true
    'F' ---> false
and following operators filled between symbols
Operators
    &   ---> boolean AND
    |   ---> boolean OR
    ^   ---> boolean XOR
Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.

Note: The answer can be large, so return it with modulo 1003

Example 1:

Input: 
n = 7
s = T|T&F^T
Output: 
4
Explaination: 
The expression evaluates to true in 4 ways ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T)).
Example 2:

Input: 
n = 5
s = T^F|F
Output: 
2
Explaination: 
((T^F)|F) and (T^(F|F)) are the only ways.
Your Task:
You do not need to read input or print anything. Your task is to complete the function countWays() which takes n and s as input parameters and returns number of possible ways modulo 1003.

Expected Time Complexity: O(n3)
Expected Auxiliary Space: O(n2)

Constraints:
1 ≤ n ≤ 200 



##################################################################################  Solution  ################################################################################################################################
//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution{
public:
    int countWays(int n, string s){
         int mod = 1003;
        vector<vector<int>> dp_true(n, vector<int>(n, 0));
        vector<vector<int>> dp_false(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            if (s[i] == 'T') {
                dp_true[i][i] = 1;
            } else {
                dp_false[i][i] = 1;
            }
        }
        for (int l = 3; l <= n; l += 2) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;
                for (int k = i + 1; k < j; k += 2) {
                    if (s[k] == '&') {
                        dp_true[i][j] += dp_true[i][k - 1] * dp_true[k + 1][j];
                        dp_false[i][j] += dp_true[i][k - 1] * dp_false[k + 1][j] + dp_false[i][k - 1] * dp_true[k + 1][j] + dp_false[i][k - 1] * dp_false[k + 1][j];
                    } else if (s[k] == '|') {
                        dp_true[i][j] += dp_true[i][k - 1] * dp_false[k + 1][j] + dp_false[i][k - 1] * dp_true[k + 1][j] + dp_true[i][k - 1] * dp_true[k + 1][j];
                        dp_false[i][j] += dp_false[i][k - 1] * dp_false[k + 1][j];
                    } else if (s[k] == '^') {
                        dp_true[i][j] += dp_true[i][k - 1] * dp_false[k + 1][j] + dp_false[i][k - 1] * dp_true[k + 1][j];
                        dp_false[i][j] += dp_true[i][k - 1] * dp_true[k + 1][j] + dp_false[i][k - 1] * dp_false[k + 1][j];
                    }
    
                    dp_true[i][j] %= mod;
                    dp_false[i][j] %= mod;
                }
            }
        }
        return dp_true[0][n - 1] % mod;
    }
};

//{ Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        
        Solution ob;
        cout<<ob.countWays(n, s)<<"\n";
    }
    return 0;
}
// } Driver Code Ends


