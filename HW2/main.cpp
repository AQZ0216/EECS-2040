#include <iostream>

using namespace std;

class Puzzle
{
public:
    Puzzle(int n);
    void input();
    void searching();
    void start(int r, int c);
private:
    string *matrix;
    int **path;
    int num;
    int length;
};

int vowel(char c);
void print_rearrange(string s);

int main()
{
    int n;
    cin >> n;

    Puzzle puzzle(n);

    puzzle.input();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            puzzle.start(i, j);
            puzzle.searching();
        }
    }

    return 0;
}

Puzzle::Puzzle(int n)
{
    num = n;
    matrix = new string[num];
    path = new int*[num];
    for(int i = 0; i < num; i++)
    {
        path[i] = new int[num];
        for(int j = 0; j < num; j++)
        {
            path[i][j] = 0;
        }
    }
}

void Puzzle::input()
{
    for(int i = 0; i < num; i++)
    {
        cin >> matrix[i];
    }
    return;
}

void Puzzle::searching()
{
    string word;
    int row;
    int col;
    int cv_plus = 0;

    for(int i = 1; i <= length; i++)
    {
        for(int j = 0; j < num; j++)
        {
            for(int k = 0; k < num; k++)
            {
                if(path[j][k] == i)
                    word += matrix[j][k];
            }
        }
    }

    int i = 0;

    while(i < length)
    {
        if( vowel(word[i]) ) //(cv+)+v
        {
            return;
        }

        i++;
        if(i == length && i >= 5 && cv_plus >= 2) //(cv+)+c
        {
            cout << word << " " ;
            print_rearrange(word);
            cout << endl;
        }
        else if(i < length)
        {
            if(vowel(word[i])==0) //(cv+)+cc
            {
                return;
            }

            while(vowel(word[i]) && i < length)//(cv+)+
            {
                i++;
            }
            cv_plus++;
        }
    }

    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            if(path[i][j] == length)
            {
                row = i;
                col = j;
            }
        }
    }

    if(row+1 < num && path[row+1][col] == 0)
    {
        length++;
        path[row+1][col] = length;
        searching();
        length--;
        path[row+1][col] = 0;
    }
    if(col+1 < num && path[row][col+1] == 0)
    {
        length++;
        path[row][col+1] = length;
        searching();
        length--;
        path[row][col+1] = 0;
    }
    if(row > 0 && path[row-1][col] == 0)
    {
        length++;
        path[row-1][col] = length;
        searching();
        length--;
        path[row-1][col] = 0;
    }
    if(col > 0 && path[row][col-1] == 0)
    {
        length++;
        path[row][col-1] = length;
        searching();
        length--;
        path[row][col-1] = 0;
    }
    return;
}

void Puzzle::start(int r, int c)
{
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            path[i][j] = 0;
        }
    }
    path[r][c] = 1;
    length = 1;
    return;
}

int vowel(char c)
{
    if(c == 'a' ||
       c == 'e' ||
       c == 'i' ||
       c == 'o' ||
       c == 'u'   )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_rearrange(string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(vowel(s[i]))
            cout << s[i];
    }
    for(int i = 0; i < s.size(); i++)
    {
        if(vowel(s[i])==0)
            cout << s[i];
    }
    return;
}
