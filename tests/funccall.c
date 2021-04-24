/*
 * Adapted from https://github.com/SVF-tools/Test-Suite
 * 
 * Alias due to lack of context-sensitivity.
 * Author: Sen Ye
 * Date: 06/09/2013
 */

void foo(int *m, int *n)
{
	int x, y;
	x = *n;
	y = *m;
	*m = x;
	*n = y;
}

int main()
{
	int *p, *q;
	int a, b, c;
	if (c) {
		p = &a;
		q = &b;
		foo(p,q);
	}
	else {
		p = &b;
		q = &c;
		foo(p,q);
	}
	return 0;
}
