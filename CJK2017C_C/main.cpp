#include <iostream>
#include<fstream>
#include<vector>
using namespace std;



int main()
{
    // 1. �����ļ������������
    ifstream infile;
    infile.open("C-small-practice.in");
    ofstream outfile;
    outfile.open("C-small-practice.out");

    // 2. ���������ĸ���
    int number;
    infile>>number;
    cout<<number<<endl;

    // 3. �����������
    for(int i = 0; i < number; i++)
    {
        // 3.1 ���������¼�ҵķ���
        int myscore;
        // 3.2 ����С������
        int N;
        infile>>N;
        cout<<"N: "<<N<<endl;
        // 3.3 ������Ŀ����
        int M;
        infile>>M;
        cout<<"M: "<<M<<endl;

        // 3.4 �����,��СΪ[N+1, M]
        vector<string>a;
        for(int j = 0; j < N+1; j++)
        {
            // �����j��С���Ĵ𰸻��Լ��Ĵ�
            string data;
            infile>>data;
            a.push_back(data);
        }

        // 3.5 ��¼a�е�0�к͵�1���д���ͬ�������1��ͬ��0��ͬ����ͳ�ƴ𰸲�һ���ĸ�����
        vector<int> s12;
        int difnum = 0; //ͳ�ƴ𰸲�һ���ĸ���
        for(int c=0; c < M; c++)
        {
            if(a[0][c]==a[1][c])
                s12.push_back(1);
            else
            {
                s12.push_back(0);
                difnum++;

            }
        }

        // 3.6 ��������ۣ���1�������ֻ��һ��С��飬��N=1��ʱ�򡣣�2�������������С���N=2ʱ
        if(N==1) //ֻ��һ��С���
        {
            // 3.6.1 ����С���ķ���������С�������ĸ���
            int score1, error_num;
            infile>>score1;
            cout<<"score1:"<<score1<<endl;
            error_num = M - score1;
            // 3.6.2 �ٷ��������
            if(error_num >= difnum) //���С�������ĸ������ڵ������ǲ�һ���Ĵ𰸵ĸ�������õ�����ǣ����ǲ�һ���Ĵ𰸣�С��鶼�����ˣ����������ˡ���һ���Ĵ���Һ����ķ���һ��������score����ô�ҵķ�����������diffnum��
            {
                myscore = score1 + difnum;
            }
            else  // ������õ�����ǣ������ȫ�����ǲ�һ���Ĵ𰸡�ʣ�µ�����һ���Ĵ𰸣�M-difnum���ȫ�ǶԵġ������ҵķ�����M-difnum+error_num;

            {
                myscore = M - difnum + error_num;
            }


        }
        else if(N==2)
        {
            // 3.6.1 ��¼��һ��С���͵ڶ���С���ķ���
            vector<int> score;
            for(int em = 0; em < N; em++)
            {
                int cur;
                infile>>cur;
                score.push_back(cur);
                cout<<"score ["<<em<<"]: "<<score[em]<<endl;
            }
            // 3.6.2 ������С������ͬ����Ŀ�����Եĸ������ڴ𰸲�ͬ����Ŀ��÷ָߵ�С������Եĸ����͵÷ֵ͵�С������Եĸ���
            int mins, maxs;
            mins = score[0] <= score[1] ? 0 : 1; //��¼�÷ֽ��ٵ�С���ı��
            maxs = score[0] <= score[1] ? 1 : 0; // ��¼�÷ֽϸߵ�С���ı��
            int diffscore12;
            diffscore12 = score[maxs] - score[mins]; //��һ���͵�2��С��鲻ͬ�Ĵ���÷ָߵ�С���ȵ÷ֵ͵�С����������diffscore����
            //ע�⣬��С��鲻ͬ��ÿһ������϶���һ������ȷ�ġ����Կ��Եõ��ڲ�ͬ�Ĵ���÷ָߵ�С������Եĸ���ymax�����÷ֵ͵�С������Եĸ���ymin��
            int ymax, ymin;
            ymax = (difnum + diffscore12)/2;
            ymin = (difnum - diffscore12)/2;
            //���ţ����Եõ�����ͬ�Ĵ������s0��������
            int s0;
            s0 = score[mins] - ymin;

            // 3.6.3 ���ҵĴ𰸺����ǵĴ𰸽��бȽϣ��õ����ܻ�õ���߷�

            // 3.6.3.1 ͳ��4�ֲ�ͬ����µĸ���
            // ����С���A��С���B��ͬ�Ĵ���ҵĴ������ǵ���ͬ�ĸ���Ϊnum1, ��ͬ�ĸ���Ϊnum2
            // ����С���A��С���B��ͬ�Ĵ���ҵĴ���÷ָߵ�С�����ͬ�ĸ���Ϊnum3,��ͬ��Ϊnum4
            int num1=0, num2=0, num3=0, num4=0;
            for(int c = 0; c < M; c++)
            {
                if(s12[c]==1 && a[2][c] == a[1][c])
                {
                    num1++;
                }
                else if(s12[c]==1 && a[2][c] != a[1][c])
                {
                    num2++;
                }
                else if(s12[c]==0 && a[2][c] == a[maxs][c])
                {
                    num3++;
                }
                else if(s12[c]==0 && a[2][c] == a[mins][c])
                {
                    num4++;
                }
            }

            // 3.6.3.2 �ȷֱ�õ���С����Ǵ�һ������Ŀ�����ܵõ�����߷ֺ���С����Ǵ𰸲�һ������Ŀ�����ܵõ�����߷�
            int myscore1, myscore2, myscore3, myscore4;
            // 3.6.3.2.1 С����Ǵ�һ������Ŀ����ܵõ�����߷�Ϊmyscore1+myscore2; (��ϣ�����Ǵ𰸶�һ����������Ǿ����������ˣ�
            if(num1<=s0)
            {
                myscore1 = num1;
                myscore2 = num2-(s0-num1);
            }
            else
            {
                myscore1 = s0;
                myscore2 = num2;

            }
            // 3.6.3.2.2 С����Ǵ𰸲�һ������Ŀ����ܵõ�����߷�Ϊmyscore3+myscore4;����ϣ���͵÷ָߵ�С����һ������Ŀ�У���������������ˣ�
            if(num3 <= ymax)
            {
                myscore3 = num3;
                myscore4 = ymin;
            }
            else
            {
                myscore3 = ymax;
                myscore4 = num4;
            }


            // 3.6.3.3�ҵ����յ���ߵ÷֡�
            myscore = myscore1 + myscore2 + myscore3 + myscore4;
        }
        // 4.����ҵ���ߵ÷�
        cout<<"Case #" << i + 1 << ": " << myscore <<endl;
        outfile<<"Case #"<< i + 1 << ": " << myscore <<endl;
    }


    return 0;

}
