
#include <stdlib.h>

#include "bar.h"
#include "test.h"

const char* include_foo = "#include \"foo.h\"";
const char* include_bar = "#include \"bar.h\"";

int main(int argc, char* argv[])
{
	assert(foo() == 1);
	assert(bar() == 2);
	return EXIT_SUCCESS;
}

