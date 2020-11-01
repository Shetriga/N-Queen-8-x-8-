#include <iostream>
#include <windows.h>

using namespace std;

class csnode
{
public:
	char x[8][8];
	int cr = 0;
	csnode *pnext;
};

int cnt = 0;
class cstack
{
public:
	csnode *phead, *ptail;

	cstack() : phead(NULL), ptail(NULL)
	{}

	void push(csnode* pnn)
	{
		pnn->pnext = phead;
		phead = pnn;
	}

	csnode* pop()
	{
		if (phead == NULL)
		{
			return NULL;
		}
		else
		{
			csnode *ptrav = phead;
			phead = phead->pnext;
			ptrav->pnext = NULL;
			return ptrav;
		}
	}
};

cstack s;

csnode* getinit()
{
	csnode *pnn = new csnode;
	for (int i = 0; i < 8; i++)
	{
		for (int c = 0; c < 8; c++)
		{
			pnn->x[i][c] = ' ';
		}
	}
	pnn->cr = 0;
	//cout << "the current row of this node is:   " << pnn->cr << endl;
	//system("pause");
	return pnn;
}

void get_children(csnode* pcur, cstack &s)
{
	csnode *pnn;
	if (pcur->cr == 0)
	{
		cout << "OK" << endl;
		//This is to be like our father!
		for (int i = 0; i < 8; i++)
		{
			//cout << "Done" << endl;
			pnn = new csnode;
			for (int r = 0; r < 8; r++)
			{
				for (int c = 0; c < 8; c++)
				{
					//	cout << "Yes" << endl;
					pnn->x[r][c] = pcur->x[r][c];
				}
			}
			//Now We add our own queen!

			pnn->x[pcur->cr][i] = 'q';
			pnn->cr++;
			s.push(pnn);
			//cout << "Over here!" << endl;
		}
	}

	else
	{
		int k = pcur->cr, flag;
		for (int i = 0; i < 8; i++)
		{
			pnn = new csnode;
			flag = 1;
			pnn->cr = pcur->cr;
			for (int r = 0; r < 8; r++)
			{
				for (int c = 0; c < 8; c++)
				{
					pnn->x[r][c] = pcur->x[r][c];
				}
			}

			for (int y = k; y >= 0; y--)
			{
				if (pnn->x[y][i] != ' ')
				{
					flag = 0;
				}
			}

			int r = i;
			for (int y = k; y >= 0; y--)
			{
				if (r >= 8)
				{
					break;
				}

				if (pnn->x[y][r] != ' ')
				{
					flag = 0;
				}
				r++;
			}

			int z = i;
			for (int y = k; y >= 0; y--)
			{
				if (z < 0)
				{
					break;
				}

				if (pnn->x[y][z] != ' ')
				{
					flag = 0;
				}
				z--;
			}

			if (flag == 1)
			{
				if (pcur->cr == 7)
				{
					cnt++;
					cout << "YESSSSSSSSSSSSSSSSSSSSS!!!" << endl;
				}
				pnn->x[k][i] = 'q';
				pnn->cr++;
				s.push(pnn);
			}
		}
	}
	
}


void dobk()
{
	csnode *pcur = getinit();
	s.push(pcur);

	while (s.phead != NULL)
	{
		pcur = s.pop();
		if (pcur->cr == 8)
		{
			for (int r = 0; r < 8; r++)
			{
				for (int c = 0; c < 8; c++)
				{                                                                  // THIS IS IF YOU WANT TO
					if (pcur->x[r][c] == ' ')                                           // DISPLAY EACH STEP OF
					{                                                                 //  THE GAME (WHICH TOOK ME
						cout << "=    ";                                             //   30 MINUTES TO MAKE SURE
					}                                                                 // THAT EVERY STEP IS VALID :)
					else
						cout << pcur->x[r][c] << "    ";
				}
				cout << endl;
			}
			cout << endl << endl << endl << endl;
		}
		//system("pause");
		get_children(pcur, s);
	}
}


void main() {
	dobk();
	cout << "Number of solutions is:   " << cnt << endl;
	system("pause");
}