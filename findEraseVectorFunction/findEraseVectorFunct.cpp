#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::vector<int> nums = {4,5,6,7,9};

    auto it = std::find(nums.begin(), nums.end(), 5);

    int index = std::distance(nums.begin(), it);

    std::cout<<index;

    return 0;
}