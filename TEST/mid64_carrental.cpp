#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(){
    int K,N,C,P,W;
    long long ans = 100000000000;
    cin >> K >>N;
    vector <int> cpw;
    vector <int> product;
    for(int i=0;i<K;i++){
        cin >> C >> P >> W;
        cpw.push_back(C);
        cpw.push_back(P);
        cpw.push_back(W);
    }
    int tmp;
    for(int i=0;i<N;i++){
        cin >> tmp;
        product.push_back(tmp);
    }

    int ic = 0 ,ip = 1,iw = 2;
    for(int i=0;i<K;i++){
        if(*max_element(product.begin(), product.end()) > cpw[iw]){
            ic += 3;
            ip += 3;
            iw += 3;
            continue;
        }
        int count = 1;
        int tmpto = 0;
        for(int j=0;j<N;j++){
            tmpto += product[j];
            if(tmpto > cpw[iw]){
                count += 1;
                tmpto = product[j];
            }
        }
        int x = cpw[ic]+(count*cpw[ip]);
        if(x < ans){
            ans = x;
        }
        ic += 3;
        ip += 3;
        iw += 3;
    }
    cout << ans;
    return 0;
}