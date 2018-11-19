#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    // 1.�������
    string data; // data�洢���ļ������ж�ȡ���ַ�����Ҳ���Ǳ������ַ���
    int number; // ��¼�����ĸ���
    int store[100];  // �洢����������
    int original[100]; // �洢ԭʼ���ַ�����Ӧ������

    // 2.������������ļ�����
    ifstream infile;
    infile.open("A-small-practice.in");
    ofstream outfile;
    outfile.open("A-small-practice.out");

    infile>>number;  //��ȡ�����ļ��ĵ�һ�����ݣ�����������Ŀ
    cout<<number<<endl; //����̨�����Ϊ�˼����������Ƿ���ȷ���ͱ���û�й�ϵ

    // 3.ѭ������ÿһ������
    for(int i = 0; i < number; i++)
    {
        // 3.1 �����i�е��ַ�������
        infile>>data;
        int length = data.length();
        cout<<data<<"----";
        // 3.2 ���ַ���ת��������
        for(int j = 0; j < length; j++)
        {
            store[j] = int(data[j]) - 65; //ǿ������ת���� ��A-Zת����0-25������

        }
        // 3.3 ���н��롣�ж�ԭ�ַ����ĳ��ȡ���Ϊ��������û��Ωһ�ı��룬ֱ�����ΪAMBIGUOUS����Ϊż��������
        if(length % 2 == 0)
            {
              // 3.3.1 ���򴫲����ó���1����3,5����������ԭ�ַ���������
              original[1] = store[0];
              for(int k = 3; k < length; k = k+2)
              {
                  int curr = store[k-1]-original[k-2];
                  original[k] = curr>0 ? curr : curr + 26;
              }
              // 3.3.2 ���򴫲����ó���N-2����N-4,4,2,0��ԭ�ַ���������
              original[length-2] = store[length-1];
              for(int k = length-4; k>=0; k = k-2)
              {
                  int curr = store[k+1]-original[k+2];
                  original[k] =  curr>0 ? curr : curr + 26;
              }
              // 3.3.3 �����ÿ�еı��
              cout<<"Case #" << i + 1 << ": " ;
              outfile<<"Case #"<< i + 1 <<": ";
              // 3.3.4 ����õ�ԭ�ַ�����Ӧ�������������ת����char�Ͳ����
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
