#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 10
#define MAX_STRING_LEN 100

const double SEVERITY_WEIGHT = 5.0;
const double VICTIMS_WEIGHT = 2.0;
const double AGING_PER_SECOND_WEIGHT = 0.1;

typedef enum {
    AVAILABLE,
    DISPATCHED
} UnitStatus;

typedef struct {
    int id;
    char description[MAX_STRING_LEN];
    char location[MAX_STRING_LEN];
    int severity;
    int victims;
    time_t timestamp;
} Incident;

typedef struct {
    char id[10];
    UnitStatus status;
    int assigned_incident_id;
    Incident* assigned_incident;
} Unit;

typedef struct {
    Incident** incidents;
    int size;
    int capacity;
} IncidentArray;

void clearInputBuffer();
int getValidatedInput(const char* prompt, int min, int max);
void printMenu();

IncidentArray* createQueue();
void addIncidentToArray(IncidentArray* q, Incident* incident);
Incident* extractMaxFromArray(IncidentArray* q);
void freeQueue(IncidentArray* q);
int compareIncidents(const void* a, const void* b);

double calculatePriority(const Incident* incident);
void handleReportIncident(IncidentArray* q, int* incident_counter);
void handleDispatch(IncidentArray* q, Unit units[], int num_units);
void handleUpdateUnitStatus(Unit units[], int num_units);
void handleShowStatus(IncidentArray* q, Unit units[], int num_units);

int main() {
    int incident_counter = 0;

    printf("--- Emergency Response Dispatch System (Simple Array Version) ---\n");
    int num_units = getValidatedInput("Enter the number of ambulance units to simulate: ", 1, 20);

    Unit* units = malloc(num_units * sizeof(Unit));
    for (int i = 0; i < num_units; i++) {
        sprintf(units[i].id, "AMB-%d", i + 1);
        units[i].status = AVAILABLE;
        units[i].assigned_incident_id = -1;
        units[i].assigned_incident = NULL;
    }

    IncidentArray* queue = createQueue();
    int choice = 0;

    while (choice != 5) {
        printMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                handleReportIncident(queue, &incident_counter);
                break;
            case 2:
                handleDispatch(queue, units, num_units);
                break;
            case 3:
                handleUpdateUnitStatus(units, num_units);
                break;
            case 4:
                handleShowStatus(queue, units, num_units);
                break;
            case 5:
                printf("\nExiting the system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
        if (choice != 5) {
             printf("\nPress Enter to continue...");
             getchar();
        }
    }

    freeQueue(queue);
    for (int i = 0; i < num_units; i++) {
        if (units[i].assigned_incident != NULL) {
            free(units[i].assigned_incident);
        }
    }
    free(units);

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidatedInput(const char* prompt, int min, int max) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < min || value > max) {
        clearInputBuffer();
        printf("Invalid input. Please enter a number between %d and %d: ", min, max);
    }
    clearInputBuffer();
    return value;
}

void printMenu() {
    printf("\n========================================\n");
    printf("                  MENU                  \n");
    printf("========================================\n");
    printf("1. Report New Incident\n");
    printf("2. Dispatch Next Unit\n");
    printf("3. Update Unit Status (Mark as Available)\n");
    printf("4. Show System Status\n");
    printf("5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-5): ");
}

IncidentArray* createQueue() {
    IncidentArray* q = (IncidentArray*)malloc(sizeof(IncidentArray));
    q->incidents = (Incident**)malloc(INITIAL_CAPACITY * sizeof(Incident*));
    q->size = 0;
    q->capacity = INITIAL_CAPACITY;
    return q;
}

void addIncidentToArray(IncidentArray* q, Incident* incident) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->incidents = (Incident**)realloc(q->incidents, q->capacity * sizeof(Incident*));
    }
    q->incidents[q->size] = incident;
    q->size++;
}

Incident* extractMaxFromArray(IncidentArray* q) {
    if (q->size == 0) {
        return NULL;
    }

    double max_priority = -1.0;
    int max_index = -1;

    for (int i = 0; i < q->size; i++) {
        double current_priority = calculatePriority(q->incidents[i]);
        if (current_priority > max_priority) {
            max_priority = current_priority;
            max_index = i;
        }
    }

    Incident* incident_to_dispatch = q->incidents[max_index];
    q->incidents[max_index] = q->incidents[q->size - 1];
    q->size--;

    return incident_to_dispatch;
}

void freeQueue(IncidentArray* q) {
    for (int i = 0; i < q->size; i++) {
        free(q->incidents[i]);
    }
    free(q->incidents);
    free(q);
}

int compareIncidents(const void* a, const void* b) {
    Incident* incidentA = *(Incident**)a;
    Incident* incidentB = *(Incident**)b;
    double priorityA = calculatePriority(incidentA);
    double priorityB = calculatePriority(incidentB);
    if (priorityA < priorityB) return 1;
    if (priorityA > priorityB) return -1;
    return 0;
}

double calculatePriority(const Incident* incident) {
    double time_elapsed = difftime(time(NULL), incident->timestamp);
    return (incident->severity * SEVERITY_WEIGHT) +
           (incident->victims * VICTIMS_WEIGHT) +
           (time_elapsed * AGING_PER_SECOND_WEIGHT);
}

void handleReportIncident(IncidentArray* q, int* incident_counter) {
    Incident* new_incident = (Incident*)malloc(sizeof(Incident));
    (*incident_counter)++;
    new_incident->id = *incident_counter;

    printf("\n--- Report New Incident ---\n");
    printf("Enter description: ");
    fgets(new_incident->description, MAX_STRING_LEN, stdin);
    new_incident->description[strcspn(new_incident->description, "\n")] = 0;

    printf("Enter location: ");
    fgets(new_incident->location, MAX_STRING_LEN, stdin);
    new_incident->location[strcspn(new_incident->location, "\n")] = 0;

    new_incident->severity = getValidatedInput("Enter severity (1-10): ", 1, 10);
    new_incident->victims = getValidatedInput("Enter number of victims: ", 0, 1000);
    new_incident->timestamp = time(NULL);

    addIncidentToArray(q, new_incident);
    printf("\nIncident ID-%d successfully reported and added to queue.\n", new_incident->id);
}

void handleDispatch(IncidentArray* q, Unit units[], int num_units) {
    if (q->size == 0) {
        printf("\nNo incidents in the queue to dispatch.\n");
        return;
    }

    int available_unit_index = -1;
    for (int i = 0; i < num_units; i++) {
        if (units[i].status == AVAILABLE) {
            available_unit_index = i;
            break;
        }
    }

    if (available_unit_index == -1) {
        printf("\nNo units available for dispatch.\n");
        return;
    }

    Incident* incident_to_dispatch = extractMaxFromArray(q);
    
    units[available_unit_index].status = DISPATCHED;
    units[available_unit_index].assigned_incident_id = incident_to_dispatch->id;
    units[available_unit_index].assigned_incident = incident_to_dispatch;

    printf("\nDISPATCHING: %s to Incident ID-%d\n", units[available_unit_index].id, incident_to_dispatch->id);
    printf("   Details: '%s'\n", incident_to_dispatch->description);
}

void handleUpdateUnitStatus(Unit units[], int num_units) {
    printf("\n--- Update Unit Status ---\n");
    printf("Dispatched units:\n");
    int dispatched_count = 0;
    for(int i = 0; i < num_units; i++) {
        if(units[i].status == DISPATCHED) {
            printf("  - %s (to Incident ID-%d)\n", units[i].id, units[i].assigned_incident_id);
            dispatched_count++;
        }
    }

    if (dispatched_count == 0) {
        printf("No units are currently dispatched.\n");
        return;
    }
    
    char unit_id_str[10];
    printf("Enter the ID of the unit that is now available (e.g., AMB-1): ");
    fgets(unit_id_str, 10, stdin);
    unit_id_str[strcspn(unit_id_str, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < num_units; i++) {
        if (strcasecmp(units[i].id, unit_id_str) == 0) {
            if (units[i].status == AVAILABLE) {
                printf("\nUnit %s is already available.\n", units[i].id);
            } else {
                units[i].status = AVAILABLE;
                if (units[i].assigned_incident != NULL) {
                    free(units[i].assigned_incident);
                    units[i].assigned_incident = NULL;
                }
                units[i].assigned_incident_id = -1;
                printf("\nUnit %s is now AVAILABLE.\n", units[i].id);
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nError: Unit with ID '%s' not found.\n", unit_id_str);
    }
}

void handleShowStatus(IncidentArray* q, Unit units[], int num_units) {
    printf("\n------------------------------------------\n");
    printf("              SYSTEM STATUS\n");
    printf("------------------------------------------\n");

    printf("\nINCIDENT QUEUE (Sorted by Priority for display):\n");
    if (q->size == 0) {
        printf("  [Queue is empty]\n");
    } else {
        Incident** sorted_copy = malloc(q->size * sizeof(Incident*));
        memcpy(sorted_copy, q->incidents, q->size * sizeof(Incident*));
        
        qsort(sorted_copy, q->size, sizeof(Incident*), compareIncidents);

        for(int i = 0; i < q->size; i++) {
            Incident* incident = sorted_copy[i];
            printf("  - ID-%d | Prio: %.2f | Desc: '%s'\n", incident->id, calculatePriority(incident), incident->description);
        }
        free(sorted_copy);
    }

    printf("\nUNIT STATUS:\n");
    for (int i = 0; i < num_units; i++) {
        printf("  - Unit %-7s | Status: %s", units[i].id, units[i].status == AVAILABLE ? "Available" : "Dispatched");
        if (units[i].status == DISPATCHED) {
            printf(" to Incident ID-%d ('%s')\n", units[i].assigned_incident_id, units[i].assigned_incident->description);
        } else {
            printf("\n");
        }
    }
    printf("------------------------------------------\n");
}