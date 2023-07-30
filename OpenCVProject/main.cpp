#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <dirent.h>

#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
int Carre(int x);

int main (int argc, char* argv[])
{

  const Scalar blue = Scalar (255, 0, 0); 
  const Scalar white = Scalar (255,255, 255); 
  Mat img = Mat (500, 700, CV_8UC3, blue); 
  const char* window_title = "Hello, OpenCV!";
 
  /* Création d'une fenêtre intitulée "Hello, OpenCV!
  " */
  //namedWindow (window_title, CV_WINDOW_AUTOSIZE);

  Size sizeBanque(32, 32);
  Size imgSize(1024, 1024);
  char Buffer[10];
  char chaine[50]; 
  vector<Mat> BANQUEIMG = vector<Mat>(30);
  vector<int> BANQUEIMGLUM = vector<int>(30);
  
  for (int i = 0; i < 30; i++)
  {
	//  itoa(i, Buffer, 10);
	  sprintf(chaine, "banqueImg/%d.jpg", i);
	  BANQUEIMG.at(i) = imread(chaine);
	  resize(BANQUEIMG.at(i), BANQUEIMG.at(i), sizeBanque);

	  Mat imageGrey = BANQUEIMG.at(i);
	  cvtColor(imageGrey, imageGrey, CV_RGB2GRAY);

	  int LuminanceImg = 0;
	  for (int z = 0; z < 32; z++)
	  {
		  for (int e = 0; e < 32; e++)
		  {
			  LuminanceImg += imageGrey.at<uchar>(z, e);

		  }
	  }
	  LuminanceImg /= 128;

	  BANQUEIMGLUM.at(i) = LuminanceImg;



  }

 

  Mat src;

  src = imread("moa6.jpg");
  resize(src, src, imgSize);
  int count = 0;
  Mat imGray;
  cvtColor(src, imGray, CV_RGB2GRAY);
  char nom[50];
  int LuminanceMap[1024][1024];
  Mat MatriceFinal = Mat(1024, 1024, CV_8UC3);
  for (int i = 0; i < 1024 / 32; i++)
  {
	  for (int j = 0; j < 1024 / 32; j++)
	  {
		  count++;
		  Rect myCrop(i * 32, j * 32, 32, 32);
		  Mat croppedImage = src(myCrop);
		  Mat croppedImageGrey = croppedImage;
		  cvtColor(croppedImageGrey, croppedImageGrey, CV_RGB2GRAY);

		  int LuminanceImg = 0;

		  double dst = 0;


			  for (int z = 0; z < 32; z++)
			  {
				  for (int e = 0; e < 32; e++)
				  {
					   LuminanceImg += croppedImageGrey.at<uchar>(z, e);
					  
					//  dst += Carre(croppedImageGrey.at<uchar>(z, e) - BANQUEIMGLUM[u]);
					  
					  /*for(int z = 0; z  < vecteursW[0].getparamSize(); z++)
					  {
					  dst += Carre(Noeuds[i][j].getVecteur().getParam(z) - vecteursData[indexTab[o]].getParam(z));

					  }
					  dst = Math.sqrt(dst);

					  if(dst < smallDistance)
					  {
					  Noeuds[i][j].setEtiquette(vecteursData[indexTab[o]].getEtq());
					  Noeuds[i][j].getVecteur().setEtq(vecteursData[indexTab[o]].getEtq());
					  smallDistance = dst;

					  }

					  dst = 0;
					  }
					  smallDistance = 5;*/



				  }
			  }

		  
		
			  LuminanceImg /= 32;

		  LuminanceMap[i][j] = LuminanceImg;

		  int Diff = 0;
		  int BestDiff = 10000;

		  int iOfBestDiff = 0;
		  for (int z = 0; z < 30; z++)
		  {
			  Diff = Carre(LuminanceMap[i][j] - BANQUEIMGLUM.at(z));
			  Diff = sqrt(Diff);
			  if (Diff < BestDiff)
			  {
				  BestDiff = Diff;
				  iOfBestDiff = z;
			  }
		  }

	
		 //MatriceFinal.at<Mat>(i*32, j*32) = BANQUEIMG.at(iOfBestDiff);


		  BANQUEIMG.at(iOfBestDiff).copyTo(MatriceFinal(cv::Rect(i* 32, j* 32, 32, 32)));
		  

		

		  //sprintf(nom, "%d", count);
		  //imshow(nom, croppedImage);	
	  }
  }


  //0.21R+0.72G+0.07B



  imshow("moa9", MatriceFinal);
  /* Affichage de l'image */
  //imshow ("moa", MatriceFinal[0][0]);




  /* Pause le temps que l'utilisateur appuie sur une touche */
  waitKey (0);

  return EXIT_SUCCESS;
}

int Carre(int x)
{
	return x*x;
}


