//
// Created by Gubaidan on 2018/9/6.
////
//
//#include <iostream>
//#include <algorithm>
//#include <stdio.h>
//#include <vector>
//using namespace std;
//const int maxn=1e5+100;
//vector<int>G[maxn];
//int max_deep;
//void dfs(int now,int fa,int deep)
//{
//    max_deep=max(max_deep,deep);
//    for(int i=0;i<(int)G[now].size();i++)
//    {
//        int to=G[now][i];
//        if(to==fa) continue;
//        dfs(to,now,deep+1);
//    }
//}
//int main()
//{
//    int n;
//    while(cin>>n)
//    {
//        for(int i=0;i<maxn;i++)
//            G[i].clear();
//
//        for(int i=1;i<n;i++)
//        {
//            int x,y;
//            cin>>x>>y;
//            G[x].push_back(y);
//            G[y].push_back(x);
//        }
//        max_deep=0;
//        dfs(1,-1,0);
//        cout<<2*(n-1)-max_deep;
//    }
//    return 0;
//}

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
//    int vote;
//    cin >> vote;
//    for (int i = 0; i < vote; i++)
//    {
//        long vote, k;
//        cin >> vote >> k;
//        cout << 0 << " ";
//        if (k < (vote + 1) / 2) cout << ((k - 1 < 0) ? 0 : k - 1) << endl;
//        else
//        {
//            if (vote % 2) {
//                int i, j;
//                i = static_cast<int>(vote / 2);
//                j = i + 1;
//                cout << i - k + j << endl;
//            }
//            else
//            {
//                int i, j;
//                i = static_cast<int>(vote / 2);
//                j = i;
//                cout << i - k + j - (k==vote/2?1:0)<< endl;
//            }
//        }
//    }
//    return 0;

    long long i = 2;
    print("%d", i);
}