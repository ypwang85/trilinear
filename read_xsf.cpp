#include<string>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;

// read the scalar field in xsf format, suppose lattice vectors a, b, c are perpendicular to each other
// 
void read_xsf( string xsf_file_name, vector< vector< vector<double> > > & data, vector<double> & zero, vector<double> & dxyz) {
  ifstream xsf;
  xsf.open(xsf_file_name);
  
  string strtmp;
  size_t found;
  
  for(;;) {
    getline(xsf, strtmp);
    found = strtmp.find("BEGIN_BLOCK_DATAGRID_3D");
    if (found != string::npos) break;
  }

  getline(xsf, strtmp);
  getline(xsf, strtmp);

  int n1, n2, n3;
  xsf >> n1 >> n2 >> n3;

  cout << n1 << " " << n2 << " " << n3 << endl;

  double z1, z2, z3;
  xsf >> z1 >> z2 >> z3;
  getline(xsf, strtmp);
  zero.push_back(z1);
  zero.push_back(z2);
  zero.push_back(z3);

  xsf >> z1; getline(xsf, strtmp);
  dxyz.push_back( z1/(n1-1) );

  xsf >> z1 >> z2; getline(xsf, strtmp);
  dxyz.push_back( z2/(n2-1) );

  xsf >> z1 >> z2 >> z3; getline(xsf, strtmp);
  dxyz.push_back( z3/(n3-1) );

  cout << "dxyz " << dxyz[0] << " " << dxyz[1] << " " << dxyz[2] << endl;

  // begin to read data
  data.resize( n1 );
  for(int i=0; i<n1; i++ ) {
    data[i].resize(n2);
    for(int j=0; j<n2; j++ ) {
      data[i][j].resize(n3);
    }
  }
  
  double dtmp;
  int index1=0;
  int index2=0;
  int index3=0;
  while(xsf >> dtmp) {
    data[index1][index2][index3] = dtmp;
    //cout << index1 << " " << index2 << " " << index3 << " " << data[index1][index2][index3] << endl;

    index1 ++;
    if ( index1 > n1-1 ) {
      index2 ++;
      index1 = 0;
    }
    if( index2 > n2-1 ) {
      index3 ++;
      index2 = 0;
    }
  }

  xsf.close();
}
