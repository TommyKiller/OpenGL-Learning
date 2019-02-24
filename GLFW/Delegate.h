#ifndef DELEGATE_H
#define DELEGATE_H


namespace Events
{
	class Delegate
	{
	public:
		Delegate();

		template <class Owner>
		Delegate(Owner *owner, void (Owner::*method)())
			: _ptrfunc(nullptr)
		{
			_ptrobject = reinterpret_cast<Object*>(owner);
			_ptrmethod = reinterpret_cast<Method>(method);
			member = true;
		}

		Delegate(void (*func)());

		void operator()();

		bool operator!();

		bool operator==(const Delegate& delegate);

		bool operator!=(const Delegate& delegate);

	private:
		struct Object {};
		typedef void (Object::*Method)();
		typedef void (*Func)();

		Object* _ptrobject;
		Method _ptrmethod;
		Func _ptrfunc;

		bool member;
	};
}


#endif
