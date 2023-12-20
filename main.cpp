#include <cstdint>
#include <iostream>

#define maxHt 800
#define maxWd 600
#define maxVer 10000

template <typename T> class DynamicArray {
public:
  DynamicArray() = default;
  ~DynamicArray() = default;
  void resetPos() { _pos = 0; }
  uint32_t getSize() { return _pos; }
  void Push(T object) {
    if (_pos >= _size) {
      _size++;
      _point = (T *)realloc(_point, sizeof(T) * _size);
    }
    _point[_pos++] = object;
  }
  T *GetBase() { return _point; }

private:
  T *_point = nullptr;
  const uint32_t _alloc_size = 32;
  uint32_t _size = 0;
  uint32_t _pos = 0;
};

typedef struct edgebucket {
  int ymax;      // max y-coordinate of edge
  float xofymin; // x-coordinate of lowest edge point updated only in aet
  float slopeinverse;
} EdgeBucket;

class EdgeTable {
public:
  float height_from_bottom;
  DynamicArray<EdgeBucket> buckets;
};
class EdgeTableArray {
public:
  EdgeTableArray(){
    m_ybottom = 0;
  }
  static const int maxarray = 1000;
  EdgeTable tables[maxarray];
  int m_ybottom;
  void SetYBottom(int bottom) { m_ybottom = bottom; }
  void StoreEdge(int ymin, float xofymin, int ymax, float slopeinverse) {
    int dy = ymin - m_ybottom;
    if (dy >= 0 && dy < maxarray) {
      EdgeBucket bucket;
      bucket.ymax = ymax;
      bucket.xofymin = xofymin;
      bucket.slopeinverse = slopeinverse;
      tables[dy].buckets.Push(bucket);
    }
  }
  void PushEdge(float x0, int y0, float x1, int y1) {
    int ymin;
    int ymax;
    float xofymin;
    // horizontal lines are not stored in edge table
    if (y0 == y1)
      return;

    float minv;
    if (x1 == x0) {
      minv = 0.000000;
    } else {
      minv = (x1 - x0) / ((float)(y1 - y0));
    }

    if (y0 > y1) {
      ymin = y1;
      ymax = y0;
      xofymin = x1;
    } else {
      ymin = y0;
      ymax = y1;
      xofymin = x0;
    }
    StoreEdge(ymin, xofymin, ymax, minv);
  }
};
class Vertex {
public:
  Vertex(float _x, float _y) {
    x = _x;
    y = _y;
  }
  float x, y;
};
int main() {
  Vertex v[] = {Vertex(0, 0), Vertex(100, 0), Vertex(100, 100), Vertex(0, 100),
                Vertex(0, 0)};
  EdgeTableArray tables;
  tables.SetYBottom(0);
  for (int i = 0; i < 5 - 1; i++) {
    tables.PushEdge(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y);
  }
  return 0;
}
