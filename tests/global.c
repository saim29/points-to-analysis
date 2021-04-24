/*
 * Adapted from https://github.com/SVF-tools/Test-Suite
 * 
 * Context-insensitive.
 * Author: Sen Ye
 * Date: 10/10/2013
 */


int global;
int *p_global;

void foo() {
	p_global = &global;
}

int main() {
    
	int *p_local;
	p_local = &global;
	foo();
	return 0;
}
