#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

double getTime(double mean) {
    return -mean * log(1.0 * rand() / RAND_MAX);
}

double getTimeOfA (bool needWash) {
    return getTime(needWash ? 5 : 8);
}

double getTimeOfB (bool needWash) {
    return getTime(needWash ? 4.5 : 7);
}

double getNextCustomerArrivingTime () {
    return getTime(3);
}

int main() {
    srand(time(0));
    int numberOfCustomersWaiting = 0;
    int numberOfCustomersLeaving = 0;
    double currentTime = 0;
    int customerNumber = 0;
    double AWillWorkTill = 0, BWillWorkTill = 0;
    int ACustomer = 0, BCustomer = 0;
    while (numberOfCustomersLeaving < 30) {
        bool waitingPeople = 0;
        if (numberOfCustomersWaiting) {
            waitingPeople = 1;
            currentTime = std::max(currentTime, std::min(AWillWorkTill, BWillWorkTill));
        } else {
            currentTime += getNextCustomerArrivingTime();
        }

        if (!waitingPeople) ++customerNumber;
        printf("%3d %5.3f\n", customerNumber, currentTime);

        bool k = 0;
        if (AWillWorkTill < currentTime && BWillWorkTill < currentTime) {
            k = rand() % 2;
        } else if (AWillWorkTill > currentTime && BWillWorkTill > currentTime) {
            if (numberOfCustomersWaiting > 6) {
                ++numberOfCustomersLeaving;
                printf("   --- Leaving\n");
            } else {
                ++numberOfCustomersWaiting;
                printf("   --- Waiting\n");
            }
            continue;
        } else {
            k = BWillWorkTill < currentTime;
        }

        bool needWash = (rand() % 10) >= 6;

        if (k == 0) { // To A
            AWillWorkTill = currentTime + getTimeOfA(needWash);
            if ((++ACustomer) % 5 == 0) AWillWorkTill += 1;
            printf("   --- For A, will end at %5.3f\n", AWillWorkTill);
        } else { // To B
            BWillWorkTill = currentTime + getTimeOfB(needWash);
            if ((++BCustomer) % 5 == 0) BWillWorkTill += 1;
            printf("   --- For B, will end at %5.3f\n", BWillWorkTill);
        }

        numberOfCustomersWaiting -= waitingPeople;
        ++numberOfCustomersLeaving;
    }
    return 0;
}