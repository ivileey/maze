#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int X = 6, Y = 6;
struct pos
{
	pos(int _x = -1, int _y = -1) :x(_x), y(_y){}
	int x, y;
};
pos b(0, 0);
pos e(4, 5);
int table[X][Y] =
{
	0,1,0,0,0,1,
	0,0,0,1,0,1,
	1,0,1,0,0,1,
	0,0,0,1,1,1,
	0,1,0,0,0,0,
	0,0,0,0,1,1,
};
void find_pos(vector<pos> &step, pos x)
{
	step.swap(vector<pos>());
	int tmp[4][2] =
	{
		0, -1,
		-1, 0,
		0, 1,
		1, 0
	};
	for (int i = 0; i < 4; ++i)
	{
		int _x = x.x + tmp[i][0];
		int _y = x.y + tmp[i][1];
		if (_x < 0 || _y < 0 || _x>X-1 || _y>Y-1)
			continue;
		if (table[_x][_y] == 0)
			step.push_back(pos(_x, _y));
	}
}
int count_ = 0;
void print_pos(vector<pos> v)
{
	cout << "第" << ++count_ << "条路径:";
	for_each(v.begin(), v.end(), [](const pos& p){cout << "(" << p.x << "," << p.y << ")  "; });
	cout << endl;
	cout << "路径长度为：" << v.size()<<endl;
}
void find_way(pos begin, vector<pos> result)
{
	vector<pos> step;
	result.push_back(begin);
	if (begin.x == e.x&&begin.y == e.y)
	{
		print_pos(result);
		return;
	}
	find_pos(step, begin);
	for (auto j : step)
	{
		table[begin.x][begin.y] = 1;
		find_way(j, result);
		table[begin.x][begin.y] = 0;
	}
}

void find_way2()
{
	static queue<pos> step;
	vector<pair<pos, pos>> result;
	vector<pos> tmp;
	step.push(b);
	while (!step.empty())
	{
		if (step.front().x == e.x&&step.front().y == e.y)
			break;
		find_pos(tmp, step.front());
		for (auto &i : tmp)
		{
			result.push_back(make_pair(step.front(),i));
			cout << i.x << ',' << i.y<<' ' ;
			table[i.x][i.y] = 1;
			step.push(i);
		}
		cout << endl;
		step.pop();
	}
	pos p(4,5);
	while (p.x != 0 || p.y != 0)
	{
		for (auto &j : result)
		{
			if (j.second.x == p.x&&j.second.y == p.y)
			{
				p.x = j.first.x; p.y = j.first.y;
				cout << p.x << ',' << p.y << endl;
				break;
			}
		}
	}
}
int main()
{
	int a[2][2] =
	{
		1, 2,
		3, 4
	};
	int *b = (int*)a;
	cout << b[3];
	//find_way2();
	cin.get();
}