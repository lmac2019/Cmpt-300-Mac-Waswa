#include "stats.h"
int producer;
int* num_factories;
int* candies_made;
int* candies_consumed;
double* min_delay;
double* max_delay;
double* total_delay;
double* avg_delay;

// static pthread_mutex_t stats_mutex;



void stats_init(int num_producers){
        producer = num_producers;
        candies_made = malloc(producer*sizeof(int));
        candies_consumed = malloc(producer*sizeof(int));
        num_factories = malloc(producer*sizeof(int));
        min_delay = malloc(producer*sizeof(double));
        max_delay = malloc(producer*sizeof(double));
        total_delay = malloc(producer*sizeof(double));
        avg_delay = malloc(producer*sizeof(double));
        for(int i = 0; i<producer; i++) {
                candies_made[i] = 0;
                candies_consumed[i] = 0;
                num_factories[i] = i;
                min_delay[i] = 0;
                max_delay[i] = 0;
                total_delay[i] = 0;
                avg_delay[i] = 0;
        }

}
void stats_cleanup(void){
        free(candies_made);
        free(candies_consumed);
        free(min_delay);
        free(max_delay);
        free(avg_delay);
        free(total_delay);
        free(num_factories);
}
void stats_record_produced(int factory_number){
        candies_made[factory_number]++;
}
void stats_record_consumed(int factory_number, double delay_in_ms){
        candies_consumed[factory_number]++;
        if(total_delay[factory_number] == 0){
          total_delay[factory_number] = delay_in_ms;
          min_delay[factory_number] = delay_in_ms;
          avg_delay[factory_number] = delay_in_ms;
          max_delay[factory_number] = delay_in_ms;
        }
        else{
          total_delay[factory_number] += delay_in_ms;
          if(min_delay[factory_number] > delay_in_ms){
            min_delay[factory_number] = delay_in_ms;
          }
          if(max_delay[factory_number]< delay_in_ms){
            max_delay[factory_number] = delay_in_ms;
          }
          avg_delay[factory_number] = total_delay[factory_number]/candies_consumed[factory_number];
        }
}
void stats_display(void){
        printf("%s%15s%15s%15s%15s%15s\n","Factory#",   "#Made",  "#Eaten","Min Delay[ms]",  "Avg Delay[ms]",  "Max Delay[ms]");
        for(int i = 0; i<producer; i++) {
                printf("%8d%15d%15d%15f%15f%15f\n",num_factories[i],candies_made[i],candies_consumed[i],min_delay[i],avg_delay[i],max_delay[i]);
        }
}
