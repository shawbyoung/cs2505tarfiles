 /** CS 2505 Spring 2022:  Intersection.c  
 *  Supplied framework for Intersecting Rectangles project.  Your task is to
 *  complete the supplied code to satisfy the posted specification for this
 *  assignment.  
 * 
 *  Student:   <Shaw Young>
 *  PID:       <shawy>
 */
#include "Intersection.h"

// DO NOT MODIFY THIS FILE IN ANY WAY!! //
 
#include <stdlib.h>       // generally useful

// Declarations for helper functions should go here:

// Returns true if B is outside of A (converse is implicit)
static bool checkOutside(int32_t  aLower, int32_t aUpper, int32_t bLower, int32_t bUpper);
// Returns true if the bounds of B are within the bounds of A
static bool checkInternal(int32_t  aLower, int32_t aUpper, int32_t bLower, int32_t bUpper);
// Returns true if variable great < greater < greater
static bool btw(int32_t great, int32_t greater, int32_t greatest);

/**  Determines whether two rectangles, A and B, intersect, computes the attributes
 *   of the intersection (if any), and returns true or false accordingly.
 *
 *   Pre:
 *         aSWx and aSWy specify the SW (lower, left) corner of A
 *         aHeight specifies the vertical dimension of A
 *         aWidth specifies the horizontal dimension of A
 *         bSWx and bSWy specify the SW (lower, left) corner of B
 *         bHeight specifies the vertical dimension of B
 *         bWidth specifies the horizontal dimension of B
 *         iSWx and iSWy point to variables the client will use to store the
 *              SW corner of the intersection, if it exists
 *         iHeight and iWidth point to variables the client will use to store
 *              the height and width of the intersection, if it exists
 *       
 *   Returns:
 *         true if A and B share at least one point; false otherwise
 */
bool Intersection(int32_t aSWx, int32_t aSWy, int32_t aHeight, int32_t aWidth,
                  int32_t bSWx, int32_t bSWy, int32_t bHeight, int32_t bWidth,
                  int32_t* const iSWx, int32_t* const iSWy, int32_t* const iHeight, int32_t* const iWidth) {

	//Set some lower and upper bounds
	int32_t bLowerX = bSWx;
	int32_t bUpperX = bSWx + bWidth;
	int32_t aLowerX = aSWx;
	int32_t aUpperX = aSWx + aWidth;
	int32_t bLowerY = bSWy;
	int32_t bUpperY = bSWy + bHeight;
	int32_t aLowerY = aSWy;
	int32_t aUpperY = aSWy + aHeight;
	int32_t zero = 0; 
	// If either the rectangles dont intersect, return zero
	if ( checkOutside( aLowerX, aUpperX, bLowerX, bLowerX ) ||
	checkOutside( aLowerY, aUpperY, bLowerY, bLowerY ) ) {

		*iSWx     = zero;
		*iSWy     = zero;
		*iHeight  = zero;
		*iWidth   = zero;
		return false;
	}

	//If Bx bounds are within Ax bounds
	if ( checkInternal(aLowerX, aUpperX, bLowerX, bUpperX)  ) {
		//If B is totally inside A, return B
		if ( checkInternal(aLowerY, aUpperY, bLowerY, bUpperY) ) { 
			*iSWx     = bSWx;
			*iSWy     = bSWy;
			*iHeight  = bHeight;
			*iWidth   = bWidth;
			return true;
		}
	}

	if ( checkInternal(bLowerX, bUpperX, aLowerX, aUpperX)  ) {
		//If A is totally inside B return A 
		if ( checkInternal(bLowerY, bUpperY, aLowerY, aUpperY) ) { 
			*iSWx     = aSWx;
			*iSWy     = aSWy;
			*iHeight  = aHeight;
			*iWidth   = aWidth;
			return true;
		}
	}

	*iSWx     = zero;
	*iSWy     = zero;
	*iHeight  = zero;
	*iWidth   = zero;
	return false;
}

// Returns true if B is outside of A (converse is implicit)
static bool checkOutside(int32_t  aLower, int32_t aUpper, int32_t bLower, int32_t bUpper) {
	return ( bLower > aUpper || bUpper < aLower );
}

// Returns true if the bounds of B are within the bounds of A
static bool checkInternal(int32_t  aLower, int32_t aUpper, int32_t bLower, int32_t bUpper) {
	return  btw(aLower, bLower, aUpper) && btw(aLower, bUpper, aUpper); 
}

// Returns true if variable great < greater < greater
static bool btw(int32_t great, int32_t greater, int32_t greatest) { 
	return great < greater && greater < greatest;
}
