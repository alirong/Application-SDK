/*******************************************************************************
Project       : Shared Pointer which is more or less compatible with 
                boost::shared_ptr
Version       : 1.0
Author        : Martin Christen
License       : MIT License
Copyright     : (c) 2007-2010 by Martin Christen. All Rights Reserved

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H

#include <string>
#include <cassert>


   template< class T > class shared_ptr;

   template< class T >
   class shared_ptr 
   {
   public:
      shared_ptr( T* ptr = 0 ) : _ref( new int( 1 ) ), _ptr( ptr ) {}
      shared_ptr( const shared_ptr& sp )
      {
         Copy(sp);
      }
      template< class X > friend class shared_ptr;
      template< class X >
      shared_ptr( const shared_ptr< X >& sp ) 
      {
         ++*sp._ref;
         _ptr = sp._ptr;
         _ref = sp._ref;
      }
      
      ~shared_ptr() 
      {
         Decrease();
      }

   public:
      shared_ptr& operator=( const shared_ptr& sp ) 
      {
         if ( this != &sp ) 
         {
	         Decrease();
	         Copy(sp);
         }
         return *this;
      }
      
      T* operator->() 
      {
         return _ptr;
      }
      
      T* get()
      {
         return _ptr;
      }
      
      const T* operator->() const 
      {
         return _ptr;
      }

      operator bool() const 
      { 
         return _ptr != 0; 
      }

   private:
      void Copy( const shared_ptr& sp ) 
      {
         ++*sp._ref;
         _ref = sp._ref;
         _ptr = sp._ptr;
      }
      
      void Decrease() 
      {
         --*_ref;
         if ( 0 == *_ref ) 
         {
	         delete _ref;
	         delete _ptr; 
	         _ptr = 0;
         }
      }

   private:
      int* _ref;
      T* _ptr;
   };

#endif