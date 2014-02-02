#ifndef Farmpoint_h
#define Farmpoint_h

struct Farmpoint {
   int col;
   int row;
   int farm;
};

bool operator==(const Farmpoint& lhs, const Farmpoint& rhs);

// FarmpointP adds include parent data
struct FarmpointP {
   int col;
   int row;
   int farm;
   int pcol; // parent col
   int prow; // parent row
   int pfarm; // parent farm
};

#endif
