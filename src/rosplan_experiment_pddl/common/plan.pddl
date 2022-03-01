Number of literals: 23
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
Pruning (pick_unknown armadillo can corner_area) - never appeared in initial RPG
Pruning (pick_unknown armadillo can elevator1) - never appeared in initial RPG
Pruning (pick_unknown armadillo can near_elevator1) - never appeared in initial RPG
Pruning (pick_unknown armadillo can open_area) - never appeared in initial RPG
Pruning (place_unknown armadillo can can corner_area) - never appeared in initial RPG
Pruning (place_unknown armadillo can can elevator1) - never appeared in initial RPG
Pruning (place_unknown armadillo can can near_elevator1) - never appeared in initial RPG
Pruning (place_unknown armadillo can can open_area) - never appeared in initial RPG
All the ground actions in this problem are compression-safe
Initial heuristic = 7.000
b (6.000 | 1.000)b (5.000 | 4.003)b (4.000 | 5.004)b (3.000 | 6.005)b (2.000 | 7.006)b (1.000 | 8.007);;;; Solution Found
; States evaluated: 11
; Cost: 9.008
; Time 0.00
0.000: (robot_navigation armadillo corridor auditorium)  [1.000]
1.001: (robot_navigation armadillo auditorium corner_area)  [1.000]
2.002: (robot_navigation armadillo corner_area outside_lab211)  [1.000]
3.003: (sense_object armadillo can outside_lab211)  [1.000]
4.004: (pick_unknown armadillo can outside_lab211)  [1.000]
5.005: (robot_navigation armadillo outside_lab211 corner_area)  [1.000]
6.006: (robot_navigation armadillo corner_area auditorium)  [1.000]
7.007: (place_unknown armadillo can table3 auditorium)  [1.000]
8.008: (robot_navigation armadillo auditorium near_elevator1)  [1.000]
