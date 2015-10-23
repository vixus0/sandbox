C++'s Absolute Bullshit
-----------------------

* extern declares without definition
* static struct member needs definition outside
* can have int x and class x for some ridiculous reason EXCEPT if class template
* stuff declared in try {…} not available in catch {…}
* declarations in else if (…) can be used in subsequent else blocks
* labels have function scope
* if reordering member declarations in a class gives a valid but alternate program stuff becomes undefined
* names defined anywhere in a class are available to all member functions
* argument dependent name lookup allows access to functions in other namespace if argument type is in that namespace
* int x - external linkage, const int x - internal, static int x - internal, extern const int x - external
* stuff declared in global namespace has static storage duration and get zero initialized
* can implicitly convert pointer to array but not array to pointer, i.e. can't do: array = pointer
* int * can be implicitly converted to int const * but not vice versa
* c-style casts do: const_cast, static_cast, reinterpret_cast
* only static casts and c-style casts can cast enum to int
* deleting a pointer to a base class pointing to a subclass is legal IF base destructor is virtual
* deleting an array of objects using a base class pointer is undefined
* pointer addition/subtraction: both operands and result must point inside same array or (int * x; x+3 = undefined)
* bit shifting by more bits than size of left operand is undefined
