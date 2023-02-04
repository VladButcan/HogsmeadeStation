#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"


/* Creeaza o gara cu un numar fix de peroane.
 * 
 * platforms_no: numarul de peroane ale garii
 *
 * return: gara creata
 */
TrainStation* open_train_station(int platforms_no) {
    if (platforms_no > 0) {
        TrainStation * gara = malloc(sizeof(TrainStation));
        gara->platforms_no = platforms_no;
        gara->platforms = malloc(sizeof(Train *) * platforms_no);
        for (int i = 0; i < platforms_no; i++) {
            gara->platforms[i] = NULL;
        }
        return gara;
    }
    return NULL;
}


/* Elibereaza memoria alocata pentru gara.
 *
 * station: gara existenta
 */
void close_train_station(TrainStation *station) {
    if (station) {
        for (int i = 0; i < station->platforms_no; i++) {
            if (station->platforms) {
                if (station->platforms[i]) {
                    if (station->platforms[i]->train_cars) {
                        TrainCar * node;
                        TrainCar * pnode;
                        node = station->platforms[i]->train_cars;
                        while (node != NULL) {
                            pnode = node;
                            node = node->next;
                            free(pnode);
                        }
                    }
                    free(station->platforms[i]);
                }
            }
        }
        free(station->platforms);
        free(station);
    }
}


/* Afiseaza trenurile stationate in gara.
 *
 * station: gara existenta
 * f: fisierul in care se face afisarea
 */
void show_existing_trains(TrainStation *station, FILE *f) {
    if (station && f) {
        if (station->platforms_no > 0) {
            for (int i = 0; i < station->platforms_no; i++) {
                fprintf(f, "%d: ", i);
                if (station->platforms) {
                    if (station->platforms[i]) {
                        if (station->platforms[i]->locomotive_power >= 0) {
                            fprintf(f, "(%d)", station->platforms[i]->locomotive_power);
                            if (station->platforms[i]->train_cars) {
                                TrainCar * newstation = station->platforms[i]->train_cars;
                                while (newstation != NULL) {
                                    fprintf(f, "-|%d|", newstation->weight);
                                    newstation = newstation->next;
                                }
                            }
                        }
                    }
                }
                fprintf(f, "\n");
            }
        }
    }
}


/* Adauga o locomotiva pe un peron.
 * 
 * station: gara existenta
 * platform: peronul pe care se adauga locomotiva
 * locomotive_power: puterea de tractiune a locomotivei
 */

// typedef struct TrainCar {
//     int weight;                 // greutatea unui vagon
//     struct TrainCar *next;      // urmatorul vagon din secventa
// } TrainCar;

// /* 
//  * Reprezentarea unui tren. 
//  */
// typedef struct Train {
//     int locomotive_power;       // puterea de tractiune a locomotivei
//     TrainCar* train_cars;       // primul vagon din secventa de vagoane
// } Train;


// typedef struct TrainStation {
//     int platforms_no;
//     Train **platforms;
// } TrainStation;

void arrive_train(TrainStation *station, int platform, int locomotive_power) {
    if (station) {
        if (station->platforms_no > 0 && station->platforms_no > platform && platform >= 0) {
            if (station->platforms) {
                if (station->platforms[platform] == NULL) {
                    station->platforms[platform] = malloc(sizeof(Train));
                    station->platforms[platform]->locomotive_power = locomotive_power;
                    station->platforms[platform]->train_cars = NULL;
                }
            }
        }
    } 
}


/* Elibereaza un peron.
 * 
 * station: gara existenta
 * platform: peronul de pe care pleaca trenul
 */
void leave_train(TrainStation *station, int platform) {
    if (platform >= 0) {
        if (station) {
            if (station->platforms) {
                if (station->platforms_no > platform) {
                    if (station->platforms[platform]) {
                        if (station->platforms[platform]->train_cars) {
                            TrainCar * vagon = station->platforms[platform]->train_cars;
                            TrainCar * remove;
                            while (vagon) {
                                remove = vagon;
                                vagon = vagon->next;
                                free(remove);
                            }
                        }
                        free(station->platforms[platform]);
                        station->platforms[platform] = NULL;
                    }
                }
            }
        }
    }
}


/* Adauga un vagon la capatul unui tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului adaugat
 */
void add_train_car(TrainStation *station, int platform, int weight) {
    if (platform >= 0 && weight >= 0 && platform < station->platforms_no) {
        if (station) {
            if (station->platforms) {
                if (station->platforms[platform]) {
                    if (station->platforms[platform]->locomotive_power >= 0) {
                        if (station->platforms[platform]->train_cars == NULL) {
                            station->platforms[platform]->train_cars = malloc(sizeof(TrainCar));
                            station->platforms[platform]->train_cars->weight = weight;
                            station->platforms[platform]->train_cars->next = NULL;
                        } else {
                            TrainCar * vagon;
                            vagon = station->platforms[platform]->train_cars;
                            while (vagon->next) {
                                vagon = vagon->next;
                            }
                            vagon->next = malloc(sizeof(TrainCar));
                            vagon->next->weight = weight;
                            vagon->next->next = NULL;
                            vagon = vagon->next;
                        }
                    }
                }
            }
        }
    }
}


/* Scoate vagoanele de o anumita greutate dintr-un tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului scos
 */
void remove_train_cars(TrainStation *station, int platform, int weight) {
    if (station) {
        if (platform >= 0 && platform < station->platforms_no && weight >= 0) {
            if (station->platforms) {
                if (station->platforms[platform]) {
                    if (station->platforms[platform]->locomotive_power >= 0) {
                        if (station->platforms[platform]->train_cars) {
                            TrainCar * vagon = station->platforms[platform]->train_cars;
                            TrainCar * pvagon;
                            TrainCar * remove;
                            while (vagon && vagon->weight == weight) {
                                remove = vagon;
                                vagon = vagon->next;
                                station->platforms[platform]->train_cars = vagon;
                                free(remove);
                            }
                            while (vagon) {
                                if (vagon->weight == weight) {
                                    remove = vagon;
                                    vagon = vagon->next;
                                    pvagon->next = vagon;
                                    remove->next = NULL;
                                    free(remove);
                                } else {
                                    pvagon = vagon;
                                    vagon = vagon->next;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


/* Muta o secventa de vagoane dintr-un tren in altul.
 * 
 * station: gara existenta
 * platform_a: peronul pe care se afla trenul de unde se scot vagoanele
 * pos_a: pozitia primului vagon din secventa
 * cars_no: lungimea secventei
 * platform_b: peronul pe care se afla trenul unde se adauga vagoanele
 * pos_b: pozitia unde se adauga secventa de vagoane
 */
void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
    if (station) {
        if (station->platforms) {
            if (station->platforms[platform_a] && station->platforms[platform_b]) {
                if (station->platforms[platform_a]->train_cars) {
                    if (pos_a > 0 && pos_b > 0 && cars_no > 0 ) {
                        int length_a = 0;
                        int length_b = 0;
                        int ok = 0;
                        TrainCar * vagon = station->platforms[platform_a]->train_cars;
                        TrainCar * past_vagon;
                        TrainCar * start_move;
                        TrainCar * stop_move;
                        while (vagon) {
                            vagon = vagon->next;
                            length_a++;
                        }
                        vagon = station->platforms[platform_b]->train_cars;

                        while (vagon) {
                            vagon = vagon->next;
                            length_b++;
                        }

                        if (pos_a == 1 && pos_a + cars_no <= length_a + 1 && pos_b <= length_b + 1) {
                            vagon = station->platforms[platform_a]->train_cars;

                            for (int i = 1; i < cars_no; i++) {
                                vagon = vagon->next;
                            }
                            start_move = station->platforms[platform_a]->train_cars;
                            stop_move = vagon;
                            station->platforms[platform_a]->train_cars = vagon->next;
                            stop_move->next = NULL;
                            ok = 1;
                        } else {
                            if (pos_a > 1 && pos_a + cars_no <= length_a + 1 && pos_b <= length_b + 1) {
                                vagon = station->platforms[platform_a]->train_cars;

                                for (int i = 1; i < pos_a; i++) {
                                    past_vagon = vagon;
                                    vagon = vagon->next;
                                }
                                start_move = vagon;

                                for (int i = 1; i < cars_no; i++) {
                                    vagon = vagon->next;
                                }
                                stop_move = vagon;
                                past_vagon->next = vagon->next;
                                stop_move->next = NULL;
                                ok = 1;
                            }
                        }
                        if (station->platforms[platform_b]->train_cars) {
                            if (ok == 1) {
                                vagon = station->platforms[platform_b]->train_cars;
                                if (pos_b == 1 && pos_b <= length_b + 1) {
                                    vagon = station->platforms[platform_b]->train_cars;
                                    stop_move->next = vagon;
                                    station->platforms[platform_b]->train_cars = start_move;
                                } else {
                                    if (pos_b <= length_b + 1) {
                                        vagon = station->platforms[platform_b]->train_cars;
                                        for (int i = 1; i < pos_b; i++) {
                                            past_vagon = vagon;
                                            vagon = vagon->next;
                                        }
                                        stop_move->next = vagon;
                                        past_vagon->next = start_move;
                                    }
                                }
                            }
                        } else {
                            if (pos_b == 1 && ok == 1) {
                                station->platforms[platform_b]->train_cars = start_move;
                            }
                        }
                    }
                }
            }
        }
    }
}


/* Gaseste trenul cel mai rapid.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station) {
    int platforma = 0, weight = 0, max_pow = 0;
    if (station && station->platforms) {
        for (int i = 0; i < station->platforms_no; i++) {
            weight = 0;
            if (station->platforms[i]) {
                TrainCar * vagon;
                vagon = station->platforms[i]->train_cars;
                while (vagon) {
                    weight = weight + vagon->weight;
                    vagon = vagon->next;
                }
                if ((station->platforms[i]->locomotive_power - weight) > max_pow) {
                    max_pow = station->platforms[i]->locomotive_power - weight;
                    platforma = i;
                }
            }
        }
    }
    return platforma;
}


/* Gaseste trenul supraincarcat.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station) {
    int weight = 0;
    if (station && station->platforms) {
        for (int i = 0; i < station->platforms_no; i++) {
            weight = 0;
            if (station->platforms[i]) {
                TrainCar * vagon;
                vagon = station->platforms[i]->train_cars;
                while (vagon) {
                    weight = weight + vagon->weight;
                    vagon = vagon->next;
                }
                if (weight > station->platforms[i]->locomotive_power) {
                    return i;
                }
            }

        }
    }
    return -1;
}


/* Gaseste trenul cu incarcatura optima.agon->next->weight = weight
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station) {
    int platforma = 0, weight = 0, max = 10000;
    if (station && station->platforms) {
        for (int i = 0; i < station->platforms_no; i++) {
            weight = 0;
            if (station->platforms[i]) {
                TrainCar * vagon;
                vagon = station->platforms[i]->train_cars;
                while (vagon) {
                    weight = weight + vagon->weight;
                    vagon = vagon->next;
                }
                if ((station->platforms[i]->locomotive_power - weight) < max) {
                    max = station->platforms[i]->locomotive_power - weight;
                    platforma = i;
                }
            }
        }
    }
    return platforma;
}


/* Gaseste trenul cu incarcatura nedistribuita bine.
 * 
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    int peron = -1, ok = 0;
    if (cars_no > 0) {
        if (station && station->platforms) {
            int max_weight = 0;
            for (int i = 0; i < station->platforms_no; i++) {
                if (station->platforms[i] && station->platforms[i]->train_cars) {
                    int weight = 0;
                    int length = 0;
                    TrainCar * vagon;
                    TrainCar * start_count;
                    vagon = station->platforms[i]->train_cars;
                    start_count = station->platforms[i]->train_cars;
                    while (vagon) {
                        length++;
                        vagon = vagon->next;
                    }
                    if (length >= cars_no) {
                        int num = cars_no;
                        vagon = station->platforms[i]->train_cars;
                        while (vagon) {
                            weight = 0;
                            vagon = start_count;
                            for (int j = 0; j < cars_no; j++) {
                                weight = weight + vagon->weight;
                                vagon = vagon->next;
                            }
                            if (weight > max_weight) {
                            max_weight = weight;
                            peron = i;
                            *start_car = start_count;
                            ok = 1;
                            }
                            start_count = start_count->next;
                        }
                    }
                }
            }
            if (ok == 1) {
                return peron;
            }
        }
    }
    *start_car = NULL;
    return -1;
}


/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void order_train(TrainStation *station, int platform) {
    if (station && station->platforms && station->platforms[platform]) {
        if (station->platforms[platform]->train_cars) {
            TrainCar * vagon = station->platforms[platform]->train_cars;
            TrainCar * swap_vagon;
            TrainCar * prev_vagon;
            if (vagon->next) {
                int ok = 1;
                vagon = station->platforms[platform]->train_cars;
                swap_vagon = vagon;
                vagon = vagon->next;
                while (ok != 0) {
                    ok = 0;
                    while (vagon) {
                        if (swap_vagon->weight < vagon->weight) {
                            if (swap_vagon == station->platforms[platform]->train_cars) {
                                swap_vagon->next = swap_vagon->next->next;
                                vagon->next = swap_vagon;
                                station->platforms[platform]->train_cars = vagon;
                                swap_vagon = station->platforms[platform]->train_cars;
                                vagon = swap_vagon->next;
                                ok++;
                            } else {
                                swap_vagon->next = vagon->next;
                                vagon->next = swap_vagon;
                                prev_vagon->next = vagon;
                                swap_vagon = prev_vagon->next;
                                vagon = prev_vagon->next->next;
                                ok++;
                            }
                        }
                        prev_vagon = swap_vagon;
                        swap_vagon = vagon;
                        vagon = vagon->next;
                    }
                    vagon = station->platforms[platform]->train_cars;
                    swap_vagon = vagon;
                    vagon = vagon->next;
                }
            }
        }
    }
}


/* Scoate un vagon din trenul supraincarcat.
 * 
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station) {
    if (station && station->platforms) {
        for (int i = 0; i < station->platforms_no; i++) {
            if (station->platforms[i] && station->platforms[i]->train_cars) {
                TrainCar * vagon = station->platforms[i]->train_cars;
                TrainCar * remove;
                int weight = 0;
                int max_diff = 0;
                while (vagon) {
                    weight = weight + vagon->weight;
                    vagon = vagon->next;
                }
                if (weight > station->platforms[i]->locomotive_power) {
                    vagon = station->platforms[i]->train_cars;
                    int count = 0;
                    int pos = 0;
                    int power = station->platforms[i]->locomotive_power;
                    while (vagon) {
                        if (power >= weight - vagon->weight) {
                            if (max_diff < power - vagon->weight) {
                                max_diff = power - vagon->weight;
                                pos = count;
                            }
                        }
                        count++;
                        vagon = vagon->next;
                    }
                    if (pos == 0) {
                        remove = station->platforms[i]->train_cars;
                        station->platforms[i]->train_cars = station->platforms[i]->train_cars->next;
                        remove->next = NULL;
                        free(remove);
                        return;
                    }
                    vagon = station->platforms[i]->train_cars->next;
                    remove = station->platforms[i]->train_cars;
                    while (pos > 1) {
                        remove = vagon;
                        vagon = vagon->next;
                        pos--;
                    }
                    remove->next = vagon->next;
                    remove = vagon;
                    vagon = vagon->next;
                    remove->next = NULL;
                    free(remove);
                }
            }
        }
    }
}
