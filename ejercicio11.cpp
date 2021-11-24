#include "iostream"
using namespace std;

class File
{
public:
  int size, score, lines;
  File(int size, int lines, int score) : size(size), lines(lines), score(score) {}
};

void mochila(File **&files, int cantFiles, int actualFile, int maxLines, int maxSize, int scoreActual, int *&solActual, int &bestScore, int *&bestSolution)
{
  if (actualFile == cantFiles)
  {
    if (scoreActual > bestScore)
    {
      bestScore = scoreActual;
      for (int i = 0; i < cantFiles; bestSolution[i] = solActual[i], i++)
        ;
    }
  }
  else
  {
    mochila(files, cantFiles, actualFile + 1, maxLines, maxSize, scoreActual, solActual, bestScore, bestSolution);

    File *file = files[actualFile];

    if (file->size <= maxSize && file->lines <= maxLines)
    {
      solActual[actualFile]++;
      maxSize -= file->size;
      maxLines -= file->lines;
      scoreActual += file->score;
      mochila(files, cantFiles, actualFile + 1, maxLines, maxSize, scoreActual, solActual, bestScore, bestSolution);
      solActual[actualFile]--;
    }
  }
}

int main()
{

  int cantFiles, maxLines, maxSize, size, score, lines;
  File **files;

  cin >> cantFiles;
  cin >> maxSize;
  cin >> maxLines;

  files = new File *[cantFiles];
  for (int i = 0; i < cantFiles; i++)
  {
    cin >> size;
    cin >> lines;
    cin >> score;

    files[i] = new File(size, lines, score);
  };

  int *actualSolution = new int[cantFiles];
  int *bestSolution = new int[cantFiles];
  for (int i = 0; i < cantFiles; actualSolution[i] = 0, bestSolution[i] = 0, i++)
    ;
  int bestScore = -1;

  mochila(files, cantFiles, 0, maxLines, maxSize, 0, actualSolution, bestScore, bestSolution);

    cout << bestScore << endl;

  return 0;
}