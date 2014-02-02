#include "farmpoint.h"

bool operator==(const Farmpoint& lhs, const Farmpoint& rhs) {
   return (lhs.col == rhs.col && lhs.row == rhs.row && lhs.farm == rhs.farm);
}
