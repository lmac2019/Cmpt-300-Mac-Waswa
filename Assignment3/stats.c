#include "stats.h"
int producer;
int* num_factories;
int* candies_made;
int* candies_consumed;
// static pthread_mutex_t stats_mutex;



void stats_init(int num_producers){
        producer = num_producers;
        candies_made = malloc(producer*sizeof(int));
        candies_consumed = malloc(producer*sizeof(int));
        num_factories = malloc(producer*sizeof(int));
        for(int i = 0; i<producer; i++) {
                candies_made[i] = 0;
                candies_consumed[i] = 0;
                num_factories[i] = i;
        }

}
void stats_cleanup(void){
        free(candies_made);
        free(candies_consumed);
}
void stats_record_produced(int factory_number){
        candies_made[factory_number]++;
}
void stats_record_consumed(int factory_number, double delay_in_ms){
        candies_consumed[factory_number]++;
}
void stats_display(void){
        printf("%s%15s%15s%15s%15s%15s\n","Factory#",   "#Made",  "#Eaten","Min Delay[ms]",  "Avg Delay[ms]",  "Max Delay[ms]");
        for(int i = 0; i<producer; i++) {
                printf("%8d%15d%15d\n",num_factories[i],candies_made[i],candies_consumed[i] );
        }
}
