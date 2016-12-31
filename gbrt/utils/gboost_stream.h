#ifndef _GBOOST_STREAM_H_
#define _GBOOST_STREAM_H_

#include <cstdio>
/**
 * \file gboost_stream.h
 * \brief general stream interface for serialization
 * \author Yufan Fu: letflykid@gmail.com
 */
namespace gboost{
namespace utils{
/** \brief interface of stream I/O, used to serialize model */
class IStream{
 public:
  /**
   * \brief read data from stream
   * \param ptr: pointer to memory buffer
   * \param size: size of block
   * \return usually is the size of data reader
   */
  virtual size_t Read(void *ptr, size_t size) = 0;
  /**
   * \brief write data to stream
   * \param ptr: pointer to memory buffer
   * \param size: size of block
   */
  virtual void Write(const void *ptr, size_t size) = 0;
  /** \brief virtual destructor */
  virtual ~IStream(void) {}
};
/** \brief implementation of file i/o stream */
class FileStream: public IStream {
 private:
  FILE *fp;
 public:
  FileStream(FILE *fp) { this->fp = fp; }
  virtual size_t Read(void *ptr, size_t size) { return fread(ptr, size, 1, fp); }
  virtual void Write(const void *ptr, size_t size) { fwrite(ptr, size, 1, fp); }
  inline void Close(void) { fclose(fp); }
};
};
};
#endif
