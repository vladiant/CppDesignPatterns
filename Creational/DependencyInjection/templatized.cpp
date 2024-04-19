// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Dependency injection
// https://godbolt.org/z/KTffoMv56

#include <iostream>
#include <vector>

using byte = unsigned char;
using Handle = unsigned int;
int GetNextHandle() {
  static int next = 0;
  return ++next;
}

struct File {
  friend int Open(File& file, int size = 0) {
    file.size = size;
    return file.handle = GetNextHandle();
  }
  File(Handle handle = 0) : handle(handle), size(size), position(0) {}
  int Read(byte* buffer, int count) {
    if (!handle) return -1;
    if (count > (size - position)) count = size - position;
    position += count;
    return count;
  }
  int Write(byte* buffer, int count) {
    if (!handle) return -1;
    if (count > (size - position)) size = position + count;
    position += count;
    if (size > position) size = position;
    return count;
  }
  int Seek(int pos) {
    if (!handle) return -1;
    if (pos > size) pos = size;
    int prev = position;
    position = pos;
    return prev;
  }
  void Close() {
    handle = ~0;
    size = 0;
    position = 0;
  }
  int Size() { return size; }

 private:
  Handle handle{};
  int size{};
  int position{};
};

struct Stream {
  friend int Open(Stream& stream) { return stream.handle = GetNextHandle(); }
  Stream(Handle handle = 0) : handle(handle) {}
  int Read(byte* buffer, int count) {
    if (!handle) return -1;
    if (count > (size - position)) count = size - position;
    position += count;
    return count;
  }
  int Write(byte* buffer, int count) {
    if (!handle) return -1;
    if (count > (size - position)) size = position + count;
    position += count;
    return count;
  }
  int Seek(int pos) {
    if (!handle) return -1;
    if (pos > size) pos = size;
    int prev = position;
    position = pos;
    return prev;
  }
  void Close() {
    handle = ~0;
    size = 0;
    position = 0;
  }

 private:
  Handle handle{};
  int size{};
  int position{};
};

template <typename Src, typename Dest>
int CopyAll(Src& src, Dest& dest) {
  int count{};
  byte buffer[255]{};
  while (int read = src.Read(buffer, sizeof(buffer))) {
    dest.Write(buffer, read);
    count += read;
  }
  return count;
}

int main() {
  File file{};
  std::cout << "open file size=1500\n";
  Open(file, 1500);

  Stream stream{};
  Open(stream);
  std::cout << "open seekable stream\n\n";

  std::cout << "CopyAll(file, stream) count:" << CopyAll(file, stream) << "\n";
  std::cout << "file.Size():" << file.Size() << "\n\n";

  std::cout << "file.Seek(777);   prev=" << file.Seek(777) << "\n";
  std::cout << "stream.Seek(222); prev=" << stream.Seek(222) << "\n\n";

  std::cout << "CopyAll(stream, file) count:" << CopyAll(stream, file) << "\n";
  std::cout << "file.Size():" << file.Size() << "\n\n";

  std::cout << "file.Close();\nstream.Close();\n\n";
  file.Close();
  stream.Close();
}
