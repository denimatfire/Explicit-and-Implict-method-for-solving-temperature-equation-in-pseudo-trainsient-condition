#include <iostream>

#include <math.h>
#include <time.h>
#include <fstream>
using namespace std;

int main()
{
    int n,m,i,j,iter=0;
    double t0[100][100],t1[100][100],t2[100][100],t3[100][100],t4[100][100], error, dx,dy, beta,x,y;
    double a[100], b[100], c[100] , d[100], p[100], q[100],l,h,dt=1;

     cout<<" enter N X M grid size \n ";
    cin>>n>>m;
    cout<<" length of the grid H and L \n";
    cin>>h>>l;

    dx=l/(n-1);
    dy=h/(m-1);
    cout<<" "<<dx<<" "<<dy;

    beta=dx/dy;
    float a1=112*pow(10, -6);
    float ax=(a1*dt)/pow(dx,2);
    float ay=(a1*dt)/pow(dy,2);

    cout<<"ax "<<ax<<" ay "<<ay;

    int hx=250;
    float ks=380;
    int tu=10;

    float r=(hx*dx)/ks;

    cout<<"r "<<r;


    for(i=0; i<n; i++){
        t0[i][0]=50;
        t0[i][m-1]=50;
        t1[i][0]=50;
        t1[i][m-1]=50;
    }
    for (j=0; j<m; j++){
        t0[n-1][j]=50;
        t1[n-1][j]=50;
    }
    for (i=1; i<n-1; i++){
       for (j=1; j<m-1; j++){
        t0[i][j]=10;
        t1[i][j]=10;
       }}
    for (j=0; j<m; j++){
        t0[0][j]=(r*tu +t0[1][j])/(r+1);
    }

    clock_t begin, end;
    double cpu_time_used;
    begin = clock();

do{ double s=0;
    for(j=1; j<m-1; j++){
        for(i=1; i<n-1; i++){
            a[0]=1;
            b[0]=0;
            c[0]=0;
            d[0]=t0[0][j];
            a[i]=-(1+ax);
            b[i]=-(ax/2);
            c[i]=-(ax/2);
            d[i]=-(t0[i][j] + (ay/2)*(t0[i][j+1] -2*t0[i][j] + t0[i][j-1]));
            p[0]=b[0]/a[0];
            q[0]=d[0]/a[0];
            p[i]=b[i]/(a[i]-c[i]*p[i-1]);
            q[i]=(d[i]+c[i]*q[i-1])/(a[i]-c[i]*p[i-1]);
}
	for(i=n-2; i>0; i--){
		t3[i][j]=p[i]*t0[i+1][j] + q[i];
		t2[i][j]=t0[i][j];
		t0[i][j]=t3[i][j];

		//s=s+ pow((t1[i][j]-t2[i][j]), 2);
    }
    t0[0][j]=(r*tu + t0[1][j])/(r+1);

    }
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            a[0]=1;
            b[0]=0;
            c[0]=0;
            d[0]=t1[i][0];
            a[j]=-(1+ay);
            b[j]=-(ay/2);
            c[j]=-(ay/2);
            d[j]=-(t0[i][j] + (ax/2)*(t0[i+1][j] -2*t0[i][j] + t0[i-1][j]));
            p[0]=b[0]/a[0];
            q[0]=d[0]/a[0];
            p[j]=b[j]/(a[j]-c[j]*p[j-1]);
            q[j]=(d[j]+c[j]*q[j-1])/(a[j]-c[j]*p[j-1]);
}
	for(j=m-2; j>0; j--){
		t1[i][j]=p[j]*t0[i][j+1] + q[j];
		t3[i][j]=t0[i][j];
		t0[i][j]=t1[i][j];
		t0[0][j]=(r*tu + t0[1][j])/(r+1);

		//s=s+ pow((t1[i][j]-t2[i][j]), 2);
    }

    }
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            s=s+ pow((t1[i][j]-t2[i][j]), 2);
        }
    }
    error= sqrt(s/((m-2)*(n-2))) ;
           	iter++;
           	cout<<" error = \t \t"<<error;
} while(error >0.0001);
cout<<" no of iteration ="<<iter;

 ofstream thefile("cfd.txt");

  for(x=0,i=0; i<=n-1; x=x+dx,i++){
    for (y=0,j=0; j<=m-1; y=y+dy,j++){
        thefile<<x<<"\t"<<y<<"\t"<<t0[i][j]<<"\n";
    }
  }

end = clock();
cpu_time_used = ((double) (end - begin))/ CLOCKS_PER_SEC;
cout<<" \n"<<cpu_time_used;
    return 0;
}

