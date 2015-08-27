
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#ifndef __bidimvec_h
#define __bidimvec_h

template <class T> bool
bd_from_string(T& t, const std::string& s)
{
  std::istringstream iss(s);
  return !(iss >> t).fail();
}


template <class T>
class bidimvec {

public:
	bidimvec(void);
	bidimvec(T v1, T v2);
	bidimvec(T &other);
	bidimvec(T *other);

	// pacchissimo...
	bidimvec(std::string);

	bidimvec<T> operator= (bidimvec<T>);
	bidimvec<T> operator+ (bidimvec<T>);
	bidimvec<T> operator- (bidimvec<T>);
	bidimvec<T> operator* (double);
	bidimvec<T> operator*= (double);
	bidimvec<T> operator/= (double);
	bidimvec<T> operator/ (double);
	bidimvec<T> operator- ();

	inline bool operator== (bidimvec<T>);

	double mod();
	void norm();
	bidimvec<T> orthonorm(void);
	bidimvec<T> rotate(double);

	double intp(bidimvec<T>, bidimvec<T>);

	T x(void);
	T y(void);


private:
	T myval1, myval2;
};

template <class T> double
bidimvec<T>::intp(bidimvec<T> v1, bidimvec<T> v2)
{ return sqrt(v1.x()*v2.x()+v1.y()*v2.y()); }

template <class T> bidimvec<T>
bidimvec<T>::operator*= (double rhs)
{ myval1*=rhs; myval2*=rhs; return *this; }

template <class T> bidimvec<T>
bidimvec<T>::operator/= (double rhs)
{ myval1/=rhs; myval2/=rhs; return *this; }

template <class T> bool
bidimvec<T>::operator== (bidimvec<T> rhs)
{ return ( (myval1==rhs.x()) && (myval2==rhs.y())); }

template <class T> double
bidimvec<T>::mod()
{ return sqrt(pow(myval1,2)+pow(myval2,2)); }

template <class T> void
bidimvec<T>::norm(void)
{ double modulus = mod(); myval1/=modulus; myval2/=modulus; }

template <class T> bidimvec<T> 
bidimvec<T>::operator+ (bidimvec<T> rhs)
{ return bidimvec<T>(myval1+rhs.x(), myval2+rhs.y()); }

template <class T> bidimvec<T> 
bidimvec<T>::operator- (bidimvec<T> rhs)
{ return bidimvec<T>(myval1-rhs.x(), myval2-rhs.y()); }

template <class T> bidimvec<T>
operator+ (double lhs, bidimvec<T> rhs)
{ return rhs+lhs; }

template <class T> bidimvec<T>
bidimvec<T>::operator/ (double rhs)
{ return (*this * (1/rhs)); }

template <class T> bidimvec<T> 
bidimvec<T>::operator* (double rhs)
{ return bidimvec<T>(myval1*rhs, myval2*rhs); }

template <class T> bidimvec<T>
operator* (double lhs, bidimvec<T> rhs)
{ return rhs*lhs; }

template <class T> bidimvec<T>
bidimvec<T>::operator- ()
{ return bidimvec<T>(-myval1, -myval2); }


template <class T> std::ostream &
operator<< (std::ostream &lhs, bidimvec<T> &myvec)
{
	lhs<<"("<<myvec.x()<<":"<<myvec.y()<<")";
	return lhs;
}


template <class T> bidimvec<T>
bidimvec<T>::operator= (bidimvec<T> rhs)
{
	myval1 = rhs.x();
	myval2 = rhs.y();
	return (*this);
}


template <class T>
bidimvec<T>::bidimvec(void) 
	: myval1(0), myval2(0) 
{}



template <class T>
bidimvec<T>::bidimvec(T v1, T v2) 
	: myval1(v1), myval2(v2) 
{}

template <class T>
bidimvec<T>::bidimvec(std::string str)
{
	int ref1 = str.find("(",0), ref2 = str.find(":",0), ref3 = str.find(")",0);
	bd_from_string<T>(myval1, str.substr(ref1+1, ref2-ref1-1) );
	bd_from_string<T>(myval2, str.substr(ref2+1, ref3-ref2-1) );
	//std::cout<<"[bidimvec<T>] std::str constructor: "<<*this<<std::endl;
}

template <class T>
bidimvec<T>::bidimvec(T &other) 
	: myval1(other.x()), myval2(other.y()) 
{}


template <class T>
bidimvec<T>::bidimvec(T *other) 
	: myval1(other->x()), myval2(other->y()) 
{}


template <class T> T
bidimvec<T>::x(void) 
{ return myval1; }


template <class T> T
bidimvec<T>::y(void) 
{ return myval2; }

// ------------------ paccottiglia generica ------------------
template <class T> double
interp_alpha(bidimvec<T> ip, bidimvec<T> ep)
{ return (ep.y()-ip.y())/(ep.x()-ip.x()); }

template <class T> double
interp_beta(bidimvec<T> ip, bidimvec<T> ep)
{ return (ip.y()-interp_alpha(ip,ep)*ip.x()); }

template <class T> bidimvec<T>
bidimvec<T>::orthonorm(void)
{ return bidimvec<T>( (myval2==0) ? 0 : 1, (myval2 == 0) ? myval1 : -myval1/myval2 ); }
//{ return bidimvec<T>( (myval2==0) ? 0 : -.5/myval2, (myval1 == 0) ? 0 : .5/myval1 ); }

template <class T> bidimvec<T>
bidimvec<T>::rotate(double theta)
{ return bidimvec<T>( myval1*cos(theta)-myval2*sin(theta), myval1*sin(theta)+myval2*cos(theta)); }

// -----------------------------------------------------------

#endif
