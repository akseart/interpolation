//
//  main.cpp
//  interpolation
//
//  Created by Артем on 09.04.2018.
//  Copyright © 2018 Артем. All rights reserved.
//


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
vector<long double> example1 (){
    vector<long double> tmp;
    tmp.push_back(0.1*M_PI);
    tmp.push_back(0.2*M_PI);
    tmp.push_back(0.3*M_PI);
    tmp.push_back(0.4*M_PI);
    return tmp;
};
vector<long double> example2 (){
    vector<long double> tmp;
    tmp.push_back(0);
    tmp.push_back(M_PI/6);
    tmp.push_back(0.3*M_PI);
    tmp.push_back(0.4*M_PI);
    return tmp;
}
long double f (long double x){
    return sin(x);
}
long double dividedDifferences (vector<long double> fix){ //Передавать аргументы функции
    if (fix.size() == 1)
        return f( fix.front());
    long double tmp =0.0;
    long double tmp1 = 0.0;
    tmp = fix.front();
    
    fix.erase(fix.begin()); //Удаляем первый
    tmp1 = dividedDifferences(fix); //Без первого
    fix.insert(fix.begin(),tmp);   //возвращаем первый
    
    tmp = 0.0;
    tmp = fix.back();
    fix.pop_back(); //Удаляем последний
    tmp1 -= dividedDifferences(fix); // без последнего
    fix.push_back(tmp);  // возвращаем последний
    
    tmp1 /= fix.back() - fix.front(); //знаменатель
    return tmp1;
}
long double Lagranzh (vector<long double> Xi, long double X){
    long double lagranzh = 0.0;
    for (int i=0; i<Xi.size(); i++) {
        long double tmp = 1.0 ;
        for (int j = 0; j < Xi.size(); j++) {
            if (i == j)
                continue;
            tmp *= (X - Xi[j])/(Xi[i] - Xi[j]);
        }
        lagranzh += f(Xi[i])*tmp;
    }
    return lagranzh;
}
long double Newton (vector<long double> Xi, long double X){
    vector<long double> tmp;
    tmp.push_back(Xi[0]);
    long double Newton = dividedDifferences(tmp); //F(x0)
    for (int i =0; i<Xi.size()-1; i++){
        tmp.push_back(Xi.at(i+1));
        double tmp1 = 1.0;
        for (int j=0; j<=i; j++) {
            tmp1 *= (X - Xi[j]);
        }
        Newton += tmp1*dividedDifferences(tmp);
    }
    return Newton;
}
int main(int argc, const char * argv[]) {
    const long double X = M_PI/4;
    cout<<"Нормальное значение: "<< f(X)<<endl;
    cout<< "Пример 1" << endl;
    cout<<"Значение интерполяции полиномом Лагранжа: "<<Lagranzh(example1(),X)<<endl;
    cout<<"Значение интерполяции полиномом Ньютона:  "<<Newton(example1(), X)<<endl;
    
    cout<< "Пример 2" << endl;
    cout<<"Значение интерполяции полиномом Лагранжа: "<<Lagranzh(example2(),X)<<endl;
    cout<<"Значение интерполяции полиномом Ньютона:  "<<Newton(example2(), X)<<endl;
    return 0;
}
