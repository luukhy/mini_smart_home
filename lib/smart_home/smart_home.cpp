#include "smart_home.h"

bool fInRange(float val, float min, float max) {
    return (val >= min && val <= max);
}