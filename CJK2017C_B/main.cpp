#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    // 1.�����ļ������������
    ifstream infile;
    infile.open("B-large-practice.in");
    ofstream outfile;
    outfile.open("B-large-practice.out");

    // 2.���������ĸ���
    int number;
    infile>>number;
    cout<<number<<endl;

    // 3.������������ж�
    for(int i = 0; i < number; i++)
    {
        bool canwin = true; //Ĭ����Ϸ��Ӯ
        // 3.1 �����i�������ĳ���
        int length;
        infile>>length;
        cout<<length<<endl;

        // 3.2 �����i��������ģ��,�������model�С�����rn��¼ÿһ�г���X�ĸ�����cn��¼ÿһ�г��ֵ�X�ĸ���
        int model[length][length]; //����model�洢��i������ģ����״�����ң���X'������1��ʾ����.'������0��ʾ
        vector<int>rn(length, 0); //����rn����¼ÿһ�г���X�ĸ�������ʼ��Ϊ0
        vector<int>cn(length,0); //����cn,��¼ÿһ�г���X�ĸ�������ʼ��Ϊ0
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

        // 3.3. ��Ϸ�ܹ�Ӯ�Ĺؼ��ǣ�����ֻ��һ�к�һ�д���1��X,���Ҹ��и�����X���ཻ������ÿ��ÿ��ֻ����2��X������������������������IMPOSSIBLE��canwin = false
        // 3.3.1 ���ҵ���һ��X�ĵ��к���
        int p = 0, q = 0;
        while(p < length && rn[p] != 1)
            p++;
        while(q < length && cn[q] != 1)
            q++;
        if(p == length || q == length) // ���û��һ�л�һ��ֻ��һ��X��ʱ����Ϸ����Ӯ
        {
            cout<<"Case #" << i + 1 << ": IMPOSSSIBLE" ;
            outfile<<"Case #"<< i + 1 <<": IMPOSSIBLE";
            outfile<<endl;
            continue;
        }
        // 3.3.2 �ж��Ƿ�ֻ��һ�к�һ�д���һ��X�������к���ȫ��ֻ������X
        sort(rn.begin(), rn.end());
        sort(cn.begin(), cn.end());
        if((rn[0] != 1) || (cn[0] != 1) || (model[p][q] !=1) )
            canwin = false;
        for(int j = 1; canwin && j < length; j++)
        {
            if(rn[j] != 2 || cn[j] != 2)
                canwin = false;
        }

        // 3.4. ������㣬��һ���жϣ���������������X���У���������һ�е���״�͸�����ȫһ�����������е�4����X���պ����һ������ʱ����Ϸ�ܳɹ��������ܡ�
        if(canwin)
        {
            // 3.4.1 ����bool����fr��fc��fr��¼ĳ���Ƿ񱻷��ʹ���fc��¼ĳ���Ƿ񱻷��ʹ�����ʼ��Ϊû���ʹ���
            vector<bool> fr(length, false);
            vector<bool> fc(length, false);
            // 3.4.2 ����ֻ��1��X���к��б��Ϊ���ʹ���
            fr[p] = fc[q] = true;
            // 3.4.3 �ӵ�0�п�ʼ���ʾ�������X���С�ÿ��Ҫ��������״һ�����У�����Ҫ��length/2���ܱ����ꡣ��lengthΪ������
            for(int t = 0; canwin && t < length/2; t++)
            {
                // 3.4.3.1 ��ͷ��ʼ�ҵ�δ�����ʵ���һ��
                int i0 = 0;
                while(fr[i0]) // ���i0�б����ʹ��ˣ�i0++,ֱ������δ�����ʹ�
                    i0++;

                // 3.4.3.2 �ҵ����е�һ�γ���X��λ��
                int j0 = 0;
                while(!model[i0][j0])
                    j0++;

                // 3.4.3.3 �ҵ����еڶ��γ���X��λ��
                int j1 = j0 + 1;
                while(!model[i0][j1])
                    j1++;

                // 3.4.3.4 ���������������һ�������ʹ��ˣ���Ϸ����Ӯ��canwin = false
                if(fc[j0] || fc[j1])
                {
                    canwin = false;
                    break;
                }

                // 3.4.3.5 �ҵ���j0�еڶ��γ���X��λ��
                int i1 = 0;
                while(!model[i1][j0] || i1 == i0)
                    i1++;
                // 3.4.3.6 ��������Ѿ������ʹ��˻��߸��еĵ�j1�в�����Xʱ������Ϸ����Ӯ��canwin=false
                if(fr[i1] || (model[i1][j1] != 1))
                {
                    canwin = false;
                    break;
                }
                // 3.4.3.7 ��Ǹոշ��ʹ������к�����
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
