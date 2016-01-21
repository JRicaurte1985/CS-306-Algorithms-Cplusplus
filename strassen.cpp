/**************************************************
* Program:
*    Stub Strassen, Matrix Multiplication
*    Brother Neff, CS306
* Author:
*    Brother Neff
* Summary: 
*    Stub code for the pressed-for-time student.
* Note:
*    A distinct lack of comments. This is intentional.
************************************************************/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Matrix
{
private:
   int** mRows;
   int mSize;

public:
   int getSize()
   {
      return mSize;
   }
   
   Matrix(int size)
   {
      mRows = new int*[size];
      for (int i = 0; i < size; i++)
      {
         mRows[i] = new int[size];
      }   
      mSize = size;
   }

   Matrix(const Matrix& matrixB)
   {
      mSize = matrixB.getSize();

      mRows = new int*[mSize];
      for (int i = 0; i < mSize; i++)
      {
         mRows[i] = new int[mSize];
         for (int j = 0; j < mSize; j++)
         {
            mRows[i][j] = matrixB.mRows[i][j];
         }
      }
   }

   Matrix& operator=(const Matrix& matrixB)
   {
      cerr << "am i ever here? " << endl;
      
      for (int i = 0; i < mSize; i++)
      {
         delete [] mRows[i];
      }
      delete [] mRows;

      mSize = matrixB.getSize();

      mRows = new int*[mSize];
      for (int i = 0; i < mSize; i++)
      {  
         mRows[i] = new int[mSize];  
         for (int j = 0; j < mSize; ++j)  
            mRows[i][j] = matrixB.mRows[i][j];  
      }
      
      return *this;  
   }  

   ~Matrix()
   {
      for (int i = 0; i < mSize; i++)
      {
         delete [] mRows[i];
      }   
      delete [] mRows;
   }

   int* operator[](int row) const
   {
      return mRows[row];
   }

   int getSize() const
   {
      return mSize;
   }

   void read(istream& is) const
   {
      for (int i = 0; i < mSize; i++)
      {
         for (int j = 0; j < mSize; j++)
         {
            is >> mRows[i][j];
         }      
      }
   }

   void write(ostream& os) const
   {
      for (int i = 0; i < mSize; i++)
      {
         for (int j = 0; j < mSize; j++)
         {
            os << mRows[i][j] << " ";
         }
         os << endl;
      }
   }

   Matrix operator+(Matrix matrixB)
   {
      Matrix result(mSize);
      
      for (int i = 0; i < mSize; i++)
         for (int j = 0; j < mSize; j++)   
            result[i][j] = (*this)[i][j] + matrixB[i][j];
         
      return result;
   }

   Matrix operator-(Matrix matrixB)
   {
      Matrix result(mSize);
      
      for (int i = 0; i < mSize; i++)
         for (int j = 0; j < mSize; j++)
            result[i][j] = (*this)[i][j] - matrixB[i][j];
             
      return result;
   }

   Matrix getQuadrant(int a, int b)
   {
      int newSize = mSize / 2;
      Matrix result(newSize);
   
      for (int i = a * newSize; i < newSize + (a * newSize); i++)
         for (int j = b * newSize; j < newSize + (b * newSize); j++)
            result[i - (a * newSize)][j - (b * newSize)] = (*this)[i][j];   
   
      return result;
   }
                   
   void putQuadrant(int a, int b, Matrix aMatrix)
   {
      for (int i = 0; i < aMatrix.mSize; i++)
      {
         for (int j = 0; j < aMatrix.mSize; j++)
         {
            (*this)[(a * aMatrix.mSize) + i][(b * aMatrix.mSize) + j] =
                   aMatrix[i][j];
         }
      }
   }
   
   Matrix operator*(Matrix matrixB)
   {
      Matrix result(mSize);
    
      if (mSize == 1)
      {
         result[0][0] = (*this)[0][0] * matrixB[0][0];
         return result;
      }
      
      Matrix A00 = this->getQuadrant(0,0);
      Matrix A01 = this->getQuadrant(0,1);
      Matrix A10 = this->getQuadrant(1,0);
      Matrix A11 = this->getQuadrant(1,1);

      Matrix B00 = matrixB.getQuadrant(0,0);
      Matrix B01 = matrixB.getQuadrant(0,1);
      Matrix B10 = matrixB.getQuadrant(1,0);
      Matrix B11 = matrixB.getQuadrant(1,1);
      
      Matrix M1 = (A00 + A11) * (B00 + B11);
      Matrix M2 = (A10 + A11) * B00;
      Matrix M3 =  A00 * (B01 - B11);
      Matrix M4 =  A11 * (B10 - B00);
      Matrix M5 = (A00 + A01) * B11;
      Matrix M6 = (A10 - A00) * (B00 + B01);
      Matrix M7 = (A01 - A11) * (B10 + B11);
      
      result.putQuadrant(0, 0, M1 + M4 - M5 + M7);
      result.putQuadrant(0, 1, M3 + M5);
      result.putQuadrant(1, 0, M2 + M4);
      result.putQuadrant(1, 1, M1 + M3 - M2 + M6);
   
      return result;
   }

};

istream& operator>>(istream& is, const Matrix& m)
{
   m.read(is);
   return is;
}

ostream& operator<< (ostream& os, const Matrix& m)
{
   m.write(os);
   return os;
}


int main(int argc, char* argv[])
{
   int size = 32;
   ifstream inFile;
   string file;

   if (argc == 2)
   {
      file = argv[1];
   }
   else if (argc > 2)
   {
      file = argv[1];
      size = atoi(argv[2]);
   }
   else 
   {
      file = "/home/cs306/files/diviconq.in";
   }   

   Matrix matrixA(size);
   Matrix matrixB(size);

   inFile.open(file.c_str());
   
   if (inFile.is_open())
   {
      inFile >> matrixA >> matrixB;
      inFile.close();
   }
   else 
   {
      cout << "Unable to open " + file;
      return 1;
   }

   cout << (matrixA * matrixB);

   return 0;
}
