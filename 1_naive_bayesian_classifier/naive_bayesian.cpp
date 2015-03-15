#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;
#define pi 3.1416

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
        //printf("%f %f %f %f\n",ii.varPL,ii.varPW,ii.varSL,ii.varSW);
        data[i] = ii;
    }
}

double denominator(double variance)
{
    return sqrt(2*pi) * variance;
}
double numerator(double variance,double X,double average)
{
    return exp(-1*(X-average)*(X-average)/(2*variance*variance));
}
void print_info()
{
    int i;
    for(i=0; i<3; i++)
    {
        info ii = data[i];
        printf("%f %f %f %f\n",ii.avgPL,ii.avgPW,ii.avgSL,ii.avgSW);
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
        //printf("%f %f %f %f %d\n",a,b,c,d,e);
        info ii = data[e];
        ii.SL.push_back(a),ii.SW.push_back(b),ii.PL.push_back(c),ii.PW.push_back(d);
        data[e] = ii;
    }
    fclose(stdin);
    calculate_average();
    calculate_variance();
    //print_info();

    freopen("set_test.txt","r",stdin);
    double maxx;
    pair <double,int> ans;
    ans.first = 0;
    ans.second = -1;
    while(scanf("%lf %lf %lf %lf %d",&a,&b,&c,&d,&e))
    {
        // 1/sqrt(2*pi*variance) * e ^ -(X-mean)^2/2*variance^2
        /*
        * a => SL
        * b => SW
        * c => PL
        * d => PW
        * e =>CLASS
        */
        maxx = 0;
        int i;
        for(i=0; i<3; i++)
        {
            info ii = data[i];
            double d = denominator(ii.varSL);
            double n = numerator(ii.varSL,a,ii.avgSL);
            //printf("%f %f %f\n",d,n,ii.varSL);
            double resSL = n/d;
            d = denominator(ii.varSW);
            n = numerator(ii.varSW,b,ii.avgSW);
            double resSW = n/d;
            d = denominator(ii.varPL);
            n = numerator(ii.varPL,c,ii.avgPL);
            double resPL = n/d;
            d = denominator(ii.varPW);
            n = numerator(ii.varPW,c,ii.avgPW);
            double resPW = n/d;
            printf("%f %f %f\n",d,n,resPW);

            double res = resSL * resSW * resPL * resPW * ii.ndata;
            printf("res %f %f %f %f %f\n",res,resSL,resSW,resPL,resPW);
            if(res > maxx)
            {
                ans.first = res;
                ans.second = i;
                maxx = res;
            }
        }

        //printf("Real %d,Estimated %d\n",e,ans.second);
    }
    fclose(stdin);


    return 0;
}
