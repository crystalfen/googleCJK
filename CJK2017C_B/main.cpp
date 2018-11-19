#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    // 1.定义文件输入输出对象
    ifstream infile;
    infile.open("B-large-practice.in");
    ofstream outfile;
    outfile.open("B-large-practice.out");

    // 2.读入样例的个数
    int number;
    infile>>number;
    cout<<number<<endl;

    // 3.逐个样例进行判断
    for(int i = 0; i < number; i++)
    {
        bool canwin = true; //默认游戏能赢
        // 3.1 读入第i个样例的长度
        int length;
        infile>>length;
        cout<<length<<endl;

        // 3.2 读入第i个样例的模型,存入矩阵model中。并用rn记录每一行出现X的个数，cn记录每一列出现的X的个数
        int model[length][length]; //矩阵model存储第i样例的模型形状，并且，‘X'用数字1表示，’.'用数字0表示
        vector<int>rn(length, 0); //定义rn，记录每一行出现X的个数。初始化为0
        vector<int>cn(length,0); //定义cn,记录每一列出现X的个数，初始化为0
        for(int r = 0; r < length; r++)
        {
            string data;
            infile>>data;
            cout<<data<<endl;
            for(int c = 0; c < length; c++)
            {
                if(data[c] == 'X')
                {
                    model[r][c] = 1;
                    rn[r]++;
                    cn[c]++;
                }
                else
                    model[r][c] = 0;


            }
        }

        // 3.3. 游戏能够赢的关键是：有且只有一行和一列存在1个X,并且该行该列在X处相交。其余每行每列只能有2个X。如果不满足上述条件，输出IMPOSSIBLE。canwin = false
        // 3.3.1 先找到有一个X的的行和列
        int p = 0, q = 0;
        while(p < length && rn[p] != 1)
            p++;
        while(q < length && cn[q] != 1)
            q++;
        if(p == length || q == length) // 如果没有一行或一列只有一个X的时候，游戏不能赢
        {
            cout<<"Case #" << i + 1 << ": IMPOSSSIBLE" ;
            outfile<<"Case #"<< i + 1 <<": IMPOSSIBLE";
            outfile<<endl;
            continue;
        }
        // 3.3.2 判断是否只有一行和一列存在一个X，其余行和列全是只有两个X
        sort(rn.begin(), rn.end());
        sort(cn.begin(), cn.end());
        if((rn[0] != 1) || (cn[0] != 1) || (model[p][q] !=1) )
            canwin = false;
        for(int j = 1; canwin && j < length; j++)
        {
            if(rn[j] != 2 || cn[j] != 2)
                canwin = false;
        }

        // 3.4. 如果满足，进一步判断：对于任意有两个X的行，都存在另一行的形状和该行完全一样。即该两行的4个‘X’刚好组成一个矩形时，游戏能成功，否则不能。
        if(canwin)
        {
            // 3.4.1 定义bool向量fr和fc，fr记录某行是否被访问过，fc记录某列是否被访问过。初始化为没访问过。
            vector<bool> fr(length, false);
            vector<bool> fc(length, false);
            // 3.4.2 先让只有1个X的行和列标记为访问过了
            fr[p] = fc[q] = true;
            // 3.4.3 从第0行开始访问具有两个X的行。每次要找两行形状一样的行，则需要找length/2次能遍历完。（length为奇数）
            for(int t = 0; canwin && t < length/2; t++)
            {
                // 3.4.3.1 从头开始找到未被访问到的一行
                int i0 = 0;
                while(fr[i0]) // 如果i0行被访问过了，i0++,直到该行未被访问过
                    i0++;

                // 3.4.3.2 找到该行第一次出现X的位置
                int j0 = 0;
                while(!model[i0][j0])
                    j0++;

                // 3.4.3.3 找到该行第二次出现X的位置
                int j1 = j0 + 1;
                while(!model[i0][j1])
                    j1++;

                // 3.4.3.4 如果这两列至少有一个被访问过了，游戏不能赢，canwin = false
                if(fc[j0] || fc[j1])
                {
                    canwin = false;
                    break;
                }

                // 3.4.3.5 找到第j0列第二次出现X的位置
                int i1 = 0;
                while(!model[i1][j0] || i1 == i0)
                    i1++;
                // 3.4.3.6 如果该行已经被访问过了或者该行的第j1列不等于X时，则游戏不能赢，canwin=false
                if(fr[i1] || (model[i1][j1] != 1))
                {
                    canwin = false;
                    break;
                }
                // 3.4.3.7 标记刚刚访问过的两列和两行
                fr[i0] = fr[i1] = true;
                fc[j0] = fc[j1] = true;


            }
        }
        if(canwin)
        {
            cout<<"Case #" << i + 1 << ": POSSSIBLE" ;
            outfile<<"Case #"<< i + 1 <<": POSSIBLE";
        }
        else
        {
            cout<<"Case #" << i + 1 << ": IMPOSSSIBLE" ;
            outfile<<"Case #"<< i + 1 <<": IMPOSSIBLE";
        }

        cout<<endl;
        outfile<<endl;
    }
    return 0;
}
