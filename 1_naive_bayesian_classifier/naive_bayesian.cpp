#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;

struct info
{
    int which_class;
    vector <double> SL,SW,PL,PW;
    int ndata;
    double avgSL,avgSW,avgPL,avgPW;
    double varSL,varSW,varPL,varPW;
};

vector <info> data;

void calculate_average()
{
    int i,j;
    for(i=0; i<3; i++)
    {
        info ii = data[i];
        ii.ndata = ii.SL.size();
        double sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += ii.SL[j];
        }
        ii.avgSL = sum / ii.ndata;
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += ii.SW[j];
        }
        ii.avgSW = sum / ii.ndata;
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += ii.PL[j];
        }
        ii.avgPL = sum / ii.ndata;
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += ii.PW[j];
        }
        ii.avgPW = sum / ii.ndata;
        data[i] = ii;
    }
}

void calculate_variance()
{
    int i,j;
    for(i=0; i<3; i++)
    {
        info ii = data[i];
        ii.ndata = ii.SL.size();
        double sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += (ii.SL[j] - ii.avgSL)*(ii.SL[j] - ii.avgSL);
        }
        ii.varSL = sqrt(sum / ii.ndata);
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += (ii.SW[j] - ii.avgSW)*(ii.SW[j] - ii.avgSW);
        }
        ii.varSW = sqrt(sum / ii.ndata);
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += (ii.PL[j] - ii.avgPL)*(ii.PL[j] - ii.avgPL);
        }
        ii.varPL = sqrt(sum / ii.ndata);
        sum = 0;
        for(j=0; j<ii.ndata; j++)
        {
            sum += (ii.PW[j] - ii.avgPW)*(ii.PW[j] - ii.avgPW);
        }
        ii.varPW = sqrt(sum / ii.ndata);
        data[i] = ii;
    }
}

void print_info()
{
    int i;
    for(i=0; i<3; i++)
    {
        info ii = data[i];
        printf("%lf %lf %lf %lf\n",ii.avgPL,ii.avgPW,ii.avgSL,ii.avgSW);
    }
}

int main()
{
    freopen("set_training.txt","r",stdin);
    double a,b,c,d;
    int e;
    info c0,c1,c2;
    c0.which_class = 0;
    c1.which_class = 1;
    c2.which_class = 2;
    data.push_back(c0),data.push_back(c1),data.push_back(c2);
    while(scanf("%lf %lf %lf %lf %d",&a,&b,&c,&d,&e))
    {
        /*
        * a => SL
        * b => SW
        * c => PL
        * d => PW
        * e =>CLASS
        */
        printf("%lf %lf %lf %lf %d\n",a,b,c,d,e);
        info ii = data[e];
        ii.SL.push_back(a),ii.SW.push_back(b),ii.PL.push_back(c),ii.PW.push_back(d);
    }

    calculate_average();
    calculate_variance();
    print_info();

    return 0;
}
