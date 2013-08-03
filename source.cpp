#include<stdio.h>
#include<string.h>
#include<math.h>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;



class UnitTrans
{
   public: 
    map<string, double> units;
    
    UnitTrans()
    {
        units.clear();
    }
    
    void load(string line, int &flag);
    
    ~UnitTrans()
    {
        units.clear();
    }
};

void UnitTrans::load(string line, int &flag)
{
    vector<string> inputs;
    inputs.clear();
    int lastPosition = 0, i, index;
    if (line.length() <= 2) return;
    while (-1 != (index = line.find(' ', lastPosition)))
    {
        inputs.push_back(line.substr(lastPosition, index-lastPosition));
        lastPosition = index + 1;
    }
    string remain = line.substr(lastPosition);
    if (!remain.empty()) inputs.push_back(remain);
    for (i = 0; i < inputs.size(); i++)
    {
       if (inputs[i].compare("=") == 0)
       {
           flag = 0;
           break;
       }
    }
    if (i == inputs.size())
    {
        flag = 1;
    }
    if (flag == 0)
    {
        units[inputs[1].substr(0,4)] = atof(inputs[3].c_str());
        if (inputs[1].substr(0, 4).compare("foot") == 0)
        {
            units["feet"] = atof(inputs[3].c_str());
        }
    }
    else if (flag == 1)
    {
        double res = 0;
        string opt("+");
        double num;
        for (i = 0; i < inputs.size(); i++)
        {
            if (inputs[i].compare("-")==0 || inputs[i].compare("+")==0) opt = inputs[i];
            else if (inputs[i][0] >= '0' && inputs[i][0] <= '9') num = atof(inputs[i].c_str());
            else
            {
                if (opt.compare("+")==0)
                {
                    res += num * units[inputs[i].substr(0,4)];
                }
                else
                {
                    res -= num * units[inputs[i].substr(0,4)];
                }
            }
        }
        printf("%.2f m\n", res);
    }
}

int main(int argc, char **argv)
{
    char str[1000];
    UnitTrans *unitTrans = new UnitTrans();
    printf("msxieyan@163.com\n\n");
    while (fgets(str, 1000, stdin)) 
    {
        int flag = 2;
        string line = str;
        unitTrans->load(line, flag);       
    }    
    
    return 0;
}
