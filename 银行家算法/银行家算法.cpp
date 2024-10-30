#include <iostream>
#include <queue>
using namespace std;
class bankalgorithm{
public:
    int m, n,request_num;//n进程数量
    queue<int> safecount;
    int* available;
    int** Max;
    int** Allocation;
    int** Need;
    int* request;
    int* work;
    void bank_algorithm()
    {
        ba_initial();
        cout << "初始化完成" << endl;
        while (true)
        {
            judge();
        }
    }
    void judge() {
        cout << "输入request进程num " << endl;
        cin >> request_num;
        cout << "输入request " << endl;
        request = new int[m];
        for (int i = 0; i < m; i++)
        {
            cin >> request[i];
        }
        if (safe()==true) {
            cout << "可以分配" << endl;
            /*for (int i = 0; i < m; i++)
            {
                cout << available[i] << endl;
            }*/
            for (int i = 0; i < n; i++)
            {
                cout << safecount.front();
                safecount.pop();
            }
            cout << endl;
        }
        else
        {
            
            cout << "不可以分配" << endl;
            /*for (int i = 0; i < m; i++)
            {
                cout << available[i] << endl;
            }*/
        }
    }
    bool safe() {
        for (int i = 0; i < m; i++)
        {
            if (request[i] > Need[request_num][i]||request[i]>available[i])
            {
                return false;
            }
        }
        //cout << "a" << endl;
        for (int i = 0; i < m; i++)
        {
            available[i] -= request[i];
            Allocation[request_num][i] += request[i];
            Need[request_num][i] -= request[i];
        }
        //cout << "b" << endl;
        bool safestate = false;
        bool *finish = new bool[n];
        for (int i = 0; i < n; i++)
        {
            finish[i] = false;
        }
        work = new int[m];
        //cout << "work" << endl;
        for (int i = 0; i < m; i++)
        {
            work[i] = available[i];
            //cout << work[i];
        }
        //cout << "c" << endl;
        //cout << safecount.size() << endl;
        while (safecount.size() < n)
        {
            bool findprecessible=false;
            for (int i = 0; i < n; i++)
            {
                if (finish[i] == false)
                {
                    bool precessiable = true;
                    for (int k = 0; k < m; k++)
                    {
                        if (work[k] < Need[i][k])
                        {
                            precessiable = false;
                            break;
                        }
                    }
                    if (precessiable == true)
                    {
                        for (int p = 0; p < m; p++)
                        {
                            work[p] += Allocation[i][p];
                        }
                        finish[i] = true;
                        safecount.push(i);
                        findprecessible = true;
                        /*for (int f = 0; f < m; f++)
                        {
                           cout<<work[f]<<" ";
                        }*/
                        //cout << endl;
                    }
                }
            }
            if (findprecessible == false)
            {
                for (int i = 0; i < m; i++)
                {
                    available[i] += request[i];
                    Allocation[request_num][i] -= request[i];
                    Need[request_num][i] += request[i];
                }
                return false;
            }

        }
        return true;
    }
    void ba_initial() {
        cout << "输入资源种类 " << endl;
        cin >> m;//列
        cout << "输入进程个数 " << endl;
        cin >> n;//行
        cout << "输入max一行一个进程 " << endl;
        Max = new int* [n];
        for (int i = 0; i < n; i++)
        {
            Max[i] = new int[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> Max[i][j];
            }
        }
        cout << "输入allocation一行一个进程 " << endl;
        Allocation = new int* [n];
        for (int i = 0; i < n; i++)
        {
            Allocation[i] = new int[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> Allocation[i][j];
            }
        } 
        Need = new int* [n];
        for (int i = 0; i < n; i++)
        {
             Need[i] = new int[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                Need[i][j]=Max[i][j]-Allocation[i][j];
            }
        }
        cout << "输入available" << endl;
        available = new int[m];
        for (int i = 0; i < m; i++)
        {
            cin >> available[i];
        }
        
    }
};
int main()
{
    bankalgorithm ba;
    ba.bank_algorithm();
    
}
