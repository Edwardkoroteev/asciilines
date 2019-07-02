#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool checkFile(string filename);
void initSpace(char** &canvas, int height, int width);
vector<string> split(string line);
void populateSpace(char** &canvas, vector<string> sep, int height, int width);
void printSpace(char** canvas, int height, int width);

int main(int argc, char *argv[])
{
  ifstream file;
  string file_tvg = argv[1];
  vector<string> seperated;
  string line;
  int counter = 0;
  char** canvas;
  int height;
  int width;


  if(checkFile(file_tvg) == false)
  {
    cerr << "File format must be .tvg" << endl;
    exit(1);
  }

  file.open(file_tvg);

  if(file.is_open())
  {
    while(getline(file, line))
    {
      seperated = split(line);
      if(counter == 0)
      {
        initSpace(canvas, stoi(seperated[0]), stoi(seperated[1]));
        height = stoi(seperated[0]);
        width = stoi(seperated[1]);
        counter++;
      }
      else
      {
        populateSpace(canvas, seperated, height, width);
      }
    }
    file.close();
  }
  else
    cout << "Unable to open file" << endl;

  printSpace(canvas, height, width);

  return 0;
}

bool checkFile(string filename)
{
  if(filename.find(".tvg") != string::npos)
    return true;

  return false;
}

void initSpace(char** &canvas, int height, int width)
{
  canvas = new char*[height];
  for(int i = 0; i < height; ++i)
    canvas[i] = new char[width];

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      canvas[i][j] = '.';
    }
  }
}

vector<string> split(string line)
{
  vector<string> internal;
  stringstream ss(line);
  string token;

  while(getline(ss, token, ' '))
  {
    internal.push_back(token);
  }

  return internal;
}

void populateSpace(char** &canvas, vector<string> sep, int height, int width)
{
  string character = sep[0];
  int y = stoi(sep[1]);
  int x = stoi(sep[2]);
  string direction = sep[3];
  int amount = stoi(sep[4]);
  char charCstring[character.size() + 1];
  strcpy(charCstring, character.c_str());

  for(int i = 0; i < amount; i++)
  {
    if(direction.at(0) == 'h')
    {
      if(x < 0)
      {
        amount = amount + x;
        x = 0;
      }

      if(amount > width)
        amount = width;

      canvas[y][i+x] = charCstring[0];
    }
    else if(direction.at(0) == 'v')
    {
      if(y < 0)
      {
        amount = amount + y;
        y = 0;
      }
        
      if(amount > height)
        amount = height;

      canvas[i+y][x] = charCstring[0];
    }
  }
}

void printSpace(char** canvas, int height, int width)
{
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      cout << canvas[i][j];
    }
    cout << endl;
  }
}
