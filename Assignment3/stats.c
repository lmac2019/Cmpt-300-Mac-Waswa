#include "stats.h"
int producer;


statsStructPtr stats_array;



void stats_init(int num_producers){
        producer = num_producers;
        stats_array = malloc(producer*sizeof(stats_t));
        for(int i = 0; i<producer; i++) {
                stats_array[i].num_factories = i;
                stats_array[i].candies_made = 0;
                stats_array[i].candies_consumed = 0;
                stats_array[i].min_delay = -1;
                stats_array[i].max_delay = -1;
                stats_array[i].total_delay = 0;
                stats_array[i].avg_delay = 0;
        }

}
void stats_cleanup(void){
        free(stats_array);
        stats_array = NULL;
}
void stats_record_produced(int factory_number){
        stats_array[factory_number].candies_made++;
}
void stats_record_consumed(int factory_number, double delay_in_ms){
        stats_array[factory_number].candies_consumed++;
        if(stats_array[factory_number].min_delay == -1) {
                stats_array[factory_number].total_delay = delay_in_ms;
                stats_array[factory_number].min_delay = delay_in_ms;
                stats_array[factory_number].max_delay = delay_in_ms;
                stats_array[factory_number].avg_delay = delay_in_ms;
        }
        else{
                stats_array[factory_number].total_delay += delay_in_ms;
                if(stats_array[factory_number].min_delay > delay_in_ms) {
                        stats_array[factory_number].min_delay = delay_in_ms;
                }
                if(stats_array[factory_number].max_delay< delay_in_ms) {
                        stats_array[factory_number].max_delay = delay_in_ms;
                }
                stats_array[factory_number].avg_delay =   stats_array[factory_number].total_delay /stats_array[factory_number].candies_consumed;
        }
}
void stats_display(void){
        printf("%8s%15s%15s%15s%15s%15s\n","Factory#",   "#Made",  "#Eaten","Min Delay[ms]",  "Avg Delay[ms]",  "Max Delay[ms]");
        for(int i = 0; i<producer; i++) {
                printf("%8d%15d%15d%15.5f%15.5f%15.5f\n",stats_array[i].num_factories,stats_array[i].candies_made,stats_array[i].candies_consumed,stats_array[i].min_delay,stats_array[i].avg_delay,stats_array[i].max_delay);
        }
}
