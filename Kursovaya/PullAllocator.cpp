#include <iostream>
using namespace std;
using namespace __gnu_cxx;

class RequiredAllocation
{
public:
	RequiredAllocation ();
	~RequiredAllocation ();
	std::basic_string<char> s = "hello world!\n";
};

RequiredAllocation::RequiredAllocation ()
{
	cout << "RequiredAllocation::RequiredAllocation()" << endl;
}
RequiredAllocation::~RequiredAllocation ()
{
	cout << "RequiredAllocation::~RequiredAllocation()" << endl;
}

void alloc(__gnu_cxx ::new_allocator<RequiredAllocation>* all, unsigned int size, void* pt, RequiredAllocation* t){
	try
		{
			all->allocate (size, pt);
			cout << all->max_size () << endl;
			for (auto& e : t->s)
				{
					cout << e;
				}
		}
	catch (std::bad_alloc& e)
		{
			cout << e.what () << endl;
		}
}

int
main ()
{

	__gnu_cxx ::new_allocator<RequiredAllocation> *all =
			new __gnu_cxx ::new_allocator<RequiredAllocation> ();

	RequiredAllocation t;
	void* pt = &t;

	/**
	 * What happens when new can find no store to allocate? By default, the allocator throws a stan-
	 * dard-library bad_alloc exception (for an alternative, see §11.2.4.1)
	 * @C Bjarne Stroustrup  The C++ Programming language
	 */
	unsigned int size = 1073741824;
	alloc(all, size, &pt, &t);

	size = 1;
	alloc(all, size, &pt, &t);

	return 0;
}