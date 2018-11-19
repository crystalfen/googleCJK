#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    // 1.定义变量
    string data; // data存储从文件中逐行读取的字符串。也就是编码后的字符串
    int number; // 记录样例的个数
    int store[100];  // 存储编码后的数字
    int original[100]; // 存储原始的字符串对应的数字

    // 2.定义输入输出文件操作
    ifstream infile;
    infile.open("A-small-practice.in");
    ofstream outfile;
    outfile.open("A-small-practice.out");

    infile>>number;  //获取输入文件的第一行内容，即样例的数目
    cout<<number<<endl; //控制台输出，为了监测程序运行是否正确，和比赛没有关系

    // 3.循环操作每一个样例
    for(int i = 0; i < number; i++)
    {
        // 3.1 读入第i行的字符串数据
        infile>>data;
        int length = data.length();
        cout<<data<<"----";
        // 3.2 将字符串转化成数字
        for(int j = 0; j < length; j++)
        {
            store[j] = int(data[j]) - 65; //强制类型转化， 将A-Z转化成0-25的数字

        }
        // 3.3 进行解码。判断原字符串的长度。若为奇数，则没有惟一的编码，直接输出为AMBIGUOUS。若为偶数，解码
        if(length % 2 == 0)
            {
              // 3.3.1 正向传播，得出第1个，3,5，，，，的原字符串的数字
              original[1] = store[0];
              for(int k = 3; k < length; k = k+2)
              {
                  int curr = store[k-1]-original[k-2];
                  original[k] = curr>0 ? curr : curr + 26;
              }
              // 3.3.2 反向传播，得出第N-2，第N-4,4,2,0个原字符串的数字
              original[length-2] = store[length-1];
              for(int k = length-4; k>=0; k = k-2)
              {
                  int curr = store[k+1]-original[k+2];
                  original[k] =  curr>0 ? curr : curr + 26;
              }
              // 3.3.3 先输出每行的标记
              cout<<"Case #" << i + 1 << ": " ;
              outfile<<"Case #"<< i + 1 <<": ";
              // 3.3.4 将获得的原字符串对应的数字数组逐个转化成char型并输出
              for(int j = 0; j < length; j++)
              {
                  int c = original[j] + 65;
                  outfile<<(char)c;
                  cout<<(char)c;
              }
            }
        else
            {
               cout<< "Case #" << i + 1 << ": AMBIGUOUS";
               outfile << "Case #" << i + 1 << ": AMBIGUOUS";
            }
        outfile<<endl;
        cout<<endl;
    }

    return 0;
}
