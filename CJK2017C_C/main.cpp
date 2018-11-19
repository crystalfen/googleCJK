#include <iostream>
#include<fstream>
#include<vector>
using namespace std;



int main()
{
    // 1. 定义文件输入输出对象
    ifstream infile;
    infile.open("C-small-practice.in");
    ofstream outfile;
    outfile.open("C-small-practice.out");

    // 2. 读入样例的个数
    int number;
    infile>>number;
    cout<<number<<endl;

    // 3. 逐个样例分析
    for(int i = 0; i < number; i++)
    {
        // 3.1 定义变量记录我的分数
        int myscore;
        // 3.2 读入小伙伴个数
        int N;
        infile>>N;
        cout<<"N: "<<N<<endl;
        // 3.3 读入题目个数
        int M;
        infile>>M;
        cout<<"M: "<<M<<endl;

        // 3.4 读入答案,大小为[N+1, M]
        vector<string>a;
        for(int j = 0; j < N+1; j++)
        {
            // 读入第j个小伙伴的答案或自己的答案
            string data;
            infile>>data;
            a.push_back(data);
        }

        // 3.5 记录a中第0行和第1行中答案异同的情况，1相同，0不同。并统计答案不一样的个数。
        vector<int> s12;
        int difnum = 0; //统计答案不一样的个数
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

        // 3.6 分情况讨论，（1）：如果只有一个小伙伴，即N=1的时候。（2）；如果有两个小伙伴N=2时
        if(N==1) //只有一个小伙伴
        {
            // 3.6.1 读入小伙伴的分数，计算小伙伴做错的个数
            int score1, error_num;
            infile>>score1;
            cout<<"score1:"<<score1<<endl;
            error_num = M - score1;
            // 3.6.2 再分情况讨论
            if(error_num >= difnum) //如果小伙伴做错的个数大于等于我们不一样的答案的个数：最好的情况是，我们不一样的答案，小伙伴都做错了，而我作对了。在一样的答案里，我和他的分数一样，都是score，那么我的分数将比他高diffnum分
            {
                myscore = score1 + difnum;
            }
            else  // 否则最好的情况是，他错的全是我们不一样的答案。剩下的我们一样的答案（M-difnum）里，全是对的。所以我的分数是M-difnum+error_num;

            {
                myscore = M - difnum + error_num;
            }


        }
        else if(N==2)
        {
            // 3.6.1 记录第一个小伙伴和第二个小伙伴的分数
            vector<int> score;
            for(int em = 0; em < N; em++)
            {
                int cur;
                infile>>cur;
                score.push_back(cur);
                cout<<"score ["<<em<<"]: "<<score[em]<<endl;
            }
            // 3.6.2 计算在小伙伴答案相同的题目中做对的个数，在答案不同的题目里，得分高的小伙伴做对的个数和得分低的小伙伴做对的个数
            int mins, maxs;
            mins = score[0] <= score[1] ? 0 : 1; //记录得分较少的小伙伴的标号
            maxs = score[0] <= score[1] ? 1 : 0; // 记录得分较高的小伙伴的标号
            int diffscore12;
            diffscore12 = score[maxs] - score[mins]; //第一个和第2个小伙伴不同的答案里，得分高的小伙伴比得分低的小伙伴多作对了diffscore道。
            //注意，在小伙伴不同的每一个答案里，肯定有一人是正确的。所以可以得到在不同的答案里，得分高的小伙伴做对的个数ymax个，得分低的小伙伴作对的个数ymin个
            int ymax, ymin;
            ymax = (difnum + diffscore12)/2;
            ymin = (difnum - diffscore12)/2;
            //接着，可以得到在相同的答案里，是有s0道作对了
            int s0;
            s0 = score[mins] - ymin;

            // 3.6.3 拿我的答案和他们的答案进行比较，得到我能获得的最高分

            // 3.6.3.1 统计4种不同情况下的个数
            // 设在小伙伴A和小伙伴B相同的答案里，我的答案与他们的相同的个数为num1, 不同的个数为num2
            // 设在小伙伴A和小伙伴B不同的答案里，我的答案与得分高的小伙伴相同的个数为num3,不同的为num4
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

            // 3.6.3.2 先分别得到在小伙伴们答案一样的题目里我能得到的最高分和在小伙伴们答案不一样的题目里我能得到的最高分
            int myscore1, myscore2, myscore3, myscore4;
            // 3.6.3.2.1 小伙伴们答案一样的题目里，我能得到的最高分为myscore1+myscore2; (我希望我们答案都一样的题里，他们尽量是做对了）
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
            // 3.6.3.2.2 小伙伴们答案不一样的题目里，我能得到的最高分为myscore3+myscore4;（我希望和得分高的小伙伴答案一样的题目中，他尽量是做多对了）
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


            // 3.6.3.3我的最终的最高得分。
            myscore = myscore1 + myscore2 + myscore3 + myscore4;
        }
        // 4.输出我的最高得分
        cout<<"Case #" << i + 1 << ": " << myscore <<endl;
        outfile<<"Case #"<< i + 1 << ": " << myscore <<endl;
    }


    return 0;

}
