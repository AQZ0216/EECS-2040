#include <iostream>
using namespace std;

int main()
{
        int n;
	int height;
	int temp;
        cin >> n;
	for(int i=0; i<n; i++)
	{
		cin >> height;
		for(int j=1; j<=height; j++)
		{
			for(int k=0; k<j; k++)
			{
				if(k == 0)
				{
					temp=1;
				}
				else
				{
					temp = temp*(j-k)/k;
					cout << " ";
				}
				cout << temp;
			}
			cout << endl;
		}
	}
        return 0;
}
