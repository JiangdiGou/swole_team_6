#include "_EntryPoint.h"
#include "gameComponents/objFactory.h"

#ifdef FACTORY_TEST_RUN
int main(int argc, char **argv)
#else
int falseMain4(int argc, char **argv)
#endif
{
	FACTORY = new objFactory();
	return 0;
}