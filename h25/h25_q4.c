#include<stdio.h>
static int c1, c2, c3, c4;

int f1(int x, int y)
{
	int r;
	for (r = 0; y > 0; y--) {
		r = r + x;
	}
	return r;
}

int f2(int x, int y)
{
	int r;
	for (r = 0; y > 0; y--) {
		c2++;
		r++;
	}
	return r;
}

int f3(int x, int y)
{
	int r;
	for (r = 0; y > 0; y--) {
		c1++;
		r = f2(r, x);
	}
	return r;
}

int f4(int x, int y)
{
	int r;
	for (r = 0; y > 0; y = y / 2) {
		if (y % 2 == 1) {
			c3++;
			r = r + x;
		}
		c4++;
		x = x * 2;
	}
	return r;
}

int g(int x, int y, int r)
{
	if (y == 0) {
		/*(ア)*/
		return r;
	}
	else {
		/*(イ),(ウ)*/
		return g(x, y - 1, r + x);
	}
}

int f5(int x, int y)
{
	/*(エ)*/
	return g(x, y, 0);
}

int f6(int x, int y)
{
	if (y == 0) {
		/*(オ)*/
		return 0;
	}
	else if (y % 2 == 1) {
		/*(カ)*/
		return f6(x * 2, y / 2) + x;
	}
	else {
		/*(キ), (ク)*/
		return f6(x * 2, y / 2);
	}
}

int main()
{
	int ans[7];
	ans[0] = f1(3, 5);
	ans[1] = f1(5, 3);
	ans[2] = f2(3, 5);
	c2 = 0;
	ans[3] = f3(3, 5);
	ans[4] = f4(3, 5);
	ans[5] = f5(3, 5);
	ans[6] = f6(3, 5);

	printf("(1)\n(A)%s (B)%s (C)%s (D)%s\n",
		ans[0] == ans[1] ? "〇" : "×", ans[0] == ans[2] ? "〇" : "×",
		ans[0] == ans[3] ? "〇" : "×", ans[0] == ans[4] ? "〇" : "×");

	printf("(2) %d回\n", c1);

	printf("(3)\nx=3,y=5の場合:%d回\n", c2);

	c3 = c4 = 0;
	f4(11, 33);
	printf("(4)\n文2:%d回\n文3:%d回\n", c3, c4);

  printf("(5)\ncheck:%s\n",ans[0] == ans[5]?"〇" : "×");

  printf("(6)\ncheck:%s\n",ans[0] == ans[6]?"〇" : "×");
}