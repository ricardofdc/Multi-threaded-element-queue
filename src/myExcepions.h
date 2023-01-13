/**
 * @file myExcepions.h
 * @author Ricardo Cardoso
 * @brief Custom exceptions for Queue class.
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MY_EXCEPTIONS_
#define MY_EXCEPTIONS_


#include <exception>


/**
 * @brief Exception thrown when Queue is initialized with negative size.
 * 
 */
struct QueueNegativeSizeException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Size of Queue must be positive.";
    }
};

/**
 * @brief Exception thrown when Push() is called for a full queue.
 * 
 */
struct QueueFullException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Queue is full.";
    }
};

/**
 * @brief Exception thrown when Push() is called with an objet from a different type.
 * 
 */
struct WrongTypeException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Types don't match.";
    }
};

#endif