#include <iostream>
#include<iomanip>
#include <stdlib.h>

using namespace std;

int determine(int **a, int width, int sum)
{
    int *row = new int[width];
    int *column = new int[width];
    int diagonal[2];

    for(int i = 0; i < width; i++)
    {
        row[i] = 0;
        for(int j = 0; j < width; j++)
        {
            row[i] += a[i][j];
        }
    }
    for(int i = 0; i < width; i++)
    {
        column[i] = 0;
        for(int j = 0; j < width; j++)
        {
            column[i] += a[j][i];
        }
    }
    diagonal[0] = 0;
    diagonal[1] = 0;
    for(int i = 0; i < width; i++)
    {
        diagonal[0] += a[i][i];
    }
    for(int i = 0; i < width; i++)
    {
        diagonal[1] += a[width-i-1][i];
    }

    for(int i = 0; i < width; i++)
    {
        if(sum != row[i])
            return -1; // Bad
        if(sum != column[i])
            return -1; // Bad
        if(sum != diagonal[0])
            return -1; // Bad
        if(sum != diagonal[1])
            return -1; // Bad
    }
    return 0;
}

int main()
{
    int n;
    int width;
    int **a;
    int *row;
    int *column;
    int diagonal[2];
    int sum;
    int error_row_cnt;
    int error_column_cnt;
    int error_row[2];
    int error_column[2];
    int state; // 1: Good, 0: Fixable, -1: Bad

    cin >> n;
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        error_row_cnt = 0;
        error_column_cnt = 0;
        state = 1;

        // Part1: read the square
        cin >> width;
        a = new int*[width];
        for(int j = 0; j < width; j++)
        {
            a[j] = new int[width];
            for(int k = 0; k < width; k++)
            {
                cin >> a[j][k];
            }
        }

        // Part 2: Calculate the sum of each row, column and diagonal
        row = new int[width];
        column = new int[width];
        for(int j = 0; j < width; j++)
        {
            row[j] = 0;
            for(int k = 0; k < width; k++)
            {
                row[j] += a[j][k];
            }
        }
        for(int j = 0; j < width; j++)
        {
            column[j] = 0;
            for(int k = 0; k < width; k++)
            {
                column[j] += a[k][j];
            }
        }
        diagonal[0] = 0;
        diagonal[1] = 0;
        for(int j = 0; j < width; j++)
        {
            diagonal[0] += a[j][j];
        }
        for(int j = 0; j < width; j++)
        {
            diagonal[1] += a[width-j-1][j];
        }

        // Part3: calculate the sum of good magic square
        for(int j = 0; j < width; j++)
        {
            sum += row[j];
        }
        if(sum % width != 0)
        {
            state = -1; // Bad
        }
        else
        {
            sum = sum / width;

            // Part4: to record the error row, column and determine the state
            for(int j = 0; j < width; j++)
            {
                if(sum != row[j])
                {
                    state = 0; //fixable
                    if(error_row_cnt < 2)
                    {
                        error_row[error_row_cnt] = j;
                    }
                    error_row_cnt++;
                }
                if(sum != column[j])
                {
                    state = 0; //fixable
                    if(error_column_cnt < 2)
                    {
                        error_column[error_column_cnt] = j;
                    }
                    error_column_cnt++;
                }
                if(sum != diagonal[0])
                    state = 0; //fixable
                if(sum != diagonal[1])
                    state = 0; //fixable
            }
        }

        // Part5: deal with fixable square candidate
        if(state == 0)
        {
            if(error_row_cnt == 2 && error_column_cnt == 0)
            {
                for(int j = 0; j < width; j++)
                {
                    swap(a[ error_row[0] ][j], a[ error_row[1] ][j]);
                    state = determine(a, width, sum);

                    if(state == 0)
                    {
                        a[ error_row[0] ][j] *= -1; // use sign to represent the swapped entries
                        a[ error_row[1] ][j] *= -1; // use sign to represent the swapped entries
                        break;
                    }
                    swap(a[ error_row[0] ][j], a[ error_row[1] ][j]);
                }
            }
            else if(error_row_cnt == 0 && error_column_cnt == 2)
            {
                for(int j = 0; j < width; j++)
                {
                    swap(a[j][ error_column[0] ], a[j][ error_column[1] ]);
                    state = determine(a, width, sum);

                    if(state == 0)
                    {
                        a[j][ error_column[0] ] *= -1; // use sign to represent the swapped entries
                        a[j][ error_column[1] ] *= -1; // use sign to represent the swapped entries
                        break;
                    }
                    swap(a[j][ error_column[0] ], a[j][ error_column[1] ]);
                }
            }
            else if(error_row_cnt == 2 && error_column_cnt == 2)
            {
                swap(a[ error_row[0] ][ error_column[0] ], a[ error_row[1] ][ error_column[1] ]);
                state = determine(a, width, sum);

                if(state == 0)
                {
                    a[ error_row[0] ][ error_column[0] ] *= -1; // use sign to represent the swapped entries
                    a[ error_row[1] ][ error_column[1] ] *= -1; // use sign to represent the swapped entries
                }
                else
                {
                    swap(a[ error_row[0] ][ error_column[0] ], a[ error_row[1] ][ error_column[1] ]);
                    swap(a[ error_row[1] ][ error_column[0] ], a[ error_row[0] ][ error_column[1] ]);
                    state = determine(a, width, sum);

                    if(state == 0)
                    {
                        a[ error_row[1] ][ error_column[0] ] *= -1; // use sign to represent the swapped entries
                        a[ error_row[0] ][ error_column[1] ] *= -1; // use sign to represent the swapped entries
                    }
                }
            }
            else
            {
                state = -1;
            }
        }

        // Part6: print the answer
        if(state == 1)
        {
            cout << "good " << sum << endl;
        }
        else if(state == 0)
        {
            cout << "fixable " << sum << endl;
            for(int j = 0; j < width; j++)
            {
                for(int k = 0; k < width; k++)
                {
                    if(a[j][k] > 0)
                    {
                        cout << setw(6) << a[j][k];
                    }
                    else
                    {
                        if(abs(a[j][k]) < 10)
                        {
                            cout << "   (" << -a[j][k] << ")";
                        }
                        else if(abs(a[j][k]) < 100)
                        {
                            cout << "  (" << -a[j][k] << ")";
                        }
                        else
                        {
                            cout << " (" << -a[j][k] << ")";
                        }
                    }
                }
                cout << endl;
            }
        }
        else
        {
            cout << "bad" << endl;
        }

        //Part7: free the memory
        for(int j = 0; j < width; j++)
        {
            delete [] a[j];
        }
        delete [] a;
    }
    return 0;
}
