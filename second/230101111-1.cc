#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

  float upto(int value){
    return ((int)(100*value))/100.00;
  }

  void printout(int i; int j; struct matrix** image){
    outFile<<"("<<i<<","<<j<<") : g_x: "<<upto(image[i][j].gx)<<", g_y :"<<upto(image[i][j].gy)<<", G :"<<upto(image[i][j].G);
  }

  //TASK-1
struct matrix{
  float gx;
  float gy;
  float G;
  int value;
};

struct meta_data{
  int image_rows;
  int image_columns;
  int kx_rows;
  int kx_columns;
  int ky_rows;
  int ky_columns;
};

    //TASK-3
void compute_gx(struct matrix** kx,struct matrix** image,int i,int j,struct meta_data data){
  for(int l=i-1;l<=i+1;l++){
    for(int m=j-1;m<=j+1;m++){
      if(l==i && m==j || l>data.image_rows-1 || m>data.image_columns-1) continue;
      if(l<0 || m<0) continue;
      image[i][j].gx += kx[l-i+1][m-j+1]*image[l][m];
    }
  }
}

void compute_gy(struct matrix** ky,struct matrix** image,int i,int j,struct meta_data data){
  for(int l=i-1;l<=i+1;l++){
    for(int m=j-1;m<=j+1;m++){
      if(l==i && m==j) continue;
      if(l<0 || m<0 || l>data.image_rows-1 || m>data.image_columns-1) continue;
      image[i][j].gy += ky[l-i+1][m-j+1]*image[l][m];
    }
  }
}

void compute_g(struct matrix** image,int i,int j){
  image.G[i][j]=sqrt(image[i][j].gx*image[i][j].gx + image[i][j].gy*image[i][j].gy);
}

int main(){
  struct matrix** kx;
  struct matrix** ky;
  struct matrix** image;

  struct meta_data data;

  ifstream in("kx.txt");
  in>>data.kx_rows>>data.kx_columns;

  kx = new struct matrix* [data.kx_rows];
  for(int i=0;i<data.kx_rows;i++){
    kx[i] = new struct matrix [data.kx_columns];
  }

  for(int i=0;i<data.kx_rows;i++){
    for(int j=0;j<data.kx_columns;j++){
      in>>kx[i][j].value;
    }
  }

  ifstream in("ky.txt");
  in>>data.ky_rows>>data.ky_columns;

  ky = new struct matrix* [data.ky_rows];
  for(int i=0;i<data.ky_rows;i++){
    ky[i] = new struct matrix [data.ky_columns];
  }

  for(int i=0;i<data.ky_rows;i++){
    for(int j=0;j<data.ky_columns;j++){
      in>>ky[i][j].value;
    }
  }

  ifstream in("image.txt");
  in>>data.image_rows>>data.image_columns;

  image = new struct matrix* [data.image_rows];
  for(int i=0;i<data.image_rows;i++){
    image[i] = new struct matrix [data.image_columns];
  }

  for(int i=0;i<data.image_rows;i++){
    for(int j=0;j<data.image_columns;j++){
      in>>image[i][j].value;
    }
  }

  // TASK-4
  for(int i=0;i<data.image_rows;i++){
    for(int j=0;j<data.image_columns;j++){
      compute_gx(kx,image,i,j,data);
      compute_gy(ky,image,i,j,data);
      compute_g(image,i,j);
    }
  }

  //TASK-5
  ofstream outFile("output-1.txt");
  if(!outFile){cerr<<"error openig file";}
  else{
    for(int i=0;i<data.image_rows;i++){
      for(int j=0;j<data.image_columns;j++){
        printout(i,j,image);
      }
    }
  }

  //TASK-6
  struct matrix** lambda_image;
  image = new struct matrix* [data.image_rows];
  for(int i=0;i<data.image_rows;i++){
    image[i] = new struct matrix [data.image_columns];
  }
  for(int i=0;i<data.image_rows;i++){
    for(int j=0;j<data.image_columns;i++){
      lambda_image[i][j]=image[i][j];
    }
  }
  auto lambda_compute_gx = [&kx,&lambda_image](int i,int j) -> float{
    float ans=0;
    for(int l=i-1;l<=i+1;l++){
      for(int m=j-1;m<=j+1;m++){
        if(l==i && m==j || l>(sizeof(sizeof(*lambda_image)/sizeof(lambda_image[1])))-1 || m>(sizeof(lambda_image[1])/sizeof(lambda_image[0][0]))-1) continue;
        if(l<0 || m<0) continue;
        ans+= kx[l-i+1][m-j+1]*lambda_image[l][m];
      }
    }
    return ans;
  };

  auto lambda_compute_gy = [&ky,&lambda_image](int i,int j) -> float{
    float ans=0;
    for(int l=i-1;l<=i+1;l++){
      for(int m=j-1;m<=j+1;m++){
        if(l==i && m==j || l>(sizeof(sizeof(*lambda_image)/sizeof(lambda_image[1])))-1 || m>(sizeof(lambda_image[1])/sizeof(lambda_image[0][0]))-1) continue;
        if(l<0 || m<0) continue;
        ans+= ky[l-i+1][m-j+1]*lambda_image[l][m];
      }
    }
    return ans;
  };

  float lambda_compute_G=[](float lambda_image[i][j].gx,float lambda_image[i][j].gy) -> float{
    return sqrt(lambda_compute_gx*lambda_compute_gx+lambda_compute_gx*lambda_compute_gx);
  }

  //TASK-7
  for(int i=0;i<data.image_rows;i++){
    for(int j=0;j<data.image.columns;j++){
      lambda_image[i][j].gx= lambda_compute_gx(kx,image,i,j);
      lambda_image[i][j].gy= lambda_compute_gy(ky,image,i,j);
      lambda_image[i][j].G= lambda_compute_G(lambda_image[i][j].gx,lambda_image[i][j].gy);
    }
  }

  
}