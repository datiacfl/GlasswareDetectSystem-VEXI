/*****************************************************************************
 * HSerial.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HSerial
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

#ifndef H_SERIAL_H
#define H_SERIAL_H


namespace Halcon {


class LIntExport HSerial: public HRootObject {
public:
  HSerial(void) {id = -1;}
  HSerial(const HTuple &PortName);
  HSerial(const char *PortName);

  ~HSerial(void);
private:
  // Copying and Assignment not allowed
  HSerial(const HSerial &inst);
  HSerial &operator= (const HSerial &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HSerial";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Clear the buffer of a serial connection.
  virtual void ClearSerial(const Halcon::HTuple &Channel) const;
  virtual void ClearSerial(const char *Channel) const;
  // Write to a serial connection.
  virtual void WriteSerial(const Halcon::HTuple &Data) const;
  virtual void WriteSerial(Hlong Data) const;
  // Read from a serial device.
  virtual HTuple ReadSerial(const Halcon::HTuple &NumCharacters) const;
  virtual HTuple ReadSerial(Hlong NumCharacters) const;
  // Get the parameters of a serial device.
  virtual Hlong GetSerialParam(Halcon::HTuple *DataBits, Halcon::HTuple *FlowControl, Halcon::HTuple *Parity, Halcon::HTuple *StopBits, Halcon::HTuple *TotalTimeOut, Halcon::HTuple *InterCharTimeOut) const;
  virtual Hlong GetSerialParam(Hlong *DataBits, char *FlowControl, char *Parity, Hlong *StopBits, Hlong *TotalTimeOut, Hlong *InterCharTimeOut) const;
  // Set the parameters of a serial device.
  virtual void SetSerialParam(const Halcon::HTuple &BaudRate, const Halcon::HTuple &DataBits, const Halcon::HTuple &FlowControl, const Halcon::HTuple &Parity, const Halcon::HTuple &StopBits, const Halcon::HTuple &TotalTimeOut, const Halcon::HTuple &InterCharTimeOut) const;
  virtual void SetSerialParam(Hlong BaudRate, Hlong DataBits, const char *FlowControl, const char *Parity, Hlong StopBits, Hlong TotalTimeOut, Hlong InterCharTimeOut) const;
  // Open a serial device.
  virtual void OpenSerial(const Halcon::HTuple &PortName);
  virtual void OpenSerial(const char *PortName);
};

}

#endif
