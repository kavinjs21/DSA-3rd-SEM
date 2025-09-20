#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_INCIDENTS 50
#define MAX_UNITS 10
#define MAX_STRING 100

typedef struct {
    int id;
    char description[MAX_STRING];
    int severity;
    int victims;
    time_t timestamp;
    int active;  // 1 = waiting, 0 = dispatched/closed
} Incident;

typedef struct {
    char id[10];
    int available;   // 1 = available, 0 = busy
    int incident_id; // which incident is assigned
} Unit;

Incident incidents[MAX_INCIDENTS];
Unit units[MAX_UNITS];
int incident_count = 0;
int num_units = 0;

double priority(Incident *i) {
    double time_elapsed = difftime(time(NULL), i->timestamp);
    return (i->severity * 5) + (i->victims * 2) + (time_elapsed * 0.1);
}

void reportIncident() {
    if (incident_count >= MAX_INCIDENTS) {
        printf("Incident list full!\n");
        return;
    }
    Incident *i = &incidents[incident_count];
    i->id = incident_count + 1;
    printf("Enter description: ");
    fgets(i->description, MAX_STRING, stdin);
    i->description[strcspn(i->description, "\n")] = 0;
    printf("Enter severity (1-10): ");
    scanf("%d", &i->severity);
    printf("Enter victims: ");
    scanf("%d", &i->victims);
    getchar();
    i->timestamp = time(NULL);
    i->active = 1;
    incident_count++;
    printf("Incident ID-%d reported.\n", i->id);
}

void dispatch() {
    int best = -1;
    double best_score = -1;
    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].active) {
            double score = priority(&incidents[i]);
            if (score > best_score) {
                best_score = score;
                best = i;
            }
        }
    }
    if (best == -1) {
        printf("No pending incidents.\n");
        return;
    }
    int free_unit = -1;
    for (int u = 0; u < num_units; u++) {
        if (units[u].available) {
            free_unit = u;
            break;
        }
    }
    if (free_unit == -1) {
        printf("No available units.\n");
        return;
    }
    units[free_unit].available = 0;
    units[free_unit].incident_id = incidents[best].id;
    incidents[best].active = 0;
    printf("Dispatched %s to Incident ID-%d (%s)\n",
           units[free_unit].id, incidents[best].id, incidents[best].description);
}

void updateUnit() {
    printf("\nUnits currently busy:\n");
    int found = 0;
    for (int u = 0; u < num_units; u++) {
        if (!units[u].available) {
            printf(" - %s (Incident-%d)\n", units[u].id, units[u].incident_id);
            found = 1;
        }
    }
    if (!found) {
        printf("No units are currently dispatched.\n");
        return;
    }
    char unit_id[10];
    printf("Enter unit ID to mark available: ");
    fgets(unit_id, 10, stdin);
    unit_id[strcspn(unit_id, "\n")] = 0;

    for (int u = 0; u < num_units; u++) {
        if (strcmp(units[u].id, unit_id) == 0) {
            units[u].available = 1;
            units[u].incident_id = -1;
            printf("%s is now available.\n", units[u].id);
            return;
        }
    }
    printf("Unit not found.\n");
}

void showStatus() {
    printf("\n--- INCIDENTS ---\n");
    int any = 0;
    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].active) {
            any = 1;
            printf("ID-%d | %s | Severity:%d | Victims:%d | Priority: %.2f\n",
                   incidents[i].id, incidents[i].description,
                   incidents[i].severity, incidents[i].victims,
                   priority(&incidents[i]));
        }
    }
    if (!any) printf("[No active incidents]\n");

    printf("\n--- UNITS ---\n");
    for (int u = 0; u < num_units; u++) {
        if (units[u].available)
            printf("%s | Available\n", units[u].id);
        else
            printf("%s | Busy (Incident-%d)\n", units[u].id, units[u].incident_id);
    }
}

int main() {
    printf("Enter number of units (max %d): ", MAX_UNITS);
    scanf("%d", &num_units);
    getchar();
    for (int i = 0; i < num_units; i++) {
        sprintf(units[i].id, "AMB-%d", i + 1);
        units[i].available = 1;
        units[i].incident_id = -1;
    }

    int choice;
    do {
        printf("\n1. Report Incident\n2. Dispatch\n3. Update Unit Status\n4. Show Status\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1) reportIncident();
        else if (choice == 2) dispatch();
        else if (choice == 3) updateUnit();
        else if (choice == 4) showStatus();
    } while (choice != 5);

    return 0;
}
