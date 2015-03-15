#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;

vector <double> SL,SW,PL,PW;
vector <int> cls;
int cls_count[3];
int total;
double P0,P1,P2;
struct info
{
    int clas;
    double SLsum,SWsum,PLsum,PWsum;
    double SLvar,SWvar,PLvar,PWvar;
    double SLmean,SWmean,PLmean,PWmean;
    double slXminusU,swXminusU,plXminusU,pwXminusU;
    vector <double> SL,SW,PL,PW;
};
vector <info> bank;

int main()
{
    freopen("set_training.txt","r",stdin);
    double a,b,c,d;
    int e;
    total = 0;
    while(scanf("%lf %lf %lf %lf %d",&a,&b,&c,&d,&e))
    {
        //printf("%lf %lf %lf %lf %d\n",a,b,c,d,e);
        SL.push_back(a);
        SW.push_back(b);
        PL.push_back(c);
        PW.push_back(d);
        cls.push_back(e);
        cls_count[e]++;
        total++;
    }
    //printf("%d %d %d %d\n",cls_count[0],cls_count[1],cls_count[2],total);
    P0 = (double)cls_count[0] / total;
    P1 = (double)cls_count[1] / total;
    P2 = (double)cls_count[2] / total;
    //printf("%lf %lf %lf\n",P0,P1,P2);
    info c0,c1,c2;
    c0.clas = 0;
    c0.pwXminusU = c0.plXminusU = c0.swXminusU = c0.slXminusU = c0.PLsum = c0.PWsum = c0.SLsum = c0.SWsum = 0.0;
    c1.clas = 0;
    c1.pwXminusU = c1.plXminusU = c1.swXminusU = c1.slXminusU = c1.PLsum = c1.PWsum = c1.SLsum = c1.SWsum = 0.0;
    c2.clas = 0;
    c2.pwXminusU = c2.plXminusU = c2.swXminusU = c2.slXminusU = c2.PLsum = c2.PWsum = c2.SLsum = c2.SWsum = 0.0;
    bank.push_back(c0);
    bank.push_back(c1);
    bank.push_back(c2);
    for(int i=0; i<total; i++)
    {
        info v;
        if(cls[i] == 0)
        {
            v = bank[0];
            v.PLsum += PL[i];
            v.PWsum += PW[i];
            v.SLsum += SL[i];
            v.SWsum += SW[i];
            v.PL.push_back(PL[i]);
            v.PW.push_back(PW[i]);
            v.SL.push_back(SL[i]);
            v.SW.push_back(SW[i]);
            bank[0] = v;
        }
        else if(cls[i] == 1)
        {
            v = bank[1];
            v.PLsum += PL[i];
            v.PWsum += PW[i];
            v.SLsum += SL[i];
            v.SWsum += SW[i];
            v.PL.push_back(PL[i]);
            v.PW.push_back(PW[i]);
            v.SL.push_back(SL[i]);
            v.SW.push_back(SW[i]);
            bank[1] = v;
        }
        else
        {
            v = bank[2];
            v.PLsum += PL[i];
            v.PWsum += PW[i];
            v.SLsum += SL[i];
            v.SWsum += SW[i];
            v.PL.push_back(PL[i]);
            v.PW.push_back(PW[i]);
            v.SL.push_back(SL[i]);
            v.SW.push_back(SW[i]);
            bank[2] = v;
        }
    }
    for(int j=0; j<3; j++)
    {
        info v;
        v = bank[j];
        v.PLmean = v.PLsum / cls_count[j];
        v.PWmean = v.PWsum / cls_count[j];
        v.SLmean = v.SLsum / cls_count[j];
        v.SWmean = v.SWsum / cls_count[j];
        bank[j] = v;
    }
    for(int j=0; j<3; j++)
    {
        info v;
        v = bank[j];
        //printf("%d %lf %lf %lf %lf\n",cls_count[j],v.SLsum,v.SWsum,v.PLsum,v.PWsum);
        //printf("%d %d %d %d %d\n",j,v.PL.size(),v.PW.size(),v.SL.size(),v.SW.size());
        vector <double> t;
        t = v.PL;
        for(int k=0; k<t.size(); k++)
        {
            double val = t[k] - v.PLmean;
            v.plXminusU += (val*val);
        }
        v.PLvar = sqrt(v.plXminusU / t.size());
        t.clear();
        t = v.PW;
        for(int k = 0; k<t.size(); k++)
        {
            double val = t[k] - v.PWmean;
            v.pwXminusU += (val*val);
        }
        v.PWvar = sqrt(v.pwXminusU / t.size());
        t.clear();
        t = v.SL;
        for(int k = 0; k<t.size(); k++)
        {
            double val = t[k] - v.SLmean;
            v.slXminusU += (val*val);
        }
        v.SLvar = sqrt(v.slXminusU / t.size());
        t.clear();
        t = v.SW;
        for(int k = 0; k<t.size(); k++)
        {
            double val = t[k] - v.SWmean;
            v.swXminusU += (val*val);
        }
        v.SWvar = sqrt(v.swXminusU / t.size());
        bank[j] = v;
    }
    fclose(stdin);
    double p0,p1,p2;
    freopen("set_training.txt","r",stdin);
    while(scanf("%lf %lf %lf %lf %d",&a,&b,&c,&d,&e))
    {

    }
    return 0;
}
