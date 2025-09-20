#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_INC   100
#define MAX_UNITS 20
#define MAX_STR   100

typedef struct {
    int id, sev, vic;
    char desc[MAX_STR], loc[MAX_STR];
    time_t ts;
} Incident;

typedef struct {
    char id[10];
    int busy;
    int incId;
} Unit;

Incident pq[MAX_INC];
double prio[MAX_INC];
int pqSize = 0;

double calcPriority(Incident *i) {
    return i->sev*5 + i->vic*2 + difftime(time(NULL), i->ts)*0.1;
}

void insertPQ(Incident x) {
    if (pqSize >= MAX_INC) {
        printf("Queue full.\n");
        return;
    }
    pq[pqSize] = x;
    prio[pqSize] = calcPriority(&x);
    pqSize++;
}

void updatePriorities() {
    for (int i = 0; i < pqSize; i++) {
        prio[i] = calcPriority(&pq[i]);
    }
}

Incident* extractMax() {
    if (pqSize == 0) return NULL;
    updatePriorities();
    int maxIdx = 0;
    for (int i = 1; i < pqSize; i++) {
        if (prio[i] > prio[maxIdx]) maxIdx = i;
    }
    static Incident top;
    top = pq[maxIdx];
    pq[maxIdx] = pq[--pqSize];
    prio[maxIdx] = prio[pqSize];
    return &top;
}

void reportIncident() {
    Incident i;
    i.id = pqSize + 1;
    printf("\n--- Report Incident ---\n");
    printf("Description: "); scanf(" %[^\n]", i.desc);
    printf("Location: ");    scanf(" %[^\n]", i.loc);
    printf("Severity (1-10): "); scanf("%d", &i.sev);
    printf("Victims: ");        scanf("%d", &i.vic);
    i.ts = time(NULL);
    insertPQ(i);
    printf("Incident ID-%d reported.\n", i.id);
}

void dispatch(Unit u[], int n) {
    int freeIdx = -1;
    for (int i = 0; i < n; i++)
        if (!u[i].busy) { freeIdx = i; break; }
    if (freeIdx == -1) { printf("No available units.\n"); return; }
    Incident *x = extractMax();
    if (!x) { printf("No incidents waiting.\n"); return; }
    u[freeIdx].busy = 1;
    u[freeIdx].incId = x->id;
    printf("Dispatching %s to Incident %d (%s)\n", u[freeIdx].id, x->id, x->desc);
}

void update(Unit u[], int n) {
    printf("\n--- Update Unit ---\nEnter Unit ID (e.g., AMB-1): ");
    char id[10]; scanf("%s", id);
    for (int i = 0; i < n; i++) {
        if (strcmp(u[i].id, id) == 0) {
            if (!u[i].busy) printf("%s is already available.\n", u[i].id);
            else { u[i].busy = 0; u[i].incId = -1; printf("%s marked AVAILABLE.\n", u[i].id); }
            return;
        }
    }
    printf("Unit %s not found.\n", id);
}

void status(Unit u[], int n) {
    updatePriorities();
    printf("\n--- System Status ---\n");
    printf("Incidents in queue: %d\n", pqSize);
    for (int i = 0; i < pqSize; i++) {
        printf("  ID-%d | Sev:%d | Vic:%d | Prio:%.2f | Desc:%s\n",
               pq[i].id, pq[i].sev, pq[i].vic, prio[i], pq[i].desc);
    }
    printf("Units:\n");
    for (int i = 0; i < n; i++) {
        printf("  %s - %s", u[i].id, u[i].busy ? "Dispatched" : "Available");
        if (u[i].busy) printf(" (Incident %d)", u[i].incId);
        printf("\n");
    }
}

int main() {
    int n;
    printf("--- Emergency Dispatch System ---\n");
    printf("Enter number of ambulance units (1-%d): ", MAX_UNITS);
    scanf("%d", &n);
    if (n < 1 || n > MAX_UNITS) { printf("Invalid number.\n"); return 0; }

    Unit u[MAX_UNITS];
    for (int i = 0; i < n; i++) {
        sprintf(u[i].id, "AMB-%d", i+1);
        u[i].busy = 0; u[i].incId = -1;
    }

    int ch;
    while (1) {
        printf("\n1.Report \n2.Dispatch \n3.Update \n4.Status \n5.Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) reportIncident();
        else if (ch == 2) dispatch(u, n);
        else if (ch == 3) update(u, n);
        else if (ch == 4) status(u, n);
        else if (ch == 5) break;
        else printf("Invalid choice.\n");
    }
    printf("Goodbye!\n");
    return 0;
}