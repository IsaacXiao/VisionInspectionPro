#ifndef INSPECT_EXCEPTION_H
#define INSPECT_EXCEPTION_H

#include <exception>
#include "CommonInclude/TypeDefine.h"

class InspectException : public std::exception
{
private:
  STRING msg_{"Inspect Exception!\t"};
public:
  InspectException()
  {
  }
  InspectException(const STRING & msg)
  {
    msg_ += msg;
  }
  const char* what() const noexcept override
  {
    return msg_.c_str();
  }
  virtual ~InspectException(){}
};

class FilePathException : public InspectException
{
public:
  FilePathException():InspectException("FilePath Exception, FilePath might not exist!"){}
  FilePathException(STRING && msg):InspectException(msg){}  
};

class DllException : public InspectException
{
public:
  DllException():InspectException("DllException!"){}
  DllException(STRING && msg):InspectException(msg){}  
};

class CfgException : public InspectException
{
public:
  CfgException():InspectException("CfgException!"){}
  CfgException(STRING && msg):InspectException(msg){}  
};

class CameraGrabberException : public InspectException
{
public:
	CameraGrabberException() :InspectException("CameraGrabberException!") {}
	CameraGrabberException(STRING && msg) :InspectException(msg) {}
};

#endif 