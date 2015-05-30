#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>
#include <random>
using namespace std;
#define MAX_T 150
#define THRESHOLD 0.5
#define RATE 0.1

double w0,w1,w2;
double x0;

class data
{
public:
    double x1,x2;
    int _class;
    data(double a,double b,int c)
    {
        x1 = a, x2 = b, _class = c;
    }
};

class pocket
{
public:
    double w0,w1,w2;
};

pocket pkt;
vector <data> train,test;
int N;

void input()
{
    train.clear();
    scanf("%d",&N);
    int i,cl;
    double a,b;
    for(i=0; i<N; i++)
    {
        scanf("%lf %lf %d",&a,&b,&cl);
        data d(a,b,cl);
        train.push_back(d);
    }
}

void print_info()
{
    int i;
    for(i=0; i<train.size(); i++)
    {
        printf("%f %f %d\n",train[i].x1,train[i].x2,train[i]._class);
    }
}

void run_perceptron()
{
    double sum = 0;
    int history = 0;
    int total_dataset = train.size();
    w0 = 0.8, w1 = 0.4, w2 = 0.0;   // initially set to some arbitrary weight
    //w0 = w1 = w2 = 0.0 // initially set to 0
    x0 = 1.0;
    int corrects;
    while(history < total_dataset)
    {
        double w_0 = w0, w_1 = w1, w_2 = w2;
        int predicted_class;
        corrects = 0;
        for(int i=0; i<total_dataset; i++)
        {
            data d = train[i];
            sum = 0;
            sum = d.x1 * w1 + d.x2 * w2 + x0*w0;
            if(sum > THRESHOLD)
            {
                predicted_class = 2;
            }
            else predicted_class = 1;

            int mult = predicted_class - d._class;
            if(mult == 0) corrects++;

            w_0 -= mult * RATE * x0;
            w_1 -= mult * RATE * d.x1;
            w_2 -= mult * RATE * d.x2;
        }
        if(corrects > history)
        {
            pkt.w0 = w0;
            pkt.w1 = w1;
            pkt.w2 = w2;
            history = corrects;
        }

        w0 = w_0;
        w1 = w_1;
        w2 = w_2;
    }
}

void run_test()
{
    double a,b,s;
    int cl;
    int match = 0;
    int tot = 0;
    while(scanf("%lf %lf %d",&a,&b,&cl)!=EOF)
    {
        tot++;
        s = a*pkt.w1 + b*pkt.w2 + pkt.w0;
        if(s > 0)
        {
            if(cl == 2) match++;
        }
        else
        {
            if(cl == 1) match++;
        }
    }
    printf("Total test data : %d\n",tot);
    printf("Correctly classified : %d\n",match);
    printf("Incorrectly classified : %d\n",tot-match);
}

int main()
{
    freopen("Train.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    input();
    //print_info();
    run_perceptron();
    fclose(stdin);
    puts("Pocket Algorithm");
    puts("Weight assigned");
    printf("w0=%f, w1=%f, w2=%f\n",pkt.w0,pkt.w1,pkt.w2);

    freopen("Test.txt","r",stdin);
    run_test();
    puts("=======");
    fclose(stdin);

    return 0;
}
