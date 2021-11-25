#include "iostream"
using namespace std;

class File
{
public:
    int size;
    int lines;
    int score;
    File(int size, int lines, int score) : size(size), lines(lines), score(score) {}
};
int max(int a, int b)
{
  return a >= b ? a : b;
}
int main()
{

  int cantElem, maxSize, maxLines, lines, size, score;

  File **files;
  cin >> cantElem;
  files = new File *[cantElem];
  cin >> maxSize;
  cin >> maxLines;
  for (int i = 0; i < cantElem; i++)
  {
    cin >> size;
    cin >> lines;
    cin >> score;
    files[i] = new File(size, lines, score);
  };

  int ***matDP = new int**[cantElem];

  for (int i = 0; i < cantElem; i++)
  {
    matDP[i] = new int*[maxSize + 1];
    
    for (int j = 0; j <= maxSize; j++)
    {
        matDP[i][j] = new int[maxLines + 1];
    }
  }
  for(int j = 0; j <= maxSize; j++){
    for(int k = 0; k <= maxLines; k++){
          matDP[0][j][k] = 0;    
    }
  }
  for (int i = 1; i < cantElem; i++)
  {
    for (int j = 1; j <= maxSize; j++)
    {
        for(int k = 1; k <= maxLines ; k++)
        {
          if (files[i]->size > j || k < files[i]->lines)
          {
              matDP[i][j][k] = matDP[i - 1][j][k];
          }
          else
          {
              int usingIt = files[i]->score + matDP[i - 1][j - files[i]->size][k - files[i]->lines];
              int notUsingIt = matDP[i - 1][j][k];
              matDP[i][j][k] = max(usingIt, notUsingIt);
          }
        }
    }
  }
  cout << matDP[cantElem - 1][maxSize][maxLines] << endl;

  return 0;
}