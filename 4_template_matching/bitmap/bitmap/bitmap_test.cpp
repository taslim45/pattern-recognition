/*
 ***************************************************************************
 *                                                                         *
 *                         Platform Independent                            *
 *                   Bitmap Image Reader Writer Library                    *
 *                                                                         *
 * Author: Arash Partow - 2002                                             *
 * URL: http://partow.net/programming/bitmap/index.html                    *
 *                                                                         *
 * Copyright notice:                                                       *
 * Free use of the Platform Independent Bitmap Image Reader Writer Library *
 * is permitted under the guidelines and in accordance with the most       *
 * current version of the Common Public License.                           *
 * http://www.opensource.org/licenses/cpl1.0.php                           *
 *                                                                         *
 ***************************************************************************
*/


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "bitmap_image.hpp"


void test01()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);
   image.convert_to_grayscale();

   if (!image)
   {
      printf("test01() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   image.save_image("test01_saved.bmp");
}

void test02()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test02() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   image.save_image("test02_saved.bmp");

   image.vertical_flip();
   image.save_image("test02_saved_vert_flip.bmp");
   image.vertical_flip();

   image.horizontal_flip();
   image.save_image("test02_saved_horiz_flip.bmp");
}

void test03()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test03() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   bitmap_image subsampled_image1;
   bitmap_image subsampled_image2;
   bitmap_image subsampled_image3;

   image.subsample(subsampled_image1);
   subsampled_image1.save_image("test03_1xsubsampled_image.bmp");

   subsampled_image1.subsample(subsampled_image2);
   subsampled_image2.save_image("test03_2xsubsampled_image.bmp");

   subsampled_image2.subsample(subsampled_image3);
   subsampled_image3.save_image("test03_3xsubsampled_image.bmp");
}

void test04()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test04() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   bitmap_image upsampled_image1;
   bitmap_image upsampled_image2;
   bitmap_image upsampled_image3;

   image.upsample(upsampled_image1);
   upsampled_image1.save_image("test04_1xupsampled_image.bmp");

   upsampled_image1.upsample(upsampled_image2);
   upsampled_image2.save_image("test04_2xupsampled_image.bmp");

   upsampled_image2.upsample(upsampled_image3);
   upsampled_image3.save_image("test04_3xupsampled_image.bmp");
}

void test05()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test05() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   image.set_all_ith_bits_low(0);
   image.save_image("test05_lsb0_removed_saved.bmp");
   image.set_all_ith_bits_low(1);
   image.save_image("test05_lsb01_removed_saved.bmp");
   image.set_all_ith_bits_low(2);
   image.save_image("test05_lsb012_removed_saved.bmp");
   image.set_all_ith_bits_low(3);
   image.save_image("test05_lsb0123_removed_saved.bmp");
   image.set_all_ith_bits_low(4);
   image.save_image("test05_lsb01234_removed_saved.bmp");
   image.set_all_ith_bits_low(5);
   image.save_image("test05_lsb012345_removed_saved.bmp");
   image.set_all_ith_bits_low(6);
   image.save_image("test05_lsb0123456_removed_saved.bmp");
}

void test06()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test06() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   bitmap_image red_channel_image;
   image.export_color_plane(bitmap_image::red_plane,red_channel_image);
   red_channel_image.save_image("test06_red_channel_image.bmp");

   bitmap_image green_channel_image;
   image.export_color_plane(bitmap_image::green_plane,green_channel_image);
   green_channel_image.save_image("test06_green_channel_image.bmp");

   bitmap_image blue_channel_image;
   image.export_color_plane(bitmap_image::blue_plane,blue_channel_image);
   blue_channel_image.save_image("test06_blue_channel_image.bmp");
}

void test07()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test07() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   image.convert_to_grayscale();
   image.save_image("test07_grayscale_image.bmp");
}

void test08()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test08() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   bitmap_image image1;
   bitmap_image image2;
   bitmap_image image3;
   bitmap_image image4;

   unsigned int w = image.width();
   unsigned int h = image.height();

   if (!image.region(0,0, w / 2, h / 2,image1))
   {
      std::cout << "ERROR: upper_left_image" << std::endl;
   }

   if (!image.region((w - 1) / 2, 0, w / 2, h / 2,image2))
   {
      std::cout << "ERROR: upper_right_image" << std::endl;
   }

   if (!image.region(0,(h - 1) / 2, w / 2, h / 2,image3))
   {
      std::cout << "ERROR: lower_left_image" << std::endl;
   }

   if (!image.region((w - 1) / 2, (h - 1) / 2, w / 2, h / 2,image4))
   {
      std::cout << "ERROR: lower_right_image" << std::endl;
   }

   image1.save_image("test08_upper_left_image.bmp");
   image2.save_image("test08_upper_right_image.bmp");
   image3.save_image("test08_lower_left_image.bmp");
   image4.save_image("test08_lower_right_image.bmp");
}

void test09()
{
   const unsigned int dim = 1000;
   bitmap_image image(dim,dim);

   for (unsigned int x = 0; x < dim; ++x)
   {
      for (unsigned int y = 0; y < dim; ++y)
      {
         rgb_store col = jet_colormap[(x + y) % dim];
         image.set_pixel(x,y,col.red,col.green,col.blue);
      }
   }

   image.save_image("test09_color_map_image.bmp");
}

void test10()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test10() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   image.invert_color_planes();
   image.save_image("test10_inverted_color_image.bmp");
}

void test11()
{
   std::string file_name("image.bmp");
   bitmap_image image(file_name);

   if (!image)
   {
      printf("test11() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   for (unsigned int i = 0; i < 10; ++i)
   {
      image.add_to_color_plane(bitmap_image::red_plane,10);
      image.save_image(std::string("test11_") + static_cast<char>(48 + i) + std::string("_red_inc_image.bmp"));
   }
}

void test12()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test12() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   double* y  = new double [image.pixel_count()];
   double* cb = new double [image.pixel_count()];
   double* cr = new double [image.pixel_count()];

   image.export_ycbcr(y,cb,cr);

   for (unsigned int i = 0; i < image.pixel_count(); ++i)
   {
      cb[i] = cr[i] = 0.0;
   }

   image.import_ycbcr(y,cb,cr);
   image.save_image("test12_only_y_image.bmp");

   delete[] y;
   delete[] cb;
   delete[] cr;
}

void test13()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test13() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   double* y  = new double [image.pixel_count()];
   double* cb = new double [image.pixel_count()];
   double* cr = new double [image.pixel_count()];

   image.export_ycbcr(y,cb,cr);

   for (unsigned int j = 0; j < 10; ++j)
   {
      for (unsigned int i = 0; i < image.pixel_count(); ++i)
      {
         y[i] += 15.0;
      }

      image.import_ycbcr(y,cb,cr);
      image.save_image(std::string("test13_") + static_cast<char>(48 + j) + std::string("_y_image.bmp"));
   }

   delete[] y;
   delete[] cb;
   delete[] cr;
}

void test14()
{
   bitmap_image image(512,512);

   image.clear();
   checkered_pattern(64,64,220,bitmap_image::red_plane,image);
   image.save_image("test14_checkered_01.bmp");

   image.clear();
   checkered_pattern(32,64,100,200,50,image);
   image.save_image("test14_checkered_02.bmp");
}

void test15()
{
   bitmap_image image(1024,1024);
   image.clear();

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   ::srand(0xA5AA5AA5);
   plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,jet_colormap);
   image.save_image("test15_plasma.bmp");
}

void test16()
{
   std::string file_name("image.bmp");

   bitmap_image image(file_name);

   if (!image)
   {
      printf("test16() - Error - Failed to open '%s'\n",file_name.c_str());
      return;
   }

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   bitmap_image plasma_image(image.width(),image.height());
   plasma(plasma_image,0,0,plasma_image.width(),plasma_image.height(),c1,c2,c3,c4,3.0,jet_colormap);

   bitmap_image temp_image(image);

   temp_image.alpha_blend(0.1, plasma_image);
   temp_image.save_image("test16_alpha_0.1.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.2, plasma_image);
   temp_image.save_image("test16_alpha_0.2.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.3, plasma_image);
   temp_image.save_image("test16_alpha_0.3.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.4, plasma_image);
   temp_image.save_image("test16_alpha_0.4.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.5, plasma_image);
   temp_image.save_image("test16_alpha_0.5.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.6, plasma_image);
   temp_image.save_image("test16_alpha_0.6.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.7, plasma_image);
   temp_image.save_image("test16_alpha_0.7.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.8, plasma_image);
   temp_image.save_image("test16_alpha_0.8.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.9, plasma_image);
   temp_image.save_image("test16_alpha_0.9.bmp");
}

void test17()
{
   bitmap_image image(1024,1024);

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,jet_colormap);

   image_drawer draw(image);

   draw.pen_width(3);
   draw.pen_color(255,0,0);
   draw.circle(image.width() / 2 + 100, image.height() / 2, 100);

   draw.pen_width(2);
   draw.pen_color(0,255,255);
   draw.ellipse(image.width() / 2, image.height() / 2, 200,350);

   draw.pen_width(1);
   draw.pen_color(255,255,0);
   draw.rectangle(50,50,250,400);

   draw.pen_color(0,255,0);
   draw.rectangle(450,250,850,880);

   image.save_image("test17_image_drawer.bmp");
}

void test18()
{
   bitmap_image image(1000,180);
   image_drawer draw(image);
   const rgb_store* colormap[9] = {
                                    autumn_colormap,
                                    copper_colormap,
                                    gray_colormap,
                                    hot_colormap,
                                    hsv_colormap,
                                    jet_colormap,
                                    prism_colormap,
                                    vga_colormap,
                                    yarg_colormap
                                  };

   for (unsigned int i = 0; i < image.width(); ++i)
   {
      for (unsigned int j = 0; j < 9; ++j)
      {
         draw.pen_color(colormap[j][i].red,colormap[j][i].green,colormap[j][i].blue);
         draw.vertical_line_segment(j * 20, (j + 1) * 20, i);
      }
   }

   image.save_image("test18_color_maps.bmp");
}

int main()
{
   test01();
   /*
   test02();
   test03();
   test04();
   test05();
   test06();
   test07();
   test08();
   test09();
   test10();
   test11();
   test12();
   test13();
   test14();
   test15();
   test16();
   test17();
   test18();
   */
   return 0;
}


/*
   Note: In some of the tests a bitmap image by the name of 'image.bmp'
         is required. If not present the test will fail.
*/
