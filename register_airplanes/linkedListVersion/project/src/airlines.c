/***************************************************
 *                                                 *
 * file: airlines.c                                *
 *                                                 *
 * @Author  Loukas Mertzanis                       *
 * @email   mertzanis@ics.forth.gr                 *
 *                                                 *
 * @brief   Implementation of airlines.h           *
 *                                                 *
 ***************************************************
 */

#include "airlines.h"


int initialize()
{
    //initialize destination lists with sentinel nodes
    int i;
    for(i=0; i<10; i++){
        destTable[i].sentinel_p = (_flights_l*)malloc(sizeof(_flights_l));
        destTable[i].sentinel_p->depart_time = 9999;
        destTable[i].sentinel_p->pId = 9999;
        destTable[i].sentinel_p->next = destTable[i].sentinel_p;
        destTable[i].flight_p = destTable[i].sentinel_p;
    }
    //initialize dummy node in circular doubly linked list
    airlines_p = (_airlines_l*)malloc(sizeof(_airlines_l));
    airlines_p->next = airlines_p;
    airlines_p->prev = airlines_p;
    airlines_p->p_root=NULL;
    airlines_p->aId = -1;
    return 1;
}

void printRegisteredAirlines()
{
    _airlines_l* tmp = airlines_p->next;
    printf("\nAirlines = ");
    while(tmp->aId != -1){
        printf("%d, ", tmp->aId);
        tmp = tmp->next;
    }
    printf("\b\b  \nDONE");
}

int register_airline(int aId) {
    /*Allocate memory for new airline node and initialize*/
    _airlines_l* newAirline = (_airlines_l*)malloc(sizeof(_airlines_l));
    if(newAirline == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newAirline->aId = aId;
	newAirline->p_root = NULL;

    /*Insert node in doubly linked list*/
    if(airlines_p == airlines_p->next){ /*empty list*/
        airlines_p->next = newAirline;
        airlines_p->prev = newAirline;
        newAirline->next = airlines_p;
        newAirline->prev = airlines_p;
    }
    else{
    airlines_p->next->prev = newAirline;
    newAirline->next = airlines_p->next;
    newAirline->prev = airlines_p;
    airlines_p->next = newAirline;
    }

    printRegisteredAirlines();
    return 1;
}

_airlines_l* searchAirline(int keyValue)
{
    int flag = 0;
    if(airlines_p == airlines_p->next){
        printf("Airline list is empty!");
        return NULL;
    }

    _airlines_l* tmp = airlines_p->next;
    while(1){
        if(tmp->aId == keyValue)
            return tmp;
        if(tmp->aId == -1){
            flag++;
        }
        if(flag == 2) //airline does not exist!
            return NULL;
        tmp = tmp->next;
    }
}

/* Eisagwgi aeroplanou stin taksinomimeni lista aeroplanwn aeroporikis etairias*/
int insertPlane(_airplane* airplane, _airlines_l* airline)
{
    if(airline->p_root==NULL){ /*empty plane list*/
        airline->p_root = airplane;
        return 1;
    }
    else if(airplane->pId < airline->p_root->pId){ /*new airplane becomes head*/
        airplane->next = airline->p_root;
        airline->p_root = airplane;
        return 1;
    }
    else{
        _airplane* tmp = airline->p_root;
        while(tmp->next != NULL){
            if(tmp->next->pId > airplane->pId){
                airplane->next = tmp->next;
                tmp->next = airplane;
                return 1;
            }
            tmp = tmp->next;
        }
        tmp->next = airplane; /*new airplane becomes last node*/
        return 1;
    }
}

int printPlanes()
{
    _airlines_l* tmp1 = airlines_p->prev;
    int i = 1;
    while(tmp1->aId != -1){
        _airplane* tmp2 = tmp1->p_root;
        printf("\nAirline%d =  ", tmp1->aId);
        i++;
        while(tmp2 != NULL){
            printf("%d:%d, ", tmp2->pId, tmp1->aId);
            tmp2 = tmp2->next;
        }
        printf("\b\b  ");
        tmp1 = tmp1->prev;
    }
    printf("\nDone");
    return 1;
}

int print_destinations()
{
    int i;
    _flights_l* tmp;
    for(i=0; i<10; i++){
        tmp = destTable[i].flight_p;
        printf("\nDestination%d =  ", i);
        while(tmp != destTable[i].sentinel_p){
            printf("%d:%d, ", tmp->pId, tmp->depart_time);
            tmp = tmp->next;
        }
        printf("\b\b  ");
    }
    printf("\nDone");
    return 1;
}


int insertFlight(_flights_l* flightNode, int destNum)
{
    _flights_l* curr = destTable[destNum].flight_p;

    if(curr == destTable[destNum].sentinel_p){ /*Only sentinel contained*/
        destTable[destNum].flight_p = flightNode;
        flightNode->next = destTable[destNum].sentinel_p;
        destTable[destNum].sentinel_p->next = flightNode;
        return 1;
    }
    if(curr->depart_time > flightNode->depart_time){ /*new node becomes head*/
        flightNode->next = destTable[destNum].flight_p;
        destTable[destNum].flight_p = flightNode;
        destTable[destNum].sentinel_p->next = flightNode;
        return 1;
    }
    while(curr->next != destTable[destNum].sentinel_p){ /*common case*/
        if(curr->next->depart_time > flightNode->depart_time){
            flightNode->next = curr->next;
            curr->next = flightNode;
            destTable[destNum].sentinel_p->next = flightNode;
            return 1;
        }
        curr = curr->next;
    }
    curr->next = flightNode;
    flightNode->next = destTable[destNum].sentinel_p;
    destTable[destNum].sentinel_p->next = flightNode; /*setup sentinel*/
    return 1;
}

int insert_airplanes(int aId, int pId, int dest, int depart_time)
{
    /*Allocate memory for new airplane node and initialize*/
    _airplane* newAirplane = (_airplane*)malloc(sizeof(_airplane));
    if(newAirplane == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newAirplane->pId = pId;
    newAirplane->dest = dest;
    newAirplane->depart_time = depart_time;
    newAirplane->next = NULL;

    int flag1 = insertPlane(newAirplane, searchAirline(aId));

    /*Allocate memory for new flight node and initialize*/
    _flights_l* newFlight = (_flights_l*)malloc(sizeof(_flights_l));
    if(newFlight == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newFlight->pId = pId;
    newFlight->depart_time = depart_time;
    newFlight->next = NULL;
    int flag2 = insertFlight(newFlight, dest);

    printPlanes();
    return (flag1 && flag2);
}

/*anazitisi kai diagrafi ptisis*/
int removeFlight(int pId, int destNum, int depTime)
{
    _flights_l *prev = NULL;
    _flights_l *curr = destTable[destNum].flight_p;
    //destTable[destNum].sentinel_p->pId = pId;
    /*list head removal case*/
    if(curr->pId == pId && curr != destTable[destNum].sentinel_p){
        destTable[destNum].flight_p = curr->next;
        free(curr);
        return 1;
    }
    /*Use sentinel's pointer to shorten the search!*/
    if(destTable[destNum].sentinel_p->next->depart_time < depTime){
        prev = destTable[destNum].sentinel_p->next;
        curr = prev->next;
    }
    while(curr->pId != pId){
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    destTable[destNum].sentinel_p->next = curr->next;
    free(curr);
    return 1;
}

int cancel_flight(int aId, int pId, int dest) {
    _airlines_l* airline = searchAirline(aId);
    _airplane* tmp = airline->p_root;
    _airplane* prev = NULL;

    if(pId == airline->p_root->pId){ //Remove head corner case
        removeFlight(pId, dest, airline->p_root->depart_time);
        airline->p_root = airline->p_root->next;
        free(tmp);
        printPlanes();
        return 1;
    }
    while(tmp->pId != pId){
        prev = tmp;
        tmp = tmp->next;
    }
    removeFlight(pId, dest, tmp->depart_time);
    prev->next = tmp->next;
    free(tmp);
    printPlanes();
    return 1;
}

int delete_airline(int aId)
{
    _airlines_l* airline;
    _airplane* tmp;
    _airplane* prev;

    airline = searchAirline(aId);
    tmp = airline->p_root;
    while(tmp!=NULL){
        prev = tmp;
        removeFlight(tmp->pId, tmp->dest, tmp->depart_time);
        tmp = tmp->next;
        free(prev);
    }
    airline->prev->next = airline->next;
    airline->next->prev = airline->prev;
    free(airline);
    printPlanes();
    return 1;
}

_airplane* combineLists(_airplane* p1, _airplane* p2)
{
    _airplane* head = NULL;
    _airplane* tmp = NULL;
    if(p1 == NULL)    /*empty list case*/
        return p2;
    if(p2 == NULL)    /*empty list case*/
        return p1;

    /*Choose smallest pId node to be head*/
    if(p1->pId <= p2->pId){
        tmp = p1;
        p1 = tmp->next;
    }
    else{
        tmp = p2;
        p2 = tmp->next;
    }
    head = tmp;

    /*Combine lists until we reach a list end*/
    while(p1 && p2){
        if(p1->pId <= p2->pId){
            tmp->next = p1;
            tmp = p1;
            p1 = tmp->next;
        }
        else{
            tmp->next = p2;
            tmp = p2;
            p2 = tmp->next;
        }
    }
    /*If there are nodes left in a list, add them at the end*/
    if(p1 == NULL)
        tmp->next = p2;
    if(p2 == NULL)
        tmp->next = p1;
    return head;
}

/*h aId2 agorazei tin aId1*/
int acquisition_airline(int aId1, int aId2)
{
    _airlines_l* buyer = searchAirline(aId2);
    _airlines_l* seller = searchAirline(aId1);
    _airlines_l* tmp;
    buyer->p_root = combineLists(buyer->p_root, seller->p_root);
    /*Delete sold out airline*/
    tmp = seller->prev;
    seller->prev->next = seller->next;
    seller->next->prev = tmp;
    free(seller);
    printPlanes();
    return 1;
}

/*h aId2 agorazei ta aeroplana tis aId1 pros dest*/

int subsidiary_airiline(int aId1, int aId2, int dest) //seg faults - needs debugging
{
    _airlines_l* buyer = searchAirline(aId2);
    _airlines_l* seller = searchAirline(aId1);
    if( !buyer || !seller) {
        printf("\nOne of the airlines does not exist!");
        printPlanes();
        return 1;}
    //geting the list of airplanes
    _airplane* head1 = buyer->p_root;
    _airplane* head2 = seller->p_root;
    //setting pointers
    _airplane* current1 = head1;
    _airplane* current2 = head2;
    //prev pointers
    _airplane* prev1;
    _airplane* prev2;
    //next pointers
    _airplane* next1;
    _airplane* next2;

    while(current2){
        if(current2->dest == dest){
            /*Arxika prepei na ton diagrapsoume apo tin lista tou seller*/
            if(current2 == head2 ) { //If the head plane gets bought
                head2 = head2->next; //ananewnoume to head
                next2 = current2->next; //settaroume ton next pointer
            }
            else{
                prev2->next = current2->next; //skippare ton komvo pou tha poulithei(diokston aptin lista tou seller)
                next2 = current2->next;
            }
            while(current1 && current1->pId < current2->pId){ //Traverse buyer list to find spot to enter bought node
                prev1 = current1;
                current1 = current1 ->next;
            }
            if(current1 == head1){ //Bought node becomes head of buyer's plane list
                current2-> next = head1;
                head1 = current2;
                current1 = head1;
            }
            else if(!current1){ //Bought node becomes tail of buyer's plane list
                prev1->next = current2;
                current1 =current2;
                current1->next = NULL;
            }
            else{ //Common case
                prev1->next = current2;
                current2 ->next = current1;
                prev1 = prev1->next;
            }
        }
        else{ //Pame ston epomeno komvo tis listas tou pwliti
            next2 = current2->next;
            prev2 = current2;
        }
        current2 = next2;
    }

    buyer->p_root = head1;
    seller->p_root = head2;
    printPlanes();
    return 1;
}

int partition_airplanes(int aId1)
{
    _airlines_l* tmp = searchAirline(aId1);
    _airlines_l* right = tmp->next;
    _airlines_l* left = tmp->prev;
    _airplane* current = tmp->p_root;
    _airplane* temp = NULL;
    if(!current){
        printf("\nNo planes found in list!");
        printPlanes();
        return 1;
    }
    while(current){
        if(right->aId == -1 || right->aId == aId1) right = right->next; /*skip dummy or self*/
        if(right->aId == -1 || right->aId == aId1) right = right->next; /*skip dummy or self*/
        temp = current->next;
        current->next = NULL;
        insertPlane(current, right);
        current = temp;
        right = right->next;

        if(!current) break; /*out of planes*/

        if(left->aId == -1 || left->aId == aId1) left = left->prev;
        if(left->aId == -1 || left->aId == aId1) left = left->prev;
        temp = current->next;
        current->next = NULL;
        insertPlane(current, left);
        current = temp;
        left = left->prev;
    }
    /*delete airline from doubly linked list*/
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);
    printPlanes();
    return 1;
}

int travel(int dest, int timestamp) {
    _flights_l* tmp;
    printf("\nAvailable Flights:  ");
    if(destTable[dest].sentinel_p->next->depart_time < timestamp)
        tmp = destTable[dest].sentinel_p->next;
    else
        tmp = destTable[dest].flight_p;
    while(tmp->depart_time <= timestamp)
        tmp = tmp->next;
    while(tmp != destTable[dest].sentinel_p){
        printf("%d:%d, ", tmp->pId, tmp->depart_time);
        tmp = tmp->next;
    }
    printf("\b\b  ");
    tmp = destTable[dest].flight_p;
    printf("\nDestination =  ");
    while(tmp != destTable[dest].sentinel_p){
        printf("%d:%d, ", tmp->pId, tmp->depart_time);
        tmp = tmp->next;
    }
    printf("\b\b  \nDONE");
    return 1;
}

int print_airlines() {
    _airlines_l* tmp1 = airlines_p->prev;
    int i = 1;
    while(tmp1->aId != -1){
        _airplane* tmp2 = tmp1->p_root;
        printf("\nAirline%d = %d\n\tAirplanes%d =  ", i, tmp1->aId, i);
        i++;
        while(tmp2 != NULL){
            printf("%d, ", tmp2->pId);
            tmp2 = tmp2->next;
        }
        printf("\b\b  ");
        tmp1 = tmp1->prev;
    }
    printf("\nDone");
    return 1;
}


int free_all(void) {
    return 1;
}
