/*****************************************************************************
 * HSocket.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Class HSocket
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.9 $
 * $Date: 2008/12/06 13:35:12 $
 *
 */

#ifndef H_SOCKET_H
#define H_SOCKET_H


#include "HCPPToolRef.h"


namespace Halcon {


class LIntExport HSocket: public HToolBase 
{
public:

  // Tool-specific functional class constructors
  
  HSocket(const HTuple &Port);
  HSocket(Hlong Port);
  HSocket(const HTuple &HostName, const HTuple &Port);
  HSocket(const char *HostName, Hlong Port);

  // Common tool class management functionality

  HSocket();
  const char *ClassName(void) const;
  Hlong GetHandle(void) const;
  void  SetHandle(Hlong ID);

  // Tool-specific member functions

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
  // Determine the Halcon data type of the next socket data.
  virtual HTuple GetNextSocketDataType() const;
  // Get the socket descriptor of a socket used by the operating system.
  virtual Hlong GetSocketDescriptor() const;
  // Get the timout of a socket.
  virtual double GetSocketTimeout() const;
  // Set the timout of a socket.
  virtual void SetSocketTimeout(const Halcon::HTuple &Timeout) const;
  // Set the timout of a socket.
  virtual void SetSocketTimeout(double Timeout) const;
  // Accept a connection request on a listening socket.
  virtual HSocket SocketAcceptConnect(const Halcon::HTuple &Wait) const;
  // Accept a connection request on a listening socket.
  virtual HSocket SocketAcceptConnect(const char *Wait) const;
  // Open a socket to an existing socket.
  virtual void OpenSocketConnect(const Halcon::HTuple &HostName, const Halcon::HTuple &Port);
  // Open a socket to an existing socket.
  virtual void OpenSocketConnect(const char *HostName, Hlong Port);
  // Open a socket that accepts connection requests.
  virtual void OpenSocketAccept(const Halcon::HTuple &Port);
  // Open a socket that accepts connection requests.
  virtual void OpenSocketAccept(Hlong Port);
};

}

#endif
