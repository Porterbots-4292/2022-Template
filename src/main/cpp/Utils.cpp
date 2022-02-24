#include "Utils.h"

static uint64_t timeSinceEpoch(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}