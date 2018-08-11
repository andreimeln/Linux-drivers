#ifndef METEO_DEV_H
#define METEO_DEV_H

#define METEO_COUNT 16
#define METEO_NAME "meteo"

/* really sizeof(double) */
#define DATASIZE 8 

struct meteo_item {
  char   f_ID[4];
  int    f_status;
#ifdef __KERNEL__
  char   f_data[DATASIZE]; // = double
#else
  union {
    char f_data[DATASIZE];
    double f_value;
  } D;
#endif
  time_t f_last; // time of last read
};

#define METEO_ACTIVE 1
#define METEO_INACTIVE 0

#ifndef __KERNEL__
#define CHECK_SIZE (sizeof(double) == DATASIZE)
#endif

#endif // METEO_DEV_H
