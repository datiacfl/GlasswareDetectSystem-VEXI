/*****************************************************************************
 * HGnuplot.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HGnuplot
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.6 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */

#ifndef H_GNUPLOT_H
#define H_GNUPLOT_H


namespace Halcon {


class LIntExport HGnuplot: public HRootObject {
public:
  HGnuplot(void) {id = -1;}
  HGnuplot(const HTuple &FileName);
  HGnuplot(const char *FileName);

  ~HGnuplot(void);
private:
  // Copying and Assignment not allowed
  HGnuplot(const HGnuplot &inst);
  HGnuplot &operator= (const HGnuplot &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HGnuplot";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Plot a function using gnuplot.
  virtual void GnuplotPlotFunct1d(const Halcon::HTuple &Function) const;
  // Plot control values using gnuplot.
  virtual void GnuplotPlotCtrl(const Halcon::HTuple &Values) const;
  // Visualize images using gnuplot.
  virtual void GnuplotPlotImage(const HImage &Image, const Halcon::HTuple &SamplesX, const Halcon::HTuple &SamplesY, const Halcon::HTuple &ViewRotX, const Halcon::HTuple &ViewRotZ, const Halcon::HTuple &Hidden3D) const;
  virtual void GnuplotPlotImage(const HImage &Image, Hlong SamplesX, Hlong SamplesY, double ViewRotX, double ViewRotZ, const char *Hidden3D) const;
  // Open a gnuplot file for visualization of images and control values.
  virtual void GnuplotOpenFile(const Halcon::HTuple &FileName);
  virtual void GnuplotOpenFile(const char *FileName);
  // Open a pipe to a gnuplot process for visualization of images and control
  // values.
  virtual void GnuplotOpenPipe(void);
};

}

#endif
