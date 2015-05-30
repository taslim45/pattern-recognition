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
    int error = 1;
    w0 = w1 = w2 = 0.0; // initially set to 0
    x0 = 1.0;
    while(error)
    {
        error = 0;
        int predicted_class;
        for(int i=0; i<train.size(); i++)
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
            if(mult!=0) error++;

            w0 -= mult * RATE * x0;
            w1 -= mult * RATE * d.x1;
            w2 -= mult * RATE * d.x2;

        }
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
        s = a*w1 + b*w2 + w0;
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
    //freopen("output.txt","a+",stdout);
    input();
    //print_info();
    run_perceptron();
    fclose(stdin);
    puts("Reward and Punishment");
    puts("Weight assigned");
    printf("w0=%f, w1=%f, w2=%f\n",w0,w1,w2);

    freopen("Test.txt","r",stdin);
    run_test();
    puts("=======");
    fclose(stdin);

    return 0;
}
