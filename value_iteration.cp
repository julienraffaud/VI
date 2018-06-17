#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double g = 1;
double probability = 0.5;
double number_of_states = 100;
vector <double> reward;
double theta = 0.0000000001;
vector <double> state_value;
vector <double> policy;
double delta;


double bellman(double num)
{
    double optimal = 0;
    
    for (double b=0; b<min(num,100 - num)+1;++b)
    {
        double win =num + b;
        double loss = num - b;
        double sum = probability * (reward[win]+g * state_value[win])+(1- probability) * (reward[loss] + g * state_value[loss]);
        if (sum>optimal)
        {
            optimal = sum;
            state_value[num] = sum;
            policy[num] = b;
        }
    }
    return 0;
}


double value_iteration()
{
    delta = 1;
    
    while (delta>theta)
    {
        delta = 0;
        
        for (int n=1; n<number_of_states;++n)
        {
            double old_value = state_value[n];
            bellman(n);
            double difference = abs(old_value - state_value[n]);
            delta = max(delta,difference);
        }
    }
    for (int n=0; n<state_value.size();++n)
    {
        cout <<state_value[n]<<endl;
    }
    return 0;
}


int main(void)
{
    for (int n=0;n<101;++n)
    {
        reward.push_back(0);
        state_value.push_back(0);
        policy.push_back(0);
    }
    reward.back() = 1;
    value_iteration();
}