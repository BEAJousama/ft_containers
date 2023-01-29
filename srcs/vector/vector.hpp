/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/30 00:18:23 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include "../utils/common.hpp"
#include <memory>

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef Allocator                                			allocator_type;
            typedef T                                        			value_type;
            typedef typename allocator_type::reference       			reference;
            typedef typename allocator_type::const_reference 			const_reference;
            typedef ft::random_access_iterator<T>            			iterator;
            typedef ft::random_access_iterator<const T>     			const_iterator;
            typedef typename allocator_type::difference_type 			difference_type;
            typedef typename allocator_type::size_type       			size_type;
            typedef typename allocator_type::pointer         			pointer;
            typedef typename allocator_type::const_pointer   			const_pointer;
            typedef ft::reverse_iterator<iterator>          			reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    			const_reverse_iterator;
			
        private:
            pointer         v_start;
            size_type       v_size ;
            size_type       v_capacity;
            allocator_type  v_alloc;
		
		private:
			
			void reallocate(size_type n)
			{
				pointer v_start_new = v_alloc.allocate(n);
				size_type v_size_new = v_size ;
				for (size_type i = 0; i < v_size; i++)
					v_alloc.construct(v_start_new + i, v_start[i]);
				this->~vector();
				v_size = v_size_new;
				v_capacity = n;
				v_start = v_start_new;
			};

			void constructable_resize (size_type n, value_type val = value_type())
            {
                if (static_cast<int>(n) < 0)
                    std::__throw_length_error("vector");
				if ( n > v_capacity )
				{
					pointer v_start_new = v_alloc.allocate(n);
					size_type v_size_new = v_size ;
					this->~vector();
					v_size = v_size_new;
					v_capacity = n;
					v_start = v_start_new;	
				}
				if ( n > v_size )
				{
					v_size = 0;
					for (size_type i = 0; i < n; i++)
					{
						v_alloc.construct(v_start + i, val);
						v_size++;
					}
				}
				if ( n < v_size )
				{
					for (size_type i = 0; i < n; i++)
						v_alloc.construct(v_start + i, val);
					for (size_type i = n; i < v_size; i++)
						v_alloc.destroy(v_start + i);
					v_size = n;
				}
            };

        public:
/*--------------------------------------------------------------- Member Functions -----------------------------------------------------------------*/
			//default		
            explicit vector (const allocator_type& alloc = allocator_type()) :
            v_start(t_nullptr), 
            v_size(0), 
            v_capacity(0), 
            v_alloc(alloc) 
            {
            };

            //fill
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
            v_size(n), 
            v_capacity(n), 
            v_alloc(alloc)
            {
                v_start = v_alloc.allocate(n);
                for(size_type i = 0; i < n; i++)
                    v_alloc.construct(v_start + i, val);
            };

            //OPERATOR=
            vector& operator= (const vector& x){
                if (this == &x)
                    return *this;
                for (size_type i = 0; i < v_size; i++)
                    v_alloc.destroy(v_start + i);
                this->v_size = x.v_size;
                if(v_capacity < v_size){
                    if (v_capacity != 0)
                        v_alloc.deallocate(v_start, v_capacity);
                    v_capacity = v_size;
                    v_start = v_alloc.allocate(v_capacity);
                }
                for (size_type i = 0; i < v_size; i++)
                    v_alloc.construct(v_start + i, x[i]);
                return *this;
            };

            //copy
            vector (const vector& x) :  v_size(0), v_capacity(0){
                *this = x;
            };

            // Range iterator
            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : v_alloc(alloc)
            {
				if (first > last)
					std::__throw_length_error("vector");
				v_size = last - first;
				v_capacity = v_size;
				v_start = v_alloc.allocate(v_capacity);
				for (difference_type i = 0; i < static_cast<difference_type>(v_size); i++)
					v_alloc.construct(v_start + i, *(first + i));
            };
            
            ~vector()
            {
                clear();
                if (v_capacity)
                    v_alloc.deallocate(v_start, v_capacity);
            };
            
/*------------------------------------------------------------------ Iterators ---------------------------------------------------------------------*/
			iterator begin()
			{
				return iterator(v_start);
			};
			
			iterator end()
			{
				return iterator(v_start + v_size);
			};

			const_iterator begin() const
			{
				return const_iterator(v_start);
			};
			
			const_iterator end() const
			{
				return const_iterator(v_start + v_size);
			};
			
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			};
			
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			};

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			};
			
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			};
/*------------------------------------------------------------------ Capacity ----------------------------------------------------------------------*/

			size_type size() const
			{
				return v_size;
			};
			
			size_type max_size() const
			{
				return v_alloc.max_size();
			};
			
			void resize (size_type n, value_type val = value_type())
            {
				if (n  > max_size() || static_cast<int>(n) < 0)
					std::__throw_length_error("vector");
				if ( n > v_capacity )
					reallocate(n);
				if ( n > v_size )
				{
					for (size_type i = v_size; i < n; i++)
					{
						v_alloc.construct(v_start + v_size , val);
						v_size++;
					}
				}
				if ( n < v_size )
				{
					for (size_type i = n; i < v_size; i++)
						v_alloc.destroy(v_start + i);
					v_size = n;
				}
            };

			size_type capacity() const
			{
				return v_capacity;;
			};

			bool empty() const
			{
				return (v_size == 0);
			};
			
            void reserve (size_type n)
            {
				if (n  > max_size())
					std::__throw_length_error("vector");
                if (n > v_capacity)
					reallocate(n);
            };
			
/*---------------------------------------------------------------- Element Access ------------------------------------------------------------------*/

            const_reference operator[] (size_type n) const
            {
                return v_start[n];   
            };
            
            reference operator[] (size_type n)
            {
                return v_start[n];   
            };

			reference at (size_type n)
			{
				if (n >= v_size)
					std::__throw_out_of_range("vector");
				return v_start[n];
			};
			
			const_reference at (size_type n) const
			{
				if (n >= v_size)
					std::__throw_out_of_range("vector");
				return v_start[n];				
			};

			reference front()
			{
				return *v_start;
			};
			
			const_reference front() const
			{
				return *v_start;
			};

			reference back()
			{
				return *(v_start + v_size - 1);
			};
			
			const_reference back() const
			{
				return *(v_start + v_size - 1);
			};
			
/*------------------------------------------------------------------ Modifiers ---------------------------------------------------------------------*/
			
			template <class InputIterator>  void assign (InputIterator first, InputIterator last,
						typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				if(first > last)
					throw std::logic_error("vector");
				clear();
				size_type diff = static_cast<size_type>(last - first);
				if (diff > v_capacity)
				{
					pointer v_start_new = v_alloc.allocate(diff);
					size_type v_size_new = v_size ;
					this->~vector();
					v_size = v_start_new;
					v_capacity = diff;
					v_start = v_start_new;	
				}
				if (diff > v_size)
				{
					v_size = 0;
					for (size_type i = 0; i < diff; i++)
					{
						v_alloc.construct(v_start + i, *first);
						v_size++;
						first++;
					}
				}
				if ( diff < v_size )
				{
					for (size_type i = 0; i < diff; i++)
					{
						v_alloc.construct(v_start + i, *first);
						first++;	
					}
					for (size_type i = diff; i < v_size; i++)
						v_alloc.destroy(v_start + i);
					v_size = diff;
				}
			};
			
			void assign (size_type n, const value_type& val)
			{
				clear();
				constructable_resize(n, val);
			};
            
			void push_back(value_type elem)
            {
                if (v_size == v_capacity)
                {
                    size_type capacity = (v_capacity == 0 ? 1 : v_capacity * 2 );
					reallocate(capacity);
                }
                v_start[v_size++] = elem;
            };

			void pop_back()
			{
				v_alloc.destroy(v_start + v_size - 1);
				v_size--;
			};

			iterator insert (iterator position, const value_type& val)
			{

				size_type pos = static_cast<size_type>(position - begin());
				if (position == end())
				{
					push_back(val);
					return (iterator(v_start + pos));
				}
				if (v_size == v_capacity)
				{
					pointer v_start_new = pointer();
					size_type v_size_new = v_size ;
					v_start_new = v_alloc.allocate(v_size * 2 + (v_capacity == 0));
					for (size_type i = v_size; i > pos; i--)
						v_alloc.construct(v_start_new + i, v_start[i - 1]);
					for (size_type i = 0; i < pos; i++)
						v_alloc.construct(v_start_new + i, v_start[i]);
					v_alloc.construct(v_start_new + pos, val);
					this->~vector();
					v_size = v_size_new;
					v_capacity = v_size * 2;
					v_start = v_start_new;
				}
				else
				{
					for (size_type i = v_size; i > pos; i--)
					{
						v_alloc.destroy(v_start + i);
						v_alloc.construct(v_start + i, v_start[i - 1]);
					}
					v_alloc.destroy(v_start + pos);
					v_alloc.construct(v_start + pos, val);		
				}
				v_size++;
				return (iterator(v_start + pos));
			};

    		void insert (iterator position, size_type n, const value_type& val)
			{

				if (n == 0)
					return;
				else if (n + v_size > max_size())
					throw std::length_error("vector");
				size_type pos = static_cast<size_type>(position - begin());
				
				if (position == end())
				{
					for (size_type i = 0 ; i < n ; i++)
						push_back(val);
					return;
				}
				if (v_size + n > v_capacity)
				{
					pointer v_start_new = pointer();
					size_type v_size_new = v_size ;
					size_type v_capacity_new = v_capacity * 2 >= v_size + n ? v_capacity * 2 : v_size + n;
					v_start_new = v_alloc.allocate(v_capacity_new);
					for (size_t i = pos ; i < v_size; i++)
						v_alloc.construct(v_start_new + n + i, v_start[i]);
					for (size_t i = pos; i < n + pos; i++)
						v_alloc.construct(v_start_new + i, val);
					for (size_t i = 0; i < pos; i++)
						v_alloc.construct(v_start_new + i, v_start[i]);
					this->~vector();
					v_size = v_size_new;
					v_capacity = v_capacity_new;
					v_start = v_start_new;
				}
				else
				{
					for (size_t i = v_size + n - 1 ; i >= pos + n ; i--)
					{
						v_alloc.destroy(v_start + i);
						v_alloc.construct(v_start + i, v_start[i - n]);
					}
					for (size_type i = pos; i < n + pos; i++)
					{
						v_alloc.destroy(v_start + i);
						v_alloc.construct(v_start + i, val);
					}
				}
				v_size += n;
			};

			template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				if (position < begin() || position > end() || first > last)
					throw std::logic_error("vector");
				size_type pos = static_cast<size_type>(position - begin());
				size_type n = static_cast<size_type>(last - first);
				if (n + v_size > max_size())
					throw std::length_error("vector");			
				if (position == end())
				{
					for (size_type i = 0 ; i < n ; i++)
					{
						push_back(*first);
						first++;
					}
					return;
				}
				if (v_size + n > v_capacity)
				{
					pointer v_start_new = pointer();
					size_type v_size_new = v_size ;
					size_type v_capacity_new = v_capacity * 2 >= v_size + n ? v_capacity * 2 : v_size + n;
					v_start_new = v_alloc.allocate(v_capacity_new);
					for (size_t i = pos ; i < v_size; i++)
						v_alloc.construct(v_start_new + n + i, v_start[i]);
					for (size_t i = pos; i < n + pos; i++)
					{
						v_alloc.construct(v_start_new + i, *first);
						first++;
					}
					for (size_t i = 0; i < pos; i++)
						v_alloc.construct(v_start_new + i, v_start[i]);
					this->~vector();
					v_size = v_size_new;
					v_capacity = v_capacity_new;
					v_start = v_start_new;
				}
				else
				{
					for (size_t i = v_size + n - 1 ; i >= pos + n ; i--)
					{
						v_alloc.destroy(v_start + i);
						v_alloc.construct(v_start + i, v_start[i - n]);
					}
					for (size_type i = pos; i < n + pos; i++)
					{
						v_alloc.destroy(v_start + i);
						v_alloc.construct(v_start + i, *first);
						first++;
					}
				}
				v_size += n;
				
			};
			
			iterator erase (iterator position){
				size_type diff = static_cast<size_type>(position - begin());
				for (size_type i = diff; i < v_size - 1; i++){
					v_alloc.destroy(v_start + i);
					v_alloc.construct(v_start + i, *(v_start + i + 1));
				}
				v_size--;
				v_alloc.destroy(v_start + v_size - 1);
				return iterator(v_start + diff);
			};

			iterator erase (iterator first, iterator last){
				difference_type __start = first - begin();
				difference_type copy = end() - last;
				
				while (first != last){
					v_alloc.destroy(&(*first));
					first++;
				}
				size_type i = __start;
				while (last < end()){
					if (this->v_start + __start != t_nullptr)
						v_alloc.destroy(v_start + i);
					v_alloc.construct(v_start + i, *last);
					i++;
					last++;
				}
				for (size_type i = __start + copy; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				v_size = __start + copy;
				return (last == end()) ? end() : iterator(v_start + __start);
			};

			void swap (vector& x)
			{
				pointer         v_start_tmp = v_start;
				size_type       v_size_tmp = v_size ;
				size_type       v_capacity_tmp = v_capacity ;
				allocator_type  v_alloc_tmp = v_alloc;

				v_start = x.v_start;
				v_alloc = x.v_alloc;
				v_size = x.v_size;
				v_capacity_tmp = x.v_capacity;

				x.v_alloc = v_alloc_tmp;
				x.v_size = v_size_tmp;
				x.v_capacity = v_capacity_tmp;
				x.v_start = v_start_tmp ;
			};
			
            void clear()
            {
				if (static_cast<int>(v_size) > 0)
				{
					for (size_type i = 0; i < v_size; i++)
						v_alloc.destroy(v_start + i);
				}
				v_size = 0;
            };
			
/*------------------------------------------------------------------ Allocator ---------------------------------------------------------------------*/

			allocator_type get_allocator() const
			{
				return v_alloc;
			};
			

    };
/*--------------------------------------------------------- Non Member Function Overloads ----------------------------------------------------------*/

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal( lhs.begin(), lhs.end(), rhs.begin());
	};
	
	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		return !(lhs == rhs);
	};

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		return !(lhs > rhs);
	};
	
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		return rhs < lhs;
	};

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		return !(lhs < rhs);
	};

	template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	};
    
};

#endif
