#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

// a box with vertices (x0,y0,z0), (x1,y0,z0), (x0,y1,z0), (x1,y1,z0)
//                     (x0,y0,z1), (x1,y0,z1), (x0,y1,z0), (x1,y1,z1)
// with values v000, ..., v111 on vertices
// output: trilinear interpolation on (x,y,z)

double trilinear(double x0, double x1,
		 double y0, double y1,
		 double z0, double z1,
		 double v000, double v001,
		 double v010, double v011,
		 double v100, double v101,
		 double v110, double v111,
		 double x, double y, double z) {
  
  double v=0.0;
  v += v000 * (x1-x)/(x1-x0) * (y1-y)/(y1-y0) * (z1-z)/(z1-z0);
  v += v010 * (x1-x)/(x1-x0) * (y-y0)/(y1-y0) * (z1-z)/(z1-z0);
  v += v100 * (x-x0)/(x1-x0) * (y1-y)/(y1-y0) * (z1-z)/(z1-z0);
  v += v110 * (x-x0)/(x1-x0) * (y-y0)/(y1-y0) * (z1-z)/(z1-z0);

  v += v001 * (x1-x)/(x1-x0) * (y1-y)/(y1-y0) * (z-z0)/(z1-z0);
  v += v101 * (x-x0)/(x1-x0) * (y1-y)/(y1-y0) * (z-z0)/(z1-z0);
  v += v011 * (x1-x)/(x1-x0) * (y-y0)/(y1-y0) * (z-z0)/(z1-z0);
  v += v111 * (x-x0)/(x1-x0) * (y-y0)/(y1-y0) * (z-z0)/(z1-z0);

return v;

}


double interpolate( vector< vector < vector <double> > > & data,
		    vector<double> & zero,
		    vector<double> & dxyz,
		    vector<double> & xyz) {
  int N1, N2, N3;
  N1 = data.size();
  N2 = data[0].size();
  N3 = data[0][0].size();

  //  cout << "dxyz " << dxyz[0] << " " << dxyz[1] << " " << dxyz[2] << endl;
  
  int n1, n2, n3;
  double f1, f2, f3;
  f1 = fmod( ( xyz[0] - zero[0] ), dxyz[0] * (N1-1) );
  //cout << "f1 " << f1<<endl;
  if(f1<0) f1 += dxyz[0] * (N1-1);
  //cout << "f1 " << f1 << endl;
  n1=f1/dxyz[0];
  //cout << "n1 " << n1 << endl;

  f2 = fmod( ( xyz[1] - zero[1] ), dxyz[1] * (N2-1) );
  //cout << "f2 " << f2<<endl;
  if(f2<0) f2 += dxyz[1] * (N2-1);
  //cout << "f2 " << f2 << endl;
  n2=f2/dxyz[1];
  //cout << "n2 " << n2 << endl;

  f3 = fmod( ( xyz[2] - zero[2] ), dxyz[2] * (N3-1) );
  //cout << "f3 " << f3 <<endl;
  if(f3<0) f3 += dxyz[2] * (N3-1);
  //cout << "f3 " << f3 << endl;
  n3=f3/dxyz[2];
  //cout << "n3 " << n3 << endl;

  double x0, x1, y0, y1, z0, z1;
  x0 = dxyz[0] * n1;
  y0 = dxyz[1] * n2;
  z0 = dxyz[2] * n3;
  x1 = x0 + dxyz[0];
  y1 = y0 + dxyz[1];
  z1 = z0 + dxyz[2];

  //cout << "x0,y0,z0 " << x0 << " " << y0 << " " << z0 << endl;

  double x, y, z;
  double nn1, nn2, nn3;
  x = fmod( xyz[0], ( dxyz[0] * (N1-1) ) );
  y = fmod( xyz[1], ( dxyz[1] * (N2-1) ) );
  z = fmod( xyz[2], ( dxyz[2] * (N3-1) ) );
  //cout << "x,y,z " << x << " " << y << " " << z << endl;

  if (x<0) x+= dxyz[0] * (N1-1);
  if (y<0) y+= dxyz[1] * (N2-1);
  if (z<0) z+= dxyz[2] * (N3-1);

  //  cout << "x,y,z " << x << " " << y << " " << z << endl;

  double v000, v001, v010, v011, v100, v101, v110, v111;
  v000 = data[n1][n2][n3];
  v001 = data[n1][n2][n3+1];
  v100 = data[n1+1][n2][n3];
  v101 = data[n1+1][n2][n3+1];
  v010 = data[n1][n2+1][n3];
  v011 = data[n1][n2+1][n3+1];
  v110 = data[n1+1][n2+1][n3];
  v111 = data[n1+1][n2+1][n3+1];

  return trilinear(x0, x1, y0, y1, z0, z1, v000, v001, v010, v011, v100, v101, v110, v111, x, y, z);
}

