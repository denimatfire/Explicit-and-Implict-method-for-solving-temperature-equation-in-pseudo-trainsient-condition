#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
using namespace std;
int main()
{
    float h,l,dx, dy, b, t0[100][100],t1[100][100],t2[100][100], error=0,x,y,t=0,time_error=0,s=0;
    int i,j,n,m,dt=1,k=0;
    cout<<" enter N X M grid size \n ";
    cin>>n>>m;
    cout<<" length of the grid H and L \n";
    cin>>h>>l;
    dx=l/(n-1);
    dy=h/(m-1);
    //cout<<" "<<dx<<" "<<dy;
    b=dx/dy;
    float a=3.4*pow(10, -6);
    float ax=(a*dt)/pow(dx,2);
    float ay=(a*dt)/pow(dy,2);
    cout<<"ax "<<ax<<" ay "<<ay;
    int hx=250;
    int ks=18;
    int tu=10;
    float q=(hx*dx)/ks;

    for(i=0; i<n; i++){
        t0[i][0]=50;
        t0[i][m-1]=50;
        t2[i][0]=50;
        t2[i][m-1]=50;
    }
    for (j=0; j<m; j++){
        t0[n-1][j]=50;
        t2[n-1][j]=50;
    }
    for (i=1; i<n-1; i++){
       for (j=1; j<m-1; j++){
        t0[i][j]=10;
        t2[i][j]=10;
       }}
    for (j=0; j<m; j++){
        t0[0][j]=(q*tu +t0[1][j])/(q+1);}
        cout<<"\n";
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                cout<<t0[i][j]<<"\t";
            }
cout<<"\n";        }

clock_t begin, end;
double cpu_time_used;
begin = clock();
do{
float iter=0,p=0;
      do{
                for(j=1; j<m-1; j++ ){
                    for(i=1; i<n-1; i++){
                    t1[i][j]=(ax*(t0[i-1][j]+t0[i+1][j]) + ay*(t0[i][j+1]+t0[i][j-1]) + t2[i][j])/(1+2*ax+2*ay);
                    s=s+ pow((t1[i][j]-t0[i][j]), 2);
                    //cout<<"sum-"<<s<<"\n";
                    t0[i][j]=t1[i][j];}
                    t0[0][j]=(q*tu + t1[1][j])/(q+1);
                }
                    error= sqrt(s/((m-2)*(n-2))) ;
                    iter++;
                    cout<<"error "<<error<<"\n";
                  s=0;
        }while(error> 0.000001);
            k=k+1;
            cout<<" no of iteration = \t"<<iter<<" for time level \t"<<k;
                for(i=1;i<n-1;i++){
				  for(j=1;j<m-1;j++){
                    p=p+ pow((t1[i][j]-t2[i][j]), 2);
            }}
           time_error=sqrt(p/((m-2)*(n-2))) ;
           for(i=1;i<n-1;i++){
                  for(j=1;j<m-1;j++){
                   t2[i][j]=t1[i][j];}}

               }while(time_error > 0.0001);
 ofstream thefile("cfd.txt");

for(x=0,i=0; i<n; i++,x=x+dx){
    for (y=0,j=0; j<m; j++,y=y+dy){
        thefile<<x<<"\t"<<y<<"\t"<<t0[i][j]<<"\n";
    }
  }

end = clock();
cpu_time_used = ((double) (end - begin))/ CLOCKS_PER_SEC;
cout<<" \n"<<cpu_time_used;
    return 0;
}








