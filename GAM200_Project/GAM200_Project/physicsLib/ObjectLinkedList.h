#pragma once

	template< typename type >
	class ObjectLinkList
	{
	public:
		typedef type * ObjPtr;
		typedef type& ObjRef;

		ObjectLinkList()
			:First(NULL),Last(NULL),ObjectCount(0)
		{
		}

		ObjPtr pop_front()
		{
			if(First==NULL)
			{
				return NULL;
			}
			else
			{
				type * first = First;
				First = first->Next;
			
				if(First)
				{
					First->Prev = NULL;
				}
				else
				{
					Last = NULL;
				}

				--ObjectCount;
				return first;
			}



		}

		void push_back(ObjPtr object)
		{
			++ObjectCount;

			if( Last == NULL )
			{
				First = object;
				Last = object;
				object->Next = NULL;
				object->Prev = NULL;
			}
			else
			{
				object->Prev = Last;
				object->Next = NULL;
				Last->Next = object;
				Last = object;
			}
		}

		void erase(ObjPtr object)
		{
			--ObjectCount;

			if( object->Next == NULL && object->Prev == NULL)
			{
				Last = NULL;
				First = NULL;
			}
			else if( object->Next == NULL )
			{
				Last = object->Prev;
				if( Last ) Last->Next = NULL;

			}
			else if( object->Prev == NULL )
			{
				First = object->Next;
				if( First ) First->Prev = NULL;
			}
			else
			{
				object->Prev->Next = object->Next;
				object->Next->Prev = object->Prev;
			}

		}

		class iterator
		{
		public:
			friend class ObjectLinkList;
			iterator(){};
			iterator(ObjPtr p) : item(p) {}
			void operator--()
			{
				item=item->Prev;
			}
			void operator++()
			{
				item=item->Next;
			}
			ObjRef operator*()
			{
				return *item;
			}
			ObjPtr operator->()
			{
				return item;
			}
			bool operator==(const iterator& i)
			{ 
				return item==i.item;
			}
			bool operator!=(const iterator& i)
			{ 
				return item!=i.item;
			}
			operator bool()
			{
				return item!=NULL;
			}
			operator ObjPtr()
			{ 
				return item;
			}
			ObjPtr GetPtr()
			{ 
				return item;
			}
		private:
			ObjPtr item;
		};

		iterator begin()
		{ 
			First;
		}
		iterator end()
		{ 
			return NULL;
		}
		ObjPtr last()
		{ 
			return Last;
		}
	private:
		ObjPtr First;
		ObjPtr Last;
		unsigned ObjectCount;
	};

