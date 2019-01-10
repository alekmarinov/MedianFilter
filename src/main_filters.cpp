//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_filters.h"
#include <math.h>
#include <stdlib.h>
//#include <qsort.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// load bitmap
void __fastcall TForm1::loadClick(TObject *Sender)
{
        if (openDialog->Execute())
        {
                Image1->Picture->LoadFromFile(openDialog->FileName);
        }
}
//---------------------------------------------------------------------------
// generate new intensity for pixel(x,y) as of the filter
void TForm1::multiply(float matrix[3][3], int x, int y)
{
        int r=0,g=0,b=0;
        unsigned int color;
        for (int j=-1; j<=1; j++)
        for (int i=-1; i<=1; i++)
        {
                color=(x+i>=0 && y+j>=0 && x+i<Image1->Picture->Width-1 && y+j<Image1->Picture->Height-1)?
                        Image1->Picture->Bitmap->Canvas->Pixels[x+i][y+j]:0;
                r+=(int)ceil(matrix[1+i][1+j]*((color>>16)&0xFF));
                g+=(int)ceil(matrix[1+i][1+j]*((color>>8)&0xFF));
                b+=(int)ceil(matrix[1+i][1+j]*((color)&0xFF));
        }

        //r/=9;
        if (r>255)r=255; if (r<0)r=0;
        //g/=9;
        if (g>255)g=255; if (g<0)g=0;
        //b/=9;
        if (b>255)b=255; if (b<0)b=0;
        color=(r<<16)|(g<<8)|b;
        Image2->Canvas->Pixels[x][y]=color;
}


// apply custom filter
void __fastcall TForm1::filterClick(TObject *Sender)
{
        float n[3][3];

        float d=atof(div->Text.c_str());
        n[0][0]=atof(m11->Text.c_str())/d;
        n[0][1]=atof(m12->Text.c_str())/d;
        n[0][2]=atof(m13->Text.c_str())/d;
        n[1][0]=atof(m21->Text.c_str())/d;
        n[1][1]=atof(m22->Text.c_str())/d;
        n[1][2]=atof(m23->Text.c_str())/d;
        n[2][0]=atof(m31->Text.c_str())/d;
        n[2][1]=atof(m32->Text.c_str())/d;
        n[2][2]=atof(m33->Text.c_str())/d;


        Image2->Canvas->FillRect(TRect(0, 0, Image2->Width-1, Image2->Height-1));

        ProgressBar1->Min=0;
        ProgressBar1->Max=Image1->Picture->Height;
        for (int j=0; j<Image1->Picture->Height; j++)
        for (int i=0; i<Image1->Picture->Width; i++)
        {
                ProgressBar1->Position=j;
                multiply(n, i, j);
        }
}
//---------------------------------------------------------------------------
// copy right image over left image
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        for (int j=0; j<Image2->Picture->Height; j++)
          for (int i=0; i<Image2->Picture->Width; i++)
          {
                Image1->Canvas->Pixels[j][i]=Image2->Canvas->Pixels[j][i];
          }
}
//---------------------------------------------------------------------------
// do median filter
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        unsigned int n[3*3];      
        ProgressBar1->Min=0;
        ProgressBar1->Max=Image1->Picture->Height;
        for (int j=0; j<Image1->Picture->Height; j++)
        {
          for (int i=0; i<Image1->Picture->Width; i++)
          {
                  for (int k=-1; k<=1; k++)
                  for (int l=-1; l<=1; l++)
                  {
                          n[1+l + (1+k)*3]=(i+l>=0 && j+k>=0 && i+l<=Image1->Picture->Width-1 && j+k <= Image1->Picture->Height-1)?Image1->Canvas->Pixels[i+l][j+k]:0;
                  }

                  for (int k=0; k<9; k++)
                  for (int l=k+1; l<9; l++)
                  {
                        unsigned int a1=n[k];
                        unsigned int b1=n[l];

                        int a2=((a1&0xFF) + ((a1>>8)&0xFF) + ((a1>>16)&0xFF))/3;
                        int b2=((b1&0xFF) + ((b1>>8)&0xFF) + ((b1>>16)&0xFF))/3;

                        if (a2>b2)
                        {
                                int temp=n[l];
                                n[l]=n[k];
                                n[k]=temp;
                        }
                  }

                  //qsort(n, 9, sizeof(int), sort_function);
                  Image2->Canvas->Pixels[i][j]=n[4];
          }
          ProgressBar1->Position=j;
        }
}
//---------------------------------------------------------------------------
// create random noise
void __fastcall TForm1::noiseClick(TObject *Sender)
{
        randomize();
        int count=atoi(num->Text.c_str());
        for (int i=0; i<count; i++)
        {
                Image1->Canvas->Pixels[rand() % Image1->Picture->Width][rand() % Image1->Picture->Height] = 0xFFFFFF;
        }
}
//---------------------------------------------------------------------------
//load rectangular coefficients
void __fastcall TForm1::Rectangle1Click(TObject *Sender)
{
        m11->Text=1;
        m12->Text=1;
        m13->Text=1;
        m21->Text=1;
        m22->Text=1;
        m23->Text=1;
        m31->Text=1;
        m32->Text=1;
        m33->Text=1;
        div->Text=9;

}
//---------------------------------------------------------------------------
//load Gauss coefficients
void __fastcall TForm1::Gauss1Click(TObject *Sender)
{
        m11->Text=1;
        m12->Text=2;
        m13->Text=1;
        m21->Text=2;
        m22->Text=4;
        m23->Text=2;
        m31->Text=1;
        m32->Text=2;
        m33->Text=1;
        div->Text=16;
}

//---------------------------------------------------------------------------
// load Sobel coefficients
void __fastcall TForm1::Sobel1Click(TObject *Sender)
{
        m11->Text=-1;
        m12->Text=0;
        m13->Text=1;
        m21->Text=-2;
        m22->Text=0;
        m23->Text=2;
        m31->Text=-1;
        m32->Text=0;
        m33->Text=1;
        div->Text=1;

}
//---------------------------------------------------------------------------
//load Laplace coefficients
void __fastcall TForm1::Laplace1Click(TObject *Sender)
{         
        m11->Text=-1;
        m12->Text=-2;
        m13->Text=-1;
        m21->Text=-2;
        m22->Text=12;
        m23->Text=-2;
        m31->Text=-1;
        m32->Text=-2;
        m33->Text=-1;
        div->Text=1;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sobel2Click(TObject *Sender)
{                   
        m11->Text=-1;
        m12->Text=-2;
        m13->Text=-1;
        m21->Text=0;
        m22->Text=0;
        m23->Text=0;
        m31->Text=1;
        m32->Text=2;
        m33->Text=1;
        div->Text=1;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Laplace2Click(TObject *Sender)
{
        m11->Text=0;
        m12->Text=-1;
        m13->Text=0;
        m21->Text=-1;
        m22->Text=4;
        m23->Text=-1;
        m31->Text=0;
        m32->Text=-1;
        m33->Text=0;
        div->Text=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BasicHighPass1Click(TObject *Sender)
{          
        m11->Text=-1;
        m12->Text=-1;
        m13->Text=-1;
        m21->Text=-1;
        m22->Text=9;
        m23->Text=-1;
        m31->Text=-1;
        m32->Text=-1;
        m33->Text=-1;
        div->Text=1;

}
//---------------------------------------------------------------------------

