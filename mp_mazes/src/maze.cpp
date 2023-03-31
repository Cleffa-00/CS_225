#include "maze.h"



void SquareMaze::makeMaze(int width, int height)
{
  width_ = width;
  height_ = height;

  graph = vector<vector<pair<bool, bool>>>(width_, vector<pair<bool, bool>>(height_, {true, true}));

  dset = DisjointSets();
  dset.addelements(width_ * height_);

  for (int x = 0; x < width_; ++ x)
    for (int y = 0; y < height_; ++ y)
    {
      vector<int> v;
      for (int d = 0; d < 4; ++ d)
      {
        int a = x + dx[d], b = y + dy[d];
        if (a < 0 || b < 0 || a >= width_ || b >= height_) continue;
        if (!canTravel(x, y, d) && dset.find(y * width_ + x) != dset.find(b * width_ + a)) v.push_back(d);
      }

      if (v.empty()) continue;
      int d = v[rand() % v.size()];
      int i = y * width_ + x;
      if (d == 0)
      {
        dset.setunion(i, i + 1);
        graph[x][y].first = false;
      }
      else if (d == 1)
      {
        dset.setunion(i, i + width_);
        graph[x][y].second = false;
      }
      else if (d == 2)
      {
        dset.setunion(i, i - 1);
        graph[x - 1][y].first = false;
      }
      else 
      {
        dset.setunion(i, i - width_);
        graph[x][y - 1].second = false;
      }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
  if (dir == 0) return !graph[x][y].first;
  else if (dir == 1) return !graph[x][y].second;
  else if (dir == 2) return x > 0 && !graph[x - 1][y].first;
  else return y > 0 && !graph[x][y - 1].second;
}

void 	SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  if (dir == 0) graph[x][y].first = exists;
  else graph[x][y].second = exists;
}

vector<int> SquareMaze::solveMaze()
{
  vector<vector<int>> st(width_, vector<int>(height_, -1));
  vector<vector<int>> from = vector<vector<int>>(width_, vector<int>(height_, -1));
  queue<pair<int, int>> q;
  q.push({0, 0});
  st[0][0] = 0;

  while (!q.empty())
  {
    auto t = q.front(); q.pop();
    int x = t.first, y = t.second;
    std::cout << x << ' ' << y << std::endl;

    for (int d = 0; d < 4; ++ d)
    {
      int a = x + dx[d], b = y + dy[d];
      if (!canTravel(x, y, d)|| st[a][b] != -1) continue;
      st[a][b] = st[x][y] + 1;
      from[a][b] = d;
      q.push({a, b});
    }
  }

  pair<int, int> ans = {0, height_ - 1};
  int m = 0;
  for (int i = 0; i < width_; ++ i)
    if (st[i][height_ - 1] > m)
    {
      m = st[i][height_ - 1];
      ans = {i, height_ - 1};
    }
  
  vector<int> ret;
  while (ans.first != 0 || ans.second != 0)
  {
    int x = ans.first, y = ans.second;
    ret.insert(ret.begin(), from[x][y]);
    ans = {x - dx[ret[0]], y - dy[ret[0]]};
  }
  return ret;
}

PNG *SquareMaze::drawMaze() const
{
  PNG * ret = new PNG(width_ * 10 + 1, height_ * 10 + 1);
  for (int x = 10; x < width_ * 10 + 1; ++ x)
    ret -> getPixel(x, 0) = HSLAPixel(0, 0, 0);
  for (int y = 0; y < height_ * 10 + 1; ++ y)
    ret -> getPixel(0, y) = HSLAPixel(0, 0, 0); 
  
  for (int y = 0; y < height_; ++ y)
    for (int x = 0; x < width_; ++ x)
    {
      if (!canTravel(x, y, 0))
        for (int k = 0; k <= 10; ++ k)
          ret -> getPixel((x + 1) * 10, y * 10 + k) = HSLAPixel(0, 0, 0);
      if (!canTravel(x, y, 1))
        for (int k = 0; k <= 10; ++ k)
          ret -> getPixel(x * 10 + k, (y + 1) * 10) = HSLAPixel(0, 0, 0);
    }
  
  return ret;
}

PNG *SquareMaze::drawMazeWithSolution()
{
  PNG *ret = drawMaze();
  vector<int> v = solveMaze();
  int x = 5, y = 5;
  for (size_t i = 0; i < v.size(); ++ i)
    for (int k = 0; k < 10; ++ k)
    {
      x += dx[v[i]], y += dy[v[i]];
      ret -> getPixel(x, y) = HSLAPixel(0, 1, 0.5);
    }
  ret -> getPixel(5, 5) = HSLAPixel(0, 1, 0.5);
  y += 5;
  for (int k = x - 4; k <= x + 4; ++ k)
    ret -> getPixel(k, y) = HSLAPixel(0, 0, 1);
  return ret;
}