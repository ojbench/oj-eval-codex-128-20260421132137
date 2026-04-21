#include <bits/stdc++.h>
using namespace std;

static bool win(const array<string,3>& b, char ch){
    for(int i=0;i<3;i++){
        if(b[i][0]==ch && b[i][1]==ch && b[i][2]==ch) return true; // row
        if(b[0][i]==ch && b[1][i]==ch && b[2][i]==ch) return true; // col
    }
    if(b[0][0]==ch && b[1][1]==ch && b[2][2]==ch) return true;
    if(b[0][2]==ch && b[1][1]==ch && b[2][0]==ch) return true;
    return false;
}

static bool plausible_last_move(array<string,3> b, char ch){
    // Try removing one piece of ch so that no one is winning
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(b[i][j]==ch){
                char old = b[i][j];
                b[i][j] = '-';
                bool xw = win(b,'x');
                bool ow = win(b,'o');
                if(!xw && !ow) return true;
                b[i][j] = old;
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<string,3> b;
    for(int i=0;i<3;i++){
        if(!(cin >> b[i])) return 0; // no input
        if((int)b[i].size()!=3){
            cout << "invalid\n";
            return 0;
        }
        for(char c: b[i]){
            if(!(c=='x'||c=='o'||c=='-')){
                cout << "invalid\n";
                return 0;
            }
        }
    }

    int cx=0, co=0, ce=0;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++){
        char c=b[i][j];
        if(c=='x') cx++; else if(c=='o') co++; else ce++;
    }

    // Turn count validity: x starts, alternate
    if(!(co <= cx && cx <= co+1)){
        cout << "invalid\n";
        return 0;
    }

    bool xw = win(b,'x');
    bool ow = win(b,'o');

    // Both cannot win
    if(xw && ow){
        cout << "invalid\n";
        return 0;
    }

    if(xw){
        // x must have just moved
        if(cx != co+1){
            cout << "invalid\n";
            return 0;
        }
        // Game should stop immediately on win
        if(!plausible_last_move(b,'x')){
            cout << "invalid\n";
            return 0;
        }
        cout << "win\n";
        return 0;
    }

    if(ow){
        // o must have just moved
        if(cx != co){
            cout << "invalid\n";
            return 0;
        }
        if(!plausible_last_move(b,'o')){
            cout << "invalid\n";
            return 0;
        }
        cout << "lose\n";
        return 0;
    }

    // No winner
    if(ce > 0) cout << "ongoing\n";
    else cout << "tie\n";
    return 0;
}
