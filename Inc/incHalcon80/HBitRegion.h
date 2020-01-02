/*****************************************************************************
 * HBitRegion.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Region as Bit-Array depicted
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.11 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */


#ifndef BIT_REGION_H
#define BIT_REGION_H


namespace Halcon {


/****************************************************************************/
/*                            HBitRegion                                    */
/****************************************************************************/
class LIntExport HBitRegion: public HAbstractRegion {
public:
  virtual HRectangle1 BoundingBox(void) const;
  virtual HAbstractRegion* CopyAbstractRegion(void) const;
  virtual void Display(const HWindow &w) const;
  virtual HBool In(const HDPoint2D &p) const;
  virtual HBool IsEmpty(void) const;
  virtual HAbstractRegion* NewEmpty(void) const;
  virtual HAbstractRegion* ToHRegion(void) const;
  virtual HAbstractRegion* ToRLRegion(void) const;
  virtual const char* ClassName(void) const;
  HBitRegion(int width, int height);
  HBitRegion(unsigned char *in, int Width, int Height);
  ~HBitRegion(void);
  void SetBit(int row, int col)
  { bits[row][col>>ColShift] |= 1<<(row&(BitsPerByte-1)); }
  void DelBit(int row, int col) 
  { bits[row][col>>ColShift] &= ~(1<<(row&(BitsPerByte-1))); }
  HBitRegion Union(const HBitRegion &in);
  HBitRegion Intersection(const HBitRegion &in);
private:
  unsigned Hlong  **bits;
  int             width;
  int             height;

  static int      BitsPerByte;    // typisch 8
  static int      BytesPerLong;   // typisch 4
  static int      ColShift;       // ld(BitsPerByte) + ld(BytesPerLong)
  static int      BitsPerLong;    // BytesPerLong * BitsPerByte

  int             LongsPerRow(int width) 
		  { return (width-1) / BitsPerLong + 1; }
  int             BytesPerRow(int width)
		  { return LongsPerRow(width) * BytesPerLong; }
  void            AllocMem(int Width, int Height);  
};


}


#endif
