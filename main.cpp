#include<string>
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;

void read_xsf( string xsf_file_name, vector< vector< vector<double> > > & data, vector<double> & zero, 
vector<double> & dxyz);

double interpolate( vector< vector < vector <double> > > & data,
		    vector<double> & zero,
		    vector<double> & dxyz,
		    vector<double> & xyz);



int main() {
  string xsf_file_name ("ELFCAR.xsf-up");
  vector< vector< vector<double> > > data;
  vector<double> zero, dxyz;
  read_xsf( xsf_file_name, data, zero, dxyz);

  vector<double> xyz;
  xyz.resize(3);
  xyz[0] = -0.1;
  xyz[1] = -0.1;
  xyz[2] = -0.1;
  cout << interpolate(data, zero, dxyz, xyz);


  vector<double> center;
  vector<double> vector1;
  vector<double> vector2;
  double length;
  double range;
  int ngrid;

  center.resize(3);
  cout << "The center: ";
  cin >> center[0] >> center[1] >> center[2];

  vector1.resize(3);
  cout << "vector 1: ";
  cin >> vector1[0] >> vector1[1] >> vector1[2];
  length = vector1[0] * vector1[0];
  length+= vector1[1] * vector1[1];
  length+= vector1[2] * vector1[2];
  length = sqrt(length);
  vector1[0] /= length;
  vector1[1] /= length;
  vector1[2] /= length;
  
  vector2.resize(3);
  cout << "vector 2: ";
  cin >> vector2[0] >> vector2[1] >> vector2[2];
  length = vector2[0] * vector2[0];
  length+= vector2[1] * vector2[1];
  length+= vector2[2] * vector2[2];
  length = sqrt(length);
  vector2[0] /= length;
  vector2[1] /= length;
  vector2[2] /= length;

  cout << "range: ";
  cin >> range;

  cout << "number of grids: ";
  cin >> ngrid;

  for(int i=0; i<2*ngrid; i++) {
    for(int j=0; j<2*ngrid; j++) {
      xyz[0] = center[0] + (i-ngrid)*vector1[0]*range/ngrid + (j-ngrid)*vector2[0]*range/ngrid;
      xyz[1] = center[1] + (i-ngrid)*vector1[1]*range/ngrid + (j-ngrid)*vector2[1]*range/ngrid;
      xyz[2] = center[2] + (i-ngrid)*vector1[2]*range/ngrid + (j-ngrid)*vector2[2]*range/ngrid;

      cout << "x,y,z,a,b,v " << xyz[0] << " " << xyz[1] << " "<< xyz[2]<<" "
	   << (i-ngrid)*range/ngrid << " " << (j-ngrid)*range/ngrid << " "
	   << interpolate(data, zero, dxyz, xyz) << endl;;
    }
  }


}

  
