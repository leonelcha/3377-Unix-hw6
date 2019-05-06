/*
 * File:                main.cc
 * Date                 04/16/19
 * Author                Leonel Chacon
 * Email                 lxc171030@utdallas.edu
 * Course                CS 3377.501 Spring 2019
 * Version               1.0
 *
 * Copyright 2019, All Rights Reserved
 * Description
 *   Using
 */

#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <sstream>
#include <string>
#include <fstream>
#include "cdk.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary Matrix"

using namespace std;

class BinaryFileHeader{
public:
  uint32_t magicNumber;         /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

/*
 * Records in the file have a fixed length buffer
 * that will hold a C‐Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;
class BinaryFileRecord{
public:
  uint8_t strLength;
  char   stringBuffer[maxRecordStringLength];
};

int main(){
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "A", "B", "C"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};


  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL){
      printf("Error creating Matrix\n");
      _exit(1);
    }

  string strConvert;
 
 /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  if(!binInfile.is_open()){
    cout << "uh oh" << endl;
  }

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  stringstream ss;

  ss << hex << uppercase << myHeader->magicNumber;
  strConvert = "Magic: 0x";
  strConvert = strConvert.c_str();
  strConvert +=  ss.str();

  setCDKMatrixCell(myMatrix, 1, 1, strConvert.c_str());
  drawCDKMatrix(myMatrix, true);
  
  ss.str("");
  strConvert = "Version: ";
  ss << dec << myHeader->versionNumber;
  strConvert += ss.str();
  
  setCDKMatrixCell(myMatrix, 1, 2, strConvert.c_str());
  drawCDKMatrix(myMatrix, true);

  ss.str("");
  strConvert = "NumRecords: ";
  ss << myHeader->numRecords;
  strConvert += ss.str();

  setCDKMatrixCell(myMatrix, 1 ,3, strConvert.c_str());
  drawCDKMatrix(myMatrix, true);
  
  string buffer;
  int length;
  for(int i = 2; i < 6 && binInfile.read((char *) myRecord, sizeof(BinaryFileRecord)); i++){
    ss.str("");
    ss << myRecord->stringBuffer;
    buffer = ss.str();
    length = buffer.length();
    strConvert = "strLength: ";
    ss.str("");
    ss << length;
    strConvert += ss.str();
  
    setCDKMatrixCell(myMatrix, i, 1, strConvert.c_str());
    drawCDKMatrix(myMatrix, true);
    
    setCDKMatrixCell(myMatrix, i, 2, buffer.c_str());
    drawCDKMatrix(myMatrix, true);
  }
  
  binInfile.close();

  /* so we can see results */
  sleep (5);

  // Cleanup screen
  endCDK();
  
  return 0;
}
