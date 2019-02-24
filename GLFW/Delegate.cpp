#include "Delegate.h"

Events::Delegate::Delegate()
	: _ptrobject(nullptr),
	_ptrmethod(nullptr),
	_ptrfunc(nullptr),
	member(false)
{}

Events::Delegate::Delegate(void(*func)())
	: _ptrobject(nullptr),
	_ptrmethod(nullptr)
{
	_ptrfunc = func;
	member = false;
}

void Events::Delegate::operator()()
{
	if (member && _ptrobject && _ptrmethod)
	{
		(_ptrobject->*_ptrmethod)();
	}
	else if (_ptrfunc)
	{
		_ptrfunc();
	}
}

bool Events::Delegate::operator!()
{
	if (member)
	{
		return (!_ptrobject || !_ptrmethod);
	}
	else
	{
		return !_ptrfunc;
	}
}

bool Events::Delegate::operator==(const Delegate& delegate)
{
	return (_ptrobject == delegate._ptrobject && _ptrmethod == delegate._ptrmethod && _ptrfunc == delegate._ptrfunc);
}

bool Events::Delegate::operator!=(const Delegate& delegate)
{
	return !(*this == delegate);
}
