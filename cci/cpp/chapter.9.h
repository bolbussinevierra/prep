//
// 9.1
//
int ways2(int n) {
    if (n < 0) {
        return 0;
    } 
    // This took a while to get why its true. Can also list ALL the base cases
    // instead of this. Read this is having been the "steps remaining equalled
    // the number of steps that were to be taken" hence 0
    else if (n == 0) {
        return 1; 
    }
    else {
        return ways2(n - 1) + ways2(n - 2) + ways2(n - 3);
    }
}
