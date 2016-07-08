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
	x.add(1);
	cout << x.front() << endl;
	x.remove(1);
	x.add(2);
	cout << x.front() << endl;
	return 0;
}