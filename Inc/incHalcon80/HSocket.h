/*****************************************************************************
 * HSocket.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HSocket
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.6 $
 * $Date: 2005/05/06 07:36:06 $
 *
 */

#ifndef H_SOCKET_H
#define H_SOCKET_H


namespace Halcon {


class LIntExport HSocket: public HRootObject {
public:
  HSocket(void) {id = -1;}
  HSocket(const HTuple &Port);
  HSocket(Hlong Port);
  HSocket(const HTuple &HostName, const HTuple &Port);
  HSocket(const char *HostName, Hlong Port);

  ~HSocket(void);
private:
  // Copying and Assignment not allowed
  HSocket(const HSocket &inst);
  HSocket &operator= (const HSocket &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HSocket";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Receive an image over a socket connection.
  virtual HImageArray ReceiveImage() const;
  // Send an image over a socket connection.
  virtual void SendImage(const HImageArray &Image) const;
  // Receive regions over a socket connection.
  virtual HRegionArray ReceiveRegion() const;
  // Send regions over a socket connection.
  virtual void SendRegion(const HRegionArray &Region) const;
  // Receive an XLD object over a socket connection.
  virtual HXLDArray ReceiveXld() const;
  // Send an XLD object over a socket connection.
  virtual void SendXld(const HXLDArray &XLD) const;
  // Receive a tuple over a socket connection.
  virtual HTuple ReceiveTuple() const;
  // Send a tuple over a socket connection.
  virtual void SendTuple(const Halcon::HTuple &Tuple) const;
  virtual void SendTuple(const char *Tuple) const;
  // Determine the Halcon data type of the next socket data.
  virtual HTuple GetNextSocketDataType() const;
  // Get the socket descriptor of a socket used by the operating system.
  virtual Hlong GetSocketDescriptor() const;
  // Get the timout of a socket.
  virtual double GetSocketTimeout() const;
  // Set the timout of a socket.
  virtual void SetSocketTimeout(const Halcon::HTuple &Timeout) const;
  virtual void SetSocketTimeout(double Timeout) const;
  // Accept a connection request on a listening socket.
  virtual Hlong SocketAcceptConnect(const Halcon::HTuple &Wait);
  virtual Hlong SocketAcceptConnect(const char *Wait);
  // Open a socket to an existing socket.
  virtual void OpenSocketConnect(const Halcon::HTuple &HostName, const Halcon::HTuple &Port);
  virtual void OpenSocketConnect(const char *HostName, Hlong Port);
  // Open a socket that accepts connection requests.
  virtual void OpenSocketAccept(const Halcon::HTuple &Port);
  virtual void OpenSocketAccept(Hlong Port);
};

}

#endif
