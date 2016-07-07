#include <cpp/util/ArrayList.h>

int testList(List<int> & list)
{
	return 0;
}

int main(int argc, char ** argv)
{
	ArrayList<int> x;
	testList(x);

	ArrayList<int> * pd = new ArrayList<int>;
	List<int> * pp = (ArrayList<int> *) pd;
	delete pp;

	return 0;
}