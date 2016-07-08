#include <cpp/util/ArrayList.h>
#include <cpp/util/LinkedList.h>

using namespace cpp::util;
int testList(List<int> list)
{
	return 0;
}

int main(int argc, char ** argv)
{
	/*
	ArrayList<int> x;
	testList(x);

	ArrayList<int> * pd = new ArrayList<int>;
	List<int> * pp = (ArrayList<int> *) pd;
	delete pp;
	*/
	
	int n = 0;
	LinkedList<int> x;

	for (int i = 0; i < 2; i++)
		x.add(i);
	LinkedList<int>::iterator iter;
	for (LinkedList<int>::iterator it = x.begin(); it != x.end(); ++it)
		std::cout << ' ' << *it;
	cout << endl;
	x.clear();
	cout << x.size() << endl;
	return 0;
}