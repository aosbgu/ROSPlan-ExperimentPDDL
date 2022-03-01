(define (problem task)
(:domain experiment_domain)
(:objects
    lab211 outside_lab211 auditorium corridor near_elevator1 open_area corner_area elevator1 - discrete_location
    up down - outer_elv_button
    armadillo - robot
    can table1 table2 table3 table4 - objects
)
(:init
    (can_act)

    (object_at table1 corridor)
    (object_at table2 lab211)
    (object_at table3 auditorium)
    (object_at table4 outside_lab211)

    (connected open_area near_elevator1)
    (connected open_area auditorium)
    (connected open_area corridor)
    (connected open_area corner_area)
    (connected corner_area outside_lab211)
    (connected lab211 outside_lab211)
    (connected corner_area auditorium)
    (connected corner_area corridor)
    (connected corner_area near_elevator1)
    (connected near_elevator1 corridor)
    (connected near_elevator1 auditorium)
    (connected auditorium corridor)
    (connected near_elevator1 elevator1)
    (connected near_elevator1 open_area)
    (connected auditorium open_area)
    (connected corridor open_area)
    (connected corner_area open_area)
    (connected outside_lab211 corner_area)
    (connected outside_lab211 lab211)
    (connected auditorium corner_area)
    (connected corridor corner_area)
    (connected near_elevator1 corner_area)
    (connected corridor near_elevator1)
    (connected auditorium near_elevator1)
    (connected corridor auditorium)
    (connected elevator1 near_elevator1)

    (possible_location can outside_lab211)

    (near armadillo corridor)

    (hand_empty armadillo)


    (buttton_associated up near_elevator1)

    (is_elevator elevator1)

    (pickable can)


)
(:goal (and
    (near armadillo near_elevator1)
    (object_at can auditorium)
))
)
