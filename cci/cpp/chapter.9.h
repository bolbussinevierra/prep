#include <iostream>
#include <vector>
#include <map>

using namespace std;

//
// 9.1
//
int ways(int n) {
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
        return ways(n - 1) + ways(n - 2) + ways(n - 3);
    }
}

//
// 9.2
//
int compute_paths(int width, int height) {
    // BTB - ** IMPORTANT **
    // [0][0] is not involved in the math which is why we allocate width+1
    // height+1
    vector<vector<int>> result(width+1, vector<int>(height+1));

    // initialize [1,0] to [width,0] = 1
    for (int x = 1; x <= width; ++x) {
        result[x][0] = 1;
    }
    // initialize [0, 1] to [0, height,] to 1
    for (int y = 1; y <= height; ++y) {
        result[0][y] = 1;
    }

    // calculate all other values from adjacent values
    for (int x = 1; x <= width; ++x) {
        for (int y = 1; y <= height; ++y) {
            result[x][y] = result[x][y-1] + result[x-1][y];
        }
    }
    return result[width][height];
}

//
// 9.2 follow up
//
bool operator<(POINT const& a, POINT const& b){
    return (a.x < b.x) && (a.y < b.y);
}

bool CanMoveTo(int x, int y) {
    if ((x == 2) && (y <= 2)) { return false; } else { return true; }
}


bool FindPathTo(int ex, int ey, vector<POINT>& path, map<POINT, bool>& cache) {
    POINT p = {ex, ey};
    bool success = false;

    std::map<POINT,bool>::iterator it = cache.find(p);
    if (cache.end() != it)
    {
        success = it->second;
    }
    else if ((ex == 0) && (ey == 0)) { // we have confirmed all the way back!
        success = true;
    }
    else {
        if ((ex >= 1) && CanMoveTo(ex-1, ey)) {
            success = FindPathTo(ex-1, ey, path, cache);
        }
        if (!success && (ey >= 1) && CanMoveTo(ex, ey-1)) {
            success = FindPathTo(ex, ey-1, path, cache);
        }
    }

    if (success) {
        printf("Next = (%d, %d)\n", p.x, p.y);
        path.push_back(p); // we have confirmed that this is not a dead end
    }
    cache.insert(pair<POINT, bool>(p, success));
    return success;
}

bool FindPathTo(int ex, int ey) {
    vector<POINT> path;
    map<POINT, bool> cache;
    return FindPathTo(ex, ey, path, cache);
}

//
// 9.3
//
void Subsets(vector<int> items, int start, vector<vector<int>>& sets) {
    if(start == items.size()){
        vector<int> empty;
        sets.push_back(empty);
    } else {
        vector<vector<int>> otherSets;
        Subsets(items, start+1, otherSets);
        for (size_t i = 0; i < otherSets.size(); ++i) {
            sets.push_back(otherSets[i]);       // add each previous set
            vector<int> cloneSet(otherSets[i]); // clone the previous et
            cloneSet.push_back(items[start]);   // add the new item
            sets.push_back(cloneSet);           // add the cloned and expanded set to list
        }
    }
}

void Subsets(int arr[], int length) {
    vector<int> items(arr, arr+length);
    vector<vector<int>> sets;
    Subsets(items, 0, sets);
    for (size_t i = 0; i < sets.size(); ++i) {
        vector<int> set = sets[i];
        if (set.empty()) {
            printf("<empty> ");
        }
        else {
            for (size_t j = 0; j < set.size(); ++j) {
                printf("%d ", set[j]);
            }
        }
        printf("\n");
    }
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}
