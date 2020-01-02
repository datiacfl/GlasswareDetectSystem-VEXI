/*****************************************************************************
 * HFramegrabber.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HFramegrabber
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.7 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */

#ifndef H_FRAMEGRABBER_H
#define H_FRAMEGRABBER_H


namespace Halcon {


class LIntExport HFramegrabber: public HRootObject {
public:
  HFramegrabber(void) {id = -1;}
  HFramegrabber(
      const HTuple &Name, 
      const HTuple &HorizontalResolution = 1, const HTuple &VerticalResolution = 1,
      const HTuple &ImageWidth = 0,           const HTuple &ImageHeight = 0,
      const HTuple &StartRow = 0,             const HTuple &StartColumn = 0,
      const HTuple &Field = "default",
      const HTuple &BitsPerChannel = -1, 
      const HTuple &ColorSpace = "default",
      const HTuple &Gain = -1,
      const HTuple &ExternalTrigger = "default", 
      const HTuple &CameraType = "default",
      const HTuple &Device = "default",
      const HTuple &Port = -1,
      const HTuple &LineIn = -1);
  HFramegrabber(
      const char *Name, 
      Hlong HorizontalResolution = 1, Hlong VerticalResolution = 1,
      Hlong ImageWidth = 0,           Hlong ImageHeight = 0,
      Hlong StartRow = 0,             Hlong StartColumn = 0,
      const char *Field = "default",
      Hlong BitsPerChannel = -1, 
      const char *ColorSpace = "default",
      double Gain = -1,
      const char *ExternalTrigger = "default", 
      const char *CameraType = "default",
      const char *Device = "default",
      Hlong Port = -1,
      Hlong LineIn = -1);

  ~HFramegrabber(void);
private:
  // Copying and Assignment not allowed
  HFramegrabber(const HFramegrabber &inst);
  HFramegrabber &operator= (const HFramegrabber &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HFramegrabber";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Get specific parameters for a frame grabber.
  virtual HTuple GetFramegrabberParam(const Halcon::HTuple &Param) const;
  virtual HTuple GetFramegrabberParam(const char *Param) const;
  // Set specific parameters for a frame grabber.
  virtual void SetFramegrabberParam(const Halcon::HTuple &Param, const Halcon::HTuple &Value) const;
  // Grab and segment an image from the specified frame grabber and
  // start the asynchronous grab of the next image.
  virtual HRegionArray GrabRegionAsync(const Halcon::HTuple &MaxDelay) const;
  virtual HRegionArray GrabRegionAsync(double MaxDelay) const;
  // Grab and segment an image from the specified frame grabber.
  virtual HRegionArray GrabRegion() const;
  // Grab of an image from the specified frame grabber and start of the 
  // asynchronous grab of the next image.
  virtual HImage GrabImageAsync(const Halcon::HTuple &MaxDelay) const;
  virtual HImage GrabImageAsync(double MaxDelay) const;
  // Start an asynchronous grab of an image from the specified frame grabber.
  virtual void GrabImageStart(const Halcon::HTuple &MaxDelay) const;
  virtual void GrabImageStart(double MaxDelay) const;
  // Grab an image from the specified frame grabber.
  virtual HImage GrabImage() const;
  // Open and configure a frame grabber.
  virtual void OpenFramegrabber(const Halcon::HTuple &Name, const Halcon::HTuple &HorizontalResolution, const Halcon::HTuple &VerticalResolution, const Halcon::HTuple &ImageWidth, const Halcon::HTuple &ImageHeight, const Halcon::HTuple &StartRow, const Halcon::HTuple &StartColumn, const Halcon::HTuple &Field, const Halcon::HTuple &BitsPerChannel, const Halcon::HTuple &ColorSpace, const Halcon::HTuple &Gain, const Halcon::HTuple &ExternalTrigger, const Halcon::HTuple &CameraType, const Halcon::HTuple &Device, const Halcon::HTuple &Port, const Halcon::HTuple &LineIn);
  virtual void OpenFramegrabber(const char *Name, Hlong HorizontalResolution, Hlong VerticalResolution, Hlong ImageWidth, Hlong ImageHeight, Hlong StartRow, Hlong StartColumn, const char *Field, Hlong BitsPerChannel, const char *ColorSpace, double Gain, const char *ExternalTrigger, const char *CameraType, const char *Device, Hlong Port, Hlong LineIn);
  // Query frame grabber lut.
  virtual HTuple GetFramegrabberLut(Halcon::HTuple *ImageGreen, Halcon::HTuple *ImageBlue) const;
  // Set frame grabber lut.
  virtual void SetFramegrabberLut(const Halcon::HTuple &ImageRed, const Halcon::HTuple &ImageGreen, const Halcon::HTuple &ImageBlue) const;
};

}

#endif
