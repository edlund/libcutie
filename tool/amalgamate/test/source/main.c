
#include <stdlib.h>

#include "bar.h"
#include "test.h"

const char* include_foo1 = "#include \"foo.h\"";
const char* include_bar1 = "#include \"bar.h\"";
const char* include_foo2 = "#include <foo.h>";
const char* include_bar2 = "#include <bar.h>";

int main(int argc, char* argv[])
{
	assert(foo() == 1);
	assert(bar() == 2);
	return EXIT_SUCCESS;
}

