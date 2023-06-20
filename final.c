#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_LEN 100
#define aa 256
#define VERT 10  // defining the number of vertices (currently)
#define INF 9999 // INF as in INFINITY

struct hotel
{
    char name[50];
    float rating;
    char addr[20];
    int price;
};

// A user-defined data type called PLACE to store the city names in singly linked list
struct place
{
    int numb;
    char name[20];
    struct place *next;
};
typedef struct place *PLACENODE;

struct hotel_tree_form
{
    struct hotel_tree_form *l;
    struct hotel_tree_form *r;
    float rat;
    char name[100];
    char add[100];
    int price;
};
typedef struct hotel_tree_form *HOTELNODEE;

struct cityname
{
    char name[20];
};

struct flight_details /// airway structure
{
    char name[30];
    int price;
    int seats;
    char des[30];
    int date[11];
    int month[6];
};
typedef struct flight_details *FLIGHTNODE;

struct roam /// structure to roam
{
    char place[30];
    int km;
    char loc[30];
};

struct stacking_structure
{
    char data[MAX_LEN];
    struct stacking_structure * next;
};
typedef struct stacking_structure * StackNode;

// global declarations
int q[100], front = -1, rear = -1, vis[50], air[VERT][VERT];
int eightroadway[9][9], thirtyroadway[31][31], eightFWroad[9][9], thirtyFWroad[31][31];
struct flight_details flights[100];
struct cityname cityy[11], eightcities[9], thirtycities[31];
struct roam roam[100];
struct hotel hot_details[100];
PLACENODE place_head = NULL;

void read_allhotels(struct hotel A[100]); // to read hotel names from a file "hotel.txt" into a struct array hot_details
void near_hotels(char d[]);               // to find hotels at given destination

HOTELNODEE create(char namee[], float data, char addr[], int roka); // function call for sorting rating less to max
void insert(HOTELNODEE root, char name[], float data, char addr[], int roka);
void inorder(HOTELNODEE root);

void places_roam(char d[], struct roam roam[]);

void read_airways(struct flight_details flights[]);
void airways(struct flight_details flights[], char d[]);
void selection_sort(int n, struct flight_details a[], char d[]); // function call for sorting rating less to max
void dijikstra(int a[10][10], int n, int s, int q);      // find shortest airway distance between city

void read_arr_city_names(struct cityname A[], int n);
void displaycityarr(struct cityname cityy[], int n); // to display array form (later done) all places available in our system

void history(StackNode top);
StackNode push(StackNode top, char data[]);
StackNode pop(StackNode top);

void hotel_rating(char d[], struct hotel z[]);

int getmonth();
int getdate(int month);
void monthdate_availableflight(struct flight_details flights[], int month, int date, char d[]);

void read_road_from_file(int n, int arr[][n + 1]);
void print_2d_array(int n, int a[][n + 1]);
void floydWarshall(int n, int arr[][n + 1]);
int distcheck(char p[], char q[], int n, struct cityname cit[], int A[][n + 1]);


// BFS can be used to find a single source shortest path in an unweighted graph because, in BFS, we reach a vertex with a minimum number of edges from a source vertex.
void bfs(int s, int n, int arr[][n + 1], struct cityname cit[]);
void add(int item); // enqueue
int delete();       // dequeue

void roaddijkstra(int ver, int graph[ver+1][ver+1], int src);
void printSolution( int n, int dist[n]);

int distcheck(char p[], char q[], int n, struct cityname cit[], int A[][n + 1])
{
    int i, source_city, dest_city;
    for (i = 1; i <= n; i++)
    {
        if (strcasecmp(p, cit[i].name) == 0)
        {
            source_city = i;
            break;
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (strcasecmp(q, cit[i].name) == 0)
        {
            dest_city = i;
            break;
        }
    }
    return (A[source_city][dest_city]);
}

int main()
{
    printf("                                       WELCOME\n");
    printf("                          Namaste :)                   HOLA!!!!\n\n\n");
    char s[20], d[20];
    float r[30], o[30];
    int n = 100, i, j, k, choice = 0, source_city = 0, dest_city = 0, flag = 1, month, date;
    HOTELNODEE hotel_root = NULL;

    // read the flight structure array
    read_airways(flights);

    // Array-"roadway" stores the distance between connected cities
    // The function is just to separate the input form the code
    read_road_from_file(8, eightroadway);
    read_road_from_file(30, thirtyroadway);

    // to read hotel names from a file "hotel.txt" into a struct array hot_details
    read_allhotels(hot_details);

    // read the cities in "city10.txt", "city8.txt", "city27.txt"
    read_arr_city_names(cityy, 10);
    read_arr_city_names(eightcities, 8);
    read_arr_city_names(thirtycities, 30);

    // To find the shortest distance between all the nodes, we are using Floyd-Warshall Algorithm.
    // It finds the shortest distance between all the nodes
    floydWarshall(8, eightFWroad);
    floydWarshall(30, thirtyFWroad);

    printf("\nThese are our available destinations!!!!\n");
    displaycityarr(cityy, 10);
    /* _________________________________________________________________________________****/

    flag = 1;
    while (flag != 0)
    {
        printf("\n\nWhere do you wanna start your journey from?\n");
        scanf("%s", s);

        for (i = 0, flag = 1; i <= VERT; i++)
        {
            if (strcasecmp(s, cityy[i].name) == 0)
            {
                source_city = i;
                flag = 0;
                break;
            }
        }

        if (flag != 0)
            printf("\n\nIncorrect source!!!  Please enter again\n\n");
    }

    // "testing when running" "while loop"
    flag = 1;
    while (flag != 0)
    {
        printf("\nwhat's your destination?\n");
        scanf("%s", d);
        for (i = 1, flag = 1; i <= VERT; i++)
        {
            if (strcasecmp(d, cityy[i].name) == 0)
            {
                dest_city = i;
                flag = 0;
                break;
            }
        }

        if (flag != 0)
            printf("\n\nIncorrect destination!!!  Please enter again.\n\n");

        if (strcmp(d, s) == 0)
        {
            printf("\nSource and destination are SAME!!! Please enter different destination.\n\n");
            flag = 1;
        }
    }

    printf("\n%d = %s : %d = %s", source_city, cityy[source_city].name, dest_city, cityy[dest_city].name);

    printf("\n\nWhat do you want to know?\n");
    printf("1. Show the available cities\n");
    printf("2. would you like to switch source and destination\n");
    printf("3: Look what you Searched for (Search history)\n");

    printf("4. Best Hotels near %s\n", d);
    printf("5. High Rated Hotels on our page\n");
    printf("6. Attraction near/around %s\n", d);
    printf("7. Wanna travel by PLANE? see distance through Airway travel\n");
    printf("8. Checkout Flights Flying to %s\n", d);
    printf("9. Check flight availability on particular date (2023)");

    if (source_city == 9 || source_city == 6 || dest_city == 9 || dest_city == 6)
    {
        printf("\nNo roadway-syatem to Maldives/Dubai :)\n");
    }

    else
    {
        printf("\nAre you a car/bike person? then-\n");
        printf("10. See the distance between source and destination \n");
        printf("11. need a plan to cover all the cities?\n");

        printf("\nBut, you are a looooooooooooong drive person? and want to travel from north to south?\n");
        printf("12. Show a large roadway plan from north to south (starting from source)\n");

        printf("13. show distance of all the cities from source point\n");

        printf("50: floydd warshall 8 roads\n");
        printf("51. OG eight roads\n");
        printf("52. floydd warshall 30 roads\n");
        printf("53. OG 30 roads\n");
    }

    printf("\nChoose what you wish for :) \nEnter choice >>>");

    while (choice != 100 || choice)
    {
        /***********HISTORY file*************/
        FILE * file;
        file = fopen("search_history.txt", "a");
        fprintf(file, "%s  %s\n", cityy[source_city].name, cityy[dest_city].name);
        fclose(file);
        StackNode top = NULL;
        char buffer[MAX_LEN];

        file = fopen("search_history.txt", "r");

        if (file == NULL)
        {
            printf("Error: Could not open file\n");
            return 1;
        }

        while (fgets(buffer, MAX_LEN, file) != NULL)
        {
            int len = strlen(buffer);
            if (buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }
            top = push(top, buffer);
        }

        fclose(file);
        /*************HISTORY FILE*********************************************************************/
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("\n\nWhat do you want to know?\n");
            printf("1. Show the available cities\n");
            printf("2. would you like to switch source and destination\n");
            printf("3: Look what you Searched for (Search history)\n");

            printf("4. Best Hotels near %s\n", d);
            printf("5. High Rated Hotels on our page\n");
            printf("6. Attraction near/around %s\n", d);
            printf("7. Wanna travel by PLANE? see distance through Airway travel\n");
            printf("8. Checkout Flights Flying to %s\n", d);
            printf("9. Check flight availability on particular date (2023)");

            if (source_city == 9 || source_city == 6 || dest_city == 9 || dest_city == 6)
            {
                printf("\nNo roadway-syatem to Maldives/Dubai :)\n");
            }

            else
            {
                printf("\nAre you a car/bike person? then-\n");
                printf("10. See the distance between source and destination \n");
                printf("11. need a plan to cover all the cities?\n");

                printf("\nBut, you are a looooooooooooong drive person? and want to travel from north to south?\n");
                printf("12. Show a large roadway plan from north to south (starting from source)\n");

                printf("13. show distance of all the cities from source point\n");

                printf("50: floydd warshall 8 roads\n");
                printf("51. OG eight roads\n");
                printf("52. floydd warshall 30 roads\n");
                printf("53. OG 30 roads\n");
            }
            break;

        case 1:
            printf("\nAvailable destinations:");
            displaycityarr(cityy, 10);
            break;

        case 2:
            flag = 1;
            while (flag != 0)
            {
                printf("\n\nWhere do you wanna start your journey from?\n");
                scanf("%s", s);

                for (i = 0, flag = 1; i <= VERT; i++)
                {
                    if (strcasecmp(s, cityy[i].name) == 0)
                    {
                        source_city = i;
                        flag = 0;
                        break;
                    }
                }

                if (flag != 0)
                    printf("\n\nIncorrect source!!!  Please enter again\n\n");
            }

            flag = 1;
            while (flag != 0)
            {
                printf("\nwhat's your destination?\n");
                scanf("%s", d);
                for (i = 1, flag = 1; i <= VERT; i++)
                {
                    if (strcasecmp(d, cityy[i].name) == 0)
                    {
                        dest_city = i;
                        flag = 0;
                        break;
                    }
                }

                if (flag != 0)
                    printf("\n\nIncorrect destination!!!  Please enter again.\n\n");

                if (strcmp(d, s) == 0)
                {
                    printf("\nSource and destination are SAME!!! Please enter different destination.\n\n");
                    flag = 1;
                }
            }
            break;

        case 3:
            history(top);
            break;

        case 4:
            printf("\n\nBTW...Nice choice of city\n");
            near_hotels(d);
            break;

        case 5:
            printf("\nHotels from highest to lowest rating\n");
            hotel_root = create(hot_details[1].name, hot_details[1].rating, hot_details[1].addr, hot_details[1].price); // function call for sorting rating less to max
            for (int l = 2; l <= 30; l++)
                insert(hotel_root, hot_details[l].name, hot_details[l].rating, hot_details[l].addr, hot_details[l].price);

            inorder(hotel_root);
            break;

        case 6:
            places_roam(d, roam);
            break;

        case 7:
            dijikstra(air, VERT, source_city, dest_city);
            break;

        case 8:
            airways(flights, d);
            break;

        case 9:
            month = getmonth();
            date = getdate(month);
            monthdate_availableflight(flights, month, date, d);
            break;

        case 10:
            printf("\nDistance between %s and %s is %d\n", s, d, distcheck(s, d, 8, eightcities, eightFWroad));
            break;

        case 11:
            for (i = 1; i <= 8; i++)
            {
                if (strcasecmp(s, eightcities[i].name) == 0)
                    break;
            }
            bfs(i, 8, eightroadway, eightcities);
            break;

        case 12:
            for (i = 1; i <= 30; i++)
            {
                if (strcasecmp(s, thirtycities[i].name) == 0)
                    break;
            }
            bfs(source_city, 30, thirtyroadway, thirtycities);
            break;

        case 13:
            for (i = 1; i <= 30; i++)
            {
                if (strcasecmp(s, thirtycities[i].name) == 0)
                    break;
            }
            roaddijkstra(30, thirtyroadway, i);
            break;


        case 50:
            printf("\nTHIRTY CITIES - The Floyd-Warshall table:\n");
            print_2d_array(8, eightFWroad);
            break;

        case 51:
            printf("\nOG eight roadway\n");
            print_2d_array(8, eightroadway);

        case 52:
            printf("\nEIGHT CITIES - The Floyd-Warshall table:\n");
            print_2d_array(30, thirtyFWroad);
            break;

        case 53:
            printf("\nOG thirty roadway\n");
            print_2d_array(30, thirtyroadway);
            break;

        case 100:
            exit(0);

        default:
            printf("choice unavailable :)");
            break;
        }
        printf("\n{To display options again, enter 0-zero}\nEnter choice >>>  ");
    }
    printf("\n");
    return 0;
}

// (array formT) to display the places/cities in our system
void displaycityarr(struct cityname cityy[], int n)
{
    int i;
    for (i = 1; i <= n; i++)
        printf("\n%d. %s", i, cityy[i].name);

    return;
}

// near_hotels function reads the hotel information from existing file of hotel.txt
// hotel.txt holds the information of hotels like- their name, city they are in, their ratings and 24 hour pricing
void near_hotels(char d[])
{
    FILE *fp1;
    fp1 = fopen("hotel.txt", "r");
    printf("Hotel\t\tRating\t\tPrice(24hr)\n");
    for (int i = 1; i <= 30; i++)
    {
        fscanf(fp1, "%s %f %s %d", hot_details[i].name, &hot_details[i].rating, hot_details[i].addr, &hot_details[i].price);

        if (strcasecmp(hot_details[i].addr, d) == 0)
            printf("%-10s\t%-12.1f\t%10d\n", hot_details[i].name, hot_details[i].rating, hot_details[i].price);
    }
    fclose(fp1);
    return;
}

void read_arr_city_names(struct cityname A[], int n)
{
    FILE *fp1;
    int i;

    if (n == 10)
        fp1 = fopen("city10.txt", "r");

    else if (n == 8)
        fp1 = fopen("city8.txt", "r");

    else if (n == 30)
        fp1 = fopen("city30.txt", "r");

    for (i = 1; i <= n; i++)
        fscanf(fp1, "%s", A[i].name);

    fclose(fp1);
    return;
}

void selection_sort(int n, struct flight_details a[], char d[])
{
    int i, j;
    struct flight_details temp;
    for (i = 1; i <= n - 1; i++)
    {
        int min = i;
        for (j = i + 1; j <= n; j++)
        {
            if (a[j].price < a[min].price)
                min = j;
        }
        if (min != i)
        {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    printf("Flight Name\tSeats_Avalable\n");
    for (i = 1; i < n; i++)
        printf("%-10s\t%-14d\t%8d\n", a[i].name, a[i].price, a[i].seats);
    printf("from %s:\n", d);

    for (i = 1; i < n; i++)
    {
        if (strcasecmp(d, a[i].des) == 0)
            printf("%-10s\t%-14d\t%8d\n", a[i].name, a[i].price, a[i].seats);
    }

    return;
}

HOTELNODEE create(char namee[], float data, char addr[], int roka)
{
    HOTELNODEE newnode = (HOTELNODEE)malloc(sizeof(struct hotel_tree_form));
    newnode->rat = data;
    newnode->price = roka;
    strcpy(newnode->name, namee);
    strcpy(newnode->add, addr);
    newnode->r = NULL;
    newnode->l = NULL;
    return newnode;
}

void insert(HOTELNODEE root, char name[], float data, char addr[], int roka)
{
    HOTELNODEE prev = NULL;
    while (root != NULL)
    {
        prev = root;
        if (data < root->rat)
            root = root->l;

        else
            root = root->r;
    }

    HOTELNODEE newnode = create(name, data, addr, roka);

    if (data < prev->rat)
        prev->l = newnode;

    else
        prev->r = newnode;
    return;
}

void inorder(HOTELNODEE root)
{
    int i = 1;
    if (root != NULL)
    {
        inorder(root->r);
        printf("%-10s\t%-12.01f\t%8s\t%10d\n", root->name, root->rat, root->add, root->price);
        inorder(root->l);
    }
    return;
}

// function to read all the hotel details into structure array A (from main, globally declared hot_details)
void read_allhotels(struct hotel A[100])
{
    FILE *fp1;
    fp1 = fopen("hotel.txt", "r");
    for (int i = 1; i <= 30; i++)
        fscanf(fp1, "%s %f %s %d", A[i].name, &A[i].rating, A[i].addr, &A[i].price);

    fclose(fp1);
    return;
}

// C program for Dijkstra's single source shortest path algorithm. The program is for adjacency matrix representation of the graph

// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int n, int dist[], bool sptSet[])
{
    // Initialize min value
    int min_index, min = INT_MAX;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void read_airways(struct flight_details flights[]) /// read flight details
{
    FILE *fp1;
    fp1 = fopen("flight.txt", "r");
    for (int i = 1; i <= 20; i++)
    {
        fscanf(fp1, "%s %d %d %s", flights[i].name, &flights[i].price, &flights[i].seats, flights[i].des);

        for (int j = 1; j <= 10; j++)
            fscanf(fp1, "%d", &flights[i].date[j]);

        for (int j = 1; j <= 5; j++)
            fscanf(fp1, "%d", &flights[i].month[j]);
    }
    fclose(fp1);
    return;
}

void airways(struct flight_details flights[], char d[]) /// flights to your destination
{
    printf("\nCurrently Running Flights to in our service \n");
    printf("Flight\tPrice\tSeats_Avalable\n");
    for (int i = 1; i <= 20; i++)
        printf("%-10s\t%-14d\t%8d\t%s\n", flights[i].name, flights[i].price, flights[i].seats, flights[i].des);

    printf("\nFlight details cheapest to costliest to %s\n", d); ///.....................
    selection_sort(20, flights, d);
    return;
}

void hotel_rating(char d[], struct hotel z[])
{
    FILE *fp1;
    fp1 = fopen("hotel.txt", "r");
    for (int i = 1; i <= 30; i++)
    {
        fscanf(fp1, "%s %f %s %d", z[i].name, &z[i].rating, z[i].addr, &z[i].price);
    }
    fclose(fp1);
}

/*void places_roam(char d[], struct roam roam[]) /// search places nearby
{
    int i = 1;
    FILE *fp1;
    fp1 = fopen("roam.txt", "r");
    printf("Places to roam                Distance(in kms)  Location\n ");
    for (int i = 1; i <= 60; i++)
    {
        fscanf(fp1, "%s %d %s", roam[i].place, &roam[i].km, roam[i].loc);
        if (strcasecmp(roam[i].loc, d) == 0)
            printf("%-29s\t%-12.01d\t%8s\n", roam[i].place, roam[i].km, roam[i].loc);
    }
    printf("\n");

    fclose(fp1);
    return;
}*/

void places_roam(char d[],  struct roam roam[])
{
    int i = 1;
    int q = 101;
    int M = strlen(d);
    int N;
    char r[50];
    char pl[50];
    int km;
    FILE *fp1;
    fp1 = fopen("roam.txt", "r");
    printf("Places to roam                Distance(in kms)  Location\n ");
    for (int i = 1; i <= 60; i++)
    {
        fscanf(fp1, "%s %d %s", roam[i].place, &roam[i].km, roam[i].loc);
        strcpy(r,roam[i].loc);
        strcpy(pl,roam[i].place);
        km=roam[i].km;
        N = strlen(r);
        int i, j;
        int p = 0; // hash value for pattern
        int t = 0; // hash value for txt
        int h = 1;

        // The value of h would be "pow(d, M-1)%q"
        for (i = 0; i < M - 1; i++)
            h = (h * aa) % q;

        // Calculate the hash value of pattern and first
        // window of text
        for (i = 0; i < M; i++)
        {
            p = (aa * p + d[i]) % q;
            t = (aa * t + r[i]) % q;
        }

        // Slide the pattern over text one by one
        for (i = 0; i <= N - M; i++)
        {
            // Check the hash values of current window of text
            // and pattern. If the hash values match then only
            // check for characters one by one
            if (p == t)
            {
                /* Check for characters one by one */
                for (j = 0; j < M; j++)
                {
                    if (r[i + j] != d[j])
                        break;
                }

                // if p == t and pat[0...M-1] = txt[i, i+1,
                // ...i+M-1]
                if (j == M)
                    printf("%-29s\t%-12.01d\t%8s\n", pl, km, r);

            }

            // Calculate hash value for next window of text:
            // Remove leading digit, add trailing digit
            if (i < N - M)
            {
                t = (aa * (t - d[i] * h) + d[i + M]) % q;

                // We might get negative value of t, converting
                // it to positive
                if (t < 0)
                    t = (t + q);
            }
        }
    }
    printf("\n");

    fclose(fp1);
}

StackNode push(StackNode  top, char data[])
{
    StackNode new_node = malloc(sizeof(struct stacking_structure));
    strcpy(new_node->data, data);
    new_node->next = top;
    return new_node;
}

StackNode pop(StackNode top)
{
    if (top == NULL)
        return NULL;

    StackNode temp = top;
    top = top->next;
    free(temp);
    return top;
}

void history(StackNode top)
{
    printf("\nSearch history:\n");
    while (top != NULL)
    {
        printf("%s\n", top->data);
        top = top->next;
    }
    return;
}

int getmonth()
{
    int month;

    while (1)
    {
        printf("\nEnter month >>>  ");
        scanf("%d", &month);
        if (month <= 12 && month >= 1)
            break;

        else
            printf("\nMonth doesn't exist");
    }
    return month;
}

void monthdate_availableflight(struct flight_details flights[], int momo, int dodo, char d[])
{
    int i, j, flag;
    printf("Name\t\tPrice\t \t      Seats\tdestination\n");
    for (i = 1; i <= 20; i++, flag = 1)
    {
        for (j = 1; j <= 5 && flag != 0; j++)
        {
            if (flights[i].month[j] == momo)
            {
                for (j = 1; j <= 10 && flag != 0; j++)
                {
                    if (flights[i].date[j] == dodo)
                    {
                        printf("%-10s\t%-14d\t%8d\t%s\n", flights[i].name, flights[i].price, flights[i].seats, flights[i].des);
                        flag = 0;
                    }
                }
            }
        }
    }
    if (flag == 0)
        printf("\nWe are sorry, but no flights on that day!!!");
    return;
}

int getdate(int mon)
{
    int date, flag = 0;
    while (flag != 1)
    {
        printf("Enter date >>>  ");
        scanf("%d", &date);
        switch (mon)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (date <= 31 && date >= 1)
                flag = 1;
            break;

        case 2:
            if (date <= 28 && date >= 1)
                flag = 1;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if (date <= 30 && date >= 1)
                flag = 1;
            break;
        }
        if (flag == 0)
            printf("\ndate doesn't exist\n");
    }
    return date;
}

void read_road_from_file(int n, int arr[][n + 1])
{
    FILE *fp1;
    int i, j;
    if (n == 8)
        fp1 = fopen("road8.txt", "r");

    else
        fp1 = fopen("road30.txt", "r");

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            fscanf(fp1, "%d ", &arr[i][j]);
    fclose(fp1);
    return;
}

void print_2d_array(int n, int a[][n + 1])
{
    int i, j;
    printf("\n\n");
    for (i = 1; i <= n; i++)
    {
        printf("\n");
        for (j = 1; j <= n; j++)
            printf("%d\t", a[i][j]);
    }
    return;
}

// floyd-warshall algorithm for shortest distance between all the points
void floydWarshall(int n, int arr[][n + 1])
{
    int graph[n][n], i, j, k;

    // function-call to read the road distance values into arr[][] array
    read_road_from_file(n, arr);

    // making all zeroes as 9999 (here, equivalent to INFINITY)
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (arr[i][j] == 0)
                arr[i][j] = INF;
        }
        arr[i][i] = 0;
    }

    // Adding vertices individually
    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                if (arr[i][k] + arr[k][j] < arr[i][j])
                    arr[i][j] = arr[i][k] + arr[k][j];
            }
        }
    }

    return;
}

void dijikstra(int a[10][10], int n, int s, int q)
{
    int i, j;
    FILE *fp1;
    fp1 = fopen("distance_air.txt", "r");
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            fscanf(fp1, "%d", &a[i][j]);
        }
    }
    int cost[10][10], distance[10], path[10];
    int visited[10], count, min, u;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] == 0)
                cost[i][j] = 999;
            else
                cost[i][j] = a[i][j];

    for (i = 0; i < n; i++)
    {
        distance[i] = cost[s][i];
        path[i] = s;
        visited[i] = 0;
    }
    distance[s] = 0;
    visited[s] = 1;
    count = 1;
    while (count < n - 1)
    {
        min = 999;
        for (i = 0; i < n; i++)
            if (distance[i] < min && !visited[i])
            {
                min = distance[i];
                u = i;
            }
        visited[u] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (min + cost[u][i] < distance[i])
                {
                    distance[i] = min + cost[u][i];
                    path[i] = u;
                }
        count++;
    }

    for (i = 0; i < n; i++)
    {
        if (i != s && i == q)
        {
            printf("\nDistance between %s and %s = %d  \t", cityy[s].name, cityy[i].name, distance[i]);
            printf("Path = %s", cityy[i].name);
            j = i;
            do
            {
                j = path[j];
                printf("<-%s", cityy[j].name);
            }
            while (j != s);
        }
    }
    printf("\n");
    return;
}

//***********BFS(breadth-frst search) code***********/
void bfs(int s, int n, int arr[][n + 1], struct cityname cit[])
{
    int p, i, count = 0;
    add(s);
    vis[s] = 1;
    p = delete ();
    if (p != 0)
        printf("\n%d. %d- %s ", ++count, p, cit[p].name);

    while (p != 0)
    {
        for (i = 1; i <= n; i++)
        {
            if ((arr[p][i] != 0) && (vis[i] == 0))
            {
                add(i);
                vis[i] = 1;
            }
        }

        p = delete ();

        if (p != 0)
            printf("\n%d. %d- %s ", ++count, p, cit[p].name);
    }

    for (i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
            bfs(i, n, arr, cit);
    }
    return;
}

void add(int item)
{
    if (rear == 99)
        printf("\nQUEUE FULL");
    else
    {
        if (rear == -1)
        {
            q[++rear] = item;
            front++;
        }
        else
            q[++rear] = item;
    }
}

int delete()
{
    int k;
    if ((front > rear) || (front == -1))
        return (0);
    else
    {
        k = q[front++];
        return (k);
    }
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void roaddijkstra(int ver, int graph[ver+1][ver+1], int src)
{
    int dist[ver]; // The output array.  dist[i] will hold the shortest distance from src to i

    // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    bool sptSet[ver];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 1; i <= ver; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < ver - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        int u = minDistance(ver, dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 1; v <= ver; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total
            // weight of path from src to  v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                    && dist[u] != INT_MAX
                    && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(30, dist);
    return;
}

// A utility function to print the constructed distance array
void printSolution( int n, int dist[n])
{
    printf("City \t\t Distance from initial point\n");
    for (int i = 1; i <= n; i++)
        printf("%d. %s \t\t\t\t %d\n", i,thirtycities[i].name, dist[i]);
}

