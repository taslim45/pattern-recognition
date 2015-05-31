#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stack>
#include <queue>

#include "bitmap_image.hpp"
using namespace std;

struct rgb
{
    int r,g,b;
    rgb(int _r,int _g,int _b)
    {
        r = _r, g = _g, b = _b;
    }
};

class Image
{
public:
    string file_name;
    bitmap_image image;
    int height,width;
    unsigned char r,g,b;
    Image(string name)
    {
        file_name = name;
        image = bitmap_image(file_name);
        //printf("%d %d\n",image.width(),image.height());
        height = image.height();
        width = image.width();
    }
    void greyscale()
    {
        image.convert_to_grayscale();
    }
    bitmap_image getImage()
    {
        return image;
    }
    void saveImage(string name)
    {
        image.save_image(name);
    }
    void collectPixelAt(int x,int y)
    {
        image.get_pixel(x,y,r,g,b);
    }
};
double diff(rgb &a, rgb &b)
{
    /*
    double p = (a.r - b.r)*(a.r - b.r);
    double q = (a.g - b.g)*(a.g - b.g);
    double r = (a.b - b.b)*(a.b - b.b);
    return sqrt(p + q + r);
    */
    double p = (a.r * a.r) + (a.g * a.g) + (a.b * a.b);
    double q = (b.r * b.r) + (b.g * b.g) + (b.b * b.b);

}
void correlationtest(Image &img,Image &temp)
{
    int bestX=-1,bestY=-1;
    double bestSAD;
    double maxSAD,SAD;
    maxSAD = -1;
    int i,j;
    for(int x=0; x<=img.height - temp.height; x++)
    {
        for(int y=0; y<=img.width - temp.width; y++)
        {
            SAD = 0.0;
            double a,b,c;
            a = b = c = 0.0;
            for(j=0; j<temp.width; j++)
            {
                for(i=0; i<temp.height; i++)
                {
                    img.collectPixelAt(x+i,y+j);
                    rgb refImg(img.r,img.g,img.b);
                    temp.collectPixelAt(i,j);
                    rgb refTemp(temp.r,temp.g,temp.b);

                    b += (refImg.r*refImg.r) + (refImg.g*refImg.g) + (refImg.b*refImg.b);
                    c += (refTemp.r*refTemp.r) + (refTemp.g*refTemp.g) + (refTemp.b*refTemp.b);
                    a += (refImg.r*refImg.r) + (refImg.g*refImg.g) + (refImg.b*refImg.b) + (refTemp.r*refTemp.r) + (refTemp.g*refTemp.g) + (refTemp.b*refTemp.b);
                    //SAD += diff(refImg,refTemp);
                }
                SAD = a / sqrt(b*c);
                if(SAD > maxSAD)
                {
                    maxSAD = SAD;
                    // give me min SAD
                    bestX = x;
                    bestY = y;
                    bestSAD = SAD;
                }
            }
        }
    }
    printf("%d %d\n",bestX,bestY);

    bitmap_image imgg("image2.bmp");
    unsigned char r = 255;
    unsigned char g = 0;
    unsigned char b = 0;
    imgg.set_pixel(bestX,bestY,r,g,b);
    imgg.save_image("result.bmp");
}

int main()
{
    Image img("image2.bmp");
    img.greyscale();
    img.saveImage("grey_image2.bmp");

    Image temp("template2.bmp");
    temp.greyscale();
    temp.saveImage("grey_template2.bmp");

    correlationtest(img,temp);
    return 0;
}
