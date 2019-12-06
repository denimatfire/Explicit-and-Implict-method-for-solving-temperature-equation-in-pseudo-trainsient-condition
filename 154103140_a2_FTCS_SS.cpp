#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>

using namespace std;

int main()
{
    float h,l,dx, dy, b, t0[100][100],t1[100][100], error,x,y;
    int i,j,n,m,dt=1,iter=0;

    cout<<" enter N X M grid size\n ";
    cin>>n>>m;
    cout<<" length of the grid H and L\n";
    cin>>h>>l;

    dx=l/(n-1);
    dy=h/(m-1);
    cout<<" "<<dx<<" "<<dy;

    b=dx/dy;
    float a=3.4*pow(10, -6);
    float ax=(a*dt)/pow(dx,2);
    float ay=(a*dt)/pow(dy,2);

    cout<<"ax "<<ax<<" ay "<<ay;

    int hx=250;
    float ks=18;
    int tu=10;

    float q=(hx*dx)/ks;

    cout<<"q "<<q;


    for(i=0; i<n; i++){
        t0[i][0]=50;
        t0[i][m-1]=50;
    }
    for (j=0; j<m; j++){
        t0[n-1][j]=50;
    }
    for (i=1; i<n-1; i++){
       for (j=1; j<m-1; j++){
        t0[i][j]=10;
       }}
    for (j=0; j<m; j++){
        t0[0][j]=(q*tu +t0[1][j])/(q+1);
    }

   /* for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            cout<<t0[i][j]<<"\t";}
        cout<<"\n";}*/

clock_t begin, end;
double cpu_time_used;
begin = clock();

 do{ float s=0;
for(i=1; i<n-1; i++ ){
    for(j=1; j<m-1; j++){
       t1[i][j]=t0[i][j]+ax*(t0[i+1][j] - 2*t0[i][j] +t0[i-1][j]) + ay*(t0[i][j+1] - 2*t0[i][j] +t0[i][j-1]);
        s=s+ pow((t1[i][j]-t0[i][j]), 2);
        t0[i][j]=t1[i][j];
        t0[0][j]=(q*tu + t0[1][j])/(q+1);
    }
    }
   /* for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            cout<<t1[i][j]<<"\t";}
        cout<<"\n";}*/
error= sqrt(s/((m-2)*(n-2))) ;
iter++;
}while(error> 0.0001);
cout<<" no of iteration ="<<iter;
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
