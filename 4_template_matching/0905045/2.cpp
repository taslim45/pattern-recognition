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

int row[]={0,-1,0,1,-1,1, 1,-1};
int col[]={1,0,-1,0, 1,1,-1,-1};

vector< pair<int,int> > getPoints(int r,int c,int k)
{
	vector<pair<int,int> > v;
	int mr=r,mc=c;
	v.push_back(make_pair(r,c));
	for(int i=0;i<8;i++)
    {
		int nr = mr + row[i]*(1<<k);
		int nc = mc + col[i]*(1<<k);
		v.push_back(make_pair(nr,nc));
	}
	return v;

}

void correlationtest(Image &img,Image &temp)
{
    int bestX=-1,bestY=-1;
    double best;
    double maxx,var;
    maxx = 1e-100;
    int i,j;
    int n = img.height;
    int m = temp.height;
    int brow = n/2;
    int bcol = n/2;
    int itr = log(n-1)/log(2)-1;

    while(itr)
    {
        vector < pair <int,int> > points = getPoints(brow,bcol,itr);
        itr--;

        for(int k=0; k<points.size(); k++)
        {
            int p = points[k].first;
            int q = points[k].second;

            if(p+m>=n) continue;
            if(q+m>=n) continue;
            double a,b,c;
            a = b = c = 0.0;

            for(j=0; j<temp.width; j++)
            {
                for(i=0; i<temp.height; i++)
                {
                    img.collectPixelAt(p+i,q+j);
                    rgb refImg(img.r,img.g,img.b);
                    temp.collectPixelAt(i,j);
                    rgb refTemp(temp.r,temp.g,temp.b);

                    //printf("%d %d %d\n",refImg.r,refImg.g,refImg.b);
                    b += (refImg.r)*(refImg.r);
                    c += (refTemp.r)*(refTemp.r);
                    a += (refImg.r*refTemp.r);
                    //SAD += diff(refImg,refTemp);
                }
            }
            var = a / sqrt(b*c);
            if(var >= maxx)
            {
                maxx = var;
                bestX = p;
                bestY = q;
                best = var;
            }
        }
    }

    printf("%d %d\n",bestX,bestY);

    bitmap_image imgg("image2.bmp");
    unsigned char r = 255;
    unsigned char g = 0;
    unsigned char b = 0;
    imgg.set_pixel(bestX,bestY,r,g,b);
    imgg.save_image("result_logarithm.bmp");
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
