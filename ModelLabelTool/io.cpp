#include "stdafx.h"
#include <fcntl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <stdint.h>
#include <stdio.h>

#include <algorithm>
#include <fstream>  // NOLINT(readability/streams)
#include <string>
#include <vector>

#include <fcntl.h>
#include <Windows.h>

#ifdef USE_LEVELDB
#include <leveldb/db.h>
#endif

//#include "caffe/common.hpp"
//#include "glog\logging.h"
#include "mlt.pb.h"
#include "io.hpp"

using namespace std;

// port for Win32
#ifdef _MSC_VER
#define open _open
#define close _close
#endif

namespace mlt {

using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

bool ReadProtoFromTextFile(const char* filename, Message* proto) {
  int fd = open(filename, O_RDONLY);
  //CHECK_NE(fd, -1) << "File not found: " << filename;
  if (fd == -1){
	  //MessageBox(0, L"File not found", L"Tip", 0);
	  close(fd);
	  return false;
  }
  FileInputStream* input = new FileInputStream(fd);
  bool success = google::protobuf::TextFormat::Parse(input, proto);
  delete input;
  close(fd);
  return success;
}

void WriteProtoToTextFile(const Message& proto, const char* filename) {
  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  FileOutputStream* output = new FileOutputStream(fd);
  //CHECK(google::protobuf::TextFormat::Print(proto, output));
  if (!google::protobuf::TextFormat::Print(proto, output)){
	  //MessageBox(0, L"File write error!", L"Tip", 0);
  }
  delete output;
  close(fd);
}

bool ReadProtoFromBinaryFile(const char* filename, Message* proto) {
  int fd = open(filename, O_RDONLY | O_BINARY);
  //CHECK_NE(fd, -1) << "File not found: " << filename;
  if (fd == -1){
	  //MessageBox(0, L"File not found", L"Tip", 0);
	  close(fd);
	  return false;
  }
  ZeroCopyInputStream* raw_input = new FileInputStream(fd);
  CodedInputStream* coded_input = new CodedInputStream(raw_input);
  coded_input->SetTotalBytesLimit(1073741824, 536870912);

  bool success = proto->ParseFromCodedStream(coded_input);

  delete coded_input;
  delete raw_input;
  close(fd);
  return success;
}

void WriteProtoToBinaryFile(const Message& proto, const char* filename) {
  fstream output(filename, ios::out | ios::trunc | ios::binary);
  //CHECK(proto.SerializeToOstream(&output));
  if (!proto.SerializeToOstream(&output)){
	  //MessageBox(0, L"File write error!", L"Tip", 0);
  }
}

}  // namespace caffe
