#include <stdio.h>

int isGravitationalZone(int planet) {
    if (planet % 3 == 0) {
        return 1;
    }
    return 0;
}

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (planet > totalPlanets) {
        printf("\nResult: Mission Successful! The spacecraft completed the journey.\n");
        return;
    }

    if (fuel <= 0) {
        printf("\nResult: Mission Failed! Fuel exhausted before reaching planet %d.\n", planet);
        return;
    }

    int currentFuel = fuel - consumption;

    if (isGravitationalZone(planet)) {
        currentFuel += recharge;
        printf("[Log] Gravitational Assist at Planet %d (+%d fuel)\n", planet, recharge);
    }

    if (planet % 4 == 0) {
        currentFuel += solarBonus;
        printf("[Log] Solar Recharge at Planet %d (+%d fuel)\n", planet, solarBonus);
    }

    if (currentFuel <= 0) {
        printf("Planet %d: Fuel Remaining = %d\n", planet, currentFuel);
        printf("\nResult: Mission Failed! Stranded at Planet %d.\n", planet);
        return;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, currentFuel);

    calculateFuel(currentFuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int startFuel = 100;
    int consumption = 15;
    int recharge = 10;
    int solarBonus = 20;
    int totalPlanets = 10;

    printf("--- Spacecraft Fuel Simulation ---\n");
    printf("Starting Fuel: %d\n", startFuel);
    
    calculateFuel(startFuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}
