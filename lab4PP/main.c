#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#define MAX_COUNT 20

pthread_mutex_t mut_q = PTHREAD_MUTEX_INITIALIZER;

sem_t sem_q;

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
pthread_t thread5;
pthread_t thread6;

int sem_value;

struct t_elem {
    int number;
    struct t_elem* next;
};

struct t_elem* tail = NULL;
int count = 0;
bool was_full = false;
bool was_empty = true;
int full_transitions = 0;
int empty_transitions = 0;
int buffer_clear_loops = 2;
//---------
pthread_cond_t sig21 = PTHREAD_COND_INITIALIZER;
pthread_cond_t sig22 = PTHREAD_COND_INITIALIZER;
int flag21 = 0;
int flag22 = 0;
pthread_mutex_t mut21 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut22 = PTHREAD_MUTEX_INITIALIZER;
sem_t  SCR21;
//-------
void add_elem(int number) {
    if (count >= MAX_COUNT) {
        printf("[Add] Cannot add %d: list is full (max %d elements)\n", number, MAX_COUNT);
        return;
    }

    struct t_elem* new_elem = malloc(sizeof(struct t_elem));
    if (!new_elem) {
        printf("Allocation failed!\n");
        return;
    }

    new_elem->number = number;

    if (tail == NULL) {

        new_elem->next = new_elem;
        tail = new_elem;
    } else {
        new_elem->next = tail->next;
        tail->next = new_elem;
        tail = new_elem;
    }

    count++;

    printf("[Add] Added %d (current count: %d)\n", number, count);
}

struct t_elem* get_elem() {
    if(count == 0)
    buffer_clear_loops--;
    if ( buffer_clear_loops == 0) {
        printf("[Buffer] EMPTY! Cannot get.\n");
        return NULL;
    }

    struct t_elem* head = tail->next;

    if (head == tail) {
        tail = NULL;
    } else {
        tail->next = head->next;
    }

    count--;

    printf("[Get] Got %d\n", head->number);
    return head;
}

int ati1 = 0, ati2 = 0;
unsigned atu1 = 0, atu2 = 0;
long atl1 = 0, atl2 = 0;
long unsigned atlu1 = 0, atlu2 = 0;

void use_atom(int tnum)
{
    printf("Thread%d use atom START: \n", tnum);
    printf("int: %d, %d\n", ati1, ati2);
    printf("unsigned: %u, %u\n", atu1, atu2);
    printf("long: %ld, %ld\n", atl1, atl2);
    printf("long unsigned: %lu, %lu\n", atlu1, atlu2);

}


void mod_atom(int tnum)
{
    printf("Thread%d mod_atom START: \n\n\n", tnum);
    printf("int sub fetch: %d\n", __atomic_sub_fetch(&ati1, tnum, __ATOMIC_RELAXED));
    printf("int xor fetch: %d\n", __atomic_and_fetch(&ati2, tnum, __ATOMIC_RELAXED));
    printf("unsigned nand fetch: %u\n", __atomic_or_fetch(&atu1, tnum, __ATOMIC_RELAXED));
    printf("unsigned fetch add: %u\n", __atomic_fetch_add(&atu2, tnum, __ATOMIC_RELAXED));
    printf("long fetch and: %ld\n", __atomic_fetch_xor(&atl1, tnum, __ATOMIC_RELAXED));
    printf("long fetch or: %ld\n", __atomic_fetch_nand(&atl2, tnum, __ATOMIC_RELAXED));
    printf("long unsigned compare exchange_n: %d\n", __atomic_compare_exchange_n(&atlu1, &atlu2, tnum, 0, __ATOMIC_RELAXED, __ATOMIC_RELAXED));
    printf("long unsigned compare exchange_n: before %lu, %lu;\n", atlu2, atlu1);
    __atomic_exchange(&atlu2, &atlu1, &atlu2, __ATOMIC_RELAXED);
    printf(" after useg compare exchange %lu, %lu\n", atlu2, atlu1);
}
void* p1 (void* arg)
{
    int num = *(int*)arg;

    while (1)
    {
//---------------------------------------
        if(sem_trywait(&SCR21) == 0)
        {
            printf("Thread%d semaphore SCR21 semaphore is open\n", num);
        }//------------------------------------------------
        use_atom(num);
        mod_atom(num);
        //--------
        pthread_mutex_lock(&mut22);
   //     printf("Thread%d: in mutex22! \n",num);
        flag22++;
        pthread_cond_signal(&sig22);
     //   printf("Thread%d: send signal22! outside mutex22 \n",num);
        pthread_mutex_unlock(&mut22);
        //--------
    }
}

void p2(void* arg)
{
    int num = *(int*)arg;
    struct t_elem* curr_elem=NULL;

    while (1) {
       //--------
        if(sem_trywait(&SCR21) == 0)
        {
            printf("Thread%d semaphore`s(SCR21)  signal was just sent \n", num);
            sem_post(&SCR21);
        }
        else
        {
            printf("Thread%d semaphor`s(SCR21) signal has already been sent before \n", num);
        }
        //----------------------
        if ( sem_trywait (&sem_q) == 0 ) {

            sem_getvalue(&sem_q,&sem_value);
            pthread_mutex_lock(&mut_q);

             curr_elem = (struct t_elem*)get_elem();

             printf("Consumer thread%d: semaphore=%d; element %d TAKEN; \n",
                    num,sem_value,curr_elem->number);

            free (curr_elem);

            pthread_mutex_unlock (&mut_q);

        }
        //----------------------
    }
}

void* p3(void* arg)
{
    int num = *(int*)arg;
    while (1) {
        //--------
        pthread_mutex_lock(&mut21);
        printf("Thread%d: in mutex21! \n",num);

        while (flag21==0)
        {
            pthread_cond_wait(&sig21,&mut21);
        }
        flag21=0;
       // printf("Thread%d: take signal1! outside mutex1 \n",num);
        pthread_mutex_unlock(&mut21);
        //--------
        use_atom(num);
        //----------------------
        sem_getvalue(&sem_q,&sem_value);
        if (sem_value < MAX_COUNT) {

            pthread_mutex_lock(&mut_q);

            add_elem(8);

            printf("Producer thread%d: semaphore=%d; element  CREATED; \n",
                    num,sem_value);

            sem_post (&sem_q);
            pthread_mutex_unlock (&mut_q);
        }
        //----------------------
    }
}
void* p4 (void* arg)
{
    int num = *(int*)arg;

    while (1)
    {
//--------
        pthread_mutex_lock(&mut22);
        printf("Thread%d: in mutex22! \n",num);

        while (flag22==0)
        {
            pthread_cond_wait(&sig22,&mut22);
        }
        flag22--;
    //    printf("Thread%d: take signal22! outside mutex22 \n",num);
        pthread_mutex_unlock(&mut22);
//--------
        use_atom(num);
        mod_atom(num);
        //--------
        if(sem_trywait(&SCR21) == 0)
        {
      //      printf("Thread%d semaphore`s(SCR21)  signal was just sent \n", num);
            sem_post(&SCR21);
        }
        else
        {
      //      printf("Thread%d semaphor`s(SCR21) signal has already been sent before\n", num);
        }
//-------
    }
}
void* p5 (void* arg)
{
    int num = *(int*)arg;
    struct t_elem* curr_elem=NULL;

    while (1) {
        //--------
        pthread_mutex_lock(&mut22);
        printf("Thread%d: in mutex22! \n",num);

        while (flag22==0)
        {
            pthread_cond_wait(&sig22,&mut22);
        }
        flag22--;
      //  printf("Thread%d: take signal22! outside mutex22 \n",num);
        pthread_mutex_unlock(&mut22);
        //----------------------
        if ( sem_trywait (&sem_q) == 0 ) {

            sem_getvalue(&sem_q,&sem_value);
            pthread_mutex_lock(&mut_q);

            curr_elem = (struct t_elem*)get_elem();

            printf("Consumer thread%d: semaphore=%d; element %d TAKEN; \n",
                    num,sem_value,curr_elem->number);

            free (curr_elem);
            pthread_mutex_unlock (&mut_q);
        }
        //----------------------
    }
}
void* p6(void* arg)
{
    int num = *(int*)arg;
    while (1) {

         mod_atom(num);
        //--------
        pthread_mutex_lock(&mut21);
        printf("Thread%d: in mutex21! \n",num);

        flag21 = 1;
        pthread_cond_signal(&sig21);
      //  printf("Thread%d: send signal21! outside mutex21 \n",num);
        pthread_mutex_unlock(&mut21);
        //----------------------
        sem_getvalue(&sem_q,&sem_value);
        if (sem_value < MAX_COUNT) {

            pthread_mutex_lock(&mut_q);

            add_elem(8);

            printf("Producer thread%d: semaphore=%d; element  CREATED; \n",
                    num,sem_value);

            sem_post (&sem_q);
            pthread_mutex_unlock (&mut_q);
        }
        //----------------------
    }
}
int main()
{
    sem_init (&sem_q, 0, 0);
    sem_init(&SCR21,0,0);

    int sem_value;
    sem_getvalue(&sem_q,&sem_value);
    printf("semaphore=%d\n",sem_value);

    int length_at_start=10;
    int i;

    for(i=0;i<length_at_start;i++) {
        add_elem(i);
        sem_post(&sem_q);
    }
    printf("Queue with elements from 0-th to %d-th has been created !!!\n",length_at_start-1);
    sem_getvalue(&sem_q,&sem_value);
    printf("semaphore=%d\n",sem_value);

    int thread1_number=1;
    int thread2_number=2;
    int thread3_number=3;
    int thread4_number=4;
    int thread5_number=5;
    int thread6_number=6;

    pthread_create (&thread1,NULL,&p1,(void*)&thread1_number);
    pthread_create (&thread2,NULL,&p2,(void*)&thread2_number);
    pthread_create (&thread3,NULL,&p3,(void*)&thread3_number);
    pthread_create (&thread4,NULL,&p4,(void*)&thread4_number);
    pthread_create (&thread5,NULL,&p5,(void*)&thread5_number);
    pthread_create (&thread6,NULL,&p6,(void*)&thread6_number);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    pthread_join(thread6,NULL);

    printf("All threads stopped !!!\n");

    pthread_mutex_destroy (&mut_q);
    pthread_mutex_destroy (&mut21);
    pthread_mutex_destroy (&mut22);
    sem_destroy (&sem_q);
    sem_destroy (&SCR21);
    pthread_cond_destroy(&sig21);
    pthread_cond_destroy(&sig22);

    return 0;
}
