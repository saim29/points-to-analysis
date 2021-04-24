/*
 * Adapted from https://github.com/SVF-tools/Test-Suite
 * 
 * Alias due to context-insensitive
 * Author: Sen Ye
 * Date: 06/09/2013
 */

int main()
{
	int *p, *q;
	int a,b;
	if (a) {
		p = &a;
		q = &b;
	}
	else {
		p = &b;
		q = &a;
	}
	return 0;
    
}
