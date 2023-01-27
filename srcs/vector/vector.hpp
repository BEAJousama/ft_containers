/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/27 18:37:40 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include "../utils/utils.hpp"
#include <memory>
#include <iostream>

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
				v_capacity = n;
				for (size_type i = 0; i < v_size; i++)
					v_alloc.construct(v_start_new + i, v_start[i]);
				this->~vector();
				v_start = v_start_new;
			};

			void constructable_resize (size_type n, value_type val = value_type())
            {
                if (static_cast<int>(n) < 0)
                    std::__throw_length_error("vector");
				if ( n > v_capacity )
				{
					pointer v_start_new = v_alloc.allocate(n);
					v_capacity = n;
					this->~vector();
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
            v_start(0), 
            v_size(0), 
            v_capacity(0), 
            v_alloc(alloc) 
            {
            }

            //fill
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
            v_size(n), 
            v_capacity(n), 
            v_alloc(alloc)
            {
                v_start = v_alloc.allocate(n);
                for(size_type i = 0; i < n; i++)
                    v_alloc.construct(v_start + i, val);
            }

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
            }

            //copy
            vector (const vector& x) :  v_size(0), v_capacity(0){
                *this = x;
            }

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
					v_capacity = diff;
					this->~vector();
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
			
			iterator erase (iterator position){
				size_type diff = static_cast<size_type>(position - begin());
				for (size_type i = diff; i < v_size - 1; i++){
					v_alloc.destroy(v_start + i);
					v_alloc.construct(v_start + i, *(v_start + i + 1));
				}
				v_size--;
				v_alloc.destroy(v_start + v_size - 1);
				return iterator(v_start + diff);
			}

			iterator erase (iterator first, iterator last){
				difference_type __start = first - begin();
				difference_type copy = end() - last;
				
				while (first != last){
					v_alloc.destroy(&(*first));
					first++;
				}
				size_type i = __start;
				while (last < end()){
					if (this->v_start + __start)
						v_alloc.destroy(v_start + i);
					v_alloc.construct(v_start + i, *last);
					i++;
					last++;
				}
				for (size_type i = __start + copy; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				v_size = __start + copy;
				return (last == end()) ? end() : iterator(v_start + __start);
			}
			
            void clear()
            {
				if (static_cast<int>(v_size) > 0)
				{
					for (size_type i = 0; i < v_size; i++)
						v_alloc.destroy(v_start + i);
				}
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
    
}

#endif
/*
namespace ft{



template < class T, class Allocator = std::allocator<T> > class vector{

template< typename L>class RandomAccessIterator
	{
	public:
		typedef	typename iterator_traits<L*>::value_type 	value_type;
		typedef	typename iterator_traits<L*>::pointer	pointer;
		typedef	typename iterator_traits<L*>::reference	reference;
		typedef	typename iterator_traits<L*>::difference_type	difference_type;
		typedef pointer iterator_type;
		//this is for std::functions
		typedef	std::random_access_iterator_tag iterator_category;

		//maybe protected???
	private:
		pointer _ptr;

	public:

		// CONSTRUCTORS
		RandomAccessIterator() : _ptr() {}

		RandomAccessIterator(pointer a) : _ptr(a) {}

		virtual ~RandomAccessIterator() {}

		RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type > & src) : _ptr(&(*src)) {}

		RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type > const & src) {
			_ptr = &(*src);
			return *this;
		}

		//OPERATORS
		RandomAccessIterator & operator++() {
			++_ptr;
			return *this;
		}

		RandomAccessIterator operator++(int) {
			RandomAccessIterator tmp(*this);
			++_ptr;
			return tmp;
		}

		RandomAccessIterator & operator--() {
			--_ptr;
			return *this;
		}

		RandomAccessIterator  operator--(int) {
			RandomAccessIterator tmp = *this;
			--_ptr;
			return tmp;
		}
		RandomAccessIterator operator+(const difference_type & a) const {
			return _ptr + a;
		}

		RandomAccessIterator operator-(const difference_type & a) const {
			return _ptr - a;
		}

		RandomAccessIterator & operator+=(const difference_type & a) {
			_ptr += a;
			return (*this);
		}

		RandomAccessIterator & operator-=(const difference_type & a) {
			_ptr -= a;
			return (*this);
		}

		pointer operator->() const {
			return _ptr;
		}

		reference operator*() const {
			return *_ptr;
		}

		reference operator[](difference_type n) const {
			return *(_ptr + n);
		}
	};

	public:
	template<typename A, typename B>
		friend bool operator==(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) == &(*rhs);


		}

		template<typename A, typename B>
		friend bool operator!=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) != &(*rhs);
		}

		template<typename A, typename B>
		friend bool operator>(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) > &(*rhs);
		}

		template<typename A, typename B>
		friend bool operator<(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) < &(*rhs);
		}

		template<typename A, typename B>
		friend bool operator<=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) <= &(*rhs);
		}


		template<typename A, typename B>
		friend bool operator>=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) >= &(*rhs);
		}

		template<typename A, typename B>
		friend typename vector::template RandomAccessIterator<A>::difference_type operator-(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) - &(*rhs);
		}

		template<typename A, typename B>
		friend typename vector::template RandomAccessIterator<A>::difference_type operator+(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) + &(*rhs);
		}

		template<typename L>
		friend vector::template RandomAccessIterator<L> operator +(const typename vector::template RandomAccessIterator<L>::difference_type & a, const vector::template RandomAccessIterator<L> & iter){
			return	(iter + a);
		}

		template<typename L>
		friend vector::template RandomAccessIterator<L> operator -(const typename vector::template RandomAccessIterator<L>::difference_type & a, const vector::template RandomAccessIterator<L> & iter){
			return	(iter - a);
		}
	

	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef RandomAccessIterator<value_type> iterator;
		typedef RandomAccessIterator<const value_type> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
	private:
		pointer		v_start;
		size_type 	v_size, v_capacity;
		allocator_type	v_alloc;
	public:	

		//CONSTRUCTORS
		
		//default		
		explicit vector (const allocator_type& alloc = allocator_type()) : v_start(0), v_size(0), v_capacity(0), v_alloc(alloc) {}

		//fill
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : v_size(n), v_capacity(n), v_alloc(alloc)
		{
			v_start = v_alloc.allocate(n);
			for(size_type i = 0; i < n; i++)
				v_alloc.construct(v_start + i, val);
		}

		//range
		template <class InputIterator>
        	 vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : v_alloc(alloc){
			if (first > last)
				throw std::length_error("vector");
			v_size = last - first;
			v_capacity = v_size;
			v_start = v_alloc.allocate(v_capacity);
			for (difference_type i = 0; i < static_cast<difference_type>(v_size); i++)
				v_alloc.construct(v_start + i, *(first + i));
		 }

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
		}

		//copy
		vector (const vector& x) :  v_size(0), v_capacity(0){
			*this = x;
		}
		
		//DESTRUCTOR
		~vector()
		{
			for (size_type i = 0; i < v_size; i++)
				v_alloc.destroy(v_start + i);
			if(v_capacity)
				v_alloc.deallocate(v_start, v_capacity);
		}

		

		//ITERATORS
		iterator begin(){
			return (iterator(v_start));
		}
		const_iterator begin() const{
			return (const_iterator(v_start));
		}
		iterator end(){
			return (iterator(v_start + v_size));
		}
		const_iterator end() const{
			return (const_iterator(v_start + v_size));
		}
		reverse_iterator rbegin(){
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator rend(){
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const{
			return (const_reverse_iterator(begin()));
		}
		
		//CAPACITY
		
		
		size_type size() const{
			return(v_size);
		}
		size_type maxv_size() const{
			return(v_alloc.maxv_size());
		}

		void reserve (size_type n){
			if (n < v_capacity)
				return;
			pointer newarr = v_alloc.allocate(n);
			try{
				for (size_type i = 0; i < v_size; i++)
					v_alloc.construct(newarr + i, *(v_start + i));
			} catch (std::exception &e){
				size_type i = 0;
				while (newarr + i != NULL && i < v_size){
					v_alloc.destroy(newarr + i);
					i++;
				}
				v_alloc.deallocate(newarr, n);
				throw;
			}
			for(size_type i = 0; i < v_size; i++)
				v_alloc.destroy(v_start + i);
			if(v_capacity)
				v_alloc.deallocate(v_start, v_capacity);
			v_capacity = n;
			v_start = newarr;
		}

		void resize (size_type n, value_type val = value_type()){
			if(n < v_size){
				for(size_type i = n; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				v_size = n;
			}
			else if (n > v_size){
				if (v_capacity < n)
					this->reserve(v_capacity * 2 > n ? v_capacity * 2 : n);
				for (size_type i = v_size; i < n; i++){
					v_alloc.construct(v_start + i, val);
					v_size++;
				}
			}
				
		}
		
		size_type capacity() const{
			return (v_capacity);
		}
		bool empty() const{
			return(v_size == 0);
		}
		
		
		//ELEMENT ACCESS
		
		
		reference operator[] (size_type n){
			return(*(v_start + n));
		}
		const_reference operator[] (size_type n) const{
			return(*(v_start + n));
		}
		
		reference at (size_type n){
			if(n > v_capacity)
				throw std::out_of_range("vector at out of range");
			return(*(v_start + n));
		}
		
		const_reference at (size_type n) const{
			if(n > v_capacity)
				throw std::out_of_range("vector at out of range");
			return(*(v_start + n));
		}
		
		reference front(){
			return(*v_start);
		}
		
		const_reference front() const{
			return(*v_start);
		}
		
		reference back(){
			return(*(v_start + v_size - 1));
		}
		
		const_reference back() const{
			return(*(v_start + v_size - 1));
		}

		//MODIFIERS
		template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
				if(first > last)
					throw std::logic_error("vector");
				difference_type count = last - first;
				clear();
				if (count > static_cast<difference_type>(capacity())){
					v_alloc.deallocate(v_start, v_capacity);
					v_start = v_alloc.allocate(count);
					v_capacity = count;
				}
				iterator pos = begin();
				while (first < last)
				{
					v_alloc.construct(&(*pos), *first);
					pos++;
					first++;
				}
				v_size = count;
			}

		void assign (size_type n, const value_type& val){
			clear();
			if (n > v_capacity){
				v_alloc.deallocate(v_start, v_capacity);
				v_start = v_alloc.allocate(n);
				v_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				v_alloc.construct(v_start + i, val);
			v_size = n;
		}
		
		void push_back (const value_type& val){
			if(v_size == v_capacity)
				reserve(v_capacity == 0 ? 1 : v_capacity * 2);
			v_alloc.construct(v_start + v_size, val);
			v_size++;
		}

		void pop_back(){
			v_alloc.destroy(v_start + v_size - 1);
			v_size--;
		}

		//single element
		iterator insert (iterator position, const value_type& val){
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			difference_type diff = position - begin();
			if (v_size == v_capacity){
				v_capacity = v_capacity * 2 + (v_capacity == 0);
				pointer v_start_new = v_alloc.allocate(v_capacity);
				std::uninitialized_copy(begin(), position, iterator(v_start_new));
				v_alloc.construct(v_start_new + start, val);
				std::uninitialized_copy(position, end(), iterator(v_start_new + start + 1));
				for (size_t i = 0; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				if(v_size)
					v_alloc.deallocate(v_start, v_size);
				v_size++;
				v_start = v_start_new;
			}
			else {
				for (size_type i = v_size; i > static_cast<size_type>(start); i--){
					v_alloc.destroy(v_start + i);
					v_alloc.construct(v_start + i, *(v_start + i - 1));
				}
				v_alloc.destroy(&(*position));
				v_alloc.construct(&(*position), val);
				v_size++;
			}
			return (begin() + start);
		}

		//fill
		void insert (iterator position, size_type n, const value_type& val){
			if (n == 0)
				return ;
			else if (maxv_size() - v_size < n)
				throw std::length_error("vector");
			difference_type start = position - begin();
			if (v_size + n > v_capacity){
				size_type new_cap = v_capacity * 2 >= v_size + n ? v_capacity * 2 : v_size + n;
				pointer v_start_new = v_alloc.allocate(new_cap);
				std::uninitialized_copy(begin(), position, iterator(v_start_new));
				for (size_type i = 0; i < n; i++)
					v_alloc.construct(v_start_new + start + i, val);
				std::uninitialized_copy(position, end(), iterator(v_start_new + start + n));
				for (size_type i = 0; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				v_alloc.deallocate(v_start, v_capacity);
				v_size += n;
				v_capacity = new_cap;
				v_start = v_start_new;
			}
			else {
				for (size_type i = v_size; i > static_cast<size_type>(start); i--) {
					v_alloc.destroy(v_start + i + n - 1);
					v_alloc.construct(v_start + i + n - 1, *(v_start + i - 1));
				}
				for (size_type i = 0; i < n; i++){
					v_alloc.destroy(v_start + i + start);
					v_alloc.construct(v_start + i + start, val);
				}
				v_size += n;
			}
		}

		//range
		template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){

				if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");
			size_type start = static_cast<size_type>(position - begin());
			size_type count = static_cast<size_type>(last - first);
			if (v_size + count > v_capacity) {
				size_type new_cap = v_capacity * 2 >= v_size + count ? v_capacity * 2 : v_size + count;
				pointer v_start_new = v_alloc.allocate(new_cap);
				std::uninitialized_copy(begin(), position, iterator(v_start_new));
				try {
					for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
						v_alloc.construct(v_start_new + start + i, *first);
				}
				catch (...){
					for (size_type i = 0; i < count + start; ++i)
						v_alloc.destroy(v_start_new + i);
					v_alloc.deallocate(v_start_new, new_cap);
					throw;
				}
				std::uninitialized_copy(position, end(), iterator(v_start_new + start + count));
				for (size_type i = 0; i < v_size; i++)
					v_alloc.destroy(v_start + i);
				v_alloc.deallocate(v_start, v_capacity);
				v_size += count;
				v_capacity = new_cap;
				v_start = v_start_new;
			}
			else {
				for (size_type i = v_size; i > static_cast<size_type>(start); i--) {
					v_alloc.destroy(v_start + i + count - 1);
					v_alloc.construct(v_start + i + count - 1, *(v_start + i - 1));
				}
				for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
					v_alloc.destroy(v_start + i + count);
					v_alloc.construct(v_start + start + i, *first);
				}
				v_size += count;
			}
		}
//				if (position < begin() || position > end() || first > last)
//					throw std::logic_error("vector");
//				difference_type start = position - begin();
//				difference_type count = last - first;
//				if (v_size + count > v_capacity){
//					size_type new_cap = v_capacity * 2 >= v_size + count ? v_capacity * 2 : v_size + count;
//					pointer v_start_new = v_alloc.allocate(new_cap);
//					std::uninitialized_copy(begin(), position, iterator(v_start_new));
//					for (size_type i = 0; i < count; i++, first++)
//						v_alloc.construct(v_start_new + start + i, *first);
//					std::uninitialized_copy(position, end(), iterator(v_start_new + start + count));
//					for (size_type i = 0; i < v_size; i++)
//						v_alloc.destroy(v_start + i);
//					v_alloc.deallocate(v_start, v_capacity);
//					v_size += count;
//					v_capacity = new_cap;
//					v_start = v_start_new;
//				}
//				else{
//					for (size_type i = v_size; i > start; i--){
//						v_alloc.destroy(v_start + i + count - 1);
//						v_alloc.construct(v_start + i + count - 1, *(v_start + i - 1));
//					}
//					for (size_type i = 0; i < count; i++, first++){
//						v_alloc.destroy(v_start + i + count);
//						v_alloc.construct(v_start + start + i, *first);
//					}
//					v_size += count;
//				}
//			}
//
		//single element
		iterator erase (iterator position){
			size_type d = static_cast<size_type>(std::distance(begin(), position));
			for (size_type i = d; i < v_size - 1; ++i){
				v_alloc.destroy(v_start + i);
				v_alloc.construct(v_start + i, *(v_start + i + 1));
			}
			v_size--;
			v_alloc.destroy(v_start + v_size - 1);
			return iterator(v_start + d);
		}

		//range
		iterator erase (iterator first, iterator last){
			difference_type start = std::distance(begin(), first);
			difference_type need_to_copy = std::distance(last, end());
			bool last_is_end = (last == end());
			while (first != last){
				v_alloc.destroy(&(*first));
				first++;
			}
			size_type i = start;
			while (last < end()){
				if (this->v_start + start)
					v_alloc.destroy(v_start + i);
				v_alloc.construct(v_start + i, *last);
				i++;
				last++;
			}
			for (size_type i = start + need_to_copy; i < v_size; i++)
				v_alloc.destroy(v_start + i);
			v_size = start + need_to_copy;
			return last_is_end ? end() : iterator(v_start + start);
		}
		
		void swap (vector& x){
			std::swap(v_start, x.v_start);
			std::swap(v_size, x.v_size);
			std::swap(v_capacity, x.v_capacity);
			std::swap(v_alloc, x.v_alloc);

		}

		void clear(){
			for (size_type i = 0; i < v_size; i++)
				v_alloc.destroy(v_start + i);
			v_size = 0;
		}

		//ALLOCATOR
		allocator_type getv_alloc() const{
			return(v_alloc);
		}
};

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs,
			                 const vector<T,Alloc>& rhs ){
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < rhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs,
		                const vector<T,Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs > rhs);
	}
	
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs,
		                const vector<T,Alloc>& rhs ){
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs < rhs);
	}

};


namespace std{
	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}
#endif

*/