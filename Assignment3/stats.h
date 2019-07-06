#ifndef STATS_H
#define STATS_H
#include "helpers.h"
#include "macros.h"

typedef struct stats {
        int num_factories;
        int candies_made;
        int candies_consumed;
        double min_delay;
        double max_delay;
        double total_delay;
        double avg_delay;
} stats_t;

#define statsStructPtr stats_t*


void stats_init(int num_producers);
void stats_cleanup(void);
void stats_record_produced(int factory_number);
void stats_record_consumed(int factory_number, double delay_in_ms);
void stats_display(void);

#endif
