
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

using namespace cv;
using namespace std;

int main(int argc , char** argv){
    
    int Max;
    Mat src;
    Mat accum_pix;
    Mat gray;
    Mat canny_output;
    Mat dest;
    vector<Vec4i> lines;
    
    /* l'mage 3alch ghdamin source hya khassha tkon b l gray , o hya le résultat ta3 2 images stériopiques une droite  droite et l'autre guache de la stériovision , ohad l'image kan hesslo 3liha hta kandiro l matching ola l'appariement l 'image droite et l'image gauche */
    
    ********************************************************************************************************************************************
    
    src=imread(argv[1],1);
    cvtColor(src,gray, COLOR_BGR2GRAY );
    
    ********************************************************************************************************************************************
/* il faut parcourir l'image source qui doit être en gray , et chercher le pc qui a la plus grande , ce dernier construira le nombre de colonne de notre accumulateur  "*/
    
    Max=gray.at<uchar>(0,0);
    for(int i=0 ; i < gray.rows ; i++ ){
        for(int j=0 ; j < gray.cols ; j++ ){
    	    if(Max < gray.at<uchar>(i,j))
                Max=gray.at<uchar>(i,j);	
        } 
    }
    
******************************************************************************************************************************************
    
    /* on crée l'accumulateur , accum_pix , on parcourt l'image source */
  
    accum_pix= Mat::zeros(gray.rows,Max,CV_8U);
    
    for(int i=0 ; i<gray.rows ; i++){
        for(int j=0 ; j<gray.cols ; j++){
            if(accum_pix.at<uchar>(i,gray.at<uchar>(i,j))<255)
                accum_pix.at<uchar>(i,gray.at<uchar>(i,j))++;
        }
    }
   
    
******************************************************************************************************************************************

    
    Canny(accum_pix , canny_output, 100, 200, 3);
    
    /*
       la carte    V_disparité , disparité map
    
   ici dans  canny , on aura une image qui contient une ligne oblique qui représente la route , et des lignes verticaux qui représentent tous ce qui dans l'image (la voiture ) , ces lignes doivent être Strictement au-dessus de la ligne oblique .
    
    la ligne vertical qui représente notre voiture ,c'est elle qui dans la même position et dans  le même niveau dans l'image et dans l'acccumulateur , on doit boucler pour trouver les éxtrémitées de cette droite qui représnte la voiture , pour cela on a fait la fonction line , on boucle jusqu'a trouvé les coordonéés de notre ligne qui représente l'obstacle = la voiture , implicitement les coordonnées de cette  droite  auront presque les mêmes valeurs des X , car c'est une ligne vertical ,dans notre cas on a trouvé pour la première extrmité 19 , pour la deuxième 21 , pour trouver ces     
      */
   
    HoughLinesP(canny_output, lines, 1, CV_PI/180, 50, 50, 10 );
    
   
    
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( canny_output , Point(l[0], l[1]), Point(l[2], l[3]), 255, 3, CV_AA);

        Point p1 = Point(l[0], l[1]);
        Point p2 = Point(l[2], l[3]);

        cout<<p1.x<<","<<p1.y<<endl;
        cout<<p2.x<<","<<p2.y<<endl;

   imshow("canny" , canny_output);
    imshow("source",src);
    imshow("Accum",accum_pix); 
    
        waitKey(0);
        

    }
    
    
    
******************************************************************************************************************************************

    
    Mat resultat=Mat::zeros(src.rows,src.cols,CV_8U);
    
    for(int i=0; i<= src.rows ; i++){
        for(int j=0; j<= src.cols ; j++){
                    
            if(gray.at<uchar>(i,j)>=19 and gray.at<uchar>(i,j)<=21)
                resultat.at<uchar>(i,j)=255;
                
        }      
    }
   
    

    imshow("canny" , canny_output);
    imshow("source",src);
    imshow("Accum",accum_pix); 
    imshow("Dest",resultat);
    waitKey(0);
    
    return 0;
}
DB.cpp
Affichage de DB.cpp en cours...


/*
    Après quand récupère les coordonnées des extrémités da la droite présentant 
 la voiture, précisément les  valeurs des deux  abscisses qui sont proches
 car c’est une droite verticale, on prend comme intervalle de test ces deux dernières
 valeurs. On parcourt et on  teste dans l‘image source, Si les valeurs des pics
 appartiennent à notre intervalle, nous les rendons blancs, sinon ils 
deviennent noirs, tout cela pour mieux visualiser l’obstacle.
 L’image ci-dessous illustre le résultat de ce traitement :

*/