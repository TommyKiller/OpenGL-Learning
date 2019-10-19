#ifndef DELEGATE_H
#define DELEGATE_H

namespace Events
{
	class Delegate
	{
	public:
		Delegate();

		template <class Owner, class ...Args>
		Delegate(Owner* owner, void (Owner::* method)(Args...))
			: _ptrfunc(nullptr),
			member(true)
		{
			_ptrobject = reinterpret_cast<Object*>(owner);
			_ptrmethod = reinterpret_cast<Method>(method);
		}

		template <class ...Args>
		Delegate(void (*func)(Args...))
			: _ptrobject(nullptr),
			_ptrmethod(nullptr),
			member(false)
		{
			_ptrfunc = reinterpret_cast<Function>(func);
		}

		template<class ...Args>
		void operator()(Args... args)
		{
			if (member && _ptrobject && _ptrmethod)
			{
				void (Object::* method)(Args...) = reinterpret_cast<void(Object::*)(Args...)>(_ptrmethod);
				(_ptrobject->*method)(args...);
			}
			else if (!member && _ptrfunc)
			{
				void (*func)(Args...) = reinterpret_cast<void(*)(Args...)>(_ptrfunc);
				func(args...);
			}
		}

		bool operator!();

		bool operator==(const Delegate& delegate);

		bool operator!=(const Delegate& delegate);

	private:
		struct Object {};
		typedef void(Object::* Method)();
		typedef void(*Function)();

		Object* _ptrobject;
		Method _ptrmethod;
		Function _ptrfunc;

		bool member;
	};
}

#endif
