/*****************************************************************************
 * HTuple.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HTuple
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.36 $
 * $Date: 2005/05/11 13:47:27 $
 *
 */

#ifndef HTUPLE_H
#define HTUPLE_H


namespace Halcon {


/****************************************************************************/
/*                           HCtrlVal                                       */
/****************************************************************************/

union CtrlUnion {
  Hlong         l;          // Parameter of Type Hlong (integer)
  double        d;          // Parameter of Type double (real)
  char          *s;         // Parameter of Type string
};

enum HCtrlType {
  LongVal   = LONG_PAR, 
  DoubleVal = DOUBLE_PAR,
  StringVal = STRING_PAR,
  UndefVal  = UNDEF_PAR
};

class LIntExport HCtrlVal : public HRootObject {
friend class HTuple;
public:
  HCtrlVal(void)      {type  = UndefVal;  val.l = 0;}
  HCtrlVal(Hlong l)   {type  = LongVal;   val.l = l;}
  HCtrlVal(int l)     {type  = LongVal;   val.l = l;}
  HCtrlVal(double d)  {type  = DoubleVal; val.d = d;}
  HCtrlVal(const char *s);
  HCtrlVal(const HCtrlVal &v) {CopyCtrlVal(v);}
  ~HCtrlVal(void)             {ClearCtrlVal();}
  HCtrlVal& operator = (const HCtrlVal &v);
 
  // Type conversion
  int         ValType() const          {return type;}
  operator    int(void) const          {return I();}
  operator    Hlong(void) const         {return L();}
  operator    double(void) const       {return D();}
  operator    const char*(void) const  {return S();}
  // Access contents
  double      D() const;
  Hlong       L() const;
  int         I() const;
  const char *S() const;
  // Arithmetics
  HCtrlVal     operator + (const HCtrlVal &val) const;
  HTuple       operator + (const HTuple &val) const;
  HCtrlVal     operator - (const HCtrlVal &val) const;
  HTuple       operator - (const HTuple &val) const;
  HCtrlVal     operator * (const HCtrlVal &val) const;
  HTuple       operator * (const HTuple &val) const;
  HCtrlVal     operator / (const HCtrlVal &val) const;
  HTuple       operator / (const HTuple &val) const;
  HCtrlVal     operator % (const HCtrlVal &val) const;
  HTuple       operator % (const HTuple &val) const;
  HBool        operator != (const HCtrlVal &val) const;
  HBool        operator != (const HTuple &val) const;
  HBool        operator == (const HCtrlVal &val) const;
  HBool        operator == (const HTuple &val) const;
  HBool        operator >= (const HCtrlVal &val) const;
  HBool        operator >= (const HTuple &val) const;
  HBool        operator <= (const HCtrlVal &val) const;
  HBool        operator <= (const HTuple &val) const;
  HBool        operator > (const HCtrlVal &val) const;
  HBool        operator > (const HTuple &val) const;
  HBool        operator < (const HCtrlVal &val) const;
  HBool        operator < (const HTuple &val) const;
  // virtuell from father
  virtual const char *ClassName(void) const { return "HCtrlVal"; }
private:
  // Data
  CtrlUnion   val;        // Value: one of the three types
  HCtrlType   type;       // Which type: ***_PAR
  // Support operationen
  void ClearCtrlVal() {if (type == StringVal) delete [] val.s;}
  void CopyCtrlVal(const HCtrlVal& source);
};



/****************************************************************************/
/*                             Tuple                                        */
/****************************************************************************/

struct SpecialTuple { 
  int val; 
  SpecialTuple(int v = H_IGNORE) {val = v;}
};



class LIntExport HTuple: public HBaseArray {
public:
  HTuple(void);
  HTuple(Hlong l);
  HTuple(HCoord l);
  HTuple(int l);
  HTuple(double d);
  HTuple(const char *s);
  HTuple(const HCtrlVal &c);
  HTuple(const HTuple &in) {CopyTuple(in);}
  HTuple(Hlong length, const HTuple &value);
  HTuple(const HTuple &length, const HTuple &value);
  HTuple(SpecialTuple d);

  ~HTuple()                     {ClearTuple();}
  HTuple &operator = (const HTuple& in);

  // The functions CopyFromCore() and CopyToCore() are used for 
  // accelerated data transfer from the HALCON core to HALCON/C++ 
  // and vice versa. Designed for internal usage only.
  void CopyFromCore(Hctuple *ocHctuple);
  void CopyToCore(Hproc_handle proc_handle, Hctuple *icHctuple) const;
  
  HTuple       Sum(void) const;
  HTuple       Mean(void) const;
  HTuple       Deviation(void) const;
  HTuple       Median(void) const;
  HTuple       Getenv(void) const;
  HTuple       Max(void) const;
  HTuple       Min(void) const;
  HTuple       Rad(void) const;
  HTuple       Deg(void) const;
  HTuple       Real(void) const;
  HTuple       Int(void) const;
  HTuple       Round(void) const;
  HTuple       Chr(void) const;
  HTuple       Ord(void) const;
  HTuple       Chrt(void) const;
  HTuple       Ords(void) const;
  HTuple       Number(void) const;
  HTuple       Sqrt(void) const;
  HTuple       IsNumber(void) const;
  HTuple       Strlen(void) const;
  HTuple       Inverse(void) const;
  HTuple       Asin(void) const;
  HTuple       Acos(void) const;
  HTuple       Atan(void) const;
  HTuple       Log(void) const;
  HTuple       Log10(void) const;
  HTuple       Sin(void) const;
  HTuple       Cos(void) const;
  HTuple       Tan(void) const;
  HTuple       Sinh(void) const;
  HTuple       Cosh(void) const;
  HTuple       Tanh(void) const;
  HTuple       Exp(void) const;
  HTuple       Abs(void) const;
  HTuple       Sgn(void) const;
  HTuple       Rand(void) const;
  HTuple       Uniq(void) const;
  HTuple       Floor(void) const;
  HTuple       Ceil(void) const;
  HTuple       Sort(void) const;
  HTuple       SortIndex(void) const;
  HTuple       Cumul(void) const;
  HTuple       Atan2(const HTuple &op) const;
  HTuple       Pow(const HTuple &op) const;
  HTuple       Ldexp(const HTuple &op) const;
  HTuple       Fmod(const HTuple &op) const;
  HTuple       Min2(const HTuple &op) const;
  HTuple       Max2(const HTuple &op) const;
  HTuple       Find(const HTuple &op) const;
  HTuple       Strchr(const HTuple &pattern) const;
  HTuple       Strchr(const char *pattern) const;
  HTuple       Strstr(const HTuple &pattern) const;
  HTuple       Strstr(const char *pattern) const;
  HTuple       Strrchr(const HTuple &pattern) const;
  HTuple       Strrchr(const char *pattern) const;
  HTuple       Strrstr(const HTuple &pattern) const;
  HTuple       Strrstr(const char *pattern) const;
  HTuple       StrBitSelect(Hlong index) const;
  HTuple       StrBitSelect(const HTuple &index) const;
  HTuple       ToString(const char *pattern) const;
  HTuple       ToString(const HTuple &pattern) const;
  HTuple       Split(const char *pattern) const;
  HTuple       Split(const HTuple &pattern) const;
  HTuple       Substring(const HTuple &index1, const HTuple &index2) const;
  HTuple       Substring(Hlong index1, Hlong index2) const;
  HTuple       Substring(const HTuple &index1, Hlong index2) const;
  HTuple       Substring(Hlong index1, const HTuple &index2) const;
  HTuple       Subset(const HTuple &index) const;
  HTuple       Remove(const HTuple &index) const;
  HTuple       SelectRank(Hlong index) const;
  HTuple       SelectRank(const HTuple &index) const;
  HBool        Xor(const HTuple &pattern) const;
  operator     HCtrlVal(void) const;
  HTuple       operator () (Hlong min, Hlong max) const;
  HTuple       operator () (const HTuple &min, const HTuple &max) const;
  HCtrlVal    &operator [] (Hlong index);
  HCtrlVal     operator [] (Hlong index) const;
  HCtrlVal    &operator [] (const HTuple &index);
  HCtrlVal     operator [] (const HTuple &index) const;
  HTuple      &operator ++ (void); // nur fuer double und Hlong
  HBool        operator !  (void) const;
  HTuple       operator ~  (void) const;
  HTuple       operator << (const HTuple &val) const;
  HTuple       operator << (Hlong val) const;
  HTuple       operator >> (const HTuple &val) const;
  HTuple       operator >> (Hlong val) const;
  HTuple       operator +  (const HTuple &val) const;
  HTuple       operator +  (double val) const;
  HTuple       operator +  (int val) const;
  HTuple       operator +  (Hlong val) const;
  HTuple       operator +  (const char *val) const;
  HTuple       operator -  (const HTuple &val) const;
  HTuple       operator -  (double val) const;
  HTuple       operator -  (int val) const;
  HTuple       operator -  (Hlong val) const;
  HTuple       operator -  (void) const;
  HTuple       operator *  (const HTuple &val) const;
  HTuple       operator *  (double val) const;
  HTuple       operator *  (int val) const;
  HTuple       operator *  (Hlong val) const;
  HTuple       operator /  (const HTuple &val) const;
  HTuple       operator /  (double val) const;
  HTuple       operator /  (int val) const;
  HTuple       operator /  (Hlong val) const;
  HTuple       operator %  (const HTuple &val) const;
  HTuple       operator %  (Hlong val) const;
  HTuple      &operator += (const HTuple &val);
  HTuple      &operator += (double val);
  HTuple      &operator += (int val);
  HTuple      &operator += (Hlong val);
  HTuple      &operator += (HCtrlVal val);
  HBool        operator != (const HTuple &val) const;
  HBool        operator != (double val) const;
  HBool        operator != (int val) const;
  HBool        operator != (Hlong val) const;
  HTuple       operator ^  (const HTuple &val) const;
  HTuple       operator ^  (Hlong val) const;
  HTuple       operator |  (const HTuple &val) const;
  HTuple       operator |  (Hlong val) const;
  HTuple       operator &  (const HTuple &val) const;
  HTuple       operator &  (Hlong val) const;
  HBool        operator && (const HTuple &val) const;
  HBool        operator && (Hlong val) const;
  HBool        operator || (const HTuple &val) const;
  HBool        operator || (Hlong val) const;
  HBool        operator == (const HTuple &val) const;
  HBool        operator == (double val) const;
  HBool        operator == (int val) const;
  HBool        operator == (Hlong val) const;
  HBool        operator >= (const HTuple &val) const;
  HBool        operator >= (double val) const;
  HBool        operator >= (int val) const;
  HBool        operator >= (Hlong val) const;
  HBool        operator <= (const HTuple &val) const;
  HBool        operator <= (double val) const;
  HBool        operator <= (int val) const;
  HBool        operator <= (Hlong val) const;
  HBool        operator >  (const HTuple &val) const;
  HBool        operator >  (double val) const;
  HBool        operator >  (int val) const;
  HBool        operator >  (Hlong val) const;
  HBool        operator <  (const HTuple &val) const;
  HBool        operator <  (double val) const;
  HBool        operator <  (int val) const;
  HBool        operator <  (Hlong val) const;

  // friend operators
  LIntExport friend HTuple operator << (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator >> (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator + (double val1, const HTuple &val2);
  LIntExport friend HTuple operator + (int val1, const HTuple &val2);
  LIntExport friend HTuple operator + (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator + (const char *val1, const HTuple &val2);
  LIntExport friend HTuple operator - (double val1, const HTuple &val2);
  LIntExport friend HTuple operator - (int val1, const HTuple &val2);
  LIntExport friend HTuple operator - (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator * (double val1, const HTuple &val2);
  LIntExport friend HTuple operator * (int val1, const HTuple &val2);
  LIntExport friend HTuple operator * (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator / (double val1, const HTuple &val2);
  LIntExport friend HTuple operator / (int val1, const HTuple &val2);
  LIntExport friend HTuple operator / (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator % (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator ^  (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator | (Hlong val1, const HTuple &val2);
  LIntExport friend HTuple operator & (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator || (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator && (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator != (double val1, const HTuple &val2);
  LIntExport friend HBool operator != (int val1, const HTuple &val2);
  LIntExport friend HBool operator != (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator == (double val1, const HTuple &val2);
  LIntExport friend HBool operator == (int val1, const HTuple &val2);
  LIntExport friend HBool operator == (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator >= (double val1, const HTuple &val2);
  LIntExport friend HBool operator >= (int val1, const HTuple &val2);
  LIntExport friend HBool operator >= (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator <= (double val1, const HTuple &val2);
  LIntExport friend HBool operator <= (int val1, const HTuple &val2);
  LIntExport friend HBool operator <= (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator > (double val1, const HTuple &val2);
  LIntExport friend HBool operator > (int val1, const HTuple &val2);
  LIntExport friend HBool operator > (Hlong val1, const HTuple &val2);
  LIntExport friend HBool operator < (double val1, const HTuple &val2);
  LIntExport friend HBool operator < (int val1, const HTuple &val2);
  LIntExport friend HBool operator < (Hlong val1, const HTuple &val2);

  HBool        Continue(const HTuple &FinalValue, const HTuple &Increment); 
  HTuple      &Append(const HTuple &t);
  HTuple       Concat(const HTuple &t) const;
  int          State(void) const   {return state;}
  void         Reset(void)         {ClearTuple(); tuple = 0; EmptyArray();}
  const char  *ClassName(void) const { return "HTuple"; }
private:
  HCtrlVal    *tuple;       // values (array of Hlong/float/string)
  char        state;
  
  void  NewLength(Hlong new_num, Hlong old_num);
  void  ClearTuple()    {if (Num() > 0) delete [] tuple;}
  void  CopyTuple(const HTuple& in);

};


}


#endif
